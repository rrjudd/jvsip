/* Created RJudd */
/* VSIPL Consultant */
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
/* $Id: vsip_mvprod3_d.c,v 2.2 2006/04/17 19:38:02 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_mviewattributes_d.h>

void (vsip_mvprod3_d)(
  const vsip_mview_d* A,
  const vsip_vview_d* b,
  const vsip_vview_d* r) {
                  
     vsip_scalar_d  *bp0 = b->block->array + b->offset * b->block->rstride,
                    *rp0 = r->block->array + r->offset * r->block->rstride,
                    *Ap00 = A->block->array + A->offset * A->block->rstride;
     vsip_stride rst = r->stride * r->block->rstride,
                ARst = A->row_stride * A->block->rstride,
                ACst = A->col_stride * A->block->rstride,
                bst = b->stride * b->block->rstride;
     vsip_scalar_d b0,b1,b2;
     vsip_scalar_d a00, a01, a02;
     vsip_scalar_d a10, a11, a12;
     vsip_scalar_d a20, a21, a22;
     vsip_scalar_d *Ap10 = Ap00 + ACst, *bp1 = bp0 + bst, *rp1 = rp0 + rst;
     vsip_scalar_d *Ap20 = Ap10 + ACst, *bp2 = bp1 + bst, *rp2 = rp1 + rst;
     b0 = *bp0; b1 = *bp1; b2 = *bp2;
     a00 = *Ap00; a01 = *(Ap00+ARst); a02 = *(Ap00 + 2 * ARst);
     a10 = *Ap10; a11 = *(Ap10+ARst); a12 = *(Ap10 + 2 * ARst);
     a20 = *Ap20; a21 = *(Ap20+ARst); a22 = *(Ap20 + 2 * ARst);
     
     *rp0 = b0 * a00 + b1 * a01 + b2 * a02; 
     *rp1 = b0 * a10 + b1 * a11 + b2 * a12; 
     *rp2 = b0 * a20 + b1 * a21 + b2 * a22; 

     return;
}

