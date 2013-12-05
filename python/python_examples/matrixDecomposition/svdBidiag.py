import pyJvsip as pv
from math import sqrt
def houseProd(v,A):
    beta = 2.0/v.jdot(v)
    v.conj;w=v.prod(A).conj;v.conj
    A -= v.outer(beta,w)
def prodHouse(A,v):
    beta = 2.0/v.jdot(v)
    w=A.prod(v)
    A-=w.outer(beta,v)
def VHmatExtract(B): #B bidiagonalized with householder vectors stored in rows and columns.
    n = B.rowlength
    V=pv.create(B.type,n,n).fill(0.0);V.diagview(0).fill(1.0)
    if(n < 3):
        return V;
    for i in range(n-3,0,-1):
        j=i+1;
        v=B.rowview(i)[j:]
        t=v[0]
        v[0]=1.0
        prodHouse(V[j:,j:],v)
        v[0]=t
    v=B.rowview(0)[1:]
    t=v[0];v[0]=1.0
    prodHouse(V[1:,1:],v)
    v[0]=t
    return V
def UmatExtract(B):
    m = B.collength
    n = B.rowlength
    U=pv.create(B.type,m,m).fill(0.0);U.diagview(0).fill(1.0)
    if (m > n):
        i=n-1;
        v=B.colview(i)[i:]
        t=v[0]
        v[0]=1.0
        houseProd(v,U[i:,i:])
        v[0]=t
    for i in range(n-2,0,-1):
        v=B.colview(i)[i:]
        t=v[0];v[0]=1.0
        houseProd(v,U[i:,i:])
        v[0]=t
    v=B.colview(0)
    t=v[0];v[0]=1.0
    houseProd(v,U)
    v[0]=t
    return U
def sign(a):
    if a.imag == 0.0:
        if a.real < 0.0:
            return -1.0
        else:
            return 1.0
    else:
        re = abs(a.real)
        im = abs(a.imag)
        if re < im:
            t=re/im; t*=t; t +=1; t = im*sqrt(t)
        else:
            t=im/re; t*=t; t +=1; t = re*sqrt(t) 
        return a/t
def houseVector(x):
    nrm=x.norm2
    t=x[0]
    x[0]=nrm * sign(t) + t
    nrm = x.norm2
    if nrm == 0.0:
        x[0]=1.0
    else:
        x /= nrm
    return x
def bidiag(B):
    x=B.colview(0)
    m=B.collength;n=B.rowlength
    assert m >= n,'For bidiag the input matrix must have a collength >= rowlength'
    v=x.empty.fill(0.0)
    for i in range(n-1):
        x=B.colview(i)[i:]
        v=v.block.bind(0,1,x.length)
        pv.copy(x,v)
        houseVector(v)
        z = v[0]; re = z.real; im = z.imag; z = re*re + im*im
        if z > 0.0:
            re /= z; im = -im/z
        if im == 0.0:
            z=re
        else:
            z=complex(re,im)
        v *= z;
        houseProd(v,B[i:,i:]);
        pv.copy(v[1:],x[1:])
        if(i < n-2):
            j = i+1;
            v.putlength(n-j)
            x=B.rowview(i)[j:]
            pv.copy(x,v)
            houseVector(v);
            v.conj
            z = v[0]; re = z.real; im = z.imag; z = re*re + im*im
            if z > 0.0:
                re /= z; im = -im/z
            if im == 0.0:
                z=re
            else:
                z=complex(re,im)
            v[:] *= z;
            prodHouse(B[i:,j:],v);
            pv.copy(v[1:],x[1:])
    if(m > n):
        i=n-1
        x=B.colview(i)[i:]
        v=v.block.bind(0,1,x.length)
        pv.copy(x,v)
        houseVector(v)
        z = v[0]; re = z.real; im = z.imag; z = re*re + im*im
        if z > 0.0:
            re /= z; im = -im/z
        if im == 0.0:
            z=re
        else:
            z=complex(re,im)
        v[:] *= z;
        houseProd(v,B[i:,i:]);
        pv.copy(v[1:],x[1:])
    return B
def biDiagPhaseToZero(B,L, d, f, R, eps0): 
    nd=d.length
    nf=f.length
    assert nd == nf+1, 'For biDiagPhaseToZero the length of d should be nf+1'
    lc=L.colview
    rr=R.rowview
    for i in range(nd):
        ps = d[i]
        m=abs(ps) 
        ps /= m
        if(m < eps0):
            d[i]=0.0
        else:
            d[i]=m
            f[i] *= ps.conjugate()
            lc(i)[:] *= ps
    for i in range(nf-1):
        j=i+1
        ps=f[i]
        m=abs(ps)
        ps /= m
        lc(j)[:] *= ps.conjugate()
        rr(j)[:] *= ps
        f[i] = m
        f[j] *= ps
    j=nf
    i=j-1
    ps=f[i]
    m=abs(ps)
    ps /= m
    f[i]=m
    lc(j)[:] *= ps.conjugate()
    rr(j)[:] *= ps
    if 'cvview' in d.type: 
        return (d.realview.copy,f.realview.copy)
    else:
        return (d.copy,f.copy)
def svdBidiag(A,eps):
    eps0 = A.normFro/float(A.rowlength) * eps
    B=A.copy
    bidiag(B)
    L=UmatExtract(B)
    R=VHmatExtract(B)
    b=B.diagview
    d,f=biDiagPhaseToZero(B,L, b(0), b(1), R, eps0)
    return(L,d,f,R,eps0)
