import vsiputils as vsip
class Kw(object):
    def __init__(self,param):
        mem=vsip.VSIP_MEM_NONE
        col=vsip.VSIP_COL
        row=vsip.VSIP_ROW
        fftfwd=vsip.VSIP_FFT_FWD
        vsip.init()
        Nsens=param['Nsens']
        Nts=param['Nts']
        Nfreq=int(Nts/2) + 1
        self.Navg=param['Navg']
        self.Nfreq=Nfreq
        self.cm_freq=vsip.create('cmview_d',(Nsens,Nfreq,col,mem)) 
        self.rm_freq=vsip.realview(self.cm_freq)
        self.m_gram=vsip.create('mview_d',(Nsens,Nfreq,col,mem))
        self.rcfftm=vsip.create('rcfftmop_d',(Nsens,Nts,1,row,0,0))
        self.ccfftm=vsip.create('ccfftmip_d',(Nsens,Nfreq,fftfwd,1,col,0,0))
        self.ts_taper=vsip.create('hanning_d',(Nts,0))
        self.array_taper=vsip.create('hanning_d',(Nsens,0));

    def __del__(self):
        vsip.destroy(self.rm_freq)
        vsip.allDestroy(self.cm_freq)
        vsip.allDestroy(self.m_gram)
        vsip.allDestroy(self.ts_taper)
        vsip.allDestroy(self.array_taper)
        vsip.destroy(self.rcfftm)
        vsip.destroy(self.ccfftm)
        vsip.finalize()

    def zero(self):
        vsip.fill(0.0,self.m_gram)

    def kw(self,m_data):
        row=vsip.VSIP_ROW
        col=vsip.VSIP_COL
        vsip.vmmul(self.ts_taper,m_data,row,m_data);
        vsip.vmmul(self.array_taper,m_data,col,m_data);
        vsip.fftop(self.rcfftm,m_data,self.cm_freq)
        vsip.fftip(self.ccfftm,self.cm_freq)
        vsip.magsq(self.cm_freq,self.rm_freq) #check rm_freq real part?
        vsip.mul(1.0/self.Navg,self.rm_freq, self.rm_freq)
        vsip.add(self.rm_freq,self.m_gram,self.m_gram)

    def instance(self):
        return self.m_gram
