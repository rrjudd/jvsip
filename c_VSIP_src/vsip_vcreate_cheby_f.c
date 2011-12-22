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
/* $Id: vsip_vcreate_cheby_f.c,v 2.5 2007/04/21 19:39:33 judd Exp $ */
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
#include<vsip_vviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include"vsip_scalars.h"
#include"VI_vcreate_f.h"
#include"VI_valldestroy_f.h"
#include"VI_cvcreate_f.h"
#include"VI_cvalldestroy_f.h"
#include"VI_vcopy_f_f.h"
#include"VI_cvfill_f.h"
#include"VI_cvsqrt_f.h"
#include"VI_rcvadd_f.h"
#include"VI_cvadd_f.h"
#include"VI_vramp_f.h"
#include"VI_vrealview_f.h"
#include"VI_svsub_f.h"
#include"VI_vclip_f.h"
#include"VI_vacos_f.h"
#include"VI_vcos_f.h"
#include"VI_svmul_f.h"
#include"VI_csvmul_f.h"
#include"VI_vmul_f.h"
#include"VI_rcvmul_f.h"
#include"VI_rscvmul_f.h"
#include"VI_veuler_f.h"
#include"VI_cvget_f.h"

#define cheby_PI ((vsip_scalar_f)3.1415926535897932384626433832795)
#define TWOPI    ((vsip_scalar_f)6.283185307179586)


/*  VSIP internal functions below */
/*******************************************************************/     
static
vsip_scalar_f 
VI_acosh_f(vsip_scalar_f x){ /*scalar acosh*/
     vsip_scalar_f a = x * x;
     vsip_scalar_f z; 
     vsip_scalar_f C1 = .25;
     vsip_scalar_f C2 = 3.0/32.0;
     vsip_scalar_f C3 = 15.0/288.0;
     vsip_scalar_f C4 = 105.0/3072.0;
     if(x <= 1.0) return 0.0;      
     if(x < 10) return (vsip_scalar_f) log(x + sqrt(a - 1.0));
     z = 1.0/a;
     return (vsip_scalar_f)(log(2.0 * x) - z * (C1 + z * (C2 + z * (C3 + z * C4))));
}

/*******************************************************************/     
static
void 
VI_cvlog_f(vsip_cvview_f *a,vsip_cvview_f *r)
{ 
     /* register */ vsip_length n = r->length;
     vsip_stride cast = a->block->cstride;
     vsip_stride crst = r->block->cstride;
     vsip_scalar_f *apr = (vsip_scalar_f *)((a->block->R->array) + cast * a->offset),
                   *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
     vsip_scalar_f *api = (vsip_scalar_f *)((a->block->I->array) + cast * a->offset),
                   *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
     /* register */ vsip_stride ast = (cast * a->stride),
                                rst = (crst * r->stride);
     vsip_scalar_f arg = 0;
     while(n-- > 0){
         arg  = (vsip_scalar_f)atan2(*api , *apr);
         *rpr = (vsip_scalar_f)log(sqrt(*apr * *apr + *api * *api));
         *rpi = arg;
        apr += ast; api += ast;
        rpr += rst; rpi += rst;
    }
}

/*******************************************************************/     
static
void 
VI_rcvacosh_f(vsip_vview_f *x, vsip_cvview_f *r){
     void VI_cvlog_f(vsip_cvview_f*,vsip_cvview_f*);
     {
         vsip_length n = r->length;
         vsip_stride r_str = r->stride * r->block->cstride;
         vsip_stride x_str = x->stride * x->block->rstride;
         vsip_stride r_off = r_str * r->offset;
         vsip_stride x_off = x_str * x->offset;
         vsip_scalar_f *x_p = x->block->array + x_off,
                       *rp_r = (vsip_scalar_f*)(r->block->R->array + r_off),
                       *rp_i = (vsip_scalar_f*)(r->block->I->array + r_off);
            
         while(n-- > 0){
                    *rp_r = *x_p * *x_p - (vsip_scalar_f)1.0;
                    *rp_i = (vsip_scalar_f)0;
                     rp_r += r_str; rp_i += r_str; x_p += x_str;
         }
      }
     VI_cvsqrt_f(r,r);
     VI_rcvadd_f(x,r,r);
     VI_cvlog_f(r,r);  
     return;
}
               
