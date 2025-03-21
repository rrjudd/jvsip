/* Created RJudd                    */
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
/* $Id: vsip_vget_uc.c,v 2.0 2003/02/22 15:19:13 judd Exp $ */
/* to add attribute support */

#include"vsip.h"
#include"vsip_vviewattributes_uc.h"

vsip_scalar_uc (vsip_vget_uc)(
  const vsip_vview_uc *v, 
  vsip_index i) {
   return (*(v->block->array + (vsip_offset)(v->offset + (vsip_stride)i * v->stride)));
}
