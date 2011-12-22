/* Created RJudd November 2, 2002       */
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
/* $Id: VI_cblockbind_f_ds.h,v 2.0 2003/02/22 15:18:28 judd Exp $ */
/* VI_cblockbind_f default split */


if(b != (vsip_cblock_f*)NULL){
   b->size     = N;
   b->kind     = VSIP_USER_BLOCK;
   b->admit    = VSIP_RELEASED_BLOCK;
   b->markings = VSIP_VALID_STRUCTURE_OBJECT;
   b->bindings = 0;
   if(Ip == (vsip_scalar_f*)NULL){ /* interleaved */
      b->cstride = 2;
      b->R = vsip_blockbind_f(Rp,N,h);
      b->I = (vsip_block_f*)malloc(sizeof(vsip_block_f));
      if((b->R == (vsip_block_f*)NULL) || 
         (b->I == (vsip_block_f*)NULL)){ /* fail; cleanup and exit */
         free((void *)b->R); 
         free((void *)b->I);
         free((void *)b);
         b = (vsip_cblock_f*)NULL;
      } else {
         b->R->rstride = b->cstride;
         b->R->kind = VSIP_DERIVED_BLOCK;
         b->R->parent = b;
         *b->I = *b->R;
         b->I->array++;
      }
   } else { /* split */
      b->cstride = 1;
      b->R = vsip_blockbind_f(Rp,N,h);
      b->I = vsip_blockbind_f(Ip,N,h);
      if((b->R == (vsip_block_f*)NULL) || 
         (b->I == (vsip_block_f*)NULL)){ /* fail; cleanup and exit */
         free((void *)b->R); 
         free((void *)b->I);
         free((void *)b);
         b = (vsip_cblock_f*)NULL;
      } else { /* success; finish block */
         b->R->kind = VSIP_DERIVED_BLOCK;
         b->R->parent = b;
         b->I->kind = VSIP_DERIVED_BLOCK;
         b->I->parent = b;
      }
   }
}

