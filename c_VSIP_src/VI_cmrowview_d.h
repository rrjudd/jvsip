/* Created RJudd July 22, 2002   */
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
/* $Id: VI_cmrowview_d.h,v 2.0 2003/02/22 15:18:30 judd Exp $ */
#ifndef VI_CMROWVIEW_D_H
#define VI_CMROWVIEW_D_H

#include"vsip.h"
#include"vsip_cmviewattributes_d.h"
#include"vsip_cvviewattributes_d.h"

static
vsip_cvview_d* 
VI_cmrowview_d(
  const vsip_cmview_d* v, 
  vsip_index i, 
  vsip_cvview_d *a) {
    a->block    = v->block;
    a->offset   = v->offset + i * v->col_stride;
    a->stride   = v->row_stride;
    a->length   = v->row_length;
    a->markings = v->markings;
    return a;
}
#endif
