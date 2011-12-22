/* Created RJudd August 29, 1999*/
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
/* $Id: vsip_qrdprodq_f.c,v 2.3 2011/08/08 03:59:38 judd Exp $ */

#include<vsip.h>
#include<vsip_qrdattributes_f.h>
#include"VI_mcolview_f.h"
#include"VI_vcopy_f_f.h"
#include"VI_vput_f.h"
#include"VI_mtransview_f.h"

static void VI_qrdzer_f(
      const vsip_mview_f *A,
      vsip_index i,
      vsip_index j,
      vsip_length m,
      vsip_length n)
{
   vsip_length nx = 0, mx = 0;
   vsip_scalar_f *Axp = A->block->array + (A->offset + 
                         i * A->col_stride + j * A->row_stride) * 
                           A->block->rstride;
   vsip_scalar_f *Ayp = Axp;
   vsip_stride ACst = A->col_stride * A->block->rstride;    
   vsip_stride ARst = A->row_stride * A->block->rstride;    
   while(nx++ < m){
        mx = 0;
        while(mx++ < n){
           *Axp = (vsip_scalar_f)0.0;
           Axp += ARst;
        }
        Axp = (Ayp += ACst);
   }
}

static void VI_smvprod_f(
     vsip_scalar_f beta,
  const vsip_mview_f* A,
  const vsip_vview_f* b,
  const vsip_vview_f* r)
  {
     vsip_length nx = 0, mx = 0;
     vsip_scalar_f *bp = b->block->array + b->offset * b->block->rstride,
                   *rp = r->block->array + r->offset * r->block->rstride,
                   *Ayp = A->block->array + A->offset * A->block->rstride,
                   *Axp = Ayp;
     vsip_stride rst = r->stride * r->block->rstride,
                 ARst = A->row_stride * A->block->rstride,
                 ACst = A->col_stride * A->block->rstride,
                 bst = b->stride * b->block->rstride;
     while(nx++ < A->col_length){
         *rp = 0;
         mx = 0;
         while(mx++ < A->row_length){
             *rp += *bp * *Axp;
             bp += bst; Axp += ARst;
         }
         *rp *= beta;
         bp = b->block->array + b->offset * b->block->rstride;
         Axp = (Ayp += ACst);
         rp += rst;
     }
  }

static void VI_svmprod_f(
  vsip_scalar_f beta,
  const vsip_vview_f* a,
  const vsip_mview_f* B,
  const vsip_vview_f* r) {
  {
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

static void VI_mprodq_f(
     vsip_mview_f *C0,
     vsip_qr_f *qr)
{
     vsip_mview_f CC = *C0;
     vsip_mview_f *C = &CC;
     vsip_mview_f HH = *(qr->A);
     vsip_mview_f *H = &HH;
     vsip_scalar_f *beta = qr->beta;
     vsip_vview_f *h, hh;
     vsip_stride k,
                 h_s = H->row_stride + H->col_stride;
     vsip_vview_f vv = *(qr->v), ww = *(qr->w);
     vsip_vview_f *v = &vv, *w = &ww;
     h = VI_mcolview_f(H,0,&hh);
     v->length = h->length;
     w->length = C->col_length;
     for(k= 0; k < (vsip_stride)H->row_length; k++){
         VI_vcopy_f_f(h,v);
         VI_VPUT_F(v,(vsip_index) 0, (vsip_scalar_f)1.0);
         v->length = C->row_length;
         VI_smvprod_f(- *beta,C,v,w);
         VI_opu_f(C,w,v);
         h->offset += h_s; h->length --;
         C->offset += C->row_stride; C->row_length--;
         v->length = h->length; beta++;
     }
     return;
}


static void VI_qprodm_f(
       vsip_mview_f *C0,
       vsip_qr_f *qr)
{
     vsip_mview_f CC = *C0;
     vsip_mview_f *C = &CC;
     vsip_mview_f HH = *(qr->A);
     vsip_mview_f *H = &HH;
     vsip_scalar_f *beta = qr->beta + qr->N - 1;
     vsip_vview_f *h, hh;
     vsip_stride k,
                 h_s = H->row_stride + H->col_stride;
     vsip_vview_f vv = *(qr->v), ww = *(qr->w);
     vsip_vview_f *v = &vv, *w = &ww;
     h = VI_mcolview_f(H,0,&hh);
     h->offset += (qr->N - 1) * h_s;
     h->length -= (qr->N - 1);
     w->length = C->row_length;
     C->col_length -= (qr->N - 1);
     C->offset += (qr->N -1) * C->col_stride;
     for(k = qr->N -1; k >= 0; k--){
          v->length = h->length;
          VI_vcopy_f_f(h,v);
          VI_VPUT_F(v,(vsip_index)0,(vsip_scalar_f)1);
          v->length = C->col_length;
          VI_svmprod_f(- *beta,v,C,w);
          v->length = h->length;
          VI_opu_f(C,v,w);
          C->offset -= C->col_stride; C->col_length++;
          h->length++; h->offset -= h_s;
          beta--;
     }
     return;
}
static void VI_mprodqt_f( 
     vsip_mview_f *C, 
     vsip_qr_f *qr) 
{ 
   vsip_mview_f CT = *C;
   VI_qprodm_f(VI_mtransview_f(C,&CT),qr);
   return; 
} 

static void VI_qtprodm_f(
       vsip_mview_f *C,
       vsip_qr_f *qr)
{
    vsip_mview_f CT = *C;
    VI_mprodq_f(VI_mtransview_f(C,&CT),qr);
    return;
}

int vsip_qrdprodq_f(
         const vsip_qr_f *qr,
         vsip_mat_op opMat,
         vsip_mat_side side,
         const vsip_mview_f *A)
{
  vsip_mview_f AA = *A;
  vsip_qr_f    qrqr = *qr;
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
                  VI_qrdzer_f(&AA,qrqr.N,0,qrqr.M - qrqr.N,AA.row_length);
               VI_qprodm_f(&AA,&qrqr);
            }
       } else if(opMat == VSIP_MAT_TRANS){ /* left trans */
            if((10 * qr->M) < A->row_length) {
               retval = 1;
            } else { 
               VI_qtprodm_f(&AA,&qrqr);
            }
       } else {
           retval = 1;
       }
  } else if(side == VSIP_MAT_RSIDE){ /*right side */
       if( opMat == VSIP_MAT_NTRANS){ /* right side no trans */
            if((10 * qr->M) < A->col_length) {
               retval = 1;
            } else { 
               VI_mprodq_f(&AA,&qrqr);
            }
       } else if(opMat == VSIP_MAT_TRANS){
            if((10 * qr->M) < A->col_length) { /* right side trans */
               retval = 1;
            } else { 
               if(qr->qopt == VSIP_QRD_SAVEQ1) 
                  VI_qrdzer_f(&AA,0,qrqr.N,AA.col_length,qrqr.M - qrqr.N);
               VI_mprodqt_f(&AA,&qrqr);
            }
       } else {
           retval = 1;
       }
  } else{
     retval = 1;
  }
  return retval;
}
