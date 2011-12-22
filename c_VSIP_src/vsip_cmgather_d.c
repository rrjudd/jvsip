/* Created RJudd March 5, 2000 */
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
/* $Id: vsip_cmgather_d.c,v 2.0 2003/02/22 15:18:42 judd Exp $ */

#include<vsip.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_vviewattributes_mi.h>
#include<vsip_vviewattributes_vi.h>

void (vsip_cmgather_d)(
  const vsip_cmview_d *a,
  const vsip_vview_mi *x,
  const vsip_cvview_d *r) {

  { 
    vsip_length n = x->length;
    vsip_stride ast_col = a->col_stride * a->block->cstride,
                ast_row = a->row_stride * a->block->cstride,
                rst = r->stride * r->block->cstride,
                xst = x->stride * 2; /* stride of matrix index row or col value */
    vsip_scalar_d *ap_r = (a->block->R->array) + a->offset * a->block->cstride,
                  *rp_r = (r->block->R->array) + r->offset * r->block->cstride;
    vsip_scalar_d *ap_i = (a->block->I->array) + a->offset * a->block->cstride,
                  *rp_i = (r->block->I->array) + r->offset * r->block->cstride;
    vsip_scalar_vi *xp_row = (x->block->array) + x->offset; /* row value */
    vsip_scalar_vi *xp_col = xp_row + 1;                      /* col value */
    vsip_index index;
    /*end define*/
    while(n-- > 0){
    index = (*xp_row * ast_col + *xp_col * ast_row);
    *rp_r = *(ap_r + index);
    *rp_i = *(ap_i + index);
     rp_r += rst; rp_i += rst;
     xp_row += xst; xp_col += xst;
    }
  }
  return;
}
