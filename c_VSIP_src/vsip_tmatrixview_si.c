/* Created RJudd  October 7, 2000 */
/* SPAWARSYSCEN D857              */
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
/* $Id: vsip_tmatrixview_si.c,v 2.0 2003/02/22 15:19:07 judd Exp $ */

#include"VI_support_priv_si.h"

vsip_mview_si *vsip_tmatrixview_si(
     const vsip_tview_si *v,
     vsip_tmslice slice,
     vsip_index index)
{
      vsip_mview_si *mview = (vsip_mview_si*)NULL;
      vsip_block_si *block = v->block;
      vsip_offset off = v->offset;
      if(slice == VSIP_TMYX){
          off += index * v->z_stride;
          mview = vsip_mbind_si(block,off,
                         v->y_stride,v->y_length,
                         v->x_stride,v->x_length);
      } else if(slice == VSIP_TMZX){
          off += index * v->y_stride;
          mview = vsip_mbind_si(block,off,
                         v->z_stride,v->z_length,
                         v->x_stride,v->x_length);
      } else if(slice == VSIP_TMZY){
          off += index * v->x_stride;
          mview = vsip_mbind_si(block,off,
                         v->z_stride,v->z_length,
                         v->y_stride,v->y_length);
      }
      return mview;
}
