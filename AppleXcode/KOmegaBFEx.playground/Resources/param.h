/* Standard Disclaimer & Copyright Status                          */
/*
     Author: judd 
*/
#ifndef _PARAM_H
#define _PARAM_H 1
#include<strings.h> 
#include<stdlib.h>
#include<stdio.h>
typedef struct{
   double c;               /* propagation speed        */
   double Fs;              /* Sample Rate              */
   int Nts;                /* length of time series    */
   double Dsens;           /* distance between sensors */
   int   Nsens;            /* number of sensors        */
   int Navg;               /* number of instances to average in beamformer*/
   int   Nsim_freqs;       /* number of tones to simulate     */
   double *sim_freqs;      /* (array) frequencies to simulate */
   double *sim_bearings;   /* (array) bearing of each frequencys          */
   int   Nsim_noise;       /* number of noise directions to simualte */
} param_obj;

int param_read(char *, param_obj*); /* returns 1 on succsess, 0 on failure */
void param_free(param_obj*); /* free memory associated with sim_freqs and sim_bearings */
void param_log(param_obj*);   /* print out parameter list */

#endif /* _PARAM_H */
