import Cocoa
import vsip
let N_data = vsip_length(4096)
let dec1 = 1
let dec3 = 3
let _ = vsip_init(nil)
var N_length = 0
var kernel: OpaquePointer?, fir: OpaquePointer?, r_state: OpaquePointer?, conv: OpaquePointer?
if let t = vsip_vcreate_kaiser_d(128,15.0,VSIP_MEM_NONE) {
    kernel = t
}
if let t = vsip_randcreate(11,1,1,VSIP_NPRNG) {
    r_state = t
}
var data: OpaquePointer?, noise: OpaquePointer?, avg: OpaquePointer?
if let t = vsip_vcreate_d(N_data,VSIP_MEM_NONE){
    data  = t
}
if let t = vsip_vcreate_d(N_data, VSIP_MEM_NONE){
    noise = t
}
if let t = vsip_vcreate_d(N_data,VSIP_MEM_NONE){
    avg = t
}
vsip_vputlength_d(data,vsip_length((Int(N_data) - 1)/dec1) + 1)
vsip_vputlength_d(avg,vsip_length((Int(N_data) - 1)/dec1) + 1)
if let t = vsip_conv1d_create_d(kernel,VSIP_NONSYM,N_data,Int32(dec1),VSIP_SUPPORT_SAME,0,vsip_alg_hint(rawValue: 0)){
    conv = t
}
if let t = vsip_fir_create_d(kernel,VSIP_NONSYM, N_data,vsip_length(dec1),VSIP_STATE_SAVE,0,vsip_alg_hint(rawValue: 0)){
    fir  = t
}
vsip_vfill_d(0.0,avg)
for _ in 0..<10 {
    vsip_vrandn_d(r_state,noise);
    vsip_convolve1d_d(conv,noise,data);
    VU_vfrdB_d(data!,1e-13);
    vsip_vsma_d(data!,0.1,avg,avg);
}
var N_len = vsip_vgetlength_d(avg);
if let x = vsip_vcreate_d( N_len,VSIP_MEM_NONE){
    vsip_vramp_d(-0.5,1.0/Double(N_len-1),x);
    VU_vfprintxyg_d("%8.6f %8.6f\n",x,avg!,"/Users/judd/local/src/jvsip/AppleXcode/example20.playground/Resources/conv_dec1");
    for i in 0..<vsip_vgetlength_d(avg) {
        vsip_vget_d(avg,vsip_index(i))
    }
    vsip_vdestroy_d(x);
}
vsip_vfill_d(0,avg);
for _ in 0..<10 {
    vsip_vrandn_d(r_state,noise);
    vsip_firflt_d(fir,noise,data);
    VU_vfrdB_d(data!,1e-13);
    vsip_vsma_d(data,0.1,avg,avg);
}
N_len = vsip_vgetlength_d(avg);
if let x = vsip_vcreate_d(N_len,VSIP_MEM_NONE){
    vsip_vramp_d(-0.5,1.0/Double(N_len-1),x);
    VU_vfprintxyg_d("%8.6f %8.6f\n",x,avg!,"/Users/judd/local/src/jvsip/AppleXcode/example20.playground/Resources/fir_dec1");
    vsip_vdestroy_d(x);
    for i in 0..<vsip_vgetlength_d(avg) {
        vsip_vget_d(avg,vsip_index(i))
    }
}
vsip_conv1d_destroy_d(conv);
vsip_fir_destroy_d(fir);
conv = vsip_conv1d_create_d(kernel,VSIP_NONSYM, N_data,Int32(dec3),VSIP_SUPPORT_SAME,0,vsip_alg_hint(rawValue: 0))
fir  = vsip_fir_create_d(
    kernel,VSIP_NONSYM,
    N_data,vsip_length(dec3),VSIP_STATE_SAVE,0,vsip_alg_hint(rawValue: 0));
vsip_vputlength_d(data,vsip_length((Int(N_data) - 1 ) / dec3 ) + 1 )
vsip_vputlength_d(avg,vsip_length((Int(N_data) - 1 ) / dec3 ) + 1 )
vsip_vfill_d(0,avg);
for _ in 0..<10 {
    vsip_vrandn_d(r_state,noise);
    vsip_convolve1d_d(conv,noise,data);
    VU_vfrdB_d(data!,1e-13);
    vsip_vsma_d(data,0.1,avg,avg);
}
N_len = vsip_vgetlength_d(avg);
if let x  = vsip_vcreate_d( N_len,VSIP_MEM_NONE){
    vsip_vramp_d(-0.5,1.0/(vsip_scalar_d)(N_len - 1),x);
    VU_vfprintxyg_d("%8.6f %8.6f\n",x, avg!,"/Users/judd/local/src/jvsip/AppleXcode/example20.playground/Resources/conv_dec3");
    vsip_vdestroy_d(x);
    for i in 0..<vsip_vgetlength_d(avg) {
        vsip_vget_d(avg,vsip_index(i))
    }
}
vsip_vfill_d(0,avg);
for _ in 0..<10 {
    vsip_vrandn_d(r_state,noise);
    vsip_firflt_d(fir,noise,data);
    VU_vfrdB_d(data!,1e-13);
    vsip_vsma_d(data,0.1,avg,avg);
}
N_len = vsip_vgetlength_d(avg);
if let x = vsip_vcreate_d(N_len,VSIP_MEM_NONE){
    vsip_vramp_d(-0.5,1.0/Double(N_len-1),x);
    VU_vfprintxyg_d("%8.6f %8.6f\n", x, avg!,"/Users/judd/local/src/jvsip/AppleXcode/example20.playground/Resources/fir_dec3");
    vsip_vdestroy_d(x);
    for i in 0..<vsip_vgetlength_d(avg) {
        vsip_vget_d(avg,vsip_index(i))
    }
}
N_len = vsip_vgetlength_d(kernel);
if let x = vsip_vcreate_d(N_len,VSIP_MEM_NONE){
    vsip_vramp_d(0,1,x);
    VU_vfprintxyg_d("%8.6f %8.6f\n", x,kernel!,"/Users/judd/local/src/jvsip/AppleXcode/example20.playground/Resources/kaiser_window");
    vsip_vramp_d(-0.5,1.0/(vsip_scalar_d)(N_len-1),x);
    VU_vfrdB_d(kernel!,1e-20);
    VU_vfprintxyg_d("%8.6f %8.6f\n",x,kernel!,"/Users/judd/local/src/jvsip/AppleXcode/example20.playground/Resources/Freq_Resp_Kaiser");
    vsip_vdestroy_d(x);
    for i in 0..<vsip_vgetlength_d(avg) {
        vsip_vget_d(avg,vsip_index(i))
    }
}
vsip_randdestroy(r_state);
vsip_valldestroy_d(kernel);
vsip_conv1d_destroy_d(conv);vsip_fir_destroy_d(fir);
vsip_valldestroy_d(data); vsip_valldestroy_d(noise);
vsip_valldestroy_d(avg);
vsip_finalize(nil);
