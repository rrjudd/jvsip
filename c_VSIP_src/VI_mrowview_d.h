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
/* $Id: VI_mrowview_d.h,v 2.0 2003/02/22 15:18:33 judd Exp $ */
#ifndef VI_MROWVIEW_D_H
#define VI_MROWVIEW_D_H 1

#include<vsip.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_vviewattributes_d.h>

static
vsip_vview_d* 
VI_mrowview_d(
  const vsip_mview_d* v,
  vsip_index i,
  vsip_vview_d *a) {
    a->block    = v->block;
    a->offset   = v->offset + i * v->col_stride;
    a->stride   = v->row_stride;
    a->length   = v->row_length;
    a->markings = v->markings;
    return a;
}
#endif
