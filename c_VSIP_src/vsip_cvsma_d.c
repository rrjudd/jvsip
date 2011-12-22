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
/* $Id: vsip_cvsma_d.c,v 2.0 2003/02/22 15:18:52 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>

void (vsip_cvsma_d)(
  const vsip_cvview_d* a,
  vsip_cscalar_d beta,
  const vsip_cvview_d* c,
  const vsip_cvview_d* r) {
  { 
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  ccst = c->block->cstride,
                  crst = r->block->cstride;
      vsip_scalar_d *apr = (vsip_scalar_d *)((a->block->R->array) + cast * a->offset),
                    *cpr = (vsip_scalar_d *)((c->block->R->array) + ccst * c->offset),
                    *rpr = (vsip_scalar_d *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_d *api = (vsip_scalar_d *)((a->block->I->array) + cast * a->offset),
                    *cpi = (vsip_scalar_d *)((c->block->I->array) + ccst * c->offset),
                    *rpi = (vsip_scalar_d *)((r->block->I->array) + crst * r->offset);
      vsip_scalar_d  temp;
      /* register */ vsip_stride ast = (cast * a->stride),
                                 cst = (ccst * c->stride),
                                 rst = (crst * r->stride);
      while(n-- > 0){
        temp = *apr * beta.r - *api * beta.i + *cpr;
        *rpi = *apr * beta.i + *api * beta.r + *cpi;
        *rpr = temp;
        apr += ast; api += ast;
        cpr += cst; cpi += cst;
        rpr += rst; rpi += rst;
       
      }     
  }
}

