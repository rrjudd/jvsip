/* Created RJudd */
/* SPAWARSYSCEN D881 */
#ifndef _vsip_corr1dattributes_d
#define _vsip_corr1dattributes_d 1
#include<VI.h>

struct vsip_corr1dattributes_d{
     vsip_cvview_d  *h;
     vsip_cvview_d  *x;
     vsip_fft_d     *fft;
     vsip_length n;
     vsip_length m;
     vsip_length mn;
     vsip_length N;
     vsip_length lag_len;
     int ntimes;
     vsip_support_region support;
     vsip_alg_hint hint;
};

#endif /* _vsip_corr1dattributes_d */
