import Foundation
import vsip

public class TimeSeries{
    public let Fs: Double
    public let c: Double
    public let Dsens: Double
    public let Nsens: Int
   public  let Nsim_noise: Int
   public  let Nsim: Int
   public  let Nts: Int
   public  var fir: OpaquePointer?
   public  var noise: OpaquePointer?
    public var bl_noise: OpaquePointer?
    public var rand: OpaquePointer?
    public var t: OpaquePointer?
    public var t_dt: OpaquePointer?
    public var m_data: OpaquePointer?
    public var v_data: OpaquePointer?
    public var freqs: [Double] = []
    public var bearings: [Double] = []
    public var d_t: Double {
        return self.Dsens/self.c
    }
    public init(param: Param) {
        var tL = 2.0 * param.Fs!
        tL /= Double(param.Nsens!) * param.Dsens!/param.c!
        tL += Double(param.Nts! + 1)
        let L = Int(2 * tL)
        self.Nsim = param.Nsim!
        self.freqs = param.freqs
        self.bearings = param.bearings
        self.Nts = param.Nts!
        self.Nsens = param.Nsens!
        self.c = param.c!
        self.Dsens = param.Dsens!
        self.Nsim_noise=param.Nsim_noise!
        self.Fs = param.Fs!
        
        if let kernel = vsip_vcreate_kaiser_d(6,1,VSIP_MEM_NONE){
            if let t = vsip_fir_create_d(kernel,VSIP_NONSYM, vsip_length(L) , 2 , VSIP_STATE_SAVE,0,VSIP_ALG_TIME){
                self.fir = t
            }
            if let t = vsip_vcreate_d(vsip_length(L),VSIP_MEM_NONE){
                self.noise = t
            }
            if let t = vsip_vcreate_d(vsip_length(Int(tL)),VSIP_MEM_NONE) {
                self.bl_noise = t
            }
            if let t = vsip_randcreate(7,1,1,VSIP_PRNG) {
                self.rand = t
            }
            if let t = vsip_vcreate_d(vsip_length(param.Nts!),VSIP_MEM_NONE) {
                self.t = t
            }
            if let t = vsip_vcreate_d(vsip_length(param.Nts!),VSIP_MEM_NONE) {
                self.t_dt = t
                let step = 1.0 / param.Fs!
                vsip_vramp_d(0.0,step,self.t);
            }
            if let t = vsip_mcreate_d(vsip_length(param.Nsens!),vsip_length(param.Nts!),VSIP_ROW,VSIP_MEM_NONE) {
                self.m_data = t
                if let t = vsip_mrowview_d(self.m_data,0){
                    self.v_data = t
                }
            }
            vsip_valldestroy_d(kernel)
        }
    }
    deinit {
        vsip_fir_destroy_d(self.fir);
        vsip_valldestroy_d(self.noise);
        vsip_valldestroy_d(self.bl_noise);
        vsip_randdestroy(self.rand);
        vsip_valldestroy_d(self.t);
        vsip_valldestroy_d(self.t_dt);
        vsip_vdestroy_d(self.v_data);
        vsip_malldestroy_d(self.m_data);
    }
    public func zero(){
        vsip_mfill_d(0.0,m_data)
    }
    public func rowview(_ i: Int){
        var mattr: vsip_mattr_d = vsip_mattr_d()
        var vattr: vsip_vattr_d = vsip_vattr_d()
        vsip_mgetattrib_d(m_data,&mattr)
        vattr.offset = vsip_offset(Int(mattr.offset) + i * Int(mattr.col_stride))
        vattr.length = mattr.row_length
        vattr.stride = mattr.row_stride
        vsip_vputattrib_d(v_data,&vattr)
    }
    public func nb_sim(){
        let d_t = self.d_t
        for i in 0..<Nsim {
            let f = freqs[i]
            let b = d_t * cos(bearings[i] * Double.pi/180)
            for j in 0..<Nsens {
                let dt = Double(j) * b
                vsip_svadd_d(dt,t,t_dt)
                vsip_svmul_d(2.0 * Double.pi * f,t_dt,t_dt)
                vsip_vcos_d(t_dt,t_dt)
                vsip_svmul_d(3.0,t_dt,t_dt)
                rowview(j);
                vsip_vadd_d(t_dt,v_data,v_data);
            } // next sensor
        } // next bearing
        
    }
    public func noise_sim(){
        let d_t = Fs * self.d_t
        let o_0 = d_t * Double(Nsens) + 1.0
        let a_stp = Double.pi / Double(self.Nsim_noise)
        var bl_attr: vsip_vattr_d = vsip_vattr_d()
        vsip_vgetattrib_d(bl_noise,&bl_attr)
        for j in 0..<Nsim_noise {
            let a_crct = cos(Double(j) * a_stp)
            vsip_vrandn_d(rand,noise);
            vsip_firflt_d(fir,noise,bl_noise);
            vsip_svmul_d(12.0/Double(Nsim_noise),bl_noise,bl_noise);
            vsip_vputlength_d(bl_noise,vsip_length(Nts))
            for i in 0..<Nsens {
                let index = vsip_index(o_0 + Double(i) * d_t * a_crct)
                vsip_vputoffset_d(bl_noise, index)
                rowview(i)
                vsip_vadd_d(bl_noise,v_data,v_data);
            }
            vsip_vputattrib_d(bl_noise,&bl_attr);
        }
        vsip_smadd_d(-vsip_mmeanval_d(m_data),m_data,m_data);        
    }
    public func instance() -> OpaquePointer {
        return self.m_data!
    }
}

