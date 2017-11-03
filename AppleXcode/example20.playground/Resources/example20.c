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
/* $Id: example20.c,v 2.0 2003/02/22 15:46:55 judd Exp $ */

#include<vsip.h>
#define N_data 4096
#define dec1   1
#define dec3   3
int  VU_vfrdB_d(vsip_vview_d*,vsip_scalar_d );
void VU_vfprintxyg_d(char*, vsip_vview_d*,
                     vsip_vview_d*, char*);
/* Start of main program*******************/
int main () { vsip_init((void*)0);
{ vsip_vview_d *kernel = 
        vsip_vcreate_kaiser_d(128,15.0,VSIP_MEM_NONE);
  vsip_randstate *r_state  =
        vsip_randcreate(11,1,1,VSIP_NPRNG);
  vsip_conv1d_d *conv;
  vsip_fir_d    *fir;
  vsip_vview_d *data  = vsip_vcreate_d(
        N_data,VSIP_MEM_NONE),
               *noise = vsip_vcreate_d(
        N_data,VSIP_MEM_NONE),
               *avg   = vsip_vcreate_d(
        N_data,VSIP_MEM_NONE);
  int i; vsip_length N_len;
  vsip_vputlength_d(data,
        (vsip_length)((N_data-1)/dec1)+1);
  vsip_vputlength_d(avg,
        (vsip_length)((N_data-1)/dec1)+1);
  conv = vsip_conv1d_create_d(
        kernel,VSIP_NONSYM,
        N_data,dec1,VSIP_SUPPORT_SAME,0,0);
  fir  = vsip_fir_create_d(
        kernel,VSIP_NONSYM, N_data,dec1,VSIP_STATE_SAVE,0,0);
  vsip_vfill_d(0,avg);
  for(i=0; i<10; i++){
         vsip_vrandn_d(r_state,noise);
         vsip_convolve1d_d(conv,noise,data);
         VU_vfrdB_d(data,1e-13);
         vsip_vsma_d(data,0.1,avg,avg);
  }
  N_len = vsip_vgetlength_d(avg);
  {  vsip_vview_d *x = vsip_vcreate_d(
           N_len,VSIP_MEM_NONE);
     vsip_vramp_d(-.5,1.0/(vsip_scalar_d)(N_len-1),x);
     VU_vfprintxyg_d("%8.6f %8.6f\n",x,avg,"conv_dec1");
     vsip_vdestroy_d(x);
  }
  vsip_vfill_d(0,avg);
   for(i=0; i<10; i++){
      vsip_vrandn_d(r_state,noise);
      vsip_firflt_d(fir,noise,data);
      VU_vfrdB_d(data,1e-13);
      vsip_vsma_d(data,0.1,avg,avg);
    }   
    N_len = vsip_vgetlength_d(avg);
    {  vsip_vview_d *x = vsip_vcreate_d(
             N_len,VSIP_MEM_NONE);
       vsip_vramp_d(-.5,1.0/(vsip_scalar_d)(N_len-1),x);
       VU_vfprintxyg_d("%8.6f %8.6f\n",x,avg,"fir_dec1");
       vsip_vdestroy_d(x);
    }
    vsip_conv1d_destroy_d(conv);
    vsip_fir_destroy_d(fir);
    conv = vsip_conv1d_create_d(
            kernel,VSIP_NONSYM,
            N_data,dec3,VSIP_SUPPORT_SAME,0,0);
    fir  = vsip_fir_create_d(
            kernel,VSIP_NONSYM,
            N_data,dec3,VSIP_STATE_SAVE,0,0);
    vsip_vputlength_d(data,
            (vsip_length)((N_data-1)/dec3)+1);
    vsip_vputlength_d(avg,
            (vsip_length)((N_data-1)/dec3)+1);
    vsip_vfill_d(0,avg);
    for(i=0; i<10; i++){
       vsip_vrandn_d(r_state,noise);
       vsip_convolve1d_d(conv,noise,data);
       VU_vfrdB_d(data,1e-13);
       vsip_vsma_d(data,0.1,avg,avg);
    }
    N_len = vsip_vgetlength_d(avg);
    {  vsip_vview_d *x = vsip_vcreate_d(
             N_len,VSIP_MEM_NONE);
       vsip_vramp_d(-.5,1.0/(vsip_scalar_d)(N_len - 1),x);
       VU_vfprintxyg_d("%8.6f %8.6f\n",
             x, avg,"conv_dec3");
       vsip_vdestroy_d(x);
    }
   vsip_vfill_d(0,avg);
    for(i=0; i<10; i++){
        vsip_vrandn_d(r_state,noise);
        vsip_firflt_d(fir,noise,data);
        VU_vfrdB_d(data,1e-13);
        vsip_vsma_d(data,0.1,avg,avg);
     }
     N_len = vsip_vgetlength_d(avg);
     {  vsip_vview_d *x = vsip_vcreate_d(
            N_len,VSIP_MEM_NONE);
        vsip_vramp_d(-.5,1.0/(vsip_scalar_d)(N_len-1),x);
        VU_vfprintxyg_d("%8.6f %8.6f\n",
            x, avg,"fir_dec3");
        vsip_vdestroy_d(x);
     }
     N_len = vsip_vgetlength_d(kernel);
     { vsip_vview_d *x = vsip_vcreate_d(
           N_len,VSIP_MEM_NONE);
       vsip_vramp_d(0,1,x);
       VU_vfprintxyg_d("%8.6f %8.6f\n",
             x,kernel,"kaiser_window");
       vsip_vramp_d(-.5,1.0/(vsip_scalar_d)(N_len-1),x);
       VU_vfrdB_d(kernel,1e-20);
       VU_vfprintxyg_d("%8.6f %8.6f\n",
             x,kernel,"Freq_Resp_Kaiser");
       vsip_vdestroy_d(x);
     }
  vsip_randdestroy(r_state);
  vsip_valldestroy_d(kernel);
  vsip_conv1d_destroy_d(conv);vsip_fir_destroy_d(fir);
  vsip_valldestroy_d(data); vsip_valldestroy_d(noise);
  vsip_valldestroy_d(avg);
  }vsip_finalize((void*)0);return 0;
}/*end of main program *******************************/

