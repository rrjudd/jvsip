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
/* $Id: vsip_ccholsol_f.c,v 2.2 2004/07/30 16:05:12 judd Exp $ */

#include"vsip.h"
#include"vsip_blockattributes_f.h"
#include"vsip_cblockattributes_f.h"
#include"vsip_cmviewattributes_f.h"
#include"vsip_cvviewattributes_f.h"
#include"vsip_ccholdattributes_f.h"

int
vsip_ccholsol_f(
                const vsip_cchol_f *chol,
                const vsip_cmview_f *XB)
{
   int retval = 0;
   const vsip_cmview_f *A = chol->matrix;
   const vsip_cmview_f *B = XB;
   if(chol->uplo == VSIP_TR_UPP){
      {
         vsip_scalar_f dot_r,dot_i;
         vsip_length n_A = A->row_length;
         vsip_length n_B = B->row_length;
         vsip_index i,j;
         
         vsip_stride A_diag_str =(A->row_stride + A->col_stride) * A->block->cstride;
         vsip_offset off_A = A->offset * A->block->cstride;
         vsip_scalar_f d0 = *(A->block->R->array + off_A);
         vsip_length n = n_B;
         vsip_stride ar_str = A->col_stride * A->block->cstride; /* doing transpose here */
         vsip_stride ac_str = A->row_stride * A->block->cstride; /* doing transpose here */
         vsip_stride bc_str = B->col_stride * B->block->cstride;
         vsip_stride br_str = B->row_stride * B->block->cstride;
         vsip_scalar_f *a_re,*a_im;
         vsip_offset off_br0 = B->offset * B->block->cstride;
         vsip_offset off_br = off_br0;
         vsip_scalar_f *b_re = B->block->R->array + off_br;
         vsip_scalar_f *b_im = B->block->I->array + off_br;
         vsip_offset off_b0 = off_br0;
         vsip_offset off_b;
         vsip_scalar_f *b;
         vsip_offset off_a = A->offset * A->block->cstride;
         if((A->block->cstride == 2) && (B->block->cstride == 2)){
            while(n-- >0){
               *b_re /= d0;
               *(b_re + 1) /= d0;
               b_re += br_str;
            }
            for(i=1; i<n_A; i++){
               off_A += A_diag_str;
               d0 = *(A->block->R->array + off_A);
               off_b0 += bc_str;
               off_b = off_b0;
               off_a += ac_str;
               off_br = off_br0;
               
               for(j=0; j<n_B; j++){
                  n = i;
                  a_re = A->block->R->array + off_a;
                  b_re = B->block->R->array + off_br;
                  dot_r = 0; dot_i = 0;
                  while(n-- > 0){
                     vsip_scalar_f ar = *a_re, ai = *(a_re + 1);
                     vsip_scalar_f br = *b_re, bi = *(b_re + 1);
                     dot_r += ar * br + ai * bi;
                     dot_i += ar * bi - ai * br;
                     a_re += ar_str;
                     b_re += bc_str;
                  }
                  b = B->block->R->array + off_b;
                  *b = (*b - dot_r)/d0;
                  b++;
                  *b = (*b - dot_i)/d0;
                  off_b += br_str;
                  off_br += br_str;
               }
            } 
         } else {
            while(n-- >0){
               *b_re /= d0; *b_im /= d0;
               b_re += br_str; b_im += br_str;
            }
            for(i=1; i<n_A; i++){
               off_A += A_diag_str;
               d0 = *(A->block->R->array + off_A);
               off_b0 += bc_str;
               off_b = off_b0;
               off_a += ac_str;
               off_br = off_br0;
               
               for(j=0; j<n_B; j++){
                  n = i;
                  a_re = A->block->R->array + off_a;
                  a_im = A->block->I->array + off_a;
                  b_re = B->block->R->array + off_br;
                  b_im = B->block->I->array + off_br;
                  dot_r = 0; dot_i = 0;
                  while(n-- > 0){
                     dot_r += (*a_re * *b_re + *a_im * *b_im);
                     dot_i += (*a_re * *b_im - *a_im * *b_re);
                     a_re += ar_str; a_im += ar_str;
                     b_re += bc_str; b_im += bc_str;
                  }
                  b = B->block->R->array + off_b;
                  *b = (*b - dot_r)/d0;
                  b = B->block->I->array + off_b;
                  *b = (*b - dot_i)/d0;
                  off_b += br_str;
                  off_br += br_str;
               }
            }
         }
      }
      {
         vsip_scalar_f dot_r,dot_i;
         vsip_scalar_f *b;
         vsip_stride ar_str = A->row_stride * A->block->cstride;
         vsip_length n_A = A->row_length;
         vsip_length n_A_1 = n_A - 1;
         vsip_stride A_diag_str = (A->col_stride + A->row_stride);
         vsip_length n_B = B->row_length;
         vsip_offset off_A = A->block->cstride * ( A->offset + (n_A_1) * A_diag_str);
         vsip_offset off_ar = (A->offset + n_A * A_diag_str - A->col_stride) * A->block->cstride; 
         vsip_scalar_f d0 = *(A->block->R->array + off_A);
         vsip_index i,j;
         vsip_offset off_br0 = (n_A_1 * B->col_stride + B->offset) * B->block->cstride;
         vsip_offset off_br = off_br0;
         vsip_offset off_bc0 = (B->offset + B->col_stride * n_A) * B->block->cstride;
         vsip_offset off_bc;
         vsip_stride br_str = B->row_stride * B->block->cstride;
         vsip_stride bc_str = B->col_stride * B->block->cstride;
         vsip_scalar_f *b_re = B->block->R->array + off_br;
         vsip_scalar_f *b_im = B->block->I->array + off_br;
         vsip_scalar_f *a_re,*a_im;
         vsip_length n = n_B;
         if((A->block->cstride == 2) && (B->block->cstride == 2)){
            while(n-- >0){
               *b_re /= d0;
               *(b_re + 1) /= d0;
               b_re += br_str;
            }
            A_diag_str *= A->block->cstride;
            for(i=1; i<n_A; i++){
               off_A -= A_diag_str;
               d0 = *(A->block->R->array + off_A);
               off_br0 -= bc_str;
               off_br = off_br0;
               off_bc0 -= bc_str;
               off_bc = off_bc0;
               off_ar -= A_diag_str;
               for(j=0; j<n_B; j++){
                  n = i;
                  a_re = A->block->R->array + off_ar;
                  b_re = B->block->R->array + off_bc;
                  dot_r = 0; dot_i = 0;
                  while(n-- > 0){
                     vsip_scalar_f ar = *a_re, ai = *(a_re + 1);
                     vsip_scalar_f br = *b_re, bi = *(b_re + 1);
                     dot_r += ar * br - ai * bi;
                     dot_i += ar * bi + ai * br;
                     a_re += ar_str;
                     b_re += bc_str;
                  }
                  b = B->block->R->array + off_br;
                  *b = (*b - dot_r)/d0;
                  b++;
                  *b = (*b - dot_i)/d0;
                  off_br += br_str;
                  off_bc += br_str;
               }
            } 
         } else {
            while(n-- >0){
               *b_re /= d0; *b_im /= d0;
               b_re += br_str; b_im += br_str;
            }
            A_diag_str *= A->block->cstride;
            for(i=1; i<n_A; i++){
               off_A -= A_diag_str;
               d0 = *(A->block->R->array + off_A);
               off_br0 -= bc_str;
               off_br = off_br0;
               off_bc0 -= bc_str;
               off_bc = off_bc0;
               off_ar -= A_diag_str;
               for(j=0; j<n_B; j++){
                  n = i;
                  a_re = A->block->R->array + off_ar;
                  a_im = A->block->I->array + off_ar;
                  b_re = B->block->R->array + off_bc;
                  b_im = B->block->I->array + off_bc;
                  dot_r = 0; dot_i = 0;
                  while(n-- > 0){
                     dot_r += (*a_re * *b_re - *a_im * *b_im);
                     dot_i += (*a_re * *b_im + *a_im * *b_re);
                     a_re += ar_str; a_im += ar_str;
                     b_re += bc_str; b_im += bc_str;
                  }
                  b = B->block->R->array + off_br;
                  *b = (*b - dot_r)/d0;
                  b = B->block->I->array + off_br;
                  *b = (*b - dot_i)/d0;
                  off_br += br_str;
                  off_bc += br_str;
               }
            } 
         }
      }
   } else { /* must be VSIP_TR_LOW */
      {
         vsip_scalar_f dot_r,dot_i;
         vsip_scalar_f *b;
         vsip_length n_A = A->row_length;
         vsip_length n_B = B->row_length;
         vsip_index i,j;
         vsip_stride A_diag_str = (A->row_stride + A->col_stride) * A->block->cstride;
         vsip_offset off_A = A->offset * A->block->cstride;
         vsip_scalar_f d0 = *(A->block->R->array + off_A);
         vsip_length n = B->row_length;
         
         vsip_offset off_br0 = B->offset * B->block->cstride;
         vsip_offset off_br = off_br0;
         
         vsip_offset off_bc0 = B->offset * B->block->cstride;
         vsip_offset off_bc;
         
         vsip_scalar_f *b_re = B->block->R->array + off_br;
         vsip_scalar_f *b_im = B->block->I->array + off_br;
         vsip_scalar_f *a_re,*a_im;
         vsip_stride a_str = A->row_stride * A->block->cstride;
         vsip_stride bc_str = B->col_stride * B->block->cstride;
         vsip_stride br_str = B->row_stride * B->block->cstride;
         vsip_offset off_a = A->offset * A->block->cstride; 
         vsip_stride off_a_str = A->col_stride * A->block->cstride;
         if((A->block->cstride == 2) && (B->block->cstride == 2)){
            while(n-- >0){
               *b_re /= d0;
               *(b_re + 1) /= d0;
               b_re += br_str;
            }
            for(i=1; i<n_A; i++){
               off_A += A_diag_str;
               off_br0 += bc_str;
               off_br = off_br0;
               off_bc = off_bc0;
               d0 = *(A->block->R->array + off_A);
               off_a += off_a_str;
               for(j=0; j<n_B; j++){
                  n = i;
                  a_re = A->block->R->array + off_a;
                  a_im = A->block->I->array + off_a;
                  b_re = B->block->R->array + off_bc;
                  b_im = B->block->I->array + off_bc;
                  dot_r = 0; dot_i = 0;
                  while(n-- > 0){
                     vsip_scalar_f ar = *a_re, ai = *(a_re + 1);
                     vsip_scalar_f br = *b_re, bi = *(b_re + 1);
                     dot_r += ar * br - ai * bi;
                     dot_i += ar * bi + ai * br;
                     a_re += a_str; a_im += a_str;
                     b_re += bc_str; b_im += bc_str;
                  }
                  b = B->block->R->array + off_br;
                  *b = (*b - dot_r)/d0;
                  b++;
                  *b = (*b - dot_i)/d0;
                  off_br +=  br_str;
                  off_bc +=  br_str;
               }
            } 
         } else {
            while(n-- >0){
               *b_re /= d0; *b_im /= d0;
               b_re += br_str; b_im += br_str;
            }
            for(i=1; i<n_A; i++){
               off_A += A_diag_str;
               off_br0 += bc_str;
               off_br = off_br0;
               off_bc = off_bc0;
               d0 = *(A->block->R->array + off_A);
               off_a += off_a_str;
               for(j=0; j<n_B; j++){
                  n = i;
                  a_re = A->block->R->array + off_a;
                  a_im = A->block->I->array + off_a;
                  b_re = B->block->R->array + off_bc;
                  b_im = B->block->I->array + off_bc;
                  dot_r = 0; dot_i = 0;
                  while(n-- > 0){
                     dot_r += (*a_re * *b_re - *a_im * *b_im);
                     dot_i += (*a_re * *b_im + *a_im * *b_re);
                     a_re += a_str; a_im += a_str;
                     b_re += bc_str; b_im += bc_str;
                  }
                  b = B->block->R->array + off_br;
                  *b = (*b - dot_r)/d0;
                  b = B->block->I->array + off_br;
                  *b = (*b - dot_i)/d0;
                  off_br +=  br_str;
                  off_bc +=  br_str;
               }
            }
         }
      }
      {
         vsip_scalar_f dot_r,dot_i;
         vsip_length n_A = A->row_length;
         vsip_length n_A_1 = n_A - 1;
         vsip_length n_B = B->row_length;
         vsip_index i,j;
         vsip_stride A_diag_str = A->row_stride + A->col_stride;
         vsip_offset off_Bc0 = (B->offset + B->col_stride * n_A ) * B->block->cstride;
         vsip_offset off_Bc;
         vsip_offset off_A = A->block->cstride * (A->offset + (n_A-1)*(A_diag_str));
         vsip_offset off_Ar= (A->offset +n_A * A_diag_str - A->row_stride) * A->block->cstride;
         vsip_stride off_A_str = A->block->cstride * (A->row_stride + A->col_stride);
         vsip_stride a_str = A->col_stride * A->block->cstride;
         vsip_scalar_f d0 = *(A->block->R->array + off_A);
         vsip_length n = n_B;
         vsip_offset off_Br = (B->offset + n_A_1 * B->col_stride) * B->block->cstride; 
         vsip_offset off_Br0 = off_Br;
         vsip_stride off_Br_str = B->block->cstride * B->col_stride; /* B row stride */
         vsip_stride bc_str = off_Br_str;
         vsip_stride br_str = B->row_stride * B->block->cstride;
         vsip_scalar_f *a_re,*a_im, *b;
         vsip_scalar_f *b_re = B->block->R->array + off_Br;
         vsip_scalar_f *b_im = B->block->I->array + off_Br;
         if((A->block->cstride == 2) && (B->block->cstride == 2)){
            while(n-- >0){
               *b_re /= d0;
               *(b_re + 1) /= d0;
               b_re += br_str;
            }
            A_diag_str *= A->block->cstride;
            for(i=1; i<n_A; i++){
               off_A -= off_A_str;
               d0 = *(A->block->R->array + off_A);
               off_Br0 -= off_Br_str;
               off_Br = off_Br0;
               off_Ar -= A_diag_str;
               off_Bc0 -= bc_str;
               off_Bc = off_Bc0;
               for(j=0; j<n_B; j++){
                  n = i;
                  a_re = A->block->R->array + off_Ar;
                  b_re = B->block->R->array + off_Bc;
                  dot_r = 0; dot_i = 0;
                  while(n-- > 0){
                     vsip_scalar_f ar = *a_re, ai=*(a_re + 1);
                     vsip_scalar_f br = *b_re, bi=*(b_re + 1);
                     dot_r += (ar * br + ai * bi);
                     dot_i += (ar * bi - ai * br);
                     a_re += a_str;
                     b_re += bc_str;
                  }
                  b = B->block->R->array + off_Br;
                  *b = (*b - dot_r)/d0;
                  b++;
                  *b = (*b - dot_i)/d0;
                  off_Br += br_str;
                  off_Bc += br_str;
               }
            }
         } else {
            while(n-- >0){
               *b_re /= d0; *b_im /= d0;
               b_re += br_str; b_im += br_str;
            }
            A_diag_str *= A->block->cstride;
            for(i=1; i<n_A; i++){
               off_A -= off_A_str;
               d0 = *(A->block->R->array + off_A);
               off_Br0 -= off_Br_str;
               off_Br = off_Br0;
               off_Ar -= A_diag_str;
               off_Bc0 -= bc_str;
               off_Bc = off_Bc0;
               for(j=0; j<n_B; j++){
                  n = i;
                  a_re = A->block->R->array + off_Ar;
                  a_im = A->block->I->array + off_Ar;
                  b_re = B->block->R->array + off_Bc;
                  b_im = B->block->I->array + off_Bc;
                  dot_r = 0; dot_i = 0;
                  while(n-- > 0){
                     dot_r += (*a_re * *b_re + *a_im * *b_im);
                     dot_i += (*a_re * *b_im - *a_im * *b_re);
                     a_re += a_str; a_im += a_str;
                     b_re += bc_str; b_im += bc_str;
                  }
                  b = B->block->R->array + off_Br;
                  *b = (*b - dot_r)/d0;
                  b = B->block->I->array + off_Br;
                  *b = (*b - dot_i)/d0;
                  off_Br += br_str;
                  off_Bc += br_str;
               }
            }
         }
      } 
   }
   return retval;
}  
