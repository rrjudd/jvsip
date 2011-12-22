/* Created RJudd April 24, 2003 */
/* SPAWARSYSCEN */
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
/* $Id: vsip_vhisto_i.c,v 2.1 2003/07/04 14:12:33 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_i.h>
#include"VI_vfill_i.h"

void (vsip_vhisto_i)(
  const vsip_vview_i* a,
  vsip_scalar_i min,
  vsip_scalar_i max,
  vsip_hist_opt opt,
  const vsip_vview_i* r) { /* histogram	*/
  {
    vsip_stride		str = 0;
    vsip_length		n = a->length;
    vsip_length		p = r->length;
    double              p_s = (double)(p - 2);
    vsip_stride ast = a->stride,
                rst = r->stride;
    double	scale = (double)rst * p_s;
    double      iscale = (double)(max-min);
    vsip_scalar_i *ap = (a->block->array) + a->offset,
                  *rp = (r->block->array) + r->offset;
    vsip_scalar_i *rp0 = rp, 
                  *rp_end = rp + p - 1 ;
    rp++;
    if(opt == VSIP_HIST_RESET) VI_vfill_i((vsip_scalar_i)0, r);
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
