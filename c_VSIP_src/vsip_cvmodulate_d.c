/* Created RJudd For Core January 7, 1998 */
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
/* $Id: vsip_cvmodulate_d.c,v 2.1 2003/04/22 02:19:57 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Tisdale error checking Sept 00 */

#include<math.h>
#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#include"vsip_scalars.h"

vsip_scalar_d (vsip_cvmodulate_d)(
  const vsip_cvview_d* a,
  vsip_scalar_d nu,
  vsip_scalar_d phi,
  const vsip_cvview_d* r) {
  { 
     /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  crst = r->block->cstride;
      vsip_scalar_d *apr = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset),
                    *rpr = (vsip_scalar_d*) ((r->block->R->array) + crst * r->offset);
      vsip_scalar_d *api = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset),
                    *rpi = (vsip_scalar_d*) ((r->block->I->array) + crst * r->offset);
      vsip_scalar_d  arg = phi;
      /* register */ vsip_stride ast = (cast * a->stride),
                                 rst = (crst * r->stride);
      while(n-- > 0){
	*rpr = *apr * VSIP_COS_D(arg) - *api * VSIP_SIN_D(arg);
        *rpi = *apr * VSIP_SIN_D(arg) + *api * VSIP_COS_D(arg);
        arg += nu;
        apr += ast; api += ast;
        rpr += rst; rpi += rst;
      }
      return arg;
  }
}
