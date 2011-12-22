/* Created RJudd September 15, 1999*/
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
/* $Id: vsip_clud_f.c,v 2.0 2003/02/22 15:18:41 judd Exp $ */
/* vsip_clud_f */    
#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_cmviewattributes_f.h>
#include<vsip_cludattributes_f.h>

static vsip_index VI_max_index_f(
       vsip_length N,
       vsip_cmview_f *A){
    vsip_scalar_f *ap_r = A->block->R->array + A->offset * A->block->cstride,
                  *ap_i = A->block->I->array + A->offset * A->block->cstride;
    vsip_stride    ast = A->col_stride * A->block->cstride;
    vsip_scalar_f *ap0_r = ap_r,
                  *ap0_i = ap_i;
    vsip_scalar_f max = *ap_i * *ap_i + *ap_r * *ap_r,
                  max0;
    vsip_index n;
    vsip_index index = 0; 
    for(n=1; n<A->col_length; n++){
       ap_r += ast, ap_i += ast;
       if((max0 = *ap_r * *ap_r + *ap_i * *ap_i) > max){
          max = max0;
          index = n;
       }
    }
    if(index != 0){
      vsip_cscalar_f temp;
      vsip_scalar_vi ofst;
      ap_r = ap0_r + index * ast;
      ap_i = ap0_i + index * ast;
      ast = A->row_stride * A->block->cstride;      
      ofst = (N - A->row_length) * ast;
      ap_r -= ofst;
      ap_i -= ofst;
      ap0_r-= ofst;
      ap0_i-= ofst;
      n=N;
      while(n-- > 0){
         temp.r = *ap0_r;
         temp.i = *ap0_i;
         *ap0_r = *ap_r;
         *ap0_i = *ap_i;
         *ap_r  = temp.r;
         *ap_i  = temp.i;
          ap_r+=ast; ap0_r+=ast;
          ap_i+=ast; ap0_i+=ast;
      }
   }
   return index;
}
 
static int VI_mlud_update_rm_f(
       vsip_cmview_f *A){
    vsip_index m = 1,
               n = A->row_length;
    vsip_stride ar_st = A->row_stride * A->block->cstride;
    vsip_stride ac_st = A->col_stride * A->block->cstride;
    vsip_scalar_f *ap0_r = A->block->R->array + A->offset * A->block->cstride,
                  *ap0_i = A->block->I->array + A->offset * A->block->cstride;
    vsip_scalar_f *ap0_0_r = ap0_r,
                  *ap0_0_i = ap0_i;
    vsip_scalar_f *ap1_r = ap0_0_r + ac_st,
                  *ap1_i = ap0_0_i + ac_st;
    vsip_scalar_f *ap1_0_r = ap1_r,
                  *ap1_0_i = ap1_i;
    vsip_scalar_f pivot;
    vsip_cscalar_f scale;
    pivot = *ap0_r * *ap0_r + *ap0_i * *ap0_i;
    if(pivot == 0) return 1;
    while(m++ < A->col_length){
       scale.r = (*ap1_r * *ap0_r + *ap1_i * *ap0_i)/pivot ;
       scale.i = (*ap1_i * *ap0_r - *ap1_r * *ap0_i)/pivot ;
       *ap1_r =  scale.r; *ap1_i =  scale.i;
       while(n-- > 1){ 
          ap0_r += ar_st; ap1_r += ar_st;
          ap0_i += ar_st; ap1_i += ar_st;
          *ap1_r -= (scale.r * *ap0_r - scale.i * *ap0_i);
          *ap1_i -= (scale.r * *ap0_i + scale.i * *ap0_r);
       }
       n = A->row_length; 
       ap0_r = ap0_0_r; ap0_i = ap0_0_i;
       ap1_0_r += ac_st; ap1_r = ap1_0_r;
       ap1_0_i += ac_st; ap1_i = ap1_0_i;
    }
    return 0;
}
static int VI_mlud_update_cm_f(
       vsip_cmview_f *A){
    vsip_index m = 1,
               n = A->row_length,
               M = A->col_length;
    vsip_stride ar_st = A->row_stride * A->block->cstride;
    vsip_stride ac_st = A->col_stride * A->block->cstride;
    vsip_scalar_f *ap0_r = A->block->R->array + A->offset * A->block->cstride,
                  *ap0_i = A->block->I->array + A->offset * A->block->cstride;
    vsip_scalar_f *ap1_r = ap0_r + ac_st,
                  *ap1_i = ap0_i + ac_st;
    vsip_scalar_f *ap1_0_r = ap1_r,
                  *ap1_0_i = ap1_i;
    vsip_scalar_f *scp_r = ap1_r,
                  *scp_i = ap1_i; /* pointer to scaling factor */
    vsip_scalar_f *scp_0_r = ap1_r,
                  *scp_0_i = ap1_i; /* pointer to first element of scale column */
    vsip_scalar_f pivot = *ap0_r * *ap0_r + *ap0_i * *ap0_i,
                  scale;
    if(pivot == 0) return 1;
    /* calculate pivots */
    while(m++ < M){
       scale = (*ap1_r * *ap0_r + *ap1_i * *ap0_i)/pivot ;
       *ap1_i = (*ap1_i * *ap0_r - *ap1_r * *ap0_i)/pivot ;
       *ap1_r = scale;
        ap1_r += ac_st; ap1_i +=ac_st;
    }
    /* done pivots */
    ap1_0_r += ar_st; ap1_r = ap1_0_r;
    ap1_0_i += ar_st; ap1_i = ap1_0_i;
    while(n-- > 1){ 
       m = 1;
       ap0_r += ar_st; ap0_i += ar_st;
       while(m++ < M){
          *ap1_r -= (*scp_r * *ap0_r - *scp_i * *ap0_i);
          *ap1_i -= (*scp_r * *ap0_i + *scp_i * *ap0_r);
          ap1_r += ac_st; scp_r += ac_st;
          ap1_i += ac_st; scp_i += ac_st;
          
       }
       scp_r = scp_0_r; scp_i = scp_0_i;
       ap1_0_r += ar_st; ap1_r = ap1_0_r;
       ap1_0_i += ar_st; ap1_i = ap1_0_i;
    }
    return 0;
}

int vsip_clud_f(
    vsip_clu_f *lud, 
    const vsip_cmview_f *A)
{
    int retval = 0;
    vsip_cmview_f a = *A;
    vsip_index *p = lud->P;
    vsip_offset a_diag_st = a.row_stride + a.col_stride;
    vsip_length N = A->row_length;
    vsip_offset  n_cl = 0;
    int (*lud_update_f)(vsip_cmview_f*) = ((A->row_stride < A->col_stride) ?
                  VI_mlud_update_rm_f : VI_mlud_update_cm_f);
    lud->LLU = a; lud->LU = &lud->LLU;

    if((A->col_length != N) || (N != lud->N)){ retval = 1; return retval;}
    while(n_cl++ < N - 1){ /* L U decomposition in place */
           *p = VI_max_index_f(N,&a); /* find pivot, exchange rows */
            p++;
           /* update matrix */
           if(lud_update_f(&a)) retval = 1;
           /* upadate row and column for next update */
           a.row_length--;
           a.col_length--;
           a.offset += a_diag_st;
     }
     return retval;
}
