/* Created RJudd February 16, 2000 */
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
/* $Id: vsip_cvrsdiv_f.c,v 2.0 2003/02/22 15:18:52 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_cvrsdiv_f)(
  const vsip_cvview_f *a,
  vsip_scalar_f beta,
  const vsip_cvview_f *r) {
  { 
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  crst = r->block->cstride;
      vsip_scalar_f *apr = (vsip_scalar_f *)((a->block->R->array) + cast * a->offset),
                    *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_f *api = (vsip_scalar_f *)((a->block->I->array) + cast * a->offset),
                    *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
      /* register */ vsip_stride ast = (cast * a->stride),
                                 rst = (crst * r->stride);
      /*end define*/
      if(r == a){ /* inplace */
         while(n-- > 0){
             *rpr /= beta;
             *rpi /= beta; 
             rpr += rst; rpi += rst;
         }
      } else {    /* out of place */
         while(n-- > 0){
             *rpr   = *apr / beta;
             *rpi   = *api / beta;
             apr += ast; api += ast;
             rpr += rst; rpi += rst;
         }
      }
   }
   return;
}
