/* Created RJudd September 15, 1997*/
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
/* $Id: vsip_csvadd_d.c,v 2.1 2007/04/16 18:31:51 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>

void (vsip_csvadd_d)(
  vsip_cscalar_d alpha,
  const vsip_cvview_d *b,
  const vsip_cvview_d *r) {
   vsip_length n = r->length;
   vsip_stride cbst = b->block->cstride,
               crst = r->block->cstride;
   vsip_scalar_d *bpr = (vsip_scalar_d *)((b->block->R->array) + cbst * b->offset),
                 *rpr = (vsip_scalar_d *)((r->block->R->array) + crst * r->offset);
   vsip_scalar_d *bpi = (vsip_scalar_d *)((b->block->I->array) + cbst * b->offset),
                 *rpi = (vsip_scalar_d *)((r->block->I->array) + crst * r->offset);
   register vsip_scalar_d tmp0,tmp1,tmp2;
   register vsip_scalar_d alpha0_r = alpha.r, alpha1_r = alpha.r, alpha2_r = alpha.r;
   register vsip_scalar_d alpha0_i = alpha.i, alpha1_i = alpha.i, alpha2_i = alpha.i ;
   vsip_stride bst = (cbst * b->stride),
               rst = (crst * r->stride);

   while(n > 2){
       tmp0  = alpha0_r + *bpr;
       *rpi =  alpha0_i + *bpi;
       *rpr = tmp0;
       bpr += bst; bpi += bst; 
       rpr += rst; rpi += rst;

       tmp1  = alpha1_r + *bpr;
       *rpi =  alpha1_i + *bpi;
       *rpr = tmp1;
       bpr += bst; bpi += bst; 
       rpr += rst; rpi += rst;

       tmp2  = alpha2_r + *bpr;
       *rpi =  alpha2_i + *bpi;
       *rpr = tmp2;
       bpr += bst; bpi += bst; 
       rpr += rst; rpi += rst;
       n -=3;
   }
   while(n-- > 0){
       tmp0  = alpha0_r + *bpr;
       *rpi =  alpha0_i + *bpi;
       *rpr = tmp0;
       bpr += bst; bpi += bst;
       rpr += rst; rpi += rst;
   }
}
