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
/* $Id: vsip_cholsol_d.c,v 2.2 2004/09/22 02:25:39 judd Exp $ */

#include<vsip.h>
#include<vsip_blockattributes_d.h>
#include<vsip_blockattributes_d.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_choldattributes_d.h>

int
vsip_cholsol_d(
          const vsip_chol_d *chol,
          const vsip_mview_d *XB)
{
   int retval = 0;
   const vsip_mview_d *A = chol->matrix;
   const vsip_mview_d *B = XB;
   if(chol->uplo == VSIP_TR_UPP){     
      {
         vsip_scalar_d dot;
         vsip_length n_A = A->row_length;
         vsip_length n_B = B->row_length;
         vsip_index i,j;
         
         vsip_stride A_diag_str =(A->row_stride + A->col_stride) * A->block->rstride;
         vsip_offset off_A = A->offset * A->block->rstride;
         vsip_scalar_d d0 = *(A->block->array + off_A);
         vsip_length n = n_B;
         vsip_stride ar_str = A->col_stride * A->block->rstride; /* doing transpose here */
         vsip_stride ac_str = A->row_stride * A->block->rstride; /* doing transpose here */
         vsip_stride bc_str = B->col_stride * B->block->rstride;
         vsip_stride br_str = B->row_stride * B->block->rstride;
         vsip_scalar_d *a_re;
         vsip_offset off_br0 = B->offset * B->block->rstride;
         vsip_offset off_br = off_br0;
         vsip_scalar_d *b_re = B->block->array + off_br;
         vsip_offset off_b0 = off_br0;
         vsip_offset off_b;
         vsip_scalar_d *b;
         vsip_offset off_a = A->offset * A->block->rstride;
         while(n-- >0){
            *b_re /= d0;
            b_re += br_str;
         }
         for(i=1; i<n_A; i++){
            off_A += A_diag_str;
            d0 = *(A->block->array + off_A);
            off_b0 += bc_str;
            off_b = off_b0;
            off_a += ac_str;
            off_br = off_br0;
            
            for(j=0; j<n_B; j++){
               n = i;
               a_re = A->block->array + off_a;
               b_re = B->block->array + off_br;
               dot = 0;
               while(n-- > 0){
                  dot += (*a_re * *b_re);
                  a_re += ar_str;
                  b_re += bc_str;
               }
               b = B->block->array + off_b;
               *b = (*b - dot)/d0;
               off_b += br_str;
               off_br += br_str;
            }
         } 
      }
      {
         vsip_scalar_d dot;
         vsip_scalar_d *b;
         vsip_stride ar_str = A->row_stride * A->block->rstride;
         vsip_length n_A = A->row_length;
         vsip_length n_A_1 = n_A - 1;
         vsip_stride A_diag_str = (A->col_stride + A->row_stride);
         vsip_length n_B = B->row_length;
         vsip_offset off_A = A->block->rstride * ( A->offset + (n_A_1) * A_diag_str);
         vsip_offset off_ar = (A->offset + n_A * A_diag_str - A->col_stride) * A->block->rstride; 
         vsip_scalar_d d0 = *(A->block->array + off_A);
         vsip_index i,j;
         vsip_length n = B->row_length;
         vsip_offset off_br0 = (n_A_1 * B->col_stride + B->offset) * B->block->rstride;
         vsip_offset off_br = off_br0;
         vsip_offset off_bc0 = (B->offset + B->col_stride * n_A) * B->block->rstride;
         vsip_offset off_bc;
         vsip_stride br_str = B->row_stride * B->block->rstride;
         vsip_stride bc_str = B->col_stride * B->block->rstride;
         vsip_scalar_d *b_re = B->block->array + off_br;
         vsip_scalar_d *a_re;
         while(n-- >0){
            *b_re /= d0;
            b_re += br_str;
         }
         A_diag_str *= A->block->rstride;
         for(i=1; i<n_A; i++){
            off_A -= A_diag_str;
            d0 = *(A->block->array + off_A);
            off_br0 -= bc_str;
            off_br = off_br0;
            off_bc0 -= bc_str;
            off_bc = off_bc0;
            off_ar -= A_diag_str;
            for(j=0; j<n_B; j++){
               n = i;
               a_re = A->block->array + off_ar;
               b_re = B->block->array + off_bc;
               dot = 0;
               while(n-- > 0){
                  dot += (*a_re * *b_re);
                  a_re += ar_str;
                  b_re += bc_str;
               }
               b = B->block->array + off_br;
               *b = (*b - dot)/d0;
               off_br += br_str;
               off_bc += br_str;
            }
         } 
      }
   } else { /* must be VSIP_TR_LOW */
      {
         vsip_scalar_d dot;
         vsip_scalar_d *b;
         vsip_length n_A = A->row_length;
         vsip_length n_B = B->row_length;
         vsip_index i,j;
         vsip_stride A_diag_str = (A->row_stride + A->col_stride) * A->block->rstride;
         vsip_offset off_A = A->offset * A->block->rstride;
         vsip_scalar_d d0 = *(A->block->array + off_A);
         vsip_length n = B->row_length;
         
         vsip_offset off_br0 = B->offset * B->block->rstride;
         vsip_offset off_br = off_br0;
         
         vsip_offset off_bc0 = B->offset * B->block->rstride;
         vsip_offset off_bc;
         
         vsip_scalar_d *b_re = B->block->array + off_br;
         vsip_scalar_d *a_re;
         vsip_stride a_str = A->row_stride * A->block->rstride;
         vsip_stride bc_str = B->col_stride * B->block->rstride;
         vsip_stride br_str = B->row_stride * B->block->rstride;
         vsip_offset off_a = A->offset * A->block->rstride; 
         vsip_stride off_a_str = A->col_stride * A->block->rstride;
         while(n-- >0){
            *b_re /= d0;
            b_re += br_str;
         }
         for(i=1; i<n_A; i++){
            off_A += A_diag_str;
            off_br0 += bc_str;
            off_br = off_br0;
            off_bc = off_bc0;
            d0 = *(A->block->array + off_A);
            off_a += off_a_str;
            for(j=0; j<n_B; j++){
               n = i;
               a_re = A->block->array + off_a;
               b_re = B->block->array + off_bc;
               dot = 0;
               while(n-- > 0){
                  dot += (*a_re * *b_re);
                  a_re += a_str;
                  b_re += bc_str;
               }
               b = B->block->array + off_br;
               *b = (*b - dot)/d0;
               off_br +=  br_str;
               off_bc +=  br_str;
            }
         } 
      }
      {
         vsip_scalar_d dot;
         vsip_length n_A = A->row_length;
         vsip_length n_A_1 = n_A - 1;
         vsip_length n_B = B->row_length;
         vsip_index i,j;
         vsip_stride A_diag_str = A->row_stride + A->col_stride;
         vsip_offset off_Bc0 = (B->offset + B->col_stride * n_A ) * B->block->rstride;
         vsip_offset off_Bc;
         vsip_offset off_A = A->block->rstride * (A->offset + (n_A-1)*(A->row_stride + A->col_stride));
         vsip_offset off_Ar= (A->offset +n_A * A_diag_str - A->row_stride) * A->block->rstride;
         vsip_stride off_A_str = A->block->rstride * (A->row_stride + A->col_stride);
         vsip_stride a_str = A->col_stride * A->block->rstride;
         vsip_scalar_d d0 = *(A->block->array + off_A);
         vsip_length n = n_B;
         vsip_stride str = B->row_stride * B->block->rstride;
         vsip_offset off_Br = (B->offset + n_A_1 * B->col_stride) * B->block->rstride; 
         vsip_offset off_Br0 = off_Br;
         vsip_stride off_Br_str = B->block->rstride * B->col_stride; /* B row stride */
         vsip_stride bc_str = off_Br_str;
         vsip_stride br_str = B->row_stride * B->block->rstride;
         vsip_scalar_d *a_re, *b;
         vsip_scalar_d *b_re = B->block->array + off_Br;
         while(n-- >0){
            *b_re /= d0;
            b_re += str;
         }
         A_diag_str *= A->block->rstride;
         for(i=1; i<n_A; i++){
            off_A -= off_A_str;
            d0 = *(A->block->array + off_A);
            off_Br0 -= off_Br_str;
            off_Br = off_Br0;
            off_Ar -= A_diag_str;
            off_Bc0 -= bc_str;
            off_Bc = off_Bc0;
            for(j=0; j<n_B; j++){
               n = i;
               a_re = A->block->array + off_Ar;
               b_re = B->block->array + off_Bc;
               dot = 0;
               while(n-- > 0){
                  dot += (*a_re * *b_re);
                  a_re += a_str;
                  b_re += bc_str;
               }
               b = B->block->array + off_Br;
               *b = (*b - dot)/d0;
               off_Br += br_str;
               off_Bc += br_str;
            }
         }
      }
   }
   return retval;
}  
