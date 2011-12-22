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
/* $Id: vsip_cvkron_f.c,v 2.0 2003/02/22 15:18:50 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_cmviewattributes_f.h>

void vsip_cvkron_f(
   vsip_cscalar_f alpha,
   const vsip_cvview_f *x,
   const vsip_cvview_f *y,
   const vsip_cmview_f *C)
{
    vsip_cscalar_f tmp;
    vsip_length n = x->length,
                m = y->length;
    vsip_scalar_f  *x_p_r = x->block->R->array + x->offset * x->block->cstride;
    vsip_scalar_f  *x_p_i = x->block->I->array + x->offset * x->block->cstride;
    vsip_scalar_f  *y_p_r = y->block->R->array + y->offset * y->block->cstride;
    vsip_scalar_f  *y_p_i = y->block->I->array + y->offset * y->block->cstride;
    vsip_scalar_f  *yp0_r = y_p_r;
    vsip_scalar_f  *yp0_i = y_p_i;
    vsip_scalar_f  *Cp0_r = C->block->R->array + C->offset * C->block->cstride;
    vsip_scalar_f  *Cp0_i = C->block->I->array + C->offset * C->block->cstride;
    vsip_scalar_f  *C_p_r = Cp0_r;
    vsip_scalar_f  *C_p_i = Cp0_i;
    vsip_stride Crst = C->row_stride * C->block->cstride,
                Ccst = C->col_stride * C->block->cstride, 
                xst  = x->stride * x->block->cstride,
                yst  = y->stride * y->block->cstride;
    while(n-- > 0){
       tmp.r = *x_p_r * alpha.r - *x_p_i * alpha.i; 
       tmp.i = *x_p_i * alpha.r + *x_p_r * alpha.i;
       x_p_r += xst;
       x_p_i += xst;
       while(m-- > 0){
          *C_p_r = tmp.r * *y_p_r - tmp.i * *y_p_i;
          *C_p_i = tmp.i * *y_p_r + tmp.r * *y_p_i;
           C_p_r += Ccst; y_p_r+= yst;
           C_p_i += Ccst; y_p_i+= yst;
       }
       Cp0_r += Crst;
       Cp0_i += Crst;
       C_p_r = Cp0_r;
       C_p_i = Cp0_i;
       y_p_r = yp0_r;
       y_p_i = yp0_i;
       m = y->length;
    }
    return;
}
