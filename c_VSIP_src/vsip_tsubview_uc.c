/* Created RJudd  */
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
/* $Id: vsip_tsubview_uc.c,v 2.0 2003/02/22 15:19:08 judd Exp $ */
#define VI_TVIEW_UC_
#include"VI_support_priv_uc.h"

vsip_tview_uc *vsip_tsubview_uc(
        const vsip_tview_uc *v,
        vsip_index z_index,
        vsip_index y_index,
        vsip_index x_index,
        vsip_length P,
        vsip_length M,
        vsip_length N)
{
      vsip_tview_uc *tsubview = VI_tview_uc();
      *tsubview = *v;
      tsubview->offset += z_index * v->z_stride +
                          y_index * v->y_stride +
                          x_index * v->x_stride;
      tsubview->z_length = P;
      tsubview->y_length = M;
      tsubview->x_length = N;
      return tsubview;
}
