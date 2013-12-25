import pyJvsip as pv
from math import sqrt
from svdBidiag import svdBidiag

def svdCorners(f):
    j=f.length-1
    while  j > 0 and f[j] == 0.0:
        j-=1
    if(j == 0 and f[j] == 0.0):
        i=0
    else:
        i = j
        while i > 0 and f[i] != 0.0:
            i -= 1

        if i==0 and f[0] == 0.0:
            i = 1
            j += 2
        elif i == 0 and f[0] != 0.0:
            i = 0
            j += 2

        else:
            i += 1
            j += 2
    return (i,j)

def givensCoef(x1, x2):
    a=abs(x1);b=abs(x2)
    if x2 == 0.0:
        return(1.0,0.0,x1)
    elif a < b:
        t = x1/x2
        t = b * sqrt(1.0 + t * t)
    else:
        t=x2/x1
        t = a * sqrt(1.0 + t * t)
    if (x1 == 0.0):
        c=0.0
        if x2 < 0:
            s = -1.0
        else:
            s = 1.0
        return(c,s,t)
    else:
        s = x2/t
        c = abs(x1)/t
        if x1 < 0:
            s = -s
            t=-t
        return(c,s,t)

def prodG(L,i,j,c,s):
    a1= L.colview(i)
    a2= L.colview(j)
    t    = c * a1 + s * a2
    a2[:]= c * a2 - s * a1
    a1[:]= t

def gtProd(i,j,c,s,R):
    a1= R.rowview(i)
    a2= R.rowview(j)
    t= c * a1 + s * a2
    a2[:]=c * a2 - s * a1
    a1[:]=t

def zeroRow(L,d,f):
    n = d.length
    xd=d[0]
    xf=f[0]
    c,s,r=givensCoef(xd,xf)
    if n == 1:
        d[0]=r
        f[0]=0.0
        prodG(L,n,0,c,s)
    else:
        d[0]=r
        f[0]=0.0
        xf=f[1]
        t= -xf * s; xf *= c
        f[1]=xf
        prodG(L,1,0,c,s);
        for i in range(1,n-1):
            xd=d[i]
            c,s,r=givensCoef(xd,t)
            prodG(L,i+1,0,c,s)
            d[i]=r
            xf=f[i+1]
            t=-xf * s; xf *= c
            f[i+1]=xf
        xd=d[n-1]
        c,s,r=givensCoef(xd,t)
        d[n-1]=r
        prodG(L,n,0,c,s)

def zeroCol(d,f,R):
    n = f.length
    if n == 1:
        c,s,r=givensCoef(d[0],f[0]);
        d[0]=r;
        f[0]=0.0;
        gtProd(0,1,c,s,R)
    elif n == 2:
        xd=d[1]
        xf=f[1]
        c,s,r=givensCoef(xd,xf)
        d[1]= r
        f[1]=0.0
        xf=f[0]
        t= -xf * s; xf *= c;
        f[0]=xf;
        gtProd(1,2,c,s,R);
        xd=d[0]
        c,s,r=givensCoef(xd,t);
        d[0]=r;
        gtProd(0,2,c,s,R);
    else:
        i=n-1; j=i-1; k=i
        xd=d[i]
        xf=f[i]
        c,s,r=givensCoef(xd,xf);
        xf=f[j]
        d[i]=r;
        f[i]=0.0;
        t=-xf*s; xf*=c
        f[j]=xf;
        gtProd(i,k+1,c,s,R);
        while i > 1:
            i = j; j = i-1;
            xd=d[i]
            c,s,r=givensCoef(xd,t);
            d[i]=r;
            xf=f[j]
            t= -xf * s; xf *= c;
            f[j]=xf;
            gtProd(i,k+1,c,s,R);
        xd=d[0]
        c,s,r=givensCoef(xd,t)
        d[0]=r
        gtProd(0,k+1,c,s,R)

def zeroFind(d,eps0):
    j = d.length
    xd = d[j-1]
    while xd > eps0:
        if j > 1:
            j -= 1
            xd=d[j-1]
        elif j==1:
            j -= 1
            return 0
    d[j-1]=0.0
    return j

