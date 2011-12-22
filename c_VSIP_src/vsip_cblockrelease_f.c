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
/* $Id: vsip_cblockrelease_f.c,v 2.1 2006/06/08 22:19:26 judd Exp $ */

#include<vsip.h>
#include<vsip_cblockattributes_f.h>

void (vsip_cblockrelease_f)(
  vsip_cblock_f* b,
  vsip_scalar_bl update,
  vsip_scalar_f* *Rp,
  vsip_scalar_f* *Ip) {
   if(b != (vsip_cblock_f*)NULL) b->update = update;
   #if defined(VSIP_DEFAULT_SPLIT)
      #include"VI_cblockrelease_f_ds.h"
   #elif defined(VSIP_ALWAYS_SPLIT)
      #include"VI_cblockrelease_f_as.h"
   #elif defined(VSIP_ALWAYS_INTERLEAVED)
      #include"VI_cblockrelease_f_ai.h"
   #else
      #include"VI_cblockrelease_f_di.h"
   #endif
   return;
}
