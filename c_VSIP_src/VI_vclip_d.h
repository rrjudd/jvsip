/* Created RJudd January 1, 1998 */
/* SPAWARSYSCEN D881 */
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
/* $Id: VI_vclip_d.h,v 2.0 2003/02/22 15:18:34 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#ifndef VI_VCLIP_D_H
#define VI_VCLIP_D_H

static
void 
VI_vclip_d(
          const vsip_vview_d* a,
          vsip_scalar_d t1,
          vsip_scalar_d t2,
          vsip_scalar_d c1,
          vsip_scalar_d c2,
          const vsip_vview_d* r) {
   {
      /* register */ vsip_length n = r->length;
      /* register */ vsip_stride ast = a->stride * a->block->rstride,
                                 rst = r->stride * r->block->rstride;
      vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,
                    *rp = (r->block->array) + r->offset * r->block->rstride;
      while(n-- > 0){
         *rp  = (*ap <= t1) ? c1 : ((*ap < t2) ? *ap : c2);
          ap += ast; rp += rst;
      }
   }
}
#endif
