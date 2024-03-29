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
/* $Id: vsip_blockrelease_bl.c,v 2.1 2006/06/08 22:19:26 judd Exp $ */

#include"vsip.h"
#include"vsip_blockattributes_bl.h"

vsip_scalar_bl* (vsip_blockrelease_bl)(
  vsip_block_bl* b,
  vsip_scalar_bl update) {	
   if ((vsip_block_bl*) NULL == b) 
      return (vsip_scalar_bl*)NULL;  /* return null if block is null */
   else if (b->kind != VSIP_USER_BLOCK) 
      return (vsip_scalar_bl*)NULL;  /* null if not a user block     */
   else{
      b->update = update;
      b->admit = VSIP_RELEASED_BLOCK;
      return b->array;
   }
}

