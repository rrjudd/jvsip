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
/* $Id: vsip_timagview_d.c,v 2.0 2003/02/22 15:19:07 judd Exp $ */

#include"VI_support_cpriv_d.h"

vsip_tview_d *vsip_timagview_d(
  const vsip_ctview_d* v) {
    return vsip_tbind_d(
              v->block->I,
              v->offset,
              v->z_stride,
              v->z_length,
              v->y_stride,
              v->y_length,
              v->x_stride,
              v->x_length);
}
