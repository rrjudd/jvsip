/* Created RJudd January 3, 1998*/
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
/* $Id: vsip_vexpoavg_d.c,v 2.0 2003/02/22 15:19:13 judd Exp $ */
/* Modified RJudd January 2, 1999 */
/* to add rstride */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>

void (vsip_vexpoavg_d)(
  vsip_scalar_d alpha,
  const vsip_vview_d* b,
  const vsip_vview_d* c) {
  { 
    /* register */ vsip_length n = c->length;
    /* register */ vsip_stride bst = b->stride * b->block->rstride,
                       cst = c->stride * c->block->rstride;
    vsip_scalar_d *bp = (b->block->array) + b->offset * b->block->rstride,
                  *cp = (c->block->array) + c->offset * c->block->rstride;
    while(n-- > 0){
       *cp = alpha * *bp + (1 - alpha) * *cp;
        cp += cst; bp += bst;
    }
  }
}
