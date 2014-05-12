#include"exUtils.h"
// Parameters
#define D 1.5
#define Ntargets  4
#define Fs 1000.0
#define F0 450.0
#define F1 300.0
#define F2 150.0
#define F3 50.0
#define Theta0 40
#define Ns 512
#define Nn 1024
#define Mp 128
#define c 1500.0

int main()
{
    int init = vsip_init((void*)0);
    vsip_scalar_d alpha = (D * Fs) / c;
    vsip_mview_d *data, *gram;
    void *targets[3];
    vsip_vview_d *freq=vsip_vcreate_d(Ntargets,VSIP_MEM_NONE);
    vsip_vview_vi *bearing=vsip_vcreate_vi(Ntargets,VSIP_MEM_NONE);
    vsip_vview_d *scale=vsip_vcreate_d(Ntargets,VSIP_MEM_NONE);
    vsip_vview_d *windowt = vsip_vcreate_hanning_d(Ns,0);
    vsip_vview_d *windowp = vsip_vcreate_hanning_d(Mp,0);
    vsip_cmview_d *gram_data = vsip_cmcreate_d(Mp,Ns/2 + 1,VSIP_COL,0);
    vsip_fftm_d *rcfftmop_obj = vsip_rcfftmop_create_d(Mp,Ns,1,VSIP_ROW,0,0);/* time fft */
    vsip_fftm_d *ccfftmip_obj =vsip_ccfftmip_create_d(Mp,Ns/2 +1,VSIP_FFT_FWD,1,VSIP_COL,0,0);
    assert(init == 0);
    targets[0]= (void*)freq;targets[1]=(void*)bearing; targets[2]=(void*)scale;
    vsip_vput_d(freq,0,F0);vsip_vput_vi(bearing,0,Theta0);vsip_vput_d(scale,0,1.5);
    vsip_vput_d(freq,1,F1);vsip_vput_vi(bearing,1,Theta0);vsip_vput_d(scale,1,2.0);
    vsip_vput_d(freq,2,F2);vsip_vput_vi(bearing,2,Theta0);vsip_vput_d(scale,2,2.0);
    vsip_vput_d(freq,3,F3);vsip_vput_vi(bearing,3,Theta0);vsip_vput_d(scale,3,3.0);
    data = noiseGen(alpha,Mp,Nn,Ns);
    narrowBandGen(data, alpha, targets, Fs);
    vsip_vmmul_d(windowt,data,VSIP_ROW,data);
    vsip_vmmul_d(windowp,data,VSIP_COL,data);
    vsip_rcfftmop_d(rcfftmop_obj,data,gram_data);
    vsip_ccfftmip_d(ccfftmip_obj,gram_data);
    gram = cmscale_d(gram_data);
    mview_store_d(gram,"gram_output");
    vsip_cmalldestroy_d(gram_data);
    vsip_malldestroy_d(gram);
    vsip_malldestroy_d(data);
    vsip_valldestroy_d(freq);vsip_valldestroy_vi(bearing); vsip_valldestroy_d(scale);
    vsip_fftm_destroy_d(rcfftmop_obj);
    vsip_fftm_destroy_d(ccfftmip_obj);
    vsip_valldestroy_d(windowt);
    vsip_valldestroy_d(windowp);
    vsip_finalize((void*)0);
}

