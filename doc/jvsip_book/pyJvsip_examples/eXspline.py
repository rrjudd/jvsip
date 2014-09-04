import pyJvsip as pjv
from math import pi as pi
from matplotlib.pyplot import *
#make up some data for vector interpolation
x0=pjv.ramp('vview_d',0.0,2*pi/10,11)
y0=pjv.sin(x0,x0.empty)
#make up an interpolation vector and output
x=pjv.ramp('vview_d',0.0,2*pi/250,251)
yEstimate=x.empty
#interploate
spln=pjv.Spline(x0.type,400)
spln.interpolate(x0,y0,x,yEstimate)
#calculate actual
yActual=pjv.sin(x,x.empty)
#plot the data and save as pdf
subplot(3,1,1)
plot(x0,y0);title('Sparse Sine')
tick_params(axis='x',labelbottom='off')
for i in range(x0.length):
    text(x0[i],y0[i],'|',verticalalignment='center',horizontalalignment='center')
subplot(3,1,2)
plot(x,yEstimate);title('Estimate of Dense Sine')
tick_params(axis='x',labelbottom='off')
subplot(3,1,3)
plot(x,yEstimate-yActual);title('Error in Dense Sine')
#plot zero line. There should be at least 11 zero errors
plot(x,yActual.fill(0.0))
xlabel('Radian Values')
for i in range(x0.length):
    text(x0[i],0,'|',verticalalignment='center',horizontalalignment='center')
tight_layout()
savefig('eXspline.pdf',figsize=(3,7))
