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
/* $Id: vsip_mput_uc.c,v 2.0 2003/02/22 15:18:59 judd Exp $ */

#include"vsip.h"
#include"vsip_mviewattributes_uc.h"

void (vsip_mput_uc)(
  const vsip_mview_uc *v,
  vsip_index row, 
  vsip_index col, 
  vsip_scalar_uc s) {
   vsip_offset offset = (vsip_offset)(v->offset + 
                          (vsip_stride)row * v->col_stride + 
                          (vsip_stride)col * v->row_stride);
   *(v->block->array + offset) = s;
   return;
}
