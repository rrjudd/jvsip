/* Created RJudd September 15, 2000 */
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
/* $Id: vsip_blockdestroy_mi.c,v 2.0 2003/02/22 15:18:37 judd Exp $ */

#include<vsip.h>
#include<vsip_blockattributes_mi.h>

void (vsip_blockdestroy_mi)(
  vsip_block_mi* b) {
   if (NULL != b) {
      b->markings = VSIP_FREED_STRUCTURE_OBJECT;
      if (b->kind == VSIP_VSIPL_BLOCK) free((void*)b->array);
      free((void*)b);
   }
   return;
}
