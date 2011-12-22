/* Created RJudd July 11, 1998 */
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
/* $Id: vsip_vcopy_mi_mi.c,v 2.0 2003/02/22 15:19:11 judd Exp $ */
/* Modified RJudd January 1, 1998 */
/* to copy _mi to _mi */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_mi.h>

void (vsip_vcopy_mi_mi)(
  const vsip_vview_mi* a,
  const vsip_vview_mi* r) {
  {
      /* register */ vsip_length n = r->length;
      vsip_scalar_vi *apr = (vsip_scalar_vi *)((a->block->array) + 2 * a->offset),
                     *rpr = (vsip_scalar_vi *)((r->block->array) + 2 * r->offset);
      vsip_scalar_vi *apc = apr + 1,
                     *rpc = rpr + 1;
      /* register */ vsip_stride ast =  2 * a->stride,
                                 rst =  2 * r->stride;
      while(n-- > 0){
          *rpr = *apr;
          *rpc = *apc;
          apr += ast; apc += ast;
          rpr += rst; rpc += rst;
      }  
  }
}  

