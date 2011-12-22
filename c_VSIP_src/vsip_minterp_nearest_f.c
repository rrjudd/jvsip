/* Created RJudd */
/**********************************************************************
// TASP VSIPL Documentation and Code includes no warranty,            /
// express or implied, including the warranties of merchantability    /
// and fitness for a particular purpose. No person or organization    /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
/* $Id: vsip_minterp_nearest_f.c,v 2.1 2008/08/17 18:01:49 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_mviewattributes_f.h>

#define GETROW(_a,_i,_row) {\
    _row->block  = _a->block; \
    _row->stride = _a->row_stride; \
    _row->length = _a->row_length; \
    _row->offset = _a->offset + _i * _a->col_stride;\
}
#define GETCOL(_a,_i,_col) {\
    _col->block  = _a->block; \
    _col->stride = _a->col_stride; \
    _col->length = _a->col_length; \
    _col->offset = _a->offset + _i * _a->row_stride;\
}

#define F2(_x1,_x2,_y1,_y2,_x,_y) {   \
   vsip_scalar_f dif1 = _x - _x1;\
   vsip_scalar_f dif2 = _x2 - _x;\
   if(dif1 > dif2) \
      _y = _y2;\
   else \
      _y = _y1; \
 }

#define VINTERP_NEAREST( _x0, _y0, _x, _y) {\
   vsip_length N0 = _x0->length; \
   vsip_length N = _x->length; \
   vsip_stride x0_str = _x0->stride * _x0->block->rstride, \
               y0_str = _y0->stride * _y0->block->rstride, \
               x_str = _x->stride * _x->block->rstride, \
               y_str = _y->stride * _y->block->rstride; \
   vsip_scalar_f *x0_ptr = _x0->block->array + _x0->offset * _x0->block->rstride, \
                 *y0_ptr = _y0->block->array + _y0->offset * _y0->block->rstride, \
                 *x_ptr  = _x->block->array  + _x->offset  * _x->block->rstride, \
                 *y_ptr  = _y->block->array  + _y->offset  * _y->block->rstride; \
   vsip_index i=0,j=0; \
   vsip_scalar_f sx1,sx2,sy1,sy2,sx; \
   while((j < N) && (i < N0-1)){ \
      sx1 = x0_ptr[i * x0_str]; \
      sx2 = x0_ptr[(i+1)*x0_str]; \
      sy1 = y0_ptr[i * y0_str]; \
      sy2 = y0_ptr[(i+1) * y0_str]; \
      sx = x_ptr[j * x_str]; \
      if(sx < sx2) { \
         vsip_scalar_f a; \
         F2(sx1,sx2,sy1,sy2,sx,a); \
         y_ptr[j * y_str] = a; \
         j++; \
      } else i++; \
   } \
}


void vsip_minterp_nearest_f(
      const vsip_vview_f *ax,
      const vsip_mview_f *ay,
      vsip_major major,
      const vsip_vview_f *bx,
      const vsip_mview_f *by){
   vsip_index i;
   vsip_vview_f *y,yy;
   vsip_vview_f *yf,yyf;
   y = &yy; 
   yf = &yyf;
   if(major == VSIP_ROW) {
      vsip_length M = ay->col_length;
      for(i=0; i<M; i++){
         GETROW(ay,i,y);
         GETROW(by,i,yf);
         VINTERP_NEAREST(ax,y,bx,yf)
      }
   } else { /* must be by column */
      vsip_length M = ay->row_length;
      for(i=0; i<M; i++){
         GETCOL(ay,i,y);
         GETCOL(by,i,yf);
         VINTERP_NEAREST(ax,y,bx,yf)
      }
   }
   return;
}
