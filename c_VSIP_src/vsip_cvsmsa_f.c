/* Created RJudd December 31, 1997 */
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
/* $Id: vsip_cvsmsa_f.c,v 2.1 2006/06/08 22:19:26 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_cvsmsa_f)(
  const vsip_cvview_f* a,
  vsip_cscalar_f beta,
  vsip_cscalar_f my_gamma,
  const vsip_cvview_f* r) {
  { 
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  crst = r->block->cstride;
      vsip_scalar_f *apr = (vsip_scalar_f *)((a->block->R->array) + cast * a->offset),
                    *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_f *api = (vsip_scalar_f *)((a->block->I->array) + cast * a->offset),
                    *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
      vsip_scalar_f  temp;
      /* register */ vsip_stride ast = (cast * a->stride),
                                 rst = (crst * r->stride);
      while(n-- > 0){
        temp = *apr * beta.r - *api * beta.i + my_gamma.r;
        *rpi = *apr * beta.i + *api * beta.r + my_gamma.i;
        *rpr = temp;
        apr += ast; api += ast;
        rpr += rst; rpi += rst;
      }     
  }
}
