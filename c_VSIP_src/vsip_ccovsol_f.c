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
/* $Id: vsip_ccovsol_f.c,v 2.1 2006/05/06 17:54:00 judd Exp $ */

#include<vsip.h>
#include<vsip_cqrdattributes_f.h>
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
   vsip_length sta = cast * a->stride, str = crst * r->stride, stB = cBst * B->col_stride;
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

static 
void 
VI_cgivens_f(
             vsip_cscalar_f a,
             vsip_cscalar_f b,
             vsip_cscalar_f *c,
             vsip_cscalar_f *s,
             vsip_cscalar_f  *r)
{
   vsip_scalar_f am = vsip_cmag_f(a);
   vsip_scalar_f bm = vsip_cmag_f(b);
   c->i = 0.0;
   if(am == 0.0){
      *r = b;
      c->r = 0.0; 
      s->r = 1; s->i = 0.0;   
   } else {
      vsip_scalar_f scale = am + bm;
      vsip_cscalar_f alpha = vsip_cmplx_f(a.r/am, a.i/am);
      vsip_scalar_f scalesq = scale * scale;
      vsip_scalar_f norm = scale * (vsip_scalar_f)sqrt((am*am)/scalesq + (bm * bm)/scalesq);
      c->r =am/norm;
      
      s->r =  (alpha.r * b.r + alpha.i * b.i)/norm; 
      s->i = (-alpha.r * b.i + alpha.i * b.r)/norm;
      r->r = alpha.r * norm;  r->i = alpha.i * norm;
   }
   return;
}

static 
void 
VI_cgivens_r_f( vsip_cmview_f *A)
{
   vsip_length m = A->col_length;
   vsip_length n = A->row_length;
   vsip_length i,j,k;
   vsip_cscalar_f c,s10,s01,r;
   vsip_stride r_st = A->row_stride * A->block->cstride;
   
   for(j=0; j<n; j++){
      for(i=m-1; i>j; i--){
         vsip_scalar_f *a0p_r = A->block->R->array + (A->offset + (i-1) * A->col_stride + j * A->row_stride) * A->block->cstride;
         vsip_scalar_f *a0p_i = A->block->I->array + (A->offset + (i-1) * A->col_stride + j * A->row_stride) * A->block->cstride;
         vsip_scalar_f *a1p_r = A->block->R->array + (A->offset + i * A->col_stride + j * A->row_stride) * A->block->cstride;
         vsip_scalar_f *a1p_i = A->block->I->array + (A->offset + i * A->col_stride + j * A->row_stride) * A->block->cstride;
         vsip_cscalar_f a,b;
         a.r = *a0p_r; a.i = *a0p_i;
         b.r = *a1p_r; b.i = *a1p_i;
         VI_cgivens_f(a,b,&c,&s01,&r);
         /* rotate r so the iamginary part is 0 and store  in a0p*/
         *a0p_r = vsip_cmag_f(r); *a0p_i = 0;
         *a1p_r = 0.0; *a1p_i = 0.0;
         /* store a rotation value in r */
         if (*a0p_r != 0){
            r.r =  r.r / *a0p_r;
            r.i = -r.i / *a0p_r;
         }
         a0p_r += r_st; a0p_i += r_st;
         a1p_r += r_st; a1p_i += r_st;
         s10.r = - s01.r; s10.i = s01.i;
         for(k=1; k<n-j; k++){
            vsip_scalar_f a0_r = *a0p_r, a1_r = *a1p_r;
            vsip_scalar_f a0_i = *a0p_i, a1_i = *a1p_i;
            vsip_cscalar_f a0;
            a0.r = a0_r * c.r + a1_r * s01.r - a1_i * s01.i;
            a0.i = a0_i * c.r + s01.r * a1_i + a1_r * s01.i;
            /* correct a0 for rotation and place in matrix*/
            *a0p_r = r.r * a0.r - r.i * a0.i; 
            *a0p_i = r.r * a0.i + r.i * a0.r;
            *a1p_r = a1_r * c.r + s10.r * a0_r - s10.i * a0_i;
            *a1p_i = a1_i * c.r + s10.r * a0_i + s10.i * a0_r; 
            a0p_r += r_st; a0p_i += r_st;
            a1p_r += r_st; a1p_i += r_st;
         }
      }
   }
   return;
}


int vsip_ccovsol_f(
         const vsip_cmview_f *A,
         const vsip_cmview_f *XB)
{
   int retval = 0;
   vsip_cmview_f RR = *A;
   vsip_cmview_f *R = &RR;
   vsip_cmview_f XX = *XB;
   vsip_cmview_f *X = &XX;
   VI_cgivens_r_f(R);
   VI_cqrdsolr_f(R,VSIP_MAT_HERM,X);
   VI_cqrdsolr_f(R,VSIP_MAT_NTRANS,X);
   return retval;               
}
