/* Created RJudd March 17, 1999 */
/* SPAWARSYSCEN D881 */
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
/* $Id: vsip_correlate1d_f.c,v 2.1 2007/04/16 16:50:41 judd Exp $ */

#include<vsip.h>
#include<vsip_corr1dattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include"VI_vcopy_f_f.h"
#include"VI_vfill_f.h"
#include"VI_vrealview_f.h"
#include"VI_vimagview_f.h"

static
void VI_vunbiasfull_f(
                      const vsip_corr1d_f *cor, 
                      const vsip_vview_f *x, 
                      const vsip_vview_f *y)
{
   /* register */ vsip_length n = y->length;
   /* register */ vsip_length s1 = n - cor->m;
   /* register */ vsip_length s2 = cor->m;
   /* register */ vsip_stride xst = x->stride * x->block->rstride,
      yst = y->stride * y->block->rstride;
   vsip_scalar_f *xp = (x->block->array) + x->offset * x->block->rstride,
      *yp = (y->block->array) + y->offset * y->block->rstride;
   vsip_scalar_f scale2 = (vsip_scalar_f)1.0/(vsip_scalar_f)cor->m,
      scale1 = (vsip_scalar_f)1.0;
   while(n-- > s1){
      *yp = *xp / scale1;
      scale1 += 1.0;
      yp+=yst; xp+=xst;
   }
   n++;
   while(n-- > s2){
      *yp = *xp * scale2;
      yp+=yst; xp+=xst;
   }
   n++;
   n++;
   while(n-- > 1){
      *yp = *xp / (vsip_scalar_f)n;
      yp+=yst; xp+=xst;
   }
   return;
}

static
void VI_vunbiassame_f(
                      const vsip_corr1d_f *cor, 
                      const vsip_vview_f *x, 
                      const vsip_vview_f *y)
{
   vsip_index i;
   register vsip_scalar_f mscale = (vsip_scalar_f)cor->m;
   vsip_length adj = (vsip_length)(cor->m & 1);
   vsip_length n0 = cor->m/2;
   vsip_length n1 = cor->n - n0;
   vsip_length n2 = cor->n;
   register vsip_scalar_f mceil = (vsip_scalar_f)(n0 + adj);
   register vsip_scalar_f N = (vsip_scalar_d)(n2 + n0);
   
   vsip_stride xst = x->stride * x->block->rstride,
               yst = y->stride * y->block->rstride;
   vsip_scalar_f *xp = (x->block->array) + x->offset * x->block->rstride,
                 *yp = (y->block->array) + y->offset * y->block->rstride;
   
   for(i=0; i < n0; i++)
      yp[i * yst] = xp[i * xst] / ((vsip_scalar_f)(i) + mceil);
   for(i=n0; i < n1; i++)
      yp[i * yst] = xp[i * xst] / mscale ;
   for(i=n1; i < n2; i++)
      yp[i * yst] = xp[i * xst] / (N - (vsip_scalar_f)i);
      return;
}
   

void vsip_correlate1d_f(
      const vsip_corr1d_f *cor,
      vsip_bias bias,
      const vsip_vview_f *h,
      const vsip_vview_f *x,
      const vsip_vview_f *y)
{
    vsip_vview_f xxr,xxi,hhr,hhi,
                 *xr = VI_vrealview_f(cor->x,&xxr),
                 *xi = VI_vimagview_f(cor->x,&xxi),
                 *hr = VI_vrealview_f(cor->h,&hhr),
                 *hi = VI_vimagview_f(cor->h,&hhi);
    xr->length = cor->x->length - x->length;
    VI_vfill_f(0,xr);
    xr->offset = xr->length;
    xr->length = x->length;
    VI_vcopy_f_f(x,xr);
    xr->offset = 0;
    xr->length = cor->x->length;
    hr->length = h->length;
    VI_vcopy_f_f(h,hr);
    hr->offset = hr->length;
    hr->length = cor->h->length - h->length;
    VI_vfill_f(0,hr);
    hr->offset = 0;
    hr->length = cor->h->length;
    VI_vfill_f(0,hi);
    VI_vfill_f(0,xi);
    vsip_ccfftip_f(cor->fft,cor->h);
    vsip_ccfftip_f(cor->fft,cor->x);
    vsip_cvjmul_f(cor->x,cor->h,cor->x);
    vsip_cvconj_f(cor->x,cor->x);
    vsip_rscvmul_f(1/(vsip_scalar_f)cor->N,cor->x,cor->x);
    vsip_ccfftip_f(cor->fft,cor->x);
    switch(cor->support){
      case VSIP_SUPPORT_FULL:
        xr->offset = xr->length - cor->mn;
        xr->length = y->length;
        if(bias == VSIP_UNBIASED){
            VI_vunbiasfull_f(cor,xr,y);
        } else {
            VI_vcopy_f_f(xr,y);
        }
        break;
      case VSIP_SUPPORT_SAME:
        xr->offset = xr->length - cor->mn + (cor->m -1 )/2;
        xr->length = y->length;
        if(bias == VSIP_UNBIASED){
            VI_vunbiassame_f(cor,xr,y);
        } else {
            VI_vcopy_f_f(xr,y);
        }
        break;
      case VSIP_SUPPORT_MIN:
        xr->offset = xr->length - cor->mn + cor->m - 1;
        xr->length = y->length;
        if(bias == VSIP_UNBIASED){
            vsip_svmul_f((vsip_scalar_f)1.0/(vsip_scalar_f)cor->m,xr,y);
        } else {
            VI_vcopy_f_f(xr,y);
        }
        break;
    }
    return;
}

