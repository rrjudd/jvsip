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
/* $Id: vsip_cblockadmit_f.c,v 2.1 2006/06/08 22:19:26 judd Exp $ */

#include<vsip.h>
#include<vsip_cblockattributes_f.h>

int (vsip_cblockadmit_f)(
  vsip_cblock_f* b,
  vsip_scalar_bl update) {
   int blockadmit = (int)update; /* keep update from warning since don't use */
   #if defined(VSIP_DEFAULT_SPLIT)
      #include"VI_cblockadmit_f_ds.h"
   #elif defined(VSIP_ALWAYS_SPLIT)
      #include"VI_cblockadmit_f_as.h"
   #elif defined(VSIP_ALWAYS_INTERLEAVED)
      #include"VI_cblockadmit_f_ai.h"
   #else
      #include"VI_cblockadmit_f_di.h"
   #endif
   return blockadmit;
}
