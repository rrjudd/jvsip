/* Created RJudd                   */
/* SPAWARSYSCEN                    */
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
/* $Id: vsip_vadd_uc.c,v 2.1 2006/10/20 16:17:09 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_uc.h>

void (vsip_vadd_uc)(
  const vsip_vview_uc *a,
  const vsip_vview_uc *b,
  const vsip_vview_uc *r) {
    {
      /*define variables*/
      /* register */ vsip_length n = r->length;
      /* register */ vsip_stride ast = a->stride,
                         bst = b->stride,
                         rst = r->stride;
      vsip_scalar_uc *ap = (a->block->array) + a->offset,
                    *bp = (b->block->array) + b->offset,
                    *rp = (r->block->array) + r->offset;
      /*end define*/
      while(n-- > 0){
         *rp = *ap + *bp;
         ap += ast; bp += bst; rp += rst;
      }
    }
}
