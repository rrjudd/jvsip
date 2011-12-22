/* Created RJudd September 15, 1997*/
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
/* $Id: VI_cvadd_f.h,v 2.0 2003/02/22 15:18:31 judd Exp $ */

#include<vsip.h>
#include <vsip_cvviewattributes_f.h>

#ifndef VI_CVADD_F_H
#define VI_CVADD_F_H

static
void 
VI_cvadd_f(
          const vsip_cvview_f *a,
          const vsip_cvview_f *b,
          const vsip_cvview_f *r) {	/* r_j = a_j + b_j	*/
  { 
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride;
      vsip_stride cbst = b->block->cstride;
      int crst = r->block->cstride;
      vsip_scalar_f *apr = (vsip_scalar_f *)((a->block->R->array) + cast * a->offset),
                    *bpr = (vsip_scalar_f *)((b->block->R->array) + cbst * b->offset),
                    *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_f *api = (vsip_scalar_f *)((a->block->I->array) + cast * a->offset),
                    *bpi = (vsip_scalar_f *)((b->block->I->array) + cbst * b->offset),
                    *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
      vsip_scalar_f tmp;
      /* register */ vsip_stride ast = (cast * a->stride),
                                 bst = (cbst * b->stride),
                                 rst = (crst * r->stride);
      while(n-- > 0){
        tmp  = *apr + *bpr;
        *rpi = *api + *bpi;
        *rpr = tmp;
        apr += ast; api += ast;
        bpr += bst; bpi += bst;
        rpr += rst; rpi += rst;
      }
   }
}
#endif
