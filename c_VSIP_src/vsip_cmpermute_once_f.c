/* Created RJudd  */
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
#include"vsip_cmviewattributes_f.h"
#include"vsip_vviewattributes_vi.h"

void vsip_cmpermute_once_f(
     const vsip_cmview_f* in,
     vsip_major major,
     const vsip_vview_vi* p,
     const vsip_cmview_f* out){
   vsip_length n_dta; /* length of data row/col to copy */
   vsip_length n_ind; /* length of matrix col/row to index */
   vsip_stride in_dta_strd, out_dta_strd;
   vsip_stride in_ind_strd, out_ind_strd;
   vsip_index i,j;
   if(major == VSIP_ROW){ 
      n_dta = in->row_length;
      n_ind = in->col_length;
      in_dta_strd = in->row_stride * in->block->cstride;
      in_ind_strd = in->col_stride * in->block->cstride;
      out_dta_strd = out->row_stride * out->block->cstride;
      out_ind_strd = out->col_stride * out->block->cstride;
   } else {
      n_dta = in->col_length;
      n_ind = in->row_length;
      in_dta_strd = in->col_stride * in->block->cstride;
      in_ind_strd = in->row_stride * in->block->cstride;
      out_dta_strd = out->col_stride * out->block->cstride;
      out_ind_strd = out->row_stride * out->block->cstride;      
   }
   if(in == out) { /* in-place */
      vsip_scalar_f *ptr_re = in->block->R->array + in->offset * in->block->cstride;
      vsip_scalar_f *ptr_im = in->block->I->array + in->offset * in->block->cstride;
      vsip_scalar_vi *b = p->block->array + p->offset;
      for(i=0; i<n_ind; i++){
         vsip_index r_or_c = b[i * p->stride]; /* row or column to copy to */
         register vsip_index from0 = b[i * p->stride] * in_ind_strd;
         register vsip_index to0 = i * in_ind_strd;
         if(from0 != to0) {
            for(j=0; j<n_dta; j++){
               vsip_index to = to0 + j * in_dta_strd;
               vsip_index from = from0 + j * in_dta_strd;
               vsip_scalar_f t = ptr_re[to];
               ptr_re[to] = ptr_re[from];
               ptr_re[from] = t;
               t = ptr_im[to];
               ptr_im[to] = ptr_im[from];
               ptr_im[from] = t;
            }
            j=i;
            while(i != b[j * p->stride]){
               j++;
               if(j > n_ind) exit(-1);
            }
            b[j * p->stride] = r_or_c;
         }
      } 
   } else { /* out-of-place */
      vsip_scalar_f *in_ptr_re = in->block->R->array + in->offset * in->block->cstride;
      vsip_scalar_f *out_ptr_re = out->block->R->array + out->offset * out->block->cstride;
      vsip_scalar_f *in_ptr_im = in->block->I->array + in->offset * in->block->cstride;
      vsip_scalar_f *out_ptr_im = out->block->I->array + out->offset * out->block->cstride;
      vsip_scalar_vi *in = p->block->array + p->offset;
      for(i=0; i<n_ind; i++){
         vsip_scalar_f *pin_re = in_ptr_re + in[i * p->stride] * in_ind_strd;
         vsip_scalar_f *pout_re = out_ptr_re + i * out_ind_strd;
         vsip_scalar_f *pin_im = in_ptr_im + in[i * p->stride] * in_ind_strd;
         vsip_scalar_f *pout_im = out_ptr_im + i * out_ind_strd;
         for(j=0; j < n_dta; j++){
            *pout_re = *pin_re;
            *pout_im = *pin_im;
            pout_re += out_dta_strd;
            pout_im += out_dta_strd;
            pin_re += in_dta_strd;
            pin_im += in_dta_strd;
         }
      }
   }
   return;
}
