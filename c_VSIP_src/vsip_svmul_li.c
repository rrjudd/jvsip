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
/* $Id: vsip_svmul_li.c,v 2.1 2007/04/16 18:39:38 judd Exp $ */
/* Modified RJudd January 3, 1998 */
/* to vsip_svmul_li.c */
/* Removed Tisdale error checking Sept 00 */

#include"vsip.h"
#include"vsip_vviewattributes_li.h"

void (vsip_svmul_li)(
  vsip_scalar_li a,
  const vsip_vview_li *b,
  const vsip_vview_li *r) {
  { 
     register vsip_scalar_li alpha = a;
     vsip_length n   = r->length;
     vsip_stride bst = b->stride,
                 rst = r->stride;
    vsip_scalar_li *bp = (b->block->array) + b->offset,
                  *rp = (r->block->array) + r->offset;
    while(n-- > 0){
       *rp = alpha * *bp;
       bp += bst; rp += rst;
    }
  }
}
