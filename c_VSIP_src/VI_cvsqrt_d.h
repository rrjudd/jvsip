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
/* $Id: VI_cvsqrt_d.h,v 2.0 2003/02/22 15:18:31 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#ifndef VI_CVSQRT_D_H
#define VI_CVSQRT_D_H

static
void 
VI_cvsqrt_d(
  const vsip_cvview_d *a,
  const vsip_cvview_d *r) {	/* r_j = sqrt(a_j)		*/
  {
      vsip_length    n = r->length;
      vsip_stride cast = a->block->cstride;
      vsip_stride crst = r->block->cstride;
      vsip_scalar_d *apr = (vsip_scalar_d *)((a->block->R->array) + cast * a->offset),
                    *rpr = (vsip_scalar_d *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_d *api = (vsip_scalar_d *)((a->block->I->array) + cast * a->offset),
                    *rpi = (vsip_scalar_d *)((r->block->I->array) + crst * r->offset);
      vsip_stride    ast = (cast * a->stride),
                     rst = (crst * r->stride);
      while(n-- > 0)
      {  /* the following is a modified version of vsip_csqrt_d */
         if (0.0 == *api) {
             if(*apr < 0.0) {
               *rpi = (vsip_scalar_d)sqrt(-*apr);
               *rpr = 0.0;
             } else {
               *rpr = (vsip_scalar_d)sqrt(*apr);
               *rpi = (vsip_scalar_d)0.0;
             }
         } else {
            if (0.0 == *apr) {
               if(*api > 0.0) {
                  *rpi = (vsip_scalar_d)sqrt(0.5 * *api);
                  *rpr = *rpi;
               } else {
                  *rpi = (vsip_scalar_d)sqrt(0.5 * -*api);
                  *rpr = - *rpi; }
             } else {
                vsip_scalar_d mag = (vsip_scalar_d)sqrt(0.5 * 
                     ((vsip_scalar_d)sqrt(*apr * *apr + *api * *api) 
                     + ((*apr > 0) ? *apr : -*apr)));
                vsip_scalar_d s   = *api/(vsip_scalar_d)( 2.0 * mag);
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
#endif
