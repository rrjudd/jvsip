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
/* $Id: VI_mcolview_f.h,v 2.0 2003/02/22 15:18:32 judd Exp $ */
#ifndef VI_MCOLVIEW_F_H
#define VI_MCOLVIEW_F_H 1

#include<vsip.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>

static
vsip_vview_f* 
VI_mcolview_f(
  const vsip_mview_f* v,
  vsip_index i,
  vsip_vview_f *a) {
    a->block    = v->block;
    a->offset   = v->offset + i * v->row_stride;
    a->stride   = v->col_stride;
    a->length   = v->col_length;
    a->markings = v->markings;
    return a;
}
#endif
