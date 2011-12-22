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
/* $Id: vsip_cqrd_d.c,v 2.1 2003/03/08 14:43:34 judd Exp $ */
/* Do QRD decomposition for complex qrd float */
/* vsip_cqrd_d.c */
#include<vsip.h>
#include<vsip_cqrdattributes_d.h>
#include"VI_cmcolview_d.h"
#include"VI_cmrowview_d.h"
#include"VI_cvcopy_d_d.h"

static void VI_rscjvmprod_d(
               vsip_scalar_d beta, 
               vsip_cvview_d *v,
               vsip_cmview_d *A,
               vsip_cvview_d *w)
{
   vsip_cvconj_d(v,v);
   vsip_cvmprod_d(v,A,w);
   vsip_cvconj_d(v,v);
   vsip_rscvmul_d(beta,w,w);
   return;
}

static void VI_copu_d(
  const vsip_cmview_d* R,
  const vsip_cvview_d* a,
  const vsip_cvview_d* b)
{
  {
     vsip_length  n = a->length,
                  m = b->length;
     vsip_stride cRst = R->block->cstride, cast = a->block->cstride, cbst = b->block->cstride;
     vsip_scalar_d  *a_pr = (vsip_scalar_d*)(a->block->R->array + cast * a->offset),
                    *a_pi = (vsip_scalar_d*)(a->block->I->array + cast * a->offset);
     vsip_length i,j;
     vsip_stride stR = cRst * R->row_stride,
                 sta = cast * a->stride,
                 stb = cbst * b->stride;
     vsip_offset Ro  = cRst * R->offset,
                 Rco = cRst * R->col_stride,
                 bo  = cbst * b->offset;
     for(i=0; i<n; i++){
         vsip_scalar_d *R_pr = (vsip_scalar_d*)(R->block->R->array + Ro + i * Rco),
                       *R_pi = (vsip_scalar_d*)(R->block->I->array + Ro + i * Rco),
                       *b_pr = (vsip_scalar_d*)(b->block->R->array + bo),
                       *b_pi = (vsip_scalar_d*)(b->block->I->array + bo);
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

static void VI_chouse_d(
               vsip_cvview_d *x,
               vsip_cvview_d *v,
               vsip_scalar_d *beta)
{
   vsip_cscalar_d x_1  = vsip_cvget_d(x,0),
                  x_2;
   vsip_scalar_d temp = vsip_real_d(vsip_cvjdot_d(x,x));
   vsip_scalar_d  x2n  = (temp <= 0) ? 0 : sqrt(temp);
   vsip_scalar_d x_1radius  = sqrt(x_1.r * x_1.r + x_1.i * x_1.i);
   x_1.r /= x_1radius; x_1.i /= x_1radius;
   x_1.r *= x2n;  x_1.i *= x2n;
   VI_cvcopy_d_d(x,v);
   x_2 = x_1;
   x_1 = vsip_csub_d(vsip_cvget_d(v,0),x_1);
   x_2 = vsip_cadd_d(vsip_cvget_d(v,0),x_2);
   x_1 = ((x_1.r * x_1.r + x_1.i * x_1.i) > (x_2.r * x_2.r + x_2.i * x_2.i)) ?
                 x_1 : x_2;
   vsip_csvmul_d(vsip_crecip_d(x_1),v,v);
   vsip_cvput_d(v,0,vsip_cmplx_d(1,0));
   *beta = 2.0 /vsip_real_d(vsip_cvjdot_d(v,v));
   return;
}

static void VI_cmrot_d(
      const vsip_cmview_d *A, 
      const vsip_cvview_d *c)
{
    vsip_cvview_d cr = *c;
    vsip_cvview_d *r = &cr;
    vsip_cmview_d Z  = *A;
    vsip_cvview_d db,da;
    vsip_cvview_d *b = VI_cmrowview_d(&Z,0,&db);
    vsip_cvview_d *a = VI_cmrowview_d(&Z,0,&da);
    b->stride = Z.row_stride + Z.col_stride;
    {
      vsip_length n = b->length;
      vsip_stride crst = r->block->cstride;
      vsip_stride cbst = b->block->cstride;
      vsip_scalar_d *rpr = (vsip_scalar_d *)((r->block->R->array) + crst * r->offset),
                    *bpr = (vsip_scalar_d *)((b->block->R->array) + cbst * b->offset);
      vsip_scalar_d *rpi = (vsip_scalar_d *)((r->block->I->array) + crst * r->offset),
                    *bpi = (vsip_scalar_d *)((b->block->I->array) + cbst * b->offset);
      vsip_scalar_d s;
      /* register */ vsip_stride rst = (crst * r->stride),
                                 bst = (cbst * b->stride);
      while(n-- > 0){
          s = fabs(*bpr) + fabs(*bpi);
          *rpr = *bpr/s; *rpi = *bpi/s;
          s = s * sqrt(*rpr * *rpr + *rpi * *rpi);
          *rpr = *bpr/s; *rpi = *bpi/s;
          *bpr = s; *bpi = 0.0;
          bpr += bst; bpi += bst;
          rpr += rst; rpi += rst;
      }  
      n=0;
        a->offset += a->stride;
      while(a->length > 1){
        a->length--;
        vsip_csvmul_d(vsip_conj_d(vsip_cvget_d(r,n)),a,a);
        n++;
        a->offset += b->stride;
      }
   }   
}
    
int vsip_cqrd_d(
            vsip_cqr_d *qr,
            const vsip_cmview_d *A)
{
   vsip_cmview_d AW = *A;
   vsip_cmview_d *aw = &AW;
   vsip_cvview_d vv = *(qr->v),
                 ww = *(qr->w);
   vsip_cvview_d *v = &vv, *w = &ww;
   vsip_scalar_d *beta = qr->beta;
   vsip_length j;
   vsip_length m = qr->M, 
               n = qr->N;
   vsip_cvview_d *ac, acc;
   ac = &acc;
   qr->AA = *A;
   VI_cmcolview_d(A,0,ac);
   for(j=0; j<n; j++){
     ac->offset = j * A->row_stride + j * A->col_stride + A->offset;
     ac->length = A->col_length -j;
     v->length  = ac->length;
     VI_chouse_d(ac,v,beta);
     aw->offset = ac->offset;
     aw->col_length = m - j;
     aw->row_length = n - j;
     w->length = aw->row_length;
     VI_rscjvmprod_d(- *beta,v,aw,w);
     beta++;
     VI_copu_d(aw,v,w);
     if(j < m - 1){
         v->length = ac->length - 1; 
         v->offset = j + 1;
         ac->length -= 1;
         ac->offset += ac->stride;
         VI_cvcopy_d_d(v,ac);
     }
   }
   VI_cmrot_d(A,qr->cI);
   return 0;
}
