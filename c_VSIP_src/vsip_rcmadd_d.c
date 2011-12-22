/* Created RJudd September 25, 1999*/
/* SPAWARSYSCEN D881 */
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
/* $Id: vsip_rcmadd_d.c,v 2.0 2003/02/22 15:19:02 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_cmviewattributes_d.h>

void (vsip_rcmadd_d)(
  const vsip_mview_d *a,
  const vsip_cmview_d *b,
  const vsip_cmview_d *r) {

  { 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn,
                bst_mj, bst_mn,
                rst_mj, rst_mn;
    vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,
                  *bp_r = (b->block->R->array) + b->offset * b->block->cstride,
                  *rp_r = (r->block->R->array) + r->offset * r->block->cstride;
    vsip_scalar_d *bp_i = (b->block->I->array) + b->offset * b->block->cstride,
                  *rp_i = (r->block->I->array) + r->offset * r->block->cstride;
    vsip_scalar_d *ap0 = ap,
                  *bp0_r = bp_r,
                  *rp0_r = rp_r;
    vsip_scalar_d *bp0_i = bp_i,
                  *rp0_i = rp_i;
    /* pick direction dependent on output */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           bst_mj = b->row_stride; bst_mn = b->col_stride;
           rst_mj *= r->block->cstride; rst_mn *= r->block->cstride;
           ast_mj *= a->block->rstride; ast_mn *= a->block->rstride;
           bst_mj *= b->block->cstride; bst_mn *= b->block->cstride;
    } else {
            n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           bst_mn = b->row_stride; bst_mj = b->col_stride;
           rst_mn *= r->block->cstride; rst_mj *= r->block->cstride;
           ast_mn *= a->block->rstride; ast_mj *= a->block->rstride;
           bst_mn *= b->block->cstride; bst_mj *= b->block->cstride;
    }
    /*end define*/
    if(b == r){         /* inplace */
       while(n_mn-- > 0){
          vsip_length n = n_mj;
          while(n-- >0){
            *rp_r += *ap;
            ap += ast_mj; rp_r += rst_mj;
          }
          ap0 += ast_mn; ap = ap0;    
          rp0_r += rst_mn; rp_r = rp0_r;
       }
    } else {            /* out of place */
       while(n_mn-- > 0){
          vsip_length n = n_mj;
          while(n-- >0){
            *rp_r = *ap + *bp_r ;
            *rp_i = *bp_i ;
            ap += ast_mj; bp_r += bst_mj; rp_r += rst_mj;
                            bp_i += bst_mj; rp_i += rst_mj;
          }
          ap0 += ast_mn; bp0_r += bst_mn; rp0_r += rst_mn;
          ap = ap0;    bp_r = bp0_r;    rp_r = rp0_r;
                           bp0_i += bst_mn; rp0_i += rst_mn;
                           bp_i = bp0_i;    rp_i = rp0_i;
       }
    }
  }
  return;
}
