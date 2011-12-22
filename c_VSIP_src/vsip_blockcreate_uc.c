/* Created RJudd  */
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
/* $Id: vsip_blockcreate_uc.c,v 2.1 2006/06/08 22:19:26 judd Exp $ */

#include<vsip.h>
#include<vsip_blockattributes_uc.h>

vsip_block_uc* (vsip_blockcreate_uc)(
  size_t N, 
  vsip_memory_hint h) {
  vsip_block_uc* b = (vsip_block_uc*)malloc(sizeof(vsip_block_uc));
  if(b != NULL){
      b->array = (vsip_scalar_uc*)malloc(N * sizeof(vsip_scalar_uc));
      if(NULL == b->array){
         free((void*)b);
         b = (vsip_block_uc*)NULL;
      } else {
         b->kind     = VSIP_VSIPL_BLOCK;
         b->admit    = VSIP_ADMITTED_BLOCK;
         b->markings = VSIP_VALID_STRUCTURE_OBJECT;
         b->size     = N;
         b->bindings = 0;
         b->hint     = h;
      }
  }
  return b;
}
