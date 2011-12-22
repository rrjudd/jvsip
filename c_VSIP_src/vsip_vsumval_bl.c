/* Created RJudd April 16, 1999 */
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
/* $Id: vsip_vsumval_bl.c,v 2.0 2003/02/22 15:19:18 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_bl.h>

vsip_scalar_vi (vsip_vsumval_bl)(
  const vsip_vview_bl* a) {
      vsip_length   n = a->length;
      vsip_stride ast = a->stride;
      vsip_scalar_bl *ap = (a->block->array) + a->offset;
      vsip_scalar_vi t = 0;
     /* do sum */
      while(n-- > 0){
        if(*ap) t += 1;
        ap += ast;
      }
     /* return sum */
      return t;
}
