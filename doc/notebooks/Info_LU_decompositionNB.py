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
# Note we create an x and calculate a b directly. To demonstrate we use A and b to estimate x.

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

# Both LU and SV overwrite the input matrix; so to preserve our original matrix we use a copy. The LU (and SV) object will keep a reference to the copy (which means python will not garbage collect it). We solve this first using SVD. We don't overwrite our original vector so we can compare the estimated solution to the actual solution. SVD does not have a solver so we do it long hand.

# <codecell>

u,s,v=A.copy.svd
s.mprint(f)
xe=v.prod(u.transview.prod(b)/s)
x.mprint(f)
xe.mprint(f)
print('Forbenius norm of x estimate - x is %.5e'%(xe-x).normFro)

# <markdowncell>

# Now we solve using LU. We start with the LU class directly.

# <markdowncell>

# Note that the class instance varialbe LU.luSel is a dictionary which lets you select the LU decomposition type using the matrix type.

# <codecell>

print('Example of LU.luSel: %s'%pv.LU.luSel[A.type])
luObj = pv.LU(pv.LU.luSel[A.type],n)
_=luObj.decompose(A.copy)
print('Solve for x using b. Done in place. Here we make a copy of b first. ')
xe = b.copy
luObj.solve(pv.VSIP_MAT_NTRANS,xe).mprint(f)
print('Forbenius norm of x estimate - x is %.5e'%(xe-x).normFro)

# <markdowncell>

# In pyJvsip a method is defined on matrix views which will create the LU object for you. We do the same problem.

# <codecell>

xe=b.copy
luObj=A.copy.lu
luObj.solve(pv.VSIP_MAT_NTRANS,xe).mprint(f)
print('Forbenius norm of x estimate - x is %.5e'%(xe-x).normFro)

# <markdowncell>

# For a simple solver we can also just solve directly. If we wanted to solve using matrix operator 'HERM' or 'TRANS' then we would need the more complicated version.

# <codecell>

xe=b.copy
A.copy.luSolve(xe).mprint(f)
print('Forbenius norm of x estimate - x is %.5e'%(xe-x).normFro)

# <markdowncell>

# We also have a pyJvsip method to calculate an inverse using the LU methods.

# <codecell>

Ainv=A.copy.luInv
print('A inverse')
Ainv.mprint(f)
print('Origional A')
A.mprint(f)
print('check to see if we have an inverse by doing a matrix product')
A.prod(Ainv).mprint(f)

# <codecell>


