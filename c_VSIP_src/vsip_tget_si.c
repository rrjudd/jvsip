/* Created RJudd September 22, 2000 */
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
/* $Id: vsip_tget_si.c,v 2.0 2003/02/22 15:19:05 judd Exp $ */

#include"VI_support_priv_si.h"

vsip_scalar_si vsip_tget_si(
  const vsip_tview_si *v,
  vsip_index zindex,
  vsip_index yindex,
  vsip_index xindex) {
   return (*(v->block->array + (vsip_offset)(v->offset + 
                v->z_stride * (vsip_stride)zindex + 
                v->y_stride * (vsip_stride)yindex + 
                v->x_stride * (vsip_stride)xindex))); 
}
