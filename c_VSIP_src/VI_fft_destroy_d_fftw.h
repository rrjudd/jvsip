/* Created By RJudd June 10, 2002 */
/* SPAWARSYSCEN code 2857         */
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
/* $Id: VI_fft_destroy_d_fftw.h,v 2.0 2003/02/22 15:18:32 judd Exp $ */
/* fft if fftw is defined */
#include<vsip.h>
#include<vsip_fftattributes_d.h>
#define __VSIPL_FFTWOBJ_FIN
#include"VI_fftw_obj.h"
#include"VI_cvalldestroy_d.h"

int vsip_fft_destroy_d(vsip_fft_d *fft)
{
    if(fft != NULL){
       vsipl_fftw_obj *obj = (vsipl_fftw_obj*)fft->ext_fft_obj;
       if(fft->wt != NULL)VI_cvalldestroy_d(fft->wt);
       if(fft->temp != NULL)VI_cvalldestroy_d(fft->temp);
       if(fft->pn != NULL)free(fft->pn);
       if(fft->p0 != NULL)free(fft->p0);
       if(fft->pF != NULL)free(fft->pF);
       if(fft->index != NULL)free(fft->index);
       vsipl_fftwobj_fin(obj);
       free(fft);
    }
    return 0;
}
