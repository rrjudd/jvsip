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
/* $Id: vsip_qrsol_d.c,v 2.1 2003/03/08 14:43:35 judd Exp $ */

#include<vsip.h>
#include<vsip_qrdattributes_d.h>
#include"VI_mrowview_d.h"
#include"VI_mcolview_d.h"
#include"VI_vcopy_d_d.h"
#include"VI_vput_d.h"
#include"VI_vget_d.h"

static void VI_svmprod_d( /* r = beta * a * B */
  vsip_scalar_d       beta,
  const vsip_vview_d* a,
  const vsip_mview_d* B,
  const vsip_vview_d* r) {
  {
     vsip_length nx = 0, mx = 0;
     vsip_scalar_d  *ap = a->block->array + a->offset * a->block->rstride,
                    *ap0 = ap,
                    *rp = r->block->array + r->offset * a->block->rstride,
                   *Byp = B->block->array + B->offset * a->block->rstride,
                   *Bxp = Byp;
     vsip_stride BCst = B->col_stride * B->block->rstride,
                 BRst = B->row_stride * B->block->rstride,
                 rst  = r->stride * r->block->rstride;
     while(nx++ < B->row_length){
         *rp = 0;
         mx = 0;
         while(mx++ < B->col_length){
             *rp += *ap * *Byp;
             ap += a->stride; Byp += BCst;
         }
         *rp *= beta;
         ap = ap0;
         Byp = (Bxp += BRst);
         rp += rst;
     }
  }
}



