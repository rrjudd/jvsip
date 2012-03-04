import vsiputils as vsip

def VU_rowview(v, m, i):
   mattr=vsip.getattrib(m)
   vattr=vsip.getattrib(v)
   vattr.offset = mattr.offset + i * mattr.col_stride
   vattr.length = mattr.row_length
   vattr.stride = mattr.row_stride
   vsip.putattrib(v,vattr);

class Sim_ts(object):
    """ Simulate acoustic data with narrow band point sources from multiple
        directions and isotropic, band-limited noise.
    """
    def __init__(self,param):
        c=param['c']
        Dsens = param['Dsens']
        Nsens = param['Nsens']
        Nts = param['Nts']
        Fs = param['Fs']
        row=vsip.VSIP_ROW
        mem=vsip.VSIP_MEM_NONE
        state=vsip.VSIP_STATE_SAVE
        sym=vsip.VSIP_NONSYM
        rng=vsip.VSIP_PRNG
        L          = int(2 * Fs/(Nsens * Dsens/c) + Nts + 1)
        self.Nsim_freqs = param['Nsim_freqs']
        self.Nsens = Nsens
        self.Nsim_noise=param['Nsim_noise']
        self.Nts = Nts
        self.Fs = Fs
        kernel     = vsip.create('kaiser_d',(6,1,0))
        self.fir   = vsip.create('fir_d',(kernel, sym, 2*L, 2, state, 0,0))
        self.noise = vsip.create('vview_d',(2*L,mem))
        self.bl_noise = vsip.create('vview_d',(L,mem))
        self.rand  = vsip.create('randstate',(7,1,1,rng))
        self.t = vsip.create('vview_d',(Nts,mem))
        vsip.ramp(0,1.0/Fs,self.t) #vector of sample times
        self.t_dt = vsip.create('vview_d',(Nts,mem))    
        self.m_data = vsip.create('mview_d',(Nsens,Nts,row,mem))
        self.v_data = vsip.rowview(self.m_data,0)
        self.d_t = param['Dsens']/param['c'] #travel time at end-fire between sensors
        self.sim_freqs = param['sim_freqs']
        self.sim_bearings = param['sim_bearings']
        vsip.allDestroy(kernel)

    def __del__(self):
        vsip.destroy(self.fir)
        vsip.allDestroy(self.noise)
        vsip.allDestroy(self.bl_noise)
        vsip.destroy(self.rand)
        vsip.allDestroy(self.t)
        vsip.allDestroy(self.t_dt)
        vsip.destroy(self.v_data)
        vsip.allDestroy(self.m_data)

    def nb_sim(self):
        from numpy import pi,cos
        for i in range(self.Nsim_freqs):
            f=self.sim_freqs[i]
            b=self.d_t * cos(self.sim_bearings[i] * pi/180.0)
            for j in range(self.Nsens):
                dt = float(j) * b
                vsip.add(dt,self.t,self.t_dt)
                vsip.mul(2 * pi * f, self.t_dt, self.t_dt);
                vsip.cos(self.t_dt,self.t_dt)
                vsip.mul(3.0,self.t_dt,self.t_dt)
                VU_rowview(self.v_data,self.m_data,j)
                vsip.add(self.t_dt,self.v_data,self.v_data)
    
    def noise_sim(self):
        from numpy import pi, cos
        d_t=self.d_t * self.Fs #sensor-to-sensor travel time at end-fire in samples
        o_0    = d_t * self.Nsens + 1 # array travel time at end-fire in samples
        a_stp = pi/self.Nsim_noise # angle step
        bl_attr = vsip.getattrib(self.bl_noise)
        for j in range(self.Nsim_noise):
            a_crct = cos(float(j) * a_stp)
            vsip.randn(self.rand,self.noise)
            vsip.firfilt(self.fir,self.noise,self.bl_noise)
            vsip.mul(12.0/float(self.Nsim_noise),self.bl_noise,self.bl_noise)
            vsip.putlength(self.bl_noise,self.Nts);
            for i in range(self.Nsens):
               vsip.putoffset(self.bl_noise,int(o_0 + i * d_t * a_crct))
               VU_rowview(self.v_data,self.m_data,i)
               vsip.add(self.bl_noise,self.v_data,self.v_data)
            vsip.putattrib(self.bl_noise,bl_attr);
        vsip.add(-vsip.meanval(self.m_data),self.m_data,self.m_data);

    def zero(self):
        vsip.fill(0.0,self.m_data)

    def instance(self):
        return self.m_data
