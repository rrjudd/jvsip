/* Created RJudd January 8, 1998 */
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
/* $Id: vsip_vnot_bl.c,v 2.0 2003/02/22 15:19:16 judd Exp $ */
/* Remove Tisdale Error Checking Sept 00 */

#include<vsip.h>
#include<vsip_vviewattributes_bl.h>

void (vsip_vnot_bl)(
  const vsip_vview_bl *a,
  const vsip_vview_bl *r) {	/* v_j = !u_j		*/
  { 
     /* register */ vsip_length n = r->length;
     /* regsiter */ vsip_stride ast =  a->stride,
                                rst =  r->stride;
      vsip_scalar_bl *ap = (a->block->array) + a->offset,
                     *rp = (r->block->array) + r->offset;
      while(n-- > 0){
          *rp = !(*ap);
          ap += ast; rp += rst;
      }
  }
}
