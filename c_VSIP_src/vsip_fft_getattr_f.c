/* Created By Randall Judd */
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
/* $Id: vsip_fft_getattr_f.c,v 2.0 2003/02/22 15:18:52 judd Exp $ */

#include<vsip.h>
#include<vsip_fftattributes_f.h>

void vsip_fft_getattr_f(
     const vsip_fft_f *fft,
     vsip_fft_attr_f *attr)
{
    switch (fft->type){
      case VSIP_CCFFTOP : {
          attr->input = fft->N;
          attr->output = fft->N;
          attr->place = VSIP_FFT_OP;
          attr->dir = fft->d;
          attr->scale = fft->scale;
          break;
      }
      case VSIP_CCFFTIP :{
          attr->input = fft->N;
          attr->output = fft->N;
          attr->place = VSIP_FFT_IP;
          attr->dir = fft->d;
          attr->scale = fft->scale;
          break;
      }
      case VSIP_RCFFTOP :{
          attr->input = fft->N * 2;
          attr->output = fft->N + 1;
          attr->place = VSIP_FFT_OP;
          attr->dir = fft->d;
          attr->scale = fft->scale;
          break;
      }
      case VSIP_CRFFTOP :{
          attr->input = fft->N + 1;
          attr->output = fft->N * 2;
          attr->place = VSIP_FFT_OP;
          attr->dir = fft->d;
          attr->scale = fft->scale;
          break;
      }
   }
   return;
}
