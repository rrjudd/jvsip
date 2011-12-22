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
/* $Id: vsip_rvcmmul_f.c,v 2.1 2003/03/08 14:43:35 judd Exp $ */
#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_cmviewattributes_f.h>
#include"VI_cmcolview_f.h"
#include"VI_cmrowview_f.h"

void (vsip_rvcmmul_f)(
  const vsip_vview_f* a,
  const vsip_cmview_f* B,
  vsip_major major,
  const vsip_cmview_f* R) {
  vsip_cvview_f bb,*b,rr,*r;
  vsip_stride sb,sr;
  vsip_length L;
  if(major == VSIP_ROW){
     sb = B->col_stride;
     sr = R->col_stride;
     L  = B->col_length;
     b = VI_cmrowview_f(B,0,&bb);
     r = VI_cmrowview_f(R,0,&rr);
  } else {
     sb = B->row_stride;
     sr = R->row_stride;
     L  = B->row_length;;
     b = VI_cmcolview_f(B,0,&bb);
     r = VI_cmcolview_f(R,0,&rr);
  }
  while(L-- >0){
     {
         /* register */ vsip_length n = r->length;
         vsip_stride cbst = b->block->cstride;
         vsip_stride crst = r->block->cstride;
         vsip_scalar_f *ap  = (vsip_scalar_f *)((a->block->array) + a->offset * a->block->rstride),
                       *bpr = (vsip_scalar_f *)((b->block->R->array) + cbst * b->offset),
                       *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
         vsip_scalar_f *bpi = (vsip_scalar_f *)((b->block->I->array) + cbst * b->offset),
                       *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
         vsip_scalar_f  temp = 0;
         /* register */ vsip_stride ast = a->stride * a->block->rstride,
                                    bst = (cbst * b->stride), 
                                    rst = (crst * r->stride);
         /*end define*/
         while(n-- > 0){
             temp = *ap * *bpr ;
             *rpi = *ap * *bpi;
             *rpr = temp;
             ap += ast; 
             bpr += bst; bpi += bst;
             rpr += rst; rpi += rst;
         }
      }
      b->offset += sb;
      r->offset += sr;
   }
   return;
}

