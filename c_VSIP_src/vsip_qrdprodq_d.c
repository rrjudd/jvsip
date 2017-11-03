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
/* $Id: vsip_qrdprodq_d.c,v 2.2 2011/08/08 03:59:38 judd Exp $ */

#include"vsip.h"
#include"vsip_qrdattributes_d.h"
#include"VI_mcolview_d.h"
#include"VI_vcopy_d_d.h"
#include"VI_vfill_d.h"
#include"VI_vput_d.h"
#include"VI_mtransview_d.h"

static void VI_smvprod_d(
               vsip_scalar_d beta,
               vsip_mview_d *A,
               vsip_vview_d *v,
               vsip_vview_d *w)
{
   vsip_mvprod_d(A,v,w);
   vsip_svmul_d(beta,w,w);
   return;
}

static void VI_svmprod_d(
               vsip_scalar_d beta,
               vsip_vview_d *v,
               vsip_mview_d *A,
               vsip_vview_d *w)
{
   vsip_vmprod_d(v,A,w);
   vsip_svmul_d(beta,w,w);
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

static void VI_mprodq_d(
     vsip_mview_d *C,
     vsip_qr_d *qr)
{
     vsip_mview_d *H = qr->A;
     vsip_scalar_d *beta = qr->beta;
     vsip_vview_d *h, hh;
     vsip_length j;
     vsip_stride k;
     vsip_vview_d vv = *(qr->v),
                  ww = *(qr->w); 
     vsip_vview_d *v = &vv,
                  *w = &ww;
     h = VI_mcolview_d(H,0,&hh);
     w->length = C->col_length;
     for(k= 0; k < (vsip_stride)H->row_length; k++){
         j = (vsip_length)k;
         h->offset = j * H->row_stride +
                     j * H->col_stride + H->offset;
         h->length = H->col_length - j;
         v->length = h->length;
         v->offset = qr->M - h->length;
         VI_vcopy_d_d(h,v);
         VI_VPUT_D(v,(vsip_index) 0, (vsip_scalar_d)1.0);
         vv = *(qr->v);
         v->length = C->col_length;
         VI_smvprod_d(-beta[j],C,v,w);
         v->length = qr->M;
         VI_opu_d(C,w,v);
         vv = *(qr->v);
         VI_VPUT_D(v,k,0);
     }   
     return;
}

static 
void 
VI_qprodm_d(
       vsip_mview_d *C,
       vsip_qr_d *qr)
{
     vsip_mview_d *H = qr->A;
     vsip_scalar_d *beta = qr->beta;
     vsip_vview_d *h, hh;
     vsip_length j;
     vsip_stride k;
     vsip_vview_d vv = *(qr->v),
                  ww = *(qr->w);
     vsip_vview_d *v = &vv, *w = &ww;
     VI_vfill_d(0,v);
     h = VI_mcolview_d(H,0,&hh);
     w->length = C->row_length;
     for(k = qr->N -1; k >= 0; k--){
          j = (vsip_length)k;
          h->offset = j * (H->row_stride + H->col_stride) + H->offset;
          h->length = H->col_length -j;
          v->length = h->length;
          v->offset = qr->M - h->length;
          VI_vcopy_d_d(h,v);
          VI_VPUT_D(v,(vsip_index)0,(vsip_scalar_d)1);
          vv = *(qr->v);
          v->length = C->col_length;
          VI_svmprod_d(-beta[j],v,C,w);
          v->length = qr->M;
          VI_opu_d(C,v,w);
     }
     return;
}

static 
void 
VI_mprodqt_d( 
     vsip_mview_d *C, 
     vsip_qr_d *qr) 
{ 
   vsip_mview_d CT = *C;
   VI_qprodm_d(VI_mtransview_d(C,&CT),qr);
   return; 
} 

static 
void 
VI_qtprodm_d(
       vsip_mview_d *C,
       vsip_qr_d *qr)
{
    vsip_mview_d CT = *C;
    VI_mprodq_d(VI_mtransview_d(C,&CT),qr);
    return;
}

int vsip_qrdprodq_d(
         const vsip_qr_d *qr,
         vsip_mat_op opMat,
         vsip_mat_side side,
         const vsip_mview_d *A)
{
  vsip_mview_d AA = *A;
  vsip_qr_d    qrqr = *qr;
  int retval = 0;
  if(qr->qopt == VSIP_QRD_NOSAVEQ){
         return 1;
  }
  if(side == VSIP_MAT_LSIDE){/* left side */
       if( opMat == VSIP_MAT_NTRANS){ /* left no trans */
            if((10 * qr->M) < A->row_length) {
               retval = 1;
            } else { 
               VI_qprodm_d(&AA,&qrqr);
            }
       } else if(opMat == VSIP_MAT_TRANS){ /* left trans */
            if((10 * qr->M) < A->row_length) {
               retval = 1;
            } else { 
               VI_qtprodm_d(&AA,&qrqr);
            }
       } else {
           retval = 1;
       }
  } else if(side == VSIP_MAT_RSIDE){ /*right side */
       if( opMat == VSIP_MAT_NTRANS){ /* right side no trans */
            if((10 * qr->M) < A->col_length) {
               retval = 1;
            } else { 
               VI_mprodq_d(&AA,&qrqr);
            }
       } else if(opMat == VSIP_MAT_TRANS){
            if((10 * qr->M) < A->col_length) { /* right side trans */
               retval = 1;
            } else { 
               VI_mprodqt_d(&AA,&qrqr);
            }
       } else {
           retval = 1;
       }
  } else{
     retval = 1;
  }
  return retval;
}
