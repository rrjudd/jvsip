/* Created RJudd December 14, 1997 */
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
/* $Id: vsip_vmeansqval_f.c,v 2.0 2003/02/22 15:19:15 judd Exp $ */
/* Modified RJudd January 2, 1999 */
/* to add rstride */
/* Removed Tisdale error checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_f.h>

vsip_scalar_f (vsip_vmeansqval_f)(
  const vsip_vview_f* a) {
  { 
     /*define variables*/
      /* register */ vsip_length n = a->length;
      /* register */ vsip_stride ast = a->stride * a->block->rstride;
      vsip_scalar_f *ap = (a->block->array) + a->offset * a->block->rstride;
      vsip_scalar_f t = 0;
      /* do sum */
       while(n-- > 0){
          t  += (*ap * *ap);
          ap += ast;
      }
      /* return average */
      return t/a->length;
   }
}
