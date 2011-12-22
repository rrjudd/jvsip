/* Created RJudd September 19, 2000 */
/* SPAWARSYSCEN D857                */
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
/* $Id: vsip_tbind_f.c,v 2.0 2003/02/22 15:19:05 judd Exp $ */

#define VI_TVIEW_F_
#include"VI_support_priv_f.h"

vsip_tview_f *vsip_tbind_f(
     const vsip_block_f *block,
     vsip_offset offset,
     vsip_stride z_stride,
     vsip_length z_length,
     vsip_stride y_stride,
     vsip_length y_length,
     vsip_stride x_stride,
     vsip_length x_length)
{
   vsip_tview_f *tview = VI_tview_f();
   if(tview != NULL){
      tview->block = (vsip_block_f*) block;
      tview->offset = offset;
      tview->z_length = z_length;
      tview->y_length = y_length;
      tview->x_length = x_length;
      tview->z_stride = z_stride;
      tview->y_stride = y_stride;
      tview->x_stride = x_stride;
      tview->markings = VSIP_VALID_STRUCTURE_OBJECT;
   }
   return tview;
}
     

