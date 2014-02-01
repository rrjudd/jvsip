"""
Example of debugging c file using vsip module. Code was developed in pyJvsip. When
working it was converted to c. To aid in debugging C code was converted back
to python using just the vsip module.
Counterpart file of svd_f.c (and svd_f.h)
Note:
In C we have typedef struct { } newType;
Here we have instead classes defined. See svdCorner, givensObj_f and svdObj_f for examples.
"""
from vsip import *
def msv_f(B, BS, i,j):
    attr = vsip_mattr_f()
    vsip_mgetattrib_f(B,attr)
    attr.row_length -= j
    attr.col_length -= i
    attr.offset += j * attr.row_stride + i * attr.col_stride
    vsip_mputattrib_f(BS,attr)
    return BS
def vsv_f( v, vs, i):
     attr = vsip_vattr_f()
     vsip_vgetattrib_f(v,attr)
     attr.offset += i * attr.stride
     attr.length -= i
     vsip_vputattrib_f(vs,attr)
     return vs
def col_sv_f(Am,vv,col):
    A = vsip_mattr_f() 
    v = vsip_vattr_f()
    vsip_mgetattrib_f(Am, A)
    v.offset = A.offset + col * A.row_stride
    v.stride = A.col_stride
    v.length = A.col_length
    vsip_vputattrib_f(vv,v)
    return vv
def row_sv_f(Am,vv,row):
    A= vsip_mattr_f()
    v= vsip_vattr_f()
    vsip_mgetattrib_f(Am,A)
    v.offset = A.offset + row * A.col_stride
    v.stride = A.row_stride
    v.length = A.row_length
    vsip_vputattrib_f(vv,v)
    return vv
def imsv_f( B, BS, i1,j1, i2, j2):
    attr = vsip_mattr_f() 
    vsip_mgetattrib_f(B,attr)
    if(j1 == 0):
       j1 =attr.col_length
    if(j2 == 0):
       j2 =attr.row_length
    attr.col_length = (j1 - i1)
    attr.row_length = (j2 - i2)
    attr.offset += i2 * attr.row_stride + i1 * attr.col_stride
    vsip_mputattrib_f(BS,attr)
    return BS
def ivsv_f(v, vs, i,j):
     attr = vsip_vattr_f()
     vsip_vgetattrib_f(v,attr)
     if(j==0):
        j=attr.length
     attr.offset += i * attr.stride
     attr.length = j-i
     vsip_vputattrib_f(vs,attr)
     return vs
def diag_sv_f(Am,a, i):
    A = vsip_mattr_f() 
    v = vsip_vattr_f()
    vsip_mgetattrib_f(Am,A)
    vsip_vgetattrib_f(a,v)
    v.stride=A.row_stride + A.col_stride
    if(i==0):
       v.length = A.row_length
       v.offset = A.offset
    elif (i == 1):
        v.offset = A.offset + A.row_stride
        v.length = A.row_length - 1
    else :
        print("Failed in diag_sv_f\n")
    vsip_vputattrib_f(a,v)
    return a
def vclone_f(x, v):
    vsip_vputlength_f(v,vsip_vgetlength_f(x))
    vsip_vcopy_f_f(x,v)
    return v
def meye_f(n):
    retval = vsip_mcreate_f(n,n,VSIP_ROW,VSIP_MEM_NONE)
    d = vsip_mdiagview_f(retval,0)
    vsip_mfill_f(0.0,retval)
    vsip_vfill_f(1.0,d)
    vsip_vdestroy_f(d)
    return retval

def sign_f(a_in):
    if(a_in < 0.0):
       return -1.0
    else: 
       return 1.0

def vnormFro_f(v):
    return vsip_sqrt_f(vsip_vsumsqval_f(v))

def vnorm2_f(v):
    return vnormFro_f(v)

def mnormFro_f(v):
    return vsip_sqrt_f(vsip_msumsqval_f(v))


def gtProd_f(i, j, c,s, svd):
    R = svd.Rs
    a1= row_sv_f(R,svd.rs_one, i)
    a2= row_sv_f(R,svd.rs_two, j)
    a1c=vclone_f(a1,svd.t)
    vsip_svmul_f(c,a1c,a1); vsip_vsma_f(a2,s,a1,a1)
    vsip_svmul_f(-s,a1c,a1c); vsip_vsma_f(a2,c,a1c,a2)


