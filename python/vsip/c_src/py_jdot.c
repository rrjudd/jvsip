#ifndef _py_jdot_cpy
#define _py_jdot_cpy 1
#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_cvviewattributes_d.h>


vsip_cscalar_f py_rcvjdot_f( const vsip_vview_f* a, const vsip_cvview_f* b) {
      vsip_length n = a->length;
      vsip_stride rast = a->block->rstride;
      vsip_stride cbst = b->block->cstride;
      vsip_scalar_f *apr = (vsip_scalar_f*) ((a->block->array) + rast * a->offset),
                    *bpr = (vsip_scalar_f*) ((b->block->R->array) + cbst * b->offset);
      vsip_scalar_f *bpi = (vsip_scalar_f*) ((b->block->I->array) + cbst * b->offset);
      vsip_stride ast = rast * a->stride, bst = cbst * b->stride;
    vsip_cscalar_f r;
    r.r = 0; r.i = 0;
    while(n-- > 0){
        r.r += (*apr * *bpr);
        r.i -= (*apr * *bpi);
        apr += ast; 
        bpr += bst; bpi += bst;
    }
    return r;
}

vsip_cscalar_f py_crvjdot_f( const vsip_cvview_f* a, const vsip_vview_f* b) {
   vsip_length n = a->length;
   vsip_stride cast = a->block->cstride;
   vsip_stride rbst = b->block->rstride;
   vsip_scalar_f *apr = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset),
                 *bpr = (vsip_scalar_f*) ((b->block->array) + rbst * b->offset);
   vsip_scalar_f *api = (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset);
   vsip_stride ast = cast * a->stride, bst = rbst * b->stride;
  vsip_cscalar_f r;
  r.r = 0; r.i = 0;
  while(n-- > 0){
      r.r += (*apr * *bpr); 
      r.i += (*api * *bpr); 
      apr += ast; api += ast;
      bpr += bst;
  }
  return r;
}

vsip_cscalar_d py_rcvjdot_d( const vsip_vview_d* a, const vsip_cvview_d* b) {
      vsip_length n = a->length;
      vsip_stride rast = a->block->rstride;
      vsip_stride cbst = b->block->cstride;
      vsip_scalar_d *apr = (vsip_scalar_d*) ((a->block->array) + rast * a->offset),
                    *bpr = (vsip_scalar_d*) ((b->block->R->array) + cbst * b->offset);
      vsip_scalar_d *bpi = (vsip_scalar_d*) ((b->block->I->array) + cbst * b->offset);
      vsip_stride ast = rast * a->stride, bst = cbst * b->stride;
    vsip_cscalar_d r;
    r.r = 0; r.i = 0;
    while(n-- > 0){
        r.r += (*apr * *bpr);
        r.i -= (*apr * *bpi);
        apr += ast;
        bpr += bst; bpi += bst;
    }
    return r;
}

vsip_cscalar_d py_crvjdot_d( const vsip_cvview_d* a, const vsip_vview_d* b) {
   vsip_length n = a->length;
   vsip_stride cast = a->block->cstride;
   vsip_stride rbst = b->block->rstride;
   vsip_scalar_d *apr = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset),
                 *bpr = (vsip_scalar_d*) ((b->block->array) + rbst * b->offset);
   vsip_scalar_d *api = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset);
   vsip_stride ast = cast * a->stride, bst = rbst * b->stride;
  vsip_cscalar_d r;
  r.r = 0; r.i = 0;
  while(n-- > 0){
      r.r += (*apr * *bpr);
      r.i += (*api * *bpr);
      apr += ast; api += ast;
      bpr += bst;
  }
  return r;
}

#endif
