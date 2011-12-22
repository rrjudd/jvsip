/* Created RJudd                    */
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
/* $Id: vsip_mbind_uc.c,v 2.0 2003/02/22 15:18:54 judd Exp $ */

#include<vsip.h>
#include<vsip_mviewattributes_uc.h>

vsip_mview_uc* (vsip_mbind_uc)(
  const vsip_block_uc* block, 
  vsip_offset offset,
  vsip_stride col_stride, 
  vsip_length col_length, 
  vsip_stride row_stride, 
  vsip_length row_length) {
  {
    vsip_mview_uc* mview_uc = (vsip_mview_uc*)malloc(sizeof(vsip_mview_uc));
    if(mview_uc != NULL){
       mview_uc->block = (vsip_block_uc*)block;
       mview_uc->offset = offset;
       mview_uc->col_stride = col_stride;
       mview_uc->row_stride = row_stride;
       mview_uc->col_length = col_length;
       mview_uc->row_length = row_length;
       mview_uc->markings = VSIP_VALID_STRUCTURE_OBJECT;
    }
    return mview_uc;
    }
  }

