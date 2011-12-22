/* Created by RJudd September 15, 1997*/
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
/* $Id: vsip_rscvadd_f.c,v 2.0 2003/02/22 15:19:04 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_rscvadd_f)(
  vsip_scalar_f alpha,
  const vsip_cvview_f *b,
  const vsip_cvview_f *r) {
  { 
     /* register */ vsip_length n = r->length;
      vsip_stride cbst = b->block->cstride,
                  crst = r->block->cstride;
      vsip_scalar_f *bpr = (vsip_scalar_f *)((b->block->R->array) + cbst * b->offset),
                    *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_f *bpi = (vsip_scalar_f *)((b->block->I->array) + cbst * b->offset),
                    *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
      vsip_scalar_f temp;
      /* register */ vsip_stride bst = (cbst * b->stride),
                                 rst = (crst * r->stride);
      /*end define*/
      while(n-- > 0){
             temp  = alpha + *bpr;
             *rpi = *bpi;
             *rpr = temp;
             bpr += bst; bpi += bst; 
             rpr += rst; rpi += rst; 
      }
  }
}
