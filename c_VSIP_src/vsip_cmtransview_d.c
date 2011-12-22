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
/* $Id: vsip_cmtransview_d.c,v 2.1 2003/03/08 14:43:34 judd Exp $ */

#include<vsip.h>
#include<vsip_cmviewattributes_d.h>

vsip_cmview_d* (vsip_cmtransview_d)(
  const vsip_cmview_d* v) {
    return vsip_cmbind_d(
                    v->block, 
                    v->offset,
                    v->row_stride, 
                    v->row_length, 
                    v->col_stride, 
                    v->col_length);
}
