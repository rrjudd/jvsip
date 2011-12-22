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
/* $Id: vsip_ctgetattrib_d.c,v 2.0 2003/02/22 15:18:48 judd Exp $ */

#include"VI_support_cpriv_d.h"

void vsip_ctgetattrib_d(
  const vsip_ctview_d *v,
  vsip_ctattr_d *attr) {
    attr->z_length = v->z_length;
    attr->y_length = v->y_length;
    attr->x_length = v->x_length;
    attr->z_stride = v->z_stride;
    attr->y_stride = v->y_stride;
    attr->x_stride = v->x_stride;
    attr->offset   = v->offset;
    attr->block    = v->block;
    return;
}
