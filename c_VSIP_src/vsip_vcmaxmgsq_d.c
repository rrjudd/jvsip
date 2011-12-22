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
/* $Id: vsip_vcmaxmgsq_d.c,v 2.0 2003/02/22 15:19:11 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Modified RJudd January 3, 1998 */
/* to incorporate rstride */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>

void (vsip_vcmaxmgsq_d)(
  const vsip_cvview_d* a,
  const vsip_cvview_d* b,
  const vsip_vview_d* r) {
{
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  cbst = b->block->cstride,
                  rrst = r->block->rstride;
      vsip_scalar_d *apr = (vsip_scalar_d *)((a->block->R->array) + cast * a->offset),
                    *bpr = (vsip_scalar_d *)((b->block->R->array) + cbst * b->offset),
                    *rp  = (vsip_scalar_d *)((r->block->array) +    rrst * r->offset);
      vsip_scalar_d *api = (vsip_scalar_d *)((a->block->I->array) + cast * a->offset),
                    *bpi = (vsip_scalar_d *)((b->block->I->array) + cbst * b->offset);
      vsip_scalar_d  magasq=0, magbsq=0;
      /* register */ vsip_stride ast = (cast * a->stride),
                                 bst = (cbst * b->stride),
                                 rst = rrst * r->stride;
      while(n-- > 0){
        magasq = *apr * *apr + *api * *api;
        magbsq = *bpr * *bpr + *bpi * *bpi;
        *rp = (magasq > magbsq) ? magasq : magbsq;
        apr += ast; api += ast;
        bpr += bst; bpi += bst;  
        rp  += rst;
      }  
   }   
}

