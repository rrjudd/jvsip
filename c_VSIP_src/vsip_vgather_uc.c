/* Created RJudd                 */
/* SPAWARSYSCEN D857             */
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
/* $Id: vsip_vgather_uc.c,v 2.0 2003/02/22 15:19:13 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_uc.h>
#include<vsip_vviewattributes_vi.h>

void (vsip_vgather_uc)(
  const vsip_vview_uc* a,
  const vsip_vview_vi* x,
  const vsip_vview_uc* r) {
  {
   /* register */ unsigned int n = (unsigned int) x->length;
   /* register */ int ast = (int) a->stride,
                      rst = (int) r->stride,
                      xst = (int) x->stride;
    vsip_scalar_uc  *ap = (a->block->array) + a->offset,
                   *rp = (r->block->array) + r->offset; 
    vsip_scalar_vi *xp = (x->block->array) + x->offset;
    while(n-- >0){
       *rp = *(ap + *xp * ast);
        rp += rst; xp += xst;
    }
  }
}
