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
/* $Id: vsip_vmag_d.c,v 2.0 2003/02/22 15:19:15 judd Exp $ */
/* Modified RJudd January 2, 1999 */
/* to add rstride */
/* Removed Tisdale error checking Sept 00 */

#include"vsip.h"
#include"vsip_vviewattributes_d.h"

void (vsip_vmag_d)(
  const vsip_vview_d* a,
  const vsip_vview_d* r) {
  {
    /* register */ vsip_length n = r->length;
    /* register */ vsip_stride ast = a->stride * a->block->rstride,
                               rst = r->stride * r->block->rstride;
    vsip_scalar_d *ap = (vsip_scalar_d*) ((a->block->array) + a->offset * a->block->rstride);
    vsip_scalar_d *rp = (vsip_scalar_d*) ((r->block->array) + r->offset * r->block->rstride);
    while(n-- > 0){
       *rp = (*ap < 0) ? -(*ap) : *ap;
       ap += ast; rp += rst;
    }
  }
}

