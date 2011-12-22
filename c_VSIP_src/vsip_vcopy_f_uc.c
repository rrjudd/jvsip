/* Created RJudd               */
/* SPAWARSYSCEN D857           */
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
/* $Id: vsip_vcopy_f_uc.c,v 2.0 2003/02/22 15:19:11 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_vviewattributes_uc.h>

void (vsip_vcopy_f_uc)(
  const vsip_vview_f* a,
  const vsip_vview_uc* r) {
  { 
      /* register */ vsip_length n   = r->length;
      /* register */ vsip_stride ast = a->stride * a->block->rstride,
                                 rst = r->stride;
      vsip_scalar_f  *ap = (a->block->array) + a->offset * a->block->rstride;
      vsip_scalar_uc *rp = (r->block->array) + r->offset;
      /*end define*/
      while(n-- > 0){
         *rp = (vsip_scalar_uc) *ap;
         ap += ast; rp += rst;
      }
   }
}
