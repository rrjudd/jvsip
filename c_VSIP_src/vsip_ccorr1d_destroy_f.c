/* Created RJudd March 17, 1999 */
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
/* $Id: vsip_ccorr1d_destroy_f.c,v 2.0 2003/02/22 15:18:40 judd Exp $ */

#include"vsip.h"
#include"vsip_ccorr1dattributes_f.h"
#include"VI_cvalldestroy_f.h"

int vsip_ccorr1d_destroy_f(vsip_ccorr1d_f *cor)
{
   if(cor != NULL){
      VI_cvalldestroy_f(cor->x);
      VI_cvalldestroy_f(cor->h);
      vsip_fft_destroy_f(cor->fft);
      free(cor);
   }
   return 0;
}
      
