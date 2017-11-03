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
/* $Id: vsip_clusol_f.c,v 2.1 2003/03/08 14:43:34 judd Exp $ */
/* vsip_clusol_f */             
#include"vsip.h"
#include"vsip_cvviewattributes_f.h"
#include"vsip_cmviewattributes_f.h"
#include"vsip_cludattributes_f.h"
#include"VI_cmrowview_f.h"

static void VI_cvjsubvmprodIP_f(
             const vsip_cvview_f *a,
             const vsip_cmview_f *B,
             const vsip_cvview_f *r)
{
   vsip_scalar_f temp_r;
   vsip_scalar_f temp_i;
   vsip_length nx = 0, mx = 0;
   vsip_stride cast = a->block->cstride, crst = r->block->cstride, cBst = B->block->cstride;
   vsip_scalar_f  *ap_r  = (vsip_scalar_f*)(a->block->R->array + cast * a->offset),
                  *ap_i  = (vsip_scalar_f*)(a->block->I->array + cast * a->offset),
                  *rp_r  = (vsip_scalar_f*)(r->block->R->array + crst * r->offset),
                  *rp_i  = (vsip_scalar_f*)(r->block->I->array + crst * r->offset),
                  *Byp_r = (vsip_scalar_f*)(B->block->R->array + cBst * B->offset),
                  *Byp_i = (vsip_scalar_f*)(B->block->I->array + cBst * B->offset),
                  *Bxpr = Byp_r,
                  *Bxpi = Byp_i;
   vsip_stride sta = cast * a->stride, str = crst * r->stride, stB = cBst * B->col_stride;
   while(nx++ < B->row_length){
       temp_r = 0; temp_i = 0;
       mx = 0;
       while(mx++ < B->col_length){
           temp_r += (*ap_r * *Byp_r + *ap_i * *Byp_i);
           temp_i += (*ap_r * *Byp_i - *ap_i * *Byp_r);
           ap_r += sta; Byp_r += stB;
           ap_i += sta; Byp_i += stB;
       }
       *rp_r -= temp_r; *rp_i -= temp_i;
       ap_r = (vsip_scalar_f*)(a->block->R->array + cast * a->offset);
       ap_i = (vsip_scalar_f*)(a->block->I->array + cast * a->offset);
       Byp_r = (Bxpr += (cBst * B->row_stride));
       Byp_i = (Bxpi += (cBst * B->row_stride));
       rp_r += str; rp_i += str;
   }
}                                                        


static void VI_cvsubvmprodIP_f(
             const vsip_cvview_f *a,
             const vsip_cmview_f *B,
             const vsip_cvview_f *r)
{
   vsip_scalar_f temp_r;
   vsip_scalar_f temp_i;
   vsip_length nx = 0, mx = 0;
   vsip_stride cast = a->block->cstride, crst = r->block->cstride, cBst = B->block->cstride;
   vsip_scalar_f  *ap_r  = (vsip_scalar_f*)(a->block->R->array + cast * a->offset),
                  *ap_i  = (vsip_scalar_f*)(a->block->I->array + cast * a->offset),
                  *rp_r  = (vsip_scalar_f*)(r->block->R->array + crst * r->offset),
                  *rp_i  = (vsip_scalar_f*)(r->block->I->array + crst * r->offset),
                  *Byp_r = (vsip_scalar_f*)(B->block->R->array + cBst * B->offset),
                  *Byp_i = (vsip_scalar_f*)(B->block->I->array + cBst * B->offset),
                  *Bxpr = Byp_r,
                  *Bxpi = Byp_i;
   vsip_length sta = cast * a->stride, str = crst * r->stride, stB = cBst * B->col_stride;
   while(nx++ < B->row_length){
       temp_r = 0; temp_i = 0;
       mx = 0;
       while(mx++ < B->col_length){
           temp_r += (*ap_r * *Byp_r - *ap_i * *Byp_i);
           temp_i += (*ap_r * *Byp_i + *ap_i * *Byp_r);
           ap_r += sta; Byp_r += stB;
           ap_i += sta; Byp_i += stB;
       }
       *rp_r -= temp_r; *rp_i -= temp_i;
       ap_r = (vsip_scalar_f*)(a->block->R->array + cast * a->offset);
       ap_i = (vsip_scalar_f*)(a->block->I->array + cast * a->offset);
       Byp_r = (Bxpr += (cBst * B->row_stride));
       Byp_i = (Bxpi += (cBst * B->row_stride));
       rp_r += str; rp_i += str;
   }
}                                                       


