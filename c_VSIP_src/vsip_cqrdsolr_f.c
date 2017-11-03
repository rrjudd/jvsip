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
/* $Id: vsip_cqrdsolr_f.c,v 2.1 2003/03/08 14:43:34 judd Exp $ */

#include"vsip.h"
#include"vsip_cqrdattributes_f.h"
#include"VI_cmrowview_f.h"

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
              vsip_cscalar_f alpha,
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
   if((alpha.r == 0) && (alpha.i == 0)) return;
   vsip_csvmul_f(alpha,x,x);
   vsip_csvmul_f(vsip_crecip_f(vsip_cvget_f(r_d,0)),x,x);
   N--;
   while(N-- >0){
      r_d->offset -= d_s;
      r_m->length++; r_m->offset -= d_s;
      x->offset -= X->col_stride;
      vsip_csvmul_f(alpha,x,x);
      VI_cvsubvmprodIP_f(r_m,X,x);
      vsip_csvmul_f(vsip_crecip_f(vsip_cvget_f(r_d,0)),x,x);
      X->col_length++; X->offset = x->offset;
   }
   return;
}

static void VI_csolve_lt_f(
              vsip_cmview_f *R,
              vsip_cscalar_f alpha,
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
   if((alpha.r == 0) && (alpha.i == 0)) return;
   vsip_csvmul_f(alpha,x,x);
  /* vsip_csvmul_f(vsip_crecip_f(vsip_conj_f(vsip_cvget_f(r_d,0))),x,x); */
   vsip_rscvmul_f((vsip_scalar_f)1.0/(vsip_real_f(vsip_cvget_f(r_d,0))),x,x);
   N--;  
   while(N-- >0){
      r_d->offset += d_s;
      r_m->length++; r_m->offset += R->col_stride; 
      x->offset += X->col_stride; 
      vsip_csvmul_f(alpha,x,x);
      VI_cvjsubvmprodIP_f(r_m,X,x);
     /*  vsip_csvmul_f(vsip_crecip_f(vsip_conj_f(vsip_cvget_f(r_d,0))),x,x); */
      vsip_rscvmul_f((vsip_scalar_f)1.0/(vsip_real_f(vsip_cvget_f(r_d,0))),x,x);
      X->col_length++; 
   }
   return;
}

int vsip_cqrdsolr_f(
         const vsip_cqr_f *qr,
         vsip_mat_op OpR,
         vsip_cscalar_f alpha,
         const vsip_cmview_f *XB)
{
      int retval = 0;
      vsip_cmview_f RR = *(qr->A);
      vsip_cmview_f *R = &RR;
      vsip_cmview_f XX = *XB;
      vsip_cmview_f *X = &XX;
      R->row_length = qr->N;
      R->col_length = qr->N;
      if(OpR == VSIP_MAT_NTRANS){
           VI_csolve_ut_f(R,alpha,X);
      } else if(OpR == VSIP_MAT_HERM){
           R->row_stride = qr->A->col_stride;
           R->col_stride = qr->A->row_stride;
           VI_csolve_lt_f(R,alpha,X);
      } else{
           retval = 1;
      }
      return retval;
}
