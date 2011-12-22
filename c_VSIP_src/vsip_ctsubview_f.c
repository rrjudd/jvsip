/* Created RJudd October 3, 2000 */
/* SPAWARSYSCEN D857             */
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
/* $Id: vsip_ctsubview_f.c,v 2.0 2003/02/22 15:18:49 judd Exp $ */

#define VI_CTVIEW_F_
#include"VI_support_cpriv_f.h"

vsip_ctview_f *vsip_ctsubview_f(
        const vsip_ctview_f *v,
        vsip_index z_index,
        vsip_index y_index,
        vsip_index x_index,
        vsip_length P,
        vsip_length M,
        vsip_length N)
{
      vsip_ctview_f *ctsubview = VI_ctview_f();
      *ctsubview = *v;
      ctsubview->offset += z_index * v->z_stride +
                           y_index * v->y_stride +
                           x_index * v->x_stride;
      ctsubview->z_length = P;
      ctsubview->y_length = M;
      ctsubview->x_length = N;
      return ctsubview;
}
