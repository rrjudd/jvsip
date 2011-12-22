/* Created RJudd */
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
/* $Id: vsip_cmvprod4_f.c,v 2.1 2006/04/27 01:58:00 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_cmviewattributes_f.h>

void (vsip_cmvprod4_f)(
  const vsip_cmview_f* A,
  const vsip_cvview_f* b,
  const vsip_cvview_f* r) {
                  
     vsip_scalar_f  *bp0_r  = b->block->R->array + b->offset * b->block->cstride,
                    *rp0_r  = r->block->R->array + r->offset * r->block->cstride,
                    *Ap00_r = A->block->R->array + A->offset * A->block->cstride;
     vsip_scalar_f  *bp0_i  = b->block->I->array + b->offset * b->block->cstride,
                    *rp0_i  = r->block->I->array + r->offset * r->block->cstride,
                    *Ap00_i = A->block->I->array + A->offset * A->block->cstride;
     vsip_stride rst  = r->stride * r->block->cstride,
                 ARst = A->row_stride * A->block->cstride,
                 ACst = A->col_stride * A->block->cstride,
                 bst  = b->stride * b->block->cstride;

     vsip_cscalar_f b0, b1, b2, b3;

     vsip_cscalar_f a00, a01, a02, a03;
     vsip_cscalar_f a10, a11, a12, a13;
     vsip_cscalar_f a20, a21, a22, a23;
     vsip_cscalar_f a30, a31, a32, a33;

     vsip_scalar_f *Ap10_r = Ap00_r + ACst, *bp1_r = bp0_r + bst, *rp1_r = rp0_r + rst;
     vsip_scalar_f *Ap20_r = Ap10_r + ACst, *bp2_r = bp1_r + bst, *rp2_r = rp1_r + rst;
     vsip_scalar_f *Ap30_r = Ap20_r + ACst, *bp3_r = bp2_r + bst, *rp3_r = rp2_r + rst;

     vsip_scalar_f *Ap10_i = Ap00_i + ACst, *bp1_i = bp0_i + bst, *rp1_i = rp0_i + rst;
     vsip_scalar_f *Ap20_i = Ap10_i + ACst, *bp2_i = bp1_i + bst, *rp2_i = rp1_i + rst;
     vsip_scalar_f *Ap30_i = Ap20_i + ACst, *bp3_i = bp2_i + bst, *rp3_i = rp2_i + rst;

     b0.r = *bp0_r; b1.r = *bp1_r; b2.r = *bp2_r; b3.r = *bp3_r;
     b0.i = *bp0_i; b1.i = *bp1_i; b2.i = *bp2_i; b3.i = *bp3_i;

     a00.r = *Ap00_r; a01.r = *(Ap00_r+ARst); a02.r = *(Ap00_r + 2 * ARst); a03.r = *(Ap00_r + 3 * ARst);
     a10.r = *Ap10_r; a11.r = *(Ap10_r+ARst); a12.r = *(Ap10_r + 2 * ARst); a13.r = *(Ap10_r + 3 * ARst);
     a20.r = *Ap20_r; a21.r = *(Ap20_r+ARst); a22.r = *(Ap20_r + 2 * ARst); a23.r = *(Ap20_r + 3 * ARst);
     a30.r = *Ap30_r; a31.r = *(Ap30_r+ARst); a32.r = *(Ap30_r + 2 * ARst); a33.r = *(Ap30_r + 3 * ARst);

     a00.i = *Ap00_i; a01.i = *(Ap00_i+ARst); a02.i = *(Ap00_i + 2 * ARst); a03.i = *(Ap00_i + 3 * ARst);
     a10.i = *Ap10_i; a11.i = *(Ap10_i+ARst); a12.i = *(Ap10_i + 2 * ARst); a13.i = *(Ap10_i + 3 * ARst);
     a20.i = *Ap20_i; a21.i = *(Ap20_i+ARst); a22.i = *(Ap20_i + 2 * ARst); a23.i = *(Ap20_i + 3 * ARst);
     a30.i = *Ap30_i; a31.i = *(Ap30_i+ARst); a32.i = *(Ap30_i + 2 * ARst); a33.i = *(Ap30_i + 3 * ARst);

     
     *rp0_r = (b0.r * a00.r + b1.r * a01.r + b2.r * a02.r + b3.r * a03.r) -
              (b0.i * a00.i + b1.i * a01.i + b2.i * a02.i + b3.i * a03.i);
     *rp1_r = (b0.r * a10.r + b1.r * a11.r + b2.r * a12.r + b3.r * a13.r) - 
              (b0.i * a10.i + b1.i * a11.i + b2.i * a12.i + b3.i * a13.i); 
     *rp2_r = (b0.r * a20.r + b1.r * a21.r + b2.r * a22.r + b3.r * a23.r) - 
              (b0.i * a20.i + b1.i * a21.i + b2.i * a22.i + b3.i * a23.i); 
     *rp3_r = (b0.r * a30.r + b1.r * a31.r + b2.r * a32.r + b3.r * a33.r) - 
              (b0.i * a30.i + b1.i * a31.i + b2.i * a32.i + b3.i * a33.i); 

     *rp0_i = b0.r * a00.i + b1.r * a01.i + b2.r * a02.i + b3.r * a03.i + 
              b0.i * a00.r + b1.i * a01.r + b2.i * a02.r + b3.i * a03.r;
     *rp1_i = b0.r * a10.i + b1.r * a11.i + b2.r * a12.i + b3.r * a13.i + 
              b0.i * a10.r + b1.i * a11.r + b2.i * a12.r + b3.i * a13.r;
     *rp2_i = b0.r * a20.i + b1.r * a21.i + b2.r * a22.i + b3.r * a23.i + 
              b0.i * a20.r + b1.i * a21.r + b2.i * a22.r + b3.i * a23.r;
     *rp3_i = b0.r * a30.i + b1.r * a31.i + b2.r * a32.i + b3.r * a33.i + 
              b0.i * a30.r + b1.i * a31.r + b2.i * a32.r + b3.i * a33.r;

     return;
}

