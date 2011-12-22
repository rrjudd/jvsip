/* Created RJudd                   */ 
/* SPAWARSYSCEN D857               */
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
/* $Id: vsip_vramp_uc.c,v 2.1 2007/04/21 19:39:33 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_uc.h>

void (vsip_vramp_uc)(vsip_scalar_uc x,
                     vsip_scalar_uc y, 
                     const vsip_vview_uc* r) {
   vsip_length N = r->length,i;
   register vsip_scalar_uc start = x;
   register vsip_scalar_uc inc = y;
   /* register */ vsip_stride rst = r->stride;
   vsip_scalar_uc *rp    = (r->block->array) + r->offset;
   *rp = start;
   for(i=1; i<N; i++){
      rp += rst;
      *rp = start + (vsip_scalar_uc)i * inc;
   }
}
