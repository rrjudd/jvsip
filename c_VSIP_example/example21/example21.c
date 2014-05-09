#include <vsip.h>

/* Parameters */
#define D 1.5      /* sensor spacing meters */
#define Fs 1000    /* sample rate Hz */
#define F0 450     /* some frequencys for a target */
#define F1 300
#define F2 150
#define F3 50
#define Theta_o 40 /* beam number of narrow band tones */
#define Ns 512     /* samples in a time series */
#define Nn 1024    /* sample in a noise series */
#define Mp 128     /* hydrophones in linear arary */
#define c 1500     /* propagation speed */
#define Nnoise 64  /* number of noise directions */
#define kaiser 9   /* window parameter */
#define Nfilter 10 /* kernel length for noise filter */

/* A method to save the output */
void VU_mprintgram_d(vsip_mview_d* M,char* fname)
{   vsip_length RL = vsip_mgetrowlength_d(M);
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

vsip_mview_d *noiseGen(){
    vsip_index i,j;
    for(j=0; j<Nnoise; j++){
        noise[j] = vsip_vcreate_d(Nn,0);
      vsip_vrandn_d(state,nv);
      vsip_firflt_d(fir,nv,noise[j]);
      vsip_svmul_d(12.0/(Nnoise),noise[j],noise[j]);
      vsip_vputlength_d(noise[j],Ns);
   }
   for(i=0; i<Mp; i++){
      vsip_scalar_d Xim_val = vsip_mget_d(Xim,i,Theta_o);
      data_v = vsip_mrowview_d(data,i);
      vsip_vsmsa_d(t,w0,-w0 * Xim_val,tt);
      vsip_vcos_d(tt,data_v); /*F0 time series */
      vsip_vsmsa_d(t,w1,-w1 * Xim_val,tt);
      vsip_vcos_d(tt,tt); /*F1 time series */
      vsip_vadd_d(tt,data_v,data_v);
      vsip_vsmsa_d(t,w2,-w2 * Xim_val,tt);
      vsip_vcos_d(tt,tt); /*F2 time series */
      vsip_vadd_d(tt,data_v,data_v);
      vsip_vsmsa_d(t,w3,-w3 * Xim_val,tt);
      vsip_vcos_d(tt,tt); /*F3 time series */
      vsip_svmul_d(3.0,tt,tt); /* scale by 3.0 */
      vsip_vadd_d(tt,data_v,data_v);
      vsip_svmul_d(3,data_v,data_v);
      for(j=0; j<Nnoise; j++){
         /* simple time delay beam forming for noise */
         vsip_vputoffset_d(noise[j],offset0 +
                           (int)( i * alpha * cos(j * cnst1)));
         vsip_vadd_d(noise[j],data_v,data_v);
      }
      /* need to destroy before going on to next phone */
      vsip_vdestroy_d(data_v);
   }

int main(){
   int init = vsip_init((void*)0);
   int i,j; /* counters */
   vsip_vview_d *windowt = vsip_vcreate_hanning_d(Ns,0);
   vsip_vview_d *windowp = vsip_vcreate_hanning_d(Mp,0);
   vsip_vview_d *kernel = vsip_vcreate_kaiser_d(Nfilter,kaiser,0);
   vsip_fir_d *fir = vsip_fir_create_d(kernel,VSIP_NONSYM,2 * Nn,2,VSIP_STATE_SAVE,0,0);
   vsip_vview_d *t =vsip_vcreate_d(Ns,0); /*time vector*/
   vsip_vview_d *noise[Nnoise];
   vsip_vview_d *nv = vsip_vcreate_d(2 * Nn,0);
   vsip_vview_d *tt = vsip_vcreate_d(Ns,0);
   vsip_mview_d *data = vsip_mcreate_d(Mp,Ns,VSIP_ROW,0),*rmview;
   vsip_vview_d *data_v, *gram_v;
   vsip_cvview_d *gram_data_v;
   vsip_cmview_d *gram_data = vsip_cmcreate_d(Mp,Ns/2 + 1,VSIP_COL,0);
   vsip_mview_d  *gram = vsip_mcreate_d(Mp,Ns/2 + 1,VSIP_ROW,0);
   vsip_mview_d  *Xim = vsip_mcreate_d(Mp,Mp+1,VSIP_ROW,0);
   vsip_scalar_d alpha = (D * Fs) / c;
   vsip_vview_d *m = vsip_vcreate_d(Mp,0);
   vsip_vview_d *Xi = vsip_vcreate_d(Mp + 1,0);
   vsip_randstate *state = vsip_randcreate(15,1,1,VSIP_PRNG);
   vsip_scalar_d w0 = 2 * M_PI * F0/Fs;
   vsip_scalar_d w1 = 2 * M_PI * F1/Fs;
   vsip_scalar_d w2 = 2 * M_PI * F2/Fs;
   vsip_scalar_d w3 = 2 * M_PI * F3/Fs;
   vsip_scalar_d cnst1 = M_PI/Nnoise;
   vsip_offset offset0 = (vsip_offset)(alpha * Mp + 1);
   vsip_fftm_d *rcfftmop_obj = vsip_rcfftmop_create_d(Mp,Ns,1,VSIP_ROW,0,0);/* time fft */
   vsip_fftm_d *ccfftmip_obj =vsip_ccfftmip_create_d(Mp,Ns/2 +1,VSIP_FFT_FWD,1,VSIP_COL,0,0);
   if(init) exit(-1);
   /* start calculations */
   vsip_vramp_d(0,1.0,t); /* time vector */
   vsip_vramp_d(0,1,m);
   vsip_vramp_d(0,M_PI/Mp,Xi);
   vsip_vcos_d(Xi,Xi);
   vsip_vouter_d(alpha,m,Xi,Xim);
   vsip_mfill_d(0.0,gram);
   /* create some coherent directional broadband noise from Nnoise bearings */
   for(j=0; j<Nnoise; j++){
      noise[j] = vsip_vcreate_d(Nn,0);
      vsip_vrandn_d(state,nv);
      vsip_firflt_d(fir,nv,noise[j]);
      vsip_svmul_d(12.0/(Nnoise),noise[j],noise[j]);
      vsip_vputlength_d(noise[j],Ns);
   }
   for(i=0; i<Mp; i++){
      vsip_scalar_d Xim_val = vsip_mget_d(Xim,i,Theta_o);
      data_v = vsip_mrowview_d(data,i);
      vsip_vsmsa_d(t,w0,-w0 * Xim_val,tt);
      vsip_vcos_d(tt,data_v); /*F0 time series */
      vsip_vsmsa_d(t,w1,-w1 * Xim_val,tt);
      vsip_vcos_d(tt,tt); /*F1 time series */
      vsip_vadd_d(tt,data_v,data_v);
      vsip_vsmsa_d(t,w2,-w2 * Xim_val,tt);
      vsip_vcos_d(tt,tt); /*F2 time series */
      vsip_vadd_d(tt,data_v,data_v);
      vsip_vsmsa_d(t,w3,-w3 * Xim_val,tt);
      vsip_vcos_d(tt,tt); /*F3 time series */
      vsip_svmul_d(3.0,tt,tt); /* scale by 3.0 */
      vsip_vadd_d(tt,data_v,data_v);
      vsip_svmul_d(3,data_v,data_v);
      for(j=0; j<Nnoise; j++){
         /* simple time delay beam forming for noise */
         vsip_vputoffset_d(noise[j],offset0 +
                           (int)( i * alpha * cos(j * cnst1)));
         vsip_vadd_d(noise[j],data_v,data_v);
      }
      /* need to destroy before going on to next phone */
      vsip_vdestroy_d(data_v);
   }
   /* window the data and the array to reduce sidelobes */
   vsip_vmmul_d(windowt,data,VSIP_ROW,data);
   vsip_vmmul_d(windowp,data,VSIP_COL,data);
   
   /* do ffts */
   vsip_rcfftmop_d(rcfftmop_obj,data,gram_data);
   vsip_ccfftmip_d(ccfftmip_obj,gram_data);
   
   { /* scale gram to db, min 0 max 255 */
      vsip_index ind;
      gram_v = vsip_mrowview_d(gram,0);
      gram_data_v = vsip_cmcolview_d(gram_data,0);
      rmview = vsip_mrealview_d(gram_data);
      vsip_vputlength_d(gram_v,Mp*(Ns/2 + 1));
      vsip_cvputlength_d(gram_data_v,Mp*(Ns/2 + 1));
      data_v = vsip_vrealview_d(gram_data_v);
      vsip_vcmagsq_d(gram_data_v,data_v);
      vsip_mcopy_d_d(rmview,gram);
      vsip_vdestroy_d(data_v);
      vsip_svadd_d(1.0 -
                   vsip_vminval_d(gram_v,&ind),gram_v,gram_v);
      vsip_vlog10_d(gram_v,gram_v);
      vsip_svmul_d(256.0 / vsip_vmaxval_d(gram_v,&ind),
                   gram_v,gram_v);/* scale */
      /* reorganize the data to place zero in the center for direction space */
      data_v = vsip_vcloneview_d(gram_v);
      vsip_vputlength_d(data_v,(Mp/2) * (Ns/2 + 1));
      vsip_vputoffset_d(data_v,(Mp/2) * (Ns/2 + 1));
      vsip_vputlength_d(gram_v,(Mp/2) * (Ns/2 + 1));
      vsip_vswap_d(data_v,gram_v);
      vsip_vdestroy_d(gram_v);
      vsip_vdestroy_d(data_v);
      vsip_cvdestroy_d(gram_data_v);
      vsip_mdestroy_d(rmview);
   }
   VU_mprintgram_d(gram,"gram_output");
   vsip_finalize((void*)0); return 0;
}

