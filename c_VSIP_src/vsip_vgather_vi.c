/* Created RJudd */
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
/* $Id: vsip_vgather_vi.c,v 2.1 2008/03/04 06:13:12 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_si.h>
#include<vsip_vviewattributes_vi.h>

void vsip_vgather_vi(
                     const vsip_vview_vi* a,
                     const vsip_vview_vi* x,
                     const vsip_vview_vi* r) {
   vsip_length n   = x->length;
   vsip_stride 
   ast =  a->stride,
   rst =  r->stride,
   xst =  x->stride;
   vsip_scalar_vi  
   *ap = (a->block->array) + a->offset,
   *rp = (r->block->array) + r->offset; 
   vsip_scalar_vi  *xp = (x->block->array) + x->offset;
   while(n-- >0){
      *rp = *(ap + *xp * ast);
      rp += rst; xp += xst;
   }
}

