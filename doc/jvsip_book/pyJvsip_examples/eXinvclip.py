import pyJvsip as pjv
from math import pi as pi
n=1000
x=pjv.create('vview_d',n).ramp(0,2*pi/float(n))
c=pjv.cos(x,x.empty)
cinvClip=pjv.invclip(c,-.6,0.0,.6,-.7,.7,c.empty)
