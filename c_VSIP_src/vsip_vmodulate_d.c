/* Created RJudd January 5, 1998 */
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
/* $Id: vsip_vmodulate_d.c,v 2.1 2003/04/22 02:19:59 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Modified RJudd January 3, 1999 */
/* to incorporate rstride */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include"vsip_scalars.h"

vsip_scalar_d (vsip_vmodulate_d)(
  const vsip_vview_d* a,
  vsip_scalar_d nu,
  vsip_scalar_d phi,
  const vsip_cvview_d* r) {
  { 
      /* register */ vsip_length n = r->length;
      vsip_stride crst = r->block->cstride,
                  rast = a->block->rstride;
      vsip_scalar_d *ap  = (vsip_scalar_d*) ((a->block->array) + rast * a->offset),
                    *rpr = (vsip_scalar_d*) ((r->block->R->array) + crst * r->offset);
      vsip_scalar_d *rpi = (vsip_scalar_d*) ((r->block->I->array) + crst * r->offset);
      vsip_scalar_d  arg = phi;
      /* register */ vsip_stride ast = rast * a->stride,
                                 rst = (crst * r->stride);
      while(n-- > 0){
	*rpr = *ap * VSIP_COS_D(arg);
        *rpi = *ap * VSIP_SIN_D(arg);
        arg += nu;
        ap += ast;
        rpr += rst; rpi += rst;
      }
      return arg;
  }
}
