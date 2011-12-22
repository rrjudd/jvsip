/* Created RJudd August 28, 1999 */
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
/* $Id: vsip_qrd_f.c,v 2.1 2003/03/08 14:43:35 judd Exp $ */
/* Do QRD decomposition for real qrd float */
/* vsip_qrd_f.c */
#include<vsip.h>
#include<vsip_qrdattributes_f.h>
#include"VI_mcolview_f.h"
#include"VI_vcopy_f_f.h"
#include"VI_vput_f.h"
#include"VI_vget_f.h"

static void VI_svmprod_f(
               vsip_scalar_f beta, 
               vsip_vview_f *v,
               vsip_mview_f *A,
               vsip_vview_f *w)
{
   vsip_vmprod_f(v,A,w);
   vsip_svmul_f(beta,w,w);
   return;
}

static void VI_opu_f(
  const vsip_mview_f* R,
  const vsip_vview_f* a,
  const vsip_vview_f* b)
{
  {
     /* register */ vsip_length n = a->length,
                                m = b->length;
     vsip_scalar_f  *a_p = a->block->array + a->offset * a->block->rstride;
     vsip_length i,j;
     vsip_stride Rrst = R->row_stride * R->block->rstride,
                 bst  = b->stride * b->block->rstride;
     vsip_offset bo  = b->offset * b->block->rstride,
                 Ro  = R->offset * R->block->rstride,
                 Rco = R->col_stride * R->block->rstride;
     for(i=0; i<n; i++){
         vsip_scalar_f *R_p = R->block->array + Ro + i * Rco,
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

static void VI_house_f(
               vsip_vview_f *x,
               vsip_vview_f *v,
               vsip_scalar_f *beta)
{
     vsip_scalar_f sigma;
     if(x->length > (vsip_length) 1){
           x->length--;
           x->offset += x->stride;
           sigma = vsip_vdot_f(x,x);
           x->length++;
           x->offset -= x->stride;
           VI_vcopy_f_f(x,v);
     } else {
           sigma = 0;
     }
     VI_VPUT_F(v,0,1.0);
     if( sigma == (vsip_scalar_f)0.0){
           *beta = 0.0;
           if((x->length == (vsip_length) 1) && (VI_VGET_F(x,0) < (vsip_scalar_f)0)) *beta = (vsip_scalar_f)2.0;
     } else {
           vsip_scalar_f xv0 = VI_VGET_F(x,0),
                          v2;
           vsip_scalar_f mu = (vsip_scalar_f)sqrt(xv0 * xv0 + sigma);
           if(xv0 <= 0){
                VI_VPUT_F(v,0,xv0 - mu);
           } else {
                VI_VPUT_F(v,0,-sigma/(xv0 + mu));
           }
           xv0 = VI_VGET_F(v,0);
           v2 = xv0 * xv0;
           *beta = (vsip_scalar_f)2.0 * v2/(sigma + v2);
           vsip_svmul_f((vsip_scalar_f)1.0/xv0,v,v);
     }
     return;
}
      
int vsip_qrd_f(
            vsip_qr_f *qr,
            const vsip_mview_f *A)
{
   vsip_mview_f AW = *A;
   vsip_mview_f *aw = &AW;
   vsip_vview_f vv = *(qr->v), 
                ww = *(qr->w);
   vsip_vview_f *v = &vv;
   vsip_vview_f *w = &ww;
   vsip_scalar_f *beta = qr->beta;
   vsip_length j;
   vsip_length m = qr->M, 
               n = qr->N;
   vsip_vview_f *ac, acc;
   ac = &acc;
   qr->AA = *A;
   VI_mcolview_f(A,0,ac);
   for(j=0; j<n; j++){
     ac->offset = j * A->row_stride + j * A->col_stride + A->offset;
     ac->length = A->col_length -j;
     v->length  = ac->length;
     VI_house_f(ac,v,beta);
     aw->offset = ac->offset;
     aw->col_length = m - j;
     aw->row_length = n - j;
     w->length = aw->row_length;
     VI_svmprod_f(- *beta,v,aw,w);
     beta++;
     VI_opu_f(aw,v,w);
     if(j < m - 1){
         v->length = ac->length - 1; 
         v->offset = j + 1;
         ac->length -= 1;
         ac->offset += ac->stride;
         VI_vcopy_f_f(v,ac);
     }
   }
   return 0;
}