void VU_vfprintxyg_d(char* format,vsip_vview_d* x,
                    vsip_vview_d* y,char* fname)
{   vsip_length N = vsip_vgetlength_d(y);
    vsip_length i;
    FILE *of = fopen(fname,"w");
    for(i=0; i<N; i++)fprintf(of,
    format, vsip_vget_d(x,i),vsip_vget_d(y,i));
    fclose(of); return;
}

int VU_vfrdB_d(vsip_vview_d *a,vsip_scalar_d range)
{ int ret = 0;
  vsip_length N_len=vsip_vgetlength_d(a);
  vsip_cvview_d *ca=vsip_cvcreate_d(N_len,VSIP_MEM_NONE);
  vsip_fft_d *fft =   vsip_ccfftip_create_d(
       N_len,1,VSIP_FFT_FWD,0,0);
  vsip_vview_d *ra = vsip_vrealview_d(ca),
               *ia = vsip_vimagview_d(ca),
               *ta = vsip_vcloneview_d(a);
  vsip_offset s = (vsip_offset)vsip_vgetstride_d(ta);
  if((ca == NULL) || (fft == NULL) || (ra == NULL) ||
     (ia == NULL) || (ta == NULL)){ret =  1;
  }else{
     vsip_vfill_d(0,ia); vsip_vcopy_d_d(a,ra);
     vsip_ccfftip_d(fft,ca);
     vsip_vcmagsq_d(ca,ra);
     {  vsip_index ind;/* scale by "range" min to max*/
        vsip_scalar_d max = vsip_vmaxval_d(ra,&ind);
        vsip_scalar_d min = max * range;
        vsip_vclip_d(ra,min,max,min,max,ra);
     }
     if(N_len%2){vsip_length Nlen = N_len/2;
         vsip_vputlength_d(ta,Nlen+1);
         vsip_vputlength_d(ra,Nlen+1);
         vsip_vputoffset_d(ta,Nlen * s);
         vsip_vcopy_d_d(ra,ta);
         vsip_vputlength_d(ra,Nlen);
         vsip_vputlength_d(ta,Nlen);
         vsip_vputoffset_d(ta,vsip_vgetoffset_d(a));
         vsip_vputoffset_d(ra,Nlen+1);
         vsip_vcopy_d_d(ra,ta);
     }else{vsip_length Nlen = N_len/2;
         vsip_vcopy_d_d(ra,ta);
         vsip_vputlength_d(ta,Nlen);
         vsip_vputlength_d(a,Nlen);
         vsip_vputoffset_d(ta,(vsip_offset)(Nlen) * s);
         vsip_vswap_d(ta,a);
         vsip_vputlength_d(a,N_len);
      }vsip_vlog10_d(a,a);vsip_svmul_d(10,a,a);
   }vsip_fft_destroy_d(fft);
     vsip_vdestroy_d(ra); vsip_vdestroy_d(ia);
     vsip_cvalldestroy_d(ca);vsip_vdestroy_d(ta);
     return ret;
}
