/* Created RJudd September 18, 2000 */
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
/* $Id: vsip_vcreate_li.c,v 2.0 2003/02/22 15:19:12 judd Exp $ */

#include<vsip.h>
#include"VI_blockcreate_li.h"

vsip_vview_li* (vsip_vcreate_li)(
  vsip_length n, 
  vsip_memory_hint h) {
   vsip_block_li* b = VI_blockcreate_li((vsip_length)n, h);
   vsip_vview_li* v = (vsip_vview_li*)NULL;
   if(b != (vsip_block_li*)NULL){
      v = vsip_vbind_li(b, (vsip_offset)0, (vsip_stride)1, n);
      if(v == (vsip_vview_li*)NULL) vsip_blockdestroy_li(b);
   }
   return v;
}
