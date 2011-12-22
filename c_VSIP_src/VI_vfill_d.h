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
/* $Id: VI_vfill_d.h,v 2.0 2003/02/22 15:18:34 judd Exp $ */
#ifndef VI_VFILL_D_H
#define VI_VFILL_D_H 1

#include<vsip.h>
#include<vsip_vviewattributes_d.h>

static
void 
VI_vfill_d(
          vsip_scalar_d alpha,
          const vsip_vview_d* r) {
   vsip_length n = r->length;
   vsip_stride rst = r->stride * r->block->rstride;
   vsip_scalar_d *rp = (r->block->array) + r->offset * r->block->rstride;
   while(n-- > 0){
      *rp  = alpha;
       rp += rst;
   }
   return;
}
#endif /* VI_VFILL_D_H */
