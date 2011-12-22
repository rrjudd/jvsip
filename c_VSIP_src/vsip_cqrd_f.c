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
/* $Id: vsip_cqrd_f.c,v 2.1 2003/03/08 14:43:34 judd Exp $ */
/* Do QRD decomposition for complex qrd float */
/* vsip_cqrd_f.c */
#include<vsip.h>
#include<vsip_cqrdattributes_f.h>
#include"VI_cmcolview_f.h"
#include"VI_cmrowview_f.h"
#include"VI_cvcopy_f_f.h"

static void VI_rscjvmprod_f(
               vsip_scalar_f beta, 
               vsip_cvview_f *v,
               vsip_cmview_f *A,
               vsip_cvview_f *w)
{
   vsip_cvconj_f(v,v);
   vsip_cvmprod_f(v,A,w);
   vsip_cvconj_f(v,v);
   vsip_rscvmul_f(beta,w,w);
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

static void VI_chouse_f(
               vsip_cvview_f *x,
               vsip_cvview_f *v,
               vsip_scalar_f *beta)
{
   vsip_cscalar_f x_1  = vsip_cvget_f(x,0),
                  x_2;
   vsip_scalar_f temp = vsip_real_f(vsip_cvjdot_f(x,x));
   vsip_scalar_f  x2n  = (temp <= 0) ? 0 : (vsip_scalar_f)sqrt(temp);
   vsip_scalar_f x_1radius  = (vsip_scalar_f)sqrt(x_1.r * x_1.r + x_1.i * x_1.i);
   x_1.r /= x_1radius; x_1.i /= x_1radius;
   x_1.r *= x2n;  x_1.i *= x2n;
   VI_cvcopy_f_f(x,v);
   x_2 = x_1;
   x_1 = vsip_csub_f(vsip_cvget_f(v,0),x_1);
   x_2 = vsip_cadd_f(vsip_cvget_f(v,0),x_2);
   x_1 = ((x_1.r * x_1.r + x_1.i * x_1.i) > (x_2.r * x_2.r + x_2.i * x_2.i)) ?
                 x_1 : x_2;
   vsip_csvmul_f(vsip_crecip_f(x_1),v,v);
   vsip_cvput_f(v,0,vsip_cmplx_f(1,0));
   *beta = (vsip_scalar_f)2.0 /vsip_real_f(vsip_cvjdot_f(v,v));
   return;
}

static void VI_cmrot_f(
      const vsip_cmview_f *A, 
      const vsip_cvview_f *c)
{
    vsip_cvview_f cr = *c;
    vsip_cvview_f *r = &cr;
    vsip_cmview_f Z  = *A;
    vsip_cvview_f db,da;
    vsip_cvview_f *b = VI_cmrowview_f(&Z,0,&db);
    vsip_cvview_f *a = VI_cmrowview_f(&Z,0,&da);
    b->stride = Z.row_stride + Z.col_stride;
    {
      vsip_length n = b->length;
      vsip_stride crst = r->block->cstride;
      vsip_stride cbst = b->block->cstride;
      vsip_scalar_f *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset),
                    *bpr = (vsip_scalar_f *)((b->block->R->array) + cbst * b->offset);
      vsip_scalar_f *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset),
                    *bpi = (vsip_scalar_f *)((b->block->I->array) + cbst * b->offset);
      vsip_scalar_f s;
      /* register */ vsip_stride rst = (crst * r->stride),
                                 bst = (cbst * b->stride);
      while(n-- > 0){
          s = (vsip_scalar_f)(fabs(*bpr) + fabs(*bpi));
          *rpr = *bpr/s; *rpi = *bpi/s;
          s = s * (vsip_scalar_f)sqrt(*rpr * *rpr + *rpi * *rpi);
          *rpr = *bpr/s; *rpi = *bpi/s;
          *bpr = s; *bpi = 0.0;
          bpr += bst; bpi += bst;
          rpr += rst; rpi += rst;
      }  
      n=0;
        a->offset += a->stride;
      while(a->length > 1){
        a->length--;
        vsip_csvmul_f(vsip_conj_f(vsip_cvget_f(r,n)),a,a);
        n++;
        a->offset += b->stride;
      }
   }   
}
    
int vsip_cqrd_f(
            vsip_cqr_f *qr,
            const vsip_cmview_f *A)
{
   vsip_cmview_f AW = *A;
   vsip_cmview_f *aw = &AW;
   vsip_cvview_f vv = *(qr->v),
                 ww = *(qr->w);
   vsip_cvview_f *v = &vv, *w = &ww;
   vsip_scalar_f *beta = qr->beta;
   vsip_length j;
   vsip_length m = qr->M, 
               n = qr->N;
   vsip_cvview_f *ac, acc;
   ac = &acc;
   qr->AA = *A;
   VI_cmcolview_f(A,0,ac);
   for(j=0; j<n; j++){
     ac->offset = j * A->row_stride + j * A->col_stride + A->offset;
     ac->length = A->col_length -j;
     v->length  = ac->length;
     VI_chouse_f(ac,v,beta);
     aw->offset = ac->offset;
     aw->col_length = m - j;
     aw->row_length = n - j;
     w->length = aw->row_length;
     VI_rscjvmprod_f(- *beta,v,aw,w);
     beta++;
     VI_copu_f(aw,v,w);
     if(j < m - 1){
         v->length = ac->length - 1; 
         v->offset = j + 1;
         ac->length -= 1;
         ac->offset += ac->stride;
         VI_cvcopy_f_f(v,ac);
     }
   }
   VI_cmrot_f(A,qr->cI);
   return 0;
}
