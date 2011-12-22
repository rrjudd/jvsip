/* Created RJudd December 30, 1997 */
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
/* $Id: vsip_crvsub_f.c,v 2.0 2003/02/22 15:18:47 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Modified RJudd January 3, 1998 */
/* to incorporate rstride */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include <vsip_vviewattributes_f.h>
#include <vsip_cvviewattributes_f.h>

void (vsip_crvsub_f)(
  const vsip_cvview_f* a,
  const vsip_vview_f* b,
  const vsip_cvview_f* r) {
  { 
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  crst = r->block->cstride,
                  rbst = b->block->rstride;
      vsip_scalar_f *apr = (vsip_scalar_f *)((a->block->R->array) + cast * a->offset),
                    *bp  = (vsip_scalar_f *)((b->block->array)  + rbst * b->offset),
                    *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_f *api = (vsip_scalar_f *)((a->block->I->array) + cast * a->offset),
                    *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
      vsip_scalar_f tmp;
 
      /* register */ vsip_stride ast =  (cast * a->stride),
                                 bst =  rbst * b->stride,
                                 rst =  (crst * r->stride);
      /*end define*/
      while(n-- > 0){
        tmp  = *apr - *bp;
        *rpi = *api;
        *rpr = tmp;
        apr += ast; api += ast;
        bp  += bst; 
        rpr += rst; rpi += rst;
      }
   }
}
