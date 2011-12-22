/* Created by RJudd August 2, 2002 */
/* SPAWARSYSCEN */
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
/* $Id: VI_fft_building_blocks_f.h,v 2.6 2009/12/26 19:18:11 judd Exp $ */
#ifndef VI_FFT_BUILDING_BLOCKS_F_H
#define VI_FFT_BUILDING_BLOCKS_F_H 1

/* constants */
#define C3PC  ((vsip_scalar_f)-1.50 ) /* -(1+cos(2pi/3) */
#define C3PS  ((vsip_scalar_f)+0.86602540378443864676372317075293618347140262690519) /* sin(2pi/3) or sqrt(3)/2 */

#define C5c1 ((vsip_scalar_f)-1.250) /* (cos(2 * pi/5) + cos(4*pi/5))/2 -1 */
#define C5c2 ((vsip_scalar_f)+0.55901699437494742410229341718281905886015458990288) /* (cos(2 * pi/5) - cos(4*pi/5))/2 */
#define C5c3 ((vsip_scalar_f)+0.58778525229247312916870595463907276859765243764315) /* sin(4 * pi/5) */
#define C5c4 ((vsip_scalar_f)+1.5388417685876267012851452880184549120033510717689) /* sin(2 * pi/5) + sin(4 * pi/5) */
#define C5c5 ((vsip_scalar_f)+0.36327126400268044294773337874030937480804619648261) /* sin(2*pi/5) - sin(4*pi/5) */

#define C7c1 ((vsip_scalar_f)-1.16666666666666666666666666666666666666666666666667) /*C7c1=-1 + (cos(2 * pi/7) + cos(4 * pi/7) + cos(6 * pi/7))/3*/
#define C7c2 ((vsip_scalar_f)+0.79015646852540019719167155067090647729894139756307) /*C7c2=(2 * cos(2 * pi/7) - cos(4 * pi/7) - cos(6 * pi/7))/3*/
#define C7c3 ((vsip_scalar_f)+0.055854267289647737622235897830128092799688902097878) /*C7c3=(cos(2 * pi/7) - 2 * cos(4 * pi/7) + cos(6 * pi/7))/3*/
#define C7c4 ((vsip_scalar_f)+0.73430220123575245956943565284077838449925249546519) /*C7c4=(cos(2 * pi/7) + cos(4 * pi/7) - 2 * cos(6 * pi/7))/3*/
#define C7c5 ((vsip_scalar_f)+0.440958551844098431750269292273210070951709863847085) /*C7c5=((sin(2 * pi/7) + sin(4 * pi/7) - sin(6 * pi/7))/3) */
#define C7c6 ((vsip_scalar_f)+0.34087293062393137695817523440084767928062465486161) /*C7c6=(2 * sin(2 * pi/7) - sin(4 * pi/7) + sin(6 * pi/7))/3*/
#define C7c7 ((vsip_scalar_f)-0.53396936033772517526786239072072114628107593677292) /*C7c7=( sin(2 * pi/7) - 2 * sin(4 * pi/7) - sin(6 * pi/7))/3*/
#define C7c8 ((vsip_scalar_f)+0.87484229096165655222603762512156882556170059163453) /*C7c8=( sin(2 * pi/7) + sin(4 * pi/7) + 2 * sin(6 * pi/7))/3*/

#define C8c1 ((vsip_scalar_f)+0.70710678118654752440084436210484903928483593768847) /*cos(pi/4)*/

#define CVCOPY_F(a,r) { \
      vsip_length n =  r->length; \
      vsip_stride cast = a->block->cstride, crst = r->block->cstride; \
      vsip_scalar_f *apr = (vsip_scalar_f *)((a->block->R->array) + cast * a->offset),\
                    *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);\
      vsip_scalar_f *api = (vsip_scalar_f *)((a->block->I->array) + cast * a->offset),\
                    *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);\
      vsip_stride ast = (cast * a->stride), rst = (crst * r->stride);\
      while(n-- > 0){ *rpr = *apr; *rpi = *api; apr += ast; api += ast; rpr += rst; rpi += rst;\
      }}

/*========================================================*/
/* dft */
/* Adapted For VSIP from Fortan example */
/* Burrus and Parks,"DFT/FFT and Convolution Algorithms" */
/******************************************************************/
static
void 
VI_dft_f(void *tfft) {
  vsip_fft_f *fft = (vsip_fft_f*) tfft;
  vsip_cvview_f *a = fft->x;
  vsip_scalar_vi i = 0, j = 0, k = 0;
  vsip_scalar_vi N = (vsip_scalar_vi)a->length;
  vsip_cvview_f *b = fft->wt,
                *c   = fft->temp;
  vsip_stride cast = a->block->cstride;
  vsip_stride cbst = b->block->cstride;
  vsip_stride ccst = c->block->cstride;
  
  vsip_stride ast = (cast * a->stride),
              bst = (cbst * fft->N / N),
              cst = (ccst * c->stride);
  vsip_scalar_f *aprp = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset),
                *apr,
                *bpr  = (vsip_scalar_f*) ((b->block->R->array) + cbst * b->offset),
                *tbpr,
                *cpr = (vsip_scalar_f*) ((c->block->R->array) + ccst * c->offset);
  vsip_scalar_f *apip = (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset),
                *api,
                *bpi  = (vsip_scalar_f*) ((b->block->I->array) + cbst * b->offset),
                *tbpi,
                *cpi = (vsip_scalar_f*) ((c->block->I->array) + cbst * c->offset);
  b->length = N;
  c->length = N;
  for(j=0; j<N; j++){
    register vsip_scalar_f t_r=0;
    register vsip_scalar_f t_i=0;
    apr = aprp; api = apip;
    t_r += (*apr * *bpr - *api * *bpi);
    t_i += (*api * *bpr + *apr * *bpi);
    k = 0;
    apr += ast; api += ast;
    for(i=1; i<N; i++){
      k += j;
      if(k > N-1) k -= N;
      tbpr = bpr + k * bst;
      tbpi = bpi + k * bst;
      t_r += (*apr * *tbpr - *api * *tbpi); 
      t_i += (*api * *tbpr + *apr * *tbpi);;
      apr += ast; api += ast;
    }
    *cpr = t_r; *cpi = t_i;
    cpr += cst; cpi += cst;
  }
  CVCOPY_F(c,a);
  return;
} 

