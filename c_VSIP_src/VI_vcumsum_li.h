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
/* $Id: VI_vcumsum_li.h,v 2.1 2004/04/03 14:19:04 judd Exp $ */
#ifndef __VI_VCUMSUM_LI_H
#define __VI_VCUMSUM_LI_H

#include"vsip.h"
#include"vsip_vviewattributes_li.h"

static
void VI_vcumsum_l(
   const vsip_vview_li *a,
   const vsip_vview_li *r) {
   {
      /*define variables*/
      /* register */ vsip_length n = r->length;
      /* register */ vsip_stride ast = a->stride,
                                 rst = r->stride;
      vsip_scalar_li *ap = (a->block->array) + a->offset,
                    *rp = (r->block->array) + r->offset;
      vsip_scalar_li cumsum = *ap;
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
#endif /* __VI_VCUMSUM_LI_H */