def prodG_f(svd,i, j,c, s):
    L = svd.Ls
    a1= col_sv_f(L,svd.ls_one,i)
    a2= col_sv_f(L,svd.ls_two,j)
    a1c=vclone_f(a1,svd.t)
    vsip_svmul_f(c,a1c,a1); vsip_vsma_f(a2,s,a1,a1)
    vsip_svmul_f(-s,a1c,a1c);vsip_vsma_f(a2,c,a1c,a2)


def houseVector_f(x):
    nrm=vnorm2_f(x)
    t = vsip_vget_f(x,0)
    s = t +  sign_f(t) * nrm
    vsip_vput_f(x,0,s)
    nrm = vnorm2_f(x)
    if (nrm == 0.0):
        vsip_vput_f(x,0,1.0)
    else:
        vsip_svmul_f(1.0/nrm,x,x)
    return x

def prodHouse_f(A, v):
    a_atr = vsip_mattr_f()
    vsip_mgetattrib_f(A,a_atr)
    B=vsip_mcreate_f(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE)
    w = vsip_vcreate_f(a_atr.col_length,VSIP_MEM_NONE)
    beta = 2.0/vsip_vdot_f(v,v)
    vsip_mvprod_f(A,v,w)
    vsip_vouter_f(beta,w,v,B)
    vsip_msub_f(A,B,A)
    vsip_valldestroy_f(w)
    vsip_malldestroy_f(B)

def  houseProd_f(v, A):
    a_atr = vsip_mattr_f()
    vsip_mgetattrib_f(A,a_atr)
    B=vsip_mcreate_f(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE)
    w = vsip_vcreate_f(a_atr.row_length,VSIP_MEM_NONE)
    beta = 2.0/vsip_vdot_f(v,v)
    vsip_vmprod_f(v,A,w)
    vsip_vouter_f(beta,v,w,B)
    vsip_msub_f(A,B,A)
    vsip_valldestroy_f(w)
    vsip_malldestroy_f(B)

def bidiag_f(svd):
    B = svd.B
    Bs = svd.Bs
    m = vsip_mgetcollength_f(B)
    n = vsip_mgetrowlength_f(B)
    x=col_sv_f(B,svd.bs,0)
    v=vclone_f(x,svd.t)
    vs = svd.ts
    for i in range(n-1):
        vsip_vputlength_f(v,m-i)
        vsip_vcopy_f_f(col_sv_f(msv_f(B,Bs,i,i),x,0),v)
        houseVector_f(v)
        vsip_svmul_f(1.0/vsip_vget_f(v,0),v,v)
        houseProd_f(v,Bs)
        vsip_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1))
        if(i < n-2):
            j = i+1
            vsip_vputlength_f(v,n-j)
            vsip_vcopy_f_f(row_sv_f(msv_f(B,Bs,i,j),x,0),v)
            houseVector_f(v)
            vsip_svmul_f(1.0/vsip_vget_f(v,0),v,v)
            prodHouse_f(Bs,v)
            vsip_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1))
    if(m > n):
        i=n-1
        vsip_vputlength_f(v,m-i)
        vsip_vcopy_f_f(col_sv_f(msv_f(B,Bs,i,i),x,0),v)
        houseVector_f(v)
        vsip_svmul_f(1.0/vsip_vget_f(v,0),v,v)
        houseProd_f(v,Bs)
        vsip_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1))
def UmatExtract_f(svd):
    B=svd.B
    U=svd.L
    m = vsip_mgetcollength_f(B)
    n = vsip_mgetrowlength_f(B)
    Bs=svd.Bs
    Us=svd.Ls
    v = col_sv_f(B,svd.bs,0)
    if (m > n):
        i=n-1
        col_sv_f(msv_f(B,Bs,i,i),v,0)
        t=vsip_vget_f(v,0); vsip_vput_f(v,0,1.0)
        houseProd_f(v,msv_f(U,Us,i,i))
        vsip_vput_f(v,0,t)
    for i in range(n-2,-1,-1):
        col_sv_f(msv_f(B,Bs,i,i),v,0)
        t=vsip_vget_f(v,0); vsip_vput_f(v,0,1.0)
        houseProd_f(v,msv_f(U,Us,i,i))
        vsip_vput_f(v,0,t)

