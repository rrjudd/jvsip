/* Created RJudd                   */
/* SPAWARSYSCEN D857               */
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
/* $Id: vsip_svadd_uc.c,v 2.0 2003/02/22 15:19:04 judd Exp $ */

#include"vsip.h"
#include"vsip_vviewattributes_uc.h"

void (vsip_svadd_uc)(
  vsip_scalar_uc alpha,
  const vsip_vview_uc *b,
  const vsip_vview_uc *r) {
  { 
    /* register */ unsigned int n = (unsigned int) r->length;
    /* register */ int bst = (int) b->stride,
                       rst = (int) r->stride;
    vsip_scalar_uc *bp = (b->block->array) + b->offset,
                   *rp = (r->block->array) + r->offset;
     while(n-- > 0){
        *rp = alpha + *bp;
        bp += bst; rp += rst;
    }
  }
}
