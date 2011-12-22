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
/* $Id: vsip_cblockdestroy_f.c,v 2.0 2003/02/22 15:18:38 judd Exp $ */

#include<vsip.h>
#include<vsip_cblockattributes_f.h>

void (vsip_cblockdestroy_f)(
   vsip_cblock_f* b) {
   #if defined(VSIP_DEFAULT_SPLIT)
      #include"VI_cblockdestroy_f_ds.h"
   #elif defined(VSIP_ALWAYS_SPLIT)
      #include"VI_cblockdestroy_f_as.h"
   #elif defined(VSIP_ALWAYS_INTERLEAVED)
      #include"VI_cblockdestroy_f_ai.h"
   #else
      #include"VI_cblockdestroy_f_di.h"
   #endif
   return;
}
