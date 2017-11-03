/* Created RJudd November 21, 2012 */
/* See copyright (MIT License) included with distribution */
/*********************************************************************
 // This code includes                                                 /
 // no warranty, express or implied, including the warranties          /
 // of merchantability and fitness for a particular purpose.           /
 // No person or entity                                                /
 // assumes any legal liability or responsibility for the accuracy,    /
 // completeness, or usefulness of any information, apparatus,         /
 // product, or process disclosed, or represents that its use would    /
 // not infringe privately owned rights                                /
 **********************************************************************/

#include"vsip.h"
#include"vsip_vviewattributes_vi.h"

vsip_scalar_vi (vsip_vmaxval_vi)(
   const vsip_vview_vi* a, 
   vsip_index *j) {
  { 
      /* register */ vsip_length n  = a->length,
                                  n0 ;
      /* register */ vsip_stride ast = a->stride;
      vsip_scalar_vi *ap = (a->block->array) + a->offset, 
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
