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
/* $Id: vsip_cmprodj_f.c,v 2.0 2003/02/22 15:18:43 judd Exp $ */
/* vsip_cmprodj_f.c used cmprod */
/* April 20, 1998 1,2 to row,col */
/* Remove Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_cmviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_cmprodj_f)(
  const vsip_cmview_f* A,
  const vsip_cmview_f* B,
  const vsip_cmview_f* R) {
  { 
    vsip_length M = A->col_length,
                N = B->row_length;
    int cRst = R->block->cstride;
    vsip_cscalar_f tmp;
    vsip_length i,j;
    vsip_cvview_f aa,bb,rr,*a,*b,*r;
    a = &aa; b = &bb; r = &rr;
    /* row view */
    a->block = A->block;
    a->offset = A->offset;
    a->stride = A->row_stride;
    a->length = A->row_length;
    /* col view */
    b->block = B->block;
    b->offset = B->offset;
    b->stride = B->col_stride;
    b->length = B->col_length;
    /* row view */
    r->block = R->block;
    r->offset = R->offset;
    r->stride = R->row_stride;
    r->length = R->row_length;

    a->markings = vsip_valid_structure_object;
    b->markings = vsip_valid_structure_object;
    r->markings = vsip_valid_structure_object;

    for(i = 0; i < M; i++){
      vsip_scalar_f  *r_pr =(vsip_scalar_f*) (r->block->R->array + cRst * r->offset); 
      vsip_scalar_f  *r_pi =(vsip_scalar_f*) (r->block->I->array + cRst * r->offset); 
      vsip_length str = cRst * r->stride;
      b->offset = B->offset;
      for(j =0; j < N; j++){
         tmp  = vsip_cvjdot_f(a,b);
         *r_pr = tmp.r; *r_pi =tmp.i; 
         r_pr += str; r_pi += str;
         b->offset += B->row_stride;
      }
      a->offset += A->col_stride;
      r->offset += R->col_stride;
    }
  }
}

