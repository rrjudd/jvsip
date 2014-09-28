
# coding: utf-8

# ## SVD Bidiagonalization   
# In this section we prototype code to bidiagonalize an input matrix as the first part of a singular value decomposition. For this algorithm where $m$ is the column length and $n$ is the row length we assume $ m \ge n $.  In the JVSIP C algorithm we remove that restriction with a little additional logic. The reason for calling this * SVD Bidiagonalization * instead of just bidiagonalization is we perform phase rotations on the central matrix to ensure the diagonals are real and positive.  This means the * SVD iteration* step is the same for both real and complex except for the updating the left and right update matrices.    
#    
# The essential part of this algorithm is $ A_{\mathbb{C}}=L_{\mathbb{C}} B_{\mathbb{R}} R_{\mathbb{C}} $   
# 
# Usage is 
# > ` L,d,f,R,eps0 = svdBidiag(A,eps) `   
# 
# Where ` eps ` is a small number passed for a clue on what is considered zero, `eps0` is passed back as the number the algorithm is using, and  `d` and `f` are vectors corresponding to the values in the the central and first diagonal entry of $B$.  These objects are needed for the iteration phase.

# In[1]:

import pyJvsip as pv
from math import sqrt


# For the main bidiagonalization I use householder methods. See the Householder notebook for more information on Householder.

# In[2]:

# H A
def houseProd(v,A):
    beta = 2.0/v.jdot(v)
    v.conj;w=v.prod(A).conj;v.conj
    A -= v.outer(beta,w)


# In[3]:

# A H
def prodHouse(A,v):
    beta = 2.0/v.jdot(v)
    w=A.prod(v)
    A-=w.outer(beta,v)


# In[4]:

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


# In[5]:

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


# In[6]:

# See miscSVDroutineNB notebook for additional information on sign 
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


# In[7]:

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


# In[8]:

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


# For additonal information on the phase rotations to make d and f real see the notebook biDiagPhaseToZeroNB.

# In[9]:

def biDiagPhaseToZero(B,L, d, f, R, eps0): # here d and f may be complex
    nd=d.length
    nf=f.length
    assert nd == nf+1, 'For biDiagPhaseToZero the length of d should be nf+1'
    lc=L.colview
    rr=R.rowview
    for i in range(nd):
        ps = d[i]
        if ps == 0.0:
            ps = 1.0
            m = 0.0
        else:
            m=abs(ps) # hypot(ps.real,ps.imag) might have better numerical properties than abs
            ps /= m
        if(m < eps0):
            d[i]=0.0
        else:
            d[i]=m
            if i < f.length:
                f[i] *= ps.conjugate()
            lc(i)[:] *= ps
    for i in range(nf-1):
        j=i+1
        ps=f[i]
        if ps == 0.0:
            ps = 1.0
            m=0.0
        else:
            m=abs(ps) # hypot(ps.real,ps.imag) might have better numerical properties than abs
            ps /= m
        lc(j)[:] *= ps.conjugate()
        rr(j)[:] *= ps
        f[i] = m
        f[j] *= ps
    j=nf
    i=j-1
    ps=f[i]
    if ps == 0.0:
        ps = 1.0
        m = 0.0
    else:
        m=abs(ps)
        ps /= m
    f[i]=m
    lc(j)[:] *= ps.conjugate()
    rr(j)[:] *= ps
    if 'cvview' in d.type: #From here d and f are real since imaginary is all zero
        return (d.realview.copy,f.realview.copy)
    else:
        return (d.copy,f.copy)


# In[10]:

def svdBidiag(A,eps):
    eps0 = A.normFro/float(A.rowlength) * eps
    B=A.copy
    bidiag(B)
    L=UmatExtract(B)
    R=VHmatExtract(B)
    b=B.diagview
    d,f=biDiagPhaseToZero(B,L, b(0), b(1), R, eps0)
    return(L,d,f,R,eps0)


# #### Example

# In[11]:

A=pv.create('mview_f',6,5).fill(0.0)
A[2,2]=3.0; A[3,4]=5.0
L,d,f,R,eps0=svdBidiag(A,1E-10)


# In[12]:

#make up some data
A=pv.create('cmview_f',6,5).randn(5)
A.mprint('%.3f')


# In[13]:

# bidiagonlize and then check to see if we can get back the origional matrix 
L,d,f,R,eps0=svdBidiag(A,1E-10)
B0=A.empty.fill(0.0)
if 'cmview' in B0.type:
    B0.realview.diagview(0)[:]=d
    B0.realview.diagview(1)[:]=f
else:
    B0.diagview(0)[:]=d
    B0.diagview(1)[:]=f
L.prod(B0).prod(R).mprint('%.3f')
print('check %e.4',(A-L.prod(B0).prod(R)).normFro)


# In[14]:

d.mprint('%.3f')
f.mprint('%.3f')


# In[14]:



