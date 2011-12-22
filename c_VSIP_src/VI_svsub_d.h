/* Created RJudd December 27, 1997 */
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
/* $Id: VI_svsub_d.h,v 2.0 2003/02/22 15:18:33 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#ifndef VI_SVSUB_D_H
#define VI_SVSUB_D_H

static
void 
VI_svsub_d(
          vsip_scalar_d alpha,
          const vsip_vview_d *b,
          const vsip_vview_d *r) {
  { 
    /* register */ vsip_length n = r->length;
    /* register */ vsip_stride bst = b->stride * b->block->rstride,
                               rst = r->stride * r->block->rstride;
    vsip_scalar_d *bp = (b->block->array) + b->offset * b->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
    while(n-- > 0){
        *rp = alpha - *bp;
        bp += bst; rp += rst;
    }
  }
}
#endif
