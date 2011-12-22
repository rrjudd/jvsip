/* Created RJudd January 1, 1998 */
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
/* $Id: vsip_vminmg_f.c,v 2.0 2003/02/22 15:19:16 judd Exp $ */
/* Modified RJudd January 2, 1999 */
/* to add rstride */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>

void (vsip_vminmg_f)(
  const vsip_vview_f* a,
  const vsip_vview_f* b,
  const vsip_vview_f* r) {
    {
      /*define variables*/
      /* register */ vsip_length n = r->length;
      /* register */ vsip_stride ast = a->stride * a->block->rstride,
                         bst = b->stride * a->block->rstride,
                         rst = r->stride * a->block->rstride;
      vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
                    *bp = (b->block->array) + b->offset * b->block->rstride,
                    *rp = (r->block->array) + r->offset * r->block->rstride;
      /*end define*/
      while(n-- > 0){
           *rp = (((*ap < 0) ? (- *ap) : *ap) < ((*bp < 0) ? (- *bp) : *bp)) ? *ap : *bp;
           *rp = (*rp < 0) ? (- *rp) : *rp;
            ap += ast; bp += bst; rp += rst;
      }
    }
}
