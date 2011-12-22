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
/* $Id: vsip_llsqsol_f.c,v 2.1 2006/05/16 16:48:17 judd Exp $ */

#include<vsip.h>
#include<vsip_qrdattributes_f.h>
#include"VI_mrowview_f.h"
#include"VI_vput_f.h"
#include"VI_vget_f.h"

static void VI_vsubvmprodIP_f(
             vsip_vview_f *a,
             vsip_mview_f *B,
             vsip_vview_f *r)
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
              vsip_mview_f *R,
              vsip_mview_f *B)
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

static void VI_solve_lt_f(
              vsip_mview_f *R,
              vsip_mview_f *B)
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

static void VI_qrdsolr_f(
         vsip_mview_f *R0,
         vsip_mat_op OpR,
         vsip_mview_f *X0)
{
      vsip_mview_f XX = *X0,
                   RR = *R0;
      vsip_mview_f *X= &XX, *R = &RR;
      if(OpR == VSIP_MAT_NTRANS){
           VI_solve_ut_f(R,X);
      } else {
           vsip_stride t_s = R->row_stride;
           R->row_stride = R->col_stride;
           R->col_stride = t_s;
           VI_solve_lt_f(R,X);
      }
      return;
}

/*------------------------------------------------*
 | Algorithm 5.2.2 From GVL                       |
 *------------------------------------------------*/

/* --------------------------------------------------------- *
 | VU_givens_f.h                                             |
 | Algorithm 5.1.3 From GVL                                  |
 | calculate cosine "c" and sine "s" of a givens rotation    |
 *-----------------------------------------------------------*/

static 
void 
VI_givens_f(
  vsip_scalar_f a,
  vsip_scalar_f b,
  vsip_scalar_f *c,
  vsip_scalar_f *s,
  vsip_scalar_f *r){
    vsip_scalar_f t;
    if(b == 0){
        *c = 1; *s = 0;    
    } else {
        if(fabs(b) > fabs(a)){         
          t = -a/b; 
          *s = (vsip_scalar_f)(1.0/sqrt(1 + t * t)); 
          *c = *s * t;
        } else {
          t = -b/a;
          *c = (vsip_scalar_f)(1.0/sqrt(1 + t * t));
          *s = *c * t;
        }
    }
    *r = *c * a - *s * b;
    return;
}

static 
int 
VI_givens_llsq_f( vsip_mview_f *A, vsip_mview_f *B)
{
    int retval = 0;
    vsip_length m = A->col_length;
    vsip_length n = A->row_length;
    vsip_length bn = B->row_length;
    vsip_length i,j,k;
    vsip_scalar_f c=0,s=0,r=0;
    vsip_stride Ar_st = A->row_stride * A->block->rstride;
    vsip_stride Br_st = B->row_stride * B->block->rstride;
  
    for(j=0; j<n; j++){
       for(i=m-1; i>j; i--){
         vsip_scalar_f *a0p = A->block->array + (A->offset + (i-1) * A->col_stride + j * A->row_stride) * A->block->rstride;
         vsip_scalar_f *a1p = A->block->array + (A->offset + i * A->col_stride + j * A->row_stride) * A->block->rstride;
         vsip_scalar_f *b0p = B->block->array + (B->offset + (i-1) * B->col_stride ) * B->block->rstride;
         vsip_scalar_f *b1p = B->block->array + (B->offset +   i * B->col_stride ) * B->block->rstride;
         VI_givens_f(*a0p,*a1p,&c,&s,&r);
         if(r == 0) retval++;
         *a0p = r; *a1p = 0;
         a1p += Ar_st; a0p +=Ar_st;
         for(k=1; k<n-j; k++){
            vsip_scalar_f a0 = *a0p, a1 = *a1p;
            *a0p = a0 * c - a1 * s;
            *a1p = a0 * s + a1 * c;
            a1p += Ar_st; a0p += Ar_st;
         }
         for(k=0; k<bn; k++){
            vsip_scalar_f b0 = *b0p, b1 = *b1p;
            *b0p = b0 * c - b1 * s;
            *b1p = b0 * s + b1 * c;
            b1p += Br_st; b0p += Br_st;
         }
       }
    }
    return retval;
}


int vsip_llsqsol_f(
         const vsip_mview_f *A,
         const vsip_mview_f *XB)
{
   int retval = 0;
   vsip_mview_f RR = *A;
   vsip_mview_f *R = &RR;
   vsip_mview_f XX = *XB;
   vsip_mview_f *X = &XX;
   retval += VI_givens_llsq_f(R,X);
   R->row_length = A->row_length;
   R->col_length = A->col_length;
   X->col_length = R->col_length;
   VI_qrdsolr_f(R,VSIP_MAT_NTRANS,X);
   return retval;
}
