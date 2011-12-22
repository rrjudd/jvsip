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
/* $Id: VI_cblockcreate_d.h,v 2.1 2006/06/08 22:19:26 judd Exp $ */

#include<vsip.h>
#include<vsip_cblockattributes_d.h>

#ifndef VI_CBLOCKCREATE_D_H
#define VI_CBLOCKCREATE_D_H
#include"VI_blockcreate_d.h"
#include"VI_blockdestroy_d.h"

static
vsip_cblock_d* 
VI_cblockcreate_d(
   size_t N, 
   vsip_memory_hint h) {
  vsip_cblock_d* b = (vsip_cblock_d*)malloc(sizeof(vsip_cblock_d));
  if(b != NULL){
      b->kind     = VSIP_VSIPL_BLOCK;
      b->admit    = VSIP_ADMITTED_BLOCK;
      b->markings = VSIP_VALID_STRUCTURE_OBJECT;
      b->size     = N;      /* size in complex elements         */
      b->bindings = 0;
      b->hint     = h;
      #if defined(VSIP_DEFAULT_SPLIT) || defined(VSIP_ALWAYS_SPLIT)
         b->cstride  = 1;   /* native block are split           */
         b->R = VI_blockcreate_d(N,h);
         b->I = VI_blockcreate_d(N,h);
         if((b->R == NULL) || (b->I == NULL)){
            VI_blockdestroy_d(b->R);
            VI_blockdestroy_d(b->I);
            free((void *)b);
            b = (vsip_cblock_d*)NULL;
         } else {
            /* modifiy real                                       */
            b->R->kind       = VSIP_DERIVED_BLOCK;
            b->I->kind       = VSIP_DERIVED_BLOCK;
            b->R->parent  = b;
            b->I->parent  = b;
         }
      #else
         b->cstride  = 2;   /* native block are interleaved     */
         b->R = VI_blockcreate_d(2 * N,h);
         b->I = (vsip_block_d*)malloc(sizeof(vsip_block_d));
         if((b->R == NULL) || (b->I == NULL)){
            VI_blockdestroy_d(b->R);
            free((void *)b->I);
            free((void *)b);
            b = (vsip_cblock_d*)NULL;
         } else {
            /* modifiy real                                       */
            b->R->kind       = VSIP_DERIVED_BLOCK;
            b->R->rstride = b->cstride;
            b->R->size    = N;  /* size in real elements          */
            b->R->parent  = b;
            /* initiate imaginary                                 */
            /* same as real except array data pointer one greater */
            *b->I = *b->R;
            b->I->array++;
         }
      #endif
      #if defined(VSIP_ALWAYS_INTERLEAVED) 
         b->data = ((void*)0);
         b->Rp = (vsip_scalar_d*)NULL;
         b->Ip = (vsip_scalar_d*)NULL;
      #elif defined(VSIP_ALWAYS_SPLIT)
         b->r_data = ((void*)0);
         b->i_data = ((void*)0);
         b->Rp = (vsip_scalar_d*)NULL;
         b->Ip = (vsip_scalar_d*)NULL;
      #endif
      b->a_scalar.r = 0.0; b->a_scalar.i = 0.0;
      b->a_zero.r = 0.0; b->a_zero.i = 0.0;
      b->a_one.r = 1.0; b->a_one.i = 0.0;
      b->a_imag_one.r = 0.0; b->a_imag_one.i = 1.0;
  }    
  return b;
}
#endif
