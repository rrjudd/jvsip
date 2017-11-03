/* Created RJudd November 22, 2000 */
/* SPAWARSYSCEN D857               */
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
/* $Id: vsip_mkron_d.c,v 2.1 2006/06/08 22:19:26 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_d.h"
#include"vsip_mviewattributes_d.h"

static
void
VI_smmul_d(
  vsip_scalar_d a,
  const vsip_mview_d *b,
  const vsip_mview_d *r) 
{
  { 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride bst_mj, bst_mn,
                rst_mj, rst_mn;
    vsip_scalar_d *bp = (b->block->array) + b->offset * b->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_d *bp0 = bp,
                  *rp0 = rp;
    /* pick direction dependent on output */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
           bst_mj = b->row_stride; bst_mn = b->col_stride;
           rst_mj *= r->block->rstride; rst_mn *= r->block->rstride;
           bst_mj *= b->block->rstride; bst_mn *= b->block->rstride;
    } else {
           n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
           bst_mn = b->row_stride; bst_mj = b->col_stride;
           rst_mn *= r->block->rstride; rst_mj *= r->block->rstride;
           bst_mn *= b->block->rstride; bst_mj *= b->block->rstride;
    }
    while(n_mn-- > 0){
       vsip_length n = n_mj;
       while(n-- >0){
         *rp = a * *bp ;
          bp += bst_mj; rp += rst_mj;
       }
       bp0 += bst_mn; rp0 += rst_mn;
       bp = bp0; rp = rp0;
    }
  }
  return;
}

static
vsip_scalar_d
VI_mget_d(
  const vsip_mview_d *v,
  vsip_index row,
  vsip_index col){
   return (*(v->block->array +
            v->block->rstride *
            (v->offset + row * v->col_stride + col * v->row_stride)));
}

void vsip_mkron_d(
   vsip_scalar_d alpha,
   const vsip_mview_d *x,
   const vsip_mview_d *y,
   const vsip_mview_d *c)
{
    vsip_mview_d C = *c;
    vsip_length y_row_length = y->row_length,
                x_row_length = x->row_length,
                y_col_length = y->col_length,
                x_col_length = x->col_length;
    vsip_offset c_offset = c->offset;
   /* c row is x_row * y_col_length, c col is x_col * y_row_length */
    vsip_stride c_str_c = y_col_length * c->col_stride; 
    vsip_stride c_str_r = y_row_length * c->row_stride; 
    vsip_length i,j;
    C.row_length = y_row_length;
    C.col_length = y_col_length;
    
    for(i=0; i< x_col_length; i++){
       for(j=0; j< x_row_length; j++){
         C.offset = c_offset + i * c_str_c + j * c_str_r;
         VI_smmul_d(VI_mget_d(x,i,j) * alpha,y,&C);
       }
    }
    return;
}
