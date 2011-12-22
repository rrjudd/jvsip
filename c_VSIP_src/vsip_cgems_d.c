/* Created RJudd January 27, 1999 */
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
/* $Id: vsip_cgems_d.c,v 2.1 2003/03/08 14:43:33 judd Exp $ */
/* vsip_gemp_d */
#include<vsip_cmviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip.h>

void (vsip_cgems_d)(vsip_cscalar_d alpha,
                   const vsip_cmview_d *AA,
                   vsip_mat_op OpA,
                   vsip_cscalar_d beta,
                   const vsip_cmview_d *C){
   vsip_cmview_d At = *AA;
   vsip_cmview_d *A = &At;
   if((OpA == 1) || (OpA == 2)){
     A->row_length = AA->col_length;
     A->col_length = AA->row_length;
     A->row_stride = AA->col_stride;
     A->col_stride = AA->row_stride;
   }
   {
      vsip_length M = A->col_length;
      vsip_length N = A->row_length;
      vsip_length i,j;
      {
         vsip_stride Cst_C = C->col_stride * C->block->cstride;
         vsip_stride Cst_R = C->row_stride * C->block->cstride;
         vsip_stride Ast_C = A->col_stride * A->block->cstride;
         vsip_stride Ast_R = A->row_stride * A->block->cstride;
         vsip_scalar_d temp;
         vsip_scalar_d *C_ptr_r =(vsip_scalar_d*) (C->block->R->array + C->offset * C->block->cstride),
                       *C_ptrR_r = C_ptr_r,
                       *C_ptr_i =(vsip_scalar_d*) (C->block->I->array + C->offset * C->block->cstride),
                       *C_ptrR_i = C_ptr_i,
                       *A_ptr_r =(vsip_scalar_d*) (A->block->R->array + A->offset * A->block->cstride),
                       *A_ptrR_r = A_ptr_r,
                       *A_ptr_i =(vsip_scalar_d*) (A->block->I->array + A->offset * A->block->cstride),
                       *A_ptrR_i = A_ptr_i;
         if((OpA == 0) || (OpA == 1)){
            for(i = 0; i < M; i++){
                for(j = 0; j < N; j++){
                    temp     = alpha.r * *A_ptr_r - alpha.i * *A_ptr_i +
                               beta.r  * *C_ptr_r - beta.i  * *C_ptr_i;
                    *C_ptr_i = alpha.r * *A_ptr_i + alpha.i * *A_ptr_r +
                               beta.r  * *C_ptr_i + beta.i  * *C_ptr_r;
                    *C_ptr_r = temp;
                    C_ptr_r += Cst_R; A_ptr_r += Ast_R;
                    C_ptr_i += Cst_R; A_ptr_i += Ast_R;
                }
                C_ptr_r = (C_ptrR_r += Cst_C); 
                A_ptr_r = (A_ptrR_r += Ast_C);
                C_ptr_i = (C_ptrR_i += Cst_C); 
                A_ptr_i = (A_ptrR_i += Ast_C);
            }
         } else {
            for(i = 0; i < M; i++){
                for(j = 0; j < N; j++){
                    temp     = alpha.r * *A_ptr_r + alpha.i * *A_ptr_i + 
                               beta.r  * *C_ptr_r - beta.i  * *C_ptr_i; 
                    *C_ptr_i = alpha.i * *A_ptr_r - alpha.r * *A_ptr_i +
                               beta.r  * *C_ptr_i + beta.i  * *C_ptr_r; 
                    *C_ptr_r = temp;
                    C_ptr_r += Cst_R; A_ptr_r += Ast_R;
                    C_ptr_i += Cst_R; A_ptr_i += Ast_R;
                }
                C_ptr_r = (C_ptrR_r += Cst_C); 
                A_ptr_r = (A_ptrR_r += Ast_C);
                C_ptr_i = (C_ptrR_i += Cst_C); 
                A_ptr_i = (A_ptrR_i += Ast_C);
            }
         }
      }
   }  
}
