/* Created RJudd January 3, 1998 */
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
/* $Id: vsip_vswap_si.c,v 2.0 2003/02/22 15:19:19 judd Exp $ */
/* Modified RJudd March 22, 1998 */
/* to vsip_vswap_si.c */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_si.h>

void (vsip_vswap_si)(
  const vsip_vview_si* a,
  const vsip_vview_si* b) {
    {
      /* register */ unsigned int n = (unsigned int) a->length;
      /* register */ int ast = (int) a->stride,
                         bst = (int) b->stride;
      vsip_scalar_si *ap = (a->block->array) + a->offset,
                    *bp = (b->block->array) + b->offset,
                     temp;
      while(n-- > 0){
          temp = *ap; *ap = *bp; *bp = temp;
          ap += ast; bp += bst;
      }
    }
}
