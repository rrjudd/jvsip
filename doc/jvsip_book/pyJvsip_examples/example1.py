import pyJvsip as pv
N=6
A = pv.create('vview_f',N).ramp(0,1)
B = A.empty.fill(5.0)
C = A.empty.fill(0.0)
print('A = '+A.mstring('%+2.0f'))
print('B = '+B.mstring('%+2.0f'))
pv.add(A,B,C)
print('C = A+B') 
print('C = '+C.mstring('%+2.0f'))
""" OUTPUT
A = [ 0  1  2  3  4  5  6  7]

B = [ 5  5  5  5  5  5  5  5]

C = A+B
C = [ 5  6  7  8  9  10  11  12]
"""
