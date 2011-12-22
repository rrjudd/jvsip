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
/* $Id: vsip_vcopy_i_i.c,v 2.0 2003/02/22 15:19:11 judd Exp $ */
/* to include attributes support */
/* Modified RJudd January 1, 1999 */
/* to vsip_vcopy_i_i.c */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_i.h>

void (vsip_vcopy_i_i)(
  const vsip_vview_i* a,
  const vsip_vview_i* r) {
  {
      /* register */ vsip_length n   = r->length;
      /* register */ vsip_stride ast = a->stride,
                                 rst = r->stride;
      vsip_scalar_i *ap = (a->block->array) + a->offset,
                    *rp = (r->block->array) + r->offset;
      /*end define*/
      while(n-- > 0){
         *rp = *ap;
         ap += ast; rp += rst;
      }
   }
}
