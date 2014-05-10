import pyJvsip as pv
import numpy as np
import matplotlib.pyplot as plt
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
gram = view_read('gram_output')
fig = plt.figure()
ax = fig.add_subplot(111)
plt.imshow(gram.list,origin='lower')
ax.set_yticks([0,31,63,95,127])
ax.set_xticks([0,51,103,154,206,256])
ax.set_yticklabels([r'$-\kappa$','$-\kappa /2$','$0$','$\kappa /2$','$\kappa$'])
ax.set_xticklabels([' 0 ','100','200','300','400','500'])
ax.set_title(r'$\vec{\kappa}\omega$ plot')
ax.set_xlabel('Frequency (Hz)')
ax.set_ylabel(r'$\kappa \cdot \cos(\theta)$')
plt.show()