/*========================================================*/
/* Created by RJudd August 27, 1998*/
/* SPAWARSYSCEN D881 */

static
void 
VI_fft2_f(void *tfft) {
   vsip_fft_f* fft = (vsip_fft_f*) tfft;
   vsip_scalar_f *xp_r = fft->xp_r,
                 *xp_i = fft->xp_i; 
   vsip_scalar_vi xpst = fft->xpst;
   vsip_cscalar_f a0, a1; 
   vsip_cscalar_f T1;
   a0.r = *xp_r; a0.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a1.r = *xp_r; a1.i = *xp_i;
   T1.r = a0.r - a1.r; T1.i = a0.i - a1.i;
   *xp_r = T1.r; 
   *xp_i = T1.i; 
    xp_r -= xpst; xp_i -= xpst;
   *xp_r = a0.r + a1.r; 
   *xp_i = a0.i + a1.i;
   return;
}

/*========================================================*/
/* Created by RJudd August 27, 1998*/
/* SPAWARSYSCEN D881 */
/* base 2 building block */
/* same as fft2, here for convenience */

static
void 
VI_ifft2_f(void *tfft) {
   vsip_fft_f* fft = (vsip_fft_f*) tfft;
   vsip_scalar_f *xp_r = fft->xp_r,
                 *xp_i = fft->xp_i; 
   vsip_scalar_vi xpst = fft->xpst;
   vsip_cscalar_f a0, a1; 
   vsip_cscalar_f T1;
   a0.r = *xp_r; a0.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a1.r = *xp_r; a1.i = *xp_i;
   T1.r = a0.r - a1.r; T1.i = a0.i - a1.i;
   *xp_r = T1.r; 
   *xp_i = T1.i; 
    xp_r -= xpst; xp_i -= xpst;
   *xp_r = a0.r + a1.r; 
   *xp_i = a0.i + a1.i;
   return;
}

/*========================================================*/
/* Created by RJudd August 27, 1998*/
/* SPAWARSYSCEN D881 */
/* Base 3 building Block */
static
void 
VI_fft3_f(void *tfft) {
   vsip_fft_f* fft = (vsip_fft_f*) tfft;
   vsip_scalar_f *xp_r = fft->xp_r,
                 *xp_i = fft->xp_i; 
   vsip_scalar_vi xpst = fft->xpst;
   vsip_cscalar_f a0,b0,d0;
   vsip_cscalar_f a1,b1,c1;
   vsip_cscalar_f a2,b2,c2;
   a0.r = *xp_r; a0.i = *xp_i; xp_r += xpst; xp_i += xpst; 
   a1.r = *xp_r; a1.i = *xp_i; xp_r += xpst; xp_i += xpst; 
   a2.r = *xp_r; a2.i = *xp_i;
   b1.r = a1.r + a2.r; b1.i = a1.i + a2.i;
   b2.r = a1.r - a2.r; b2.i = a1.i - a2.i;
   b0.r = a0.r + b1.r; b0.i = a0.i + b1.i;
   c1.r = C3PC * b1.r; c1.i = C3PC * b1.i;
   c2.r = C3PS * b2.i;  c2.i = C3PS * b2.r;
   d0.r = b0.r + c1.r; d0.i = b0.i + c1.i;
   *xp_r = d0.r - c2.r; *xp_i = d0.i + c2.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d0.r + c2.r; *xp_i = d0.i - c2.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = b0.r; *xp_i = b0.i;
   return;
}

/*========================================================*/
/* Created by RJudd August 27, 1998*/
/* SPAWARSYSCEN D881 */
/* Base 3 building block */
/* Based on Winograd 3-point FFT */
/* "Handbook of Real-Time Fast Fourier Transforms */
/* Winthrop Smith, Joanne Smith */

static
void 
VI_ifft3_f(void *tfft) {
   vsip_fft_f* fft = (vsip_fft_f*) tfft;
   vsip_scalar_f *xp_r = fft->xp_r,
                 *xp_i = fft->xp_i;
   vsip_scalar_vi xpst = fft->xpst;
   vsip_cscalar_f a0,b0,d0;
   vsip_cscalar_f a1,b1,c1;
   vsip_cscalar_f a2,b2,c2;
   a0.r = *xp_r; a0.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a1.r = *xp_r; a1.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a2.r = *xp_r; a2.i = *xp_i;
   b1.r = a1.r + a2.r; b1.i = a1.i + a2.i;
   b2.r = a1.r - a2.r; b2.i = a1.i - a2.i;
   b0.r = a0.r + b1.r; b0.i = a0.i + b1.i;
   c1.r = C3PC * b1.r; c1.i = C3PC * b1.i;
   c2.r = -C3PS * b2.i; c2.i = -C3PS * b2.r;
   d0.r = b0.r + c1.r; d0.i = b0.i + c1.i;
   *xp_r = d0.r - c2.r; *xp_i = d0.i + c2.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d0.r + c2.r; *xp_i = d0.i - c2.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = b0.r; *xp_i = b0.i;
   return;
}

