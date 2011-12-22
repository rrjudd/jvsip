/* Created RJudd September 25, 1997 */
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
/* $Id: vsip_cvsqrt_f.c,v 2.0 2003/02/22 15:18:52 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_cvsqrt_f)(
  const vsip_cvview_f *a,
  const vsip_cvview_f *r) {	/* r_j = sqrt(a_j)		*/
  {
      vsip_length    n = r->length;
      vsip_stride cast = a->block->cstride;
      vsip_stride crst = r->block->cstride;
      vsip_scalar_f *apr = (vsip_scalar_f *)((a->block->R->array) + cast * a->offset),
                    *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_f *api = (vsip_scalar_f *)((a->block->I->array) + cast * a->offset),
                    *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
      vsip_stride    ast = (cast * a->stride),
                     rst = (crst * r->stride);
      while(n-- > 0)
      {  /* the following is a modified version of vsip_csqrt_f */
         if (0.0 == *api) {
             if(*apr < 0.0) {
               *rpi = (vsip_scalar_f)sqrt(-*apr);
               *rpr = 0.0;
             } else {
               *rpr = (vsip_scalar_f)sqrt(*apr);
               *rpi = (vsip_scalar_f)0.0;
             }
         } else {
            if (0.0 == *apr) {
               if(*api > 0.0) {
                  *rpi = (vsip_scalar_f)sqrt(0.5 * *api);
                  *rpr = *rpi;
               } else {
                  *rpi = (vsip_scalar_f)sqrt(0.5 * -*api);
                  *rpr = - *rpi; }
             } else {
                vsip_scalar_f mag = (vsip_scalar_f)sqrt(0.5 * 
                     ((vsip_scalar_f)sqrt(*apr * *apr + *api * *api) 
                     + ((*apr > 0) ? *apr : -*apr)));
                vsip_scalar_f s   = *api/(vsip_scalar_f)( 2.0 * mag);
                if(*apr < 0.0) {
                   if(*api < 0.0) {
                      *rpr = -s; *rpi = - mag;
                   } else {
                      *rpr = s; *rpi = mag;
                   }
               } else {
                   *rpr = mag; *rpi = s;
               }
             }
           }
           apr += ast; api += ast; 
           rpr += rst; rpi += rst;
      }
  }
}
