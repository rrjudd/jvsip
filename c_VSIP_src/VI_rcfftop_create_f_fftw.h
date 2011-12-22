/* Created By RJudd October 14, 1998 */
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
/* $Id: VI_rcfftop_create_f_fftw.h,v 2.0 2003/02/22 15:18:33 judd Exp $ */
/* real to complex fft */
#ifndef _VI_RCFFTOP_CREATE_F_FFTW_H
#define _VI_RCFFTOP_CREATE_F_FFTW_H

/* selectively include functions in fftw_obj */
#define __VSIPL_FFTWOBJ_INIT
#define __VSIPL_FFTWOBJ_FIN
#include"VI_vrealview_f.h"
#include"VI_vimagview_f.h"
#include"VI_vramp_f.h"
#include"VI_vcos_f.h"
#include"VI_vsin_f.h"
#include"VI_fftw_obj.h"
#define VI_ft_f_PI  3.1415926535897932384626433

/* For this function N is required to be even */
vsip_fft_f* vsip_rcfftop_create_f(
          vsip_length N,
          vsip_scalar_f scale,
          unsigned int ntimes,
          vsip_alg_hint hint)
{
    vsip_fft_f *fft = (vsip_fft_f*) malloc(sizeof(vsip_fft_f));
    vsipl_fftw_obj *obj;
    fftw_direction fftw_dir = FFTW_FORWARD;
    int flags = (hint == VSIP_ALG_TIME) ? FFTW_MEASURE : FFTW_ESTIMATE;
    int init;

    if(fft == NULL) return (vsip_fft_f*) NULL;

    fft->N = N/2;
    fft->scale = scale;
    fft->d = VSIP_FFT_FWD;
    fft->pn = NULL;
    fft->p0 = NULL;
    fft->pF = NULL;
    fft->wt = (vsip_cvview_f*)NULL;
    fft->index = (NULL);
    fft->hint = hint;
    fft->ntimes = ntimes; 
    fft->type = VSIP_RCFFTOP; 

    fft->temp = vsip_cvcreate_f(fft->N,VSIP_MEM_NONE); 
    init = vsipl_fftwobj_init(&obj,fftw_dir,fft->N,flags);

    if((init!=0) || (fft->temp == (vsip_cvview_f*)NULL)){
       if(init != 0) vsipl_fftwobj_fin(obj);
       if(fft->temp != NULL) vsip_cvdestroy_f(fft->temp);
       free(fft);
       return (vsip_fft_f*)NULL;
    }
    fft->ext_fft_obj = (void*)obj;

    {
        vsip_vview_f wt1,wt2;
        vsip_vview_f *wtR = VI_vrealview_f(fft->temp,&wt1);
        vsip_vview_f *wtI = VI_vimagview_f(fft->temp,&wt2); 
        VI_vramp_f((vsip_scalar_f)0,(vsip_scalar_f)VI_ft_f_PI/fft->N,wtR);
        VI_vsin_f(wtR,wtI);
        VI_vcos_f(wtR,wtR);
    }
    return fft;
}

#endif /* _VI_RCFFTOP_CREATE_F_FFTW_H */
