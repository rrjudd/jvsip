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
/* $Id: vsip_cmkron_f.c,v 2.1 2006/06/08 22:19:26 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_cmviewattributes_f.h>

static
void
VI_csmmul_f(
  vsip_cscalar_f a,
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
    vsip_scalar_f temp;
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
    /* end define */
    while(n_mn-- > 0){
       vsip_length n = n_mj;
       while(n-- >0){
          temp =  a.r * *bp_r - a.i * *bp_i;
          *rp_i = a.r * *bp_i + a.i * *bp_r;
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
  return;
}

static
vsip_cscalar_f 
VI_cmget_f(
  const vsip_cmview_f *v, 
  vsip_index row, 
  vsip_index col) {
   vsip_stride str = v->block->cstride * (
                     v->offset + row * v->col_stride + col * v->row_stride);
   vsip_cscalar_f retval;
   retval.r = *(v->block->R->array + str); 
   retval.i = *(v->block->I->array + str); 
   return retval;
}

static
vsip_cscalar_f 
VI_cmul_f(
  vsip_cscalar_f x, 
  vsip_cscalar_f y) {
  vsip_cscalar_f tmp;
    tmp.r = x.r * y.r - x.i * y.i;
    tmp.i = x.r * y.i + x.i * y.r;
  return tmp;
}


void vsip_cmkron_f(
   vsip_cscalar_f alpha,
   const vsip_cmview_f *x,
   const vsip_cmview_f *y,
   const vsip_cmview_f *c)
{
    vsip_cmview_f C = *c;
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
         VI_csmmul_f(VI_cmul_f(VI_cmget_f(x,i,j) , alpha),y,&C);
       }
    }
    return;
}