/*========================================================*/
/* Created by RJudd August 27, 1998*/
/* SPAWARSYSCEN D881 */
/* Base 4 building block */
static
void 
VI_fft4_f(void *tfft) {
   vsip_fft_f* fft = (vsip_fft_f*) tfft;
   vsip_scalar_f *xp_r = fft->xp_r,
                 *xp_i = fft->xp_i;
   vsip_scalar_vi xpst = fft->xpst;
   vsip_cscalar_f a0,a1,a2,a3;
   vsip_cscalar_f b0,b1,b2,b3;

   a0.r = *xp_r; a0.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a1.r = *xp_r; a1.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a2.r = *xp_r; a2.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a3.r = *xp_r; a3.i = *xp_i;
   b0.r = a0.r + a2.r; b0.i = a0.i + a2.i;
   b1.r = a0.r - a2.r; b1.i = a0.i - a2.i;
   b2.r = a1.r + a3.r; b2.i = a1.i + a3.i;
   b3.r = a1.r - a3.r; b3.i = a1.i - a3.i;
   *xp_r = b1.r - b3.i; *xp_i = b1.i + b3.r; xp_r -= xpst; xp_i -= xpst;
   *xp_r = b0.r - b2.r; *xp_i = b0.i - b2.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = b1.r + b3.i; *xp_i = b1.i - b3.r; xp_r -= xpst; xp_i -= xpst;
   *xp_r = b0.r + b2.r; *xp_i = b0.i + b2.i;
   return;
}

/*========================================================*/
/* Created by RJudd August 27, 1998*/
/* SPAWARSYSCEN D881 */
/* 4 point building block */
/* Based on 4-point FFT */
/* "Handbook of Real-Time Fast Fourier Transforms */ 
/* Winthrop Smith, Joanne Smith */

static
void 
VI_ifft4_f(void *tfft) {
   vsip_fft_f* fft = (vsip_fft_f*) tfft;
   vsip_scalar_f *xp_r = fft->xp_r,
                 *xp_i = fft->xp_i;
   vsip_scalar_vi xpst = fft->xpst;
   vsip_cscalar_f a0,a1,a2,a3;
   vsip_cscalar_f b0,b1,b2,b3;
   a0.r = *xp_r; a0.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a1.r = *xp_r; a1.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a2.r = *xp_r; a2.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a3.r = *xp_r; a3.i = *xp_i;
   b0.r = a0.r + a2.r; b0.i = a0.i + a2.i;
   b1.r = a0.r - a2.r; b1.i = a0.i - a2.i;
   b2.r = a1.r + a3.r; b2.i = a1.i + a3.i;
   b3.r = a1.r - a3.r; b3.i = a1.i - a3.i;
   *xp_r = b1.r + b3.i; *xp_i = b1.i - b3.r; xp_r -= xpst; xp_i -= xpst;
   *xp_r = b0.r - b2.r; *xp_i = b0.i - b2.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = b1.r - b3.i; *xp_i = b1.i + b3.r; xp_r -= xpst; xp_i -= xpst;
   *xp_r = b0.r + b2.r; *xp_i = b0.i + b2.i;
   return;
}

/*========================================================*/
/* Created By RJudd August 26, 1998 */
/* SPAWARSYSCEN D881 */
/* Base 5 building block */
/* Based on Winograd 5-point FFT */
/* "Handbook of Real-Time Fast Fourier Transforms */
/* Winthrop Smith, Joanne Smith */
static
void 
VI_fft5_f(void *tfft) {
   vsip_fft_f* fft = (vsip_fft_f*) tfft;
   vsip_scalar_f *xp_r = fft->xp_r,
                 *xp_i = fft->xp_i; 
   vsip_scalar_vi xpst = fft->xpst;
   vsip_cscalar_f a0,a1,a2,a3,a4 ;
   vsip_cscalar_f b1,b2,b3,b4;
   vsip_cscalar_f c1,c3,c5;
   vsip_cscalar_f d0,d1,d2,d4;
   vsip_cscalar_f e1,e3,e5;
   vsip_cscalar_f f1,f2,f3,f4;
   a0.r = *xp_r; a0.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a1.r = *xp_r; a1.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a2.r = *xp_r; a2.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a3.r = *xp_r; a3.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a4.r = *xp_r; a4.i = *xp_i;

     b1.r = a1.r + a4.r; b1.i = a1.i + a4.i;
     b2.r = a1.r - a4.r; b2.i = a1.i - a4.i;
     b3.r = a2.r + a3.r; b3.i = a2.i + a3.i;
     b4.r = a3.r - a2.r; b4.i = a3.i - a2.i;
     c1.r = b1.r + b3.r; c1.i = b1.i + b3.i;
     c3.r = b1.r - b3.r; c3.i = b1.i - b3.i;
     c5.r = b2.r + b4.r; c5.i = b2.i + b4.i;
     d0.r = c1.r + a0.r; d0.i = c1.i + a0.i;
/* step 2 */
     d1.r = c1.r * C5c1; d1.i = c1.i * C5c1;
     e3.r = c3.r * C5c2; e3.i = c3.i * C5c2;
     e5.r = c5.r * C5c3; e5.i = c5.i * C5c3;
     d2.r = b2.i * C5c4; d2.i = -(b2.r * C5c4);
     d4.r = -(b4.i * C5c5); d4.i = b4.r * C5c5;
/* step 3 */
     e1.r = d1.r + d0.r; e1.i = d1.i + d0.i;
     f1.r = e1.r + e3.r; f1.i = e1.i + e3.i;
     f2.r = d2.r - e5.i; f2.i = d2.i + e5.r;
     f3.r = e1.r - e3.r; f3.i = e1.i - e3.i;
     f4.r = d4.r - e5.i; f4.i = d4.i + e5.r;
/* step 4 */
   *xp_r = f1.r - f2.r; *xp_i = f1.i - f2.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = f3.r + f4.r; *xp_i = f3.i + f4.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = f3.r - f4.r; *xp_i = f3.i - f4.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = f1.r + f2.r; *xp_i = f1.i + f2.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d0.r; *xp_i = d0.i;
   return;
}

/*========================================================*/
/* Created By RJudd August 26, 1998 */
/* SPAWARSYSCEN D881 */
/* 5 point building block */
/* Based on Winograd 5-point FFT */
/* "Handbook of Real-Time Fast Fourier Transforms */
/* Winthrop Smith, Joanne Smith */

