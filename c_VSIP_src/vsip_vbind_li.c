/* Created RJudd September 19, 2000 */
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
/* $Id: vsip_vbind_li.c,v 2.0 2003/02/22 15:19:10 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_li.h"

vsip_vview_li* (vsip_vbind_li)(
  const vsip_block_li* b, 
  vsip_offset o, 
  vsip_stride s, 
  vsip_length n) {
   vsip_vview_li* v = (vsip_vview_li*)malloc(sizeof(vsip_vview_li));
   if(v != (vsip_vview_li*)NULL){
        v->block  = (vsip_block_li*)b;
        v->offset = o;
        v->stride = s;
        v->length = n;
        v->markings = VSIP_VALID_STRUCTURE_OBJECT;
   }
   return v;
}

