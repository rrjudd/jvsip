import pyJvsip as pjv
L = 9
a=pjv.create('vview_f',L);
b=a.empty
ab_bl=pjv.create('vview_bl',L);
a.ramp(-2.0,1)
b.ramp(2.0,-1)
print('index    A       B\n')
for i in range(L):
    print('%3i %7.1f %7.1f\n'%(i,a[i],b[i]))
_=pjv.leq(a,b,ab_bl)
if ab_bl.anytrue:
    ab_vi=ab_bl.indexbool
    for i in range(ab_vi.length):
        print('A = B at index %3i\n'%int(ab_vi[i]))
else:
    print('No true cases')
