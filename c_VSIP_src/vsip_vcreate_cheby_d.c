/* RJudd 22 February, 98 */
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
/* $Id: vsip_vcreate_cheby_d.c,v 2.5 2007/04/21 19:39:33 judd Exp $ */
/* Converted matlab code to VSIP */
/* Modifed March 8, 98 */
/* DAVID'S Matlab Code for cheby */
/*
//  function window = chebyw(nf, ripple)
//  % nf - window length
//  % ripple - stopband attenuation in dB
//  dp = 10.^(-ripple/20);
//  odd = rem(nf,2);
//  n2 = fix(nf/2);
//  df = acos(1/cosh(acosh((1+dp)/dp)/(nf-1)))/pi;
//  x0 = (3-cos(2*pi*df))/(1.+cos(2*pi*df));
//  alpha = (x0 + 1)/2;
//  beta = (x0 - 1)/2;
//  k = (0:nf-1);
//  f = k/nf;
//  x = alpha*cos(2*pi*f) + beta;
//  tmp = (abs(x) > 1);
//  j = sqrt(-1);
//  wf = dp*(tmp.*(cosh(((nf-1)/2).*acosh(x)))+(1-tmp).*cos(((nf-1)/2).*acos(x)));
//  if (~odd)
//     wf = real(wf).*exp(-j*pi*f);
//     wf(n2+1:nf) = -wf(n2+1:nf);
//  else
//     wf = wf +j*zeros(1,nf);
//  end
//  wt = fft(wf);
//  wt = wt(1:nf)/wt(1);
//  window = real([wt(n2+2:nf) wt(1:n2+1)]');
//  %size(window)
//  %plot(window,1,4*nf)
//  %plot(window)
*/

#include<math.h>
#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include"vsip_scalars.h"
#include"VI_vcreate_d.h"
#include"VI_valldestroy_d.h"
#include"VI_cvcreate_d.h"
#include"VI_cvalldestroy_d.h"
#include"VI_vcopy_d_d.h"
#include"VI_cvfill_d.h"
#include"VI_cvsqrt_d.h"
#include"VI_rcvadd_d.h"
#include"VI_cvadd_d.h"
#include"VI_vramp_d.h"
#include"VI_vrealview_d.h"
#include"VI_svsub_d.h"
#include"VI_vclip_d.h"
#include"VI_vacos_d.h"
#include"VI_vcos_d.h"
#include"VI_svmul_d.h"
#include"VI_csvmul_d.h"
#include"VI_vmul_d.h"
#include"VI_rcvmul_d.h"
#include"VI_rscvmul_d.h"
#include"VI_veuler_d.h"
#include"VI_cvget_d.h"

#define cheby_PI ((vsip_scalar_d)3.1415926535897932384626433832795)
#define TWOPI    ((vsip_scalar_d)6.283185307179586)


/*  VSIP internal functions below */
/*******************************************************************/     
static
vsip_scalar_d 
VI_acosh_d(vsip_scalar_d x){ /*scalar acosh*/
     vsip_scalar_d a = x * x;
     vsip_scalar_d z;
     vsip_scalar_d C1 = .25;
     vsip_scalar_d C2 = 3.0/32.0;
     vsip_scalar_d C3 = 15.0/288.0;
     vsip_scalar_d C4 = 105.0/3072.0;
     if(x <= 1.0) return 0.0;      
     if(x < 10) return (vsip_scalar_d) log(x + sqrt(a - 1.0));
     z = 1.0/a;
     return (vsip_scalar_d)(log(2.0 * x) - z * (C1 + z * (C2 + z * (C3 + z * C4))));
}

