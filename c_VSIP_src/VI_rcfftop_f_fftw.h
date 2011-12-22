/* Created by RJudd June 13, 2002 */
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
/* $Id: VI_rcfftop_f_fftw.h,v 2.0 2003/02/22 15:18:33 judd Exp $ */
#ifndef _VI_RCFFTOP_F_FFTW_H
#define _VI_RCFFTOP_F_FFTW_H

#include"VI_fftw_obj.h"

/* Note x and z must be unit stride      */
/* This is required by the specification */

void vsip_rcfftop_f(
           const vsip_fft_f    *Offt, 
           const vsip_vview_f  *x,
           const vsip_cvview_f *z)
{
   vsip_fft_f Nfft = *Offt;
   vsip_fft_f *fft = &Nfft;
   vsipl_fftw_obj *obj = (vsipl_fftw_obj*)fft->ext_fft_obj;
   vsip_length n = fft->N;
   
   vsip_scalar_f scale = .5 * fft->scale;
   
   /* Get phase shift pointers */
   vsip_cvview_f *w = fft->temp;
   vsip_stride w_str = w->stride * w->block->R->rstride;
   vsip_scalar_f *wr = w->block->R->array + w->offset * w->block->R->rstride;
   vsip_scalar_f *wi = w->block->I->array + w->offset * w->block->I->rstride;
   
   /* view stride should always be 1 so memory stride is just block stride */
   vsip_stride z_str = z->block->R->rstride * z->stride;
   vsip_stride x_str = x->block->rstride * x->stride;
   vsip_offset offset = (vsip_offset)(z->offset * z->block->R->rstride);
   #if defined(VSIP_ASSUME_COMPLEX_IS_INTERLEAVED)
      /* do top and bottom together stop in the middle */
      vsip_length n_end = (vsip_length)(fft->N/2);
      /* offsets into memory of z data */
      vsip_offset offset_end = (vsip_offset)((z->offset + n) * z->block->R->rstride);

      /* begining of output; go through forward */
      vsip_scalar_f *fr = z->block->R->array + offset;
      vsip_scalar_f *fi = z->block->I->array + offset;
      
      /* end of output; go through backward */
      vsip_scalar_f *br = z->block->R->array + offset_end;
      vsip_scalar_f *bi = z->block->I->array + offset_end;
      
      /* Need some temporary storage */
      vsip_scalar_f temp1,temp2,temp3;
      
      /* make a pointer to use in fftw. Here is where interleaved is assumed */
      fftw_complex *in  = (fftw_complex*)(x->block->array + x->offset * x_str);
      fftw_complex *out = (fftw_complex*)fr;
      
      /* do the fft; note stride is one so use fftw_one */
      fftw_one(obj->p,in,out);
      
      /* sort things out */
      /* do the final point */
      *br =  fft->scale * (*fr - *fi);
      *bi =  0;

      /* do the zero point */
      *fr =  fft->scale * (*fr + *fi);
      *fi =  0;

      n = fft->N;
      /* do all others */
      while(n-- > n_end + 1){
         wr += w_str; wi += w_str;
         fr += z_str; fi += z_str;
         br -= z_str; bi -= z_str;
         temp1 = scale * (*fr + *br + *wr * (*fi + *bi) - *wi * (*fr - *br));
         temp2 = scale * (*br + *fr - *wr * (*bi + *fi) - *wi * (*br - *fr));
         temp3 = scale * (*fi - *bi - *wr * (*fr - *br) - *wi * (*fi + *bi));
         *bi = scale * (*bi - *fi + *wr * (*br - *fr) - *wi * (*bi + *fi));
         *br = temp2;
         *fi = temp3;
         *fr = temp1;
      }
      if(!(fft->N % 2)){ /* do the odd middle point */
         fr += z_str; fi += z_str;
         *fr =  fft->scale *  *fr;
         *fi = -fft->scale * *fi;
      }
   #else
      /* get the pointer to the real and imaginary part of output */
      vsip_scalar_f *zptr_r = z->block->R->array + offset;
      vsip_scalar_f *zptr_i = z->block->I->array + offset;
      
      /* get the pointer to the input data */ 
      vsip_scalar_f *xptr = x->block->array + x_str * x->offset; 
      
      /* pointers for use with fftw */
      fftw_complex *ptr = obj->in,*f,*b;

      /* copy the data from the  input vector to fftw data buffer */
      while(n-- > 0){
         (*ptr).re = (fftw_real)*xptr;
         xptr += x_str;
         (*ptr).im = (fftw_real)*xptr;
         ptr++; xptr += x_str;
      }
      
      /* do the fft */
      fftw_one(obj->p,obj->in,obj->out);
      
      /* do sorting work here */
      /* reset our counter */
      n = fft->N;
      
      /* pointer to begining of fftw output */
      f = &(obj->out[0]);
      
      /* pointer to end of fftw output */
      b = &(obj->out[fft->N-1]);
  
      /* calculate the zero point */
      *zptr_r =  fft->scale * ((vsip_scalar_f)(*f).re + (vsip_scalar_f)(*f).im);
      *zptr_i =  0;
      zptr_r += z_str; zptr_i += z_str;
      wr += w_str; wi += w_str;
      f++;

      /* do all others EXCEPT the final point */
      while(n-- > 1){
         *zptr_r = scale * ((vsip_scalar_f)(*f).re + (vsip_scalar_f)(*b).re + 
         *wr * ((vsip_scalar_f)(*f).im + (vsip_scalar_f)(*b).im) - 
         *wi * ((vsip_scalar_f)(*f).re - (vsip_scalar_f)(*b).re));
         *zptr_i = scale * ((vsip_scalar_f)(*f).im - (vsip_scalar_f)(*b).im - 
         *wr * ((vsip_scalar_f)(*f).re - (vsip_scalar_f)(*b).re) - 
         *wi * ((vsip_scalar_f)(*f).im + (vsip_scalar_f)(*b).im));
         zptr_r += z_str; zptr_i += z_str;
         wr += w_str; wi += w_str;
         b--; f++;
      }

      /* do the final point */
      *zptr_r =  fft->scale * ((vsip_scalar_f)(*b).re - (vsip_scalar_f)(*b).im);
      *zptr_i =  0;
   #endif
   return;
}

#endif /* _VI_RCFFTOP_F_FFTW_H */
