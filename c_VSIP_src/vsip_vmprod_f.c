/* Created RJudd March 14, 1998 */
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
/* $Id: vsip_vmprod_f.c,v 2.1 2004/04/03 14:04:13 judd Exp $ */
/* April 21, 1998 1,2 to row,col */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_mviewattributes_f.h>

void (vsip_vmprod_f)(
  const vsip_vview_f* a,
  const vsip_mview_f* B,
  const vsip_vview_f* r) {
  {
     vsip_length nx = 0, mx = 0;
     vsip_scalar_f  *ap = a->block->array + a->offset * a->block->rstride,
                    *ap0 = ap,
                    *rp = r->block->array + r->offset * r->block->rstride,
                   *Byp = B->block->array + B->offset * B->block->rstride,
                   *Bxp = Byp;
     vsip_stride BCst = B->col_stride * B->block->rstride,
                 BRst = B->row_stride * B->block->rstride,
                 rst  = r->stride * r->block->rstride;
     while(nx++ < B->row_length){
         *rp = 0;
         mx = 0;
         while(mx++ < B->col_length){
             *rp += *ap * *Byp;
             ap += a->stride; Byp += BCst;
         }
         ap = ap0;
         Byp = (Bxp += BRst);
         rp += rst;
     }
  }
}