static
void 
VI_ifft5_f(void *tfft) {
   vsip_fft_f* fft = (vsip_fft_f*) tfft;
   vsip_scalar_f *xp_r = fft->xp_r,
                 *xp_i = fft->xp_i;
   vsip_scalar_vi xpst = fft->xpst;
   vsip_cscalar_f a0,a1,a2,a3,a4 ;
   vsip_cscalar_f b1,b2,b3,b4;
   vsip_cscalar_f c1,c3,c5;
   vsip_cscalar_f d0,d1,d2,d4;
   vsip_cscalar_f e1,e3,e5;
   vsip_cscalar_f f1,f2,f3,f4;
   a0.r = *xp_r; a0.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a1.r = *xp_r; a1.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a2.r = *xp_r; a2.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a3.r = *xp_r; a3.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a4.r = *xp_r; a4.i = *xp_i;
/* step 1 */
   b1.r = a1.r + a4.r; b1.i = a1.i + a4.i; 
   b2.r = a1.r - a4.r; b2.i = a1.i - a4.i;
   b3.r = a2.r + a3.r; b3.i = a2.i + a3.i;
   b4.r = a3.r - a2.r; b4.i = a3.i - a2.i;
   c1.r = b1.r + b3.r; c1.i = b1.i + b3.i;
   c3.r = b1.r - b3.r; c3.i = b1.i - b3.i; 
   c5.r = b2.r + b4.r; c5.i = b2.i + b4.i; 
   d0.r = c1.r + a0.r; d0.i = c1.i + a0.i;
   /* step 2 */
   d1.r = c1.r * C5c1; d1.i = c1.i * C5c1; 
   e3.r = c3.r * C5c2; e3.i = c3.i * C5c2; 
   e5.r = c5.r * (-C5c3); e5.i = c5.i * (-C5c3); 
   d2.r = b2.i * (-C5c4); d2.i = b2.r * C5c4;
   d4.r = b4.i * C5c5; d4.i = -(b4.r * C5c5); 
   /* step 3 */
   e1.r = d1.r + d0.r; e1.i = d1.i + d0.i; 
   f1.r = e1.r + e3.r; f1.i = e1.i + e3.i; 
   f2.r = d2.r - e5.i; f2.i = d2.i + e5.r; 
   f3.r = e1.r - e3.r; f3.i = e1.i - e3.i; 
   f4.r = d4.r - e5.i; f4.i = d4.i + e5.r;
   /* step 4 */
   *xp_r = f1.r - f2.r; *xp_i = f1.i - f2.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = f3.r + f4.r; *xp_i = f3.i + f4.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = f3.r - f4.r; *xp_i = f3.i - f4.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = f1.r + f2.r; *xp_i = f1.i + f2.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d0.r; *xp_i = d0.i;
   return;
}

/*========================================================*/
/* Created By RJudd August 26, 1998 */
/* SPAWARSYSCEN D881 */
/* Base 7 building block */
/* Based on Winograd 7-point FFT */
/* "Handbook of Real-Time Fast Fourier Transforms */
/* Winthrop Smith, Joanne Smith */
static
void 
VI_fft7_f(void *tfft) {
   vsip_fft_f* fft = (vsip_fft_f*) tfft;
   vsip_scalar_f *xp_r = fft->xp_r,
   *xp_i = fft->xp_i; 
   vsip_scalar_vi xpst = fft->xpst;
   vsip_cscalar_f a0,a1,a2,a3,a4,a5,a6;
   vsip_cscalar_f b1,b2,b3,b4,b5,b6;
   vsip_cscalar_f c1,c2,c3,c4,c5,c6,c7,c8;
   vsip_cscalar_f d1,d2;
   vsip_cscalar_f e0,e1,e2,e3,e4,e5,e6,e7,e8;
   vsip_cscalar_f f1,f2,f3,f4;
   vsip_cscalar_f g1,g2,g3,g4,g5,g6;
   vsip_cscalar_f h1,h2,h3;
   a0.r = *xp_r; a0.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a1.r = *xp_r; a1.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a2.r = *xp_r; a2.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a3.r = *xp_r; a3.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a4.r = *xp_r; a4.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a5.r = *xp_r; a5.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a6.r = *xp_r; a6.i = *xp_i;
   /* step 1 */
   b1.r = a1.r + a6.r; b1.i = a1.i + a6.i;
   b2.r = a1.r - a6.r; b2.i = a1.i - a6.i;
   b3.r = a4.r + a3.r; b3.i = a4.i + a3.i;
   b4.r = a4.r - a3.r; b4.i = a4.i - a3.i;
   b5.r = a2.r + a5.r; b5.i = a2.i + a5.i;
   b6.r = a2.r - a5.r; b6.i = a2.i - a5.i;
   /* step 2 */
   c1.r = b1.r + b3.r; c1.i = b1.i + b3.i;
   c2.r = b3.r - b5.r; c2.i = b3.i - b5.i;
   c3.r = b1.r - b3.r; c3.i = b1.i - b3.i;
   c4.r = b5.r - b1.r; c4.i = b5.i - b1.i;
   c5.r = b2.r + b4.r; c5.i = b2.i + b4.i;
   c6.r = b2.r - b4.r; c6.i = b2.i - b4.i;
   c7.r = b4.r - b6.r; c7.i = b4.i - b6.i;
   c8.r = b6.r - b2.r; c8.i = b6.i - b2.i;
   /* step 3 */
   d1.r = b5.r + c1.r; d1.i = b5.i + c1.i;
   d2.r = b6.r + c5.r;  d2.i = b6.i + c5.i;
   e0.r = a0.r + d1.r; e0.i = a0.i + d1.i;
   /* step 4 */
   e1.r = d1.r * C7c1; e1.i = d1.i * C7c1;
   e2.r = c3.r * C7c2; e2.i = c3.i * C7c2;
   e3.r = c2.r * C7c3; e3.i = c2.i * C7c3;
   e4.r = c4.r * C7c4; e4.i = c4.i * C7c4;
   e5.r = -(d2.i * C7c5); e5.i = d2.r * C7c5;
   e6.r = -(c6.i * C7c6); e6.i = c6.r * C7c6;
   e7.r = -(c7.i * C7c7); e7.i = c7.r * C7c7;
   e8.r = -(c8.i * C7c8); e8.i = c8.r * C7c8;
   /* step 5 */
   f1.r = e0.r + e1.r; f1.i = e0.i + e1.i;
   f2.r = e5.r + e6.r; f2.i = e5.i + e6.i;
   f3.r = e5.r - e6.r; f3.i = e5.i - e6.i;
   f4.r = e5.r - e7.r; f4.i = e5.i - e7.i;
   /* step 6 */
   g1.r = f1.r + e2.r; g1.i = f1.i + e2.i;
   g2.r = f1.r - e2.r; g2.i = f1.i - e2.i;
   g3.r = f1.r - e3.r; g3.i = f1.i - e3.i;
   g4.r = f2.r + e7.r; g4.i = f2.i + e7.i;
   g5.r = f3.r - e8.r; g5.i = f3.i - e8.i;
   g6.r = f4.r + e8.r; g6.i = f4.i + e8.i;
   /* step 7 */
   h1.r = g1.r + e3.r; h1.i = g1.i + e3.i;
   h2.r = g2.r - e4.r; h2.i = g2.i - e4.i;
   h3.r = g3.r + e4.r; h3.i = g3.i + e4.i;
   /* step 8 */
   *xp_r = h1.r + g4.r; *xp_i = h1.i + g4.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = h2.r + g5.r; *xp_i = h2.i + g5.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = h3.r - g6.r; *xp_i = h3.i - g6.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = h3.r + g6.r; *xp_i = h3.i + g6.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = h2.r - g5.r; *xp_i = h2.i - g5.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = h1.r - g4.r; *xp_i = h1.i - g4.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = e0.r; *xp_i = e0.i;
   return;
}

