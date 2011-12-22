/* Created RJudd September 16, 2000 */
/* SPAWARSYSCEN D857                */
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
/* $Id: vsip_cblockrelease_d.c,v 2.1 2006/06/08 22:19:26 judd Exp $ */

#include<vsip.h>
#include<vsip_cblockattributes_d.h>

void (vsip_cblockrelease_d)(
  vsip_cblock_d* b,
  vsip_scalar_bl update,
  vsip_scalar_d* *Rp,
  vsip_scalar_d* *Ip) {
   if(b != (vsip_cblock_d*)NULL) b->update = update;
   #if defined(VSIP_DEFAULT_SPLIT)
      #include"VI_cblockrelease_d_ds.h"
   #elif defined(VSIP_ALWAYS_SPLIT)
      #include"VI_cblockrelease_d_as.h"
   #elif defined(VSIP_ALWAYS_INTERLEAVED)
      #include"VI_cblockrelease_d_ai.h"
   #else 
      #include"VI_cblockrelease_d_di.h"
   #endif 
   return;
}
