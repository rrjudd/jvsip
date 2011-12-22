/* Created RJudd January 4, 1998 */
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
/* $Id: vsip_vcminmgsqval_f.c,v 2.0 2003/02/22 15:19:11 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Modified RJudd January 3, 1999 */
/* To incorporate rstride */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>

vsip_scalar_f (vsip_vcminmgsqval_f)(
   const vsip_cvview_f* a,
   vsip_index *j) {
  { 
      /* register */ vsip_length n  = a->length, n0 ;
      vsip_stride cast = a->block->cstride;
      vsip_scalar_f *apr = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset);
      vsip_scalar_f *api = (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset);
      vsip_scalar_f  r     = 0, magsq = 0;
      /* register */ vsip_stride ast = (cast * a->stride);
      n0 = n - 1;
      r = *apr * *apr + *api * *api;
      if(j != NULL) *j = (vsip_index) 0;
      while(n-- > 0){
         magsq = *apr * *apr + *api * *api;
         if(r > magsq){
              r = magsq;
              if(j != NULL) *j = (vsip_index) ( n0 - n);
         }
         apr += ast; api += ast;
      }
      return r;
  }
}
