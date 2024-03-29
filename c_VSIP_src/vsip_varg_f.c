/* Created RJudd February 5, 2000 */
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
/* $Id: vsip_varg_f.c,v 2.0 2003/02/22 15:19:09 judd Exp $ */
#include"vsip.h"
#include"vsip_vviewattributes_f.h"
#include"vsip_cvviewattributes_f.h"

void (vsip_varg_f)(
  const vsip_cvview_f* a,
  const vsip_vview_f* r) {
  {
      /* register */ vsip_length n = r->length;
      vsip_scalar_f *ap_r = (vsip_scalar_f *)((a->block->R->array) + a->offset * a->block->cstride),
                    *ap_i = (vsip_scalar_f *)((a->block->I->array) + a->offset * a->block->cstride),
                    *rp_r = (vsip_scalar_f *)((r->block->array) + r->offset * r->block->rstride);
      vsip_stride ast = a->stride * a->block->cstride,
                  rst = r->stride * r->block->rstride;
      /*end define*/
      while(n-- > 0){
          *rp_r = (vsip_scalar_f)atan2(*ap_i,*ap_r);
          rp_r += rst;
          ap_r += ast; ap_i += ast;
      }
   }
   return;
}

