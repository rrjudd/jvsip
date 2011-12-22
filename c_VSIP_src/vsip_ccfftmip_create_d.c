/* Created By RJudd January 9, 1999 */
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
/* $Id: vsip_ccfftmip_create_d.c,v 2.0 2003/02/22 15:18:38 judd Exp $ */
/* calculate number of factors of 2,3,4 in N */
/* calculate N = 2^n2 * 4^n4 * 8^n8 * 3^n3 * 5^n5 *7^n7 * n */
#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_fftmattributes_d.h>
#if defined(VSIP_USE_FFT_FOR_FFTM_D)
   #include"VI_ccfftmip_create_d_loop.h"
#else
   #include"VI_ccfftmip_create_d_def.h"
#endif
