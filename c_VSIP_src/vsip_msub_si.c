/* Created RJudd */
/* SPAWARSYSCEN  */
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
/* $Id: vsip_msub_si.c,v 2.1 2004/04/03 16:03:08 judd Exp $ */

#include"vsip.h"
#include"vsip_mviewattributes_si.h"

void (vsip_msub_si)(
  const vsip_mview_si *a,
  const vsip_mview_si *b,
  const vsip_mview_si *r) {

  { 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn,
                bst_mj, bst_mn,
                rst_mj, rst_mn;
    vsip_scalar_si *ap = (a->block->array) + a->offset,
                  *bp = (b->block->array) + b->offset,
                  *rp = (r->block->array) + r->offset;
    vsip_scalar_si *ap0 = ap,
                  *bp0 = bp,
                  *rp0 = rp;
    /* pick direction dependent on output */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           bst_mj = b->row_stride; bst_mn = b->col_stride;
    } else {
            n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           bst_mn = b->row_stride; bst_mj = b->col_stride;
    }
    /*end define*/
    while(n_mn-- > 0){
       vsip_length n = n_mj;
       while(n-- >0){
         *rp = *ap - *bp ;
         ap += ast_mj; bp += bst_mj; rp += rst_mj;
       }
       ap0 += ast_mn; bp0 += bst_mn; rp0 += rst_mn;
       ap = ap0; bp = bp0; rp = rp0;
    }
  }
  return;
}
