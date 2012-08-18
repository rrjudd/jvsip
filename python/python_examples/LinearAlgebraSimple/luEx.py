#!python
# Example of solving Ax=b using LU
import pyJvsip as pv
import cProfile
#create a non-singular matrix
def mySolve(A,x):
    p,l,u=A.plu
    u.usolve(l.lsolve(x.permute(p)))
N=100
A=pv.create('mview_d',N,N).fill(-1.0)
A.diagview(0).ramp(1,1.1)
A.diagview(1).fill(2)
A.diagview(-1).fill(2)
#create a test 'good x' vector
x0=pv.create('vview_d',A.rowlength).ramp(.1,.1)
# create and calculate a y vector based on x vector
y0=A.prod(x0)
#Create a copy of y0 to solve for x0
xy=y0.copy
#check to make sure A non-singular. Det uses up A so make copy 
if A.copy.det < .0001:
    print('Matrix may be singular')
#solve longhand using plu and triangular backsolverssolvers (mySolve Above)
print('RESULTS for mySolve function using plu method and backsolvers')
cProfile.run('mySolve(A,xy)')
#check to see if xy is x0
chk=(xy-x0).sumsqval
if chk > .000001:
    print('We don\'t seem to have the right answer using mySolve; check=%e'%chk)
else:
    print('Check only %e. This is probably correct for mySolve function'%chk)
#Solve using luSolve method. Make copy of A so we con't overwrite it
xy=y0.copy
print('\nRESULTS using VSIPL LUD solver methods')
cProfile.run('A.copy.luSolve(xy)')
chk = (xy-x0).sumsqval
chk=(xy-x0).sumsqval
if chk > .000001:
    print('We don\'t seem to have the right answer using luSolve method; check=%e'%chk)
else:
    print('Check is %e. This is probably correct for luSolve method'%chk)