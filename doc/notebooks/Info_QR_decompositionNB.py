# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <markdowncell>

# ### QR Decomposition    

# <codecell>

import pyJvsip as pv
f='%.5f'

# <markdowncell>

# Solve using QR Class

# <markdowncell>

# Create some data A x = b   
# Note we create an x and calculate a b directly

# <codecell>

m=7;n=5
A=pv.create('mview_d',m,n).randn(5)
x=pv.create('mview_d',n,1).randn(9)
print('Matrix A');A.mprint(f)
print('Known x vector');x.transview.mprint(f)
b=A.prod(x)
print('Calculated b=Ax vector');b.transview.mprint(f)

# <markdowncell>

# Note QR overwrites the input matrix; so to preserve our original matrix we use a copy. The QR object will keep a reference to the copy (which means python will not garbage collect it). The QR class has a dictionary item which allows the user to query for the proper type bassed on the associated matrix.

# <codecell>

print('Example of QR.qrSel: %s'%pv.QR.qrSel[A.type])
qrObj = pv.QR(pv.QR.qrSel[A.type],m,n,pv.VSIP_QRD_SAVEQ)
_=qrObj.decompose(A.copy)
print('Solve for x estimate using b. Done in place. Here we make a copy of b first. A subview is printed since b is longer than the xestimate')
xb = b.copy
qrObj.solve('LLS',xb).transview[:,:A.rowlength].mprint(f)

# <markdowncell>

# Below we use the create function to produce a qr object with (default) save full Q. We then extract Q using prodQ and the identity matrix. We then check to see if Q is orthonormal.

# <codecell>

B=pv.create('cmview_d',8,3).randn(10)
qr=pv.create('cqr_d',8,3)
Q=qr.decompose(B).prodQ('NTRANS','RSIDE',pv.create('cmview_d',8,8).identity)
Q.mprint('%.2f')
Q.prodh(Q).mprint('%.1f')

# <markdowncell>

# Below we do the above example except we use a convenience view method to create the QR object directly from the matrix view; and we use prodQ twice to do the matrix multiply first times the identity to get Q and then Q times it's hermitian.

# <codecell>

qr=pv.create('cmview_d',8,3).randn(10).qr
Q=qr.prodQ('NTRANS','RSIDE',pv.create('cmview_d',8,8).identity)
qr.prodQ('HERM','RSIDE',Q).mprint('%.2f')

# <markdowncell>

# We also have a convenience view method to get the Q and R matrices explicitly.

# <codecell>

B=pv.create('cmview_d',8,3).randn(10)
print('input B');B.mprint('%.2f')
Q,R=B.copy.qrd
print('Q');Q.mprint('%.2f')
print('R');R.mprint('%.2f'); 
print('Frobenius norm of difference of B-Q * R:  %.5f '%(Q.prod(R)-B).normFro)

# <codecell>


