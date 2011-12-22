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
/* $Id: VI_blockcreate_bl.h,v 2.1 2006/06/08 22:19:25 judd Exp $ */

#include<vsip.h>
#include<vsip_blockattributes_bl.h>

#ifndef VI_BLOCKCREATE_BL_H
#define VI_BLOCKCREATE_BL_H

static
vsip_block_bl* 
VI_blockcreate_bl(
  size_t N, 
  vsip_memory_hint h) {
  vsip_block_bl* b = (vsip_block_bl*)malloc(sizeof(vsip_block_bl));
  if(b != NULL){
      b->array = (vsip_scalar_bl*)malloc(N * sizeof(vsip_scalar_bl));
      if(NULL == b->array){
         free((void*)b);
         b = (vsip_block_bl*)NULL;
      } else {
         b->kind     = VSIP_VSIPL_BLOCK; 
         b->admit    = VSIP_ADMITTED_BLOCK;
         b->markings = VSIP_VALID_STRUCTURE_OBJECT;
         b->size     = N;  /* size in block elements */
         b->bindings = 0;
         b->hint     = h;
      }
  }
  return b;
}
#endif
