/* Created RJudd September 13, 1997*/ 
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
/* $Id: vsip_vramp_i.c,v 2.1 2007/04/21 19:39:33 judd Exp $ */
/* Modified RJudd March 19, 1998 for vsip_vramp_i.c */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_i.h>

void (vsip_vramp_i)(
                     vsip_scalar_i x,
                     vsip_scalar_i y, 
                     const vsip_vview_i* r) {
   vsip_length N = r->length,i;
   register vsip_scalar_i start = x;
   register vsip_scalar_i inc = y;
   vsip_stride rst = r->stride;
   vsip_scalar_i *rp    = (r->block->array) + r->offset;
   *rp = start;
   for(i=1; i<N; i++){
      rp += rst;
      *rp = start + (vsip_scalar_i)i * inc;
   }
}

