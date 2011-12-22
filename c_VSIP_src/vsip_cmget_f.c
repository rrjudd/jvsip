/* Created RJudd September 22, 2000 */
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
/* $Id: vsip_cmget_f.c,v 2.0 2003/02/22 15:18:42 judd Exp $ */

#include<vsip.h>
#include<vsip_cmviewattributes_f.h>

vsip_cscalar_f (vsip_cmget_f)(
  const vsip_cmview_f *v, 
  vsip_index row, 
  vsip_index col) {
   vsip_offset offset = (vsip_offset)(v->block->cstride * (v->offset + 
                    (vsip_stride)row * v->col_stride + 
                    (vsip_stride)col * v->row_stride));
   vsip_cscalar_f retval;
   retval.r = *(v->block->R->array + offset); 
   retval.i = *(v->block->I->array + offset); 
   return retval;
}
