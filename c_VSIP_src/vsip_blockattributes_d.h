#ifndef _vsip_blockattributes_d_h
#define _vsip_blockattributes_d_h 1
/* Modified RJudd October 11, 1998 and later*/
/* SPAWARSYSCEN D881                        */
/* for real block stride                    */
/* Modified RJudd February 14, 1999         */
/* to _d from _f for core                   */
/* To remove Tisdale Error Checking         */
/* to add parent pointer Sept 17, 2000      */
/* $Id: vsip_blockattributes_d.h,v 2.1 2006/06/09 01:40:21 judd Exp $ */
/* vsip_blockattributes_d.h
// 
// This file contains the PRIVATE vsip_blockattributes_d definition.
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
// Revision History:
// Feb. 28, 1997      Added copyright notice.
// Mar. 31, 1997      Modified to conform with VSIP decoder ring.      */

#include<vsip.h>
#include<VI.h>

struct vsip_blockattributes_d {
  vsip_cblock_d*   parent;        /* if derived point to parent else null                   */
  vsip_scalar_d*   array;         /* external data array                                    */
  int              kind;          /* 0 ==> private, 1 ==> public, 2==> derived              */
  int              admit;         /* 0 ==> No,      1 ==> Yes                               */
  vsip_stride      rstride;       /* real block stride; stride = view_stride * block_stride */
  size_t           size;          /* block size in elements                                 */
  int              bindings;      /* reference counter                                      */
  int              markings;      /* valid|destoyed block object                            */
  vsip_memory_hint hint;          /* Not used in this implementation                        */
  vsip_scalar_bl update;          /* a place to store update flag */
  };
#endif /* _vsip_blockattributes_d_h */
