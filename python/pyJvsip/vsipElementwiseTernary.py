from vsip import *

def __isSizeCompatible(a,b):
    if 'mview' in a.type and  'mview' in b.type:
        if (a.rowlength == b.rowlength) and (a.collength == b.collength):
            return True
    elif 'vview' in a.type and 'vview' in b.type:
        if a.length == b.length:
            return True
    else:
        return False

#vsip_dvam_p
#vsip_dvsam_p
def am(a,b,c,d):
    """
    vector add and multiply
    add two vectors and multiply times a vector, elementwise
    or
    add a vector and a scalar, elementwise, and mutiply times a vector elementwise
    """
    f={'cvview_dcvview_dcvview_dcvview_d':vsip_cvam_d,
       'cvview_dcscalarcvview_dcvview_d':vsip_cvsam_d,
       'cvview_fcscalarcvview_fcvview':vsip_cvsam_f,
       'vview_dscalarvview_dvview_d':vsip_vsam_d,
       'vview_fscalarvview_fvview_f':vsip_vsam_f,
       'cvview_fcvview_fcvview_fcvview_f':vsip_cvam_f,
       'vview_dvview_dvview_dvview_d':vsip_vam_d,
       'vview_fvview_fvview_fvview_f':vsip_vam_f}
    assert 'pyJvsip.__View' in repr(a),'Argument one must be a pyJvsip view object in am'
    t1=a.type
    assert __isSizeCompatible(a,c),'Size error in add-multiply (am)'
    assert __isSizeCompatible(a,d),'Size error in add-multiply (am)'
    if isinstance(b,int) or isinstance(b,long) or isinstance(b,float):
        t2='scalar'
    elif isinstance(b,complex):
        t2='cscalar'
    else:
        assert 'pyJvsip.__View' in repr(b),\
          'Argument two must be a scalar or a pyJvsip view object in am'
        t2=b.type
        assert a.type==b.type,'View types must agree in am'
    assert 'pyJvsip.__View' in repr(c),'Argument three must be a pyJvsip view object in am'
    assert __isSizeCompatible(a,c),'Size error in add-multiply (am)'
    t3=c.type
    assert a.type==c.type,'View types must agree in am'
    assert 'pyJvsip.__View' in repr(d),'Argument four must be a pyJvsip view object in am'
    assert __isSizeCompatible(a,d),'Size error in add-multiply (am)'
    assert a.type==d.type,'View types must agree in am'
    t4=d.type
    if 'scalar' in t2 and 'cvview' in t1:
        t2='cscalar'
    t=t1+t2+t3+t4
    assert f.has_key(t), 'Type <:'+t+':> not recognized for am'
    if 'cscalar' in t:
        if 'cvview_d' in t:
            f[t](a.view,vsip_cmplx_d(b.real,b.imag),c.view,d.view)
        else:
            f[t](a.view,vsip_cmplx_f(b.real,b.imag),c.view,d.view)
    elif 'scalar' in t:
        f[t](a.view,b,c.view.d.view)
    else:            
        f[t](a.view,b.view,c.view,d.view)
    return d

