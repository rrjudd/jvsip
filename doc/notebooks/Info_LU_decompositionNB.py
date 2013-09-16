# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <markdowncell>

# ### LU Decomposition    

# <codecell>

import pyJvsip as pv
f='%.5f'

# <markdowncell>

# Solve using LU Class

# <markdowncell>

# Create some data A x = b   
# Note we create an x and calculate a b directly

# <codecell>

n=5
A=pv.create('mview_d',n,n).fill(0.0)
A.block.vector.randn(5)
x=pv.create('vview_d',n).randn(9)
print('Matrix A');A.mprint(f)
print('Known x vector');x.mprint(f)
b=A.prod(x)
print('Calculated b=Ax vector');b.mprint(f)

# <markdowncell>

# Note LU overwrites the input matrix; so to preserve our original matrix we use a copy. The LU object will keep a reference to the copy (which means python wont garbage collect it).

# <codecell>

u,s,v=A.copy.svd
s.mprint(f)
xe=v.prod(u.transview.prod(b)/s)
x.mprint(f)
xe.mprint(f)
print('%.5e'%(xe-x).normFro)

# <markdowncell>

# First we solve using the LU class directly.

# <markdowncell>

# Note LU.luSel is a dictionary which lets you select the LU decomposition type using the matrix type

# <codecell>

print('Example of LU.luSel: %s'%pv.LU.luSel[A.type])
luObj = pv.LU(pv.LU.luSel[A.type],n)
_=luObj.decompose(A.copy)
print('Solve for x using b. Done in place. Here we make a copy of b first. ')
xb = b.copy
luObj.solve(pv.VSIP_MAT_NTRANS,xb).mprint(f)
print('Calculate an error using (x-xb).normFro %.5e:'%(x-xb).normFro)

# <markdowncell>

# In pyJvsip a method is defined on matrix views which will create the LU object for you. We do the same problem.

# <codecell>

xb=b.copy
luObj=A.copy.lu
luObj.solve(pv.VSIP_MAT_NTRANS,xb).mprint(f)
print('Calculate an error using (x-xb).normFro %.5e:'%(x-xb).normFro)

# <markdowncell>

# For a simple solver we can also just solve directly. If we wanted to solve using matrix operator 'HERM' or 'TRANS' then we would need the more complicated version.

# <codecell>

xb=b.copy
A.copy.luSolve(xb).mprint(f)
print('Calculate an error using (x-xb).normFro %.5e:'%(x-xb).normFro)

# <markdowncell>

# We also have a pyJvsip method to calculate an inverse using the LU methods.

# <codecell>

Ainv=A.copy.luInv
Ainv.mprint(f)
A.mprint(f)
A.prod(Ainv).mprint(f)

# <codecell>


