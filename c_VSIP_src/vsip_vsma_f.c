/* Created RJudd 30 December 1997 */
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
/* $Id: vsip_vsma_f.c,v 2.2 2008/03/03 18:07:14 judd Exp $ */
/* Modified RJudd January 2, 1999 */
/* to add rstride */
/* Removed Tisdale error checking Sept 00 */

#include"vsip.h"
#include"vsip_vviewattributes_f.h"

void (vsip_vsma_f)(
  const vsip_vview_f* a,
  vsip_scalar_f beta,
  const vsip_vview_f* c,
  const vsip_vview_f* r) {
   /* register */ vsip_length n = r->length;
   /* register */ vsip_stride ast = a->stride * a->block->rstride,
                       cst = c->stride * c->block->rstride,
                       rst = r->stride * r->block->rstride;
   vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride,
                  *cp = (c->block->array) + c->offset * c->block->rstride,
                  *rp = (r->block->array) + r->offset * r->block->rstride;
    /* if c == r then this is a saxpy */
  if (cp == rp ){
      while(n-- > 0){
         *cp = *ap * beta + *cp;
         ap += ast;
         cp += cst;
      }
   } else {
       while(n-- > 0){
          *rp = (*ap * beta) + *cp;
           ap += ast;
           cp += cst;
           rp += rst;
       }
   }
}

