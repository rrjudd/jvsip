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
/* $Id: vsip_cvmprod_f.c,v 2.0 2003/02/22 15:18:51 judd Exp $ */
/* April 20, 1998 1,2 to row,col         */
/* Remove Development Mode RJudd Sept 00 */

#include"vsip.h"
#include"vsip_cvviewattributes_f.h"
#include"vsip_cmviewattributes_f.h"

void (vsip_cvmprod_f)(
  const vsip_cvview_f* a,
  const vsip_cmview_f* B,
  const vsip_cvview_f* r) {
  { 
      vsip_length nx = 0, mx = 0;
      vsip_stride cast = a->block->cstride, crst = r->block->cstride, cBst = B->block->cstride;
      vsip_scalar_f  *ap_r  = (vsip_scalar_f*)(a->block->R->array + cast * a->offset),
                     *ap_i  = (vsip_scalar_f*)(a->block->I->array + cast * a->offset),
                     *rp_r  = (vsip_scalar_f*)(r->block->R->array + crst * r->offset),
                     *rp_i  = (vsip_scalar_f*)(r->block->I->array + crst * r->offset),
                     *Byp_r = (vsip_scalar_f*)(B->block->R->array + cBst * B->offset),
                     *Byp_i = (vsip_scalar_f*)(B->block->I->array + cBst * B->offset),
                     *Bxpr = Byp_r,
                     *Bxpi = Byp_i;
       vsip_stride sta = cast * a->stride, str = crst * r->stride, stB = cBst * B->col_stride;
       while(nx++ < B->row_length){
           *rp_r = 0; *rp_i = 0;
           mx = 0;
           while(mx++ < B->col_length){
               *rp_r += *ap_r * *Byp_r - *ap_i * *Byp_i;
               *rp_i += *ap_r * *Byp_i + *ap_i * *Byp_r;
               ap_r += sta; Byp_r += stB;
               ap_i += sta; Byp_i += stB;
           }
           ap_r = (vsip_scalar_f*)(a->block->R->array + cast * a->offset);
           ap_i = (vsip_scalar_f*)(a->block->I->array + cast * a->offset);
           Byp_r = (Bxpr += (cBst * B->row_stride));
           Byp_i = (Bxpi += (cBst * B->row_stride));
           rp_r += str; rp_i += str;
     }   
  }
}

