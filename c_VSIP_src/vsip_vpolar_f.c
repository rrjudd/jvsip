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
/* $Id: vsip_vpolar_f.c,v 2.0 2003/02/22 15:19:17 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Modified RJudd January 3, 1998 */
/* to incorporate rstride */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_vpolar_f)(
  const vsip_cvview_f* a,
  const vsip_vview_f* r,
  const vsip_vview_f* t) {
  {
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  rrst = r->block->rstride,
                  trst = t->block->rstride;
      vsip_scalar_f *apr = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset),
                    *rp  = (vsip_scalar_f*) ((r->block->array) + rrst * r->offset),
                    *tp  = (vsip_scalar_f*) ((t->block->array) + trst * t->offset);
      vsip_scalar_f *api =  (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset);
      vsip_scalar_f  tmp;
      /* register */ vsip_stride ast = (cast * a->stride),
                                 rst = rrst * r->stride,
                                 tst = trst * t->stride;
      while(n-- > 0){
          tmp = (vsip_scalar_f)atan2(*api,*apr);
          *rp = (vsip_scalar_f)sqrt(*apr * *apr + *api * *api);
          *tp = tmp;
          apr += ast; api += ast;
          rp += rst; tp += tst;
      }
  }
}
