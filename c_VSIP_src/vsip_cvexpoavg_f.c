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
/* $Id: vsip_cvexpoavg_f.c,v 2.0 2003/02/22 15:18:50 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_cvexpoavg_f)(
  vsip_scalar_f alpha,
  const vsip_cvview_f* b,
  const vsip_cvview_f* c) {
  { 
      /* register */ vsip_length n = c->length;
      vsip_stride cbst = b->block->cstride,
                  ccst = c->block->cstride;
      vsip_scalar_f *bpr = (vsip_scalar_f*) ((b->block->R->array) + cbst * b->offset),
                    *cpr = (vsip_scalar_f*) ((c->block->R->array) + ccst * c->offset);
      vsip_scalar_f *bpi = (vsip_scalar_f*) ((b->block->I->array) + cbst * b->offset),
                    *cpi = (vsip_scalar_f*) ((c->block->I->array) + ccst * c->offset);
      /* register */ vsip_stride bst = (cbst * b->stride),
                                 cst = (ccst * c->stride);

    while(n-- > 0){
       *cpr = alpha * *bpr + (1 - alpha) * *cpr;
       *cpi = alpha * *bpi + (1 - alpha) * *cpi;
        bpr += bst; bpi += bst;
        cpr += cst; cpi += cst;
    }
  }
}
