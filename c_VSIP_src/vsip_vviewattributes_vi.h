#ifndef _vsip_vviewattributes_vi_h
#define _vsip_vviewattributes_vi_h 1
/* To remove Tisdale Error Checking */
/* vsip_vviewattributes_vi.h Version 0.000 February 28, 1997
// 
// This file contains the PRIVATE vsip_vviewattributes_vi
// definition.
//
// Copyright (c) Hughes Research Laboratories, Inc. 1997
// A non-exclusive, non-royalty bearing license is hereby granted to all
// persons to copy, modify, distribute and produce derivative works for
// any purpose, provided that this copyright notice and following disclaimer
// appear on all copies.
//
// THIS LICENSE INCLUDES NO WARRANTEES, EXPRESSED OR IMPLIED, WHETHER ORAL
// OR WRITTEN, WITH RESPECT TO THE SOFTWARE OR OTHER MATERIAL, INCLUDING
// BUT NOT LIMITED TO ANY IMPLIED WARRANTIES OF MERCHANTABILITY, OR FITNESS
// FOR A PARTICULAR PURPOSE, OR ARISING FROM A COURSE OF PERFORMANCE, OR
// DEALING, OR FROM USAGE OR TRADE, OR OF NON-INFRINGEMENT OF ANY PATENTS
// OF THIRD PARTIES.
//
// This material is based upon work supported by Ft. Huachuca/DARPA under
// Contract No.  DABT63-96-C-0060.  Any opinions, findings and conclusions
// or recommendations expressed in this material are those of the author(s)
// and do not necessarily reflect the views of Ft. Huachuca/DARPA.
//
// Author: E. Robert Tisdale
//
// Along with a reference to a vsip_block_vi object, vector view objects
// include information about the offset to the first element, the stride be-
// tween successive elements and number of elements.  The exact representation
// of this information in vector view objects is hidden from the application
// programmer but integral types vsip_offset, vsip_stride and vsip_length are
// defined so that information about the corresponding attributes can be passed
// into and returned from VSIP library functions
//
// Revision History:
// Feb. 28, 1997	Added copyright notice.
// Mar. 31, 1997	Modified to conform with VSIP decoder ring.	*/

#include<vsip.h>
#include<VI.h>
#include<vsip_blockattributes_vi.h>

struct vsip_vviewattributes_vi {
  vsip_block_vi*	block;		/* memory data block object	*/
  vsip_offset		offset;
  vsip_stride		stride;
  vsip_length		length;
  int			markings;	/* valid|destoyed vview object	*/
  };
#endif /* _vsip_vviewattributes_vi_h */
