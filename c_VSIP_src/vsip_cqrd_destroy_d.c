/* Created RJudd August 29, 1999 */
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
/* $Id: vsip_cqrd_destroy_d.c,v 2.0 2003/02/22 15:18:46 judd Exp $ */
/* vsip_cqrd_destroy_d */

#include<vsip.h>
#include<vsip_cqrdattributes_d.h>
#include"VI_cvalldestroy_d.h"

int vsip_cqrd_destroy_d(
         vsip_cqr_d* qr)
{
   if(qr != NULL){
      VI_cvalldestroy_d(qr->w);
      VI_cvalldestroy_d(qr->v);
      VI_cvalldestroy_d(qr->cI);
      free(qr->beta);
      free(qr);
   }
   return 0;
}
