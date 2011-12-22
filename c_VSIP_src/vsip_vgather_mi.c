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
/* $Id: vsip_vgather_mi.c,v 2.1 2008/03/04 06:13:12 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_mi.h>
#include<vsip_vviewattributes_vi.h>

void (vsip_vgather_mi)(
  const vsip_vview_mi* a,
  const vsip_vview_vi* x,
  const vsip_vview_mi* r) {
  {
    vsip_length n   = x->length;
    vsip_stride ast =  2 * a->stride,
                rst =  2 * r->stride,
                xst =  x->stride;
    vsip_scalar_vi *apr = (a->block->array) + 2 * a->offset,
                   *rpr = (r->block->array) + 2 * r->offset; 
    vsip_scalar_vi *apc = apr + 1,
                   *rpc = rpr + 1;
    vsip_scalar_vi  *xp = (x->block->array) + x->offset;
    while(n-- >0){
       *rpr = *(apr + *xp * ast);
       *rpc = *(apc + *xp * ast);
        rpr += rst; rpc += rst; xp += xst;
    }
  }
}
