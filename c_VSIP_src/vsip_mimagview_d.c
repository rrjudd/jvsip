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
/* $Id: vsip_mimagview_d.c,v 2.0 2003/02/22 15:18:57 judd Exp $ */

#include<vsip.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_mviewattributes_d.h>

vsip_mview_d* (vsip_mimagview_d)(
  const vsip_cmview_d* v) {
    return vsip_mbind_d(
              v->block->I,
              v->offset,
              v->col_stride,
              v->col_length,
              v->row_stride,
              v->row_length);
}
