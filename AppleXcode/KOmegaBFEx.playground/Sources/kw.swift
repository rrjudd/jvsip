import Foundation
import vsip
func oddNumber(_ n: Int) -> Bool {
    return (n % 2) == 1
}
public class KW {
    public let Nfreq: Int                /* Nts/2 + 1              */
    public let Navg:Int                  /* Scale factor for number of averages */
    public var cm_freq: OpaquePointer?   /* (Nsens, Nfreq) col maj vsip_cmview_d */
    public var rm_freq: OpaquePointer?   /* (Nsens, Nts)   rwo maj vsip_mview_d */
    public var m_gram: OpaquePointer?    /* (Nsens, Nfreq) col maj */
    public var rcfftm: OpaquePointer?    /* by row Nsens by Nts    */
    var ccfftm: OpaquePointer?    /* by col Nsens by Nfreq  */
    public var ts_taper: OpaquePointer?  /* of length Nts          */
    public var array_taper: OpaquePointer? /* of length Nsens        */
    public init(param: Param){
        if oddNumber(param.Nts!){
            preconditionFailure("Data Length must be even")
        }
        Navg = param.Navg!
        Nfreq = param.Nts!/2 + 1
        if let cm_freq = vsip_cmcreate_d(vsip_length(param.Nsens!),vsip_length(Nfreq),VSIP_COL,VSIP_MEM_NONE) {
            self.cm_freq = cm_freq
            if let rm_freq = vsip_mrealview_d(self.cm_freq){
                self.rm_freq = rm_freq
            }
        }
        if let m_gram = vsip_mcreate_d(vsip_length(param.Nsens!), vsip_length(Nfreq), VSIP_COL,VSIP_MEM_NONE){
            self.m_gram = m_gram
        }
        if let rcfftm = vsip_rcfftmop_create_d(vsip_length(param.Nsens!),vsip_length(param.Nts!),1,VSIP_ROW,0,vsip_alg_hint(rawValue: 0)) {
            self.rcfftm = rcfftm
        }
        if let ccfftm = vsip_ccfftmip_create_d(vsip_length(param.Nsens!),vsip_length(Nfreq),1.0,VSIP_FFT_FWD,VSIP_COL,0,vsip_alg_hint(rawValue: 0)){
            self.ccfftm = ccfftm
        }
        if let ts_taper   = vsip_vcreate_hanning_d(vsip_length(param.Nts!),VSIP_MEM_NONE){
            self.ts_taper = ts_taper
        }
        if let array_taper = vsip_vcreate_hanning_d(vsip_length(param.Nsens!),VSIP_MEM_NONE) {
            self.array_taper = array_taper
        }
    }
    deinit {
        vsip_malldestroy_d(m_gram);
        vsip_fftm_destroy_d(rcfftm);
        vsip_fftm_destroy_d(ccfftm);
        vsip_valldestroy_d(ts_taper);
        vsip_valldestroy_d(array_taper);
        vsip_mdestroy_d(rm_freq);
        vsip_cmalldestroy_d(cm_freq);
    }
    public func komega(m_data: OpaquePointer){
        /* Data tapers for time and space */
        vsip_vmmul_d(self.ts_taper,m_data,VSIP_ROW,m_data)
        vsip_vmmul_d(self.array_taper,m_data,VSIP_COL,m_data)
        
        /* FFT for time and space */
        vsip_rcfftmop_d(rcfftm,m_data,cm_freq);
        vsip_ccfftmip_d(ccfftm,cm_freq)
        
        /* power estimate */
        /* to save memory place estimate in real part of spectral matrix */
        vsip_mcmagsq_d(cm_freq,rm_freq)
        
        /* scaling for average */
        vsip_smmul_d(1.0/Double(Navg),rm_freq,rm_freq)
        /* add in new values to gram estimate */
        vsip_madd_d(rm_freq,m_gram,m_gram)
    }
    public func zero(){
         vsip_mfill_d(0.0,m_gram)
    }
    public func instance() -> OpaquePointer {
        return self.m_gram!
    }
}
