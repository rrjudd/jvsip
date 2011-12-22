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
/* $Id: vsip_cvexp_f.c,v 2.1 2003/04/22 02:19:57 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Development Mode RJudd Sept 00 */

#include<math.h>
#include<vsip.h>
#include<vsip_cvviewattributes_f.h>
#include"vsip_scalars.h"

void (vsip_cvexp_f)(
  const vsip_cvview_f *a,
  const vsip_cvview_f *r) {
  {
      vsip_length n = r->length;
      vsip_stride cast = a->block->cstride;
      vsip_stride crst = r->block->cstride;
      vsip_scalar_f *apr = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset),
                    *rpr = (vsip_scalar_f*) ((r->block->R->array) + crst * r->offset);
      vsip_scalar_f *api = (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset),
                    *rpi = (vsip_scalar_f*) ((r->block->I->array) + crst * r->offset);
      vsip_stride    ast = (cast * a->stride),
                     rst = (crst * r->stride);
      vsip_scalar_f mag  = 0;
      while(n-- > 0){
          mag  = VSIP_EXP_F(*apr);
          *rpr = mag * VSIP_COS_F(*api);
          *rpi = mag * VSIP_SIN_F(*api);
          apr += ast; api += ast; 
          rpr += rst; rpi += rst;
      }

    }
}