def svdMu(d2,f1,d3,f2, eps0):
    cu=d2 * d2 + f1 * f1
    cl=d3 * d3 + f2 * f2
    cd = d2 * f2;
    T = (cu + cl)
    D = 4*(cu * cl - cd * cd)/(T*T)
    if D >= 1.0:
        root = 0.0
    else:
        root = T * sqrt(1.0 - D)
    lambda1 = (T + root)/(2.)
    lambda2 = (T - root)/(2.)
    c1=abs(lambda1-cl)
    c2=abs(lambda2-cl)
    if(root == 0.0):
        if f2 < (d2 + d3) * eps0:
            f2=0.0
    if(c1 < c2):
        mu = lambda1
    else:
        mu = lambda2
    return (mu, f2)

def checksvd(L,d,f,R):
    B=pv.create(L.type,L.collength,R.rowlength).fill(0.0)
    if 'cmview' in B.type:
        b=B.realview.diagview
    else:
        b=B.diagview
    b(0)[:]=d
    b(1)[:]=f
    L.prod(B).prod(R).mprint('%.3f')

def svdStep(L,d,f,R, eps0):
    n = d.length
    mu=0.0; x1=0.0; x2=0.0; t=0.0
    d2=0.0; f1=0.0; d3=0.0; f2=0.0
    assert n > 1, 'Error. d.length for svdStep must be at least 2'
    if n >= 3:
        d2=d[n-2];f1= f[n-3];d3 = d[n-1];f2= f[n-2]
    else:
        d2=d[0]; d3=d[1]; f1=0.0; f2=f[0]
    mu, f2 = svdMu(d2, f1, d3, f2, eps0)
    if(f2 == 0.0):
        f[n-2] = 0.0
    x1=d[0]
    x2 = x1 * f[0]
    x1 *= x1; x1 -= mu
    c,s,r=givensCoef(x1,x2)
    x1=d[0];x2=f[0]
    f[0]=c*x2-s*x1
    d[0]=c*x1+s*x2
    t=d[1]
    d[1] *= c
    t *= s
    gtProd(0,1,c,s,R)
    for i in range(n-2):
        j=i+1; k=i+2
        c,s,r = givensCoef(d[i],t)
        d[i]=r
        x1=d[j]*c
        x2=f[i]*s
        t= x1 - x2
        x1=f[i] * c
        x2=d[j] * s
        f[i] = x1+x2
        d[j] = t
        x1=f[j]
        t=s * x1
        f[j]=x1*c
        prodG(L,i, j, c, s)
        c,s,r=givensCoef(f[i],t)
        f[i]=r
        x1=d[j]; x2=f[j]
        d[j]=c * x1 + s * x2; f[j]=c * x2 - s * x1
        x1=d[k]
        t=s * x1; d[k]=x1*c
        gtProd(j,k, c, s,R)
    i=n-2; j=n-1
    c,s,r = givensCoef(d[i],t)
    d[i] = r
    x1=d[j]*c; x2=f[i]*s
    t=x1 - x2
    x1 = f[i] * c; x2=d[j] * s
    f[i] = x1+x2
    d[j] = t
    prodG(L,i, j, c, s)

def phaseCheck(L,d,f,R,eps0):
    nf=f.length;
    for i in range(d.length):
        ps=d[i]
        m = abs(ps)
        if(m >= eps0) and ps < 0.0:
            L.colview(i).neg
            d[i]=m;
            if (i < nf):
                f[i] = -f[i]
        elif m < eps0:
            d[i]=0.0
    for i in range(nf):
        if abs(f[i]) < (d[i] + d[i+1]) * eps0:
            f[i]=0.0


def svdIteration(L0,d0,f0,R0,eps0):
    cntr=0.0
    maxcntr = 5 * d0.length
    while (cntr < maxcntr):
        cntr += 1
        i,j=svdCorners(f0)
        if (j == 0):
            break
        d=d0[i:j]; f=f0[i:j-1]
        L=L0[:,i:j];R=R0[i:j,:]
        n=f.length
        k=zeroFind(d,eps0)
        if (k > 0 ):
            k=k-1;
            if(d[n] == 0.0):
                zeroCol(d,f,R);
            else:
                L=L[:,k:]
                d.putlength(d.length-(k+1))
                d.putoffset(d.offset+k+1)
                f.putlength(f.length - k)
                f.putoffset(f.offset + k)
                zeroRow(L,d,f)
        else:
            svdStep(L,d,f,R, eps0)
        phaseCheck(L0,d0,f0,R0,eps0)
    return (L0,d0,R0)
