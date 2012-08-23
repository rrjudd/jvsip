#!python
# Motivation
# Demonstrate submatrix by calculating a determinant.
# Check against included det method
import pyJvsip as pv
import timeit
# NOTE myDet is not efficient. Keep N below 7 or 8
N=6
# Function myDet uses definition of Determinant in most Linear Algebra Texts
# by expansion of cofactors along a row 
def myDet(A):
    m = A.collength
    det = 0
    if m == 1:
        return A[0,0]
    for i in range(m):
        det += A[0,i] * pow(-1,i) * myDet(A.submatrix(0,i))
    return det
# For example we need some data so we Create a non-singular matrix 'A'
A=pv.create('mview_d',N,N).fill(-1.0)
A.diagview(0).ramp(1,1.1)
A.diagview(1).fill(2)
A.diagview(-1).fill(2)
# Find the determinant with pyJvsip det method
d0=A.copy.det
# Find the determinant using myDet funciton
d1=myDet(A)
#compare
print('difference d0 - d1 = %f - %f = %f'%(d0,d1,d0-d1))
# Below we do some timing measureents to show inefficiency of myDet.
sMyDet='def myDet(A):\n    m = A.collength\n    det = 0\n    if m == 1:\n'
sMyDet+='        return A[0,0]\n    for i in range(m):\n'
sMyDet+='        det += A[0,i] * pow(-1,i) * myDet(A.submatrix(0,i))\n    return det\n'
Amake='A=pv.create(\'mview_d\',N,N).fill(-1.0)\n'
Amake +='A.diagview(0).ramp(1,1.1);A.diagview(1).fill(2);A.diagview(-1).fill(2)\n'
s='N=6\n'+sMyDet+Amake+'myDet(A)\n'
t=timeit.timeit(s,'import pyJvsip as pv',number=5)/5.0
print('Time for calculating myDet using N=6 is %f seconds'%(t))
s='N=6\n'+Amake+'A.det\n'
t=timeit.timeit(s,'import pyJvsip as pv',number=50)/50.0
print('Time for calculating A.det using N=6 is %f seconds'%(t))
