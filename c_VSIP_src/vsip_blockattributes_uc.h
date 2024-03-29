#ifndef _vsip_blockattributes_uc_h
#define _vsip_blockattributes_uc_h 1
/* Modified RJudd Jan 98 and later   */
/* To Remove Tisdales Error Checking */
/* vsip_blockattributes_uc.h
// 
// This file contains the PRIVATE vsip_blockattributes_uc definition.
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
// Feb. 28, 1997   Added copyright notice.
// Mar. 31, 1997   Modified to conform with VSIP decoder ring.   */

#include"vsip.h"
#include"VI.h"

struct vsip_blockattributes_uc {
  vsip_scalar_uc*  array;       /* external data array            */
  int              kind;        /* 0 ==> private, 1 ==> public    */
  int              admit;       /* 0 ==> No,      1 ==> Yes       */
  vsip_length      size;        /* block size in elements         */
  int              bindings;    /* reference counter              */
  int              markings;    /* valid|destoyed block object    */
  vsip_memory_hint hint;       /* not used in this implementation */
  vsip_scalar_bl update;          /* a place to store update flag */
  };
#endif /* _vsip_blockattributes_uc_h */

