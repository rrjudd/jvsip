/* Created RJudd January 4, 1998 */
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
/* $Id: vsip_vrect_d.c,v 2.1 2003/04/21 12:55:16 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Modified January 3, 1999 */
/* to incorporate rstride */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include"vsip_scalars.h"

void (vsip_vrect_d)(
  const vsip_vview_d* r,
  const vsip_vview_d* t,
  const vsip_cvview_d* a) {
  {
      /* register */ vsip_length n = r->length;
      vsip_stride cast = a->block->cstride,
                  rrst = r->block->rstride,
                  trst = r->block->rstride;
      vsip_scalar_d *apr = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset),
                    *rp  = (vsip_scalar_d*) ((r->block->array) + rrst * r->offset),
                    *tp  = (vsip_scalar_d*) ((t->block->array) + trst * t->offset);
      vsip_scalar_d *api = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset);
      vsip_scalar_d  temp = 0;
      /* register */ vsip_stride ast = (cast * a->stride),
                                 rst = rrst * r->stride,
                                 tst = trst * t->stride;
      while(n-- > 0){
          temp = *rp * VSIP_SIN_D(*tp);
          *apr = *rp * VSIP_COS_D(*tp);
          *api = temp;
          apr += ast; api += ast; 
          rp += rst; 
          tp += tst;
      }
  }
}
