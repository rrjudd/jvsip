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
/* $Id: vsip_mtransview_uc.c,v 2.1 2003/03/08 14:43:35 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_uc.h>

vsip_mview_uc* (vsip_mtransview_uc)(
  const vsip_mview_uc* v) {
    return vsip_mbind_uc(
                   v->block, 
                   v->offset, 
                   v->row_stride, 
                   v->row_length, 
                   v->col_stride, 
                   v->col_length);
}
