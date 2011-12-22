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
/* $Id: VI_blockcreate_f.h,v 2.1 2006/06/08 22:19:26 judd Exp $ */

#include<vsip.h>
#include<vsip_blockattributes_f.h>

#ifndef VI_BLOCKCREATE_F_H
#define VI_BLOCKCREATE_F_H

static
vsip_block_f* 
VI_blockcreate_f(
  size_t N, 
  vsip_memory_hint h) {
  vsip_block_f* b = (vsip_block_f*)malloc(sizeof(vsip_block_f));
  if(b != NULL){
      b->array = (vsip_scalar_f*)malloc(N * sizeof(vsip_scalar_f));
      if(b->array == (vsip_scalar_f*)NULL){
         free((void*)b);
         b = (vsip_block_f*)NULL;
      } else {
         b->kind     = VSIP_VSIPL_BLOCK;
         b->admit    = VSIP_ADMITTED_BLOCK;
         b->markings = VSIP_VALID_STRUCTURE_OBJECT;
         b->size     = N; /* size in block elements */
         b->rstride  = 1;
         b->bindings = 0;
         b->hint     = h;
         b->parent = (vsip_cblock_f*)NULL;
      }
  }
  return b;
}
#endif
