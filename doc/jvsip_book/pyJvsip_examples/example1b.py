import pyJvsip as pv
N=6
A = pv.create('cvview_d',N).randn(7)
B = A.empty.fill(5.0)
C = A.empty.fill(0.0)
print('A = '+A.mstring('%+.2f'))
print('B = '+B.mstring('%+.2f'))
pv.add(A,B,C)
print('C = A+B') 
print('C = '+C.mstring('%+.2f'))
""" OUTPUT
A = [+0.16+0.50i -0.21-0.75i -0.56-0.09i \
     +1.15+0.45i +0.10+0.43i +0.63-1.05i]

B = [+5.00+0.00i +5.00+0.00i +5.00+0.00i \
     +5.00+0.00i +5.00+0.00i +5.00+0.00i]

C = A+B
C = [+5.16+0.50i +4.79-0.75i +4.44-0.09i \
     +6.15+0.45i +5.10+0.43i +5.63-1.05i]
"""