def VHmatExtract_f(svd):
    B = svd.B
    n = vsip_mgetrowlength_f(B)
    Bs=svd.Bs
    V=svd.R
    Vs=svd.Rs
    if(n < 3):
        return
    v = row_sv_f(B,svd.bs,0)
    for i in range(n-3,-1,-1):
        j=i+1
        row_sv_f(msv_f(B,Bs,i,j),v,0)
        t=vsip_vget_f(v,0);vsip_vput_f(v,0,1.0)
        prodHouse_f(msv_f(V,Vs,j,j),v)
        vsip_vput_f(v,0,t)


def svdZeroCheckAndSet_f(e, b0, b1):
    n = vsip_vgetlength_f(b1)
    z = 0.0
    for i in range(n):
        b = vsip_mag_f(vsip_vget_f(b1,i))
        a = e*(vsip_mag_f(vsip_vget_f(b0,i))
                        +    vsip_mag_f(vsip_vget_f(b0,i+1)))
        if( b < a ): 
            vsip_vput_f(b1,i,z)

def biDiagPhaseToZero_f( svd):
    L = svd.L
    d = svd.d
    f = svd.f
    R = svd.R
    eps0 = svd.eps0
    n_d=vsip_vgetlength_f(d)
    n_f=vsip_vgetlength_f(f)
    l = svd.ls_one
    r = svd.rs_one
    for i in range(n_d):
        ps=vsip_vget_f(d,i)
        m = vsip_mag_f(ps)
        ps=sign_f(ps)
        if(m > eps0):
            col_sv_f(L,l,i);vsip_svmul_f(ps,l,l)
            vsip_vput_f(d,i,m)
            if (i < n_f):
                vsip_vput_f(f,i,ps*vsip_vget_f(f,i))
        else:
            vsip_vput_f(d,i,0.0)
    svdZeroCheckAndSet_f(eps0,d,f)
    for i in range(n_f-1):
        j=i+1
        ps = vsip_vget_f(f,i)
        m = vsip_mag_f(ps)
        ps=sign_f(ps)
        col_sv_f(L, l, j);vsip_svmul_f(ps,l,l)
        row_sv_f(R,r,j);vsip_svmul_f(ps,r,r)
        vsip_vput_f(f,i,m)
        vsip_vput_f(f,j,ps * vsip_vget_f(f,j))
    j=n_f
    i=j-1
    ps=vsip_vget_f(f,i)
    m=vsip_mag_f(ps)
    ps=sign_f(ps)
    vsip_vput_f(f,i,m)
    col_sv_f(L, l, j);vsip_svmul_f(ps,l,l)
    row_sv_f(R,r,j);vsip_svmul_f(ps,r,r)
def svdBidiag_f(svd):
    B = svd.B
    sv = mnormFro_f(B)/vsip_mgetrowlength_f(B)
    bidiag_f(svd)
    vsip_vcopy_f_f(diag_sv_f(B,svd.bs,0),svd.d)
    vsip_vcopy_f_f(diag_sv_f(B,svd.bs,1),svd.f)
    UmatExtract_f(svd)
    VHmatExtract_f(svd)
    svd.eps0=sv*1E-10
    biDiagPhaseToZero_f(svd)
def givensCoef_f(x1, x2):
    retval = givensObj_f()
    t = vsip_hypot_f(x1,x2)
    if (x2 == 0.0):
        retval.c=1.0;retval.s=0.0;retval.r=x1
    elif (x1 == 0.0):
        retval.c=0.0;retval.s=sign_f(x2);retval.r=t
    else:
        sn = sign_f(x1)
        retval.c=vsip_mag_f(x1)/t;retval.s=sn*x2/t; retval.r=sn*t
    return retval

def svdCorners_f(f):
    crnr = svdCorner()
    j=vsip_vgetlength_f(f)-1
    while((j > 0) and (vsip_vget_f(f,j) == 0.0)):
        j-=1
    if(j == 0 and vsip_vget_f(f,0) == 0.0):
        crnr.i=0
        crnr.j=0
    else: 
        i = j
        j += 1
        while((i > 0) and (vsip_vget_f(f,i) != 0.0)):
            i -= 1
        if((i == 0) and (vsip_vget_f(f,0)== 0.0)):
            crnr.i=1
            crnr.j=j+1
        elif (i==0):
            crnr.i=0
            crnr.j=j+1
        else: 
            crnr.i=i+1
            crnr.j=j+1
    return crnr

