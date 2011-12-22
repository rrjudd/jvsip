/* Created RJudd */
/* */
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
/* $Id: vsip_mvprod4_f.c,v 2.1 2006/04/27 01:58:00 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_mviewattributes_f.h>

void (vsip_mvprod4_f)(
  const vsip_mview_f* A,
  const vsip_vview_f* b,
  const vsip_vview_f* r) {
     vsip_scalar_f  *bp0 = b->block->array + b->offset * b->block->rstride,
                    *rp0 = r->block->array + r->offset * r->block->rstride,
                    *Ap00 = A->block->array + A->offset * A->block->rstride;
     vsip_stride rst = r->stride * r->block->rstride,
                 ARst = A->row_stride * A->block->rstride,
                 ACst = A->col_stride * A->block->rstride,
                 bst = b->stride * b->block->rstride;

     vsip_scalar_f b0,b1,b2,b3;

     vsip_scalar_f a00, a01, a02, a03;
     vsip_scalar_f a10, a11, a12, a13;
     vsip_scalar_f a20, a21, a22, a23;
     vsip_scalar_f a30, a31, a32, a33;

     vsip_scalar_f *Ap10 = Ap00 + ACst, *bp1 = bp0 + bst, *rp1 = rp0 + rst;
     vsip_scalar_f *Ap20 = Ap10 + ACst, *bp2 = bp1 + bst, *rp2 = rp1 + rst;
     vsip_scalar_f *Ap30 = Ap20 + ACst, *bp3 = bp2 + bst, *rp3 = rp2 + rst;

     b0 = *bp0; b1 = *bp1; b2 = *bp2; b3 = *bp3;

     a00 = *Ap00; a01 = *(Ap00+ARst); a02 = *(Ap00 + 2 * ARst); a03 = *(Ap00 + 3 * ARst);
     a10 = *Ap10; a11 = *(Ap10+ARst); a12 = *(Ap10 + 2 * ARst); a13 = *(Ap10 + 3 * ARst);
     a20 = *Ap20; a21 = *(Ap20+ARst); a22 = *(Ap20 + 2 * ARst); a23 = *(Ap20 + 3 * ARst);
     a30 = *Ap30; a31 = *(Ap30+ARst); a32 = *(Ap30 + 2 * ARst); a33 = *(Ap30 + 3 * ARst);
     
     *rp0 = b0 * a00 + b1 * a01 + b2 * a02 + b3 * a03; 
     *rp1 = b0 * a10 + b1 * a11 + b2 * a12 + b3 * a13; 
     *rp2 = b0 * a20 + b1 * a21 + b2 * a22 + b3 * a23; 
     *rp3 = b0 * a30 + b1 * a31 + b2 * a32 + b3 * a33; 

     return;
}

