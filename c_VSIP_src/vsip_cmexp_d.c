/* Created RJudd February 1, 2000*/
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
/* $Id: vsip_cmexp_d.c,v 2.1 2003/04/22 02:19:57 judd Exp $ */

#include<vsip.h>
#include<vsip_cmviewattributes_d.h>
#include"vsip_scalars.h"

void (vsip_cmexp_d)(
  const vsip_cmview_d *a,
  const vsip_cmview_d *r) {

  { 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn,
                rst_mj, rst_mn;
    vsip_scalar_d *ap_r = (a->block->R->array) + a->offset * a->block->cstride,
                  *rp_r = (r->block->R->array) + r->offset * r->block->cstride;
    vsip_scalar_d *ap_i = (a->block->I->array) + a->offset * a->block->cstride,
                  *rp_i = (r->block->I->array) + r->offset * r->block->cstride;
    vsip_scalar_d *ap0_r = ap_r,
                  *rp0_r = rp_r;
    vsip_scalar_d *ap0_i = ap_i,
                  *rp0_i = rp_i;
    vsip_scalar_d mag = 0;
    /* pick direction dependent on output */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           rst_mj *= r->block->cstride; rst_mn *= r->block->cstride;
           ast_mj *= a->block->cstride; ast_mn *= a->block->cstride;
    } else {
           n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           rst_mn *= r->block->cstride; rst_mj *= r->block->cstride;
           ast_mn *= a->block->cstride; ast_mj *= a->block->cstride;
    }
    /*end define*/
    if(ap_i == rp_i){ /* inplace */
       while(n_mn-- > 0){
          vsip_length n = n_mj;
          while(n-- >0){
             mag = VSIP_EXP_D(*rp_r);
             *rp_r = mag * VSIP_COS_D(*rp_i);
             *rp_i = mag * VSIP_SIN_D(*rp_i);
             rp_r += rst_mj;
             rp_i += rst_mj;
          }
          rp0_r += rst_mn;
          rp0_i += rst_mn;
          rp_r = rp0_r;
          rp_i = rp0_i;
       }
    } else { /* out of place */
       while(n_mn-- > 0){
          vsip_length n = n_mj;
          while(n-- >0){
             mag = VSIP_EXP_D(*ap_r);
             *rp_r = mag * VSIP_COS_D(*ap_i);
             *rp_i = mag * VSIP_SIN_D(*ap_i);
             ap_r += ast_mj;  rp_r += rst_mj;
             ap_i += ast_mj;  rp_i += rst_mj;
          }
          ap0_r += ast_mn; rp0_r += rst_mn;
          ap0_i += ast_mn; rp0_i += rst_mn;
          ap_r = ap0_r; rp_r = rp0_r;
          ap_i = ap0_i; rp_i = rp0_i;
    }
   }
  }
  return;
}
