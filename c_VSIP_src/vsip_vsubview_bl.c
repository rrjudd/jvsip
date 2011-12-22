/* Created RJudd October 3, 2000 */
/* SPAWARSYSCEN D857             */
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
/* $Id: vsip_vsubview_bl.c,v 2.0 2003/02/22 15:19:18 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_bl.h>

vsip_vview_bl* (vsip_vsubview_bl)(
  const vsip_vview_bl* v, 
  vsip_index i, 
  vsip_length n) {
    return vsip_vbind_bl(v->block, 
                         v->offset + i * v->stride,
                         v->stride, 
                         n);
}
