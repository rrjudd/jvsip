/* Created RJudd January 4, 1998 */
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
/* $Id: vsip_vcmplx_d.c,v 2.0 2003/02/22 15:19:11 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Tisdale error checking Sept 00 */

#include"vsip.h"
#include"vsip_vviewattributes_d.h"
#include"vsip_cvviewattributes_d.h"

void vsip_vcmplx_d(
                   const vsip_vview_d* a,
                   const vsip_vview_d* b,
                   const vsip_cvview_d* r) {
   vsip_length n = r->length;
   vsip_stride crst = r->block->cstride;
   vsip_scalar_d 
   *ap  = (vsip_scalar_d*) (a->block->array) +  a->offset * a->block->rstride,
   *bp  = (vsip_scalar_d*) (b->block->array) +  b->offset * b->block->rstride,
   *rpr = (vsip_scalar_d*) ((r->block->R->array) + crst * r->offset),
   *rpi = (vsip_scalar_d*) ((r->block->I->array) + crst * r->offset);
   vsip_scalar_d  temp;
   vsip_stride ast = a->stride * a->block->rstride,
   bst = b->stride * b->block->rstride,
   rst = (crst * r->stride);
   while(n-- > 0){
      temp = *ap;
      *rpi = *bp;
      *rpr = temp;
      ap += ast;
      bp += bst;
      rpr += rst; rpi += rst;
   }
}
