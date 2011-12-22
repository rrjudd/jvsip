/* Created RJudd October 17, 1999*/
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
/* $Id: vsip_lusol_f.c,v 2.1 2003/03/08 14:43:34 judd Exp $ */
/* vsip_lusol_f */     
#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_ludattributes_f.h>
#include"VI_mrowview_f.h"
#include"VI_vget_f.h"

static void VI_vsubvmprodIP_f(
             const vsip_vview_f *a,
             const vsip_mview_f *B,
             const vsip_vview_f *r)
{
   vsip_scalar_f temp;
   vsip_length nx = 0, mx = 0;
   vsip_scalar_f  *ap = a->block->array + a->offset * a->block->rstride,
                  *ap0 = ap,
                  *rp = r->block->array + r->offset * a->block->rstride,
                 *Byp = B->block->array + B->offset * a->block->rstride,
                 *Bxp = Byp;
   vsip_stride BCst = B->col_stride * B->block->rstride,
               BRst = B->row_stride * B->block->rstride,
               rst  = r->stride * r->block->rstride;
   while(nx++ < B->row_length){
       temp = 0;
       mx = 0;
       while(mx++ < B->col_length){
           temp += (*ap * *Byp);
           ap += a->stride; Byp += BCst;
       }
       *rp -= temp;
       ap = ap0;
       Byp = (Bxp += BRst);
       rp += rst;
   }
}                                               

static void VI_solve_ut_f(
              const vsip_mview_f *R,
              const vsip_mview_f *B)
{
   vsip_length N = R->row_length;
   vsip_mview_f XX = *B;
   vsip_mview_f *X = &XX;
   vsip_vview_f xx, rr;
   vsip_vview_f *x = VI_mrowview_f(X,(vsip_index) (N-1),&xx);
   vsip_vview_f *r_d = VI_mrowview_f(R,(vsip_index) 0,&rr);
   vsip_vview_f rr_m = rr;
   vsip_vview_f *r_m = &rr_m;
   vsip_stride d_s = R->row_stride + R->col_stride;
   r_d->length = 1; r_d->offset += ((N-1) * d_s);
   r_m->length = 0; r_m->offset = r_d->offset + R->row_stride;
   X->col_length = 1; X->offset = x->offset;
   vsip_svmul_f((vsip_scalar_f) 1.0/(VI_VGET_F(r_d,0)),x,x);
   N--;
   while(N-- >0){
      r_d->offset -= d_s;
      r_m->length++; r_m->offset -= d_s;
      x->offset -= X->col_stride;
      VI_vsubvmprodIP_f(r_m,X,x);
      vsip_svmul_f((vsip_scalar_f) 1.0/(VI_VGET_F(r_d,0)),x,x);
      X->col_length++; X->offset = x->offset;
   }
   return;
}

static void VI_solve_ut_special_f(
              const vsip_mview_f *R,
              const vsip_mview_f *B)
{
   vsip_length N = R->row_length;
   vsip_mview_f XX = *B;
   vsip_mview_f *X = &XX;
   vsip_vview_f xx, rr;
   vsip_vview_f *x = VI_mrowview_f(X,(vsip_index) (N-1),&xx);
   vsip_vview_f *r_d = VI_mrowview_f(R,(vsip_index) 0,&rr);
   vsip_vview_f rr_m = rr;
   vsip_vview_f *r_m = &rr_m;
   vsip_stride d_s = R->row_stride + R->col_stride;
   r_d->offset += ((N-1) * d_s);
   r_m->length = 0; r_m->offset = r_d->offset + R->row_stride;
   X->col_length = 1; X->offset = x->offset;
   N--;
   while(N-- >0){
      r_m->length++; r_m->offset -= d_s;
      x->offset -= X->col_stride;
      VI_vsubvmprodIP_f(r_m,X,x);
      X->col_length++; X->offset = x->offset;
   }
   return;
}

