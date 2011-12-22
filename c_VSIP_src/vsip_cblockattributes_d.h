#ifndef _vsip_cblockattributes_d_h
#define _vsip_cblockattributes_d_h 1
/* Modified RJudd June 20, 1998  and later */
/* SPAWARSYSCEN D881                       */
/* to vsip_cblockattributes_f.h            */
/* Modified RJudd July 10, 1998            */
/* change to cblock                        */ 
/* vsip_cblockattributes_f.h               */
/* Modified RJudd February 14, 1999        */
/* to _d from _f for core                  */
/* To Remove Tisdales Error Checking       */
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
// Feb. 28, 1997    Added copyright notice.
// Mar. 31, 1997    Modified to conform with VSIP decoder ring.    */

#include<vsip.h>
#include<VI.h>
#include<vsip_blockattributes_d.h>

struct vsip_cblockattributes_d {
  vsip_block_d *R,
               *I;            /* blocks holding data array                */
  int           kind;         /* 0 ==> private, 1 ==> public              */
  int           admit;        /* 0 ==> No,      1 ==> Yes                 */
  int           cstride;      /* 1 for split, 2 for interleaved           */
  size_t        size;         /* block size in elements                   */
  int           bindings;     /* reference counter                        */
  int           markings;     /* valid|destoyed block object              */
  vsip_memory_hint hint;       /* not used in this implementation */
  #if defined(VSIP_ALWAYS_INTERLEAVED) 
     vsip_scalar_d *data;  /* created data                              */
     vsip_scalar_d *Rp;    /* pointer to user data; real or interleaved */
     vsip_scalar_d *Ip;    /* pointer to split imaginary user data      */
  #elif defined(VSIP_ALWAYS_SPLIT)
     vsip_scalar_d *r_data;  /* created data                              */
     vsip_scalar_d *i_data;  /* created data                              */
     vsip_scalar_d *Rp;      /* pointer to user data; real or interleaved */
     vsip_scalar_d *Ip;      /* pointer to split imaginary user data      */
  #endif
  vsip_cscalar_d a_scalar;
  vsip_cscalar_d a_zero;
  vsip_cscalar_d a_one;
  vsip_cscalar_d a_imag_one;
  vsip_scalar_bl update;          /* a place to store update flag */
  };
#endif /* _vsip_cblockattributes_d_h */