def phaseCheck_f(svd):
    biDiagPhaseToZero_f(svd)

def zeroFind_f(d, eps0):
    j = vsip_vgetlength_f(d)
    xd=vsip_vget_f(d,j-1)
    while(xd > eps0):
        if (j > 1):
            j -= 1
            xd=vsip_vget_f(d,j-1)
        else:
            break
    if(xd <= eps0):
        vsip_vput_f(d,j-1,0.0)
    if (j == 1):
        j=0
    return j

def zeroRow_f(svd):
    L = svd.Ls
    d = svd.ds
    f = svd.fs
    n = vsip_vgetlength_f(d)
    g = givensObj_f()
    xd=vsip_vget_f(d,0)
    xf=vsip_vget_f(f,0)
    g=givensCoef_f(xd,xf)
    if (n == 1):
        vsip_vput_f(f,0,0.0)
        vsip_vput_f(d,0,g.r)
    else:
        vsip_vput_f(f,0,0.0)
        vsip_vput_f(d,0,g.r)
        xf=vsip_vget_f(f,1)
        t= -xf * g.s; xf *= g.c
        vsip_vput_f(f,1,xf)
        prodG_f(svd,1,0,g.c,g.s)
        for i in range(1,n-1):
            xd=vsip_vget_f(d,i)
            g=givensCoef_f(xd,t)
            prodG_f(svd,i+1,0,g.c,g.s)
            vsip_vput_f(d,i,g.r)
            xf=vsip_vget_f(f,i+1)
            t=-xf * g.s; xf *= g.c
            vsip_vput_f(f,i+1,xf)
        xd=vsip_vget_f(d,n-1)
        g=givensCoef_f(xd,t)
        vsip_vput_f(d,n-1,g.r)
        prodG_f(svd,n,0,g.c,g.s)
def zeroCol_f(svd):
    d=svd.ds
    f=svd.fs
    R=svd.Rs
    n = vsip_vgetlength_f(f)
    g = givensObj_f()
    if (n == 1):
        xd=vsip_vget_f(d,0)
        xf=vsip_vget_f(f,0)
        g=givensCoef_f(xd,xf)
        vsip_vput_f(d,0,g.r)
        vsip_vput_f(f,0,0.0)
        gtProd_f(0,1,g.c,g.s,svd)
    elif (n == 2):
        xd=vsip_vget_f(d,1)
        xf=vsip_vget_f(f,1)
        g=givensCoef_f(xd,xf)
        vsip_vput_f(d,1,g.r)
        vsip_vput_f(f,1,0.0)
        xf=vsip_vget_f(f,0)
        t= -xf * g.s; xf *= g.c
        vsip_vput_f(f,0,xf)
        gtProd_f(1,2,g.c,g.s,svd)
        xd=vsip_vget_f(d,0)
        g=givensCoef_f(xd,t)
        vsip_vput_f(d,0,g.r)
        gtProd_f(0,2,g.c,g.s,svd)
    else:
        i=n-1; j=i-1; k=i
        xd=vsip_vget_f(d,i)
        xf=vsip_vget_f(f,i)
        g=givensCoef_f(xd,xf)
        xf=vsip_vget_f(f,j)
        vsip_vput_f(f,i,0.0)
        vsip_vput_f(d,i,g.r)
        t=-xf*g.s; xf*=g.c
        vsip_vput_f(f,j,xf)
        gtProd_f(i,k+1,g.c,g.s,svd)
        while (i > 1):
            i = j; j = i-1
            xd=vsip_vget_f(d,i)
            g=givensCoef_f(xd,t)
            vsip_vput_f(d,i,g.r)
            xf=vsip_vget_f(f,j)
            t= -xf * g.s; xf *= g.c
            vsip_vput_f(f,j,xf)
            gtProd_f(i,k+1,g.c,g.s,svd)
        xd=vsip_vget_f(d,0)
        g=givensCoef_f(xd,t)
        vsip_vput_f(d,0,g.r)
        gtProd_f(0,k+1,g.c,g.s,svd)
