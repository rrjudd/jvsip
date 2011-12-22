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
/* $Id: vsip_tput_i.c,v 2.0 2003/02/22 15:19:07 judd Exp $ */

#include"VI_support_priv_i.h"

void (vsip_tput_i)(
  const vsip_tview_i *v,
  vsip_index zindex,
  vsip_index yindex,
  vsip_index xindex,
  vsip_scalar_i s) {
   vsip_offset offset = (vsip_offset)(v->offset + 
                      (vsip_stride)zindex * v->z_stride + 
                      (vsip_stride)yindex * v->y_stride + 
                      (vsip_stride)xindex * v->x_stride);
   *(v->block->array + offset) = s;
   return;
}
