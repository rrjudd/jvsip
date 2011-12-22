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
/* $Id: vsip_blockfind_uc.c,v 2.0 2003/02/22 15:18:37 judd Exp $ */

#include<vsip.h>
#include<vsip_blockattributes_uc.h>

vsip_scalar_uc* (vsip_blockfind_uc)(
  const vsip_block_uc* b) {
   if(b->admit == VSIP_RELEASED_BLOCK)
      return b->array;
   else
      return (vsip_scalar_uc*)NULL;
}
