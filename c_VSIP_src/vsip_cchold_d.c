/* Created RJudd August 30, 2002 */
/* SPAWARSYSCEN  */
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
/* $Id: vsip_cchold_d.c,v 2.3 2004/09/22 02:25:38 judd Exp $ */

#include<vsip.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_ccholdattributes_d.h>

static
int
VI_ccholesky_low_ai_d(
          const vsip_cmview_d *A)
{
   int retval = 0;
   vsip_index j,k;
   vsip_length n = A->col_length;
   double scale = 1;
   vsip_scalar_d re_scale = 1, im_scale = 1;
   vsip_scalar_d *scale_ptr;
   vsip_scalar_d *aptr_re;
   vsip_scalar_d *bptr_re;
   vsip_stride col_str = A->col_stride * 2;
   vsip_offset off_a_col = (A->offset + A->col_stride) * 2;
   vsip_stride A_diag_str = (A->col_stride + A->row_stride) * 2;
   vsip_offset off_A_diag = 2 * A->offset;
   vsip_length m0 = n;
   vsip_length m;
   vsip_offset off_b0 = off_A_diag;
   vsip_offset off_b;

   vsip_offset off_a0 = off_A_diag;
   vsip_offset off_a;

   vsip_offset off_as0 = off_A_diag;
   vsip_offset off_as;

   for(k=0; k<n; k++){
      vsip_scalar_d *a_kk_r   = A->block->R->array + off_A_diag;
      off_A_diag += A_diag_str;
      /* for the diagonal a_kk must have zero imaginary */
      if(*a_kk_r <= 0){
         retval++;
         return retval;
      } else { 
         scale = (double) *a_kk_r;
         scale = sqrt(scale);
      }
      re_scale = (vsip_scalar_d) scale;
      *a_kk_r = re_scale;
      *(a_kk_r + 1) = 0.0;

      aptr_re = A->block->R->array + off_a_col;
      off_a_col += A_diag_str;
      m0--; m = m0;
      while(m-- > 0){
         *aptr_re /= re_scale; *(aptr_re + 1) /= re_scale;
         aptr_re += col_str;
      }
      off_b = off_b0;
      off_b0 += A_diag_str;
      off_as = off_a0;
      off_as0 += A_diag_str;
      off_a = off_a0;
      off_a0 += A_diag_str;
      scale_ptr = A->block->R->array + off_as;
      for(j=k+1; j<n; j++){
         off_b += col_str;
         bptr_re = A->block->R->array  + off_b;
         off_as += col_str;
         scale_ptr += col_str;
         re_scale = - *scale_ptr;
         im_scale =   *(scale_ptr + 1);
         off_a += A_diag_str;
         aptr_re = A->block->R->array  + off_a;
         m = n - j;
         while(m-- >0){
             vsip_scalar_d br = *bptr_re, bi = *(bptr_re + 1);
            *aptr_re       += br * re_scale - bi * im_scale;
            *(aptr_re + 1) += br * im_scale + bi * re_scale;
             aptr_re += col_str; bptr_re += col_str;
         }
      }
   }
   return retval;
}
static
int
VI_ccholesky_low_d(
          const vsip_cmview_d *A)
{
   int retval = 0;
   vsip_index j,k;
   vsip_length n = A->col_length;
   double scale = 1;
   vsip_scalar_d re_scale = 1, im_scale = 1;
   vsip_scalar_d *aptr_re, *aptr_im;
   vsip_scalar_d *bptr_re, *bptr_im;
   vsip_stride col_str = A->col_stride * A->block->cstride;
   vsip_offset off_a_col = (A->offset + A->col_stride) * A->block->cstride;
   vsip_stride A_diag_str = (A->col_stride + A->row_stride) * A->block->cstride;
   vsip_offset off_A_diag = A->block->cstride * A->offset;
   vsip_length m0 = n;
   vsip_length m;
   vsip_offset off_b0 = off_A_diag;
   vsip_offset off_b;

   vsip_offset off_a0 = off_A_diag;
   vsip_offset off_a;

   vsip_offset off_as0 = off_A_diag;
   vsip_offset off_as;

   for(k=0; k<n; k++){
      vsip_scalar_d *a_kk_r   = A->block->R->array + off_A_diag;
      vsip_scalar_d *a_kk_i = A->block->I->array + off_A_diag;
      off_A_diag += A_diag_str;
      /* for the diagonal a_kk must have zero imainary */
      *a_kk_i = 0.0;
      if(*a_kk_r <= 0){
         retval++;
         return retval;
      } else { 
         scale = (double) *a_kk_r;
         scale = sqrt(scale);
      }
      re_scale = (vsip_scalar_d) scale;
      *a_kk_r = re_scale;

      aptr_re = A->block->R->array + off_a_col;
      aptr_im = A->block->I->array + off_a_col;
      off_a_col += A_diag_str;
      m0--; m = m0;
      while(m-- > 0){
         *aptr_re /= re_scale; *aptr_im /= re_scale;
         aptr_re += col_str; aptr_im += col_str;
      }
      off_b = off_b0;
      off_b0 += A_diag_str;
      off_as = off_a0;
      off_as0 += A_diag_str;
      off_a = off_a0;
      off_a0 += A_diag_str;
      for(j=k+1; j<n; j++){
         off_b += col_str;
         bptr_re = A->block->R->array  + off_b;
         bptr_im = A->block->I->array  + off_b;
         off_as += col_str;
         re_scale = - *(A->block->R->array + off_as);
         im_scale =   *(A->block->I->array + off_as);
         off_a += A_diag_str;
         aptr_re = A->block->R->array  + off_a;
         aptr_im = A->block->I->array  + off_a;
         m = n - j;
         while(m-- >0){
            *aptr_re += *bptr_re * re_scale - *bptr_im * im_scale;
            *aptr_im += *bptr_re * im_scale + *bptr_im * re_scale;
             aptr_re += col_str; bptr_re += col_str;
             aptr_im += col_str; bptr_im += col_str;
         }
      }
   }
   return retval;
}

