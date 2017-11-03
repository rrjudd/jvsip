/* Created RJudd December 27, 1997 */
/* SPAWARSYSCEN D881 */
/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States/
// Government, the United States Navy, nor any of their employees,/
// makes any warranty, express or implied, including the warranties /
// of merchantability and fitness for a particular purpose, or  /
// assumes any legal liability or responsibility for the accuracy,/
// completeness, or usefulness of any information, apparatus,   /
// product, or process disclosed, or represents that its use would/
// not infringe privately owned rights                          /
**********************************************************************/
#include"vsip.h"
#include"vsip_vviewattributes_f.h"

void vsip_vhypot_f(
     const vsip_vview_f *a,
     const vsip_vview_f *b,
     const vsip_vview_f *r) {
   vsip_length n = r->length;
   vsip_stride ast = a->stride * a->block->rstride,
               bst = b->stride * b->block->rstride,
               rst = r->stride * r->block->rstride;
   vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
                 *bp = (b->block->array) + b->offset * b->block->rstride,
                 *rp = (r->block->array) + r->offset * r->block->rstride;
   while(n-- > 0){
      vsip_scalar_f a=fabs(*ap), b=fabs(*bp);
      if (a == 0.0)
         *rp = b;
      else if (b == 0.0)
         *rp = a;
      else if (b < a)
         *rp = a * (vsip_scalar_f)sqrt(1.0 + (b/a) * (b/a));
      else
         *rp = b * (vsip_scalar_f)sqrt(1.0 + (a/b) * (a/b));
      ap += ast; bp += bst; rp += rst; 
   }
}
