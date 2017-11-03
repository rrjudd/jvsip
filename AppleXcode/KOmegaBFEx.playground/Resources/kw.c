#include"kw.h"

void kw_zero(kw_obj *kw){
   vsip_mfill_f(0.0,kw->m_gram);
}

void komega( kw_obj* kw, vsip_mview_f *m_data){
    /* Data tapers for time and space */
    vsip_vmmul_f(kw->ts_taper,m_data,VSIP_ROW,m_data);
    vsip_vmmul_f(kw->array_taper,m_data,VSIP_COL,m_data);

    /* FFT for time and space */
    vsip_rcfftmop_f(kw->rcfftm,m_data,kw->cm_freq);
    vsip_ccfftmip_f(kw->ccfftm,kw->cm_freq);

    /* power estimate */
    /* to save memory place estimate in real part of spectral matrix */
    vsip_mcmagsq_f(kw->cm_freq,kw->rm_freq);

    /* scaling for average */
    vsip_smmul_f(1.0/(float)kw->Navg,kw->rm_freq,kw->rm_freq);
    /* add in new values to gram estimate */
    vsip_madd_f(kw->rm_freq,kw->m_gram,kw->m_gram);
    return;
}

/* initialize the komega object */
int kw_init(kw_obj* kw, param_obj* param){
     int retval = 0;
     vsip_length Nsens = param->Nsens;
     vsip_length Nts   = param->Nts;
     vsip_length Nfreq;
     vsip_length L = Nsens * Nfreq;
     if(param->Nts % 2){
          printf("Data length must be even\n"); 
          retval++;
     }
     kw->Nfreq = Nts/2 + 1;
     kw->Navg = param->Navg;
     Nfreq = kw->Nfreq;
     kw->cm_freq = vsip_cmcreate_f(Nsens,Nfreq,VSIP_COL,VSIP_MEM_NONE);
     if(kw->cm_freq){
         kw->rm_freq=vsip_mrealview_f(kw->cm_freq);
         if(!kw->rm_freq) retval++;
     } else {
         retval++;
         kw->rm_freq = NULL;
     }
     kw->m_gram = vsip_mcreate_f(Nsens, Nfreq, VSIP_COL,VSIP_MEM_NONE);
     if(!kw->m_gram) retval++;
     kw->rcfftm = vsip_rcfftmop_create_f(Nsens,Nts,1,VSIP_ROW,0,0);
     if(!kw->rcfftm) retval++;
     kw->ccfftm = vsip_ccfftmip_create_f(Nsens,Nfreq,1.0,VSIP_FFT_FWD,VSIP_COL,0,0);
     if(!kw->ccfftm) retval++;
     kw->ts_taper   = vsip_vcreate_hanning_f(Nts,0);
     if(!kw->ts_taper) retval++;
     kw->array_taper = vsip_vcreate_hanning_f(Nsens,0);
     if(!kw->array_taper) retval++;
     if(retval) printf("Error in kw initialization\n");
     return retval;
}

/* finalize the komega object */
void kw_fin( kw_obj *kw){
     vsip_malldestroy_f(kw->m_gram);
     vsip_fftm_destroy_f(kw->rcfftm);
     vsip_fftm_destroy_f(kw->ccfftm);
     vsip_valldestroy_f(kw->ts_taper);
     vsip_valldestroy_f(kw->array_taper);
     vsip_mdestroy_f(kw->rm_freq);
     vsip_cmalldestroy_f(kw->cm_freq);
     return;
}

vsip_mview_f *kw_instance(kw_obj* kw){
    return kw->m_gram;
};
