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
/* $Id: vsip_cvmag_f.c,v 2.0 2003/02/22 15:18:51 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_cvviewattributes_f.h>

void (vsip_cvmag_f)(
  const vsip_cvview_f* a,
  const vsip_vview_f* r) {
  { 
    /* register */ vsip_length n = r->length;
    vsip_scalar_f s,ss;
    vsip_stride cast = a->block->cstride;
    vsip_scalar_f *ap_r = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset),
                  *rp  = (vsip_scalar_f*) ((r->block->array) + r->offset * r->block->rstride);
    vsip_scalar_f *ap_i = (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset);
    /* register */ vsip_stride ast = (cast * a->stride),
                               rst = r->stride * r->block->rstride;
    while(n-- > 0){
       s = (vsip_scalar_f)((*ap_r > 0) ? *ap_r: -*ap_r) + ((*ap_i >0) ? *ap_i: -*ap_i);
       ss = s * s;
       if(ss == 0){
           *rp = 0;
       } else {
           *rp = s * (vsip_scalar_f)sqrt((*ap_r * *ap_r)/ss + (*ap_i * *ap_i)/ss);
       }
       ap_r += ast; ap_i += ast; rp += rst;
    }
  }
}
