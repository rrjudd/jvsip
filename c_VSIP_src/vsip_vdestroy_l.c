/* Created RJudd September 21, 2000 */
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
/* $Id: vsip_vdestroy_l.c,v 2.0 2003/02/22 15:19:12 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_l.h>

vsip_block_l* (vsip_vdestroy_l)(
  vsip_vview_l* v) {
   vsip_block_l* b = (vsip_block_l*)NULL;
   if(v != (vsip_vview_l*)NULL){
      b = v->block;
      v->markings = VSIP_FREED_STRUCTURE_OBJECT;
      free((void*)v);
   }
   return b;
}
