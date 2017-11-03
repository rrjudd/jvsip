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
/* $Id: vsip_cvgather_d.c,v 2.0 2003/02/22 15:18:50 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Tisdale error checking Sept 00 */

#include"vsip.h"
#include"vsip_vviewattributes_vi.h"
#include"vsip_cvviewattributes_d.h"

void vsip_cvgather_d(
                     const vsip_cvview_d* a,
                     const vsip_vview_vi* x,
                     const vsip_cvview_d* r) {
   vsip_length n = x->length;
   vsip_stride cast = a->block->cstride,
   crst = r->block->cstride;
   vsip_scalar_d 
   *apr = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset),
   *rpr = (vsip_scalar_d*) ((r->block->R->array) + crst * r->offset),
   *api = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset),
   *rpi = (vsip_scalar_d*) ((r->block->I->array) + crst * r->offset);
   vsip_stride 
   ast = (cast * a->stride),
   rst = (crst * r->stride);
   vsip_scalar_vi *xp = (x->block->array) + x->offset;
   vsip_stride xinc = 0;
   while(n-- >0){
      xinc = *xp * ast;
      *rpr = *(apr + xinc);
      *rpi = *(api + xinc);
      rpr += rst; rpi += rst; 
      xp  += x->stride;
   }
}


