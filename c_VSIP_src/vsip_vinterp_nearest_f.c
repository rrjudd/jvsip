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
/* $Id: vsip_vinterp_nearest_f.c,v 2.1 2008/08/17 18:01:49 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>

#define F2(x1,x2,y1,y2,x,y) {   \
   vsip_scalar_f dif1 = x - x1;\
   vsip_scalar_f dif2 = x2 - x;\
   if(dif1 > dif2) \
      y = y2;\
   else \
      y = y1; \
 }

void vsip_vinterp_nearest_f(
      const vsip_vview_f *x0,
      const  vsip_vview_f *y0,
      const  vsip_vview_f *x,
      const  vsip_vview_f *y){
   vsip_length N0 = x0->length;
   vsip_length N = x->length;
   vsip_stride x0_str = x0->stride * x0->block->rstride,
               y0_str = y0->stride * y0->block->rstride,
               x_str = x->stride * x->block->rstride,
               y_str = y->stride * y->block->rstride;
   vsip_scalar_f *x0_ptr = x0->block->array + x0->offset * x0->block->rstride,
                 *y0_ptr = y0->block->array + y0->offset * y0->block->rstride,
                 *x_ptr  = x->block->array  + x->offset  * x->block->rstride,
                 *y_ptr  = y->block->array  + y->offset  * y->block->rstride;
   vsip_index i=0,j=0;
   vsip_scalar_f sx1,sx2,sy1,sy2,sx;
   while((j < N) && (i < N0-1)){
      sx1 = x0_ptr[i * x0_str];
      sx2 = x0_ptr[(i+1)*x0_str];
      sy1 = y0_ptr[i * y0_str];
      sy2 = y0_ptr[(i+1) * y0_str];
      sx = x_ptr[j * x_str];
      if(sx < sx2) {
         vsip_scalar_f a;
         F2(sx1,sx2,sy1,sy2,sx,a);
         y_ptr[j * y_str] = a;
         j++;
      } else i++;
   }
   return;
}
