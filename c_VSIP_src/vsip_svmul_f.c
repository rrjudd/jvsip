/* Created RJudd December 30, 1997 */
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
/* $Id: vsip_svmul_f.c,v 2.0 2003/02/22 15:19:04 judd Exp $ */
/* Modified RJudd January 2, 1999 */
/* to add rstride */
/* Removed Tisdale error checking Sept 00 */

#include"vsip.h"
#include"vsip_vviewattributes_f.h"

void (vsip_svmul_f)(
  vsip_scalar_f alpha,
  const vsip_vview_f *b,
  const vsip_vview_f *r) {
  { 
    /* register */ vsip_length n = r->length;
    /* register */ vsip_stride bst = b->stride * b->block->rstride,
                               rst = r->stride * r->block->rstride;
    vsip_scalar_f *bp = (b->block->array) + b->offset * b->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
    while(n-- > 0){
        *rp = alpha * *bp;
        bp += bst; rp += rst;
     }
  }
}
