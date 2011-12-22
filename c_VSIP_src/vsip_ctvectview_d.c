/* Created RJudd */
/* SPAWARSYSCEN D857 */
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
/* $Id: vsip_ctvectview_d.c,v 2.0 2003/02/22 15:18:49 judd Exp $ */

#include"VI_support_cpriv_d.h"

vsip_cvview_d *vsip_ctvectview_d(
      const vsip_ctview_d *v,
      vsip_tvslice slice,
      vsip_index i,
      vsip_index j)
{
     vsip_cvview_d *cvview = (vsip_cvview_d*)NULL;
     vsip_cblock_d *block = v->block;
     vsip_offset offset = v->offset;
     if(slice == VSIP_TVX){
        offset += i * v->z_stride + j * v->y_stride;
        cvview = vsip_cvbind_d(block,offset,v->x_stride,v->x_length);

     } else if(slice == VSIP_TVY) {
        offset += i * v->z_stride + j * v->x_stride;
        cvview = vsip_cvbind_d(block,offset,v->y_stride,v->y_length);

     } else if(slice == VSIP_TVZ){
        offset += i * v->y_stride + j * v->x_stride;
        cvview = vsip_cvbind_d(block,offset,v->z_stride,v->z_length);

     }
     return cvview;
}
