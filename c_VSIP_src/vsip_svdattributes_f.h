/*
 *  vsip_svdattributes_f.h
 *  Created by Randall Judd on 9/5/08.
 *  Copyright 2008 Home. All rights reserved.
 *
 */

#ifndef _vsip_svd_f_h  
#define _vsip_svd_f_h 1 

#include<vsip.h>
#include<vsip_vviewattributes_f.h>
#include<vsip_mviewattributes_f.h>
#include<vsip_mviewattributes_f.h>

struct vsip_svdattributes_f{
   vsip_svd_uv optU;
   vsip_svd_uv optV;
   vsip_length M;   /* size of U */
   vsip_length N;   /* size of V */
   vsip_length L;   /* diagonal length */
   /* Aval will hold the attributes of the input matrix */
   vsip_mview_f Aval; /* matrix view object */
   vsip_mview_f *A;   /* pointer to Aval */
   vsip_scalar_f *U; /* M by M */
   vsip_mview_f *mU;
   vsip_scalar_f *V; /* N by N */
   vsip_mview_f *mV;
   vsip_vview_f *buf; /* working space of size max(M,N) */
   vsip_vview_vi *vi; /* working space of size max(M,N) */
   vsip_vview_vi *ui; /* working space of size max(M,N) */
   vsip_scalar_f *v; /* used by householder */
   vsip_scalar_f *w; /* used by householder */
   vsip_scalar_f *betaR; /* beta for upper part */
   vsip_scalar_f *betaL; /* beta for lower part */
   vsip_scalar_f *d; /* diagonal of Bidiagonal */
   vsip_vview_f *vd;
   vsip_scalar_f *f; /* supper diagonal of Bidiagnal */
   vsip_scalar_f *c_l;
   vsip_scalar_f *s_l;
   vsip_scalar_f *c_r;
   vsip_scalar_f *s_r;
   
};

#endif /*_vsip_svd_f_h */
