/* Created RJudd March 7, 2000*/
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
/* $Id: VI_cmfill_f.h,v 2.1 2006/04/09 21:08:38 judd Exp $ */
#ifndef VI_CMFILL_F_H
#define VI_CMFILL_F_H 1

#include<vsip.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_cmviewattributes_f.h>

static
void 
VI_cmfill_f(
  vsip_cscalar_f alpha,
  const vsip_cmview_f *r) {
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride rst_mj, rst_mn;
    vsip_scalar_f *rp_r = (r->block->R->array) + r->offset * r->block->cstride;
    vsip_scalar_f *rp_i = (r->block->I->array) + r->offset * r->block->cstride;
    vsip_scalar_f *rp0_r = rp_r;
    vsip_scalar_f *rp0_i = rp_i;
    /* pick direction dependent on output */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           rst_mj *= r->block->cstride; rst_mn *= r->block->cstride;
    } else {
            n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           rst_mn *= r->block->cstride; rst_mj *= r->block->cstride;
    }
    /*end define*/
    while(n_mn-- > 0){
       vsip_length n = n_mj;
       while(n-- >0){
         *rp_r = alpha.r;
         *rp_i = alpha.i;
          rp_r += rst_mj;
          rp_i += rst_mj;
       }
       rp0_r += rst_mn; rp_r = rp0_r;
       rp0_i += rst_mn; rp_i = rp0_i;
    }
  return;
}

#endif
