/* Created RJudd February 16, 2000 */
/* SPAWARSYSCEN D857 */
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
/* $Id: vsip_rcvdiv_d.c,v 2.0 2003/02/22 15:19:03 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_d.h"
#include"vsip_cvviewattributes_d.h"

void (vsip_rcvdiv_d)(
  const vsip_vview_d *a,
  const vsip_cvview_d *b,
  const vsip_cvview_d *r) {
  { 
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->rstride,
                  cbst = b->block->cstride,
                  crst = r->block->cstride;
      vsip_scalar_d *ap  = (vsip_scalar_d *)((a->block->array) + cast * a->offset),
                    *bpr = (vsip_scalar_d *)((b->block->R->array) + cbst * b->offset),
                    *rpr = (vsip_scalar_d *)((r->block->R->array) + crst * r->offset);
      vsip_scalar_d *bpi = (vsip_scalar_d *)((b->block->I->array) + cbst * b->offset),
                    *rpi = (vsip_scalar_d *)((r->block->I->array) + crst * r->offset);
      vsip_scalar_d temp,magbsq;
      /* register */ vsip_stride ast = (cast * a->stride),
                                 bst = (cbst * b->stride),
                                 rst = (crst * r->stride);
      /*end define*/
      if(r == b){ /* inplace */
         while(n-- > 0){
             magbsq = (*rpr * *rpr + *rpi * *rpi);
             temp   = (*ap * *rpr ) / magbsq;
             *rpi   = ( - *ap * *rpi) / magbsq;
             *rpr   = temp;
             ap += ast; 
             rpr += rst; rpi += rst;
         }
      } else {    /* out of place */
         while(n-- > 0){
             magbsq = (*bpr * *bpr + *bpi * *bpi);
             temp   = (*ap * *bpr ) / magbsq;
             *rpi   = ( - *ap * *bpi) / magbsq;
             *rpr   = temp;
             ap += ast; 
             bpr += bst; bpi += bst;
             rpr += rst; rpi += rst;
         }
      }
   }
   return;
}