def svdMu_f(d2,f1,d3,f2):
    cu=d2 * d2 + f1 * f1
    cl=d3 * d3 + f2 * f2
    cd = d2 * f2
    D = (cu * cl - cd * cd)
    T = (cu + cl)
    root = vsip_sqrt_f(T*T - 4 * D)
    lambda1 = (T + root)/(2.)
    lambda2 = (T - root)/(2.)
    if(vsip_mag_f(lambda1 - cl) < vsip_mag_f(lambda2 - cl)):
        mu = lambda1
    else:
        mu = lambda2
    return mu

def svdStep_f(svd):
    L = svd.Ls
    d = svd.ds
    f = svd.fs
    R = svd.Rs
    g = givensObj_f()
    n = vsip_vgetlength_f(d)
    mu=0.0; x1=0.0; x2=0.0
    t=0.0
    if(n >= 3):
        d2=vsip_vget_f(d,n-2);f1= vsip_vget_f(f,n-3);d3 = vsip_vget_f(d,n-1);f2= vsip_vget_f(f,n-2)
    elif(n == 2):
        d2=vsip_vget_f(d,0);f1= 0.0;d3 = vsip_vget_f(d,1);f2= vsip_vget_f(f,0)
    else:
        d2=vsip_vget_f(d,0);f1 = 0.0;d3 = 0.0;f2 = 0.0
    mu = svdMu_f(d2,f1,d3,f2)
    x1=vsip_vget_f(d,0)
    x2 = x1 * vsip_vget_f(f,0)
    x1 *= x1; x1 -= mu
    g=givensCoef_f(x1,x2)
    x1=vsip_vget_f(d,0);x2=vsip_vget_f(f,0)
    vsip_vput_f(f,0,g.c * x2 - g.s * x1)
    vsip_vput_f(d,0,x1 * g.c + x2 * g.s)
    t=vsip_vget_f(d,1); vsip_vput_f(d,1,t*g.c)
    t*=g.s
    gtProd_f(0,1,g.c,g.s,svd)
    for i in range(n-2):
        j=i+1; k=i+2
        g = givensCoef_f(vsip_vget_f(d,i),t)
        vsip_vput_f(d,i,g.r)
        x1=vsip_vget_f(d,j)*g.c
        x2=vsip_vget_f(f,i)*g.s
        t= x1 - x2;       
        x1=vsip_vget_f(f,i) * g.c
        x2=vsip_vget_f(d,j) * g.s
        vsip_vput_f(f,i,x1+x2)
        vsip_vput_f(d,j,t);       
        x1=vsip_vget_f(f,j)
        t=g.s * x1
        vsip_vput_f(f,j, x1*g.c)
        prodG_f(svd,i, j, g.c, g.s)
        g=givensCoef_f(vsip_vget_f(f,i),t)
        vsip_vput_f(f,i,g.r)
        x1=vsip_vget_f(d,j); x2=vsip_vget_f(f,j)
        vsip_vput_f(d,j,g.c * x1 + g.s * x2); vsip_vput_f(f,j,g.c * x2 - g.s * x1)
        x1=vsip_vget_f(d,k)
        t=g.s * x1; vsip_vput_f(d,k,x1*g.c)
        gtProd_f(j,k, g.c, g.s,svd)
    i=n-2; j=n-1
    g = givensCoef_f(vsip_vget_f(d,i),t)
    vsip_vput_f(d,i,g.r)
    x1=vsip_vget_f(d,j)*g.c; x2=vsip_vget_f(f,i)*g.s
    t=x1 - x2
    x1 = vsip_vget_f(f,i) * g.c; x2=vsip_vget_f(d,j) * g.s
    vsip_vput_f(f,i,x1+x2)
    vsip_vput_f(d,j,t)
    prodG_f(svd,i, j, g.c, g.s)

