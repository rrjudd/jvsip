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
/* $Id: vsip_cmcreate_d.c,v 2.0 2003/02/22 15:18:42 judd Exp $ */

#include<vsip.h>
#include"VI_cblockcreate_d.h"
#include"VI_cblockdestroy_d.h"

vsip_cmview_d* (vsip_cmcreate_d)(
  vsip_length m, 
  vsip_length n, 
  vsip_major rc, 
  vsip_memory_hint h) {
   vsip_cblock_d* b = VI_cblockcreate_d((size_t)(m*n), h);
   vsip_cmview_d* v = (vsip_cmview_d*)NULL;
   if(b != (vsip_cblock_d*)NULL){

      v = (rc == VSIP_ROW) 
      ?
      vsip_cmbind_d(b, (vsip_offset)0,
        (vsip_stride)n, m, (vsip_stride)1, n)
      :
      vsip_cmbind_d(b, (vsip_offset)0,
        (vsip_stride)1, m, (vsip_stride)m, n);

      if(v == (vsip_cmview_d*)NULL) VI_cblockdestroy_d(b);
   }
   return v;
}
