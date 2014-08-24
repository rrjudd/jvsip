import pyJvsip as pjv
from math import pi as pi
n=1000
x=pjv.create('vview_d',n).ramp(0,2*pi/float(n))
c=pjv.cos(x,x.empty)
cClip=pjv.clip(c,-.9,.9,-.8,.8,c.empty)
