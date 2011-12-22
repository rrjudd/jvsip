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
/* $Id: vsip_cqrdprodq_d.c,v 2.2 2011/08/08 03:59:38 judd Exp $ */

#include<vsip.h>
#include<vsip_cqrdattributes_d.h>
#include"VI_cmcolview_d.h"
#include"VI_cmrowview_d.h"
#include"VI_cvcopy_d_d.h"
#include"VI_cvfill_d.h"
#include"VI_cmtransview_d.h"

static void VI_cqrdzer_d(
      const vsip_cmview_d *A,
      vsip_index i,
      vsip_index j,
      vsip_length m,
      vsip_length n)
{
   vsip_length nx = 0, mx = 0;
   vsip_scalar_d *Axp_r = A->block->R->array + (A->offset +
                         i * A->col_stride + j * A->row_stride) *
                           A->block->cstride;
   vsip_scalar_d *Axp_i = A->block->I->array + (A->offset +
                         i * A->col_stride + j * A->row_stride) *
                           A->block->cstride;
   vsip_scalar_d *Ayp_r = Axp_r, *Ayp_i = Axp_i;
   vsip_stride ACst = A->col_stride * A->block->cstride;
   vsip_stride ARst = A->row_stride * A->block->cstride;
   while(nx++ < m){
        mx = 0;
        while(mx++ < n){
           *Axp_r = (vsip_scalar_d)0.0;
           *Axp_i = (vsip_scalar_d)0.0;
           Axp_r += ARst;
           Axp_i += ARst;
        }
        Axp_r = (Ayp_r += ACst);
        Axp_i = (Ayp_i += ACst);
   }
}

static vsip_cmview_d *VI_cmconjIP_d(
               vsip_cmview_d *A)
{
   vsip_cvview_d v;
   vsip_index i;
   for(i=0; i<A->col_length; i++){
       VI_cmrowview_d(A,i,&v);
       vsip_cvconj_d(&v,&v);
   }
   return A;
}

static void VI_rscmvprod_d(
               vsip_scalar_d beta,
               vsip_cmview_d *A,
               vsip_cvview_d *v,
               vsip_cvview_d *w)
{
   vsip_cmvprod_d(A,v,w);
   vsip_rscvmul_d(beta,w,w);
   return;
}

static void VI_rscvmprod_d(
               vsip_scalar_d beta,
               vsip_cvview_d *v,
               vsip_cmview_d *A,
               vsip_cvview_d *w)
{
   vsip_cvmprod_d(v,A,w);
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
                                    
static void VI_copuh_d(
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
             *R_pr += (*a_pr * *b_pr + *a_pi * *b_pi);
             *R_pi += (*a_pi * *b_pr - *a_pr * *b_pi);
              R_pr += stR; b_pr += stb;
              R_pi += stR; b_pi += stb;
         }
         a_pr += sta;
         a_pi += sta;
     }
  }
}                                                         

static void VI_cmprodq_d(
     vsip_cmview_d *C,
     vsip_cqr_d *qr)
{
     vsip_cmview_d *H = qr->A;
     vsip_scalar_d *beta = qr->beta;
     vsip_cvview_d *h, hh;
     vsip_length j;
     vsip_stride k;
     vsip_cvview_d vv = *(qr->v),
                   ww = *(qr->w); 
     vsip_cvview_d *v = &vv,
                   *w = &ww;
     h = VI_cmcolview_d(H,0,&hh);
     w->length = C->col_length;
     for(k= 0; k < (vsip_stride)H->row_length; k++){
         j = (vsip_length)k;
         h->offset = j * H->row_stride +
                     j * H->col_stride + H->offset;
         h->length = H->col_length - j;
         v->length = h->length;
         v->offset = qr->M - h->length;
         VI_cvcopy_d_d(h,v);
         vsip_cvput_d(v,(vsip_index) 0, vsip_cmplx_d(1.0,0.0));
         vv = *(qr->v);
         v->length = C->col_length;
         VI_rscmvprod_d(-beta[j],C,v,w);
         v->length = qr->M;
         VI_copuh_d(C,w,v);
         vv = *(qr->v);
         vsip_cvput_d(v,k,vsip_cmplx_d(0.0,0.0));
     }   
     { vsip_cmview_d CC = *C;
       CC.row_length = qr->N;
       vsip_cvmmul_d(qr->cI,&CC,VSIP_ROW,&CC);
     }
     return;
}

