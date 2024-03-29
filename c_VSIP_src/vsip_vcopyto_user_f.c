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
/* $Id: vsip_vcopyto_user_f.c,v 2.2 2007/04/21 19:39:33 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_f.h"

void (vsip_vcopyto_user_f)(
  const vsip_vview_f* a,
  vsip_scalar_f* const r) {
   vsip_length n   = a->length;
   vsip_stride ast = a->stride * a->block->rstride;
   vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride;
   vsip_scalar_f *rp = r;
   while(n-- > 0){
      *rp = *ap;
      ap += ast; rp++;
   }
   return;
}

