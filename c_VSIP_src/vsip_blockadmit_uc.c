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
/* $Id: vsip_blockadmit_uc.c,v 2.1 2006/06/08 22:19:26 judd Exp $ */

#include<vsip.h>
#include<vsip_blockattributes_uc.h>

int (vsip_blockadmit_uc)(
  vsip_block_uc* b,
  vsip_scalar_bl update) {
   int blockadmit = (int)update; /* keep update from warning since don't use */
   if ((vsip_scalar_uc*)NULL == b->array) 
      blockadmit = 1;    /* fail if no data array  */
   else if (b->kind != VSIP_USER_BLOCK)
      blockadmit = 1;    /* fail if not user block */
   else{  
      b->admit = VSIP_ADMITTED_BLOCK;
      blockadmit = 0;    /* return zero on success */
   }
   return blockadmit;
}

