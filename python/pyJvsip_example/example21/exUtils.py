import pyJvsip as pv
from math import pi as M_PI
from math import cos as cos
def view_store(M,fname): #VU_mprintgram
    assert 'pyJvsip' in repr(M),'First input argument must be a pyJvsip view'
    assert M.type in ['vview_f','mview_f','vview_d','mview_d'], 'View type not supported'
    assert isinstance(fname,str), 'File name is a string'
    if 'mview' in M.type:
        RL=M.rowlength; CL=M.collength
        of=open(fname,'w')
        of.write('%s\n'%M.type)
        of.write('%ld %ld\n'%(CL,RL))
        for row in range(CL):
            for col in range(RL):
                of.write('%ld %ld %e\n'%(row,col,M[row,col]))
        of.close()
    else:
        L=M.length
        of=open(fname,'w')
        of.write('%s'%M.type)
        of.write('%ld'%L)
        for i in range(L):
            of.write('%ld %e'%(i,M[i]))
        of.close()
    return
def view_read(fname):
    from pyJvsip import create as create
    fd=open(fname,'r')
    t=fd.readline().split()[0]
    assert t in ['vview_f','mview_f','vview_d','mview_d'], 'Type <:%s:> not supported'%t
    if 'mview' in t:
        sz=fd.readline().split()
        M=pv.create(t,int(sz[0]),int(sz[1]))
        for lin in fd:
            a=lin.split()
            r=int(a[0]);c=int(a[1]);x=float(a[2])
            M[r,c]=x
    else:
        sz=fd.readline().split()
        M=create(t,int(sz))
        for lin in fd:
            a=lin.split()
            i=int(a[0]);x=float(a[2])
            M[i]=x
    fd.close()
    return M
def center(gram):
    assert gram.rowstride == 1
    assert gram.colstride == gram.rowlength
    if gram.collength & 1: #odd
        for i in range(gram.rowlength):
            pv.freqswap(gram.colview(i))
    else: #even number of columns; use trick
        lngth = int(gram.collength*gram.rowlength/2)
        gramvec=gram.block.vector
        pv.swap(gramvec[lngth:],gramvec[:lngth])     
    return gram
# scale gram to db, min 0 max 255 */
def scale(gram_data):
    f={'cmview_d':'mview_d','cmview_f':'mview_f'}
    assert gram_data.type in ['cmview_d','cmview_f'], 'gram_data must be complex float matrix'
    M=gram_data.collength; N=gram_data.rowlength; t=f[gram_data.type]
    gram=pv.create(t,M,N,'ROW')
    pv.cmagsq(gram_data,gram)
    gram += (1.0-gram.minval)
    gram.log10
    gram *= 256.0/gram.maxval
    return center(gram)
def noiseGen(t,alpha,Mp,Nn,Ns):
    """
    Usage:
        data = noiseGen(t,alpha,Mp,Nn,Ns)
    where:
        data is a matrix of type t and size Mp by Ns)
        alpha is a linear array constant
        Mp is the number of sensors in the linear array
        Nn is the size of the simulated noise vector
        Ns is the size of the output noise field for each sensor
    Note the noise field is returned in data
    """
    # program parameters
    from math import pi as M_PI
    kaiser=9
    Nfilter=10   # Kernel length for noise filter
    Nnoise=64    # number of Simulated Noise Directions
    cnst1 = M_PI/Nnoise
    offset0 = int(alpha * Mp + 1)
    nv = pv.create('vview_d',2 * Nn)
    noise=pv.create('mview_d',Mp,Nn)
    kernel = pv.create('vview_d',Nfilter).kaiser(kaiser)
    fir = pv.FIR('fir_d',kernel,'NONE',2 * Nn,2,'YES')
    data = pv.create('mview_d',Mp,Ns).fill(0.0)
    state = pv.Rand('PRNG',15)
    for j in range(Nnoise):
        noise_j=noise.rowview(j)
        state.randn(nv)
        fir.flt(nv,noise_j)
        noise_j *= 12.0/float(Nnoise)
    #view_store(noise,'noiseData');
    noise.putrowlength(Ns)
    for i in range(Mp):
        data_v = data.rowview(i)
        for j in range(Nnoise):
            noise_j=noise.rowview(j)
            noise_j.putoffset(offset0 +(int)( i * alpha * cos(j * cnst1)))
            pv.add(noise_j,data_v,data_v)
    #view_store(data,'Data');
    return data
def narrowBandGen(data,alpha,targets,Fs):
    """
    Usage:
       data = narrowBandGen(data,alpha,targets,Fs)
    Where:
       data is an array of size number of sensors by samples
          Matrix data contains simulated noise field for array
       alpha is the array constant
       targets is a list of tuples containing simulated narrow band target information
       Fs is the sample rate (Hz)
    """
    from math import pi as M_PI
    f={'mview_d':'vview_d','mview_f':'vview_f'}
    tp=data.type   
    N=data.rowlength
    M=data.collength
    t =pv.create(f[tp],N).ramp(0,1)
    tt = pv.create(f[tp],N)
    Xim = pv.create(tp,M,M+1,'ROW')
    m = pv.create(f[tp],M).ramp(0,1)
    Xi = pv.create(f[tp],M + 1).ramp(0,M_PI/M).cos
    pv.outer(alpha,m,Xi,Xim)
    for i in range(M):
        data_v = data.rowview(i)
        for j in range(len(targets)):
            tgt=targets[j];
            w0=float(2.0 * M_PI * tgt[0]/Fs); Theta=int(tgt[1])
            sc=tgt[2]
            Xim_val = Xim[i,Theta]
            pv.ma(t,w0,-w0 * Xim_val,tt)
            tt.cos
            tt *= sc
            data_v += tt
    return data
