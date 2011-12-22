/* Created RJudd March 14, 1998 */
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
/* $Id: vsip_mvprod_d.c,v 2.0 2003/02/22 15:19:01 judd Exp $ */
/* Modified to vsip_mvpord_d.c */
/* April 21, 1998 1,2 to row,col */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_mviewattributes_d.h>

void (vsip_mvprod_d)(
  const vsip_mview_d* A,
  const vsip_vview_d* b,
  const vsip_vview_d* r) {
  {
     vsip_length nx = 0, mx = 0;
                  
     vsip_scalar_d  *bp = b->block->array + b->offset * b->block->rstride,
                    *rp = r->block->array + r->offset * r->block->rstride,
                   *Ayp = A->block->array + A->offset * A->block->rstride,
                   *Axp = Ayp;
     vsip_stride rst = r->stride * r->block->rstride,
                 ARst = A->row_stride * A->block->rstride,
                 ACst = A->col_stride * A->block->rstride,
                 bst = b->stride * b->block->rstride;
     while(nx++ < A->col_length){
         *rp = 0;
         mx = 0;
         while(mx++ < A->row_length){
             *rp += *bp * *Axp;
             bp += bst; Axp += ARst;
         }
         bp = b->block->array + b->offset * b->block->rstride;
         Axp = (Ayp += ACst);
         rp += rst;
     }
  }
}

