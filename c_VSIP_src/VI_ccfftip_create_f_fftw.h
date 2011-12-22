/* Created By RJudd June 10, 2002 */
/* SPAWARSYSCEN D881              */
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
/* $Id: VI_ccfftip_create_f_fftw.h,v 2.0 2003/02/22 15:18:29 judd Exp $ */
/* use fftw to calculate fft */

#define __VSIPL_FFTWOBJ_INIT
#define __VSIPL_FFTWOBJ_FIN
#include"VI_fftw_obj.h"
#include"VI_cvalldestroy_f.h"

vsip_fft_f* vsip_ccfftip_create_f(vsip_length N,
                       vsip_scalar_f scale,
                       vsip_fft_dir dir,
                       unsigned int ntimes,
                       vsip_alg_hint hint)
{
    vsipl_fftw_obj *obj;	
    fftw_direction fftw_dir;
    int flags;
    int init;
    vsip_fft_f *fft = (vsip_fft_f*) malloc(sizeof(vsip_fft_f));
    if(fft == NULL) return (vsip_fft_f*) NULL;
    
    if(dir == VSIP_FFT_FWD) fftw_dir = FFTW_FORWARD;
    else fftw_dir = FFTW_BACKWARD;

    if(hint == VSIP_ALG_TIME) flags = FFTW_MEASURE;
    else flags = FFTW_ESTIMATE;

    init = vsipl_fftwobj_init(&obj,fftw_dir,N,flags);
    #if defined(VSIP_ASSUME_COMPLEX_IS_INTERLEAVED)
       fft->temp = vsip_cvcreate_f(N,VSIP_MEM_NONE);
       if((init != 0) || (fft->temp == NULL)){
          vsipl_fftwobj_fin(obj);
          if(fft->temp != NULL) VI_cvalldestroy_f(fft->temp);
          free(fft);
          return (vsip_fft_f*)NULL;
       } 
    #else
       fft->temp = (vsip_cvview_f*)NULL;
       if(init != 0){
          vsipl_fftwobj_fin(obj);
          free(fft);
          return (vsip_fft_f*)NULL;
       }
    #endif
    fft->ext_fft_obj = (void*)obj;

    fft->N = N;
    fft->scale  = scale;
    fft->d      = dir;
    fft->hint   = hint;
    fft->ntimes = ntimes; 
    fft->type   = VSIP_CCFFTIP; 
    fft->pn     = NULL;
    fft->p0     = NULL;
    fft->pF     = NULL;
    fft->index  = NULL;
    fft->wt     = (vsip_cvview_f*)NULL;
    
    return fft;
}
