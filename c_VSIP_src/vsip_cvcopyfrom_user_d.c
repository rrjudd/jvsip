/* Created RJudd September 4, 2006 */
/* VSIPL Consultant */
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
/* $Id: vsip_cvcopyfrom_user_d.c,v 2.1 2007/04/18 17:15:17 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>

void (vsip_cvcopyfrom_user_d)(
  vsip_scalar_d* const r,
  vsip_scalar_d* const i,
  const vsip_cvview_d* a) {
   vsip_length n   = a->length;
   vsip_stride ast = a->stride * a->block->cstride;
   vsip_scalar_d *ap_r = (a->block->R->array) + a->offset * a->block->cstride;
   vsip_scalar_d *ap_i = (a->block->I->array) + a->offset * a->block->cstride;
   if(i == NULL){ /* user storage must be interleaved */
      vsip_scalar_d *rp = r;
      while(n-- > 0){
         *ap_r = *rp;
         rp++; ap_r += ast;
         *ap_i = *rp;
         ap_i+= ast; rp++;
      }
   } else { /* user storage must be split */
      vsip_scalar_d *rp = r;
      vsip_scalar_d *ip = i;
      while(n-- > 0){
         *ap_r = *rp;
         rp++; ap_r += ast;
         *ap_i = *ip;
         ap_i+= ast; ip++;
      }
   }
   return;
}

