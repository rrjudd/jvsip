/* Created RJudd August 8, 2002 */
/* SPAWARSYSCEN */
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
/* $Id: VI_vcopy_d_d.h,v 2.0 2003/02/22 15:18:34 judd Exp $ */
#ifndef VI_VCOPY_D_D_H
#define VI_VCOPY_D_D_H 1

#include<vsip.h>
#include<vsip_vviewattributes_d.h>

static
void 
VI_vcopy_d_d(
  const vsip_vview_d* a,
  const vsip_vview_d* r) {
  {
      /* register */ vsip_length n   = r->length;
      /* register */ vsip_stride ast = a->stride * a->block->rstride,
                                 rst = r->stride * r->block->rstride;
      vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,
                    *rp = (r->block->array) + r->offset * r->block->rstride;
      /*end define*/
      while(n-- > 0){
         *rp = *ap;
         ap += ast; rp += rst;
      }
   }
   return;
}
#endif
