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
/* $Id: vsip_tputxstride_si.c,v 2.0 2003/02/22 15:19:08 judd Exp $ */


#include"VI_support_priv_si.h"

vsip_tview_si* (vsip_tputxstride_si)(
  vsip_tview_si *v,
  vsip_stride s) {
    v->x_stride = s;
    return v;
}
