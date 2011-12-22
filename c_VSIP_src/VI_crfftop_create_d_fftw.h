/* Created By RJudd June 16, 2002 */
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
/* $Id: VI_crfftop_create_d_fftw.h,v 2.1 2003/03/08 14:43:33 judd Exp $ */
/* complex to real fft */

#include"VI_fft_building_blocks_d.h"
#define __VSIPL_FFTWOBJ_INIT
#define __VSIPL_FFTWOBJ_FIN
#include"VI_fftw_obj.h"
#include"VI_vrealview_d.h"
#include"VI_vimagview_d.h"

vsip_fft_d* vsip_crfftop_create_d(vsip_length N,
                       vsip_scalar_d scale,
                       unsigned int ntimes,
                       vsip_alg_hint hint)
{
    vsip_fft_d *fft = (vsip_fft_d*) malloc(sizeof(vsip_fft_d));
    vsipl_fftw_obj *obj;
    fftw_direction fftw_dir = FFTW_BACKWARD;
    int flags = (hint == VSIP_ALG_TIME) ? FFTW_MEASURE : FFTW_ESTIMATE;
    int init;

    if(fft == NULL) return (vsip_fft_d*) NULL;

    fft->N = N/2;
    fft->scale = scale;
    fft->d = VSIP_FFT_INV;
    fft->pn = NULL;
    fft->p0 = NULL;
    fft->pF = NULL;
    fft->wt = (vsip_cvview_d*)NULL;
    fft->index = (NULL);
    fft->hint = hint;
    fft->ntimes = ntimes; 
    fft->type = VSIP_CRFFTOP; 

    fft->temp = vsip_cvcreate_d(fft->N+1,VSIP_MEM_NONE); 
    init = vsipl_fftwobj_init(&obj,fftw_dir,fft->N,flags);
    
    /* need some storage to keep from overwriting input */
    if(obj->in == NULL){
         obj->in = (fftw_complex*)malloc(fft->N * sizeof(fftw_complex));
    }
    if(obj->in == NULL) init++;

    if((init!=0) || (fft->temp == (vsip_cvview_d*)NULL)){
       if(init != 0) vsipl_fftwobj_fin(obj);
       if(fft->temp != NULL) vsip_cvdestroy_d(fft->temp);
       free(fft);
       return (vsip_fft_d*)NULL;
    }

    fft->ext_fft_obj = (void*)obj;
    {
        vsip_vview_d wt1,wt2;
        vsip_vview_d *wtR = VI_vrealview_d(fft->temp,&wt1);
        vsip_vview_d *wtI = VI_vimagview_d(fft->temp,&wt2); 
        vsip_vramp_d((vsip_scalar_d)0, (vsip_scalar_d)VI_ft_d_PI/fft->N,wtR);
        vsip_vsin_d(wtR,wtI);
        vsip_vcos_d(wtR,wtR);
    }
    return fft;
}
