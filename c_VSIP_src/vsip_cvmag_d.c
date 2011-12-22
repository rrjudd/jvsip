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
/* $Id: vsip_cvmag_d.c,v 2.0 2003/02/22 15:18:51 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Tisdale error checking Sept 00 */

#include<math.h>
#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>

void (vsip_cvmag_d)(
  const vsip_cvview_d* a,
  const vsip_vview_d* r) {
  { 
    /* register */ vsip_length n = r->length;
    vsip_scalar_d s,ss;
    vsip_stride cast = a->block->cstride;
    vsip_scalar_d *ap_r = (vsip_scalar_d*) ((a->block->R->array) + cast * a->offset),
                  *rp  = (vsip_scalar_d*) ((r->block->array) + r->offset * r->block->rstride);
    vsip_scalar_d *ap_i = (vsip_scalar_d*) ((a->block->I->array) + cast * a->offset);
    /* register */ vsip_stride ast = (cast * a->stride),
                               rst = r->stride * r->block->rstride;
    while(n-- > 0){
       s = (vsip_scalar_d)(((*ap_r > 0) ? *ap_r: -*ap_r) + ((*ap_i >0) ? *ap_i: -*ap_i));
       ss = s * s;
       if(ss == 0){
           *rp = 0;
       } else {
           *rp = s * (vsip_scalar_d)sqrt((*ap_r * *ap_r)/ss + (*ap_i * *ap_i)/ss);
       }
       ap_r += ast; ap_i += ast; rp += rst;
    }
  }
}
