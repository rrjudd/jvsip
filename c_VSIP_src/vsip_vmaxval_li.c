/* Created RJudd */
/* SPAWARSYSCEN  */
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
/* $Id: vsip_vmaxval_li.c,v 2.1 2004/04/03 16:03:09 judd Exp $ */

#include<vsip.h>
#include<vsip_vviewattributes_li.h>

vsip_scalar_li (vsip_vmaxval_li)(
   const vsip_vview_li* a, 
   vsip_index *j) {
  { 
      /* register */ vsip_length n  = a->length,
                                  n0 ;
      /* register */ vsip_stride ast = a->stride;
      vsip_scalar_li *ap = (a->block->array) + a->offset, 
                      r;
      n0 = n - 1;
      r  = *ap;
      if(j != NULL) *j = (vsip_index) 0;
      while(n-- > 0){
         if( r < *ap){
            r = *ap;
            if(j != NULL) *j = (vsip_index) ( n0 - n);
         }
         ap += ast;
      }
      return r;
  }
}
