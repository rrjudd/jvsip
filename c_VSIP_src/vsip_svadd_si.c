/* Created RJudd September 13, 1997*/
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
/* $Id: vsip_svadd_si.c,v 2.1 2006/10/20 16:21:59 judd Exp $ */
/* Modified RJudd March 20, 1998 */
/* to vsip_vadd_si.c */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_si.h>

void (vsip_svadd_si)(
  vsip_scalar_si alpha,
  const vsip_vview_si *b,
  const vsip_vview_si *r) {
  { 
    /* register */ vsip_length n = r->length;
    /* register */ vsip_stride bst =  b->stride,
                               rst = r->stride;
    vsip_scalar_si *bp = (b->block->array) + b->offset,
                   *rp = (r->block->array) + r->offset;
     while(n-- > 0){
        *rp = alpha + *bp;
        bp += bst; rp += rst;
    }
  }
}