/*========================================================*/
/* Created By RJudd August 26, 1998 */
/* SPAWARSYSCEN D881 */
/* 7-point building block */
/* Based on Winograd 7-point FFT */
/* "Handbook of Real-Time Fast Fourier Transforms */
/* Winthrop Smith, Joanne Smith */

static
void 
VI_ifft7_f(void *tfft) {
   vsip_fft_f* fft = (vsip_fft_f*) tfft;
   vsip_scalar_f *xp_r = fft->xp_r,
                 *xp_i = fft->xp_i;
   vsip_scalar_vi xpst = fft->xpst;
   vsip_cscalar_f a0,a1,a2,a3,a4,a5,a6;
   vsip_cscalar_f b1,b2,b3,b4,b5,b6;
   vsip_cscalar_f c1,c2,c3,c4,c5,c6,c7,c8;
   vsip_cscalar_f d1,d2;
   vsip_cscalar_f e0,e1,e2,e3,e4,e5,e6,e7,e8;
   vsip_cscalar_f f1,f2,f3,f4;
   vsip_cscalar_f g1,g2,g3,g4,g5,g6;
   vsip_cscalar_f h1,h2,h3;
   a0.r = *xp_r; a0.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a1.r = *xp_r; a1.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a2.r = *xp_r; a2.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a3.r = *xp_r; a3.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a4.r = *xp_r; a4.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a5.r = *xp_r; a5.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a6.r = *xp_r; a6.i = *xp_i;
/* step 1 */
     b1.r = a1.r + a6.r; b1.i = a1.i + a6.i; 
     b2.r = a1.r - a6.r; b2.i = a1.i - a6.i;
     b3.r = a4.r + a3.r; b3.i = a4.i + a3.i; 
     b4.r = a4.r - a3.r; b4.i = a4.i - a3.i; 
     b5.r = a2.r + a5.r; b5.i = a2.i + a5.i; 
     b6.r = a2.r - a5.r; b6.i = a2.i - a5.i; 
/* step 2 */
   c1.r = b1.r + b3.r; c1.i = b1.i + b3.i; 
   c2.r = b3.r - b5.r; c2.i = b3.i - b5.i; 
   c3.r = b1.r - b3.r; c3.i = b1.i - b3.i; 
   c4.r = b5.r - b1.r; c4.i = b5.i - b1.i; 
   c5.r = b2.r + b4.r; c5.i = b2.i + b4.i; 
   c6.r = b2.r - b4.r; c6.i = b2.i - b4.i; 
   c7.r = b4.r - b6.r; c7.i = b4.i - b6.i; 
   c8.r = b6.r - b2.r; c8.i = b6.i - b2.i;
/* step 3 */
     d1.r = b5.r + c1.r; d1.i = b5.i + c1.i;
     d2.r = b6.r + c5.r;  d2.i = b6.i + c5.i;
     e0.r = a0.r + d1.r; e0.i = a0.i + d1.i; 
/* step 4 */
   e1.r = d1.r * C7c1; e1.i = d1.i * C7c1;
   e2.r = c3.r * C7c2; e2.i = c3.i * C7c2;
   e3.r = c2.r * C7c3; e3.i = c2.i * C7c3;
   e4.r = c4.r * C7c4; e4.i = c4.i * C7c4;
   e5.r = d2.i * C7c5; e5.i = -(d2.r * C7c5);
   e6.r = c6.i * C7c6; e6.i = -(c6.r * C7c6);
   e7.r = c7.i * C7c7; e7.i = -(c7.r * C7c7);
   e8.r = c8.i * C7c8; e8.i = -(c8.r * C7c8);
/* step 5 */
   f1.r = e0.r + e1.r; f1.i = e0.i + e1.i;
   f2.r = e5.r + e6.r; f2.i = e5.i + e6.i;
   f3.r = e5.r - e6.r; f3.i = e5.i - e6.i;
   f4.r = e5.r - e7.r; f4.i = e5.i - e7.i;
/* step 6 */
   g1.r = f1.r + e2.r; g1.i = f1.i + e2.i;
   g2.r = f1.r - e2.r; g2.i = f1.i - e2.i;
   g3.r = f1.r - e3.r; g3.i = f1.i - e3.i;
   g4.r = f2.r + e7.r; g4.i = f2.i + e7.i;
   g5.r = f3.r - e8.r; g5.i = f3.i - e8.i;
   g6.r = f4.r + e8.r; g6.i = f4.i + e8.i;
/* step 7 */
   h1.r = g1.r + e3.r; h1.i = g1.i + e3.i;
   h2.r = g2.r - e4.r; h2.i = g2.i - e4.i;
   h3.r = g3.r + e4.r; h3.i = g3.i + e4.i;
/* step 8 */
   *xp_r = h1.r + g4.r; *xp_i = h1.i + g4.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = h2.r + g5.r; *xp_i = h2.i + g5.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = h3.r - g6.r; *xp_i = h3.i - g6.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = h3.r + g6.r; *xp_i = h3.i + g6.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = h2.r - g5.r; *xp_i = h2.i - g5.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = h1.r - g4.r; *xp_i = h1.i - g4.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = e0.r; *xp_i = e0.i;
   return;
}

