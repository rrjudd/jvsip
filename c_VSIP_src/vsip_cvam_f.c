/* Created RJudd December 30, 1997 */
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
/* $Id: vsip_cvam_f.c,v 2.0 2003/02/22 15:18:49 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Development Mode RJudd Sept 00 */

#include"vsip.h"
#include"vsip_cvviewattributes_f.h"

void (vsip_cvam_f)(
  const vsip_cvview_f* a,
  const vsip_cvview_f* b,
  const vsip_cvview_f* c,
  const vsip_cvview_f* r) {/* r_j = (a_j + b_j)*c_j	*/
  { 
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  cbst = b->block->cstride,
                  ccst = c->block->cstride,
                  crst = r->block->cstride;
      vsip_scalar_f *apr = (vsip_scalar_f *)((a->block->R->array) + cast * a->offset),
                    *bpr = (vsip_scalar_f *)((b->block->R->array) + cbst * b->offset),
                    *cpr = (vsip_scalar_f *)((c->block->R->array) + ccst * c->offset),
                    *rpr = (vsip_scalar_f *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_f *api = (vsip_scalar_f *)((a->block->I->array) + cast * a->offset),
                    *bpi = (vsip_scalar_f *)((b->block->I->array) + cbst * b->offset),
                    *cpi = (vsip_scalar_f *)((c->block->I->array) + ccst * c->offset),
                    *rpi = (vsip_scalar_f *)((r->block->I->array) + crst * r->offset);
      vsip_scalar_f temp;
      /* register */ vsip_stride ast = (cast * a->stride),
                                 bst = (cbst * b->stride),
                                 cst = (ccst * c->stride),
                                 rst = (crst * r->stride);
      while(n-- > 0){
        temp = (*apr + *bpr) * *cpr - (*api + *bpi) * *cpi;
        *rpi = (*apr + *bpr) * *cpi + (*api + *bpi) * *cpr;
        *rpr = temp;
        apr += ast; api += ast;
        bpr += bst; bpi += bst;
        cpr += cst; cpi += cst;
        rpr += rst; rpi += rst;
        
      }  
  }
}

