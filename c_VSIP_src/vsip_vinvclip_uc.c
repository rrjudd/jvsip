/* Created RJudd                 */
/* SPAWARSYSCEN D857             */
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
/* $Id: vsip_vinvclip_uc.c,v 2.0 2003/02/22 15:19:14 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_uc.h>

void (vsip_vinvclip_uc)(
  const vsip_vview_uc* a,
  vsip_scalar_uc t1,
  vsip_scalar_uc t2,
  vsip_scalar_uc t3,
  vsip_scalar_uc c1,
  vsip_scalar_uc c2,
  const vsip_vview_uc* r) {
   {
     /* register */ unsigned int n = (unsigned int) r->length;
     /* register */ int ast = (int) a->stride,
                        rst = (int) r->stride;
      vsip_scalar_uc *ap = (a->block->array) + a->offset,
                    *rp = (r->block->array) + r->offset;
      while(n-- > 0){
         *rp  = (*ap < t1) ? *ap : ((*ap < t2) ? c1 : ((*ap <= t3) ? c2 : *ap));
          ap += ast; rp += rst;
      }
   }
}