static void VI_csolve_ut_f(
              const vsip_cmview_f *R,
              const vsip_cmview_f *B)
{
   vsip_length N = R->row_length;
   vsip_cmview_f XX = *B;
   vsip_cmview_f *X = &XX;
   vsip_cvview_f xx, rr;
   vsip_cvview_f *x = VI_cmrowview_f(X,(vsip_index) (N-1),&xx);
   vsip_cvview_f *r_d = VI_cmrowview_f(R,(vsip_index) 0,&rr);
   vsip_cvview_f rr_m = rr;
   vsip_cvview_f *r_m = &rr_m;
   vsip_stride d_s = R->row_stride + R->col_stride;
   r_d->length = 1; r_d->offset += ((N-1) * d_s);
   r_m->length = 0; r_m->offset = r_d->offset + R->row_stride;
   X->col_length = 1; X->offset = x->offset;
   vsip_csvmul_f(vsip_crecip_f(vsip_cvget_f(r_d,0)),x,x);
   N--;
   while(N-- >0){
      r_d->offset -= d_s;
      r_m->length++; r_m->offset -= d_s;
      x->offset -= X->col_stride;
      VI_cvsubvmprodIP_f(r_m,X,x);
      vsip_csvmul_f(vsip_crecip_f(vsip_cvget_f(r_d,0)),x,x);
      X->col_length++; X->offset = x->offset;
   }
   return;
}                                                            

static void VI_csolve_ut_special_f(
              const vsip_cmview_f *R,
              const vsip_cmview_f *B)
{
   vsip_length N = R->row_length;
   vsip_cmview_f XX = *B;
   vsip_cmview_f *X = &XX;
   vsip_cvview_f xx, rr;
   vsip_cvview_f *x = VI_cmrowview_f(X,(vsip_index) (N-1),&xx);
   vsip_cvview_f *r_d = VI_cmrowview_f(R,(vsip_index) 0,&rr);
   vsip_cvview_f rr_m = rr;
   vsip_cvview_f *r_m = &rr_m;
   vsip_stride d_s = R->row_stride + R->col_stride;
   r_d->length = 1; r_d->offset += ((N-1) * d_s);
   r_m->length = 0; r_m->offset = r_d->offset + R->row_stride;
   X->col_length = 1; X->offset = x->offset;
   N--;
   while(N-- >0){
      r_m->length++; r_m->offset -= d_s;
      x->offset -= X->col_stride;
      VI_cvjsubvmprodIP_f(r_m,X,x);
      X->col_length++; X->offset = x->offset;
   }
   return;
}                                                            



static void VI_csolve_lt_f(
              const vsip_cmview_f *R,
              const vsip_cmview_f *B)
{
   vsip_length N = R->row_length;
   vsip_cmview_f XX = *B;
   vsip_cmview_f *X = &XX;
   vsip_cvview_f xx, rr;
   vsip_cvview_f *x = VI_cmrowview_f(X,(vsip_index)0,&xx);
   vsip_cvview_f *r_d = VI_cmrowview_f(R,(vsip_index) 0,&rr);
   vsip_cvview_f rr_m = rr;
   vsip_cvview_f *r_m = &rr_m;
   vsip_stride d_s = R->row_stride + R->col_stride;
   r_d->length = 1;
   r_m->length = 0;
   X->col_length = 1;
   vsip_csvmul_f(vsip_crecip_f(vsip_conj_f(vsip_cvget_f(r_d,0))),x,x);
   N--;
   while(N-- >0){
      r_d->offset += d_s;
      r_m->length++; r_m->offset += R->col_stride;
      x->offset += X->col_stride;
      VI_cvjsubvmprodIP_f(r_m,X,x);
      vsip_csvmul_f(vsip_crecip_f(vsip_conj_f(vsip_cvget_f(r_d,0))),x,x); 
      X->col_length++;
   }
   return;
}                                                             

