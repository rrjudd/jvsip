/* Created RJudd December 29, 1997 */
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
/* $Id: vsip_cvsub_f.c,v 2.0 2003/02/22 15:18:52 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Development Mode RJudd Sept 00 */

#include"vsip.h"
#include "vsip_cvviewattributes_f.h"

void (vsip_cvsub_f)(
  const vsip_cvview_f *a,
  const vsip_cvview_f *b,
  const vsip_cvview_f *r) {
  { 
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride;
      vsip_stride cbst = b->block->cstride;
      vsip_stride crst = r->block->cstride;
      vsip_scalar_f *apr = (vsip_scalar_f *)((a->block->R->array) + cast * a->offset),
                    *bpr = (vsip_scalar_f *)((b->block->R->array) + cbst * b->offset),
                    *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_f *api = (vsip_scalar_f *)((a->block->I->array) + cast * a->offset),
                    *bpi = (vsip_scalar_f *)((b->block->I->array) + cbst * b->offset),
                    *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
      /* register */ vsip_stride ast = (cast * a->stride),
                                 bst = (cbst * b->stride),
                                 rst = (crst * r->stride);
      /*end define*/
      while(n-- > 0){
        *rpr = *apr - *bpr;
        *rpi = *api - *bpi;
        apr += ast; api += ast; 
        bpr += bst; bpi += bst; 
        rpr += rst; rpi += rst;
      }
   }
}
