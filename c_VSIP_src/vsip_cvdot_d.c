/* Created RJudd December 29, 1997 */
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
/* $Id: vsip_cvdot_d.c,v 2.0 2003/02/22 15:18:50 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_d.h>

vsip_cscalar_d (vsip_cvdot_d)(
  const vsip_cvview_d* a,
  const vsip_cvview_d* b) {
  {
      /* register */ vsip_length n = a->length;
      vsip_stride cast = a->block->cstride;
      vsip_stride cbst = b->block->cstride;
      vsip_scalar_d *apr = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset),
                    *bpr = (vsip_scalar_d*) ((b->block->R->array) + cbst * b->offset);
      vsip_scalar_d *api = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset),
                    *bpi = (vsip_scalar_d*) ((b->block->I->array) + cbst * b->offset);
      /* register */ vsip_stride ast = (cast * a->stride),
                                 bst = (cbst * b->stride);
    vsip_cscalar_d r;
    r.r = 0; r.i = 0;
    while(n-- > 0){
        r.r += (*apr * *bpr - *api * *bpi);
        r.i += (*api * *bpr + *apr * *bpi);
        apr += ast; bpr += bst;
        api += ast; bpi += bst;
    }
    return r;
  }
}
