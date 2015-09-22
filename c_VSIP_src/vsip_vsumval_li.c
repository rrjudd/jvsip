/* Created RJudd December 14, 1997 */
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
/* $Id: vsip_vsumval_li.c,v 2.0 2003/02/22 15:19:19 judd Exp $ */
/* Modified RJudd March 20, 1998 */
/* to vsip_vsumval_li.c */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_li.h>

vsip_scalar_li (vsip_vsumval_li)(
  const vsip_vview_li* a) {
  { 
     /*define variables*/
      vsip_length   n = a->length;
      vsip_stride ast = a->stride;
      vsip_scalar_li *ap = (a->block->array) + a->offset;
      vsip_scalar_li t = 0;
     /* do sum */
      while(n-- > 0){
         t  += *ap;
         ap += ast;
      }
     /* return sum */
      return t;
   }
}
