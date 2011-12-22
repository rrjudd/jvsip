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
/* $Id: vsip_cvmmul_f.c,v 2.1 2003/03/08 14:43:34 judd Exp $ */
#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_cmviewattributes_f.h>
#include"VI_cmcolview_f.h"
#include"VI_cmrowview_f.h"

void (vsip_cvmmul_f)(
  const vsip_cvview_f *a,
  const vsip_cmview_f *B,
  vsip_major major,
  const vsip_cmview_f *R) {
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
          /*define variables*/
          /* register */ vsip_length n = r->length;
          vsip_stride cast = a->block->cstride;
          vsip_stride cbst = b->block->cstride;
          vsip_stride crst = r->block->cstride;
          vsip_scalar_f *apr = (vsip_scalar_f *)((a->block->R->array) + cast * a->offset),
                        *bpr = (vsip_scalar_f *)((b->block->R->array) + cbst * b->offset),
                        *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
          vsip_scalar_f *api = (vsip_scalar_f *)((a->block->I->array) + cast * a->offset),
                        *bpi = (vsip_scalar_f *)((b->block->I->array) + cbst * b->offset),
                        *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
          vsip_scalar_f temp;
          /* register */ vsip_stride ast = (cast * a->stride), 
                                     bst = (cbst * b->stride), 
                                     rst = (crst * r->stride);
          while(n-- > 0){
              temp = *apr * *bpr - *bpi * *api;
              *rpi = *apr * *bpi + *api * *bpr;
              *rpr = temp;
              apr += ast; api += ast; 
              bpr += bst; bpi += bst; 
              rpr += rst; rpi += rst;
          }
      }  
      b->offset += sb;
      r->offset += sr;
   }
   return;
}