static void VI_csolve_lt_special_f(
              const vsip_cmview_f *R,
              const vsip_cmview_f *B)
{
   vsip_length N = R->row_length;
   vsip_cmview_f XX = *B;
   vsip_cmview_f *X = &XX;
   vsip_cvview_f xx, rr;
   vsip_cvview_f *x = VI_cmrowview_f(X,(vsip_index)0,&xx);
   vsip_cvview_f *r_d = VI_cmrowview_f(R,(vsip_index) 0,&rr);
   vsip_cvview_f rr_m = rr;
   vsip_cvview_f *r_m = &rr_m;
   r_d->length = 1;
   r_m->length = 0;
   X->col_length = 1;
   N--;
   while(N-- >0){
      r_m->length++; r_m->offset += R->col_stride;
      x->offset += X->col_stride;
      VI_cvsubvmprodIP_f(r_m,X,x);
      X->col_length++;
   }
   return;
}

static void VI_sortIP_f(
     vsip_index *p, 
     const vsip_cmview_f *B)
{
   vsip_length N = B->row_length,
               M = B->col_length,
               m,n;
   vsip_scalar_f *bp_r = B->block->R->array + B->offset * B->block->cstride,
                 *bp_i = B->block->I->array + B->offset * B->block->cstride;
   vsip_scalar_f *bp0_r = bp_r,
                 *bp0_i = bp_i,
                 *bp_exch_r,
                 *bp_exch_i; 
   vsip_stride row_st = B->row_stride * B->block->cstride,
               col_st = B->col_stride * B->block->cstride;
   vsip_cscalar_f temp;
   for(m = 0; m<(M-1); m++){
      if(*p != 0){
          bp_exch_r = bp_r + *p * col_st;
          bp_exch_i = bp_i + *p * col_st;
          for(n=0; n<N; n++){
             temp.r = *bp_r;
             temp.i = *bp_i;
             *bp_r = *bp_exch_r;
             *bp_i = *bp_exch_i;
             *bp_exch_r = temp.r;
             *bp_exch_i = temp.i;
             bp_r += row_st; bp_exch_r += row_st;
             bp_i += row_st; bp_exch_i += row_st;
          }
       }
       bp0_r += col_st; bp_r = bp0_r;
       bp0_i += col_st; bp_i = bp0_i;
       p++;
   }
   return;
}

static void VI_unsortIP_f(
     vsip_index *p, 
     const vsip_cmview_f *B)
{
   vsip_length N = B->row_length,
               M = B->col_length,
               m,n;
   vsip_stride row_st = B->row_stride * B->block->cstride,
               col_st = B->col_stride * B->block->cstride;
   vsip_scalar_f *bp_r = B->block->R->array + B->offset * B->block->cstride,
                 *bp_i = B->block->I->array + B->offset * B->block->cstride;
   vsip_scalar_f *bp0_r = bp_r + (M-2) * col_st,
                 *bp0_i = bp_i + (M-2) * col_st,
                 *bp_exch_r,
                 *bp_exch_i; 
   vsip_cscalar_f temp;
   bp_r = bp0_r;
   bp_i = bp0_i;
   p += (M-2);
   for(m = 0; m<(M-1); m++){
      if(*p != 0){
          bp_exch_r = bp_r + *p * col_st;
          bp_exch_i = bp_i + *p * col_st;
          for(n=0; n<N; n++){
             temp.r = *bp_r;
             temp.i = *bp_i;
             *bp_r = *bp_exch_r;
             *bp_i = *bp_exch_i;
             *bp_exch_r = temp.r;
             *bp_exch_i = temp.i;
             bp_r += row_st; bp_exch_r += row_st;
             bp_i += row_st; bp_exch_i += row_st;
          }
       }
       bp0_r -= col_st; bp_r = bp0_r;
       bp0_i -= col_st; bp_i = bp0_i; 
       p--;
   }
   return;
}
        
   
int vsip_clusol_f(
   const vsip_clu_f* lud,
   vsip_mat_op OpA,
   const vsip_cmview_f *XB)
{
   int retval = 0;
   vsip_index *p = lud->P;
   vsip_cmview_f AA = lud->LLU;
   vsip_cmview_f *A = &AA;
   if(OpA == VSIP_MAT_NTRANS){
       VI_sortIP_f(p, XB);
       VI_csolve_lt_special_f(A,XB);
       VI_csolve_ut_f(A,XB);
   } else if( OpA == VSIP_MAT_HERM){
      /* transpose A */
       vsip_stride temp = A->col_stride;
       A->col_stride = A->row_stride; 
       A->row_stride = temp;
      /* solve */
       VI_csolve_lt_f(A,XB);
       VI_csolve_ut_special_f(A,XB);
       VI_unsortIP_f(p, XB); 
   } else {
       retval = 1;
   }
   return retval;
}
