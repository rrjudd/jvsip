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
/* $Id: VI_mrowview_i.h,v 2.1 2004/04/03 14:37:17 judd Exp $ */
#ifndef VI_MROWVIEW_I_H
#define VI_MROWVIEW_I_H

#include<vsip.h>
#include<vsip_mviewattributes_i.h>
#include<vsip_vviewattributes_i.h>

static
vsip_vview_i* 
VI_mrowview_i(
  const vsip_mview_i* v,
  vsip_index i,
  vsip_vview_i *a) {
    a->block    = v->block;
    a->offset   = v->offset + i * v->col_stride;
    a->stride   = v->row_stride;
    a->length   = v->row_length;
    a->markings = v->markings;
    return a;
}
#endif
