/* Modified RJudd September 19, 1998 */ 
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
/* $Id: vsip_csqrt_f.c,v 2.0 2003/02/22 15:18:47 judd Exp $ */
/* to float from double */
/* vsip_csqrt_f.c Version 0.000 February 28, 1997
// 
// This file contains the vsip_csqrt_f function definition.
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
// This file contains a prototype object oriented ANSI C language definition
// for the application programmer's interface
// to the VSIP (Vector Signal Image Processing) scalar library.
//
// Revision History:
// Feb. 28, 1997	Added copyright notice.
// Mar. 31, 1997	Modified to conform with VSIP decoder ring.	*/

#include<vsip.h>

vsip_cscalar_f (vsip_csqrt_f)(
  vsip_cscalar_f x) {			/* sqrt(x)	*/
  if (0.0 == vsip_imag_f(x)) {		/* pure real		*/
    if (vsip_real_f(x) < 0.0) {
      return vsip_cmplx_f((vsip_scalar_f)0,
	(vsip_scalar_f)sqrt(-(vsip_real_f(x))));
      }
    else {
      return vsip_cmplx_f((vsip_scalar_f)sqrt(vsip_real_f(x)),
	(vsip_scalar_f)0);
      }
    }
  else
  if (0.0 == vsip_real_f(x)) {		/* pure imaginary	*/
    vsip_scalar_f r = (vsip_scalar_f)sqrt((0.5 * (vsip_scalar_f)fabs(vsip_imag_f(x))));
    if (vsip_imag_f(x) < 0.0) {
      return vsip_cmplx_f(r, -(r));
      }
    else {
      return vsip_cmplx_f(r, r);
      }
    }
  else {
    vsip_scalar_f r = (vsip_scalar_f)sqrt((0.5 * (vsip_cmag_f(x) + (vsip_scalar_f)fabs(
	vsip_real_f(x)))));
    vsip_scalar_f s = (vsip_imag_f(x) / (vsip_scalar_f)(2.0 * r));
    if (vsip_real_f(x) < 0.0) {
      if (vsip_imag_f(x) < 0.0) {
	return vsip_cmplx_f(-(s), -(r));
	}
      else {
	return vsip_cmplx_f(s, r);
	}
      }
    else {
      return vsip_cmplx_f(r, s);
      }
    }
  }

