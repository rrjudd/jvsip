/* Created RJudd */
/* SPAWARSYSCEN D881 */
#ifndef _vsip_fftattributes_f_h
#define _vsip_fftattributes_f_h 1
#include<VI.h>
#include"VI_ffttype.h"

struct vsip_fftattributes_f{
     vsip_cvview_f *wt;
     vsip_cvview_f *temp;
     vsip_vview_bl *bit;
     vsip_scalar_vi *index;
     vsip_scalar_vi *pn;  
     vsip_scalar_vi *p0;
     vsip_scalar_vi *pF;
     vsip_cvview_f *x;
     vsip_scalar_f *x_r, *x_i;
     vsip_scalar_f *xp_r, *xp_i;
     vsip_stride    xst;
     vsip_stride    xpst;
     vsip_scalar_f  scale;
     vsip_length    N;
     vsip_length    length; /* number of stages */
     vsip_fft_dir   d; /*direction + or- 1 */
     vsip_ffttype   type;
     int            dft; /*no suitable factors, just a DFT option */
     unsigned int ntimes;
     vsip_alg_hint hint;
     vsip_scalar_vi stage; 
     /* a pointer for encapsulating external fft */
     void *ext_fft_obj;
};
#endif /* _vsip_fftattributes_f_h */
