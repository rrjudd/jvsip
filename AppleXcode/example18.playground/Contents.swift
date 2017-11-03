//: Playground - noun: a place where people can play

import Cocoa
import vsip
let path = Bundle.main.resourcePath
var fname = path?.appending("/Cheby_Window")
let _ = vsip_init(nil)
let ripple = 100
let Nlength = 101
let Cw = vsip_vcreate_cheby_d(vsip_length(Nlength),vsip_scalar_d(ripple),vsip_memory_hint(rawValue: 0));
let fft  = vsip_ccfftip_create_d(vsip_length(Nlength),1.0,VSIP_FFT_FWD,0,vsip_alg_hint(rawValue: 0));
let FCW = vsip_cvcreate_d(vsip_length(Nlength),vsip_memory_hint(rawValue: 0));
/*printf("CW = "); VU_vprintm_d("%6.8f ;\n",Cw); */
VU_vfprintyg_d(format: "%6.8f\n",a: Cw!,fname: "/Users/judd/local/sandboxes/Cheby_Window");
for i in 0..<Nlength{
    vsip_vget_d(Cw!, vsip_index(i))
}
vsip_cvfill_d(vsip_cmplx_d(0,0),FCW);
let rv = vsip_vrealview_d(FCW);
            vsip_vcopy_d_d(Cw,rv);
            vsip_ccfftip_d(fft,FCW);
            vsip_vcmagsq_d(FCW,rv);
var ind: vsip_index = 0
let max = vsip_vmaxval_d(rv,&ind);
let min = max/(10e12);
vsip_vclip_d(rv,min,max,min,max,rv);
vsip_vlog10_d(rv,rv)
vsip_svmul_d(10,rv,rv)
VU_vfreqswapIP_d(b: rv!)
VU_vfprintyg_d(format: "%6.8f\n",a: rv!,fname: "/Users/judd/local/sandboxes/Cheby_Window_Frequency_Response")
for i in 0..<vsip_vgetlength_d(rv!) {
    vsip_vget_d(rv!, vsip_index(i))
}
vsip_vdestroy_d(rv);
vsip_fft_destroy_d(fft)
vsip_valldestroy_d(Cw)
vsip_cvalldestroy_d(FCW)
vsip_finalize(nil)


