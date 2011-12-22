/* Created Randall Judd */
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
/* $Id: vsip_fftm_getattr_f.c,v 2.0 2003/02/22 15:18:52 judd Exp $ */
#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_fftmattributes_f.h>

void vsip_fftm_getattr_f(
     const vsip_fftm_f *fft,
     vsip_fftm_attr_f *attr)
{
    switch (fft->type){
      case VSIP_CCFFTOP : {
          (attr->input).r = fft->M;
          (attr->input).c = fft->N;
          (attr->output).r = fft->M;
          (attr->output).c = fft->N;
          attr->place = VSIP_FFT_OP;
          attr->dir = fft->d;
          attr->scale = fft->scale;
          attr->major = fft->major;
          break;
      }
      case VSIP_CCFFTIP :{
          (attr->input).r = fft->M;
          (attr->input).c = fft->N;
          (attr->output).r = fft->M;
          (attr->output).c = fft->N;
          attr->place = VSIP_FFT_IP;
          attr->dir = fft->d;
          attr->scale = fft->scale;
          attr->major = fft->major;
          break;
      }
      case VSIP_RCFFTOP :{
          (attr->input).r = fft->M;
          (attr->input).c = fft->N;
          (attr->output).r = (fft->major == VSIP_ROW) ? fft->mN : (fft->MN + 1); 
          (attr->output).c = (fft->major == VSIP_ROW) ? (fft->MN + 1) : fft->mN;
          attr->place  = VSIP_FFT_OP;
          attr->dir    = fft->d;
          attr->scale  = fft->scale;
          attr->major = fft->major;
          break;
      }
      case VSIP_CRFFTOP :{
          (attr->input).r = (fft->major == VSIP_ROW) ? fft->mN : (fft->MN + 1); 
          (attr->input).c = (fft->major == VSIP_ROW) ? (fft->MN + 1) : fft->mN;
          (attr->output).r = fft->M;
          (attr->output).c = fft->N;
          attr->place   = VSIP_FFT_OP;
          attr->dir     = fft->d;
          attr->scale   = fft->scale;
          attr->major = fft->major;
          break;
      }
   }
   return;
}
