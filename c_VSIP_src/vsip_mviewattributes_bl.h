/* Created RJudd January 15, 2000 */
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
/* $Id: vsip_mviewattributes_bl.h,v 2.0 2003/02/22 15:48:15 judd Exp $ */
#ifndef _vsip_mviewattributes_bl_h
#define _vsip_mviewattributes_bl_h 1
#include<vsip.h>
#include<VI.h>
#include<vsip_blockattributes_bl.h>

struct vsip_mviewattributes_bl {
  vsip_block_bl*	block;
  vsip_offset		offset;
  vsip_stride		row_stride;
  vsip_length		row_length;
  vsip_stride		col_stride;
  vsip_length		col_length;
  int			markings; /* to indicate  valid object */
  };
#endif /* _vsip_mviewattributes_bl_h */
