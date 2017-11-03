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
/* $Id: vsip_cblockbind_f.c,v 2.2 2009/05/20 17:11:15 judd Exp $ */

#include"vsip.h"
#include"vsip_cblockattributes_f.h"
#include"vsip_blockattributes_f.h"

vsip_cblock_f* (vsip_cblockbind_f)(
  vsip_scalar_f*  const Rp,
  vsip_scalar_f*  const Ip,
  vsip_length N, 
  vsip_memory_hint h) {
  vsip_cblock_f* b = (vsip_cblock_f*)malloc(sizeof(vsip_cblock_f));
  if(b != (vsip_cblock_f*)NULL) b->hint = h;
  #if defined(VSIP_DEFAULT_SPLIT)
     #include"VI_cblockbind_f_ds.h"
  #elif defined(VSIP_ALWAYS_SPLIT)
     #include"VI_cblockbind_f_as.h"
  #elif defined(VSIP_ALWAYS_INTERLEAVED)
     #include"VI_cblockbind_f_ai.h"
  #else
     #include"VI_cblockbind_f_di.h"
  #endif
  return b;
}