/*========================================================*/
/* Created By RJudd August 26, 1998 */
/* SPAWARSYSCEN D881 */
/* Base 8 building block */
/* Based on Winograd 8-point FFT */
/* "Handbook of Real-Time Fast Fourier Transforms */
/* Winthrop Smith, Joanne Smith */

static
void 
VI_fft8_f(void *tfft) {
   vsip_fft_f* fft = (vsip_fft_f*) tfft;
   vsip_scalar_f *xp_r = fft->xp_r,
                 *xp_i = fft->xp_i; 
   vsip_scalar_vi xpst = fft->xpst;
   vsip_cscalar_f a0,a1,a2,a3,a4,a5,a6,a7;
   vsip_cscalar_f b0,b1,b2,b3,b4,b5,b6,b7;
   vsip_cscalar_f c0,c1,c2,c3,c4,c5;
   vsip_cscalar_f d0,d1,d2,d3,d4,d5,d6,d7;
   a0.r = *xp_r; a0.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a1.r = *xp_r; a1.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a2.r = *xp_r; a2.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a3.r = *xp_r; a3.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a4.r = *xp_r; a4.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a5.r = *xp_r; a5.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a6.r = *xp_r; a6.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a7.r = *xp_r; a7.i = *xp_i;
/* step 1 */
   b0.r = a0.r + a4.r; b0.i = a0.i + a4.i;
   b1.r = a0.r - a4.r; b1.i = a0.i - a4.i;
   b2.r = a1.r + a5.r; b2.i = a1.i + a5.i;
   b3.r = a1.r - a5.r; b3.i = a1.i - a5.i;
   b4.r = a2.r + a6.r; b4.i = a2.i + a6.i;
   b5.r = a2.r - a6.r; b5.i = a2.i - a6.i;
   b6.r = a3.r + a7.r; b6.i = a3.i +a7.i;
   b7.r = a3.r - a7.r; b7.i = a3.i - a7.i;
   c0.r = b0.r + b4.r; c0.i = b0.i + b4.i;
   c1.r = b0.r - b4.r; c1.i = b0.i - b4.i;
   c2.r = b2.r + b6.r; c2.i = b2.i + b6.i;
   c3.r =b2.r - b6.r; c3.i = b2.i - b6.i;
   c4.r = b3.r + b7.r; c4.i = b3.i + b7.i;
   c5.r = b3.r - b7.r; c5.i = b3.i - b7.i;
/* step 2 */
   c4.r = c4.r * C8c1; c4.i =  c4.i * C8c1; 
   c5.r = c5.r * C8c1; c5.i = c5.i * C8c1; 
/* step 3 */
   d0.r = c0.r + c2.r; d0.i = c0.i + c2.i;
   d4.r = c0.r - c2.r; d4.i = c0.i - c2.i;
   d2.r = c1.r + c3.i; d2.i = c1.i - c3.r;
   d6.r = c1.r - c3.i; d6.i = c1.i + c3.r;
   d1.r = b1.r + c5.r; d1.i = b1.i + c5.i;
   d5.r = b1.r - c5.r; d5.i = b1.i - c5.i;
   d3.r = b5.i + c4.i; d3.i = b5.r + c4.r;
   d7.r = c4.i - b5.i; d7.i = b5.r - c4.r;
/* step 4 */
   *xp_r = d1.r - d3.r; *xp_i = d1.i + d3.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d6.r; *xp_i = d6.i;  xp_r -= xpst; xp_i -= xpst;
   *xp_r = d5.r - d7.r; *xp_i = d5.i - d7.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d4.r; *xp_i =d4.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d5.r + d7.r; *xp_i = d5.i + d7.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d2.r; *xp_i = d2.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d1.r + d3.r; *xp_i = d1.i - d3.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d0.r; *xp_i = d0.i;
   return;
}

/*========================================================*/
/* Created By RJudd August 26, 1998 */
/* SPAWARSYSCEN D881 */
/* 8-point building block */
/* Based on Winograd 8-point FFT */
/* "Handbook of Real-Time Fast Fourier Transforms */
/* Winthrop Smith, Joanne Smith */

