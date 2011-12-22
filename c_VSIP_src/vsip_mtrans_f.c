/* Created R Judd March 18, 1998 */
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
/* $Id: vsip_mtrans_f.c,v 2.0 2003/02/22 15:19:01 judd Exp $ */
/* April 21, 1998 1,2 to row,col */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_mviewattributes_f.h>

void (vsip_mtrans_f)(
  const vsip_mview_f* A,
  const vsip_mview_f* R) {	/* transpose matrix	*/
  { 
    vsip_length  lx = A->row_length,
                 ly = A->col_length;
    vsip_scalar_f tmp;
    vsip_scalar_f *a_p = A->block->array + A->offset * A->block->rstride,
                  *r_p = R->block->array + R->offset * R->block->rstride;
    vsip_length i, j;
    vsip_stride stAx = A->row_stride * A->block->rstride, stAy = A->col_stride * A->block->rstride;
    vsip_stride stRx = R->row_stride * R->block->rstride, stRy = R->col_stride * R->block->rstride;
    if((lx == ly) && (a_p == r_p)){
      for(i=1; i<lx; i++){
        for(j=0; j<i; j++){ 
           tmp = *(a_p + j * stAy + i * stAx);
           *(a_p + j * stAy + i * stAx) = *(a_p + j * stAx + i * stAy);
           *(a_p + j * stAx + i * stAy) = tmp; 
        }
      }
    } else {
       for(i=0; i<ly; i++){
         r_p = R->block->array + R->offset * R->block->rstride + i * stRx;
         a_p = A->block->array + A->offset * A->block->rstride + i * stAy;
         for(j=0; j<lx; j++){
            *r_p = *a_p;
            r_p += stRy; a_p += stAx;
         }
      }
    }
  }
}

