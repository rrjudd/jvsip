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
/* $Id: vsip_mclip_i.c,v 2.1 2004/04/03 16:03:08 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_i.h>

void (vsip_mclip_i)(
  const vsip_mview_i *a,
  vsip_scalar_i t1,
  vsip_scalar_i t2,
  vsip_scalar_i c1,
  vsip_scalar_i c2,
  const vsip_mview_i *r) {
  {
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn,
                rst_mj, rst_mn;
    vsip_scalar_i *ap = (a->block->array) + a->offset,
                  *rp = (r->block->array) + r->offset;
    vsip_scalar_i *ap0 = ap,
                  *rp0 = rp;
    /* pick direction dependent on output */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
    } else {
            n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
    }
    /*end define*/
    if(ap == rp){ /* inplace */
       while(n_mn-- > 0){
          vsip_length n = n_mj;
          while(n-- >0){
            *rp  = (*rp <= t1) ? c1 : ((*rp < t2) ? *rp : c2);
            rp += rst_mj;
          }
          rp0 += rst_mn;
          rp = rp0;
       }
    } else {
       while(n_mn-- > 0){
          vsip_length n = n_mj;
          while(n-- >0){
           *rp  = (*ap <= t1) ? c1 : ((*ap < t2) ? *ap : c2);
            ap += ast_mj;  rp += rst_mj;
          }
          ap0 += ast_mn; rp0 += rst_mn;
          ap = ap0; rp = rp0;
    }
   }
  }
  return;
}
