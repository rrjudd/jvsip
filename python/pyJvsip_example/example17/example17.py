import pyJvsip as pjv
from math import pi as pi
L=50 # A length
aBlock = pjv.Block('block_d',L)
a=aBlock.bind(0,1,L).fill(0.0)
b=a.empty.ramp(0.0,2.0*pi/float(L-1)).cos
ab_bl = b.lgt(a)
assert ab_bl.anytrue,'No true values in boolean vector.'
ab_vi=ab_bl.indexbool
pjv.gather(b,ab_vi,a.putlength(ab_vi.length))
b.fill(0.0)
pjv.scatter(a,b,ab_vi)
for i in range(L):
    print('%.3f'%b[i])
