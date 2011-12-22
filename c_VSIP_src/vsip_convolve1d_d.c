/* Created by Randall Judd */
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
/* $Id: vsip_convolve1d_d.c,v 2.0 2003/02/22 15:18:45 judd Exp $ */
#include<vsip.h>
#include<vsip_conv1dattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include"VI_cmrowview_d.h"
#include"VI_vcopy_d_d.h"
#include"VI_cvfill_d.h"
#include"VI_vrealview_d.h"
#include"VI_vimagview_d.h"

void vsip_convolve1d_d(
       const vsip_conv1d_d *conv,
       const vsip_vview_d *x,
       const vsip_vview_d *y)
{
  if(conv->method == 0){ /*kernel >= N/2 or kernel > 1000 */
     vsip_vview_d xxt = *x;
     vsip_vview_d *xt = &xxt;
     vsip_vview_d xxr,xxi;
     vsip_vview_d *xr = VI_vrealview_d(conv->x,&xxr),
                  *xi = VI_vimagview_d(conv->x,&xxi);
     vsip_length xtn2 = x->length/2;
     xi->length = xtn2;
     if((x->length % 2) != 0) xtn2++;
     xr->length = xtn2;
     /* make sure work area starts full of zeros */
     VI_cvfill_d(vsip_cmplx_d((vsip_scalar_d)0,(vsip_scalar_d)0),conv->x);
     /* copy input vector into work area */
     xt->length = xtn2; VI_vcopy_d_d(xt,xr);
     xt->offset = xtn2; xt->length = x->length - xtn2; VI_vcopy_d_d(xt,xi);
     /* do the fft on the input data */
     vsip_ccfftip_d(conv->fft,conv->x);
     /* multiply time filter in frequency domain */
     vsip_cvmul_d(conv->H,conv->x,conv->x);
     /* do invers fft using forward fft */
     vsip_cvconj_d(conv->x,conv->x);
     vsip_rscvmul_d(1.0/(vsip_scalar_d)conv->x->length,conv->x,conv->x);
     vsip_ccfftip_d(conv->fft,conv->x);
     vsip_cvconj_d(conv->x,conv->x);
     /* do overlap add of real with complex */
     xr->offset = xtn2; 
     xr->length = conv->nh - 1;
     xi->offset = 0; 
     xi->length = xr->length;
     vsip_vadd_d(xr,xi,xi);
     /* set length and offset of real to first half without overlap */
     xr->length = xr->offset; 
     xr->offset = 0; 
     /* desample by setting stride */
     xr->stride = (vsip_stride)conv->D; 
     xi->stride = (vsip_stride)conv->D;
     if(conv->support == VSIP_SUPPORT_SAME){
        vsip_vview_d yyt = *y;
        vsip_vview_d *yt = &yyt;
        xr->offset = (conv->nh/2);
        xr->length -= xr->offset;
        {
           vsip_offset o = xr->length % xr->stride;
           /* if o is zero, xi offset is zero, otherwise is stride - o */
           xi->offset = o ? xi->stride - o : o;
           xr->length /= xr->stride;
           if(o != 0) xr->length++;
        }
        xi->length = conv->Noutput - xr->length;
        yt->length = xr->length;
        VI_vcopy_d_d(xr,yt);
        yt->length = xi->length;
        yt->offset += (yt->stride * xr->length);
        VI_vcopy_d_d(xi,yt);
     }
     if(conv->support == VSIP_SUPPORT_MIN){
        vsip_vview_d yyt = *y;
        vsip_vview_d *yt = &yyt;
        if(xtn2 < conv->nh) {
          xi->offset = conv->nh - xtn2 -1;
          xi->length = conv->Noutput;
          VI_vcopy_d_d(xi,yt);
        } else { 
          xr->offset = conv->nh - 1;
          xr->length = (xr->length - xr->offset);
          {
             vsip_offset o = xr->length % xr->stride;
             /* if o is zero, xi offset is zero, otherwise is stride - o */
             xi->offset = o ? xi->stride - o : o;
             xr->length /= xr->stride;
             if(o != 0) xr->length++;
          }
          xi->length = conv->Noutput - xr->length;
          yt->length = xr->length;
          VI_vcopy_d_d(xr,yt);
          yt->length = xi->length;
          yt->offset += (yt->stride * xr->length);
          VI_vcopy_d_d(xi,yt);
        }  
     }
     if(conv->support == VSIP_SUPPORT_FULL){
       vsip_vview_d yyt = *y;
       vsip_vview_d *yt = &yyt;
       {
          vsip_offset o = xr->length % xr->stride;
          /* if o is zero, xi offset is zero, otherwise is stride - o */
          xi->offset = o ? xi->stride - o : o;
          xr->length /= xr->stride;
          if(o != 0) xr->length++;
       }
       xi->length = conv->Noutput - xr->length;
       yt->length = xr->length;
       VI_vcopy_d_d(xr,yt);
       yt->length = xi->length;
       yt->offset += (yt->stride * xr->length);
       VI_vcopy_d_d(xi,yt);
      }
   }else{
      vsip_cmview_d XXm = *conv->Xm,
                  *Xm  = &XXm;
     { /* make sure we start with an initialized zero matrix */
          vsip_cvview_d XXVt,
                        *XVt = VI_cmrowview_d(Xm,0,&XXVt);
          XVt->length = Xm->row_length * Xm->col_length;
          VI_cvfill_d(vsip_cmplx_d((vsip_scalar_d)0,(vsip_scalar_d)0),XVt);
     }
     { /* copy data into matrix */
       unsigned int i = 1;
       vsip_vview_d XXR,XXI,XX = *x,*XT;
       vsip_cvview_d XXC;
       vsip_cvview_d *XC = VI_cmrowview_d(Xm,0,&XXC);
       vsip_vview_d *XR = VI_vrealview_d(XC,&XXR);
       vsip_vview_d *XI = VI_vimagview_d(XC,&XXI);
       vsip_vview_d *X = &XX;
       vsip_length Xinc,XTinc;
       if(x->length > conv->Ndata){
           vsip_length L = X->length - conv->Ndata;
           X->length = conv->Ndata;
           XR->length = conv->Ndata;
           XI->length = conv->Ndata;
           Xinc = X->length * X->stride;
           XTinc = Xm->col_stride;
           XT = XR;
           while(L > 0){
              VI_vcopy_d_d(X,XT);
              X->offset += Xinc;
              if(i%2) { 
                   XT = XI;
                   XR->offset += XTinc;
              } else {
                   XT = XR;
                   XI->offset += XTinc;
              }
              if(L > XT->length){
                 L -= XT->length;
              } else {
                   XT->length = L;
                   X->length = L;
                   VI_vcopy_d_d(X,XT);
                   L = 0;
              }
              i++;
           }
       } else { 
           XR->length = X->length;
           VI_vcopy_d_d(X,XR);
       }
     }
     { /* do forward fft and multiply the filter (freq domain kernel) */
          vsip_ccfftmip_d(conv->fftm,Xm);
          vsip_cvmmul_d(conv->H,Xm,VSIP_ROW,Xm);
     }
     {  /* do inverse fft using forward fft */
          vsip_cvview_d XXVt,
                        *XVt = VI_cmrowview_d(Xm,0,&XXVt);
          XVt->length = Xm->row_length * Xm->col_length; /* flaten matrix */
          vsip_cvconj_d(XVt,XVt); /* conjugate */
          vsip_rscvmul_d(1.0/Xm->row_length,XVt,XVt); /* scale */
          vsip_ccfftmip_d(conv->fftm,Xm); /* forward fftm */
          vsip_cvconj_d(XVt,XVt); /* conjugate */
     }
     { /* do overlap add */
          vsip_length i;
          vsip_cvview_d xxc;
          vsip_vview_d  xxr,xxi,
                        xxo,*xo=&xxo,
                        xxa,*xa=&xxa;
          vsip_cvview_d *xc = VI_cmrowview_d(Xm,0,&xxc);
          vsip_vview_d  *xr = VI_vrealview_d(xc,&xxr);
          vsip_vview_d  *xi = VI_vimagview_d(xc,&xxi);
          vsip_offset xinc = Xm->col_stride;
          vsip_length loa = conv->nh - 1;
          vsip_offset Oo  = conv->Ndata;
          xi->length = loa; xr->length = loa;
          for(i=1; i<conv->NumSection; i++){
             if(i%2) {
                   xxo = xxr; xxa = xxi;
                   xr->offset += xinc;
             }else{
                   xxo = xxi; xxa = xxr;
                   xi->offset += xinc;
             }
             xo->offset += Oo;
             vsip_vadd_d(xo,xa,xa);
          } 
      }
      { /* copy to output vector */
          unsigned int i = 1;
          vsip_cvview_d XXC;
          vsip_vview_d  XXR,XXI,XXT;
          vsip_cvview_d *XC = VI_cmrowview_d(Xm,0,&XXC);
          vsip_vview_d  *XR = VI_vrealview_d(XC,&XXR);
          vsip_vview_d  *XI = VI_vimagview_d(XC,&XXI);
          vsip_vview_d  *XT = &XXT;
          vsip_offset xinc = Xm->col_stride;
          vsip_length L = conv->Noutput;
          XR->stride = conv->D;
          XI->stride = conv->D;
          XR->length = conv->Ndata;
          XI->length = conv->Ndata;
          XXT = XXR;
          if(conv->support == VSIP_SUPPORT_SAME){
             vsip_vview_d yyt = *y;
             vsip_vview_d *yt = &yyt;
             XT->offset = conv->nh / 2;
             XT->length -= XT->offset;
             while(L > 0){
                vsip_offset o = XT->length % XT->stride;
                XT->length /= XT->stride;
                if(o != 0){
                    o = XT->stride - o; 
                    XT->length++;
                }
                if(L > XT->length){
                      L -= XT->length;
                }else{
                      XT->length = L;
                      L = 0;
                }
                yt->length = XT->length;
                VI_vcopy_d_d(XT,yt);
                yt->offset += (yt->length * yt->stride);
                if(i%2){
                    XXT = XXI;
                    XR->offset += xinc;
                    XT->offset += o;
                    XT->length -= o;
                }else{
                    XXT = XXR;
                    XI->offset += xinc;
                    XT->offset += o;
                    XT->length -= o;
                }
                i++;
             }
          }
          if(conv->support == VSIP_SUPPORT_MIN){
             vsip_vview_d yyt = *y;
             vsip_vview_d *yt = &yyt;
             XT->offset = conv->nh - 1;
             XT->length -= XT->offset;
             while(L > 0){
                vsip_offset o = XT->length % XT->stride;
                XT->length /= XT->stride;
                if(o != 0){
                    o = XT->stride - o; 
                    XT->length++;
                }
                if(L > XT->length){ 
                      L -= XT->length;
                }else{ 
                      XT->length = L; 
                      L = 0; 
                } 
                yt->length = XT->length;
                VI_vcopy_d_d(XT,yt);
                yt->offset += (yt->length * yt->stride);
                if(i%2){
                    XXT = XXI;
                    XR->offset += xinc;
                    XT->offset += o;
                    XT->length -= o;
                }else{
                    XXT = XXR;
                    XI->offset += xinc;
                    XT->offset += o;
                    XT->length -= o;
                }
                i++; 
             }   
          }
          if(conv->support == VSIP_SUPPORT_FULL){
             vsip_vview_d yyt = *y;   
             vsip_vview_d *yt = &yyt; 
             while(L > 0){ 
                vsip_offset o = XT->length % XT->stride; 
                XT->length /= XT->stride;
                if(o != 0){
                    o = XT->stride - o; 
                    XT->length++;
                }
                if(L > XT->length){   
                      L -= XT->length;
                }else{  
                      XT->length = L;  
                      L = 0;  
                }  
                yt->length = XT->length; 
                VI_vcopy_d_d(XT,yt); 
                yt->offset += (yt->length * yt->stride); 
                if(i%2){ 
                    XXT = XXI;   
                    XR->offset += xinc;  
                    XT->offset += o;
                    XT->length -= o;  
                }else{ 
                    XXT = XXR;   
                    XI->offset += xinc;  
                    XT->offset += o;
                    XT->length -= o;  
                } 
                i++;  
             }   
          }
      }
   }
   return;
}
