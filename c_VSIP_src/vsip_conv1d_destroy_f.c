/* Created RJudd March 21, 1999 */
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
/* $Id: vsip_conv1d_destroy_f.c,v 2.0 2003/02/22 15:18:45 judd Exp $ */

#include<vsip.h>
#include<vsip_conv1dattributes_f.h>
#include"VI_cvalldestroy_f.h"

int vsip_conv1d_destroy_f(vsip_conv1d_f *conv)
{
   if(conv != NULL){
      if(conv->x != NULL) VI_cvalldestroy_f(conv->x);
      if(conv->H != NULL) VI_cvalldestroy_f(conv->H);
      if(conv->fft != NULL) vsip_fft_destroy_f(conv->fft);
      if(conv->fftm != NULL) vsip_fftm_destroy_f(conv->fftm);
      if(conv->Xm != NULL) vsip_cmalldestroy_f(conv->Xm);
      free(conv);
   }
   return 0;
}
