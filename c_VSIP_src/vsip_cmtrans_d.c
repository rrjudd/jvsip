/* Created RJudd March 18, 1998 */
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
/* $Id: vsip_cmtrans_d.c,v 2.0 2003/02/22 15:18:44 judd Exp $ */
/* April 20, 1998 1,2 to row,col */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_cmviewattributes_d.h>

void (vsip_cmtrans_d)(
  const vsip_cmview_d* A,
  const vsip_cmview_d* R) {
  {
    vsip_length lx = A->row_length,
                 ly = A->col_length;
    vsip_stride cAst = A->block->cstride, cRst = R->block->cstride;
    vsip_scalar_d tmp;
    vsip_scalar_d *a_p_r = (vsip_scalar_d*)(A->block->R->array + cAst * A->offset),
                  *a_p_i = (vsip_scalar_d*)(A->block->I->array + cAst * A->offset),
                  *r_p_r = (vsip_scalar_d*)(R->block->R->array + cRst * R->offset),
                  *r_p_i;
    vsip_length i, j;
    vsip_stride stAx = cAst * A->row_stride, stAy = cAst * A->col_stride;
    vsip_stride stRx = cRst * R->row_stride, stRy = cRst * R->col_stride;
    if((lx == ly) && (a_p_r == r_p_r)){
      for(i=1; i<lx; i++){
        for(j=0; j<i; j++){ 
           tmp = *(a_p_r + j * stAy + i * stAx);
           *(a_p_r + j * stAy + i * stAx) = *(a_p_r + j * stAx + i * stAy);
           *(a_p_r + j * stAx + i * stAy) = tmp; 
           tmp = *(a_p_i + j * stAy + i * stAx);
           *(a_p_i + j * stAy + i * stAx) = *(a_p_i + j * stAx + i * stAy);
           *(a_p_i + j * stAx + i * stAy) = tmp; 
        }
      }
    } else {
       for(i=0; i<ly; i++){
         r_p_r = (vsip_scalar_d*)(R->block->R->array + cRst * R->offset + i * stRx);
         r_p_i = (vsip_scalar_d*)(R->block->I->array + cRst * R->offset + i * stRx);
         a_p_r = (vsip_scalar_d*)(A->block->R->array + cAst * A->offset + i * stAy);
         a_p_i = (vsip_scalar_d*)(A->block->I->array + cAst * A->offset + i * stAy);
         for(j=0; j<lx; j++){
            *r_p_r = *a_p_r;
            *r_p_i = *a_p_i;
            r_p_r += stRy; a_p_r += stAx;
            r_p_i += stRy; a_p_i += stAx;
         }
      }
    }
  }
}
