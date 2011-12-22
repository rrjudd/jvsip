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
/* $Id */

#include<vsip.h>
#ifndef VI_VCREATE_D_H
#define VI_VCREATE_D_H

#include"VI_blockcreate_d.h"
#include"VI_blockdestroy_d.h"

static
vsip_vview_d* 
VI_vcreate_d(
          vsip_length n, 
          vsip_memory_hint h) {
   vsip_block_d* b = VI_blockcreate_d((size_t)n, h);
   vsip_vview_d* v = (vsip_vview_d*)NULL;
   if(b != (vsip_block_d*)NULL){
      v = vsip_vbind_d(b, (vsip_offset)0, (vsip_stride)1, n);
      if(v == (vsip_vview_d*)NULL) VI_blockdestroy_d(b);
   }
   return v;
}

#endif
