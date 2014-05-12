#include<vsip.h>
#include<math.h>
#include<assert.h>

void mview_store_d(vsip_mview_d *M, char* fname)
{
   vsip_length RL = vsip_mgetrowlength_d(M);
   vsip_length CL = vsip_mgetcollength_d(M);
   FILE *of = fopen(fname,"w");
   vsip_length row,col;
   fprintf(of,"%s\n%ld %ld\n","mview_d",CL,RL);
   for(row = 0; row<CL; row++)
      for(col=0; col<RL; col++)
         fprintf(of,"%ld %ld %e\n",
                 row,col,vsip_mget_d(M,row,col));
   fclose(of);
   return;
}
vsip_mview_d *mcenter_d(vsip_mview_d *gram)
{
    vsip_index i;
    vsip_length cl=vsip_mgetcollength_d(gram),
                rl=vsip_mgetrowlength_d(gram);
    vsip_stride rs=vsip_mgetrowstride_d(gram),
                cs=vsip_mgetcolstride_d(gram);
    vsip_offset o = vsip_mgetoffset_d(gram);
    assert(rs == 1);
    assert(cs == (vsip_stride)rl);
    if (cl & 1){ // odd use freqswap for each column
        vsip_vview_d *v=vsip_mcolview_d(gram,0);
        for(i=0; i<rl; i++){
            vsip_vfreqswap_d(v);
            o += cs;
            vsip_vputoffset_d(v,o);
        }
        vsip_vdestroy_d(v);
    } else { // even number of columns use trick
        vsip_length lngth = (vsip_length)(cl * rl/2);
        vsip_vview_d *v1=vsip_mrowview_d(gram,0),*v2;
        vsip_vputlength_d(v1,lngth);
        v2=vsip_vcloneview_d(v1);
        vsip_vputoffset_d(v2,o+lngth);
        vsip_vswap_d(v1,v2);
        vsip_vdestroy_d(v1);
        vsip_vdestroy_d(v2);
    }
    return gram;
}
vsip_mview_d *cmscale_d(vsip_cmview_d *gram_data)
{
    vsip_scalar_mi indx;
    vsip_length M = vsip_cmgetcollength_d(gram_data);
    vsip_length N = vsip_cmgetrowlength_d(gram_data);
    vsip_mview_d *gram = vsip_mcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
    vsip_mcmagsq_d(gram_data,gram);
    vsip_smadd_d(1.0-vsip_mminval_d(gram,&indx),gram, gram);
    vsip_mlog10_d(gram,gram);
    vsip_smmul_d(256.0/vsip_mmaxval_d(gram,&indx),gram,gram);
    return mcenter_d(gram);
}
vsip_mview_d *noiseGen(
    vsip_scalar_d alpha, 
    vsip_length Mp,
    vsip_length Nn,
    vsip_length Ns)
{
    vsip_index i,j;
    vsip_scalar_d kaiser=9.0;
    vsip_length Nfilter=10,
                Nnoise=64;
    vsip_scalar_d cnst1=M_PI/(vsip_scalar_d)Nnoise;
    vsip_offset offset0 = (vsip_offset)(alpha * Mp + 1);
    vsip_vview_d *kernel=vsip_vcreate_kaiser_d(Nfilter,kaiser,VSIP_MEM_NONE);
    vsip_mview_d *data=vsip_mcreate_d(Mp,Ns,VSIP_ROW,VSIP_MEM_NONE);
    vsip_mview_d *noise=vsip_mcreate_d(Mp,Nn,VSIP_ROW,VSIP_MEM_NONE);
    vsip_vview_d *nv = vsip_vcreate_d(2 * Nn,VSIP_MEM_NONE);
    vsip_fir_d *fir =  \
            vsip_fir_create_d(kernel,VSIP_NONSYM,2*Nn,2,VSIP_STATE_SAVE,0,0);
    vsip_randstate *state = vsip_randcreate(15,1,1,VSIP_PRNG);
    vsip_mfill_d(0.0,data);
    for(j=0; j<Nnoise; j++){
        vsip_vview_d *noise_j=vsip_mrowview_d(noise,j);
        vsip_vrandn_d(state,nv);
        vsip_firflt_d(fir,nv,noise_j);
        vsip_svmul_d(12.0/(float)Nnoise,noise_j,noise_j);
        vsip_vdestroy_d(noise_j);
    }
    vsip_mputrowlength_d(noise,Ns);
    for(i=0; i<Mp; i++){//for each sensor
        vsip_vview_d *data_v = vsip_mrowview_d(data,i);
        for(j=0; j<Nnoise; j++){//for each noise direction
            vsip_vview_d *noise_j = vsip_mrowview_d(noise,j);
            vsip_vputoffset_d(noise_j,offset0 +(int)( i * alpha * cos(j * cnst1)));
            vsip_vadd_d(noise_j,data_v,data_v);
            vsip_vdestroy_d(noise_j);
        }
        vsip_vdestroy_d(data_v);
    }
    vsip_valldestroy_d(kernel);
    vsip_valldestroy_d(nv);
    vsip_malldestroy_d(noise);
    return data;
}
vsip_mview_d *narrowBandGen(
       vsip_mview_d *data,
       vsip_scalar_d alpha,
       void **targets,
       vsip_scalar_d Fs)
{
    vsip_index i,j;
    vsip_length M=vsip_mgetcollength_d(data);
    vsip_length N = vsip_mgetrowlength_d(data);
    vsip_vview_d *t = vsip_vcreate_d(N,VSIP_MEM_NONE);
    vsip_vview_d *tt= vsip_vcreate_d(N,VSIP_MEM_NONE);
    vsip_mview_d *Xim = vsip_mcreate_d(M,M+1,VSIP_ROW,VSIP_MEM_NONE);
    vsip_vview_d *m = vsip_vcreate_d(M,VSIP_MEM_NONE);
    vsip_vview_d *Xi = vsip_vcreate_d(M + 1,VSIP_MEM_NONE);
    vsip_vview_d *freq=(vsip_vview_d*)targets[0];
    vsip_vview_vi *bearing=(vsip_vview_vi*)targets[1];
    vsip_vview_d *scale=(vsip_vview_d*)targets[2];
    vsip_vramp_d(0.0,1.0,t);
    vsip_vramp_d(0.0,M_PI/(vsip_scalar_d)M,Xi);
    vsip_vcos_d(Xi,Xi);
    vsip_vramp_d(0,1.0,m);
    vsip_vouter_d(alpha,m,Xi,Xim);
    for(i=0; i<M; i++){//for each sensor
        vsip_vview_d *data_v = vsip_mrowview_d(data,i);
        for(j=0; j<vsip_vgetlength_d(freq); j++){//for each noise direction
            vsip_scalar_d f=vsip_vget_d(freq,j);
            vsip_scalar_d w0=vsip_vget_d(freq,j) * 2.0 * M_PI/(vsip_scalar_d)Fs;
            vsip_index Theta=vsip_vget_vi(bearing,j);
            vsip_scalar_d sc = vsip_vget_d(scale,j);
            vsip_scalar_d Xim_val = vsip_mget_d(Xim,i,Theta);
            vsip_vsmsa_d(t,w0,-w0*Xim_val,tt);
            vsip_vcos_d(tt,tt);
            vsip_svmul_d(sc,tt,tt);
            vsip_vadd_d(tt,data_v,data_v);
        }
        vsip_vdestroy_d(data_v);
    } 
    vsip_valldestroy_d(tt);
    vsip_valldestroy_d(t);
    vsip_valldestroy_d(m);
    vsip_malldestroy_d(Xim);
    vsip_valldestroy_d(Xi);
    return data;
}
    