/* Created RJudd February 13, 2000 */
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
/* $Id: vsip_mhisto_f.c,v 2.2 2004/07/18 15:33:48 judd Exp $ */

#include"vsip.h"
#include"vsip_mviewattributes_f.h"
#include"vsip_vviewattributes_f.h"
#include"VI_vfill_f.h"

void (vsip_mhisto_f)(
  const vsip_mview_f* a,
  vsip_scalar_f min,
  vsip_scalar_f max,
  vsip_hist_opt opt,
  const vsip_vview_f* r) { /* histogram	*/
  {
    vsip_stride		str = 0;
    vsip_length		p = r->length;
    double              p_s = (double)(p - 2);
    vsip_stride rst = r->stride * r->block->rstride;
    double	scale = (double)rst * p_s;
    double      iscale = (double)(max-min);
    vsip_scalar_f *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_f *rp0 = rp, *rp_end = rp + p - 1 ;

    vsip_length n_mj, /* major length */
                n_mn; /* minor length */
    vsip_stride ast_mj, ast_mn;
    vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride;
    vsip_scalar_f *ap0 = ap;
    if(a->row_stride < a->col_stride){
           n_mj = a->row_length; n_mn = a->col_length;
           ast_mj = a->row_stride; ast_mn = a->col_stride;
           ast_mj *= a->block->rstride; ast_mn *= a->block->rstride;
    } else {
           n_mn = a->row_length; n_mj = a->col_length;
           ast_mn = a->row_stride; ast_mj = a->col_stride;
           ast_mn *= a->block->rstride; ast_mj *= a->block->rstride;
    }

    rp++;
    if(opt == VSIP_HIST_RESET) VI_vfill_f((vsip_scalar_f)0., r);
    while(n_mn-- > 0){
          vsip_length n = n_mj;
          while(n-- >0){
             if(*ap < min){
                  (*rp0)++;
             } else if (*ap >= max){
                  (*rp_end)++;
             } else {
                  str = (vsip_stride)((scale * (double)(*ap - min))/iscale);
                  (*(rp + str))++;
             }
            ap += ast_mj;
          }
          ap0 += ast_mn;
          ap = ap0;
    }
  }
}
