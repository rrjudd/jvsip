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
/* $Id: vsip_minterp_linear_d.c,v 2.1 2008/09/14 20:48:40 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_d.h"
#include"vsip_mviewattributes_d.h"

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

#define F1(x0,x1,y0,y1,x,y) {y = y0 + (y1-y0)/(x1-x0) * (x - x0);}

#define VINTERP_LINEAR(_x, _y, _xf, _yf) { \
   vsip_length N0 = _x->length; vsip_length N  = _xf->length; vsip_index i=0,j=0; \
   vsip_scalar_d sx1,sx2,sy1,sy2,sx; \
   vsip_stride _xst = _x->stride * _x->block->rstride, _yst = _y->stride * _x->block->rstride,\
               _xfst = _xf->stride * _xf->block->rstride, _yfst = _yf->stride * _yf->block->rstride;\
   vsip_scalar_d *_xptr = (_x->block->array) + _x->offset * _x->block->rstride, \
                 *_yptr = (_y->block->array) + _y->offset * _y->block->rstride,\
                 *_xfptr = (_xf->block->array) + _xf->offset * _xf->block->rstride, \
                 *_yfptr = (_yf->block->array) + _yf->offset * _yf->block->rstride; \
   while((j < N) && (i < N0-1)){\
      sx1 = _xptr[i * _xst];\
      sx2 = _xptr[(i + 1) * _xst];\
      sy1 = _yptr[i * _yst];\
      sy2 = _yptr[(i + 1) * _yst];;\
      sx  = _xfptr[j * _xfst];\
      if(sx < sx2) {\
         vsip_scalar_d a;\
         F1(sx1,sx2,sy1,sy2,sx,a);\
         _yfptr[j * _yfst] = a;\
         j++;\
      } else i++;\
   }\
}

void vsip_minterp_linear_d(
      const vsip_vview_d *ax,
      const vsip_mview_d *ay,
      vsip_major major,
      const vsip_vview_d *bx,
      const vsip_mview_d *by){
   vsip_index i;
   vsip_vview_d *y,yy;
   vsip_vview_d *yf,yyf;
   y = &yy; 
   yf = &yyf;
   if(major == VSIP_ROW) {
      vsip_length M = ay->col_length;
      for(i=0; i<M; i++){
         GETROW(ay,i,y);
         GETROW(by,i,yf);
         VINTERP_LINEAR(ax,y,bx,yf)
      }
   } else { /* must be by column */
      vsip_length M = ay->row_length;
      for(i=0; i<M; i++){
         GETCOL(ay,i,y);
         GETCOL(by,i,yf);
         VINTERP_LINEAR(ax,y,bx,yf)
      }
   }
   return;
}
