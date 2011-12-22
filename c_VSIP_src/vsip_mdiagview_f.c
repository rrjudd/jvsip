/* Created RJudd October 9, 2000 */
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
/* $Id: vsip_mdiagview_f.c,v 2.0 2003/02/22 15:18:56 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_f.h>

vsip_vview_f* (vsip_mdiagview_f)(
  const vsip_mview_f* v,
  int idiag) {
    vsip_index i = (idiag < 0) ? -idiag : 0,  /* row index of origin       */
               j = (idiag > 0) ?  idiag : 0;  /* col index of origin       */
    vsip_length n_row = v->col_length - i;    /* # rows from origin to end */
    vsip_length	n_col = v->row_length - j;    /* # cols from origin to end */
    return vsip_vbind_f(
                    v->block, 
                    v->offset + i * v->col_stride + j * v->row_stride, 
                    v->row_stride + v->col_stride, 
                    (n_row < n_col) ? n_row : n_col);
}
