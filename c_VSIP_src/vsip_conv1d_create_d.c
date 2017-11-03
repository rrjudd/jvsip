/* Created RJudd March 19, 1999 */
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
/* $Id: vsip_conv1d_create_d.c,v 2.0 2003/02/22 15:18:44 judd Exp $ */

#include"vsip.h"
#include"vsip_conv1dattributes_d.h"
#include"vsip_cvviewattributes_d.h"
#include"vsip_vviewattributes_d.h"
#include"VI_vcopy_d_d.h"
#include"VI_cvfill_d.h"
#include"VI_vrealview_d.h"

static void VI_selectNsection1(vsip_conv1d_d*);

vsip_conv1d_d *vsip_conv1d_create_d(
     const vsip_vview_d *h,
     vsip_symmetry symm,
     vsip_length N,
     int D,
     vsip_support_region support,
     unsigned int ntimes,
     vsip_alg_hint hint)
{
     vsip_conv1d_d *conv = (vsip_conv1d_d*) malloc(sizeof(vsip_conv1d_d));
     vsip_length klength;
     if(conv == NULL) return (vsip_conv1d_d*) NULL;
     conv->H = (vsip_cvview_d*)NULL;
     conv->x = (vsip_cvview_d*)NULL;
     conv->Xm = (vsip_cmview_d*)NULL;
     conv->fft = (vsip_fft_d*)NULL;
     conv->fftm = (vsip_fftm_d*)NULL;
     conv->support = support;
     conv->hint = hint;
     conv->ntimes = ntimes;
     conv->D  = D;
     conv->symm  = symm;
     conv->nx = N;
     switch(symm){
           case 0: klength = h->length;
                   break;
           case 1: klength = 2 * h->length - 1;
                   break;
           case 2: klength = 2 * h->length;
                   break;
           default: klength = h->length;
     }
     conv->nh = klength;
     if((((float)N /(float) h->length) > 2) && (h->length < 1000) ){
        VI_selectNsection1(conv);
     }else{
         vsip_length p = conv->nh + N/2;
         conv->Nsection = 1;
         while(conv->Nsection <= p){
            conv->Nsection *=2;
         } 
     /*    if(conv->Nsection > 2 * N) conv->Nsection /= 2; */
     }
     if((conv->H = vsip_cvcreate_d(conv->Nsection,VSIP_MEM_NONE)) == NULL){
          vsip_conv1d_destroy_d(conv);
          return (vsip_conv1d_d*) NULL;
     }
     { /* copy h to conv object */
        vsip_vview_d HHr;
        vsip_vview_d *Hr = VI_vrealview_d(conv->H, &HHr);
        VI_cvfill_d(vsip_cmplx_d((vsip_scalar_d)0,(vsip_scalar_d)0),conv->H);
        switch(symm){
            case 0:{
               Hr->length = klength;
               VI_vcopy_d_d(h,Hr);
            }
            break;
            case 1: {
               Hr->length = h->length;
               VI_vcopy_d_d(h,Hr);
               Hr->offset = klength - 1;
               Hr->stride = -1;
               VI_vcopy_d_d(h,Hr);
            }
            break;
            case 2: {
               Hr->length = h->length;
               VI_vcopy_d_d(h,Hr);
               Hr->offset = klength - 1;
               Hr->stride = -1;
               VI_vcopy_d_d(h,Hr);
            }
            break;
        } 
     }
     if((((float)N /(float) klength) > 2) && (klength < 1000) ){
         conv->method = 1;
         /* create transform of window */
         if((conv->fft = vsip_ccfftip_create_d(conv->Nsection,1,VSIP_FFT_FWD,0,hint)) == NULL){
               vsip_conv1d_destroy_d(conv);
               return(vsip_conv1d_d*) NULL;
         }
         vsip_ccfftip_d(conv->fft,conv->H);
         vsip_fft_destroy_d(conv->fft);
         conv->fft = (vsip_fft_d*)NULL;
         /* create fftm and Matrix to hold data for fft */
         { vsip_length m,n;
           conv->Ndata = (n = conv->Nsection - conv->nh);
           m = N / n;
           if((N % n)) m++;
           conv->NumSection = m;
           m = (m % 2) ? (m/2 + 1) : m/2; 
           conv->fftm = vsip_ccfftmip_create_d(m,conv->Nsection, 1, VSIP_FFT_FWD, VSIP_ROW,0,hint);
           conv->Xm   = vsip_cmcreate_d(m,conv->Nsection,VSIP_ROW,VSIP_MEM_NONE);
         }
         if((conv->fftm == NULL) || (conv->Xm == NULL)){
               vsip_conv1d_destroy_d(conv);
               return(vsip_conv1d_d*) NULL;
         }
     }else{
         conv->method = 0;
         conv->x = vsip_cvcreate_d(conv->Nsection,VSIP_MEM_NONE);
         conv->fft = vsip_ccfftip_create_d(conv->Nsection,1,VSIP_FFT_FWD,0,hint);
         if((conv->x == NULL) ||
            (conv->fft == NULL)){
                 vsip_conv1d_destroy_d(conv);
                 return (vsip_conv1d_d*)NULL;
         }
         vsip_ccfftip_d(conv->fft,conv->H);
     }
     switch(conv->support){ /* figure out the length of the output vector */
        case VSIP_SUPPORT_FULL:{
           conv->Noutput = (klength + N - 2)/(vsip_length)D + 1;
           break;
        }
        case VSIP_SUPPORT_SAME:{
           conv->Noutput = (N - 1)/(vsip_length)D + 1;
           break;
        }
        case VSIP_SUPPORT_MIN:{
           conv->Noutput = (N - 1)/(vsip_length)D - (klength - 1)/(vsip_length)D + 1;
           break;
        }
     }
     return conv;
}

static void VI_selectNsection1(vsip_conv1d_d *conv)
{ /* just use the table from Brigham FFT book */
     vsip_length L = conv->nh;
     if(L < 11){ 
        conv->Nsection = 32; return;}
     if(L < 20){ 
        conv->Nsection =  64; return;}
     if(L < 30){ 
        conv->Nsection =  128; return;}
     if(L < 50){ 
        conv->Nsection =  256; return;}
     if(L < 100){ 
        conv->Nsection =  512; return;}
     if(L < 200){ 
        conv->Nsection = 1024; return;}
     if(L < 300){ 
        conv->Nsection = 2048; return;}
     if(L < 600){ 
        conv->Nsection = 4096; return;}
     conv->Nsection = 8192; return;
}
     
