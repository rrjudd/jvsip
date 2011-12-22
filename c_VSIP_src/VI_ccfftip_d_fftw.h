/* Created by RJudd June 10, 2002 */
/* SPAWARSYSCEN code 2857 */
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
/* $Id: VI_ccfftip_d_fftw.h,v 2.0 2003/02/22 15:18:29 judd Exp $ */
/* use fftw for calculation */
#include<vsip.h>
#include<vsip_fftattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#if !defined(VSIP_ASSUME_COMPLEX_IS_INTERLEAVED)
   #define __VSIPL_CVCOPY_TO_FFTW_D
   #define __VSIPL_CVCOPY_FROM_FFTW_D
#endif
#include"VI_fftw_obj.h"

/*========================================================*/
void vsip_ccfftip_d(const vsip_fft_d *Offt, 
                    const vsip_cvview_d *x)
{
     vsip_fft_d Nfft = *Offt;
     vsip_fft_d *fft = &Nfft;
     vsipl_fftw_obj *obj = (vsipl_fftw_obj*)fft->ext_fft_obj;
     #if defined(VSIP_ASSUME_COMPLEX_IS_INTERLEAVED)
        fftw_complex *in, *out;
        vsip_cvview_d *z = fft->temp;
        int howmany = 1;
        int istride = (int)(z->stride);
        int ostride = (int)(x->stride);
        int idist = 1,
            odist = 1;
        vsip_cvcopy_d_d(x,z);
        in  = (fftw_complex*)(z->block->R->array + z->offset * z->block->R->rstride);
        out = (fftw_complex*)(x->block->R->array + x->offset * x->block->R->rstride);
        fftw(obj->p,howmany,in,istride,idist,out,ostride,odist);
     #else
        vsipl_cvcopy_to_fftw_d(x,obj);
        fftw_one(obj->p,obj->in,obj->out);
        vsipl_cvcopy_from_fftw_d(obj,x);
     #endif
     if (fft->scale != 1) vsip_rscvmul_d(fft->scale,x,x);
     return;
}
