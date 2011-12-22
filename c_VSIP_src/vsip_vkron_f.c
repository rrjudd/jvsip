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
/* $Id: vsip_vkron_f.c,v 2.0 2003/02/22 15:19:14 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_mviewattributes_f.h>

void vsip_vkron_f(
   vsip_scalar_f alpha,
   const vsip_vview_f *x,
   const vsip_vview_f *y,
   const vsip_mview_f *C)
{
    vsip_scalar_f tmp;
    vsip_length n = x->length,
                m = y->length;
    vsip_scalar_f  *x_p = x->block->array + x->offset * x->block->rstride;
    vsip_scalar_f  *y_p = y->block->array + y->offset * y->block->rstride;
    vsip_scalar_f  *yp0 = y_p;
    vsip_scalar_f  *Cp0 = C->block->array + C->offset * C->block->rstride;
    vsip_scalar_f  *C_p = Cp0;
    vsip_stride Crst = C->row_stride * C->block->rstride,
                Ccst = C->col_stride * C->block->rstride, 
                xst  = x->stride * x->block->rstride,
                yst  = y->stride * y->block->rstride;
    while(n-- > 0){
       tmp = *x_p * alpha; x_p += xst;
       while(m-- > 0){
          *C_p = tmp * *y_p;
           C_p += Ccst; y_p+= yst;
       }
       Cp0 += Crst;
       C_p = Cp0;
       y_p = yp0;
       m = y->length;
    }
    return;
}
