import pyJvsip as pjv

# Elementwise add using columns. 
# This is just to demo pyJvsip API features. There is no good reason to actually use this code

def madd(A,B,C):
    assert 'pyJvsip.__View' in repr(A),'Input parameters must be views of type pyJvsip.__View.'
    assert type(A) == type(B) and type(A) == type(C),'Input paramteters must be the same type'
    assert 'mview' in A.type,'Only matrix views are supported for madd.'
    L = A.rowlength
    a = A.colview
    b = B.colview
    c = C.colview
    for i in range(L):
        pjv.add(a(i),b(i),c(i))
    return C
a = pjv.create('vview_d',50)
b = pjv.create('vview_d',50)
c = pjv.create('vview_d',50)
A=a.block.bind(0,4,3,1,4)
B=b.block.bind(0,4,3,1,4)
C=c.block.bind(0,4,3,1,4)
a.ramp(0.0,.01)
b.ramp(0.0,1.0)
madd(A,B,C);
print('A = ');        A.mprint('%.2f')
print('B= ');         B.mprint('%.2f')
print("A + B = C = ");C.mprint('%.2f')
