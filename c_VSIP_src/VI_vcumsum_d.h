/* Created RJudd  */
/* SPAWARSYSCEN   */
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
/* $Id: VI_vcumsum_d.h,v 2.3 2007/04/16 16:32:09 judd Exp $ */
#ifndef __VI_VCUMSUM_D_H
#define __VI_VCUMSUM_D_H

#include"vsip.h"
#include"vsip_vviewattributes_d.h"

static
void VI_vcumsum_d(
   const vsip_vview_d *a,
   const vsip_vview_d *r) {
   {
      /*define variables*/
      /* register */ vsip_length n = r->length;
      /* register */ vsip_stride ast = a->stride * a->block->rstride,
                                 rst = r->stride * r->block->rstride;
      vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,
                    *rp = (r->block->array) + r->offset * r->block->rstride;
      register vsip_scalar_d cumsum = *ap;
      *rp = cumsum;
      ap += ast; rp += rst;
      n--;
      /*end define*/
      while(n-- > 0){
         cumsum += *ap;
         *rp = cumsum;
         ap += ast; rp += rst;
      }
   }
}

#endif /* __VI_VCUMSUM_D_H */
