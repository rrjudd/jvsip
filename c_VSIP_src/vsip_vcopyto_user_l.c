/* Created RJudd August 29, 2006 */
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
/* $Id: vsip_vcopyto_user_l.c,v 2.1 2007/04/21 19:39:33 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_l.h>

void (vsip_vcopyto_user_l)(
  const vsip_vview_l* a,
  vsip_scalar_l* const r) {
   vsip_length n   = a->length;
   vsip_stride ast = a->stride;
   vsip_scalar_l *ap = (a->block->array) + a->offset;
   vsip_scalar_l *rp = r;
   while(n-- > 0){
      *rp = *ap;
      ap += ast; rp++;
   }
   return;
}

