/* Created By RJudd January 9, 1999 */
/* SPAWARSYSCEN D881 */
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
/* $Id: vsip_fftm_destroy_f.c,v 2.0 2003/02/22 15:18:52 judd Exp $ */
/* destroy vsip vectors created in vsip_xxfftxx_create_f */
#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_fftmattributes_f.h>
#include"VI_cvalldestroy_f.h"

int vsip_fftm_destroy_f(vsip_fftm_f *fftm)
{
    #if defined(VSIP_USE_FFT_FOR_FFTM_F)
       if(fftm != NULL){
          vsip_fft_f* fft = (vsip_fft_f*) fftm->ext_fftm_obj;
          if(fft != NULL) vsip_fft_destroy_f(fft);
          free(fftm);
       } 
    #else
       if(fftm != NULL){
          VI_cvalldestroy_f(fftm->wt);
          VI_cvalldestroy_f(fftm->temp);
          free(fftm->pn);
          free(fftm->p0);
          free(fftm->pF);
          free(fftm->index);
          free(fftm);
       }
    #endif
    return 0;
}
