/* Created RJudd January 26, 2000 */
/* SPAWARSYSCEN D857 */
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
/* $Id: vsip_mgather_f.c,v 2.0 2003/02/22 15:18:56 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_vviewattributes_mi.h>
#include<vsip_vviewattributes_vi.h>

void (vsip_mgather_f)(
  const vsip_mview_f *a,
  const vsip_vview_mi *x,
  const vsip_vview_f *r) {

  { 
    vsip_length n = x->length;
    vsip_stride ast_c = a->col_stride * a->block->rstride,
                ast_r = a->row_stride * a->block->rstride,
                rst = r->stride * r->block->rstride,
                xst = x->stride * 2; /* stride of matrix index row or col value */
    vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_vi *xp_r = (x->block->array) + x->offset; /* row value */
    vsip_scalar_vi *xp_c = xp_r + 1;                      /* col value */
    /*end define*/
    while(n-- > 0){
    *rp = *(ap + *xp_r * ast_c + *xp_c * ast_r);
     rp += rst; xp_r += xst; xp_c += xst;
    }
  }
  return;
}
