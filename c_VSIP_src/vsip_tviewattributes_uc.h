/* Created RJudd */
/* SPAWARSYSCEN D857 */
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
/* $Id: vsip_tviewattributes_uc.h,v 2.0 2003/02/22 15:48:16 judd Exp $ */

#ifndef _vsip_tviewattributes_uc_h
#define _vsip_tviewattributes_uc_h 1

#include<vsip.h>
#include<VI.h>
#include<vsip_blockattributes_uc.h>

struct vsip_tviewattributes_uc {
  vsip_block_uc*      block;      /* memory data block object        */
  vsip_offset        offset;
  vsip_stride        x_stride;
  vsip_stride        y_stride;
  vsip_stride        z_stride;
  vsip_length        x_length;
  vsip_length        y_length;
  vsip_length        z_length;
  int                markings;   /* valid|destoyed tview object        */
  };

#endif /* _vsip_tviewattributes_uc_h */
