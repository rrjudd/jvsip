/* Created RJudd  */
/* $Id: vsip_mpermute_f.c,v 2.1 2008/08/17 18:01:49 judd Exp $ */

/*
 *  vsip_mpermute_f.c
 *  Created by Randall Judd on 7/21/07.
 *
 */
/*********************************************************************
 // This code includes                                                 /
 // no warranty, express or implied, including the warranties          /
 // of merchantability and fitness for a particular purpose.           /
 // No person or entity                                                /
 // assumes any legal liability or responsibility for the accuracy,    /
 // completeness, or usefulness of any information, apparatus,         /
 // product, or process disclosed, or represents that its use would    /
 // not infringe privately owned rights                                /
 **********************************************************************/

#include"vsip.h"
#include"vsip_permuteattributes.h"
#include"vsip_vviewattributes_vi.h"
#include"vsip_mviewattributes_f.h"


void 
vsip_mpermute_f( 
      const vsip_mview_f *in, 
      const vsip_permute *perm, 
      const vsip_mview_f *out){
   vsip_length n_dta; /* length of data row/col to copy */
   vsip_length n_ind; /* length of matrix col/row to index */
   vsip_stride in_dta_strd, out_dta_strd;
   vsip_stride in_ind_strd, out_ind_strd;
   vsip_index i,j;
   if(perm->major == VSIP_ROW){ 
      n_dta = in->row_length;
      n_ind = in->col_length;
      in_dta_strd = in->row_stride * in->block->rstride;
      in_ind_strd = in->col_stride * in->block->rstride;
      out_dta_strd = out->row_stride * out->block->rstride;
      out_ind_strd = out->col_stride * out->block->rstride;
   } else {
      n_dta = in->col_length;
      n_ind = in->row_length;
      in_dta_strd = in->col_stride * in->block->rstride;
      in_ind_strd = in->row_stride * in->block->rstride;
      out_dta_strd = out->col_stride * out->block->rstride;
      out_ind_strd = out->row_stride * out->block->rstride;      
   }
   if(in == out) { /* in-place */
      vsip_scalar_f *ptr = in->block->array + in->offset * in->block->rstride;
      vsip_scalar_vi *b = perm->b;
      for(i=0; i<n_ind; i++){ /* initialize modifiable index vector */
         b[i]=perm->in[i];    /* in[i] should remain const unless reinitialized */
      }
      for(i=0; i<n_ind; i++){
         vsip_index r_or_c = b[i]; /* row or column to copy to */
         register vsip_index from0 = b[i] * in_ind_strd;
         register vsip_index to0 = i * in_ind_strd;
         if(from0 != to0) {
            for(j=0; j<n_dta; j++){
               vsip_index to = to0 + j * in_dta_strd;
               vsip_index from = from0 + j * in_dta_strd;
               vsip_scalar_f t = ptr[to];
               ptr[to] = ptr[from];
               ptr[from] = t;
            }
            j=i;
            while(i != b[j]){
               j++;
               if(j > n_ind) exit(-1);
            }
            b[j] = r_or_c;
         }
      } 
   } else { /* out-of-place */
      vsip_scalar_f *in_ptr = in->block->array + in->offset * in->block->rstride;
      vsip_scalar_f *out_ptr = out->block->array + out->offset * out->block->rstride;
      vsip_scalar_vi *in = perm->in;
      for(i=0; i<n_ind; i++){
         vsip_scalar_f *pin = in_ptr + in[i] * in_ind_strd;
         vsip_scalar_f *pout = out_ptr + i * out_ind_strd;
         for(j=0; j < n_dta; j++){
            *pout = *pin;
            pout += out_dta_strd;
            pin += in_dta_strd;
         }
      }
   }
   return;
}



