import pyJvsip as pv
N=6
A = pv.create('vview_f',N).randn(7)
B = A.empty.fill(5.0)
C = A.empty.fill(0.0)
print('A = '+A.mstring('%+.2f'))
print('B = '+B.mstring('%+.2f'))
pv.add(A,B,C)
print('C = A+B') 
print('C = '+C.mstring('%+.2f'))
""" OUTPUT
A = [-0.05 +0.59 +0.73 -0.37 -0.21 -0.83]

B = [+5.00 +5.00 +5.00 +5.00 +5.00 +5.00]

C = A+B
C = [+4.95 +5.59 +5.73 +4.63 +4.79 +4.17]
"""
