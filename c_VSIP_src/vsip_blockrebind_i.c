/* Created RJudd September 17, 2000 */
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
/* $Id: vsip_blockrebind_i.c,v 2.1 2009/05/20 17:11:15 judd Exp $ */

#include"vsip.h"
#include"vsip_blockattributes_i.h"

vsip_scalar_i* (vsip_blockrebind_i)(
  vsip_block_i *b,
  vsip_scalar_i * const data) {	
   if ((vsip_block_i*) NULL == b) return (vsip_scalar_i*)NULL;
   else
   if (b->admit != VSIP_RELEASED_BLOCK) return (vsip_scalar_i*)NULL; 
   else{
      vsip_scalar_i *oldArray = b->array;
      b->array = data;
      return oldArray;
   }
}

