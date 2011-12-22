/* Created RJudd February 16, 1999 */
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
/* $Id: vsip_vmmul_f.c,v 2.1 2003/03/08 14:43:35 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_mviewattributes_f.h>
#include"VI_mrowview_f.h"
#include"VI_mcolview_f.h"

void (vsip_vmmul_f)(
  const vsip_vview_f *a,
  const vsip_mview_f *B,
  vsip_major major,
  const vsip_mview_f *R) {
  vsip_vview_f bb,*b,rr,*r;
  vsip_stride sb,sr;
  vsip_length L;
  if(major == VSIP_ROW){
     sb = B->col_stride;
     sr = R->col_stride;
     L  = B->col_length;
     b = VI_mrowview_f(B,0,&bb);
     r = VI_mrowview_f(R,0,&rr);
  } else {
     sb = B->row_stride; 
     sr = R->row_stride; 
     L  = B->row_length;;
     b = VI_mcolview_f(B,0,&bb); 
     r = VI_mcolview_f(R,0,&rr);
  }
  while(L-- >0){
     { 
         /*define variables*/
         /* register */ vsip_length n = r->length;
         /* register */ vsip_stride ast = a->stride * a->block->rstride,
                                    bst = b->stride * b->block->rstride,
                                    rst = r->stride * r->block->rstride;
         vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
                       *bp = (b->block->array) + b->offset * b->block->rstride,
                       *rp = (r->block->array) + r->offset * r->block->rstride;
         /*end define*/
         while(n-- > 0){
            *rp = *ap * *bp;
            ap += ast; bp += bst; rp += rst;
         }
      }
      b->offset += sb;
      r->offset += sr;
   }
   return;
}