static void VI_vsubvmprodIP_d(
             vsip_vview_d *a,
             vsip_mview_d *B,
             vsip_vview_d *r)
{
   vsip_scalar_d temp;
   vsip_length nx = 0, mx = 0;
   vsip_scalar_d  *ap = a->block->array + a->offset * a->block->rstride,
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

static void VI_solve_ut_d(
              vsip_mview_d *R,
              vsip_mview_d *B)
{
   vsip_length N = R->row_length;
   vsip_mview_d XX = *B;
   vsip_mview_d *X = &XX;
   vsip_vview_d xx, rr;
   vsip_vview_d *x = VI_mrowview_d(X,(vsip_index) (N-1),&xx);
   vsip_vview_d *r_d = VI_mrowview_d(R,(vsip_index) 0,&rr);
   vsip_vview_d rr_m = rr;
   vsip_vview_d *r_m = &rr_m; 
   vsip_stride d_s = R->row_stride + R->col_stride;
   r_d->length = 1; r_d->offset += ((N-1) * d_s);
   r_m->length = 0; r_m->offset = r_d->offset + R->row_stride;
   X->col_length = 1; X->offset = x->offset;
   vsip_svmul_d((vsip_scalar_d) 1.0/(VI_VGET_D(r_d,0)),x,x);
   N--;
   while(N-- >0){
      r_d->offset -= d_s;
      r_m->length++; r_m->offset -= d_s;
      x->offset -= X->col_stride;
      VI_vsubvmprodIP_d(r_m,X,x);
      vsip_svmul_d((vsip_scalar_d) 1.0/(VI_VGET_D(r_d,0)),x,x);
      X->col_length++; X->offset = x->offset;
   }
   return;
}

static void VI_solve_lt_d(
              vsip_mview_d *R,
              vsip_mview_d *B)
{
   vsip_length N = R->row_length;
   vsip_mview_d XX = *B;
   vsip_mview_d *X = &XX;
   vsip_vview_d xx, rr;
   vsip_vview_d *x = VI_mrowview_d(X,(vsip_index)0,&xx);
   vsip_vview_d *r_d = VI_mrowview_d(R,(vsip_index) 0,&rr);
   vsip_vview_d rr_m = rr;
   vsip_vview_d *r_m = &rr_m; 
   vsip_stride d_s = R->row_stride + R->col_stride;
   r_d->length = 1; 
   r_m->length = 0;
   X->col_length = 1;
   vsip_svmul_d((vsip_scalar_d) 1.0/(VI_VGET_D(r_d,0)),x,x);
   N--;  
   while(N-- >0){
      r_d->offset += d_s;
      r_m->length++; r_m->offset += R->col_stride; 
      x->offset += X->col_stride; 
      VI_vsubvmprodIP_d(r_m,X,x);
      vsip_svmul_d((vsip_scalar_d) 1.0/(VI_VGET_D(r_d,0)),x,x);
      X->col_length++; 
   }
   return;
}

static void VI_qrdsolr_d(
         vsip_mview_d *R0,
         vsip_mat_op OpR,
         vsip_mview_d *X0)
{
      vsip_mview_d XX = *X0,
                   RR = *R0;
      vsip_mview_d *X= &XX, *R = &RR;
      if(OpR == VSIP_MAT_NTRANS){
           VI_solve_ut_d(R,X);
      } else {
           vsip_stride t_s = R->row_stride;
           R->row_stride = R->col_stride;
           R->col_stride = t_s;
           VI_solve_lt_d(R,X);
      }
      return;
}


static void VI_opu_d(
  const vsip_mview_d* R,
  const vsip_vview_d* a,
  const vsip_vview_d* b)
{
  {
     /* register */ vsip_length n = a->length,
                                m = b->length;
     vsip_scalar_d  *a_p = a->block->array + a->offset * a->block->rstride;
     vsip_length i,j;
     vsip_stride Rrst = R->row_stride * R->block->rstride,
                 bst  = b->stride * b->block->rstride;
     vsip_offset bo  = b->offset * b->block->rstride,
                 Ro  = R->offset * R->block->rstride,
                 Rco = R->col_stride * R->block->rstride;
     for(i=0; i<n; i++){
         vsip_scalar_d *R_p = R->block->array + Ro + i * Rco,
                       *b_p = b->block->array + bo;
         for(j=0; j<m; j++){
             *R_p += *a_p * *b_p;
              R_p += Rrst; b_p += bst;
         }
         a_p += a->stride;
     }
  }
  return;
}                                          

int vsip_qrsol_d(
         const vsip_qr_d *qr,
         vsip_qrd_prob prob,
         const vsip_mview_d *XB)
{
   int retval = 0;
   vsip_mview_d RR = *(qr->A);
   vsip_mview_d *R = &RR;
   vsip_mview_d AA = RR;
   vsip_mview_d *A = &AA;
   vsip_mview_d XX = *XB;
   vsip_mview_d *X = &XX;
   R->row_length = qr->N;
   R->col_length = qr->N;
   if(prob == VSIP_COV){
       VI_qrdsolr_d(R,VSIP_MAT_TRANS,X);
       VI_qrdsolr_d(R,VSIP_MAT_NTRANS,X);
   } else if (prob == VSIP_LLS){
       vsip_vview_d vv = *(qr->v),
                    ww = *(qr->w),
                    aa_c;
       vsip_vview_d *a_c = &aa_c,
                    *v = &vv,
                    *w = &ww;
       vsip_scalar_d *beta = qr->beta;
       vsip_index j;
       w->length = X->row_length;
       for(j=0; j<qr->N; j++){
          v->length = A->col_length;
          VI_mcolview_d(A,j,a_c);
          VI_vcopy_d_d(a_c,v);
          VI_VPUT_D(v,(vsip_index)0,(vsip_scalar_d)1.0);
          VI_svmprod_d(- *beta,v,X,w);
          VI_opu_d(X,v,w);
          beta++;
          X->offset += X->col_stride;
          X->col_length--;
          A->offset += A->col_stride;
          A->col_length--;
       } 
       XX = *XB;
       X->col_length = qr->N;
       VI_qrdsolr_d(R,VSIP_MAT_NTRANS,X);
   } else {
       retval = 1;
   }
   return retval;
}
