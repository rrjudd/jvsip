/* Created RJudd August 30, 2006 */
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
/* $Id: vsip_cvcopyto_user_f.c,v 2.1 2006/10/20 16:26:36 judd Exp $ */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_cvcopyto_user_f)(
  const vsip_cvview_f* a,
  vsip_scalar_f* const r,
  vsip_scalar_f* const i) {
   vsip_length n   = a->length;
   vsip_stride ast = a->stride * a->block->cstride;
   vsip_scalar_f *ap_r = (a->block->R->array) + a->offset * a->block->cstride;
   vsip_scalar_f *ap_i = (a->block->I->array) + a->offset * a->block->cstride;
   if(i == NULL){ /* user storage must be interleaved */
      vsip_scalar_f *rp = r;
      while(n-- > 0){
         *rp = *ap_r;
         rp++; ap_r += ast;
         *rp = *ap_i;
         ap_i+= ast; rp++;
      }
   } else { /* user storage must be split */
      vsip_scalar_f *rp = r;
      vsip_scalar_f *ip = i;
      while(n-- > 0){
         *rp = *ap_r;
         rp++; ap_r += ast;
         *ip = *ap_i;
         ap_i+= ast; ip++;
      }
   }
   return;
}

