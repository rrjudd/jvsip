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
/* $Id: vsip_vinterp_spline_d.c,v 2.1 2008/09/14 20:48:40 judd Exp $ */

/* Based on f77 algorithm in Cheney & Kincaid Numerical Mathematics (2ndEd) */
 
#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_splineattributes_d.h>

void vsip_vinterp_spline_d(
      const vsip_vview_d *t0, 
      const vsip_vview_d *y0, 
      vsip_spline_d *spl, 
      const vsip_vview_d *xf0, 
      const vsip_vview_d *yf0){
   vsip_length N = t0->length;
   vsip_length M = xf0->length;
   vsip_stride t_st = t0->stride * t0->block->rstride,
               y_st = y0->stride * y0->block->rstride,
               xf_st = xf0->stride * xf0->block->rstride,
               yf_st = yf0->stride * yf0->block->rstride;
   vsip_index i;
   vsip_stride j;
   vsip_scalar_d *t = t0->block->array + t0->offset * t0->block->rstride;
   vsip_scalar_d *y = y0->block->array + y0->offset * y0->block->rstride;
   vsip_scalar_d *xf = xf0->block->array + xf0->offset * xf0->block->rstride;
   vsip_scalar_d *yf = yf0->block->array + yf0->offset * yf0->block->rstride;
   vsip_scalar_d *z = spl->z, *h=spl->h, *b = spl->b, *u = spl->u, *v = spl->v;
   { /* calculate constants */
      for(i=0; i<N-1; i++){
         h[i] = t[(i+1) * t_st] - t[i * t_st];
         b[i] = (y[(i+1) * y_st] - y[i * y_st])/h[i];
      }
      u[1] = 2.0 * (h[0] + h[1]);
      v[1] = 6.0 * (b[1] - b[0]);
      for(i=2; i<N-1; i++){
         u[i] = 2.0 * (h[i] + h[i-1]) - h[i-1] * h[i-1] / u[i-1];\
         v[i] = 6.0 * (b[i] - b[i-1]) - h[i-1] * v[i-1] / u[i-1];\
      }
      z[N-1] = 0.0;
      for(i=N-2; i>0; i--)
         z[i] = (v[i] - h[i] * z[i+1])/u[i];
      z[0] = 0.0;
   }
   for(i=0; i<M; i++){
      vsip_scalar_d d,h,b,p,x;
      x = xf[i * xf_st];
      j = N-2;
      while((x < (d = t[j * t_st])) && (j >= 0)){
         j--;
      }
      {
         register vsip_scalar_d yj,zj,zj1;
         yj = y[j * y_st];
         zj=z[j]; zj1=z[j+1];
         d = x - d;
         if(j < 0) j = 0;
         if(d < 0) return;
         h = t[(j+1) * t_st] - t[j * t_st];
         b = (y[(j+1) * y_st] - yj)/h - h * (zj1 + 2.0 * zj)/6.0;
         p = ((0.5 * zj +d * (zj1 - zj)/(6.0 * h)) * d + b) * d;
         yf[i * yf_st] = yj + p;;
      }
   }
   return;
}   
