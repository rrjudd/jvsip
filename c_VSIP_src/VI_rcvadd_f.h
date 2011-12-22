/* Created RJudd 27 Dec 1997 */
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
/* $Id: VI_rcvadd_f.h,v 2.0 2003/02/22 15:18:33 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#ifndef VI_RCVADD_F_H
#define VI_RCVADD_F_H

static
void 
VI_rcvadd_f(
  const vsip_vview_f *a,
  const vsip_cvview_f *b,
  const vsip_cvview_f *r) {
  { 
      /* register */ vsip_length n = r->length;
      vsip_stride cbst = b->block->cstride,
                  crst = r->block->cstride,
                  rast = a->block->rstride;
      vsip_scalar_f *ap = (vsip_scalar_f *)((a->block->array) + a->offset * rast),
                    *bpr = (vsip_scalar_f *)((b->block->R->array) + cbst * b->offset),
                    *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_f *bpi = (vsip_scalar_f *)((b->block->I->array) + cbst * b->offset),
                    *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
      vsip_scalar_f temp;
      /* register */ vsip_stride ast = a->stride * rast,
                                 bst = (cbst * b->stride),
                                 rst = (crst * r->stride);
      while(n-- > 0){
        temp = *ap + *bpr;
        *rpi = *bpi;
        *rpr = temp;
        ap  += ast;
        bpr += bst; bpi += bst;
        rpr += rst; rpi += rst;
      }
   }
}

#endif
