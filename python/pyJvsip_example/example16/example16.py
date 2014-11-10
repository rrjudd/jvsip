import pyJvsip as pjv
from math import pi as pi
view=pjv.create
L = 20 # A length
a = view('vview_d',L).ramp(0.0,2.0*pi/float(L-1))
b = a.empty
ab_bl=view('vview_bl',L)
pjv.cos(a,b)
a.fill(0.0)
pjv.lgt(b,a,ab_bl)
assert ab_bl.anytrue, 'No true values in boolean vector'
ab_vi = ab_bl.indexbool
pjv.gather(b,ab_vi,a.putlength(ab_vi.length))
print(repr([(ab_vi[i], a[i]) for i in range(ab_vi.length)]))
