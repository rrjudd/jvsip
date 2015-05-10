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
/* $Id: VI_vramp_l.h,v 2.1 2003/07/04 14:12:33 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_l.h>

#ifndef VI_VRAMP_I_H
#define VI_VRAMP_I_H

static
void 
VI_vramp_l(
          vsip_scalar_l x,
          vsip_scalar_l y, 
          const vsip_vview_l* r) {
  { 
      vsip_length N = r->length,
                  i;
    
      /* register */ vsip_stride rst = r->stride * r->block->rstride;
      vsip_scalar_l *rp    = (r->block->array) + r->offset * r->block->rstride;
      *rp = x;
       for(i=1; i<N; i++){
           rp += rst;
          *rp = x + (vsip_scalar_l)i * y;
       }
   }
}
#endif
