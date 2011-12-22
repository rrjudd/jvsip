/* Created RJudd                 */
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
/* $Id: vsip_vsubview_uc.c,v 2.0 2003/02/22 15:19:18 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_uc.h>

vsip_vview_uc* (vsip_vsubview_uc)(
  const vsip_vview_uc* v, 
  vsip_index i, 
  vsip_length n) {
    return vsip_vbind_uc(v->block, 
                         v->offset + i * v->stride,
                         v->stride, 
                         n);
}
