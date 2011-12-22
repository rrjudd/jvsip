/* Created RJudd January 2, 1998 */
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
/* $Id: vsip_vmaxval_d.c,v 2.0 2003/02/22 15:19:15 judd Exp $ */
/* Modified RJudd January 2, 1999 */
/* to add rstride */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_d.h>

vsip_scalar_d (vsip_vmaxval_d)(
  const vsip_vview_d* a, 
  vsip_index *j) {
  { 
      /* register */ vsip_length n  = a->length,
                                  n0 ;
      /* register */ vsip_stride ast = a->stride * a->block->rstride;
      vsip_scalar_d *ap = (a->block->array) + a->offset * a->block->rstride,
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

