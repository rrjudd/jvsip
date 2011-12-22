/* Created RJudd July 27, 1998 */
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
/* $Id: vsip_vcopy_f_vi.c,v 2.0 2003/02/22 15:19:11 judd Exp $ */
/* to include attributes information */
/* Modified RJudd September 2, 2001 */
/* to copy f to vi */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_vviewattributes_vi.h>

void (vsip_vcopy_f_vi)(
  const vsip_vview_f* a,
  const vsip_vview_vi* r) {
  { 
      /* register */ vsip_length n   = r->length;
      /* register */ vsip_stride ast = a->stride * a->block->rstride,
                                 rst = r->stride;
      vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride;
      vsip_scalar_vi *rp = (r->block->array) + r->offset;
      /*end define*/
      while(n-- > 0){
         *rp = (vsip_scalar_vi) *ap;
         ap += ast; rp += rst;
      }
   }
}
