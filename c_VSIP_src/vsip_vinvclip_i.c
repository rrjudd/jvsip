/* Created RJudd January 1, 1998 */
/* SPAWARSYSCEN */
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
/* $Id: vsip_vinvclip_i.c,v 2.0 2003/02/22 15:19:14 judd Exp $ */
/* Modified RJudd March 1, 1998 */
/* to vsip_vinvclip_d.c */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_i.h>

void (vsip_vinvclip_i)(
  const vsip_vview_i* a,
  vsip_scalar_i t1,
  vsip_scalar_i t2,
  vsip_scalar_i t3,
  vsip_scalar_i c1,
  vsip_scalar_i c2,
  const vsip_vview_i* r) {
   {
     vsip_length   n = r->length;
     vsip_stride ast = a->stride,
                 rst = r->stride;
      vsip_scalar_i *ap = (a->block->array) + a->offset,
                    *rp = (r->block->array) + r->offset;
      while(n-- > 0){
         *rp  = (*ap < t1) ? *ap : ((*ap < t2) ? c1 : ((*ap <= t3) ? c2 : *ap));
          ap += ast; rp += rst;
      }
   }
}
