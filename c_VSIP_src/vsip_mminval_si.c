/* Created RJudd November 21, 2012 */
/* See copyright (MIT License) included with distribution */
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
#include<vsip_mviewattributes_si.h>

vsip_scalar_si vsip_mminval_si(
  const vsip_mview_si *r,
  vsip_scalar_mi *index)
{ 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride rst_mj, rst_mn;
    vsip_scalar_si *rp = (r->block->array) + r->offset;
    vsip_scalar_si *rp0 = rp;
    vsip_scalar_si retval = *rp0;
    vsip_index major_i = 0,
               minor_i = 0;
    vsip_length n0_mn,n0_mj;
    /* pick search direction */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
    } else {
           n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
    }
    n0_mn = n_mn - 1;
    n0_mj = n_mj - 1;
    /*end define*/
    while(n_mn-- > 0){
          vsip_length n = n_mj;
          while(n-- >0){
            if(retval > *rp){
                   retval = *rp;
                   major_i = n0_mj - n;
                   minor_i = n0_mn - n_mn;
            }
            rp += rst_mj;
          }
          rp0 += rst_mn;
          rp = rp0;
    }
    if(index != NULL){
       if(r->row_stride < r->col_stride){
           index->r = minor_i;
           index->c = major_i;
       } else {
           index->r = major_i;
           index->c = minor_i;
       }
    }
    return retval;
}
