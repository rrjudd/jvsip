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
/* $Id: vsip_vinterp_linear_f.c,v 2.1 2008/08/17 18:01:49 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>

#define F1(x0,x1,y0,y1,x,y) {y = y0 + (y1-y0)/(x1-x0) * (x - x0);}

void vsip_vinterp_linear_f(
      const vsip_vview_f *ax,
      const vsip_vview_f *ay,
      const vsip_vview_f *bx,
      const vsip_vview_f *by){
   vsip_length N0 = ax->length;
   vsip_length N  = bx->length;
   vsip_index i=0,j=0;
   vsip_scalar_f sx1,sx2,sy1,sy2,sx;
   vsip_stride axst = ax->stride * ax->block->rstride,
               ayst = ay->stride * ax->block->rstride,
               bxst = bx->stride * bx->block->rstride,
               byst = by->stride * by->block->rstride;
   vsip_scalar_f *axptr = (ax->block->array) + ax->offset * ax->block->rstride,
                 *ayptr = (ay->block->array) + ay->offset * ay->block->rstride,
                 *bxptr = (bx->block->array) + bx->offset * bx->block->rstride,
                 *byptr = (by->block->array) + by->offset * by->block->rstride;
  
   while((j < N) && (i < N0-1)){
      sx1 = axptr[i * axst];
      sx2 = axptr[(i + 1) * axst];
      sy1 = ayptr[i * ayst];
      sy2 = ayptr[(i + 1) * ayst];;
      sx  = bxptr[j * bxst];
      if(sx < sx2) {
         vsip_scalar_f a;
         F1(sx1,sx2,sy1,sy2,sx,a);
         byptr[j * byst] = a;
         j++;
      } else i++;
   }
   return;
}
