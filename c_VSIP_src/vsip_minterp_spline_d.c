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
/* $Id: vsip_minterp_spline_d.c,v 2.1 2008/09/14 20:48:40 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_splineattributes_d.h>

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
 
#define VINTERP_SPLINE( _t0, _y0, _spl, _xf0, _yf0) { \
   vsip_length N = _t0->length; \
   vsip_length M = _xf0->length; \
   vsip_stride t_st = _t0->stride * _t0->block->rstride, \
               y_st = _y0->stride * _y0->block->rstride, \
               xf_st = _xf0->stride * _xf0->block->rstride, \
               yf_st = _yf0->stride * _yf0->block->rstride; \
   vsip_index i; \
   vsip_stride j; \
   vsip_scalar_d *t = _t0->block->array + _t0->offset * _t0->block->rstride; \
   vsip_scalar_d *_y = _y0->block->array + _y0->offset * _y0->block->rstride; \
   vsip_scalar_d *xf = _xf0->block->array + _xf0->offset * _xf0->block->rstride; \
   vsip_scalar_d *_yf = _yf0->block->array + _yf0->offset * _yf0->block->rstride; \
   vsip_scalar_d *z = _spl->z, *h=_spl->h, *b = _spl->b, *u = _spl->u, *v = _spl->v; \
   for(i=0; i<N-1; i++){ \
      h[i] = t[(i+1) * t_st] - t[i * t_st]; \
      b[i] = (_y[(i+1) * y_st] - _y[i * y_st])/h[i]; \
   } \
   u[1] = 2.0 * (h[0] + h[1]); \
   v[1] = 6.0 * (b[1] - b[0]); \
   for(i=2; i<N-1; i++){ \
      u[i] = 2.0 * (h[i] + h[i-1]) - h[i-1] * h[i-1] / u[i-1];\
      v[i] = 6.0 * (b[i] - b[i-1]) - h[i-1] * v[i-1] / u[i-1];\
   } \
   z[N-1] = 0.0; \
   for(i=N-2; i>0; i--) \
      z[i] = (v[i] - h[i] * z[i+1])/u[i]; \
   z[0] = 0.0; \
   for(i=0; i<M; i++){ \
      register vsip_scalar_d yj,zj,zj1; \
      register vsip_scalar_d d,h,b,p,x; \
      x = xf[i * xf_st]; \
      j = N-2; \
      while((x < (d = t[j * t_st])) && (j >= 0)) j--; \
      yj = _y[j * y_st]; \
      zj=z[j]; zj1=z[j+1]; \
      d = x - d; \
      if(j < 0) j = 0; \
      if(d < 0) break; \
      h = t[(j+1) * t_st] - t[j * t_st];\
      b = (_y[(j+1) * y_st] - yj)/h - h * (zj1 + 2.0 * zj)/6.0;\
      p = ((0.5 * zj +d * (zj1 - zj)/(6.0 * h)) * d + b) * d;\
      _yf[i * yf_st] = yj + p;\
    } }   

void vsip_minterp_spline_d(
      const vsip_vview_d *ax,
      const vsip_mview_d *ay,
      vsip_spline_d *spl,
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
         VINTERP_SPLINE(ax,y,spl,bx,yf);
      }
   } else { /* must be by column */
      vsip_length M = ay->row_length;
      for(i=0; i<M; i++){
         GETCOL(ay,i,y);
         GETCOL(by,i,yf);
         VINTERP_SPLINE(ax,y,spl,bx,yf);
      }
   }
   return;
}
