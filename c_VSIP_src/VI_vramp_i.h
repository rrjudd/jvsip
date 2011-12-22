/* Created RJudd April 24, 2003*/ 
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
/* $Id: VI_vramp_i.h,v 2.1 2003/07/04 14:12:33 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_i.h>

#ifndef VI_VRAMP_I_H
#define VI_VRAMP_I_H

static
void 
VI_vramp_i(
          vsip_scalar_i x,
          vsip_scalar_i y, 
          const vsip_vview_i* r) {
  { 
      vsip_length N = r->length,
                  i;
    
      /* register */ vsip_stride rst = r->stride * r->block->rstride;
      vsip_scalar_i *rp    = (r->block->array) + r->offset * r->block->rstride;
      *rp = x;
       for(i=1; i<N; i++){
           rp += rst;
          *rp = x + (vsip_scalar_i)i * y;
       }
   }
}
#endif
