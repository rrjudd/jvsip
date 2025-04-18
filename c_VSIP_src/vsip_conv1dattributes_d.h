/* Created RJudd March 19, 1999 */
/* SPAWARSYSCEN D881 */

#ifndef _vsip_conv1dattributes_d
#define _vsip_conv1dattributes_d 1
#include"VI.h"

struct vsip_conv1dattributes_d{
     vsip_cvview_d  *H;
     vsip_cvview_d  *x;
     vsip_cmview_d  *Xm;
     vsip_fft_d     *fft;
     vsip_fftm_d    *fftm;
     vsip_scalar_vi  method; /* 0 = vector, 1 = matrix */
     vsip_symmetry   symm;
     int             D; /* decimation */
     vsip_length nh; /* length of h */
     vsip_length nx; /* length of input */
     vsip_length Nsection; /* length of section */
     vsip_length Noutput;  /* total length of output vector */
     vsip_length Ndata;
     vsip_length Ndataf;
     vsip_length NumSection;
     int ntimes;           /* ignored */
     vsip_support_region support;
     vsip_alg_hint hint;   /* ignored */
};

#endif /* _vsip_conv1dattributes_d */
