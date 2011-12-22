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
/* $Id: vsip_gems_d.c,v 2.1 2003/03/08 14:43:34 judd Exp $ */
/* vsip_gemp_d */
#include<vsip_mviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip.h>

void (vsip_gems_d)(vsip_scalar_d alpha,
                   const vsip_mview_d *AA,
                   vsip_mat_op OpA,
                   vsip_scalar_d beta,
                   const vsip_mview_d *C){
   vsip_mview_d At = *AA;
   vsip_mview_d *A = &At;
   if(OpA == 1){
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
         vsip_stride Cst_C = C->col_stride * C->block->rstride;
         vsip_stride Cst_R = C->row_stride * C->block->rstride;
         vsip_stride Ast_C = A->col_stride * A->block->rstride;
         vsip_stride Ast_R = A->row_stride * A->block->rstride;
         vsip_scalar_d  *C_ptr =(vsip_scalar_d*) (C->block->array + C->offset * C->block->rstride),
                        *C_ptrR = C_ptr, /* pointer to row element zero */
                        *A_ptr =(vsip_scalar_d*) (A->block->array + A->offset * A->block->rstride),
                        *A_ptrR = A_ptr; /* pointer to row element zero */
         for(i = 0; i < M; i++){
             for(j = 0; j < N; j++){
                *C_ptr = alpha * *A_ptr + beta * *C_ptr;
                 C_ptr += Cst_R; A_ptr += Ast_R;
             }
             C_ptr = (C_ptrR += Cst_C); 
             A_ptr = (A_ptrR += Ast_C);
         }
      }
   }  
}
