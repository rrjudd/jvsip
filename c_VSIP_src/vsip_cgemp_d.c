/* Created RJudd January 27, 1999 */
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
/* $Id: vsip_cgemp_d.c,v 2.2 2008/03/03 17:48:38 judd Exp $ */

#include"vsip_cmviewattributes_d.h"
#include"vsip_cvviewattributes_d.h"
#include"vsip.h"

#define CMCOLVIEW(_v,_j,_a) {\
   (_a)->block    = (_v)->block;\
   (_a)->offset   = (_v)->offset + _j * (_v)->row_stride;\
   (_a)->stride   = (_v)->col_stride;\
   (_a)->length   = (_v)->col_length;\
   (_a)->markings = (_v)->markings;\
}

#define CMROWVIEW(_v,_i,_a) {\
   (_a)->block    = (_v)->block;\
   (_a)->offset   = (_v)->offset + _i * (_v)->col_stride;\
   (_a)->stride   = (_v)->row_stride;\
   (_a)->length   = (_v)->row_length;\
   (_a)->markings = (_v)->markings;\
}   

static
vsip_cscalar_d 
VI_cvjjdot_d(const vsip_cvview_d *a,const vsip_cvview_d *b)
{
    /* register */ vsip_length n = a->length;
    vsip_stride cast = a->block->cstride;
    vsip_stride cbst = b->block->cstride;
    vsip_scalar_d *apr = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset),
                  *bpr = (vsip_scalar_d*) ((b->block->R->array) + cbst * b->offset);
    vsip_scalar_d *api = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset),
                  *bpi = (vsip_scalar_d*) ((b->block->I->array) + cbst * b->offset);
    /* register */ vsip_stride ast = (cast * a->stride),
                               bst = (cbst * b->stride);
  vsip_cscalar_d r;
  r.r = 0; r.i = 0;
  while(n-- > 0){
      r.r += (*apr * *bpr - *api * *bpi);
      r.i -= (*api * *bpr + *apr * *bpi);
      apr += ast; api += ast;
      bpr += bst; bpi += bst;
  }
  return r;
}

void vsip_cgemp_d(vsip_cscalar_d alpha,
                   const vsip_cmview_d *AA,
                   vsip_mat_op OpA,
                   const vsip_cmview_d *BB,
                   vsip_mat_op OpB,
                   vsip_cscalar_d beta,
                   const vsip_cmview_d *C){
  vsip_cmview_d At = *AA,
                Bt = *BB;
  vsip_cmview_d *A = &At,
                *B = &Bt;
  vsip_cscalar_d (*dot)(const vsip_cvview_d*,const vsip_cvview_d*) = vsip_cvdot_d;
  if((OpA == VSIP_MAT_TRANS) || (OpA == VSIP_MAT_HERM)){
       A->row_length = AA->col_length;
       A->col_length = AA->row_length;
       A->row_stride = AA->col_stride;
       A->col_stride = AA->row_stride;
  }
  if((OpB == VSIP_MAT_TRANS) || (OpB == VSIP_MAT_HERM)){
       B->row_length = BB->col_length;
       B->col_length = BB->row_length;
       B->row_stride = BB->col_stride;
       B->col_stride = BB->row_stride;
  }
  {
      vsip_length M = A->col_length,
                  N = B->row_length;
      vsip_length i,j;
      vsip_cvview_d aa,bb,cc,*a,*b,*c,*af,*bs;
      vsip_offset Boffset = B->offset;
      vsip_stride Brow_stride = B->row_stride,
                  Acol_stride = A->col_stride;
      a = &aa;b = &bb;
      CMROWVIEW(A,0,a);
      CMCOLVIEW(B,0,b);
      af = a; bs = b;
      if( ((OpA == VSIP_MAT_HERM) || (OpA == VSIP_MAT_CONJ)) && ((OpB != VSIP_MAT_HERM) || (OpB != VSIP_MAT_CONJ))){
                  dot = vsip_cvjdot_d;
                  af = b;
                  bs = a;
      }
      if( ((OpA != VSIP_MAT_HERM) || (OpA != VSIP_MAT_CONJ)) && ((OpB ==VSIP_MAT_HERM) || (OpB ==VSIP_MAT_CONJ))){
                 dot = vsip_cvjdot_d;
      } 
      if( ((OpA == VSIP_MAT_HERM) || (OpA == VSIP_MAT_CONJ)) && ((OpB ==VSIP_MAT_HERM) || (OpB ==VSIP_MAT_CONJ))){
                  dot = VI_cvjjdot_d;
      }
      c = &cc;
      CMROWVIEW(C,0,c);
      {
        vsip_cscalar_d temp;
        vsip_scalar_d  temp_r;
        vsip_stride str  = c->stride * c->block->cstride;
        vsip_stride str1 = C->col_stride * C->block->cstride;
        vsip_scalar_d  *c_pr_r =(vsip_scalar_d*) (c->block->R->array + c->offset * c->block->cstride),
                       *c_pr1_r = c_pr_r;
        vsip_scalar_d  *c_pr_i =(vsip_scalar_d*) (c->block->I->array + c->offset * c->block->cstride),
                       *c_pr1_i = c_pr_i;
        for(i = 0; i < M; i++){
          c_pr_r = c_pr1_r;
          c_pr_i = c_pr1_i;
          b->offset = Boffset;
          for(j =0; j < N; j++){
               temp_r = beta.r * *c_pr_r - beta.i * *c_pr_i;
              *c_pr_i = beta.i * *c_pr_r + beta.r * *c_pr_i;
              *c_pr_r = temp_r;
               temp = dot(af,bs);
              *c_pr_r += (alpha.r * temp.r - alpha.i * temp.i);
              *c_pr_i += (alpha.i * temp.r + alpha.r * temp.i);
               c_pr_r += str;
               c_pr_i += str;
               b->offset += Brow_stride;
          }  
          a->offset += Acol_stride;
          c_pr1_r += str1;
          c_pr1_i += str1;
        }
      }
   }  
}
