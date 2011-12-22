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
/* $Id: vsip_mbind_bl.c,v 2.0 2003/02/22 15:18:54 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_bl.h>

vsip_mview_bl* (vsip_mbind_bl)(
  const vsip_block_bl* block, 
  vsip_offset offset,
  vsip_stride col_stride, 
  vsip_length col_length, 
  vsip_stride row_stride, 
  vsip_length row_length) {
  {
    vsip_mview_bl* mview_bl = (vsip_mview_bl*)malloc(sizeof(vsip_mview_bl));
    if(mview_bl != NULL){
       mview_bl->block = (vsip_block_bl*)block;
       mview_bl->offset = offset;
       mview_bl->col_stride = col_stride;
       mview_bl->row_stride = row_stride;
       mview_bl->col_length = col_length;
       mview_bl->row_length = row_length;
       mview_bl->markings = VSIP_VALID_STRUCTURE_OBJECT;
    }
    return mview_bl;
    }
  }

