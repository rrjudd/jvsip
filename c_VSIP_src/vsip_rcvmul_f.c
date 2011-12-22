/* Created RJudd December 12, 1997 */
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
/* $Id: vsip_rcvmul_f.c,v 2.0 2003/02/22 15:19:03 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_rcvmul_f)(
  const vsip_vview_f* a,
  const vsip_cvview_f* b,
  const vsip_cvview_f* r) {
  {
      /* register */ vsip_length n = r->length;
      vsip_stride cbst = b->block->cstride;
      vsip_stride crst = r->block->cstride;
      vsip_scalar_f *ap  = (vsip_scalar_f *)((a->block->array) + a->offset * a->block->rstride),
                    *bpr = (vsip_scalar_f *)((b->block->R->array) + cbst * b->offset),
                    *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_f *bpi = (vsip_scalar_f *)((b->block->I->array) + cbst * b->offset),
                    *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
      vsip_scalar_f  temp = 0;
      /* register */ vsip_stride ast = a->stride * a->block->rstride,
                                 bst = (cbst * b->stride), 
                                 rst = (crst * r->stride);
      /*end define*/
      while(n-- > 0){
          temp = *ap * *bpr ;
          *rpi = *ap * *bpi;
          *rpr = temp;
          ap += ast; 
          bpr += bst; bpi += bst;
          rpr += rst; rpi += rst;
      }
   }
}

