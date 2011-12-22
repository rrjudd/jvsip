/* Created RJudd April 26, 2000 */
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
/* $Id: vsip_cvcopy_d_f.c,v 2.0 2003/02/22 15:18:50 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_cvcopy_d_f)(
  const vsip_cvview_d* a,
  const vsip_cvview_f* r) {
  {
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  crst = r->block->cstride;
      vsip_scalar_d *apr = (vsip_scalar_d *)((a->block->R->array) + cast * a->offset);
      vsip_scalar_f *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_d *api = (vsip_scalar_d *)((a->block->I->array) + cast * a->offset);
      vsip_scalar_f *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
      /* register */ vsip_stride ast = (cast * a->stride),
                                 rst = (crst * r->stride);
      while(n-- > 0){
          *rpr = (vsip_scalar_f)*apr;
          *rpi = (vsip_scalar_f)*api;
          apr += ast; api += ast;
          rpr += rst; rpi += rst;
      }  
  }
}  

