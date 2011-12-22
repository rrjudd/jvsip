/* Created RJudd October 17, 1999*/
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
/* $Id: vsip_lud_d.c,v 2.0 2003/02/22 15:18:53 judd Exp $ */
/* vsip_lud_d */    
#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_ludattributes_d.h>

static vsip_index VI_max_index_d(
       vsip_length N,
       vsip_mview_d *A){
    vsip_scalar_d *ap = A->block->array + A->offset * A->block->rstride;
    vsip_stride    ast = A->col_stride * A->block->rstride;
    vsip_scalar_d *ap0 = ap;
    vsip_scalar_d max =  (*ap < 0) ? -*ap : *ap,
                  max0;
    vsip_index n;
    vsip_index index = 0; 
    for(n=1; n<A->col_length; n++){
       ap += ast;
       if( (max0 = (*ap < 0) ? -*ap: *ap) > max){
          max = max0;
          index = n;
       }
    }
    if(index != 0){
      vsip_scalar_d temp;
      ap = ap0 + index * ast;
      ast = A->row_stride * A->block->rstride;      
      ap -=(N - A->row_length) * ast;
      ap0-=(N - A->row_length) * ast;
      n=N;
      while(n-- > 0){
         temp = *ap0;
         *ap0 = *ap;
         *ap  = temp;
          ap+=ast; ap0+=ast;
      }
   }
   return index;
}
 
static int VI_mlud_update_rm_d(
       vsip_mview_d *A){
    vsip_index m = 1,
               n = A->row_length;
    vsip_stride ar_st = A->row_stride * A->block->rstride;
    vsip_stride ac_st = A->col_stride * A->block->rstride;
    vsip_scalar_d *ap0 = A->block->array + A->offset * A->block->rstride;
    vsip_scalar_d *ap0_0 = ap0;
    vsip_scalar_d *ap1 = ap0_0 + ac_st;
    vsip_scalar_d *ap1_0 = ap1;
    vsip_scalar_d pivot, scale;
    pivot = *ap0;
    if(pivot == 0) return 1;
    while(m++ < A->col_length){
       scale = *ap1 / pivot;
       *ap1 =  scale;
       while(n-- > 1){ 
          ap0 += ar_st; ap1 += ar_st;
          *ap1 -= (scale * *ap0);
       }
       n = A->row_length; 
       ap0 = ap0_0;
       ap1_0 += ac_st; ap1 = ap1_0;
    }
    return 0;
}
static int VI_mlud_update_cm_d(
       vsip_mview_d *A){
    vsip_index m = 1,
               n = A->row_length,
               M = A->col_length;
    vsip_stride ar_st = A->row_stride * A->block->rstride;
    vsip_stride ac_st = A->col_stride * A->block->rstride;
    vsip_scalar_d *ap0 = A->block->array + A->offset * A->block->rstride;
    vsip_scalar_d *ap1 = ap0 + ac_st;
    vsip_scalar_d *ap1_0 = ap1;
    vsip_scalar_d *scp = ap1; /* pointer to scaling factor */
    vsip_scalar_d *scp_0 = ap1; /* pointer to first element of scale column */
    vsip_scalar_d pivot = *ap0;
    if(pivot == 0) return 1;
    /* calculate pivots */
    while(m++ < M){
       *ap1 /= pivot;
        ap1 += ac_st;
    }
    /* done pivots */
    ap1_0 += ar_st; ap1 = ap1_0;
    while(n-- > 1){ 
       m = 1;
       ap0 += ar_st;
       while(m++ < M){
          *ap1 -= (*scp * *ap0);
          ap1 += ac_st; scp += ac_st; 
          
       }
       scp = scp_0;
       ap1_0 += ar_st; ap1 = ap1_0;
    }
    return 0;
}

int vsip_lud_d(
    vsip_lu_d *lud, 
    const vsip_mview_d *A)
{
    int retval = 0;
    vsip_mview_d a = *A;
    vsip_index *p = lud->P;
    vsip_offset a_diag_st = a.row_stride + a.col_stride;
    vsip_length N = A->row_length;
    vsip_offset  n_cl = 0;
    int (*lud_update_d)(vsip_mview_d*) = ((A->row_stride < A->col_stride) ?
                  VI_mlud_update_rm_d : VI_mlud_update_cm_d);
    lud->LLU = a; lud->LU = &lud->LLU;

    if((A->col_length != N) || (N != lud->N)){ retval = 1; return retval;}
    while(n_cl++ < N - 1){ /* L U decomposition in place */
           *p = VI_max_index_d(N,&a); /* find pivot, exchange rows */
            p++;
           /* update matrix */
           if(lud_update_d(&a)) return 1;
           /* upadate row and column for next update */
           a.row_length--;
           a.col_length--;
           a.offset += a_diag_st;
     }
     return retval;
}
