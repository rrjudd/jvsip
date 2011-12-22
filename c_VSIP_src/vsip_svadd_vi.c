/*
 *  vsip_svadd_vi.c
 *  tvcpp_xcode
 *
 *  Created by Randall Judd on 7/17/06.
 *  Copyright 2006 
 *  See Copyright statement in top level directory
 *
 */
/* $Id: vsip_svadd_vi.c,v 2.2 2007/04/16 18:37:19 judd Exp $ */
#include<vsip.h>
#include<vsip_vviewattributes_vi.h>

void (vsip_svadd_vi)(
                     vsip_scalar_vi a,
                     const vsip_vview_vi *b,
                     const vsip_vview_vi *r) {
   register vsip_scalar_vi alpha = a;  
   vsip_length n = r->length;
   vsip_stride bst = b->stride,
               rst = r->stride;
   vsip_scalar_vi *bp = (b->block->array) + b->offset,
                  *rp = (r->block->array) + r->offset;
   while(n-- > 0){
      *rp = alpha + *bp;
      bp += bst; rp += rst;
   }
}



