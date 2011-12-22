/* Created RJudd April 24, 2003 */
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
/* $Id: VI_vfill_si.h,v 2.1 2004/04/03 16:15:17 judd Exp $ */
#ifndef VI_VFILL_SI_H
#define VI_VFILL_SI_H 1

#include<vsip.h>
#include<vsip_vviewattributes_si.h>

static
void 
VI_vfill_si(
          vsip_scalar_si alpha,
          const vsip_vview_si* r) {
   vsip_length n = r->length;
   vsip_stride rst = r->stride;
   vsip_scalar_si *rp = (r->block->array) + r->offset;
   while(n-- > 0){
      *rp  = alpha;
       rp += rst;
   }
   return;
}
#endif /* VI_VFILL_I_H */
