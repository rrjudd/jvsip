/* Created RJudd September 30, 2000 */
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
/* $Id: vsip_ctputattrib_f.c,v 2.0 2003/02/22 15:18:49 judd Exp $ */

#include"VI_support_cpriv_f.h"

void (vsip_ctputattrib_f)(
  vsip_ctview_f *v,
  const vsip_ctattr_f *attr) {
    v->offset = attr->offset;
    v->z_length = attr->z_length;
    v->y_length = attr->y_length;
    v->x_length = attr->x_length;
    v->z_stride = attr->z_stride;
    v->y_stride = attr->y_stride;
    v->x_stride = attr->x_stride;
    return;
}
