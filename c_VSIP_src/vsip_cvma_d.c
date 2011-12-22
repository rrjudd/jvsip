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
/* $Id: vsip_cvma_d.c,v 2.1 2007/04/16 18:34:00 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>

void (vsip_cvma_d)(
  const vsip_cvview_d* a,
  const vsip_cvview_d* b,
  const vsip_cvview_d* c,
  const vsip_cvview_d* r) {
  { 
      vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  cbst = b->block->cstride,
                  ccst = c->block->cstride,
                  crst = r->block->cstride;
      vsip_scalar_d *apr = (vsip_scalar_d *)((a->block->R->array) + cast * a->offset),
                    *bpr = (vsip_scalar_d *)((b->block->R->array) + cbst * b->offset),
                    *cpr = (vsip_scalar_d *)((c->block->R->array) + ccst * c->offset),
                    *rpr = (vsip_scalar_d *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_d *api = (vsip_scalar_d *)((a->block->I->array) + cast * a->offset),
                    *bpi = (vsip_scalar_d *)((b->block->I->array) + cbst * b->offset),
                    *cpi = (vsip_scalar_d *)((c->block->I->array) + ccst * c->offset),
                    *rpi = (vsip_scalar_d *)((r->block->I->array) + crst * r->offset);
      register vsip_scalar_d temp;
      vsip_stride ast = (cast * a->stride),
                  bst = (cbst * b->stride),
                  cst = (ccst * c->stride),
                  rst = (crst * r->stride);
      while(n-- > 0){
        temp = *apr * *bpr - *api * *bpi + *cpr;
        *rpi = *apr * *bpi + *api * *bpr + *cpi;
        *rpr = temp;
        apr += ast; api += ast; 
        bpr += bst; bpi += bst;
        cpr += cst; cpi += cst;
        rpr += rst; rpi += rst;
      }     
  }
}