static void VI_cqprodm_d(
       vsip_cmview_d *C,
       vsip_cqr_d *qr)
{
     vsip_cmview_d *H = qr->A;
     vsip_scalar_d *beta = qr->beta;
     vsip_cvview_d *h, hh;
     vsip_length j;
     vsip_stride k;
     vsip_cvview_d vv = *(qr->v),
                   ww = *(qr->w);
     vsip_cvview_d *v = &vv, *w = &ww;
     VI_cvfill_d(vsip_cmplx_d(0.0,0.0),v);
     h = VI_cmcolview_d(H,0,&hh);
     w->length = C->row_length;
     { vsip_cmview_d CC = *C; 
       CC.col_length = qr->N; 
       vsip_cvmmul_d(qr->cI,&CC,VSIP_COL,&CC); 
     }   
     for(k = qr->N -1; k >= 0; k--){
          j = (vsip_length)k;
          h->offset = j * (H->row_stride + H->col_stride) + H->offset;
          h->length = H->col_length -j;
          v->length = h->length;
          v->offset = qr->M - h->length;
          VI_cvcopy_d_d(h,v);
          vsip_cvput_d(v,(vsip_index)0,vsip_cmplx_d(1.0,0.0));
          vv = *(qr->v);
          v->length = C->col_length;
          vsip_cvconj_d(v,v);
          VI_rscvmprod_d(-beta[j],v,C,w);
          vsip_cvconj_d(v,v);
          v->length = qr->M;
          VI_copu_d(C,v,w);
     }
     return;
}

static void VI_cmprodqh_d( 
     vsip_cmview_d *C, 
     vsip_cqr_d *qr) 
{ 
   vsip_cmview_d CT = *C;
   VI_cqprodm_d(VI_cmconjIP_d(VI_cmtransview_d(C,&CT)),qr);
   VI_cmconjIP_d(&CT);
   return; 
} 

static void VI_cqhprodm_d(
       vsip_cmview_d *C,
       vsip_cqr_d *qr)
{
    vsip_cmview_d CT = *C;
    VI_cmprodq_d(VI_cmconjIP_d(VI_cmtransview_d(C,&CT)),qr);
    VI_cmconjIP_d(&CT);
    return;
}

int vsip_cqrdprodq_d(
         const vsip_cqr_d *qr,
         vsip_mat_op opMat,
         vsip_mat_side side,
         const vsip_cmview_d *A)
{
  vsip_cmview_d AA = *A;
  vsip_cqr_d    qrqr = *qr;
  int retval = 0;
  if(qr->qopt == VSIP_QRD_NOSAVEQ){ 
         return 1;
  }
  if(side == VSIP_MAT_LSIDE){/* left side */
       if( opMat == VSIP_MAT_NTRANS){ /* left no trans */
            if((10 * qr->M) < A->row_length) {
               retval = 1;
            } else { 
               if(qr->qopt == VSIP_QRD_SAVEQ1)
                  VI_cqrdzer_d(&AA,qrqr.N,0,qrqr.M - qrqr.N,AA.row_length);
               VI_cqprodm_d(&AA,&qrqr);
            }
       } else if(opMat == VSIP_MAT_HERM){ /* left trans */
            if((10 * qr->M) < A->row_length) {
               retval = 1;
            } else { 
               VI_cqhprodm_d(&AA,&qrqr);
            }
       } else {
           retval = 1;
       }
  } else if(side == VSIP_MAT_RSIDE){ /*right side */
       if( opMat == VSIP_MAT_NTRANS){ /* right side no trans */
            if((10 * qr->M) < A->col_length) {
               retval = 1;
            } else { 
               VI_cmprodq_d(&AA,&qrqr);
            }
       } else if(opMat == VSIP_MAT_HERM){
            if((10 * qr->M) < A->col_length) { /* right side trans */
               retval = 1;
            } else { 
              if(qr->qopt == VSIP_QRD_SAVEQ1)
                  VI_cqrdzer_d(&AA,0,qrqr.N,AA.col_length,qrqr.M - qrqr.N);
               VI_cmprodqh_d(&AA,&qrqr);
            }
       } else {
           retval = 1;
       }
  } else{
     retval = 1;
  }
  return retval;
}
