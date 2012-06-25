/* Created RJudd June 24,2012 */
/* JVSIP  */
/* created starting with vsip_mfill_si.c */
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
#include<vsip.h>
#include<vsip_mviewattributes_uc.h>

void vsip_mfill_uc(
          vsip_scalar_uc alpha,
          const vsip_mview_uc* r) {
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride rst_mj, rst_mn;
    vsip_scalar_uc *rp = (r->block->array) + r->offset;
    vsip_scalar_uc *rp0 = rp;
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