/*******************************************************************/     
static
void 
VI_cvlog_d(vsip_cvview_d *a,vsip_cvview_d *r)
{ 
     /* register */ vsip_length n = r->length;
     vsip_stride cast = a->block->cstride;
     vsip_stride crst = r->block->cstride;
     vsip_scalar_d *apr = (vsip_scalar_d *)((a->block->R->array) + cast * a->offset),
                   *rpr = (vsip_scalar_d *)((r->block->R->array) + crst * r->offset);
     vsip_scalar_d *api = (vsip_scalar_d *)((a->block->I->array) + cast * a->offset),
                   *rpi = (vsip_scalar_d *)((r->block->I->array) + crst * r->offset);
     /* register */ vsip_stride ast = (cast * a->stride),
                                rst = (crst * r->stride);
     vsip_scalar_d arg = 0;
     while(n-- > 0){
         arg  = (vsip_scalar_d)atan2(*api , *apr);
         *rpr = (vsip_scalar_d)log(sqrt(*apr * *apr + *api * *api));
         *rpi = arg;
        apr += ast; api += ast;
        rpr += rst; rpi += rst;
    }
}

/*******************************************************************/     
static
void 
VI_rcvacosh_d(vsip_vview_d *x, vsip_cvview_d *r){
     void VI_cvlog_d(vsip_cvview_d*,vsip_cvview_d*);
     {
         vsip_length n = r->length;
         vsip_stride r_str = r->stride * r->block->cstride;
         vsip_stride x_str = x->stride * x->block->rstride;
         vsip_stride r_off = r_str * r->offset;
         vsip_stride x_off = x_str * x->offset;
         vsip_scalar_d *x_p = x->block->array + x_off,
                       *rp_r = (vsip_scalar_d*)(r->block->R->array + r_off),
                       *rp_i = (vsip_scalar_d*)(r->block->I->array + r_off);
            
         while(n-- > 0){
                    *rp_r = *x_p * *x_p - (vsip_scalar_d)1.0;
                    *rp_i = (vsip_scalar_d)0;
                     rp_r += r_str; rp_i += r_str; x_p += x_str;
         }
      }
     VI_cvsqrt_d(r,r);
     VI_rcvadd_d(x,r,r);
     VI_cvlog_d(r,r);  
     return;
}
               
/*******************************************************************/     
static
void 
VI_cvcosh_d(vsip_cvview_d *x, vsip_cvview_d *r){
     vsip_length n = r->length;
     vsip_stride stx = x->block->cstride * x->stride,
                 str = r->block->cstride * r->stride;
     vsip_scalar_d *x_pr = (vsip_scalar_d*)(x->block->R->array + stx * x->offset),
                   *x_pi = (vsip_scalar_d*)(x->block->I->array + stx * x->offset),
                   *r_pr = (vsip_scalar_d*)(r->block->R->array + str * r->offset),
                   *r_pi = (vsip_scalar_d*)(r->block->I->array + str * r->offset),
                    tmp, mag, maginv;
     while(n-- > 0){
        mag    =  (vsip_scalar_d)0.50 * VSIP_EXP_D(*x_pr); 
        maginv =  (vsip_scalar_d)0.25 / mag;
        tmp    = (mag + maginv) * VSIP_COS_D(*x_pi); 
        *r_pi  = (mag - maginv) * VSIP_SIN_D(*x_pi);
        *r_pr  = tmp;
        x_pr += stx; r_pr += str;
        x_pi += stx; r_pi += str;
     }
}

/*******************************************************************/     
static
void 
VI_vfreqswap_d(vsip_vview_d *a)
{ 
   vsip_length n;
   vsip_length n2 = (a->length / 2);
   vsip_scalar_d *a_p = a->block->array + a->offset * a->block->rstride,
                 *t_p,
                 tmp;
   vsip_stride ast = a->stride * a->block->rstride;
   if(a->length % 2){
      t_p = a_p + n2 + 1;
      tmp = *(t_p - 1);
      *(t_p - 1) = *a_p;
      n = n2 - 1;
      while(n-- > 0){
         *a_p = *t_p;
          a_p += a->stride;
         *t_p = *a_p;
          t_p += a->stride;
      }
      *a_p = *t_p;
      *t_p = tmp;
   } else {
      n = n2;
      t_p = a_p + n2 ;
      while(n-- > 0){
        tmp = *t_p;
        *t_p = *a_p;
        *a_p =  tmp;
         a_p += ast; t_p += ast;
      }
   }
}

