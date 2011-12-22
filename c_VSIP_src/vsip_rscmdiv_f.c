/* Created RJudd February 16, 2000*/
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
/* $Id: vsip_rscmdiv_f.c,v 2.0 2003/02/22 15:19:03 judd Exp $ */

#include<vsip.h>
#include<vsip_cmviewattributes_f.h>

void (vsip_rscmdiv_f)(
  vsip_scalar_f alpha,
  const vsip_cmview_f *b,
  const vsip_cmview_f *r) {

 { 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride bst_mj, bst_mn,
                rst_mj, rst_mn;
    vsip_scalar_f *bp_r = (b->block->R->array) + b->offset * b->block->cstride,
                  *rp_r = (r->block->R->array) + r->offset * r->block->cstride;
    vsip_scalar_f *bp_i = (b->block->I->array) + b->offset * b->block->cstride,
                  *rp_i = (r->block->I->array) + r->offset * r->block->cstride;
    vsip_scalar_f *bp0_r = bp_r,
                  *rp0_r = rp_r;
    vsip_scalar_f *bp0_i = bp_i,
                  *rp0_i = rp_i;
    vsip_scalar_f temp,magsq;
    /* pick direction dependent on output */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           bst_mj = b->row_stride; bst_mn = b->col_stride;
           rst_mj *= r->block->cstride; rst_mn *= r->block->cstride;
           bst_mj *= b->block->cstride; bst_mn *= b->block->cstride;
    } else {
            n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           bst_mn = b->row_stride; bst_mj = b->col_stride;
           rst_mn *= r->block->cstride; rst_mj *= r->block->cstride;
           bst_mn *= b->block->cstride; bst_mj *= b->block->cstride;
    }
    /*end define*/
    if(b == r){
       while(n_mn-- > 0){ /* in place */
          vsip_length n = n_mj;
          while(n-- >0){
            magsq = (*rp_r * *rp_r + *rp_i * *rp_i);
            temp  = (alpha * *rp_r) / magsq;
            *rp_i = (- alpha * *rp_i) / magsq;
            *rp_r = temp;
             rp_r += rst_mj; rp_i += rst_mj;
          }
          rp0_r += rst_mn; rp_r = rp0_r;
          rp0_i += rst_mn; rp_i = rp0_i;
      }
    } else {             /* not in place */
       while(n_mn-- > 0){
          vsip_length n = n_mj;
          while(n-- >0){
            magsq = (*bp_r * *bp_r + *bp_i * *bp_i);
            temp  = (alpha * *bp_r) / magsq;
            *rp_i = (- alpha * *bp_i) / magsq;
            *rp_r = temp;
            bp_r += bst_mj; rp_r += rst_mj;
            bp_i += bst_mj; rp_i += rst_mj;
          }
          bp0_r += bst_mn; rp0_r += rst_mn;
          bp_r = bp0_r; rp_r = rp0_r;
          bp0_i += bst_mn; rp0_i += rst_mn;
          bp_i = bp0_i; rp_i = rp0_i;
      }
    }
  }
  return;
}
