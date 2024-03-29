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
/* $Id: vsip_cmadd_d.c,v 2.1 2004/08/02 16:24:00 judd Exp $ */

#include"vsip.h"
#include"vsip_mviewattributes_d.h"
#include"vsip_cmviewattributes_d.h"

void (vsip_cmadd_d)(
  const vsip_cmview_d *a,
  const vsip_cmview_d *b,
  const vsip_cmview_d *r) {
   if((a->block->cstride == 2)&&(b->block->cstride == 2)&&(r->block->cstride == 2)){
       vsip_length n_mj, /* major length */
                   n_mn; /* minor length */
       vsip_stride ast_mj, ast_mn,
                   bst_mj, bst_mn,
                   rst_mj, rst_mn;
       vsip_scalar_d *ap_r = (a->block->R->array) + a->offset * 2,
                     *bp_r = (b->block->R->array) + b->offset * 2,
                     *rp_r = (r->block->R->array) + r->offset * 2;
       vsip_scalar_d *ap0_r = ap_r,
                     *bp0_r = bp_r,
                     *rp0_r = rp_r;
       /* pick direction dependent on output */
       if(r->row_stride < r->col_stride){
              n_mj = r->row_length; n_mn = r->col_length;
              rst_mj = r->row_stride; rst_mn = r->col_stride;
              ast_mj = a->row_stride; ast_mn = a->col_stride;
              bst_mj = b->row_stride; bst_mn = b->col_stride;
              rst_mj *= 2; rst_mn *= 2;
              ast_mj *= 2; ast_mn *= 2;
              bst_mj *= 2; bst_mn *= 2;
       } else {
              n_mn = r->row_length; n_mj = r->col_length;
              rst_mn = r->row_stride; rst_mj = r->col_stride;
              ast_mn = a->row_stride; ast_mj = a->col_stride;
              bst_mn = b->row_stride; bst_mj = b->col_stride;
              rst_mn *= 2; rst_mj *= 2;
              ast_mn *= 2; ast_mj *= 2;
              bst_mn *= 2; bst_mj *= 2;
       }
       /*end define*/
       if((rst_mj == 2) && (ast_mj == 2) && (bst_mj == 2)){
          while(n_mn-- > 0){
             vsip_length n = 2 * n_mj;
             while(n-- >0){
               *rp_r = *ap_r + *bp_r;
               rp_r++; ap_r++; bp_r++;
             }
             ap0_r += ast_mn; bp0_r += bst_mn; rp0_r += rst_mn;
             ap_r = ap0_r; bp_r = bp0_r; rp_r = rp0_r;
          }

       }else if(rst_mj == 2){
          while(n_mn-- > 0){
             vsip_length n = n_mj;
             while(n-- >0){
               vsip_scalar_d ar = *ap_r, ai = *(ap_r+1);
               vsip_scalar_d br = *bp_r, bi = *(bp_r+1);
               *rp_r = ar + br ;
               rp_r++; 
               *rp_r = ai + bi ;
               rp_r++;
               ap_r += ast_mj; bp_r += bst_mj;
             }
             ap0_r += ast_mn; bp0_r += bst_mn; rp0_r += rst_mn;
             ap_r = ap0_r; bp_r = bp0_r; rp_r = rp0_r;
          }
       } else {
          while(n_mn-- > 0){
             vsip_length n = n_mj;
             while(n-- >0){
               vsip_scalar_d ar = *ap_r, ai = *(ap_r+1);
               vsip_scalar_d br = *bp_r, bi = *(bp_r+1);
               *rp_r = ar + br ;
               *(rp_r + 1) = ai + bi ;
               ap_r += ast_mj; bp_r += bst_mj; rp_r += rst_mj;
             }
             ap0_r += ast_mn; bp0_r += bst_mn; rp0_r += rst_mn;
             ap_r = ap0_r; bp_r = bp0_r; rp_r = rp0_r;
          }
       }
     } else { 
       vsip_length n_mj, /* major length */
                   n_mn; /* minor length */
       vsip_stride ast_mj, ast_mn,
                   bst_mj, bst_mn,
                   rst_mj, rst_mn;
       vsip_scalar_d *ap_r = (a->block->R->array) + a->offset * a->block->cstride,
                     *bp_r = (b->block->R->array) + b->offset * b->block->cstride,
                     *rp_r = (r->block->R->array) + r->offset * r->block->cstride;
       vsip_scalar_d *ap_i = (a->block->I->array) + a->offset * a->block->cstride,
                     *bp_i = (b->block->I->array) + b->offset * b->block->cstride,
                     *rp_i = (r->block->I->array) + r->offset * r->block->cstride;
       vsip_scalar_d *ap0_r = ap_r,
                     *bp0_r = bp_r,
                     *rp0_r = rp_r;
       vsip_scalar_d *ap0_i = ap_i,
                     *bp0_i = bp_i,
                     *rp0_i = rp_i;
       /* pick direction dependent on output */
       if(r->row_stride < r->col_stride){
              n_mj = r->row_length; n_mn = r->col_length;
              rst_mj = r->row_stride; rst_mn = r->col_stride;
              ast_mj = a->row_stride; ast_mn = a->col_stride;
              bst_mj = b->row_stride; bst_mn = b->col_stride;
              rst_mj *= r->block->cstride; rst_mn *= r->block->cstride;
              ast_mj *= a->block->cstride; ast_mn *= a->block->cstride;
              bst_mj *= b->block->cstride; bst_mn *= b->block->cstride;
       } else {
               n_mn = r->row_length; n_mj = r->col_length;
              rst_mn = r->row_stride; rst_mj = r->col_stride;
              ast_mn = a->row_stride; ast_mj = a->col_stride;
              bst_mn = b->row_stride; bst_mj = b->col_stride;
              rst_mn *= r->block->cstride; rst_mj *= r->block->cstride;
              ast_mn *= a->block->cstride; ast_mj *= a->block->cstride;
              bst_mn *= b->block->cstride; bst_mj *= b->block->cstride;
       }
       /*end define*/
       while(n_mn-- > 0){
          vsip_length n = n_mj;
          while(n-- >0){
            *rp_r = *ap_r + *bp_r ;
            *rp_i = *ap_i + *bp_i ;
            ap_r += ast_mj; bp_r += bst_mj; rp_r += rst_mj;
            ap_i += ast_mj; bp_i += bst_mj; rp_i += rst_mj;
          }
          ap0_r += ast_mn; bp0_r += bst_mn; rp0_r += rst_mn;
          ap_r = ap0_r; bp_r = bp0_r; rp_r = rp0_r;
          ap0_i += ast_mn; bp0_i += bst_mn; rp0_i += rst_mn;
          ap_i = ap0_i; bp_i = bp0_i; rp_i = rp0_i;
       }
     }
  return;
}
