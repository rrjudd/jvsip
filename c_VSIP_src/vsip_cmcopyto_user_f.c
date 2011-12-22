/* Created RJudd September 5, 2006 */
/* VSIPL Consultant */
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
/* $Id: vsip_cmcopyto_user_f.c,v 2.1 2007/04/18 17:15:17 judd Exp $ */

#include<vsip.h>
#include<vsip_cmviewattributes_f.h>

void (vsip_cmcopyto_user_f)(
  const vsip_cmview_f* a,
  vsip_major major,
  vsip_scalar_f* const re,
  vsip_scalar_f* const im){
   vsip_index i,j;
   vsip_length m = a->col_length;
   vsip_length n = a->row_length;
   vsip_stride ast_row = a->row_stride * a->block->cstride;
   vsip_stride ast_col = a->col_stride * a->block->cstride;
   vsip_scalar_f *ap_r = (a->block->R->array) + a->offset * a->block->cstride;
   vsip_scalar_f *ap_i = (a->block->I->array) + a->offset * a->block->cstride;
   vsip_scalar_f *aprow_r;
   vsip_scalar_f *apcol_r;
   vsip_scalar_f *aprow_i;
   vsip_scalar_f *apcol_i;
   if(im == NULL){ /* user storage must be interleaved */
      if(major == VSIP_ROW){
         vsip_scalar_f *rp = re;
         for(j=0; j<m; j++){
            aprow_r = ap_r + ast_col * j;
            aprow_i = ap_i + ast_col * j;
            for(i=0; i<n; i++){
               *rp = *aprow_r;
               rp++; aprow_r += ast_row;
               *rp = *aprow_i;
               aprow_i += ast_row; rp++;
             }
         }
      } else { /* must be column */
         vsip_scalar_f *rp = re;
         for(i=0; i<n; i++){
            apcol_r = ap_r + ast_row * i;
            apcol_i = ap_i + ast_row * i;
            for(j=0; j<m; j++){
               *rp = *apcol_r;
               rp++; apcol_r += ast_col;
               *rp = *apcol_i;
               apcol_i += ast_col; rp++;
            }
         }
      }
   } else { /* user storage must be split */
      if(major == VSIP_ROW){
         vsip_scalar_f *rp = re;
         vsip_scalar_f *ip = im;
         for(j=0; j<m; j++){
            aprow_r = ap_r + ast_col * j;
            aprow_i = ap_i + ast_col * j;
            for(i=0; i<n; i++){
               *rp = *aprow_r;
               rp++; aprow_r += ast_row;
               *ip = *aprow_i;
               aprow_i += ast_row; ip++;
             }
         }
      } else { /* must be column */
         vsip_scalar_f *rp = re;
         vsip_scalar_f *ip = im;
         for(i=0; i<n; i++){
            apcol_r = ap_r + ast_row * i;
            apcol_i = ap_i + ast_row * i;
            for(j=0; j<m; j++){
               *rp = *apcol_r;
               rp++; apcol_r += ast_col;
               *ip = *apcol_i;
               apcol_i += ast_col; ip++;
            }
         }
      }
   }
   return;
}