static
int
VI_ccholesky_upp_ai_d(
        const vsip_cmview_d *A)
{
   int retval = 0;
   vsip_length n = A->row_length;
   vsip_length m0 = n - 1;
   vsip_length m =  m0;
   vsip_length m_in =0;
   vsip_index j,k;
   double scale;

   vsip_offset a_kk_off = 2 * A->offset;
   vsip_scalar_d *a_kk_r = A->block->R->array + a_kk_off;

   vsip_stride A_diag_str = 2 * (A->row_stride + A->col_stride); 

   vsip_scalar_d re_scale, im_scale;
   vsip_scalar_d *a_re_ptr, *a_re_ptr0;
   vsip_scalar_d *b_re_ptr, *b_re_ptr0;
   vsip_stride a_str = 2 * A->row_stride;
   vsip_stride b_str = a_str;
   for(k=0; k<n; k++){
      /* for the diagonal a_kk must have zero imaginary */
      if(*a_kk_r <= 0){
         retval++;
         return retval;
      } else {
         scale = (double) *a_kk_r;
         scale = sqrt(scale);
      }
      *a_kk_r = (vsip_scalar_d) scale;
      *(a_kk_r + 1) = 0.0;
      a_re_ptr = a_kk_r + a_str;
      while(m-- > 0){
         *a_re_ptr /= (vsip_scalar_d)scale; *(a_re_ptr + 1) /= (vsip_scalar_d)scale;
         a_re_ptr += a_str;
      }
      m0--;
      m=m0;
      a_re_ptr0 = a_kk_r + A_diag_str; 
      b_re_ptr0 = a_kk_r + b_str;
      for(j=k+1; j<n; j++){
         m_in = n-j;
         a_re_ptr = a_re_ptr0;
         b_re_ptr = b_re_ptr0;
         re_scale = - *(b_re_ptr);
         im_scale =   *(b_re_ptr + 1);
         while(m_in-- >0){
            vsip_scalar_d br = *b_re_ptr, bi = *(b_re_ptr + 1);
            *a_re_ptr += br * re_scale - bi * im_scale;
            *(a_re_ptr + 1) += br * im_scale + bi * re_scale;
             a_re_ptr += a_str; b_re_ptr += b_str;
         }
         a_re_ptr0 += A_diag_str;
         b_re_ptr0 += b_str;
      }
      a_kk_r += A_diag_str;
   }
   return retval;
}

