/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/

#include<vsip.h>
#define N_data 24576
#define dec1   1
#define dec3   3
int  VU_vfrdB_f(vsip_vview_f*,vsip_scalar_f );
void VU_vfprintxyg_f(char*, vsip_vview_f*,
                     vsip_vview_f*, char*);
int main () {
vsip_init((void*)0);
{ vsip_vview_f *kernel = 
        vsip_vcreate_kaiser_f(128,15.0,VSIP_MEM_NONE);
  vsip_randstate *r_state  =
        vsip_randcreate(11,1,1,VSIP_NPRNG);
  vsip_conv1d_f *conv;
  vsip_fir_f    *fir;
  vsip_vview_f *data  = vsip_vcreate_f(
        2 * N_data,VSIP_MEM_NONE),
               *noise = vsip_vcreate_f(
        3 * N_data,VSIP_MEM_NONE),
               *avg   = vsip_vcreate_f(
        4 * N_data,VSIP_MEM_NONE);
  int i; vsip_length N_len;
  vsip_vputlength_f(data,
        (vsip_length)((N_data-1)/dec1)+1);
  vsip_vputlength_f(avg,
        (vsip_length)((N_data-1)/dec1)+1);
  vsip_vputstride_f(data,2);
  vsip_vputstride_f(avg,4);
  vsip_vputlength_f(noise,N_data); vsip_vputstride_f(noise,3);
  conv = vsip_conv1d_create_f(
        kernel,VSIP_NONSYM,
        N_data,dec1,VSIP_SUPPORT_SAME,0,0);
  fir  = vsip_fir_create_f(
        kernel,VSIP_NONSYM, N_data,dec1,VSIP_STATE_NO_SAVE,0,0);
  vsip_vfill_f(0,avg);
  for(i=0; i<10; i++){
         vsip_vrandn_f(r_state,noise);
         vsip_convolve1d_f(conv,noise,data);
         VU_vfrdB_f(data,1e-13);
         vsip_vsma_f(data,0.1,avg,avg);
  }
  N_len = vsip_vgetlength_f(avg);
  {  vsip_vview_f *x = vsip_vcreate_f(
           N_len,VSIP_MEM_NONE);
     vsip_vramp_f(-.5,1.0/(vsip_scalar_f)(N_len-1),x);
     VU_vfprintxyg_f("%8.6f %8.6f\n",x,avg,"conv_dec1");
     vsip_vdestroy_f(x);
  }
   vsip_vfill_f(0,avg);
   for(i=0; i<10; i++){
      vsip_vrandn_f(r_state,noise);
      vsip_firflt_f(fir,noise,data);
      VU_vfrdB_f(data,1e-13);
      vsip_vsma_f(data,0.1,avg,avg);
    }   
    N_len = vsip_vgetlength_f(avg);
    {  vsip_vview_f *x = vsip_vcreate_f(
             N_len,VSIP_MEM_NONE);
       vsip_vramp_f(-.5,1.0/(vsip_scalar_f)(N_len-1),x);
       VU_vfprintxyg_f("%8.6f %8.6f\n",x,avg,"fir_dec1");
       vsip_vdestroy_f(x);
    }
    vsip_conv1d_destroy_f(conv);
    vsip_fir_destroy_f(fir);
    conv = vsip_conv1d_create_f(
            kernel,VSIP_NONSYM,
            N_data,dec3,VSIP_SUPPORT_SAME,0,0);
    fir  = vsip_fir_create_f(
            kernel,VSIP_NONSYM,
            N_data,dec3,VSIP_STATE_NO_SAVE,0,0);
    vsip_vputlength_f(data,
            (vsip_length)((N_data-1)/dec3)+1);
    vsip_vputlength_f(avg,
            (vsip_length)((N_data-1)/dec3)+1);
    vsip_vfill_f(0,avg);
    for(i=0; i<10; i++){
       vsip_vrandn_f(r_state,noise);
       vsip_convolve1d_f(conv,noise,data);
       VU_vfrdB_f(data,1e-13);
       vsip_vsma_f(data,0.1,avg,avg);
    }
    N_len = vsip_vgetlength_f(avg);
    {  vsip_vview_f *x = vsip_vcreate_f(
             N_len,VSIP_MEM_NONE);
       vsip_vramp_f(-.5,1.0/(vsip_scalar_f)(N_len - 1),x);
       VU_vfprintxyg_f("%8.6f %8.6f\n",
             x, avg,"conv_dec3");
       vsip_vdestroy_f(x);
    }
   vsip_vfill_f(0,avg);
    for(i=0; i<10; i++){
        vsip_vrandn_f(r_state,noise);
        vsip_firflt_f(fir,noise,data);
        VU_vfrdB_f(data,1e-13);
        vsip_vsma_f(data,0.1,avg,avg);
     }
     N_len = vsip_vgetlength_f(avg);
     {  vsip_vview_f *x = vsip_vcreate_f(
            N_len,VSIP_MEM_NONE);
        vsip_vramp_f(-.5,1.0/(vsip_scalar_f)(N_len-1),x);
        VU_vfprintxyg_f("%8.6f %8.6f\n",
            x, avg,"fir_dec3");
        vsip_vdestroy_f(x);
     }
     N_len = vsip_vgetlength_f(kernel);
     { vsip_vview_f *x = vsip_vcreate_f(
           N_len,VSIP_MEM_NONE);
       vsip_vramp_f(0,1,x);
       VU_vfprintxyg_f("%8.6f %8.6f\n",
             x,kernel,"kaiser_window");
       vsip_vramp_f(-.5,1.0/(vsip_scalar_f)(N_len-1),x);
       VU_vfrdB_f(kernel,1e-20);
       VU_vfprintxyg_f("%8.6f %8.6f\n",
             x,kernel,"Freq_Resp_Kaiser");
       vsip_vdestroy_f(x);
     }
  vsip_randdestroy(r_state);
  vsip_valldestroy_f(kernel);
  vsip_conv1d_destroy_f(conv);vsip_fir_destroy_f(fir);
  vsip_valldestroy_f(data); vsip_valldestroy_f(noise);
  vsip_valldestroy_f(avg);
  } vsip_finalize((void*)0); return 0;
}/*end of main program *******************************/

