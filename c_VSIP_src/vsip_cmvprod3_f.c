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
/* $Id: vsip_cmvprod3_f.c,v 2.1 2006/04/27 01:58:00 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_cmviewattributes_f.h>

void (vsip_cmvprod3_f)(
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

     vsip_cscalar_f b0,b1,b2;

     vsip_cscalar_f a00, a01, a02;
     vsip_cscalar_f a10, a11, a12;
     vsip_cscalar_f a20, a21, a22;

     vsip_scalar_f *Ap10_r = Ap00_r + ACst, *bp1_r = bp0_r + bst, *rp1_r = rp0_r + rst;
     vsip_scalar_f *Ap20_r = Ap10_r + ACst, *bp2_r = bp1_r + bst, *rp2_r = rp1_r + rst;

     vsip_scalar_f *Ap10_i = Ap00_i + ACst, *bp1_i = bp0_i + bst, *rp1_i = rp0_i + rst;
     vsip_scalar_f *Ap20_i = Ap10_i + ACst, *bp2_i = bp1_i + bst, *rp2_i = rp1_i + rst;

     b0.r = *bp0_r; b1.r = *bp1_r; b2.r = *bp2_r;
     b0.i = *bp0_i; b1.i = *bp1_i; b2.i = *bp2_i;

     a00.r = *Ap00_r; a01.r = *(Ap00_r+ARst); a02.r = *(Ap00_r + 2 * ARst);
     a10.r = *Ap10_r; a11.r = *(Ap10_r+ARst); a12.r = *(Ap10_r + 2 * ARst);
     a20.r = *Ap20_r; a21.r = *(Ap20_r+ARst); a22.r = *(Ap20_r + 2 * ARst);

     a00.i = *Ap00_i; a01.i = *(Ap00_i+ARst); a02.i = *(Ap00_i + 2 * ARst);
     a10.i = *Ap10_i; a11.i = *(Ap10_i+ARst); a12.i = *(Ap10_i + 2 * ARst);
     a20.i = *Ap20_i; a21.i = *(Ap20_i+ARst); a22.i = *(Ap20_i + 2 * ARst);
     
     *rp0_r = (b0.r * a00.r + b1.r * a01.r + b2.r * a02.r) -
              (b0.i * a00.i + b1.i * a01.i + b2.i * a02.i);
     *rp1_r = (b0.r * a10.r + b1.r * a11.r + b2.r * a12.r) - 
              (b0.i * a10.i + b1.i * a11.i + b2.i * a12.i); 
     *rp2_r = (b0.r * a20.r + b1.r * a21.r + b2.r * a22.r) - 
              (b0.i * a20.i + b1.i * a21.i + b2.i * a22.i); 

     *rp0_i = b0.r * a00.i + b1.r * a01.i + b2.r * a02.i + 
              b0.i * a00.r + b1.i * a01.r + b2.i * a02.r;
     *rp1_i = b0.r * a10.i + b1.r * a11.i + b2.r * a12.i + 
              b0.i * a10.r + b1.i * a11.r + b2.i * a12.r;
     *rp2_i = b0.r * a20.i + b1.r * a21.i + b2.r * a22.i + 
              b0.i * a20.r + b1.i * a21.r + b2.i * a22.r;

     return;
}