static
void 
VI_ifft8_f(void *tfft) {
   vsip_fft_f* fft = (vsip_fft_f*) tfft;
   vsip_scalar_f *xp_r = fft->xp_r,
                 *xp_i = fft->xp_i;
   vsip_scalar_vi xpst = fft->xpst;
   vsip_cscalar_f a0,a1,a2,a3,a4,a5,a6,a7;
   vsip_cscalar_f b0,b1,b2,b3,b4,b5,b6,b7;
   vsip_cscalar_f c0,c1,c2,c3,c4,c5;
   vsip_cscalar_f d0,d1,d2,d3,d4,d5,d6,d7;
   a0.r = *xp_r; a0.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a1.r = *xp_r; a1.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a2.r = *xp_r; a2.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a3.r = *xp_r; a3.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a4.r = *xp_r; a4.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a5.r = *xp_r; a5.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a6.r = *xp_r; a6.i = *xp_i; xp_r += xpst; xp_i += xpst;
   a7.r = *xp_r; a7.i = *xp_i;
/* step 1 */
   b0.r = a0.r + a4.r; b0.i = a0.i + a4.i;
   b1.r = a0.r - a4.r; b1.i = a0.i - a4.i;
   b2.r = a1.r + a5.r; b2.i = a1.i + a5.i;
   b3.r = a1.r - a5.r; b3.i = a1.i - a5.i;
   b4.r = a2.r + a6.r; b4.i = a2.i + a6.i;
   b5.r = a2.r - a6.r; b5.i = a2.i - a6.i;
   b6.r = a3.r + a7.r; b6.i = a3.i +a7.i;
   b7.r = a3.r - a7.r; b7.i = a3.i - a7.i;
   c0.r = b0.r + b4.r; c0.i = b0.i + b4.i;
   c1.r = b0.r - b4.r; c1.i = b0.i - b4.i;
   c2.r = b2.r + b6.r; c2.i = b2.i + b6.i;
   c3.r =b2.r - b6.r; c3.i = b2.i - b6.i;
   c4.r = b3.r + b7.r; c4.i = b3.i + b7.i;
   c5.r = b3.r - b7.r; c5.i = b3.i - b7.i;
/* step 2 */
   c4.r = c4.r * C8c1; c4.i =  c4.i * C8c1;
   c5.r = c5.r * C8c1; c5.i = c5.i * C8c1;
/* step 3 */
   d0.r = c0.r + c2.r; d0.i = c0.i + c2.i;
   d4.r = c0.r - c2.r; d4.i = c0.i - c2.i;
   d2.r = c1.r - c3.i; d2.i = c1.i + c3.r;
   d6.r = c1.r + c3.i; d6.i = c1.i - c3.r;
   d1.r = b1.r + c5.r; d1.i = b1.i + c5.i;
   d5.r = b1.r - c5.r; d5.i = b1.i - c5.i;
   d3.r = -(b5.i + c4.i); d3.i = -(b5.r + c4.r);
   d7.r = b5.i - c4.i; d7.i = c4.r - b5.r;
/* step 4 */
   *xp_r = d1.r - d3.r; *xp_i = d1.i + d3.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d6.r; *xp_i = d6.i;  xp_r -= xpst; xp_i -= xpst;
   *xp_r = d5.r - d7.r; *xp_i = d5.i - d7.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d4.r; *xp_i =d4.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d5.r + d7.r; *xp_i = d5.i + d7.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d2.r; *xp_i = d2.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d1.r + d3.r; *xp_i = d1.i - d3.i; xp_r -= xpst; xp_i -= xpst;
   *xp_r = d0.r; *xp_i = d0.i;
   return;
}
/* fft_wt.c multiply by twiddle factors */

static
void 
VI_fft_wt_f(void *tfft) {
   vsip_fft_f* fft = (vsip_fft_f*) tfft;
      vsip_cvview_f *a = fft->x;
      vsip_cvview_f *b = fft->wt;
      vsip_cvview_f *r = fft->x;
      vsip_stride cast = a->block->cstride;
      vsip_stride cbst = b->block->cstride;
      vsip_length n = r->length;
      vsip_scalar_f *apr = (vsip_scalar_f *)((a->block->R->array) + cast * a->offset),
                    *bpr = (vsip_scalar_f *)(b->block->R->array),
                    *rpr = apr;
      vsip_scalar_f *api = (vsip_scalar_f *)((a->block->I->array) + cast * a->offset),
                    *bpi = (vsip_scalar_f *)(b->block->I->array),
                    *rpi = api;
      vsip_scalar_f temp;
      vsip_stride ast = cast * a->stride, 
                                 bst = cbst * b->stride, 
                                 rst = ast;
      while(n-- > 0){
          temp = *apr * *bpr - *bpi * *api;
          *rpi = *apr * *bpi + *api * *bpr;
          *rpr = temp;
          apr += ast; api += ast; 
          bpr += bst; bpi += bst; 
          rpr += rst; rpi += rst;
      }
   return;
}

