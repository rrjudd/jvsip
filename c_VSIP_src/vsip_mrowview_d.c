/* Created RJudd October 6, 2000 */
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
/* $Id: vsip_mrowview_d.c,v 2.0 2003/02/22 15:19:00 judd Exp $ */

#include"vsip.h"
#include"vsip_mviewattributes_d.h"
#include"vsip_vviewattributes_d.h"

vsip_vview_d* (vsip_mrowview_d)(
  const vsip_mview_d* v, 
  vsip_index i) {
    return vsip_vbind_d(
                   v->block, 
                   v->offset + i * v->col_stride, 
                   v->row_stride, 
                   v->row_length);
}
