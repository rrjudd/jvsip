/* Created RJudd                    */
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
/* $Id: vsip_vcreate_uc.c,v 2.0 2003/02/22 15:19:12 judd Exp $ */

#include<vsip.h>
#include"VI_blockcreate_uc.h"
#include"VI_blockdestroy_uc.h"

vsip_vview_uc* (vsip_vcreate_uc)(
  vsip_length n, 
  vsip_memory_hint h) {
   vsip_block_uc* b = VI_blockcreate_uc((size_t)n, h);
   vsip_vview_uc* v = (vsip_vview_uc*)NULL;
   if(b != (vsip_block_uc*)NULL){
       v = vsip_vbind_uc(b, (vsip_offset)0, (vsip_stride)1, n);
       if(v ==(vsip_vview_uc*)NULL) VI_blockdestroy_uc(b);
   }
   return v;
}
