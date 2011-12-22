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
/* $Id: vsip_mprodt_f.c,v 2.1 2003/03/08 14:43:34 judd Exp $ */
/* modified to vsip_mprodt_f.c     */
/* April 21, 1998 1,2 to row,col */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_vviewattributes_f.h>
#include"VI_mrowview_f.h"

void (vsip_mprodt_f)(
  const vsip_mview_f* A,
  const vsip_mview_f* B,
  const vsip_mview_f* R) {
  { 
    vsip_length M = A->col_length,
                N = B->col_length;
    vsip_length i,j;
    vsip_vview_f bb,aa,rr;
    for(i = 0; i < M; i++){
      vsip_vview_f  *a = VI_mrowview_f(A, i,&aa), 
                    *r = VI_mrowview_f(R, i,&rr);
      vsip_scalar_f *r_p = r->block->array + r->offset * r->block->rstride; 
      for(j =0; j < N; j++){
         vsip_vview_f *b = VI_mrowview_f(B,j,&bb);
         *r_p = vsip_vdot_f(a,b);
          r_p += r->stride;
      }
    }
  }
}