void VU_vfprintxyg_f(char* format,vsip_vview_f* x,
                    vsip_vview_f* y,char* fname)
{   vsip_length N = vsip_vgetlength_f(y);
    vsip_length i;
    FILE *of = fopen(fname,"w");
    for(i=0; i<N; i++)fprintf(of,
    format, vsip_vget_f(x,i),vsip_vget_f(y,i));
    fclose(of); return;
}
int VU_vfrdB_f(vsip_vview_f *a,vsip_scalar_f range)
{ int ret = 0;
  vsip_length N_len=vsip_vgetlength_f(a);
  vsip_cvview_f *ca=vsip_cvcreate_f(N_len,VSIP_MEM_NONE);
  vsip_fft_f *fft =   vsip_ccfftip_create_f(
       N_len,1,VSIP_FFT_FWD,0,0);
  vsip_vview_f *ra = vsip_vrealview_f(ca),
               *ia = vsip_vimagview_f(ca),
               *ta = vsip_vcloneview_f(a);
  vsip_offset s = (vsip_offset)vsip_vgetstride_f(ta);
  if((ca == NULL) || (fft == NULL) || (ra == NULL) ||
     (ia == NULL) || (ta == NULL)){ret =  1;
  }else{
     vsip_vfill_f(0,ia); vsip_vcopy_f_f(a,ra);
     vsip_ccfftip_f(fft,ca);
     vsip_vcmagsq_f(ca,ra);
     {  vsip_index ind;/* scale by "range" min to max*/
        vsip_scalar_f max = vsip_vmaxval_f(ra,&ind);
        vsip_scalar_f min = max * range;
        vsip_vclip_f(ra,min,max,min,max,ra);
     }
     if(N_len%2){vsip_length Nlen = N_len/2;
         vsip_vputlength_f(ta,Nlen+1);
         vsip_vputlength_f(ra,Nlen+1);
         vsip_vputoffset_f(ta,Nlen * s);
         vsip_vcopy_f_f(ra,ta);
         vsip_vputlength_f(ra,Nlen);
         vsip_vputlength_f(ta,Nlen);
         vsip_vputoffset_f(ta,vsip_vgetoffset_f(a));
         vsip_vputoffset_f(ra,Nlen+1);
         vsip_vcopy_f_f(ra,ta);
     }else{vsip_length Nlen = N_len/2;
         vsip_vcopy_f_f(ra,ta);
         vsip_vputlength_f(ta,Nlen);
         vsip_vputlength_f(a,Nlen);
         vsip_vputoffset_f(ta,(vsip_offset)(Nlen) * s);
         vsip_vswap_f(ta,a);
         vsip_vputlength_f(a,N_len);
      }vsip_vlog10_f(a,a);vsip_svmul_f(10,a,a);
   }vsip_fft_destroy_f(fft);
     vsip_vdestroy_f(ra); vsip_vdestroy_f(ia);
     vsip_cvalldestroy_f(ca);vsip_vdestroy_f(ta);
     return ret;
}
