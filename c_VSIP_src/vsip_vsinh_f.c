/* Created RJudd January 29, 2000 */
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
/* $Id: vsip_vsinh_f.c,v 2.2 2005/12/21 00:03:46 judd Exp $ */
#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include"vsip_scalars.h"

void (vsip_vsinh_f)(
  const vsip_vview_f *a,
  const vsip_vview_f *r) {
  { 
      /*define variables*/
      /* register */ vsip_length n = r->length;
      /* register */ vsip_stride ast = a->stride * a->block->rstride,
                                 rst = r->stride * r->block->rstride;
      vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
                    *rp = (r->block->array) + r->offset * r->block->rstride;
      /*end define*/
      if(a == r){ /* in place */
         while(n-- >0){
           *rp = VSIP_SINH_F(*rp);
             rp += rst;
         }
      } else { /* not in place */
         while(n-- >0){
           *rp = VSIP_SINH_D(*ap);
            ap += ast; rp += rst;
         }
      }
   }
}
