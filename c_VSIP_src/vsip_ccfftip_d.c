/* Created by RJudd January 7, 1999 */
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
/* $Id: vsip_ccfftip_d.c,v 2.1 2009/05/23 21:56:57 judd Exp $ */
#include"vsip.h"
#include"vsip_fftattributes_d.h"
#include"vsip_cvviewattributes_d.h"

#if defined(VSIP_USE_FFTW_FOR_FFT_D)
      #include"VI_ccfftip_d_fftw.h"
#else 
      #include"VI_ccfftip_d_def.h"
#endif
