/* Created RJudd September 23, 2000 */
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
/* $Id: vsip_vput_f.c,v 2.0 2003/02/22 15:19:17 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_f.h"

void (vsip_vput_f)(
  const vsip_vview_f *v,
  vsip_index i, 
  vsip_scalar_f s) {
   vsip_offset offset = (vsip_offset)((v->offset + 
                           (vsip_stride)i * v->stride) * v->block->rstride);
   *(v->block->array + offset) = s;
   return;
}
