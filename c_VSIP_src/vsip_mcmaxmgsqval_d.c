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
/* $Id: vsip_mcmaxmgsqval_d.c,v 2.0 2003/02/22 15:18:54 judd Exp $ */

#include<vsip.h>
#include<vsip_cmviewattributes_d.h>

vsip_scalar_d (vsip_mcmaxmgsqval_d)(
  const vsip_cmview_d *a,
  vsip_scalar_mi *index) {
  vsip_scalar_d retval = 0;
  { 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn;
  
    vsip_scalar_d *ap_r = (a->block->R->array) + a->offset * a->block->cstride;
    vsip_scalar_d *ap_i = (a->block->I->array) + a->offset * a->block->cstride;
    vsip_scalar_d *ap0_r = ap_r;
    vsip_scalar_d *ap0_i = ap_i;
    vsip_scalar_d mag = 0;
    vsip_index major_i = 0,
               minor_i = 0;
    vsip_length n0_mn, n0_mj;
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
    n0_mn = n_mn - 1;
    n0_mj = n_mj - 1;
    retval = *ap_r * *ap_r + *ap_i * *ap_i;
    /*end define*/
    while(n_mn-- > 0){
       vsip_length n = n_mj;
       while(n-- >0){
           mag = *ap_r * *ap_r + *ap_i * *ap_i;
           if(retval < mag){
                 retval = mag;
                 major_i = n0_mj - n;
                 minor_i = n0_mn - n_mn;
           }
           ap_r += ast_mj;
           ap_i += ast_mj;
        }
        ap0_r += ast_mn;
        ap0_i += ast_mn;
        ap_r = ap0_r;
        ap_i = ap0_i;
    }
    if(index != NULL){
       if(a->row_stride < a->col_stride){
           index->r = minor_i;
           index->c = major_i;
       } else {
           index->r = major_i;
           index->c = minor_i;
       }
    }
  }
  return retval;
}
