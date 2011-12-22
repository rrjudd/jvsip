/* Created RJudd */
/* SPAWARSYSCEN D857                */
/**********************************************************************
e/ For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
/* $Id: vsip_tputattrib_uc.c,v 2.0 2003/02/22 15:19:07 judd Exp $ */
#include"VI_support_priv_uc.h"

void (vsip_tputattrib_uc)(
  vsip_tview_uc *v,
  const vsip_tattr_uc *attr) {
    v->offset   = attr->offset;
    v->z_length = attr->z_length;
    v->y_length = attr->y_length;
    v->x_length = attr->x_length;
    v->z_stride = attr->z_stride;
    v->y_stride = attr->y_stride;
    v->x_stride = attr->x_stride;
    return;
}