static void VI_solve_lt_f(
              const vsip_mview_f *R,
              const vsip_mview_f *B)
{
   vsip_length N = R->row_length;
   vsip_mview_f XX = *B;
   vsip_mview_f *X = &XX;
   vsip_vview_f xx, rr;
   vsip_vview_f *x = VI_mrowview_f(X,(vsip_index)0,&xx);
   vsip_vview_f *r_d = VI_mrowview_f(R,(vsip_index) 0,&rr);
   vsip_vview_f rr_m = rr;
   vsip_vview_f *r_m = &rr_m;
   vsip_stride d_s = R->row_stride + R->col_stride;
   r_d->length = 1;
   r_m->length = 0;
   X->col_length = 1;
   vsip_svmul_f((vsip_scalar_f) 1.0/(VI_VGET_F(r_d,0)),x,x);
   N--;
   while(N-- >0){
      r_d->offset += d_s;
      r_m->length++; r_m->offset += R->col_stride;
      x->offset += X->col_stride;
      VI_vsubvmprodIP_f(r_m,X,x);
      vsip_svmul_f((vsip_scalar_f) 1.0/(VI_VGET_F(r_d,0)),x,x);
      X->col_length++;
   }
   return;
}

static void VI_solve_lt_special_f(
              const vsip_mview_f *R,
              const vsip_mview_f *B)
{
   vsip_length N = R->row_length;
   vsip_mview_f XX = *B;
   vsip_mview_f *X = &XX;
   vsip_vview_f xx, rr;
   vsip_vview_f *x = VI_mrowview_f(X,(vsip_index)0,&xx);
   vsip_vview_f *r_d = VI_mrowview_f(R,(vsip_index) 0,&rr);
   vsip_vview_f rr_m = rr;
   vsip_vview_f *r_m = &rr_m;
   r_d->length = 1;
   r_m->length = 0;
   X->col_length = 1;
   N--;
   while(N-- >0){
      r_m->length++; r_m->offset += R->col_stride;
      x->offset += X->col_stride;
      VI_vsubvmprodIP_f(r_m,X,x);
      X->col_length++;
   }
   return;
}

static void VI_sortIP_f(
     vsip_index *p, 
     const vsip_mview_f *B)
{
   vsip_length N = B->row_length,
               M = B->col_length,
               m,n;
   vsip_scalar_f *bp = B->block->array + B->offset * B->block->rstride;
   vsip_scalar_f *bp0 = bp,
                 *bp_exch; 
   vsip_stride row_st = B->row_stride * B->block->rstride,
               col_st = B->col_stride * B->block->rstride;
   vsip_scalar_f temp;
   for(m = 0; m<(M-1); m++){
      if(*p != 0){
          bp_exch = bp + *p * col_st;
          for(n=0; n<N; n++){
             temp = *bp;
             *bp = *bp_exch;
             *bp_exch = temp;
             bp += row_st; bp_exch += row_st;
          }
       }
       bp0 += col_st; bp = bp0; p++;
   }
   return;
}

static void VI_unsortIP_f(
     vsip_index *p, 
     const vsip_mview_f *B)
{
   vsip_length N = B->row_length,
               M = B->col_length,
               m,n;
   vsip_stride row_st = B->row_stride * B->block->rstride,
               col_st = B->col_stride * B->block->rstride;
   vsip_scalar_f *bp = B->block->array + B->offset * B->block->rstride;
   vsip_scalar_f *bp0 = bp + (M-2) * col_st,
                 *bp_exch; 
   vsip_scalar_f temp;
   bp = bp0;
   p += (M-2);
   for(m = 0; m<(M-1); m++){
      if(*p != 0){
          bp_exch = bp + *p * col_st;
          for(n=0; n<N; n++){
             temp = *bp;
             *bp = *bp_exch;
             *bp_exch = temp;
             bp += row_st; bp_exch += row_st;
          }
       }
       bp0 -= col_st; bp = bp0; p--;
   }
   return;
}
        
   
int vsip_lusol_f(
   const vsip_lu_f* lud,
   vsip_mat_op OpA,
   const vsip_mview_f *XB)
{
   int retval = 0;
   vsip_index *p = lud->P;
   vsip_mview_f AA = lud->LLU;
   vsip_mview_f *A = &AA;
   if(OpA == VSIP_MAT_NTRANS){
       VI_sortIP_f(p, XB);
       VI_solve_lt_special_f(A,XB);
       VI_solve_ut_f(A,XB);
   } else if( OpA == VSIP_MAT_TRANS){
      /* transpose A */
       vsip_stride temp = A->col_stride;
       A->col_stride = A->row_stride; 
       A->row_stride = temp;
      /* solve */
       VI_solve_lt_f(A,XB);
       VI_solve_ut_special_f(A,XB);
       VI_unsortIP_f(p, XB); 
   } else {
       retval = 1;
   }
   return retval;
}



                                                                         
