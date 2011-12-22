/* Created RJudd September 30, 2000 */
/* SPAWARYSCEN D857                 */
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
/* $Id: vsip_vputoffset_f.c,v 2.0 2003/02/22 15:19:17 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>

vsip_vview_f* (vsip_vputoffset_f)(
  vsip_vview_f* v, 
  vsip_offset o) {
    v->offset = o;
    return v;
}
