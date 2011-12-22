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
/* $Id: vsip_cvexpoavg_d.c,v 2.0 2003/02/22 15:18:50 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>

void (vsip_cvexpoavg_d)(
  vsip_scalar_d alpha,
  const vsip_cvview_d* b,
  const vsip_cvview_d* c) {
  { 
      /* register */ vsip_length n = c->length;
      vsip_stride cbst = b->block->cstride,
                  ccst = c->block->cstride;
      vsip_scalar_d *bpr = (vsip_scalar_d*) ((b->block->R->array) + cbst * b->offset),
                    *cpr = (vsip_scalar_d*) ((c->block->R->array) + ccst * c->offset);
      vsip_scalar_d *bpi = (vsip_scalar_d*) ((b->block->I->array) + cbst * b->offset),
                    *cpi = (vsip_scalar_d*) ((c->block->I->array) + ccst * c->offset);
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
