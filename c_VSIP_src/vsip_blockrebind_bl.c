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
/* $Id: vsip_blockrebind_bl.c,v 2.0 2003/02/22 15:18:37 judd Exp $ */

#include"vsip.h"
#include"vsip_blockattributes_bl.h"

vsip_scalar_bl* (vsip_blockrebind_bl)(
  vsip_block_bl *b,
  vsip_scalar_bl *data) {	
   if (b == (vsip_block_bl*) NULL) return (vsip_scalar_bl*)NULL;
   else
   if (b->admit != VSIP_RELEASED_BLOCK) return (vsip_scalar_bl*)NULL; 
   else{
      vsip_scalar_bl *oldArray = b->array;
      b->array = data;
      return oldArray;
   }
}

