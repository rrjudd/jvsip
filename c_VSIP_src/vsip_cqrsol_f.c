/* Created RJudd August 29, 1999 */
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
/* $Id: vsip_cqrsol_f.c,v 2.1 2003/03/08 14:43:34 judd Exp $ */

#include<vsip.h>
#include<vsip_cqrdattributes_f.h>
#include"VI_cmcolview_f.h"
#include"VI_cmrowview_f.h"
#include"VI_cvcopy_f_f.h"

static void VI_rscvjmprod_f( /* r = beta * conj(a) * B */
        vsip_scalar_f beta,
  const vsip_cvview_f* a,
  const vsip_cmview_f* B,
  const vsip_cvview_f* r) {
  { 
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
           *rp_r = 0; *rp_i = 0;
           mx = 0;
           while(mx++ < B->col_length){
               *rp_r += *ap_r * *Byp_r + *ap_i * *Byp_i;
               *rp_i += *ap_r * *Byp_i - *ap_i * *Byp_r;
               ap_r += sta; Byp_r += stB;
               ap_i += sta; Byp_i += stB;
           }
           *rp_r *= beta;
           *rp_i *= beta;
           ap_r = (vsip_scalar_f*)(a->block->R->array + cast * a->offset);
           ap_i = (vsip_scalar_f*)(a->block->I->array + cast * a->offset);
           Byp_r = (Bxpr += (cBst * B->row_stride));
           Byp_i = (Bxpi += (cBst * B->row_stride));
           rp_r += str; rp_i += str;
     }   
  }
}


static void VI_cvjmmul_col_f(
  const vsip_cvview_f *a,
  const vsip_cmview_f *B,
  const vsip_cmview_f *R) {
   vsip_cvview_f bb,*b,rr,*r;
   vsip_stride sb,sr;
   vsip_length L;
   sb = B->row_stride;
   sr = R->row_stride;
   L  = B->row_length;;
   b = VI_cmcolview_f(B,0,&bb);
   r = VI_cmcolview_f(R,0,&rr);
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
              temp = *apr * *bpr + *bpi * *api;
              *rpi = *apr * *bpi - *api * *bpr;
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



static void VI_cvjsubvmprodIP_f(
             vsip_cvview_f *a,
             vsip_cmview_f *B,
             vsip_cvview_f *r)
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
             vsip_cvview_f *a, 
             vsip_cmview_f *B,
             vsip_cvview_f *r)
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
              vsip_cmview_f *R,
              vsip_cmview_f *B)
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

static void VI_csolve_lt_f(
              vsip_cmview_f *R,
              vsip_cmview_f *B)
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
  /* vsip_csvmul_f(vsip_crecip_f(vsip_conj_f(vsip_cvget_f(r_d,0))),x,x); */
   vsip_rscvmul_f((vsip_scalar_f)1.0/(vsip_real_f(vsip_cvget_f(r_d,0))),x,x);
   N--;  
   while(N-- >0){
      r_d->offset += d_s;
      r_m->length++; r_m->offset += R->col_stride; 
      x->offset += X->col_stride; 
      VI_cvjsubvmprodIP_f(r_m,X,x);
     /*  vsip_csvmul_f(vsip_crecip_f(vsip_conj_f(vsip_cvget_f(r_d,0))),x,x); */
      vsip_rscvmul_f((vsip_scalar_f)1.0/(vsip_real_f(vsip_cvget_f(r_d,0))),x,x);
      X->col_length++; 
   }
   return;
}

static void VI_cqrdsolr_f(
         vsip_cmview_f *R0,
         vsip_mat_op OpR,
         vsip_cmview_f *X0)
{
      vsip_cmview_f XX = *X0,
                    RR = *R0;
      vsip_cmview_f *X= &XX, *R = &RR;    
      if(OpR == VSIP_MAT_NTRANS){
           VI_csolve_ut_f(R,X);
      } else {
           vsip_stride t_s = R->row_stride;
           R->row_stride = R->col_stride;
           R->col_stride = t_s;
           VI_csolve_lt_f(R,X);
      } 
      return;
}

static void VI_copu_f(
  const vsip_cmview_f* R,
  const vsip_cvview_f* a,
  const vsip_cvview_f* b)
{
  {
     vsip_length  n = a->length,
                  m = b->length;
     vsip_stride cRst = R->block->cstride, cast = a->block->cstride, cbst = b->block->cstride;
     vsip_scalar_f  *a_pr = (vsip_scalar_f*)(a->block->R->array + cast * a->offset),
                    *a_pi = (vsip_scalar_f*)(a->block->I->array + cast * a->offset);
     vsip_length i,j;
     vsip_stride stR = cRst * R->row_stride,
                 sta = cast * a->stride,
                 stb = cbst * b->stride;
     vsip_offset Ro  = cRst * R->offset,
                 Rco = cRst * R->col_stride,
                 bo  = cbst * b->offset;
     for(i=0; i<n; i++){
         vsip_scalar_f *R_pr = (vsip_scalar_f*)(R->block->R->array + Ro + i * Rco),
                       *R_pi = (vsip_scalar_f*)(R->block->I->array + Ro + i * Rco),
                       *b_pr = (vsip_scalar_f*)(b->block->R->array + bo),
                       *b_pi = (vsip_scalar_f*)(b->block->I->array + bo);
         for(j=0; j<m; j++){
             *R_pr += (*a_pr * *b_pr - *a_pi * *b_pi);
             *R_pi += (*a_pi * *b_pr + *a_pr * *b_pi);
              R_pr += stR; b_pr += stb;
              R_pi += stR; b_pi += stb;
         }
         a_pr += sta;
         a_pi += sta;
     }
  }
}
                                    
int vsip_cqrsol_f(
         const vsip_cqr_f *qr,
         vsip_qrd_prob prob,
         const vsip_cmview_f *XB)
{
   int retval = 0;
   vsip_cmview_f RR = *(qr->A);
   vsip_cmview_f *R = &RR;
   vsip_cmview_f AA = RR;
   vsip_cmview_f *A = &AA;
   vsip_cmview_f XX = *XB;
   vsip_cmview_f *X = &XX;
   R->row_length = qr->N;
   R->col_length = qr->N;
   if(prob == VSIP_COV){
       VI_cqrdsolr_f(R,VSIP_MAT_HERM,X);
       VI_cqrdsolr_f(R,VSIP_MAT_NTRANS,X);
   } else if (prob == VSIP_LLS){
       vsip_cvview_f vv = *(qr->v),
                    ww = *(qr->w),
                    aa_c;
       vsip_cvview_f *a_c = &aa_c,
                    *v = &vv,
                    *w = &ww;
       vsip_scalar_f *beta = qr->beta;
       vsip_index j;
       w->length = X->row_length;
       for(j=0; j<qr->N; j++){
          v->length = A->col_length;
          VI_cmcolview_f(A,j,a_c);
          VI_cvcopy_f_f(a_c,v);
          vsip_cvput_f(v,(vsip_index)0,vsip_cmplx_f(1.0,0.0));
          VI_rscvjmprod_f(- *beta,v,X,w); 
          VI_copu_f(X,v,w);
          beta++;
          X->offset += X->col_stride;
          X->col_length--;
          A->offset += A->col_stride;
          A->col_length--;
       }
       XX = *XB;
       X->col_length = qr->N;
       VI_cvjmmul_col_f(qr->cI,X,X);
       VI_cqrdsolr_f(R,VSIP_MAT_NTRANS,X);
   } else {
       retval = 1;
   }
   return retval;               
}
