/* Created RJudd March 6, 2000*/
/* SPAWARSYSCEN D857 */
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
/* $Id: vsip_malltrue_bl.c,v 2.0 2003/02/22 15:18:54 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_bl.h>

vsip_scalar_bl (vsip_malltrue_bl)(
  const vsip_mview_bl *r){ 
  vsip_stride M = r->row_length * r->col_length;
  { 
    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride rst_mj, rst_mn;
    vsip_scalar_bl *rp = r->block->array + r->offset;
    vsip_scalar_bl *rp0 = rp;
    /* pick search direction */
    if(r->row_stride < r->col_stride){
           n_mj = r->row_length; n_mn = r->col_length;
           rst_mj = r->row_stride; rst_mn = r->col_stride;
    } else {
           n_mn = r->row_length; n_mj = r->col_length;
           rst_mn = r->row_stride; rst_mj = r->col_stride;
    }
    /* end define */
    while(n_mn-- > 0){
          vsip_length n = n_mj;
          while(n-- >0){
            if(*rp != VSIP_FALSE) M--;
            rp += rst_mj;
          }
          rp0 += rst_mn;
          rp = rp0;
    }
  }
  return ((M == 0) ? VSIP_TRUE : VSIP_FALSE);
}
