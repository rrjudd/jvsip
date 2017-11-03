/* Created RJudd Sep 26, 2013 */
/* created using vsip_vcopy_i_d.c as template*/
/*
 //  Copyright (c) 2013 Independent Consultant. All rights reserved.
 */
/*********************************************************************
 // This code includes no warranty, express or implied, including     /
 // the warranties of merchantability and fitness for a particular    /
 // purpose.                                                          /
 // No person or entity assumes any legal liability or responsibility /
 // for the accuracy, completeness, or usefulness of any information, /
 // apparatus, product, or process disclosed, or represents that      /
 // its use would not infringe privately owned rights.                /
 *********************************************************************/
/*********************************************************************
 // The MIT License (see copyright for jvsip in top level directory)
 // http://opensource.org/licenses/MIT
 **********************************************************************/
#include"vsip.h"
#include"vsip_vviewattributes_d.h"
#include"vsip_vviewattributes_vi.h"

void (vsip_vcopy_vi_d)(
  const vsip_vview_vi* a,
  const vsip_vview_d* r) {
  { 
      vsip_length n   = r->length;
      vsip_stride ast = a->stride, rst = r->stride * r->block->rstride;
      vsip_scalar_vi *ap = (a->block->array) + a->offset;
      vsip_scalar_d *rp = (r->block->array) + r->offset * r->block->rstride;
      /*end define*/
      while(n-- > 0){
         *rp = (vsip_scalar_d) *ap;
         ap += ast; rp += rst;
      }
   }
}
