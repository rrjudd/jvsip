/* Created RJudd  */
/* SPAWARSYSCEN  */
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
/* $Id: VI_mcolview_si.h,v 2.1 2004/04/03 14:37:17 judd Exp $ */
#ifndef VI_MCOLVIEW_SI_H
#define VI_MCOLVIEW_SI_H 1

#include<vsip.h>
#include<vsip_mviewattributes_si.h>
#include<vsip_vviewattributes_si.h>

static
vsip_vview_si* 
VI_mcolview_si(
  const vsip_mview_si* v,
  vsip_index i,
  vsip_vview_si *a) {
    a->block    = v->block;
    a->offset   = v->offset + i * v->row_stride;
    a->stride   = v->col_stride;
    a->length   = v->col_length;
    a->markings = v->markings;
    return a;
}
#endif
