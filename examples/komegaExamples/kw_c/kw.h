#ifndef _KW_H
#define _KW_H 1
#include<vsip.h>
#include"param.h"
/*
 * k-omega object structure
 * Nfreq       => Number of frequencies in cm_freq;
 * cm_freq     => array to hold output of FFT's
 * rm_freq     => real view of cm_freq to hold powers.
 * data_gram   => User data array to hold output data
 * m_gram      => Matrix associated with data_gram
 * rcfftm      => FFT from time to frequency space
 * ccfftm      => FFT across array to direction space
 * ts_taper    => Time series data taper
 * array_taper => Array data taper
 */

typedef struct{
   vsip_length Nfreq;         /* Nts/2 + 1              */
   int Navg;                  /* Scale factor for number of averages */
   vsip_cmview_f *cm_freq;    /* (Nsens, Nfreq) col maj */
   vsip_mview_f *rm_freq;     /* (Nsens, Nts)   rwo maj */
   vsip_mview_f *m_gram;      /* (Nsens, Nfreq) col maj */
   vsip_fftm_f *rcfftm;       /* by row Nsens by Nts    */
   vsip_fftm_f *ccfftm;       /* by col Nsens by Nfreq  */
   vsip_vview_f *ts_taper;    /* of length Nts          */
   vsip_vview_f *array_taper; /* of length Nsens        */
} kw_obj;
int kw_init(kw_obj*, param_obj*);
void kw_fin(kw_obj*);
void komega( kw_obj*, vsip_mview_f*);
void kw_zero( kw_obj*);
vsip_mview_f *kw_instance(kw_obj*);

#endif /* _KW_H */