#vsip_vma_p
#vsip_dvmsa_p
#vsip_dvsma_p
#vsip_dvsmsa_p
def ma(a,b,c,d):
    """
    Multiply-Add
    ma(a,b,c,d)
    a=>vector view
    b=> vector view or scalar
    c=> vector view or scalar
    d=> vector view of same type as a
    a and d can be the same view (in-place)
    """
    f={'cvview_dcvview_dcvview_dcvview_d':vsip_cvma_d,
       'cvview_fcvview_fcvview_fcvview_f':vsip_cvma_f,
       'vview_dvview_dvview_dvview_d':vsip_vma_d,
       'vview_fvview_fvview_fvview_f':vsip_vma_f,
       'cvview_dcscalarcvview_dcvview_d':vsip_cvsma_d,
       'cvview_fcscalarcvview_fcvview_f':vsip_cvsma_f,
       'vview_dscalarvview_dvview_d':vsip_vsma_d,
       'vview_fscalarvview_fvview_f':vsip_vsma_f,
       'cvview_dcvview_dcscalarcvview_d':vsip_cvmsa_d,
       'cvview_fcvview_fcscalarcvview_f':vsip_cvmsa_f,
       'vview_dvview_dscalarvview_d':vsip_vmsa_d,
       'vview_fvview_fscalarvview_f':vsip_vmsa_f,
       'cvview_dcscalarcscalarcvview_d':vsip_cvsmsa_d,
       'cvview_fcscalarcscalarcvview_f':vsip_cvsmsa_f,
       'vview_dscalarscalarvview_d':vsip_vsmsa_d,
       'vview_fscalarscalarvview_f':vsip_vsmsa_f}
    assert 'pyJvsip.__View' in repr(a),'Argument one must be a pyJvsip view object in am'
    t1=a.type
    assert 'pyJvsip.__View' in repr(d),'Argument four must be a pyJvsip view object in am'
    t4=d.type
    assert t1 == t4,'Views in ma must be the same type'
    assert __isSizeCompatible(a,d),'Size error in ma (multiply-add)'
    if isinstance(b,int) or isinstance(b,long) or isinstance(b,float):
        if 'cvview_d' in t1:
            t2='cscalar'
            b0=vsip_cmplx_d(float(b),0.0)
        elif 'cvview_f' in t1:
            t2='cscalar'
            b0=vsip_cmplx_f(float(b),0.0)
        else:
            t2='scalar'
            b0=float(b)
    elif isinstance(b,complex):
        t2='cscalar'
        if 'cvview_d' in t1:
            b0=vsip_cmplx_d(b.real,b.imag)
        else:
            b0=vsip_cmplx_f(b.real,b.imag)
    else:
        assert 'pyJvsip.__View' in repr(b),\
             'Argument two must be a pyJvsip view object or scalar in am'
        assert __isSizeCompatible(a,b),'Size error in ma (multiply-add)'
        t2=b.type
        b0=b.view
    if isinstance(c,int) or isinstance(c,long) or isinstance(c,float):
        if 'cvview_d' in t1:
            t3='cscalar'
            c0=vsip_cmplx_d(float(c),0.0)
        elif 'cvview_f' in t1:
            t3='cscalar'
            c0=vsip_cmplx_f(float(c),0.0)
        else:
            t3='scalar'
            c0=float(c)
    elif isinstance(c,complex):
        t3='cscalar'
        if 'cvview_d' in t1:
            c0=vsip_cmplx_d(c.real,c.imag)
        else:
            c0=vsip_cmplx_f(c.real,c.imag)
    else:
        assert 'pyJvsip.__View' in repr(c),\
             'Argument three must be a pyJvsip view object or scalar in ma'
        assert __isSizeCompatible(a,c),'Size error in ma (multiply-add)'
        t3=c.type
        c0=c.view
    t=t1+t2+t3+t4
    assert f.has_key(t), 'Type <:'+t+':> not recognized for ma'
    f[t](a.view,b0,c0,d.view)
    return d

#vsip_dvmsb_p
def msb(a,b,c,d):
    """
    vector multiply - vector subtract
    msb(a,b,c,d) d == a * b - c (elementwise)
    a=>vector view
    b=>vector view
    c=>vector view
    d=>vector view
    May be done in place so d may be a, b, or c
    """
    f={'cvview_dcvview_dcvview_dcvview_d':vsip_cvmsb_d,
       'cvview_fcvview_fcvview_fcvview_f':vsip_cvmsb_f,
       'vview_dvview_dvview_dvview_d':vsip_vmsb_d,
       'vview_fvview_fvview_fvview_f':vsip_vmsb_f}
    assert 'pyJvsip.__View' in repr(a),'Argument one must be a pyJvsip view object in msb'
    assert 'pyJvsip.__View' in repr(b),'Argument two must be a pyJvsip view object in msb'
    assert 'pyJvsip.__View' in repr(c),'Argument three must be a pyJvsip view object in msb'
    assert 'pyJvsip.__View' in repr(d),'Argument four must be a pyJvsip view object in msb'
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c) and __isSizeCompatible(a,b)\
              ,'Size error in ma (multiply-add)'
    t=a.type+b.type+c.type+d.type
    assert f.has_key(t), 'Type <:'+t+':> not recognized for msb'
    f[t](a.view,b.view,c.view,d.view)
    return d

#vsip_dvsbm_p
def sbm(a,b,c,d):
    """
    vector subtract - vector multiply
    msb(a,b,c,d) d == (a - b) * c (elementwise)
    a=>vector view
    b=>vector view
    c=>vector view
    d=>vector view
    May be done in place so d may be a, b, or c
    """
    f={'cvview_dcvview_dcvview_dcvview_d':vsip_cvsbm_d,
       'cvview_fcvview_fcvview_fcvview_f':vsip_cvsbm_f,
       'vview_dvview_dvview_dvview_d':vsip_vsbm_d,
       'vview_fvview_fvview_fvview_f':vsip_vsbm_f}
    assert 'pyJvsip.__View' in repr(a),'Argument one must be a pyJvsip view object in msb'
    assert 'pyJvsip.__View' in repr(b),'Argument two must be a pyJvsip view object in msb'
    assert 'pyJvsip.__View' in repr(c),'Argument three must be a pyJvsip view object in msb'
    assert 'pyJvsip.__View' in repr(d),'Argument four must be a pyJvsip view object in msb'
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c) and __isSizeCompatible(a,b)\
              ,'Size error in ma (multiply-add)'
    t=a.type+b.type+c.type+d.type
    assert f.has_key(t), 'Type <:'+t+':> not recognized for msb'
    f[t](a.view,b.view,c.view,d.view)
    return d