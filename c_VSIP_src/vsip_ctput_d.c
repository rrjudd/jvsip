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
/* $Id: vsip_ctput_d.c,v 2.0 2003/02/22 15:18:49 judd Exp $ */

#include"VI_support_cpriv_d.h"

void (vsip_ctput_d)(
  const vsip_ctview_d *v,
  vsip_index zindex,
  vsip_index yindex,
  vsip_index xindex,
  vsip_cscalar_d s) {
   vsip_offset offset = (vsip_offset)((v->offset + 
                       (vsip_stride)zindex * v->z_stride + 
                       (vsip_stride)yindex * v->y_stride + 
                       (vsip_stride)xindex * v->x_stride) * v->block->cstride);
   *(v->block->R->array + offset) = s.r;
   *(v->block->I->array + offset) = s.i;
   return;
}
