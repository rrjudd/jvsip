/* Created By RJudd October 14, 1998 */
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
/* $Id: vsip_crfftop_create_d.c,v 2.1 2003/03/08 14:43:34 judd Exp $ */
/* real to complex fft */
#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_fftattributes_d.h>

#if defined(VSIP_USE_FFTW_FOR_FFT_D)
   #include"VI_crfftop_create_d_fftw.h"
#else
   #include"VI_crfftop_create_d_def.h"
#endif
