/* Created RJudd January 4, 1998 */
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
/* $Id: vsip_cvfill_f.c,v 2.0 2003/02/22 15:18:50 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_cvfill_f)(vsip_cscalar_f alpha,
  const vsip_cvview_f* r) {	/* r_j = alpha		*/
  {
      /* register */ vsip_length n = r->length;
      vsip_stride crst = r->block->cstride;
      vsip_scalar_f *rpr = (vsip_scalar_f*) ((r->block->R->array) + crst * r->offset);
      vsip_scalar_f *rpi = (vsip_scalar_f*) ((r->block->I->array) + crst * r->offset);
      /* register */ vsip_stride rst = (crst * r->stride);
      while(n-- > 0){
          *rpr = alpha.r;
          *rpi = alpha.i;
          rpr += rst; rpi += rst;
      }
  }
}

