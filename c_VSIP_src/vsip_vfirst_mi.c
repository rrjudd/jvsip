/* Created RJudd March 5, 2002 */
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
/* $Id: vsip_vfirst_mi.c,v 2.1 2007/01/30 20:24:04 judd Exp $ */


#include<vsip.h>
#include<vsip_vviewattributes_mi.h>
#include<vsip_vviewattributes_bl.h>

vsip_index (vsip_vfirst_mi)(
  vsip_index j,
  vsip_bool (*f)(vsip_scalar_mi,vsip_scalar_mi),
  const vsip_vview_mi* a,
  const vsip_vview_mi* b) {
    {
      /*define variables*/
      /* register */ unsigned int n = (unsigned int) a->length;
      /* register */ int ast = (int) a->stride * 2,
                         bst = (int) b->stride * 2;
      vsip_scalar_vi  *ap = (a->block->array) + a->offset * 2,
                      *bp = (b->block->array) + b->offset * 2;
      vsip_scalar_mi mi_a,mi_b;
      
      /*end define*/
      
      if(j >= n) return j;
      n -= j;
      ap += j * ast;
      bp += j * bst;

      while(n-- > 0){
           mi_a.r = *ap; mi_a.c = *(ap+1);
           mi_b.r = *bp; mi_b.c = *(bp+1);
           if(f(mi_a,mi_b)) return (vsip_index)(a->length - n -1);
            ap += ast; bp += bst;
      }
      return (vsip_index)a->length;
    }
}
