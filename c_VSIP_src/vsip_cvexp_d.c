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
/* $Id: vsip_cvexp_d.c,v 2.1 2003/04/22 02:19:57 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Tisdale error checking Sept 00 */

#include<math.h>
#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#include"vsip_scalars.h"

void (vsip_cvexp_d)(
  const vsip_cvview_d *a,
  const vsip_cvview_d *r) {
  {
      vsip_length n = r->length;
      vsip_stride cast = a->block->cstride;
      vsip_stride crst = r->block->cstride;
      vsip_scalar_d *apr = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset),
                    *rpr = (vsip_scalar_d*) ((r->block->R->array) + crst * r->offset);
      vsip_scalar_d *api = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset),
                    *rpi = (vsip_scalar_d*) ((r->block->I->array) + crst * r->offset);
      vsip_stride ast = (cast * a->stride),
                  rst = (crst * r->stride);
      vsip_scalar_d mag  = 0;
      while(n-- > 0){
          mag  = VSIP_EXP_D(*apr);
          *rpr = mag * VSIP_COS_D(*api);
          *rpi = mag * VSIP_SIN_D(*api);
          apr += ast; api += ast; 
          rpr += rst; rpi += rst;
      }

    }
}
