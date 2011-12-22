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
/* $Id: vsip_svmul_uc.c,v 2.1 2007/04/16 18:39:38 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_uc.h>

void (vsip_svmul_uc)(
  vsip_scalar_uc a,
  const vsip_vview_uc *b,
  const vsip_vview_uc *r) {
   register vsip_scalar_uc alpha = a;
   vsip_length n = r->length;
   vsip_stride bst = b->stride,
               rst = r->stride;
   vsip_scalar_uc *bp = (b->block->array) + b->offset,
                  *rp = (r->block->array) + r->offset;
   while(n-- > 0){
      *rp = alpha * *bp;
      bp += bst; rp += rst;
   }
}

