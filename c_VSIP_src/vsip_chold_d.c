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
/* $Id: vsip_chold_d.c,v 2.3 2004/09/22 02:25:39 judd Exp $ */

#include"vsip.h"
#include"vsip_mviewattributes_d.h"
#include"vsip_vviewattributes_d.h"
#include"vsip_choldattributes_d.h"

static
int
VI_cholesky_low_d(
          const vsip_mview_d *A)
{
   int retval = 0;
   vsip_index j,k;
   vsip_length n = A->col_length;
   double scale = 1;
   vsip_scalar_d re_scale = 1;
   vsip_scalar_d *aptr_re;
   vsip_scalar_d *bptr_re;
   vsip_stride col_str = A->col_stride * A->block->rstride;
   vsip_offset off_a_col = (A->offset + A->col_stride) * A->block->rstride;
   vsip_stride A_diag_str = (A->col_stride + A->row_stride) * A->block->rstride;
   vsip_offset off_A_diag = A->block->rstride * A->offset;
   vsip_length m0 = n;
   vsip_length m;
   vsip_offset off_b0 = off_A_diag;
   vsip_offset off_b;

   vsip_offset off_a0 = off_A_diag;
   vsip_offset off_a;

   vsip_offset off_as;

   for(k=0; k<n; k++){
      vsip_scalar_d *a_kk_r   = A->block->array + off_A_diag;
      off_A_diag += A_diag_str;
      if(*a_kk_r <= 0){
         retval++;
         return retval;
      } else { 
         scale = (double) *a_kk_r;
         scale = sqrt(scale);
      }
      re_scale = (vsip_scalar_d) scale;
      *a_kk_r = re_scale;

      aptr_re = A->block->array + off_a_col;
      off_a_col += A_diag_str;
      m0--; m = m0;
      while(m-- > 0){
         *aptr_re /= re_scale;
         aptr_re += col_str;
      }
      off_b = off_b0;
      off_b0 += A_diag_str;
      off_as = off_a0;
      off_a = off_a0;
      off_a0 += A_diag_str;
      for(j=k+1; j<n; j++){
         off_b += col_str;
         bptr_re = A->block->array  + off_b;
         off_as += col_str;
         re_scale = - *(A->block->array + off_as);
         off_a += A_diag_str;
         aptr_re = A->block->array  + off_a;
         m = n - j;
         while(m-- >0){
            *aptr_re += *bptr_re * re_scale;
             aptr_re += col_str; bptr_re += col_str;
         }
      }
   }
   return retval;
}


static
int
VI_cholesky_upp_d(
        const vsip_mview_d *A)
{
   int retval = 0;
   vsip_length n = A->row_length;
   vsip_length m0 = n - 1;
   vsip_length m =  m0;
   vsip_length m_in =0;
   vsip_index j,k;
   double scale;

   vsip_offset a_kk_off = A->block->rstride * A->offset;
   vsip_scalar_d *a_kk_r = A->block->array + a_kk_off;

   vsip_stride A_diag_str = A->block->rstride * (A->row_stride + A->col_stride); 

   vsip_scalar_d re_scale;
   vsip_scalar_d *a_re_ptr, *a_re_ptr0;
   vsip_scalar_d *b_re_ptr, *b_re_ptr0;
   vsip_stride a_str = A->block->rstride * A->row_stride;
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
      a_re_ptr = a_kk_r + a_str;
      while(m-- > 0){
         *a_re_ptr /= (vsip_scalar_d)scale;
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
         while(m_in-- >0){
            *a_re_ptr += *b_re_ptr * re_scale;
             a_re_ptr += a_str; b_re_ptr += b_str;
         }
         a_re_ptr0 += A_diag_str;
         b_re_ptr0 += b_str;
      }
      a_kk_r += A_diag_str;
   }
   return retval;
}

int
vsip_chold_d(
          vsip_chol_d* chol,
          const vsip_mview_d *A)
{
   int retval     = 0;
   chol->matrix   = A;
   if(chol->uplo == VSIP_TR_LOW){
      retval = VI_cholesky_low_d(A);
   } else { /* must be vsip_tr_upp */
      retval = VI_cholesky_upp_d(A);
   } 
   return retval;
}
