#!python
#Demonstrate submatrix by calculating a determinant.
#Check against include Determinant method
#NOTE myDet is not efficient. Keep N below 7 or 8
#make up some data
N=6
def myDet(A):
    m = A.collength
    det = 0
    if m == 1:
        return A[0,0]
    for i in range(m):
        det += A[0,i] * pow(-1,i) * myDet(A.submatrix(0,i))
    return det
#create a matrix
A=pv.create('mview_d',N,N).fill(-1.0)
A.diagview(0).ramp(1,1.1)
A.diagview(1).fill(2)
A.diagview(-1).fill(2)


