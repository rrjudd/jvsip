/* Created RJudd March 12, 1998 */
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
/* $Id: vsip_cvouter_f.c,v 2.1 2004/05/16 05:01:48 judd Exp $ */
/* April 20, 1998 1,2 to row,col */
/* Modified RJudd Feb 14, 1999 */
/* to fix cmbind */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include<vsip_cmviewattributes_f.h>

void (vsip_cvouter_f)(
  vsip_cscalar_f alpha,
  const vsip_cvview_f* a,
  const vsip_cvview_f* b,
  const vsip_cmview_f* R) {   /* R_ij = a_i * conj(b_j) */
  if((a->block == b->block) && (a->offset == b->offset) && (alpha.i == 0)){ /* covariance matrix with real multiplier */
     vsip_length  n = a->length;
     vsip_stride cRst = R->block->cstride,
                 cast = a->block->cstride;
     vsip_scalar_f *a_pr = (vsip_scalar_f*)(a->block->R->array + cast * a->offset),
                   *a_pi = (vsip_scalar_f*)(a->block->I->array + cast * a->offset);
     vsip_length i,j;
     vsip_stride stRu = cRst * R->row_stride, /* upper stride (above diagonal) */
                 stRl = cRst * R->col_stride, /* lower stride (below diagonal) */
                 sta = cast * a->stride; /* stride of a (and b) */
     vsip_offset Ro  = cRst * R->offset,
                 Rdiag = cRst * (R->col_stride + R->row_stride);
     vsip_scalar_f *R_pr = (vsip_scalar_f*)(R->block->R->array + Ro),
                   *R_pi = (vsip_scalar_f*)(R->block->I->array + Ro);
     for(i=0; i<n; i++){
        /* prep for next loop */
        vsip_scalar_f *R_plr = R_pr + stRl,  /* pointer to lower real */
                      *R_pli = R_pi + stRl,  /* pointer to lower imaginary */
                      *R_pur = R_pr + stRu,  /* pointer to upper real */
                      *R_pui = R_pi + stRu;  /* pointer to upper imaginary */
        vsip_scalar_f atmp_r = *a_pr * alpha.r;
        vsip_scalar_f atmp_i = *a_pi * alpha.r;
        vsip_scalar_f *b_pr = a_pr + sta, *b_pi = a_pi + sta;
        /* do diagonal member */
        *(R_pr) = (atmp_r * *a_pr + atmp_i * *a_pi);
        *(R_pi) = 0;
        R_pr += Rdiag; R_pi += Rdiag;
        for(j=i+1; j<n; j++){
          /* do other members, along row for upper, column for lower */
          vsip_scalar_f tmp = (atmp_r * *b_pr + atmp_i * *b_pi);
          *R_plr = tmp; *R_pur = tmp;
          tmp = (atmp_i * *b_pr - atmp_r * *b_pi);
          *R_pli = -tmp; *R_pui = tmp;
           R_plr += stRl; R_pli += stRl;
           R_pur += stRu; R_pui += stRu;
           b_pr += sta; b_pi += sta;
        }
        a_pr += sta, a_pi += sta;
     }
  } else { 
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
         vsip_cscalar_f temp = vsip_cmul_f(alpha,vsip_cmplx_f(*a_pr,*a_pi));
         for(j=0; j<m; j++){
             *R_pr = (temp.r * *b_pr + temp.i * *b_pi);
             *R_pi = (temp.i * *b_pr - temp.r * *b_pi);
              R_pr += stR; b_pr += stb;
              R_pi += stR; b_pi += stb;
         }
         a_pr += sta;
         a_pi += sta;
     }  
  }
}

