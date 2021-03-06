# run some matrices to see if the SVD works
import pyJvsip as pv
from decompositionUtilities import *
fmt='%.5f'
def checkBack(A,U,S,VH):
    chk=(A-U[:,0:S.length].prod(S.mmul(VH.copy.COL))).normFro
    print('%.7f'%chk)
    if chk < A.normFro/(A.rowlength * 1E10):
        print('SVD Decomposition appears to agree with input matrix')
    elif chk < A.normFro/(A.rowlength*1E5):
        print('SVD Decomposition appears to agree witin 5 decimal places')
    else:
        print('SVD Decomposition does not agree with input matrix')
 
print('\nTEST')
A=pv.create('cmview_d',9,7).fill(0.0)
A.block.vector.realview.randn(3)
A.block.vector.imagview.randn(7)
U,S,VH = svd(A)
checkBack(A,U,S,VH)
print('Singular values are');S.mprint(fmt)
print('for matrix of type ' + A.type);A.mprint(fmt)
print('%.7f, %.7f'%(A.normFro,S.normFro))
print('Frobenius norm difference %.10e'%abs(A.normFro - S.normFro))

print('\nTEST')
A=pv.create('cmview_f',7,7).fill(0.0)
A.block.vector.realview.randn(3)
A.block.vector.imagview.randn(7)
A[:,0]=A[:,4];
A[:,1] = 3 * A[:,4]
U,S,VH = svd(A)
checkBack(A,U,S,VH)
print('Singular values are');S.mprint(fmt)
print('for matrix of type ' + A.type);A.mprint(fmt)
print('%.7f, %.7f'%(A.normFro,S.normFro))
print('Frobenius norm difference %.10e'%abs(A.normFro - S.normFro))

print('\nTEST')
A=pv.create('cmview_d',9,7).fill(0.0)
A.diagview(0).randn(5)
A.diagview(1).randn(7)
A[2,2]=0.0; A[4,4]=0.0
U,S,VH = svd(A)
checkBack(A,U,S,VH)
print('Singular values are');S.mprint(fmt)
print('for matrix of type ' + A.type);A.mprint(fmt)
print('%.7f, %.7f'%(A.normFro,S.normFro))
print('Frobenius norm difference %.10e'%abs(A.normFro - S.normFro))

print('\nTEST')
A=pv.create('mview_d',5,5).fill(0.0)
A.block.vector.randn(19)
U,S,VH=svd(A)
checkBack(A,U,S,VH)
print('Singular values are');S.mprint(fmt)
print('for matrix of type ' + A.type);A.mprint(fmt)
print('%.7f, %.7f'%(A.normFro,S.normFro))
print('Frobenius norm difference %.10e'%abs(A.normFro - S.normFro))