/*******************************************************************/     
static
void 
VI_cvcosh_f(vsip_cvview_f *x, vsip_cvview_f *r){
     vsip_length n = r->length;
     vsip_stride stx = x->block->cstride * x->stride,
                 str = r->block->cstride * r->stride;
     vsip_scalar_f *x_pr = (vsip_scalar_f*)(x->block->R->array + stx * x->offset),
                   *x_pi = (vsip_scalar_f*)(x->block->I->array + stx * x->offset),
                   *r_pr = (vsip_scalar_f*)(r->block->R->array + str * r->offset),
                   *r_pi = (vsip_scalar_f*)(r->block->I->array + str * r->offset),
                    tmp, mag, maginv;
     while(n-- > 0){
        mag    =  (vsip_scalar_f)0.50 * VSIP_EXP_F(*x_pr); 
        maginv =  (vsip_scalar_f)0.25 / mag;
        tmp    = (mag + maginv) * VSIP_COS_F(*x_pi); 
        *r_pi  = (mag - maginv) * VSIP_SIN_F(*x_pi);
        *r_pr  = tmp;
        x_pr += stx; r_pr += str;
        x_pi += stx; r_pi += str;
     }
}

/*******************************************************************/     
static
void 
VI_vfreqswap_f(vsip_vview_f *a)
{ 
   vsip_length n;
   vsip_length n2 = (a->length / 2);
   vsip_scalar_f *a_p = a->block->array + a->offset * a->block->rstride,
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

vsip_vview_f* (vsip_vcreate_cheby_f)(
          vsip_length nf, 
          vsip_scalar_f ripple,
          vsip_memory_hint hint) {
    vsip_vview_f *window = VI_vcreate_f(nf,hint);
    int odd = 0;
    vsip_length n2 = 0;
    vsip_scalar_f dp     = 0.0,
                  df     = 0.0,
                  x0     = 0.0, 
                  alpha  = 0.0, 
                  beta   = 0.0;
    vsip_cvview_f *wf    = VI_cvcreate_f(nf,hint),
                  *Cfoo  = VI_cvcreate_f(nf,hint);
    vsip_vview_f *f      = VI_vcreate_f(nf,hint),
                 *x      = VI_vcreate_f(nf,hint), 
                 *tmp    = VI_vcreate_f(nf,hint),
                 *nottmp = VI_vcreate_f(nf,hint);

    vsip_vview_f wwfR;
    vsip_vview_f *wfR = VI_vrealview_f(wf,&wwfR);
    vsip_vview_f RRefoo; 
    vsip_vview_f *Refoo = VI_vrealview_f(Cfoo,&RRefoo);

    /* check for malloc errors, destroy everything and return null on failure */
    if((wf == NULL) | (Cfoo == NULL) | (f == NULL) | (x == NULL) | 
       (tmp == NULL) | (wfR == NULL) | (Refoo == NULL) | 
       (window == NULL) | (nottmp == NULL)){
            VI_valldestroy_f(x);
            VI_valldestroy_f(f);
            VI_valldestroy_f(tmp);
            VI_cvalldestroy_f(wf);
            VI_cvalldestroy_f(Cfoo);
            VI_valldestroy_f(nottmp);
            VI_valldestroy_f(window);
            return (vsip_vview_f*)NULL;
    }
    VI_cvfill_f(wf->block->a_zero,wf); /* zero fill */
    dp    = VSIP_EXP10_F(-ripple/20.0); /*dp = 10.^(-ripple/20);*/
    odd   = ((int)nf) % 2;  /*odd = rem(nf,2);*/
    n2    = VSIP_FLOOR_F((vsip_scalar_f)nf/2.0); /*n2 = fix(nf/2);*/
            /*df = acos(1/cosh(acosh((1+dp)/dp)/(nf-1)))/pi;*/
    df    = (vsip_scalar_f)VSIP_ACOS_F(1.0/VSIP_COSH_F(VI_acosh_f(((vsip_scalar_f)1.0 + dp)/dp) / ((vsip_scalar_f)nf - 1.0)))/cheby_PI;
            /*x0 = (3-cos(2*pi*df))/(1.+cos(2*pi*df));*/
    x0    = (vsip_scalar_f)((3. - VSIP_COS_F(TWOPI * df))/(1. + VSIP_COS_F(TWOPI * df)));
    alpha = (x0 + (vsip_scalar_f)1.0) / (vsip_scalar_f)2.; /*alpha = (x0 + 1)/2;*/
    beta  = (x0 - (vsip_scalar_f)1.0) / (vsip_scalar_f)2.; /*beta = (x0 - 1)/2;*/
    VI_vramp_f(((vsip_scalar_f)0.0),((vsip_scalar_f)1.0/((vsip_scalar_f)nf)),f); /*k = (0:nf-1);f = k/nf;*/
    /* x = alpha*cos(2*pi*f) + beta; */
    {
      vsip_length n = nf;
      vsip_scalar_f *f_p = f->block->array + f->offset,
                    *x_p = x->block->array + x->offset;
      while(n-- > 0){
        *x_p = alpha * (vsip_scalar_f)VSIP_COS_F(TWOPI * *f_p) + beta;
         x_p += x->stride; f_p += f->stride; 
      }
    } 
    /* END x = alpha*cos(2*pi*f) + beta; */

    /*tmp = (mag(x) > 1); */
    {
      vsip_length n = nf;
      vsip_scalar_f *x_p   = x->block->array   + x->offset,
                    *tmp_p = tmp->block->array + tmp->offset;
      while(n-- > 0){
        *tmp_p = (vsip_scalar_f)((((*x_p >= 0) ? *x_p : - *x_p) > 1) ? 1.0 : 0.0);
         x_p += x->stride; tmp_p += tmp->stride;
      }
    }
    /* END tmp = (mag(x) > 1); */

    /* wf = dp*(tmp.*(cosh((((vsip_scalar_f)nf-1.0)/2).*acosh(x)))+
                (1-tmp).*cos((((vsip_scalar_f)nf-1.0)/2).*acos(x)));*/
    { 
      VI_svsub_f(1.0,tmp,nottmp);
      VI_vclip_f(x,-1.0,1.0,-1.0,1.0,wfR); /* modified to handle x out side of range of acos*/
      /* ensures that for x > 1 default return value of acos is zero */
      VI_vacos_f(wfR,Refoo);
      VI_svmul_f(((vsip_scalar_f)nf-(vsip_scalar_f)1.0)/(vsip_scalar_f)2.0,Refoo,Refoo);
      VI_vcos_f(Refoo,Refoo);
      VI_vmul_f(nottmp,Refoo,wfR);
  
      VI_rcvacosh_f(x,Cfoo);

      VI_rscvmul_f(((vsip_scalar_f)nf - (vsip_scalar_f)1.0)/(vsip_scalar_f)2.0,Cfoo,Cfoo);
      VI_cvcosh_f(Cfoo,Cfoo);
      VI_rcvmul_f(tmp,Cfoo,Cfoo); 
      VI_cvadd_f(Cfoo,wf,wf);
      VI_rscvmul_f(dp,wf,wf);
    }
    /* END wf = dp*(tmp.*(cosh(((nf-1)/2).*acosh(x)))+
                (1-tmp).*cos(((nf-1)/2).*acos(x)));*/

    if(!odd ){ /* if (~odd) */
      /*wf = real(wf).*exp(-j*pi*f);*/ 
      { 
        VI_svmul_f((vsip_scalar_f)(-cheby_PI),f,f); 
        VI_veuler_f(f,Cfoo);
        VI_rcvmul_f(wfR,Cfoo,wf);
      }
      /*END wf = real(wf).*exp(-j*pi*f);*/

      /* wf(n2+1:nf) = -wf(n2+1:nf); */
      { 
        vsip_stride str = wf->block->cstride;
        vsip_length n = n2;
        vsip_scalar_f *wf_rp = (vsip_scalar_f*)(wf->block->R->array + str * n); 
        vsip_scalar_f *wf_ip = (vsip_scalar_f*)(wf->block->I->array + str * n); 
        while(n-- > 0){ *wf_rp = - *wf_rp; wf_rp += str; *wf_ip = - *wf_ip; wf_ip += str;}
      }
      /*END wf(n2+1:nf) = -wf(n2+1:nf);*/
    }/* END if (~odd) */

    {/* wt = fft(wf); */
      vsip_fft_f* fftplan = vsip_ccfftip_create_f(nf,(vsip_scalar_f)(1.0/(vsip_scalar_f)nf),VSIP_FFT_FWD,0,VSIP_ALG_NOISE);
      vsip_ccfftip_f(fftplan,wf);
      {/* wt = wt(1:nf)/wt(1) */
        vsip_cscalar_f scale;
        vsip_scalar_f magsq;
        VI_CVGETP_F(wf,0);
        scale = VI_CVGET_F(wf);
        scale.i = -scale.i;
        magsq = scale.i * scale.i + scale.r * scale.r;
        scale.i /= magsq; scale.r /= magsq;
        VI_csvmul_f(scale,wf,wf);
      }            
      vsip_fft_destroy_f(fftplan);
    }/*END wt = fft(wf); */

    VI_vcopy_f_f(wfR, window);
    VI_vfreqswap_f(window);
    VI_valldestroy_f(x);
    VI_valldestroy_f(f);
    VI_valldestroy_f(tmp);
    VI_valldestroy_f(nottmp);
    VI_cvalldestroy_f(wf);
    VI_cvalldestroy_f(Cfoo);
    return window;
}
