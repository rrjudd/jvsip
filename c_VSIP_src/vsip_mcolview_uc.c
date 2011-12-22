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
/* $Id: vsip_mcolview_uc.c,v 2.0 2003/02/22 15:18:55 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_uc.h>
#include<vsip_vviewattributes_uc.h>

vsip_vview_uc* (vsip_mcolview_uc)(
   const vsip_mview_uc* v, 
   vsip_index j) { 
   return vsip_vbind_uc(
                  v->block, 
                  v->offset + j * v->row_stride, 
                  v->col_stride,
                  v->col_length);
}
