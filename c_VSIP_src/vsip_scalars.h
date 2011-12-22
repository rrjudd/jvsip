/* Created RJudd  */
/* SPAWARSYSCEN   */
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
/* $Id: vsip_scalars.h,v 2.3 2006/10/20 16:25:38 judd Exp $ */

/* The purpose of this file is to provide an abstraction
 * layer for the math library used internal to vsipl funtions.
 * The default is the defined math library for ANSI C89, but
 * by changing the names of the underylying functions supporting the
 * macros in this file then a differnt math libary may be used even
 * if the function names are not the same as ANSI. This is primarily 
 * to support both float and double precision functions. By default
 * only double is supported native to the math library.
 */

#ifndef __VSIP_SCALARS_H
#define __VSIP_SCALARS_H

#define VSIP_SINH_F(x) ((vsip_scalar_f) sinh(x))
#define VSIP_SINH_D(x) ((vsip_scalar_d) sinh(x))
#define VSIP_SIN_F(x) ((vsip_scalar_f) sin(x))
#define VSIP_SIN_D(x) ((vsip_scalar_d) sin(x))
#define VSIP_ASIN_F(x) ((vsip_scalar_f) asin(x))
#define VSIP_ASIN_D(x) ((vsip_scalar_d) asin(x))
#define VSIP_COSH_F(x) ((vsip_scalar_f) cosh(x))
#define VSIP_COSH_D(x) ((vsip_scalar_d) cosh(x))
#define VSIP_COS_F(x) ((vsip_scalar_f) cos(x))
#define VSIP_COS_D(x) ((vsip_scalar_d) cos(x))
#define VSIP_ACOS_F(x) ((vsip_scalar_f) acos(x))
#define VSIP_ACOS_D(x) ((vsip_scalar_d) acos(x))
#define VSIP_EXP10_F(x)  ((vsip_scalar_f) pow(10.0 , (x)))
#define VSIP_EXP10_D(x)  ((vsip_scalar_d) pow(10.0 , (x)))
#define VSIP_EXP_F(x)  ((vsip_scalar_f) exp(x))
#define VSIP_EXP_D(x)  ((vsip_scalar_d) exp(x))
#define VSIP_FLOOR_F(x) ((vsip_scalar_f) floor(x))
#define VSIP_FLOOR_D(x) ((vsip_scalar_d) floor(x))

#endif
