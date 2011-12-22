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
/* $Id: vsip_mcreate_d.c,v 2.0 2003/02/22 15:18:55 judd Exp $ */

#include<vsip.h>
#include"VI_blockcreate_d.h"
#include"VI_blockdestroy_d.h"

vsip_mview_d* (vsip_mcreate_d)(
  vsip_length m, 
  vsip_length n, 
  vsip_major rc, 
  vsip_memory_hint h) {
   vsip_block_d* b = VI_blockcreate_d((size_t)(m*n), h);
   vsip_mview_d* v = (vsip_mview_d*)NULL;
   if(b != (vsip_block_d*)NULL){

      v = (rc == VSIP_ROW)
         ?  
         vsip_mbind_d(b, (vsip_offset)0,
           (vsip_stride)n, m, (vsip_stride)1, n)
         :  
         vsip_mbind_d(b, (vsip_offset)0,
           (vsip_stride)1, m, (vsip_stride)m, n);

      if(v == (vsip_mview_d*)NULL) VI_blockdestroy_d(b);
   }
   return v;
}

