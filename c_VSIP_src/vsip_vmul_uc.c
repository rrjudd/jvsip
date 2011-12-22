/* Created RJudd                   */
/* SPAWARSYSCEN D857               */
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
/* $Id: vsip_vmul_uc.c,v 2.0 2003/02/22 15:19:16 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_uc.h>

void (vsip_vmul_uc)(
  const vsip_vview_uc *a,
  const vsip_vview_uc *b,
  const vsip_vview_uc *r) {
  { 
      /*define variables*/
      /* register */ unsigned int n = (unsigned int) r->length;
      /* register */ int ast = (int) a->stride,
                         bst = (int) b->stride,
                         rst = (int) r->stride;
      vsip_scalar_uc *ap = (a->block->array) + a->offset,
                    *bp = (b->block->array) + b->offset,
                    *rp = (r->block->array) + r->offset;
      /*end define*/
      while(n-- > 0){
         *rp = *ap * *bp;
         ap += ast; bp += bst; rp += rst;
      }
   }
}
