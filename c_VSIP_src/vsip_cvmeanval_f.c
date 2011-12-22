/* Created RJudd December 26, 1997 */
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
/* $Id: vsip_cvmeanval_f.c,v 2.0 2003/02/22 15:18:51 judd Exp $ */
/* Modified RJudd June 28, 1998 */
/* to add complex block support */
/* Removed Development Mode RJudd Sept 00 */

#include<vsip.h>
#include<vsip_cvviewattributes_f.h>

vsip_cscalar_f (vsip_cvmeanval_f)(
  const vsip_cvview_f* a) {/* (a_0 + a_1 + ... + a_n-1)/n	*/
  { 
    /* register */ vsip_length n = a->length;
    vsip_stride cast = a->block->cstride;
    vsip_scalar_f *apr  = (vsip_scalar_f*) ((a->block->R->array) + cast * a->offset);
    vsip_scalar_f *api  = (vsip_scalar_f*) ((a->block->I->array) + cast * a->offset);
    vsip_cscalar_f sum = vsip_cmplx_f(0,0);
    /* register */ vsip_stride ast = (cast * a->stride);
    while(n-- > 0){
       sum.r += *apr;
       sum.i += *api;
       apr += ast; api += ast;
    }
    sum.r /= a->length;
    sum.i /= a->length;
    return sum;
  }
}
