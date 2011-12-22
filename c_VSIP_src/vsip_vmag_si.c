/* Created RJudd October 22, 1997 */
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
/* $Id: vsip_vmag_si.c,v 2.0 2003/02/22 15:19:15 judd Exp $ */
/* Modified RJudd January 3, 1999 */
/* to vsip_vmag_si.c */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_si.h>

void (vsip_vmag_si)(
  const vsip_vview_si* a,
  const vsip_vview_si* r) {
  {
    /* register */ vsip_length n = r->length;
    /* register */ vsip_stride ast = a->stride,
                               rst = r->stride;
    vsip_scalar_si *ap = (vsip_scalar_si*) ((a->block->array) + a->offset);
    vsip_scalar_si *rp = (vsip_scalar_si*) ((r->block->array) + r->offset);
    while(n-- > 0){
       *rp = (*ap < 0) ? -(*ap) : *ap;
       ap += ast; rp += rst;
    }
  }
}

