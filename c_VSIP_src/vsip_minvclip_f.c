/* Created RJudd January 26, 2000*/
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
/* $Id: vsip_minvclip_f.c,v 2.0 2003/02/22 15:18:57 judd Exp $ */

#include"vsip.h"
#include"vsip_mviewattributes_f.h"

void (vsip_minvclip_f)(
  const vsip_mview_f *a,
  vsip_scalar_f t1,
  vsip_scalar_f t2,
  vsip_scalar_f t3,
  vsip_scalar_f c1,
  vsip_scalar_f c2,
  const vsip_mview_f *r) {

  { 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn,
                rst_mj, rst_mn;
    vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_f *ap0 = ap,
                  *rp0 = rp;
    /* pick direction dependent on output */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           rst_mj *= r->block->rstride; rst_mn *= r->block->rstride;
           ast_mj *= a->block->rstride; ast_mn *= a->block->rstride;
    } else {
           n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           rst_mn *= r->block->rstride; rst_mj *= r->block->rstride;
           ast_mn *= a->block->rstride; ast_mj *= a->block->rstride;
    }
    /*end define*/
    if(ap == rp){ /* inplace */
       while(n_mn-- > 0){
          vsip_length n = n_mj;
          while(n-- >0){
            *rp  = (*rp < t1) ? *rp : ((*rp < t2) ? c1 : ((*rp <= t3) ? c2 : *rp));
             rp += rst_mj;
          }
          rp0 += rst_mn;
          rp = rp0;
       }
    } else {
       while(n_mn-- > 0){
          vsip_length n = n_mj;
          while(n-- >0){
            *rp  = (*ap < t1) ? *ap : ((*ap < t2) ? c1 : ((*ap <= t3) ? c2 : *ap));
             ap += ast_mj;  rp += rst_mj;
          }
          ap0 += ast_mn; rp0 += rst_mn;
          ap = ap0; rp = rp0;
    }
   }
  }
  return;
}
