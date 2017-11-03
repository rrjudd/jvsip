/* Created RJudd February 7, 2000*/
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
/* $Id: vsip_cmmeanval_f.c,v 2.0 2003/02/22 15:18:43 judd Exp $ */

#include"vsip.h"
#include"vsip_cmviewattributes_f.h"

vsip_cscalar_f (vsip_cmmeanval_f)(
  const vsip_cmview_f *a) {
  vsip_cscalar_f retval = vsip_cmplx_f(0.,0.);
  vsip_scalar_f num = (vsip_scalar_f) (a->row_length * a->col_length);
  { 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn;
  
    vsip_scalar_f *ap_r = (a->block->R->array) + a->offset * a->block->cstride;
    vsip_scalar_f *ap_i = (a->block->I->array) + a->offset * a->block->cstride;
    vsip_scalar_f *ap0_r = ap_r;
    vsip_scalar_f *ap0_i = ap_i;
    /* pick direction dependent on output */
    if(a->row_stride < a->col_stride){
           n_mj = a->row_length; n_mn = a->col_length;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           ast_mj *= a->block->cstride; ast_mn *= a->block->cstride;
    } else {
           n_mn = a->row_length; n_mj = a->col_length;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           ast_mn *= a->block->cstride; ast_mj *= a->block->cstride;
    }
    /*end define*/
    while(n_mn-- > 0){
       vsip_length n = n_mj;
       while(n-- >0){
           retval.r += *ap_r;
           retval.i += *ap_i;
           ap_r += ast_mj;
           ap_i += ast_mj;
        }
        ap0_r += ast_mn;
        ap0_i += ast_mn;
        ap_r = ap0_r;
        ap_i = ap0_i;
    }
    retval.r /= num;
    retval.i /= num;
  }
  return retval;
}
