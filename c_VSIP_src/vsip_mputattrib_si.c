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
/* $Id: vsip_mputattrib_si.c,v 2.0 2003/02/22 15:18:59 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_si.h>

vsip_mview_si* (vsip_mputattrib_si)(
  vsip_mview_si* v, 
  const vsip_mattr_si *attr){
    v->offset = attr->offset;
    v->row_stride = attr->row_stride;
    v->row_length = attr->row_length;
    v->col_stride = attr->col_stride;
    v->col_length = attr->col_length;
    return v;
}
