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
/* $Id: vsip_vgetattrib_bl.c,v 2.0 2003/02/22 15:19:13 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_bl.h>

void (vsip_vgetattrib_bl)(
  const vsip_vview_bl* v,
  vsip_vattr_bl *attr){
    attr->block  = v->block;
    attr->offset = v->offset;
    attr->stride = v->stride;
    attr->length = v->length;
}
