/* Created RJudd */
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
/* $Id: vsip_blockrebind_uc.c,v 2.1 2009/05/20 17:11:15 judd Exp $ */

#include<vsip.h>
#include<vsip_blockattributes_uc.h>

vsip_scalar_uc* (vsip_blockrebind_uc)(
  vsip_block_uc *b,
  vsip_scalar_uc * const data) {	
   if ((vsip_block_uc*) NULL == b) return (vsip_scalar_uc*)NULL;
   else
   if (b->admit != VSIP_RELEASED_BLOCK) return (vsip_scalar_uc*)NULL; 
   else{
      vsip_scalar_uc *oldArray = b->array;
      b->array = data;
      return oldArray;
   }
}