vsip_vview_d* (vsip_vcreate_cheby_d)(
          vsip_length nf, 
          vsip_scalar_d ripple,
          vsip_memory_hint hint) {
    vsip_vview_d *window = VI_vcreate_d(nf,hint);
    int odd = 0;
    vsip_length n2 = 0;
    vsip_scalar_d dp     = 0.0,
                  df     = 0.0,
                  x0     = 0.0, 
                  alpha  = 0.0, 
                  beta   = 0.0;
    vsip_cvview_d *wf    = VI_cvcreate_d(nf,hint),
                  *Cfoo  = VI_cvcreate_d(nf,hint);
    vsip_vview_d *f      = VI_vcreate_d(nf,hint),
                 *x      = VI_vcreate_d(nf,hint), 
                 *tmp    = VI_vcreate_d(nf,hint),
                 *nottmp = VI_vcreate_d(nf,hint);

    vsip_vview_d wwfR;
    vsip_vview_d *wfR = VI_vrealview_d(wf,&wwfR);
    vsip_vview_d RRefoo; 
    vsip_vview_d *Refoo = VI_vrealview_d(Cfoo,&RRefoo);

    /* check for malloc errors, destroy everything and return null on failure */
    if((wf == NULL) | (Cfoo == NULL) | (f == NULL) | (x == NULL) | 
       (tmp == NULL) | (wfR == NULL) | (Refoo == NULL) | 
       (window == NULL) | (nottmp == NULL)){
            VI_valldestroy_d(x);
            VI_valldestroy_d(f);
            VI_valldestroy_d(tmp);
            VI_cvalldestroy_d(wf);
            VI_cvalldestroy_d(Cfoo);
            VI_valldestroy_d(nottmp);
            VI_valldestroy_d(window);
            return (vsip_vview_d*)NULL;
    }
    VI_cvfill_d(wf->block->a_zero,wf); /* zero fill */
    dp    = VSIP_EXP10_D(-ripple/20.0);/*dp = 10.^(-ripple/20);*/
    odd   = ((int)nf) % 2;  /*odd = rem(nf,2);*/
    n2    = (vsip_length) VSIP_FLOOR_D((vsip_scalar_d)nf/2.0); /*n2 = fix(nf/2);*/
            /*df = acos(1/cosh(acosh((1+dp)/dp)/(nf-1)))/pi;*/
    df    = (vsip_scalar_d)VSIP_ACOS_D(1.0/VSIP_COSH_D(VI_acosh_d(((vsip_scalar_d)1.0 + dp)/dp) / ((vsip_scalar_d)nf - 1.0)))/cheby_PI;
            /*x0 = (3-cos(2*pi*df))/(1.+cos(2*pi*df));*/
    x0    = (vsip_scalar_d)((3. - VSIP_COS_D(TWOPI * df))/(1. + VSIP_COS_D(TWOPI * df)));
    alpha = (x0 + (vsip_scalar_d)1.0) / (vsip_scalar_d)2.; /*alpha = (x0 + 1)/2;*/
    beta  = (x0 - (vsip_scalar_d)1.0) / (vsip_scalar_d)2.; /*beta = (x0 - 1)/2;*/
    VI_vramp_d(((vsip_scalar_d)0.0),((vsip_scalar_d)1.0/((vsip_scalar_d)nf)),f); /*k = (0:nf-1);f = k/nf;*/
    /* x = alpha*cos(2*pi*f) + beta; */
    {
      vsip_length n = nf;
      vsip_scalar_d *f_p = f->block->array + f->offset,
                    *x_p = x->block->array + x->offset;
      while(n-- > 0){
        *x_p = alpha * (vsip_scalar_d)VSIP_COS_D(TWOPI * *f_p) + beta;
         x_p += x->stride; f_p += f->stride; 
      }
    } 
    /* END x = alpha*cos(2*pi*f) + beta; */

    /*tmp = (mag(x) > 1); */
    {
      vsip_length n = nf;
      vsip_scalar_d *x_p   = x->block->array   + x->offset,
                    *tmp_p = tmp->block->array + tmp->offset;
      while(n-- > 0){
        *tmp_p = (vsip_scalar_d)((((*x_p >= 0) ? *x_p : - *x_p) > 1) ? 1.0 : 0.0);
         x_p += x->stride; tmp_p += tmp->stride;
      }
    }
    /* END tmp = (mag(x) > 1); */

    /* wf = dp*(tmp.*(cosh((((vsip_scalar_d)nf-1.0)/2).*acosh(x)))+
                (1-tmp).*cos((((vsip_scalar_d)nf-1.0)/2).*acos(x)));*/
    { 
      VI_svsub_d(1.0,tmp,nottmp);
      VI_vclip_d(x,-1.0,1.0,-1.0,1.0,wfR); /* modified to handle x out side of range of acos*/
      /* ensures that for x > 1 default return value of acos is zero */
      VI_vacos_d(wfR,Refoo);
      VI_svmul_d(((vsip_scalar_d)nf-(vsip_scalar_d)1.0)/(vsip_scalar_d)2.0,Refoo,Refoo);
      VI_vcos_d(Refoo,Refoo);
      VI_vmul_d(nottmp,Refoo,wfR);
  
      VI_rcvacosh_d(x,Cfoo);

      VI_rscvmul_d(((vsip_scalar_d)nf - (vsip_scalar_d)1.0)/(vsip_scalar_d)2.0,Cfoo,Cfoo);
      VI_cvcosh_d(Cfoo,Cfoo);
      VI_rcvmul_d(tmp,Cfoo,Cfoo); 
      VI_cvadd_d(Cfoo,wf,wf);
      VI_rscvmul_d(dp,wf,wf);
    }
    /* END wf = dp*(tmp.*(cosh(((nf-1)/2).*acosh(x)))+
                (1-tmp).*cos(((nf-1)/2).*acos(x)));*/

    if(!odd ){ /* if (~odd) */
      /*wf = real(wf).*exp(-j*pi*f);*/ 
      { 
        VI_svmul_d((vsip_scalar_d)(-cheby_PI),f,f); 
        VI_veuler_d(f,Cfoo);
        VI_rcvmul_d(wfR,Cfoo,wf);
      }
      /*END wf = real(wf).*exp(-j*pi*f);*/

      /* wf(n2+1:nf) = -wf(n2+1:nf); */
      { 
        vsip_stride str = wf->block->cstride;
        vsip_length n = n2;
        vsip_scalar_d *wf_rp = (vsip_scalar_d*)(wf->block->R->array + str * n); 
        vsip_scalar_d *wf_ip = (vsip_scalar_d*)(wf->block->I->array + str * n); 
        while(n-- > 0){ *wf_rp = - *wf_rp; wf_rp += str; *wf_ip = - *wf_ip; wf_ip += str;}
      }
      /*END wf(n2+1:nf) = -wf(n2+1:nf);*/
    }/* END if (~odd) */

    {/* wt = fft(wf); */
      vsip_fft_d* fftplan = vsip_ccfftip_create_d(nf,(vsip_scalar_d)(1.0/(vsip_scalar_d)nf),VSIP_FFT_FWD,0,VSIP_ALG_NOISE);
      vsip_ccfftip_d(fftplan,wf);
      {/* wt = wt(1:nf)/wt(1) */
        vsip_cscalar_d scale;
        vsip_scalar_d magsq;
        VI_CVGETP_D(wf,0);
        scale = VI_CVGET_D(wf);
        scale.i = -scale.i;
        magsq = scale.i * scale.i + scale.r * scale.r;
        scale.i /= magsq; scale.r /= magsq;
        VI_csvmul_d(scale,wf,wf);
      }            
      vsip_fft_destroy_d(fftplan);
    }/*END wt = fft(wf); */

    VI_vcopy_d_d(wfR, window);
    VI_vfreqswap_d(window);
    VI_valldestroy_d(x);
    VI_valldestroy_d(f);
    VI_valldestroy_d(tmp);
    VI_valldestroy_d(nottmp);
    VI_cvalldestroy_d(wf);
    VI_cvalldestroy_d(Cfoo);
    return window;
}
