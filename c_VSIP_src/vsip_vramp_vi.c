/*
 *  vsip_vramp_vi.c
 *  Created by Randall Judd on 5/16/06.
 *  Copyright 2006 
 *  See Copyright statement in top level directory
 */
/* $Id: vsip_vramp_vi.c,v 2.4 2007/04/21 19:39:33 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_vi.h"

void (vsip_vramp_vi)(
                    vsip_scalar_vi x,
                    vsip_scalar_vi y, 
                    const vsip_vview_vi* r) {
   vsip_length N = r->length,i;
   register vsip_scalar_vi start = x;
   register vsip_scalar_vi inc = y;
   vsip_stride rst = r->stride;
   vsip_scalar_vi *rp    = (r->block->array) + r->offset;
   *rp = start;
   for(i=1; i<N; i++){
      rp += rst;
      *rp = start + (vsip_scalar_vi)i * inc;
   }
}

