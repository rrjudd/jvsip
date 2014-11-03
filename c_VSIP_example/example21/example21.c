#include<vsip.h>
#include"exUtils.h"
/* define parameters */
#define D 1.5        /* Sensor Spacing Meters */
#define Fs 1000.0    /* Sample Frequency (Hz) */
#define F0 450.0     /* Target Frequency */
#define F1 300.0     /* Target Frequency */
#define F2 150.0     /* Target Frequency */
#define F3 50.0      /* Target Frequency */
#define Theta_o 40   /* Target Direction */
#define Ns 512       /* samples in a time series */
#define N 512        /* length of sampled time series (samples) */
#define Nn 1024      /* length of (simulated) noise series */
#define Mp 128       /* number of sensors in linear array */
#define c 1500.0     /* Propagation Speed (Meters/Second) */
/*Calculate input data*/
int main(){
    vsip_fftm_d *rcfftmop_obj = vsip_rcfftmop_create_d(Mp,Ns,1,VSIP_ROW,0,0);
    vsip_fftm_d *ccfftmip_obj = vsip_ccfftmip_create_d(Mp,Ns/2 + 1,VSIP_FFT_FWD,1,VSIP_COL,0,0);
    vsip_vview_d* windowt = vsip_vcreate_hanning_d(Ns,VSIP_MEM_NONE);
    vsip_vview_d* windowp = vsip_vcreate_hanning_d(Mp,VSIP_MEM_NONE);
    vsip_scalar_d alpha = (vsip_scalar_d)(D * Fs) / c ;/*Array Constant*/
    vsip_mview_d *data = noiseGen(alpha,Mp,Nn,Ns);
    vsip_cmview_d *gram_data = vsip_cmcreate_d(Mp,Ns/2 + 1,VSIP_COL,0);
    vsip_mview_d *gram;
    void* targets[3];
    vsip_vview_d*freq;vsip_vview_vi *bearing;vsip_vview_d *scale;
    targets[0] = (void*)vsip_vcreate_d(4,VSIP_MEM_NONE);/* freq */
    targets[1] = (void*)vsip_vcreate_vi(4,VSIP_MEM_NONE);/* bearng */
    targets[2] = (void*)vsip_vcreate_d(4,VSIP_MEM_NONE);/*scalae*/
    freq =(vsip_vview_d*)targets[0];
    bearing = (vsip_vview_vi*)targets[1];
    scale = (vsip_vview_d*)targets[2];
    vsip_vfill_vi(Theta_o,bearing);
    vsip_vput_d(scale,0,1.5);vsip_vput_d(scale,1,2.0);vsip_vput_d(scale,2,2.0);vsip_vput_d(scale,3,3.0);
    vsip_vput_d(freq,0,F0);vsip_vput_d(freq,1,F1);vsip_vput_d(freq,2,F2);vsip_vput_d(freq,3,F3);
    narrowBandGen(data,alpha,targets,Fs);
    /*beamform data and output in a form sutiable for display*/
    vsip_vmmul_d(windowt,data,VSIP_ROW,data); 
    vsip_vmmul_d(windowp,data,VSIP_COL,data) ; 
    vsip_rcfftmop_d(rcfftmop_obj,data,gram_data);
    vsip_ccfftmip_d(ccfftmip_obj,gram_data);
    gram = cmscale_d(gram_data);
    /*save data */
    mview_store_d(gram,"gram_output");
    vsip_malldestroy_d(gram);
    vsip_cmalldestroy_d(gram_data);
    vsip_malldestroy_d(data);
    vsip_valldestroy_d(windowt);
    vsip_valldestroy_d(windowp);
    vsip_fftm_destroy_d(rcfftmop_obj);
    vsip_fftm_destroy_d(ccfftmip_obj);
}
