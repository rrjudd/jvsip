import vsiputils as vsip
from param import *
import kw as KW
import ts as TS
import numpy as np
import matplotlib.pyplot as plt

def mToA(m):
    M=vsip.getcollength(m)
    N=vsip.getrowlength(m)
    a=np.empty((M,N),float,'C')
    for i in range(M):
        for j in range(N):
            a[i,j] = vsip.get(m,(i,j))
    return a

def beamformer(fileName,figNum=1):
    param=param_read(fileName)
    navg=param['Navg']
    ts=TS.Sim_ts(param)
    kw=KW.Kw(param)
    kw.zero()
    dtaIn=ts.instance()
    gramOut=kw.instance()
    for i in range(navg):
        ts.zero()
        ts.nb_sim()
        ts.noise_sim()
        kw.kw(dtaIn)
    for i in range(vsip.getrowlength(gramOut)):
        v=vsip.colview(gramOut,i)
        vsip.freqswap(v)
        vsip.destroy(v)
    max = vsip.maxval(gramOut,None)
    avg = vsip.meanval(gramOut)
    vsip.clip(gramOut,0.0,max,avg/100000.0,max,gramOut)
    vsip.log10(gramOut,gramOut)
    min = vsip.minval(gramOut,None)
    vsip.add(-min,gramOut,gramOut)
    max=vsip.maxval(gramOut,None)
    vsip.mul(1.0/max,gramOut,gramOut)
    fig = plt.figure(figNum,figsize=(10,4))
    ax = fig.add_axes([0.10,0.10,0.85,0.80])
    ax.set_yticklabels(['0','0','30','60','90','120','150','180'])
    ax.yaxis.set_ticks_position('right')
    im=mToA(gramOut)
    plt.imshow(im)
    plt.title('K-Omega Beamformer Output')
    plt.xlabel('Frequency')
    plt.ylabel(r'$\frac{cos(\theta)}{\lambda}$',fontsize=16,rotation='horizontal')
    plt.colorbar()
