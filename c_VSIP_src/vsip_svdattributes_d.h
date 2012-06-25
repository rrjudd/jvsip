/*
 *  vsip_svdattributes_d.h
 *  Created by Randall Judd on 9/5/08.
 *
 */
/*********************************************************************
 // This code includes                                                 /
 // no warranty, express or implied, including the warranties          /
 // of merchantability and fitness for a particular purpose.           /
 // No person or entity                                                /
 // assumes any legal liability or responsibility for the accuracy,    /
 // completeness, or usefulness of any information, apparatus,         /
 // product, or process disclosed, or represents that its use would    /
 // not infringe privately owned rights                                /
 **********************************************************************/

#ifndef _vsip_svd_d_h  
#define _vsip_svd_d_h 1 

#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_mviewattributes_d.h>

struct vsip_svdattributes_d{
   vsip_svd_uv optU;
   vsip_svd_uv optV;
   vsip_length M;   /* size of U */
   vsip_length N;   /* size of V */
   vsip_length L;   /* diagonal length */
   /* Aval will hold the attributes of the input matrix */
   vsip_mview_d Aval; /* matrix view object */
   vsip_mview_d *A;   /* pointer to Aval */
   vsip_scalar_d *U; /* M by M */
   vsip_mview_d *mU;
   vsip_scalar_d *V; /* N by N */
   vsip_mview_d *mV;
   vsip_vview_d *buf; /* working space of size max(M,N) */
   vsip_vview_vi *vi; /* working space of size max(M,N) */
   vsip_vview_vi *ui; /* working space of size max(M,N) */
   vsip_scalar_d *v; /* used by householder */
   vsip_scalar_d *w; /* used by householder */
   vsip_scalar_d *betaR; /* beta for upper part */
   vsip_scalar_d *betaL; /* beta for lower part */
   vsip_scalar_d *d; /* diagonal of Bidiagonal */
   vsip_vview_d *vd;
   vsip_scalar_d *f; /* supper diagonal of Bidiagnal */
   vsip_scalar_d *c_l;
   vsip_scalar_d *s_l;
   vsip_scalar_d *c_r;
   vsip_scalar_d *s_r;
   
};

#endif /*_vsip_svd_d_h */
