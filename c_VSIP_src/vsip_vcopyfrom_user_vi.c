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
/* $Id: vsip_vcopyfrom_user_vi.c,v 2.1 2008/09/17 02:30:40 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_vi.h"

void (vsip_vcopyfrom_user_vi)(
  vsip_scalar_vi* const r,
  const vsip_vview_vi* a) {
   vsip_length n   = a->length;
   vsip_stride ast = a->stride;
   vsip_scalar_vi *ap = (a->block->array) + a->offset;
   vsip_scalar_vi *rp = r;
   while(n-- > 0){
      *ap = *rp;
      ap += ast; rp++;
   }
   return;
}

