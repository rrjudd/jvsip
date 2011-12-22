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
/* $Id: vsip_ctbind_d.c,v 2.0 2003/02/22 15:18:48 judd Exp $ */

#define VI_CTVIEW_D_
#include"VI_support_cpriv_d.h"

vsip_ctview_d *vsip_ctbind_d(
     const vsip_cblock_d *block,
     vsip_offset offset,
     vsip_stride z_stride,
     vsip_length z_length,
     vsip_stride y_stride,
     vsip_length y_length,
     vsip_stride x_stride,
     vsip_length x_length)
{
   vsip_ctview_d *ctview = VI_ctview_d();
   if(ctview != NULL){
      ctview->block = (vsip_cblock_d*) block;
      ctview->offset = offset;
      ctview->z_length = z_length;
      ctview->y_length = y_length;
      ctview->x_length = x_length;
      ctview->z_stride = z_stride;
      ctview->y_stride = y_stride;
      ctview->x_stride = x_stride;
      ctview->markings = VSIP_VALID_STRUCTURE_OBJECT;
   }
   return ctview;
}
     

