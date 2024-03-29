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
/* $Id: vsip_rvcmmul_d.c,v 2.1 2003/03/08 14:43:35 judd Exp $ */
#include"vsip.h"
#include"vsip_vviewattributes_d.h"
#include"vsip_cvviewattributes_d.h"
#include"vsip_cmviewattributes_d.h"
#include"VI_cmcolview_d.h"
#include"VI_cmrowview_d.h"

void (vsip_rvcmmul_d)(
  const vsip_vview_d* a,
  const vsip_cmview_d* B,
  vsip_major major,
  const vsip_cmview_d* R) {
  vsip_cvview_d bb,*b,rr,*r;
  vsip_stride sb,sr;
  vsip_length L;
  if(major == VSIP_ROW){
     sb = B->col_stride;
     sr = R->col_stride;
     L  = B->col_length;
     b = VI_cmrowview_d(B,0,&bb);
     r = VI_cmrowview_d(R,0,&rr);
  } else {
     sb = B->row_stride;
     sr = R->row_stride;
     L  = B->row_length;;
     b = VI_cmcolview_d(B,0,&bb);
     r = VI_cmcolview_d(R,0,&rr);
  }
  while(L-- >0){
     {
         /* register */ vsip_length n = r->length;
         vsip_stride cbst = b->block->cstride;
         vsip_stride crst = r->block->cstride;
         vsip_scalar_d *ap  = (vsip_scalar_d *)((a->block->array) + a->offset * a->block->rstride),
                       *bpr = (vsip_scalar_d *)((b->block->R->array) + cbst * b->offset),
                       *rpr = (vsip_scalar_d *)((r->block->R->array) + crst * r->offset);
         vsip_scalar_d *bpi = (vsip_scalar_d *)((b->block->I->array) + cbst * b->offset),
                       *rpi = (vsip_scalar_d *)((r->block->I->array) + crst * r->offset);
         vsip_scalar_d  temp = 0;
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

