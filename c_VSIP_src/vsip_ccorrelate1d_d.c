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
/* $Id: vsip_ccorrelate1d_d.c,v 2.1 2007/04/16 16:48:42 judd Exp $ */

#include<vsip.h>
#include<vsip_ccorr1dattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include"VI_cvcopy_d_d.h"
#include"VI_cvfill_d.h"

static
void VI_cvunbiasfull_d(
                       const vsip_ccorr1d_d *cor, 
                       const vsip_cvview_d *x, 
                       const vsip_cvview_d *y)
{
   /* register */ vsip_length n = y->length;
   /* register */ vsip_length s1 = n - cor->m;
   /* register */ vsip_length s2 = cor->m;
   /* register */ vsip_stride cxst = x->block->cstride,
      cyst = y->block->cstride;
   /* register */ vsip_stride xst = x->stride * cxst,
      yst = y->stride * cyst;
   vsip_scalar_d *xpr = (x->block->R->array) + x->offset * cxst,
      *ypr = (y->block->R->array) + y->offset * cyst;
   vsip_scalar_d *xpi = (x->block->I->array) + x->offset * cxst,
      *ypi = (y->block->I->array) + y->offset * cyst;
   vsip_scalar_d scale2 = 1.0/(vsip_scalar_d)cor->m,
      scale1 = 1.0;
   while(n-- > s1){
      *ypr = *xpr / scale1;
      *ypi = *xpi / scale1;
      scale1 += 1.0;
      ypr+=yst; xpr+=xst;
      ypi+=yst; xpi+=xst;
   }
   n++;
   while(n-- > s2){
      *ypr = *xpr * scale2;
      *ypi = *xpi * scale2;
      ypr+=yst; xpr+=xst;
      ypi+=yst; xpi+=xst;
   }
   n++;
   n++;
   while(n-- > 1){
      *ypr = *xpr / (vsip_scalar_d)n;
      *ypi = *xpi / (vsip_scalar_d)n;
      ypr+=yst; xpr+=xst;
      ypi+=yst; xpi+=xst;
   }
   return;
}

static
void VI_cvunbiassame_d(
                      const vsip_ccorr1d_d *cor, 
                      const vsip_cvview_d *x, 
                      const vsip_cvview_d *y)
{
   vsip_index i;
   register vsip_scalar_d mscale = (vsip_scalar_d)cor->m;
   vsip_length adj = (vsip_length)(cor->m & 1);
   vsip_length n0 = cor->m/2;
   vsip_length n1 = cor->n - n0;
   vsip_length n2 = cor->n;
   register vsip_scalar_d mceil = (vsip_scalar_d)(n0 + adj);
   register vsip_scalar_f N = (vsip_scalar_d)(n2 + n0);   
   
   vsip_stride cxst = x->block->cstride,
               cyst = y->block->cstride;
   vsip_stride xst = x->stride * cxst,
               yst = y->stride * cyst;
   vsip_scalar_d *xpr = (x->block->R->array) + x->offset * cxst,
                 *ypr = (y->block->R->array) + y->offset * cyst;
   vsip_scalar_d *xpi = (x->block->I->array) + x->offset * cxst,
                 *ypi = (y->block->I->array) + y->offset * cyst;
   
   for(i=0; i < n0; i++){
      ypr[i * yst] = xpr[i * xst] / ((vsip_scalar_d)(i) + mceil);
      ypi[i * yst] = xpi[i * xst] / ((vsip_scalar_d)(i) + mceil);
   }
   for(i=n0; i < n1; i++){
      ypr[i * yst] = xpr[i * xst] / mscale ;
      ypi[i * yst] = xpi[i * xst] / mscale ;
   }
   for(i=n1; i < n2; i++){
      ypr[i * yst] = xpr[i * xst] / (N - (vsip_scalar_d)i);
      ypi[i * yst] = xpi[i * xst] / (N - (vsip_scalar_d)i);
   }
   return;
}

void vsip_ccorrelate1d_d(
      const vsip_ccorr1d_d *cor,
      vsip_bias bias,
      const vsip_cvview_d *h,
      const vsip_cvview_d *x,
      const vsip_cvview_d *y)
{
    vsip_cvview_d xx = *cor->x,
                  hh = *cor->h;
    vsip_cvview_d *xt = &xx,
                  *ht = &hh;
    xt->length = cor->x->length - x->length;
    VI_cvfill_d(vsip_cmplx_d((vsip_scalar_d)0,(vsip_scalar_d)0),xt);
    xt->offset = xt->length;
    xt->length = x->length;
    VI_cvcopy_d_d(x,xt);
    xt->length = cor->x->length;
    xt->offset = 0;

    ht->length = cor->h->length - h->length;
    ht->offset = h->length; 
    VI_cvfill_d(vsip_cmplx_d((vsip_scalar_d)0,(vsip_scalar_d)0),ht);
    ht->offset = 0;
    ht->length = h->length;
    VI_cvcopy_d_d(h,ht);

    vsip_ccfftip_d(cor->fft,cor->h);
    vsip_ccfftip_d(cor->fft,cor->x);
    
    vsip_cvjmul_d(cor->x,cor->h,cor->x);
    vsip_cvconj_d(cor->x,cor->x);
    vsip_rscvmul_d(1/(vsip_scalar_d)cor->N,cor->x,cor->x);
    vsip_ccfftip_d(cor->fft,cor->x);
    /* vsip_cvconj_d(cor->x,cor->x); */

    switch(cor->support){
      case VSIP_SUPPORT_FULL:
        xt->offset = xt->length - cor->mn;
        xt->length = y->length;
        if(bias == VSIP_UNBIASED){
            VI_cvunbiasfull_d(cor,xt,y);
        } else {
            VI_cvcopy_d_d(xt,y);
        }
        break;
      case VSIP_SUPPORT_SAME:
        xt->offset = xt->length - cor->mn + (cor->m-1)/2;
        xt->length = y->length;
        if(bias == VSIP_UNBIASED){
            VI_cvunbiassame_d(cor,xt,y);
        } else {
            VI_cvcopy_d_d(xt,y);
        }
        break;
      case VSIP_SUPPORT_MIN:
        xt->offset = xt->length - cor->mn + cor->m - 1;
        xt->length = y->length;
        if(bias == VSIP_UNBIASED){
            vsip_rscvmul_d(1.0/(vsip_scalar_d)cor->m,xt,y);
        } else {
            VI_cvcopy_d_d(xt,y);
        }
        break;
    }
    return;
}

