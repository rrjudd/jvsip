import Foundation
import vsip
public func oddNumber(_ n: Int) -> Bool {
    let b = n % 2
    return b == 1
}
public func VU_vfrdB_d(_ a: OpaquePointer,_ range: Double) -> Int {
    var ret = 0
    let N_len = vsip_length(vsip_vgetlength_d(a))
    var ca: OpaquePointer?, ia: OpaquePointer?, ra: OpaquePointer?, ta: OpaquePointer?
    var fft: OpaquePointer?
    if let t = vsip_cvcreate_d(N_len,VSIP_MEM_NONE) {
        ca = t
    } else {
        ret = 1
    }
    if let t = vsip_ccfftip_create_d(N_len,1,VSIP_FFT_FWD,0,vsip_alg_hint(rawValue: 0)){
        fft = t
    } else {
        ret = 1
    }
    if let t = vsip_vrealview_d(ca) {
        ra = t
    }else {
        ret = 1
    }
    if let t = vsip_vimagview_d(ca){
        ia = t
    }else {
        ret = 1
    }
    if let t = vsip_vcloneview_d(a) {
        ta = t
    }else {
        ret = 1
    }
    if ret == 0 {
        let s = vsip_offset(vsip_vgetstride_d(ta))
        vsip_vfill_d(0,ia); vsip_vcopy_d_d(a,ra)
        vsip_ccfftip_d(fft,ca)
        vsip_vcmagsq_d(ca,ra)
        var ind: vsip_index = 0
        let max = vsip_vmaxval_d(ra,&ind)
        let min = max * range
        vsip_vclip_d(ra,min,max,min,max,ra)
        if oddNumber(Int(N_len)) {
            let Nlen = vsip_length( N_len/2)
            vsip_vputlength_d(ta,Nlen+1)
            vsip_vputlength_d(ra,Nlen+1)
            vsip_vputoffset_d(ta,Nlen * s)
            vsip_vcopy_d_d(ra,ta)
            vsip_vputlength_d(ra,Nlen)
            vsip_vputlength_d(ta,Nlen)
            vsip_vputoffset_d(ta,vsip_vgetoffset_d(a))
            vsip_vputoffset_d(ra,Nlen+1)
            vsip_vcopy_d_d(ra,ta)
        } else {
            let Nlen = vsip_length( N_len/2)
            vsip_vcopy_d_d(ra,ta)
            vsip_vputlength_d(ta,Nlen)
            vsip_vputlength_d(a,Nlen)
            vsip_vputoffset_d(ta,(vsip_offset)(Nlen) * s)
            vsip_vswap_d(ta,a);
            vsip_vputlength_d(a,N_len)
        }
        vsip_vlog10_d(a,a)
        vsip_svmul_d(10,a,a)
    }
    vsip_fft_destroy_d(fft)
    vsip_vdestroy_d(ra)
    vsip_vdestroy_d(ia)
    vsip_cvalldestroy_d(ca)
    vsip_vdestroy_d(ta)
    return ret
}
