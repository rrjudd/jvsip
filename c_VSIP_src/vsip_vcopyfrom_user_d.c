/* Created RJudd September 4, 2006 */
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
/* $Id: vsip_vcopyfrom_user_d.c,v 2.1 2007/04/18 17:15:18 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>

void (vsip_vcopyfrom_user_d)(
  vsip_scalar_d* const r,
  const vsip_vview_d* a) {
   vsip_length n   = a->length;
   vsip_stride ast = a->stride * a->block->rstride;
   vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride;
   vsip_scalar_d *rp = r;
   while(n-- > 0){
      *ap = *rp;
      ap += ast; rp++;
   }
   return;
}

