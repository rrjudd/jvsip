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
/* $Id: vsip_ccfftmip_f.c,v 2.0 2003/02/22 15:18:39 judd Exp $ */
#include"vsip.h"
#include"vsip_cmviewattributes_f.h"
#include"vsip_cvviewattributes_f.h"
#include"vsip_fftmattributes_f.h"
#if defined(VSIP_USE_FFT_FOR_FFTM_F)
   #include"VI_ccfftmip_f_loop.h"
#else
  #include"VI_ccfftmip_f_def.h"
#endif

