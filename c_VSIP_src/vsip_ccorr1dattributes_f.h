/* Created RJudd */
/* SPAWARSYSCEN D881 */
#ifndef _vsip_ccorr1dattributes_f
#define _vsip_ccorr1dattributes_f 1
#include<VI.h>

struct vsip_ccorr1dattributes_f{
     vsip_cvview_f  *h;
     vsip_cvview_f  *x;
     vsip_fft_f     *fft;
     vsip_length n;
     vsip_length m;
     vsip_length mn;
     vsip_length N;
     vsip_length lag_len;
     int ntimes;
     vsip_support_region support;
     vsip_alg_hint hint;
};

#endif /* _vsip_ccorr1dattributes_f */
