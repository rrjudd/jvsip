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
/* $Id: vsip_vhisto_si.c,v 2.3 2004/07/18 15:27:38 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_si.h>
#include"VI_vfill_si.h"

void (vsip_vhisto_si)(
  const vsip_vview_si* a,
  vsip_scalar_si min,
  vsip_scalar_si max,
  vsip_hist_opt opt,
  const vsip_vview_si* r) { /* histogram	*/
  {
    vsip_stride		str = 0;
    vsip_length		n = a->length;
    vsip_length		p = r->length;
    double              p_s = (double)(p - 2);
    vsip_stride ast = a->stride,
                rst = r->stride;
    double	scale = (double)rst * p_s;
    double      iscale = (double)(max-min);
    vsip_scalar_si *ap = (a->block->array) + a->offset,
                  *rp = (r->block->array) + r->offset;
    vsip_scalar_si *rp0 = rp, 
                  *rp_end = rp + p - 1 ;
    rp++;
    if(opt == VSIP_HIST_RESET) VI_vfill_si((vsip_scalar_si)0, r);
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
