# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <markdowncell>

# ### Discrete Fourier Transform Coefficients   
# In this notebook I explore the baseline DFT and examine the decomposition of the coefficient matrix. At the moment this is mostly play to see what I can learn.
# 
# ####Reference
# My primary reference is Charles Van Loan's Computational Frameworks for the Fast Fourier Transform.
# There are  many references available but I won't try and list them here.

# <codecell>

import pyJvsip as pv

# <markdowncell>

# The DFT matrix is square and complex. We designate it as $F_n$ where n is the size of the matrix. If we have a (column) vector $\vec x$ of size $n$ then the dft is   
# $\vec X = F_n \vec x$.   
# Elements of $F_n$ are designated $f_{q,p}$.  These elements are equally spaced around the unit circle in the complex plane at increments of ${2  \pi} \over {n}$ so that    
# $f_{q,p}$ = `complex`$\left(\cos(2 q p \pi/n),-\sin(2 q p \pi/n)\right)$   
# Since $q$ and $p$ traverse all value pairs between $0$ and $n-1$ and go around the unit circle more than once if we set $t$ to the $pq$ modulo $n$ then we can compute just a vector of DFT weights from $0$ to $n-1$ and look up the proper value with index $t$.

# <markdowncell>

# Below we define functions to return the matrix of DFT weights for matrix of size n. The function dftCoefE returns the actual weight. The function dftCoef returns the matrix of index values $t$ described above.

# <codecell>

def dftCoefE(n):
     m=pv.create('cmview_d',n,n)
     for i in range(n):
         for j in range(n):
             t=(i*j)%n
             x=2.0*pi/n * float(t)
             m[i,j]=complex(cos(x),-sin(x))
     return m

def dftCoef(n):
    m=pv.create('mview_d',n,n)
    for i in range(n):
        for j in range(n):
            m[i,j]=(i*j)%n
    return m

# <codecell>

A=dftCoefE(4)
A.mprint('%.3f')

# <codecell>

B=dftCoef(4)
B.mprint('%.3f')

# <codecell>

dftCoef(5).mprint('%.1f')

# <codecell>

dftCoef(3).sv.mprint('%.3f')

# <codecell>

dftCoef(5).sv.mprint('%.3f')

# <codecell>

dftCoef(7).sv.mprint('%.3f')

# <codecell>

dftCoef(11).sv.mprint('%.3f')

# <codecell>

dftCoef(13).sv.mprint('%.3f')

# <codecell>

dftCoef(17).sv.mprint('%.3f')

# <codecell>

dftCoef(3*2).sv.mprint('%.3f')

# <codecell>

dftCoef(2).sv.mprint('%.3f')

# <markdowncell>

# So, playing, I notice if I find the singular values of the $t$ values matrix and I use a prime number for $n$ then the largest singular value is an integer equal to (n-1)/2 * n.  Don't know if this is of use but is interesting.

# <codecell>

136/17
(17-1)/2*17

# <codecell>

print('%d, %d'%(78/13, (13-1)/2*13))

# <codecell>

print('%d, %d'%(55/11, (11-1)/2*11))

# <codecell>

21/7

# <codecell>

3/3

# <codecell>

#try it for not prime 6
print('%f, %f'%(12.97, (6.-1.)/2.*6.))

# <codecell>


