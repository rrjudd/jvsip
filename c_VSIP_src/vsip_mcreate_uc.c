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
/* $Id: vsip_mcreate_uc.c,v 2.0 2003/02/22 15:18:55 judd Exp $ */

#include<vsip.h>
#include"VI_blockcreate_uc.h"
#include"VI_blockdestroy_uc.h"

vsip_mview_uc* (vsip_mcreate_uc)(
  vsip_length col_length, 
  vsip_length row_length, 
  vsip_major major, 
  vsip_memory_hint mem_hint) {
   vsip_block_uc* b = VI_blockcreate_uc(
             (size_t)(col_length * row_length), mem_hint);
   vsip_mview_uc* v = (vsip_mview_uc*)NULL;
   if(b != NULL){

      v = (major == VSIP_ROW)
      ?
      vsip_mbind_uc(b, (vsip_offset)0,
          (vsip_stride)row_length, col_length,
          (vsip_stride)1, row_length)
      :
      vsip_mbind_uc(b, (vsip_offset)0,
          (vsip_stride)1,col_length,
          (vsip_stride)col_length, row_length);
    
      if(v == (vsip_mview_uc*)NULL) VI_blockdestroy_uc(b);
   }
   return v;
}
