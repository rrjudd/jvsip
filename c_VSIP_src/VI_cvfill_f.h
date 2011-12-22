/* Created RJudd August 8, 2002 */
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
/* $Id: VI_cvfill_f.h,v 2.0 2003/02/22 15:18:31 judd Exp $ */
#ifndef VI_CVFILL_F_H
#define VI_CVFILL_F_H 1

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>

static
void 
VI_cvfill_f(
          vsip_cscalar_f alpha,
          const vsip_cvview_f* r) 
{
   vsip_length n = r->length;
   vsip_stride crst = r->block->cstride;
   vsip_scalar_f *rpr = (vsip_scalar_f*) ((r->block->R->array) + crst * r->offset);
   vsip_scalar_f *rpi = (vsip_scalar_f*) ((r->block->I->array) + crst * r->offset);
   vsip_stride rst = (crst * r->stride);
   while(n-- > 0){
      *rpr = alpha.r;
      *rpi = alpha.i;
      rpr += rst; rpi += rst;
   }
   return;
} 
#endif /* VI_CVFILL_F_H */
