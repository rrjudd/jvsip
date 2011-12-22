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
/* $Id: vsip_mindexbool.c,v 2.0 2003/02/22 15:18:57 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_mi.h>
#include<vsip_mviewattributes_bl.h>

vsip_length vsip_mindexbool(
   const vsip_mview_bl *r,
   vsip_vview_mi *x){
   vsip_length retval = 0;
   {
     vsip_length n_mj, /* major length */
                 n_mn; /* minor length */
      vsip_stride mn_i = -1, 
                  mj_i = -1;
      vsip_stride rst_mj, rst_mn;
      vsip_scalar_bl *rp = r->block->array + r->offset;
      vsip_scalar_bl *rp0 = rp;
      vsip_scalar_vi *xp = x->block->array + x->offset,
                     *xp_mj, *xp_mn;
      vsip_stride xst = 2 * x->stride;
      /* pick search direction */
      if(r->row_stride < r->col_stride){
             xp_mj = xp + 1; xp_mn = xp;
             n_mj = r->row_length; n_mn = r->col_length;
             rst_mj = r->row_stride; rst_mn = r->col_stride;
      } else {
             xp_mj = xp; xp_mn = xp + 1;
             n_mn = r->row_length; n_mj = r->col_length;
             rst_mn = r->row_stride; rst_mj = r->col_stride;
      }
      /* end define */
      while(mn_i++ < (vsip_stride)(n_mn - 1)){
         mj_i = -1;
         while(mj_i++ < (vsip_stride)(n_mj - 1)){
           if(*rp != VSIP_FALSE){
              *xp_mj = (vsip_index)mj_i;
              *xp_mn = (vsip_index)mn_i;
              xp_mj += xst; xp_mn+= xst;
              retval++;
           }
           rp += rst_mj;
         }
         rp0 += rst_mn;
         rp = rp0;
      }
      if(retval > 0) x->length = retval;
   }
   return retval;
}