static
int
VI_ccholesky_upp_d(
        const vsip_cmview_d *A)
{
   int retval = 0;
   vsip_length n = A->row_length;
   vsip_length m0 = n - 1;
   vsip_length m =  m0;
   vsip_length m_in =0;
   vsip_index j,k;
   double scale;

   vsip_offset a_kk_off = A->block->cstride * A->offset;
   vsip_scalar_d *a_kk_r = A->block->R->array + a_kk_off;
   vsip_scalar_d *a_kk_i = A->block->I->array + a_kk_off;

   vsip_stride A_diag_str = A->block->cstride * (A->row_stride + A->col_stride); 

   vsip_scalar_d re_scale, im_scale;
   vsip_scalar_d *a_re_ptr, *a_re_ptr0;
   vsip_scalar_d *a_im_ptr, *a_im_ptr0;
   vsip_scalar_d *b_re_ptr, *b_re_ptr0;
   vsip_scalar_d *b_im_ptr, *b_im_ptr0;
   vsip_stride a_str = A->block->cstride * A->row_stride;
   vsip_stride b_str = a_str;
   for(k=0; k<n; k++){
      /* for the diagonal a_kk must have zero imaginary */
      if(*a_kk_r <= 0){
         retval++;
         return retval;
      } else {
         scale = (double) *a_kk_r;
         scale = sqrt(scale);
      }
      *a_kk_r = (vsip_scalar_d) scale;
      *a_kk_i = 0.0;
      a_re_ptr = a_kk_r + a_str;
      a_im_ptr = a_kk_i + a_str;
      while(m-- > 0){
         *a_re_ptr /= (vsip_scalar_d)scale; *a_im_ptr /= (vsip_scalar_d)scale;
         a_re_ptr += a_str; a_im_ptr += a_str;
      }
      m0--;
      m=m0;
      a_re_ptr0 = a_kk_r + A_diag_str; a_im_ptr0 = a_kk_i + A_diag_str;
      b_re_ptr0 = a_kk_r + b_str; b_im_ptr0 = a_kk_i + b_str;
      for(j=k+1; j<n; j++){
         m_in = n-j;
         a_re_ptr = a_re_ptr0;
         a_im_ptr = a_im_ptr0;
         b_re_ptr = b_re_ptr0;
         b_im_ptr = b_im_ptr0;
         re_scale = - *(b_re_ptr);
         im_scale =   *(b_im_ptr);
         while(m_in-- >0){
            *a_re_ptr += *b_re_ptr * re_scale - *b_im_ptr * im_scale;
            *a_im_ptr += *b_re_ptr * im_scale + *b_im_ptr * re_scale;
             a_re_ptr += a_str; b_re_ptr += b_str;
             a_im_ptr += a_str; b_im_ptr += b_str;
         }
         a_re_ptr0 += A_diag_str;
         a_im_ptr0 += A_diag_str;
         b_re_ptr0 += b_str;
         b_im_ptr0 += b_str;
      }
      a_kk_r += A_diag_str; a_kk_i += A_diag_str;
   }
   return retval;
}

int
vsip_cchold_d(
          vsip_cchol_d* chol,
          const vsip_cmview_d *A)
{
   int retval     = 0;
   chol->matrix   = A;
   if(chol->uplo == VSIP_TR_LOW){
      if(A->block->cstride == 2)
         retval = VI_ccholesky_low_ai_d(A);
      else
         retval = VI_ccholesky_low_d(A);
   } else { /* must be vsip_tr_upp */
      if(A->block->cstride == 2)
         retval = VI_ccholesky_upp_ai_d(A);
      else
         retval = VI_ccholesky_upp_d(A);
   } 
   return retval;
}