def svdIteration_f(svd):
    L0 = svd.L; L = svd.Ls
    d0 = svd.d; d = svd.ds
    f0 = svd.f; f = svd.fs
    R0 = svd.R; R= svd.Rs
    eps0 = svd.eps0
    cnr = svdCorner()
    cntr=0
    maxcntr=20*vsip_vgetlength_f(d0)
    while (cntr < maxcntr):
        cntr += 1
        phaseCheck_f(svd)
        cnr=svdCorners_f(f0)
        if (cnr.j == 0):
            break
        ivsv_f(d0,d,cnr.i,cnr.j)
        ivsv_f(f0,f,cnr.i,cnr.j-1)
        imsv_f(L0,L,0,0,cnr.i,cnr.j)
        imsv_f(R0,R,cnr.i,cnr.j,0,0)
        n=vsip_vgetlength_f(f)
        k=zeroFind_f(d,eps0)
        if (k > 0):
            if(vsip_vget_f(d,n) == 0.0):
                zeroCol_f(svd)
            else:
                imsv_f(L,L,0,0,k-1,0)
                ivsv_f(d0,d,k,0)
                ivsv_f(f0,f,k-1,0)
                zeroRow_f(svd)
        else:
            svdStep_f(svd)
def svdSort_f(svd):
    d = svd.d
    n=vsip_vgetlength_f(d)
    indx_L = svd.indx_L
    indx_R = svd.indx_R
    L0 = svd.L
    L=svd.Ls
    R0 = svd.R
    vsip_vsortip_f(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,1,indx_L)
    vsip_vcopy_vi_vi(indx_L,indx_R)
    imsv_f( L0, L, 0,0, 0, n)
    vsip_mpermute_once_f(L,VSIP_COL,indx_L,L)
    vsip_mpermute_once_f(R0,VSIP_ROW,indx_R,R0)

class svdCorner:
    def __init__(self):
        self.i=0
        self.j=0
class givensObj_f:
    def __init__(self):
        self.c=0.0
        self.s=0.0
        self.r=0.0
class svdObj_f:
    def __init__(self,m,n):
        if(m < n):
            print("Column length must not be less than row length")
            return
        self.t  = vsip_vcreate_f(m,VSIP_MEM_NONE)
        self.ts = vsip_vcloneview_f(self.t) 
        self.B=vsip_mcreate_f(m,n,VSIP_ROW,VSIP_MEM_NONE)
        self.Bs=vsip_mcloneview_f(self.B)
        self.bs=vsip_mrowview_f(self.B,0)
        self.L=meye_f(m)
        self.Ls = vsip_mcloneview_f(self.L)
        self.ls_two = vsip_mrowview_f(self.Ls,0)
        self.ls_one = vsip_mrowview_f(self.Ls,0)
        self.R=meye_f(n)
        self.Rs = vsip_mcloneview_f(self.R)
        self.rs_two = vsip_mrowview_f(self.Rs,0)
        self.rs_one = vsip_mrowview_f(self.Rs,0)
        self.indx_L=vsip_vcreate_vi(n,VSIP_MEM_NONE)
        self.indx_R=vsip_vcreate_vi(n,VSIP_MEM_NONE)
        self.d=vsip_vcreate_f(n,VSIP_MEM_NONE);
        self.f=vsip_vcreate_f(n-1,VSIP_MEM_NONE)
        self.ds=vsip_vcloneview_f(self.d)
        self.fs=vsip_vcloneview_f(self.f)
        
    def __del__(self):
        vsip_vdestroy_f(self.ts)
        vsip_valldestroy_f(self.t)
        vsip_vdestroy_f(self.rs_one)
        vsip_vdestroy_f(self.rs_two)
        vsip_mdestroy_f(self.Rs)
        vsip_vdestroy_f(self.ls_one)
        vsip_vdestroy_f(self.ls_two)
        vsip_mdestroy_f(self.Ls)
        vsip_mdestroy_f(self.Bs)
        vsip_vdestroy_f(self.bs)
        vsip_malldestroy_f(self.B)
        vsip_malldestroy_f(self.R)
        vsip_malldestroy_f(self.L)
        vsip_valldestroy_vi(self.indx_L)
        vsip_valldestroy_vi(self.indx_R)
        vsip_vdestroy_f(self.ds);vsip_valldestroy_f(self.d)
        vsip_vdestroy_f(self.fs);vsip_valldestroy_f(self.f)

def svd_f(A):
    svd = svdObj_f(vsip_mgetcollength_f(A),vsip_mgetrowlength_f(A))
    vsip_mcopy_f_f(A,svd.B)
    svdBidiag_f(svd)
    svdIteration_f(svd)
    svdSort_f(svd)
    return svd
