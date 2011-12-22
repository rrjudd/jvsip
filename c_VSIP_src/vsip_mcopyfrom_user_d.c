/* Created RJudd */
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
/* $Id: vsip_mcopyfrom_user_d.c,v 2.1 2007/04/18 17:15:18 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_d.h>

void (vsip_mcopyfrom_user_d)(
  vsip_scalar_d* const r,
  vsip_major major,
  const vsip_mview_d *a){
   vsip_length row_length = a->row_length;
   vsip_length col_length = a->col_length;
   vsip_scalar_d *ap = a->block->array + a->offset * a->block->rstride;
   vsip_stride row_st = a->row_stride * a->block->rstride,
               col_st = a->col_stride * a->block->rstride;
   vsip_scalar_d *rp = r;
   vsip_index i,j;
   if(major == VSIP_ROW){ /* copy by rows */
      for(i=0; i<col_length; i++){
         vsip_scalar_d *ap_r = ap + i * col_st;
         for(j=0; j<row_length; j++){
            *ap_r = *rp;
            rp++; ap_r += row_st;
         }
       }
    } else { /* copy by columns */
       for(j=0; j<row_length; j++){
         vsip_scalar_d *ap_c = ap + j * row_st;
         for(i=0; i<col_length; i++){
            *ap_c = *rp;
            rp++; ap_c += col_st;
         }
      }
   }
   return;
}
