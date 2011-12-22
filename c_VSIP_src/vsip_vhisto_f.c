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
/* $Id: vsip_vhisto_f.c,v 2.0 2003/02/22 15:19:14 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include"VI_vfill_f.h"

void (vsip_vhisto_f)(
  const vsip_vview_f* a,
  vsip_scalar_f min,
  vsip_scalar_f max,
  vsip_hist_opt opt,
  const vsip_vview_f* r) { /* histogram	*/
  {
    vsip_stride		str = 0;
    vsip_length		n = a->length;
    vsip_length		p = r->length;
    double              p_s = (double)(p - 2);
    vsip_stride ast = a->stride * a->block->rstride,
                rst = r->stride * r->block->rstride;
    double	scale = (double)rst * p_s;
    double      iscale = (double)(max-min);
    vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
    vsip_scalar_f *rp0 = rp, 
                  *rp_end = rp + p - 1 ;
    rp++;
    if(opt == VSIP_HIST_RESET) VI_vfill_f((vsip_scalar_f)0, r);
    while(n-- > 0){
       if(*ap < min){
            (*rp0)++;
       } else if (*ap >= max){
            (*rp_end)++;
       } else {
            str = (vsip_stride)((scale * (double)(*ap - min))/iscale);
            (*(rp + str))++;
       }
       ap += ast;
    }
  }
}
