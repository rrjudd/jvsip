/*
 *  vsip_vadd_vi.c
 *  Created by Randall Judd on 7/17/06.
 *  Copyright 2006 
 *  See Copyright statement in top level directory
 */
/* $Id: vsip_vadd_vi.c,v 2.2 2007/04/16 18:40:59 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_vi.h>

void (vsip_vadd_vi)(
  const vsip_vview_vi *a,
  const vsip_vview_vi *b,
  const vsip_vview_vi *r) {
   vsip_length n = r->length;
   vsip_stride ast = a->stride,
               bst = b->stride,
               rst = r->stride;
   vsip_scalar_vi *ap = (a->block->array) + a->offset,
                  *bp = (b->block->array) + b->offset,
                  *rp = (r->block->array) + r->offset;
   while(n-- > 0){
      *rp = *ap + *bp;
      ap += ast; bp += bst; rp += rst;
   }
}
