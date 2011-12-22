/* Created by RJudd June 15, 2002 */
/* SPAWARSYSCEN Code 2857 */
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
/* $Id: VI_crfftop_d_fftw.h,v 2.1 2003/03/08 14:43:33 judd Exp $ */

/* Note that the spec requires x and z views to be unit stride */

#include"VI_fftw_obj.h"

void 
vsip_crfftop_d(
           const vsip_fft_d    *Offt, 
           const vsip_cvview_d *z,
           const vsip_vview_d  *x)
{
   vsip_fft_d Nfft = *Offt;
   vsip_fft_d *fft = &Nfft;
   vsip_scalar_d scale = fft->scale;
   
   vsipl_fftw_obj *obj = (vsipl_fftw_obj*)fft->ext_fft_obj;
   
   vsip_length n = fft->N;
   
   vsip_cvview_d *w = fft->temp;
   vsip_stride wst = w->stride * w->block->R->rstride;
   vsip_scalar_d *wpr = (vsip_scalar_d *)((w->block->R->array) + wst * w->offset),
                 *wpi = (vsip_scalar_d *)((w->block->I->array) + wst * w->offset);
   
   vsip_stride fst = z->block->R->rstride;
   vsip_stride bst = -fst;
   vsip_scalar_d *fpr = (vsip_scalar_d *)((z->block->R->array) + fst * z->offset),
                 *bpr = (vsip_scalar_d *)((z->block->R->array) + fst * (z->offset + n)),
                 *fpi = (vsip_scalar_d *)((z->block->I->array) + fst * z->offset),
                 *bpi = (vsip_scalar_d *)((z->block->I->array) + fst * (z->offset + n));

   vsip_stride xst = x->block->rstride;
   vsip_scalar_d *xptr = (vsip_scalar_d *)((x->block->array) + x->offset * xst);

   fftw_complex *in = obj->in;

   if(scale == 1){
      (*in).re = (*fpr + *bpr);
      (*in).im = (*fpr - *bpr);
      while(n-- > 1){
         in++;
         wpr += wst; wpi += wst;
         fpr += fst; fpi += fst;
         bpr += bst; bpi += bst;
         (*in).re = (*fpr + *bpr + *wpi * (*bpr - *fpr) - *wpr * (*fpi + *bpi));
         (*in).im = (*fpi - *bpi - *wpi * (*fpi + *bpi) + *wpr * (*fpr - *bpr));
      }
   } else {
      (*in).re = scale * (*fpr + *bpr);
      (*in).im = scale * (*fpr - *bpr);
      while(n-- > 1){
         in++;
         wpr += wst; wpi += wst;
         fpr += fst; fpi += fst;
         bpr += bst; bpi += bst;
         (*in).re = scale * (*fpr + *bpr + *wpi * (*bpr - *fpr) - *wpr * (*fpi + *bpi));
         (*in).im = scale * (*fpi - *bpi - *wpi * (*fpi + *bpi) + *wpr * (*fpr - *bpr));
      }
   }
   #if defined(VSIP_ASSUME_COMPLEX_IS_INTERLEAVED)
      fftw_one(obj->p,obj->in,(fftw_complex*)xptr);
   #else
   { 
      fftw_complex *out = obj->out;
      fftw_one(obj->p,obj->in,obj->out);
      n = fft->N;
      while(n-- > 0){
         *xptr = (*out).re; 
         xptr += xst; 
         *xptr = (*out).im;
         xptr += xst; 
         out++;
      }
   }
   #endif
   return;
}
