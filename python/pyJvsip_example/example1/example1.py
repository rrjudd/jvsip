#* Created RJudd */
#* pyJvsip version of c_VSIP_example example1

import pyJvsip as pv
N=8
A = pv.create('vview_f',N).ramp(0,1)
B = A.empty.fill(5.0)
C = A.empty.fill(0.0)
print('A = ');A.mprint('%2.0f')
print('B = ');B.mprint('%2.0f')
pv.add(A,B,C)
print('C = A+B');
print('C = ');C.mprint('%2.0f')
