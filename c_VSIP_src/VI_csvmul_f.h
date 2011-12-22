/* Created RJudd December 8, 1997 */
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
/* $Id: VI_csvmul_f.h,v 2.1 2006/10/20 16:22:58 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#ifndef VI_CSVMUL_F_H
#define VI_CSVMUL_F_H

static
void 
VI_csvmul_f(
  vsip_cscalar_f alpha,
  const vsip_cvview_f *b,
  const vsip_cvview_f *r) {	/* r_j = alpha*b_j	*/
   {
      /* register */ vsip_length n = r->length;
      vsip_stride cbst = b->block->cstride;
      vsip_stride crst = r->block->cstride;
      vsip_scalar_f *bpr = (vsip_scalar_f *)((b->block->R->array) + cbst * b->offset),
                    *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_f *bpi = (vsip_scalar_f *)((b->block->I->array) + cbst * b->offset),
                    *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
      register vsip_scalar_f temp;
      register vsip_stride bst = (cbst * b->stride),
                           rst = (crst * r->stride);
      while(n-- > 0){
          temp = alpha.r * *bpr - *bpi    * alpha.i;
          *rpi = alpha.r * *bpi + alpha.i * *bpr;
          *rpr = temp;
          bpr += bst; bpi += bst; 
          rpr += rst; rpi += rst;
      }
   }
}
#endif
