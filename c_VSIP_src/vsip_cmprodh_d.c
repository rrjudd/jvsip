/* Created R. Judd March 12, 1998 */
/* SPAWARSYSCEN D881 */
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
/* $Id: vsip_cmprodh_d.c,v 2.0 2003/02/22 15:18:43 judd Exp $ */
/* April 20, 1998 RJudd 1,2 to row,col*/
/* vsip_cmprodh_d.c used cmprodj */
/* vsip_cmprodj_d.c used cmprod */
/* Removed Tisdale error checking Sept 00 */

#include"vsip.h"
#include"vsip_cmviewattributes_d.h"
#include"vsip_cvviewattributes_d.h"

void (vsip_cmprodh_d)(
  const vsip_cmview_d* A,
  const vsip_cmview_d* B,
  const vsip_cmview_d* R) {
  { 
    vsip_length M = A->col_length,
                N = B->col_length;
    vsip_stride cRst = R->block->cstride;
    vsip_cscalar_d tmp;
    vsip_length i,j;
    vsip_cvview_d aa,bb,rr,*a,*b,*r;
    a = &aa; b = &bb; r = &rr;
    /* row view */
    a->block = A->block;
    a->offset = A->offset;
    a->stride = A->row_stride;
    a->length = A->row_length;
    /* row view */
    b->block = B->block;
    b->offset = B->offset;
    b->stride = B->row_stride;
    b->length = B->row_length;
    /* row view */
    r->block = R->block;
    r->offset = R->offset;
    r->stride = R->row_stride;
    r->length = R->row_length;
    a->markings = vsip_valid_structure_object; 
    b->markings = vsip_valid_structure_object;
    r->markings = vsip_valid_structure_object;
 
    for(i = 0; i < M; i++){
      vsip_scalar_d  *r_pr =(vsip_scalar_d*) (r->block->R->array + cRst * r->offset); 
      vsip_scalar_d  *r_pi =(vsip_scalar_d*) (r->block->I->array + cRst * r->offset); 
      vsip_stride str = cRst * r->stride;
      b->offset = B->offset;
      for(j =0; j < N; j++){
          tmp  = vsip_cvjdot_d(a,b);
          *r_pr = tmp.r; *r_pi =tmp.i; 
          r_pr += str; r_pi += str;
         b->offset += B->col_stride;
      }
      a->offset += A->col_stride;
      r->offset += R->col_stride;
    }
  }
}

