#ifndef _TS_H
#define _TS_H 1
#include<vsip.h>
#include"param.h"

/*
 * fir      => FIR is a low pass filter for the noise.
 * noise    => is a vector to hold the output of the random generator.
 * bl_noise => holds the output of the bandlimited noise after the
 *             FIR filter.
 * rand     => random object holding the state of the generator.
 * t        => is a vector of times coresponding to the sensor 
 *             samples in a time series.
 * t_dt     => is a vector of times with the delay time corresponding
 *             to a propagation time given a particular noise direction
 *             added to t. t_dt = t + Dsens/c * cos(bearing);
 * m_data => the matrix holding the input data
 * v_data => a vector allocated on the same block as m_data for 
 *           use for vector views of m_data
 */

typedef struct {
   double Fs;
   double c;
   double Dsens;
   int Nsens;
   int Nsim_noise;
   int Nsim_freqs;
   int Nts;
   vsip_fir_f *fir;
   vsip_vview_f *noise;
   vsip_vview_f *bl_noise;
   vsip_randstate *rand;
   vsip_vview_f *t;
   vsip_vview_f *t_dt;
   vsip_mview_f *m_data;
   vsip_vview_f *v_data;
   double *freqs;
   double *bearings;
} ts_obj;

int  ts_init(ts_obj*, param_obj*);
void ts_fin(ts_obj*);
vsip_mview_f* ts_instance(ts_obj*);
void ts_zero(ts_obj*);
void ts_sim_nb(ts_obj*);
void ts_sim_noise(ts_obj*);

#endif /* _TS_H */
