/* Created RJudd January 9, 2000*/
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
#include"vsip.h"
#include"vsip_mviewattributes_d.h"

void (vsip_mhypot_d)(
  const vsip_mview_d *a,
  const vsip_mview_d *b,
  const vsip_mview_d *r) {

  { 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn,
                bst_mj, bst_mn,
                rst_mj, rst_mn;
    vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,
                  *bp = (b->block->array) + b->offset * b->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_d *ap0 = ap,
                  *bp0 = bp,
                  *rp0 = rp;
    /* pick direction dependent on output */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           bst_mj = b->row_stride; bst_mn = b->col_stride;
           rst_mj *= r->block->rstride; rst_mn *= r->block->rstride;
           ast_mj *= a->block->rstride; ast_mn *= a->block->rstride;
           bst_mj *= b->block->rstride; bst_mn *= b->block->rstride;
    } else {
            n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           bst_mn = b->row_stride; bst_mj = b->col_stride;
           rst_mn *= r->block->rstride; rst_mj *= r->block->rstride;
           ast_mn *= a->block->rstride; ast_mj *= a->block->rstride;
           bst_mn *= b->block->rstride; bst_mj *= b->block->rstride;
    }
    /*end define*/
    while(n_mn-- > 0){
       vsip_length n = n_mj;
       while(n-- >0){
          vsip_scalar_d a=fabs(*ap), b=fabs(*bp);
          if (a == 0.0)
             *rp = b;
          else if (b == 0.0)
             *rp = a;
          else if (b < a)
             *rp = a * (vsip_scalar_d)sqrt(1.0 + (b/a) * (b/a));
          else
             *rp = b * (vsip_scalar_d)sqrt(1.0 + (a/b) * (a/b));
         ap += ast_mj; bp += bst_mj; rp += rst_mj;
       }
       ap0 += ast_mn; bp0 += bst_mn; rp0 += rst_mn;
       ap = ap0; bp = bp0; rp = rp0;
    }
  }
  return;
}