static
void 
VI_p0pF_f(void *tfft) {
  vsip_fft_f *fft = (vsip_fft_f*) tfft;
  vsip_scalar_vi p0 = fft->p0[fft->stage];
  vsip_scalar_vi pF = fft->pF[fft->stage];
  vsip_scalar_vi M  = fft->pn[fft->stage];

  vsip_length N   = ((fft->stage) == 0) ? fft->N : fft->pF[fft->stage - 1];
  vsip_scalar_vi Ns = N;
  vsip_scalar_vi N1;
  vsip_scalar_vi wtstr = fft->N / N;
  vsip_scalar_vi seg = 1;
  vsip_stride k=0,i=0,j=0,case_pF;
  vsip_stride cxst = fft->x->block->cstride;

  void (*fft_p)(void*) = VI_p0pF_f;

  vsip_cvattr_f xattr;

  fft->x_r = (vsip_scalar_f *)((fft->x->block->R->array) + cxst * fft->x->offset);
  fft->x_i = (vsip_scalar_f *)((fft->x->block->I->array) + cxst * fft->x->offset);
  fft->xst = cxst * fft->x->stride;

  vsip_cvgetattrib_f(fft->x,&xattr);

  fft->stage++;
  case_pF = (pF < 9) ? pF : ((fft->stage) == (fft->length )) ? 101 : 103;

   fft->wt->length = p0;   /* set weight vector length*/
   fft->x->length = p0;     /* set x vector length */

  if(fft->d == -1){ /*forward section */
      switch( p0){ /* fft building block for p0 */
        case 2  : fft_p = VI_fft2_f; break;
        case 3  : fft_p = VI_fft3_f; break;
        case 4  : fft_p = VI_fft4_f; break;
        case 5  : fft_p = VI_fft5_f; break;
        case 7  : fft_p = VI_fft7_f; break;
        case 8  : fft_p = VI_fft8_f; break;
      }
      for(k=0; k<(int)M-1; k++ ) { /* (M-1 segments) *( pF building blocks of length p0)*/
        N1 = Ns;
        Ns = Ns/p0; 
        fft->x->stride = xattr.stride * Ns; /* x stride for segment */
        fft->xpst = Ns * fft->xst;
        fft->wt->stride = 0;
        /*j = 0 */
        fft->x->offset = xattr.offset;
        fft->xp_r = fft->x_r;
        fft->xp_i = fft->x_i;
        fft_p(fft);
        for(i = N1; i < N; i+= N1){
          fft->x->offset = xattr.offset + xattr.stride * i;
          fft->xp_r = fft->x_r + fft->xst * i;
          fft->xp_i = fft->x_i + fft->xst * i;
          fft_p(fft);
          VI_fft_wt_f(fft);
        }
        fft->wt->stride += (seg * wtstr); 
        for(j=1; j<(int)Ns; j++){
          for(i = j; i < N; i+= N1){
            fft->x->offset = xattr.offset + xattr.stride * i;
            fft->xp_r = fft->x_r + fft->xst * i;
            fft->xp_i = fft->x_i + fft->xst * i;
            fft_p(fft);
            VI_fft_wt_f(fft); /*vsip_cvmul_f(fft->x,wt,fft->x);*/
          }
          fft->wt->stride += (seg * wtstr);
        }  
      seg *= p0 ;
      }
      N1 = Ns;
      Ns = Ns/pF; 
      fft->x->stride = xattr.stride * Ns;
      fft->xpst = Ns * fft->xst;
      fft->x->length = pF;
      switch(case_pF){
        case 2  : fft_p = VI_fft2_f; break;
        case 3  : fft_p = VI_fft3_f; break;
        case 4  : fft_p = VI_fft4_f; break;
        case 5  : fft_p = VI_fft5_f; break;
        case 7  : fft_p = VI_fft7_f; break;
        case 8  : fft_p = VI_fft8_f; break;
        case 101: fft_p = VI_dft_f; break;
        case 103: fft_p = VI_p0pF_f; break;
      }
      for(j=0; j<(int)Ns; j++){
        for(i = j; i < N; i+= N1){
          fft->x->offset = xattr.offset + xattr.stride * i;
          fft->xp_r = fft->x_r + fft->xst * i;
          fft->xp_i = fft->x_i + fft->xst * i;
          fft_p(fft);
        }
      }  
    }  /* end forward section */

      else { /*inverse section */
      switch( p0){ /* fft building block for p0 */
        case 2  : fft_p = VI_ifft2_f; break;
        case 3  : fft_p = VI_ifft3_f; break;
        case 4  : fft_p = VI_ifft4_f; break;
        case 5  : fft_p = VI_ifft5_f; break;
        case 7  : fft_p = VI_ifft7_f; break;
        case 8  : fft_p = VI_ifft8_f; break;
      }  
      for(k=0; k<(int)M-1; k++ ) { /* (M-1 segments) *( pF building blocks of length p0)*/
        N1 = Ns;
        Ns = Ns/p0;
        fft->x->stride = xattr.stride * Ns; /* x stride for segment */
        fft->xpst = Ns * fft->xst;
        fft->wt->stride = 0;
        /*j = 0 */ 
        fft->x->offset = xattr.offset;
        fft->xp_r = fft->x_r;
        fft->xp_i = fft->x_i;
        fft_p(fft);
        for(i = N1; i < N; i+= N1){
          fft->x->offset = xattr.offset + xattr.stride * i;
          fft->xp_r = fft->x_r + fft->xst * i;
          fft->xp_i = fft->x_i + fft->xst * i;
          fft_p(fft);
          VI_fft_wt_f(fft);
        }
        fft->wt->stride += (seg * wtstr);
        for(j=1; j<(int)Ns; j++){
          for(i = j; i < N; i+= N1){
            fft->x->offset = xattr.offset + xattr.stride * i;
            fft->xp_r = fft->x_r + fft->xst * i;
            fft->xp_i = fft->x_i + fft->xst * i;
            fft_p(fft);
            VI_fft_wt_f(fft); /*vsip_cvmul_f(fft->x,wt,fft->x);*/
          }
          fft->wt->stride += (seg * wtstr);
        }
      seg *= p0 ;
      }  
      N1 = Ns;
      Ns = Ns/pF;
      fft->x->stride = xattr.stride * Ns;
      fft->xpst = Ns * fft->xst;
      fft->x->length = pF;
      switch(case_pF){
        case 2  : fft_p = VI_ifft2_f; break;
        case 3  : fft_p = VI_ifft3_f; break;
        case 4  : fft_p = VI_ifft4_f; break;
        case 5  : fft_p = VI_ifft5_f; break;
        case 7  : fft_p = VI_ifft7_f; break;
        case 8  : fft_p = VI_ifft8_f; break;
        case 101: fft_p = VI_dft_f; break;
        case 103: fft_p = VI_p0pF_f; break;
      }  
      for(j=0; j<(int)Ns; j++){
        for(i = j; i < N; i+= N1){
          fft->x->offset = xattr.offset + xattr.stride * i;
          fft->xp_r = fft->x_r + fft->xst * i;
          fft->xp_i = fft->x_i + fft->xst * i;
          fft_p(fft);
        }
      }  
    } /* end inverse section */
    vsip_cvputattrib_f(fft->x,&xattr);
    fft->stage--;
    return;
}
#endif
