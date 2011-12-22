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
/* $Id: vsip_crvsub_d.c,v 2.0 2003/02/22 15:18:47 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Modified RJudd January 3, 1998 */
/* to incorporate rstride */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include <vsip_vviewattributes_d.h>
#include <vsip_cvviewattributes_d.h>

void (vsip_crvsub_d)(
  const vsip_cvview_d* a,
  const vsip_vview_d* b,
  const vsip_cvview_d* r) {
  { 
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  crst = r->block->cstride,
                  rbst = b->block->rstride;
      vsip_scalar_d *apr = (vsip_scalar_d *)((a->block->R->array) + cast * a->offset),
                    *bp  = (vsip_scalar_d *)((b->block->array)  + rbst * b->offset),
                    *rpr = (vsip_scalar_d *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_d *api = (vsip_scalar_d *)((a->block->I->array) + cast * a->offset),
                    *rpi = (vsip_scalar_d *)((r->block->I->array) + crst * r->offset);
      vsip_scalar_d tmp;
 
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
