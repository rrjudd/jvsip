/* Created RJudd */
/* SPAWARSYSCEN  */
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
/* $Id: vsip_mfill_i.c,v 2.1 2004/04/03 16:03:08 judd Exp $ */

#include"vsip.h"
#include"vsip_mviewattributes_i.h"

void (vsip_mfill_i)(
          vsip_scalar_i alpha,
          const vsip_mview_i* r) {
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride rst_mj, rst_mn;
    vsip_scalar_i *rp = (r->block->array) + r->offset;
    vsip_scalar_i *rp0 = rp;
    if(r->row_stride < r->col_stride){
       n_mj = r->row_length; n_mn = r->col_length;
       rst_mj = r->row_stride; rst_mn = r->col_stride;
    } else {
       n_mn = r->row_length; n_mj = r->col_length;
       rst_mn = r->row_stride; rst_mj = r->col_stride;
    }
    while(n_mn-- > 0){
       vsip_length n = n_mj;
       while(n-- >0){
          *rp  = alpha;
           rp += rst_mj;
       }
       rp0 += rst_mn;
       rp = rp0;
    }
}
