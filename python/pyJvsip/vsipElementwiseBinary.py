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
def __isView(a):
    return 'pyJvsip.__View' in repr(a)
def add(a,b,c):
    """
    The add function includes view+view adds and scalar+view adds.
    """
    f={'vview_dvview_dvview_d':vsip_vadd_d,'vview_fvview_fvview_f':vsip_vadd_f,
       'vview_ivview_ivview_i':vsip_vadd_i,'vview_sivview_sivview_si':vsip_vadd_si,
       'vview_ucvview_ucvview_uc':vsip_vadd_uc,'mview_dmview_dmview_d':vsip_madd_d,
       'mview_fmview_fmview_f':vsip_madd_f,'mview_imview_imview_i':vsip_madd_i,
       'mview_simview_simview_si':vsip_madd_si,'mview_dcmview_dcmview_d':vsip_rcmadd_d,
       'mview_fcmview_fcmview_f':vsip_rcmadd_f,'vview_vivview_vivview_vi':vsip_vadd_vi,
       'cvview_dcvview_dcvview_d':vsip_cvadd_d,'cvview_fcvview_fcvview_f':vsip_cvadd_f,
       'cmview_dcmview_dcmview_d':vsip_cmadd_d,'cmview_fcmview_fcmview_f':vsip_cmadd_f,
       'vview_dcvview_dcvview_d':vsip_rcvadd_d,'vview_fcvview_fcvview_f':vsip_rcvadd_f,
       'scalarmview_dmview_d':vsip_smadd_d, 'scalarmview_fmview_f':vsip_smadd_f,
       'scalarvview_dvview_d':vsip_svadd_d, 'scalarvview_fvview_f':vsip_svadd_f,
       'scalarvview_ivview_i':vsip_svadd_i, 'scalarcmview_dcmview_d':vsip_rscmadd_d,
       'scalarcmview_fcmview_f':vsip_rscmadd_f, 'scalarcvview_dcvview_d':vsip_rscvadd_d,
       'scalarcvview_fcvview_f':vsip_rscvadd_f, 'scalarivview_sivview_si':vsip_svadd_si,
       'scalarcvview_ucvview_uc':vsip_svadd_uc, 'scalarvview_vivview_vi':vsip_svadd_vi,
       'cscalarcmview_dcmview_d':vsip_csmadd_d, 'cscalarcmview_fcmview_f':vsip_csmadd_f,
       'cscalarcvview_dcvview_d':vsip_csvadd_d, 'cscalarcvview_fcvview_f':vsip_csvadd_f}
    assert __isView(b),'Argument two must be a pyJvsip view object in add'
    assert __isView(c),'Argument three must be a pyJvsip view object in add'
    assert __isSizeCompatible(b,c),'Size error in add function'
    if isinstance(a,int) or isinstance(a,long) or isinstance(a,float):
        t='scalar'+b.type+c.type
    elif isinstance(a,complex):
        t='cscalar'+b.type+c.type
    else:
        assert __isView(a),'Argument one must be a scalar or a pyJvsip view object in add'
        t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:'+t+':> not recognized for add'
    if 'cscalar' in t:
        if 'view_d' in t:
            f[t](vsip_cmplx_d(a.real,a.imag),b.view,c.view)
        else:
            f[t](vsip_cmplx_f(a.real,a.imag),b.view,c.view)
    elif 'scalar' in t:
        f[t](a,b.view,c.view)
    else:
        f[t](a.view,b.view,c.view)
    return c        
def div(a,b,c):
    """
    The div function includes view/view, scalar/view, and view/(real scalar) .
    """
    err1='Argument one and argument three must have the same size if argument one is not a scalar in div'
    err2='Argument two and argument three must have the same size if argument two is not a scalar in div'
    f={'cmview_dcmview_dcmview_d':vsip_cmdiv_d, 'cmview_fcmview_fcmview_f':vsip_cmdiv_f,
       'cmview_dscalarcmview_d':vsip_cmrsdiv_d, 'cmview_fscalarcmview_f':vsip_cmrsdiv_f,
       'cmview_dmview_dcmview_d':vsip_crmdiv_d, 'cmview_fmview_fcmview_f':vsip_crmdiv_f,
       'cvview_dvview_dcvview_d':vsip_crvdiv_d, 'cvview_fvview_fcvview_f':vsip_crvdiv_f,
       'cvview_dcvview_dcvview_d':vsip_cvdiv_d, 'cvview_fcvview_fcvview_f':vsip_cvdiv_f,
       'mview_dmview_dmview_d':vsip_mdiv_d, 'mview_fmview_fmview_f':vsip_mdiv_f,
       'mview_dscalarmview_d':vsip_msdiv_d, 'mview_fscalarmview_f':vsip_msdiv_f,
       'mview_dcmview_dcmview_d':vsip_rcmdiv_d, 'mview_fcmview_fcmview_f':vsip_rcmdiv_f,
       'vview_dcvview_dcvview_d':vsip_rcvdiv_d, 'vview_fcvview_fcvview_f':vsip_rcvdiv_f,
       'vview_dvview_dvview_d':vsip_vdiv_d, 'vview_fvview_fvview_f':vsip_vdiv_f,
       'vview_dscalarvview_d':vsip_vsdiv_d, 'vview_fscalarvview_f':vsip_vsdiv_f,
       'cvview_dscalarcvview_d':vsip_cvrsdiv_d, 'cvview_fscalarcvview_f':vsip_cvrsdiv_f,
       'scalarcmview_dcmview_d':vsip_rscmdiv_d, 'scalarcmview_fcmview_f':vsip_rscmdiv_f,
       'scalarcvview_dcvview_d':vsip_rscvdiv_d, 'scalarcvview_fcvview_f':vsip_rscvdiv_f,
       'scalarmview_dmview_d':vsip_smdiv_d, 'scalarmview_fmview_f':vsip_smdiv_f,
       'scalarvview_dvview_d':vsip_svdiv_d, 'scalarvview_fvview_f':vsip_svdiv_f,
       'cscalarcmview_dcmview_d':vsip_csmdiv_d, 'cscalarcmview_fcmview_f':vsip_csmdiv_f,
       'cscalarcvview_dcvview_d':vsip_csvdiv_d, 'cscalarcvview_fcvview_f':vsip_csvdiv_f}
    assert 'pyJvsip.__View' in repr(c),'Argument 3 is not a pyJvsip view in div'
    t3=c.type
    if isinstance(a,int) or isinstance(a,long) or isinstance(a,float):
        t1='scalar'
    elif isinstance(a,complex):
        t1='cscalar'
    else:
        assert 'pyJvsip.__View' in repr(a),'Argument one must be a scalar or a pyJvsip view object in div'
        assert __isSizeCompatible(a,c), err1
        t1=a.type
    if isinstance(b,int) or isinstance(b,long) or isinstance(b,float):
        t2='scalar'
    else:
        assert 'pyJvsip.__View' in repr(b),'Argument two must be a real scalar or a pyJvsip view object in div'
        assert __isSizeCompatible(b,c), err2
        t2=b.type
    t=t1+t2+t3
    assert f.has_key(t),'Type <:'+t+':> not recognized for div'
    if 'cscalar' in t1:
        if 'vview_d' in t3:
            f[t](vsip_cmplx_d(a.real,a.imag),b.view,c.view)
        else:
            f[t](vsip_cmplx_f(a.real,a.imag),b.view,c.view)
    elif 'scalar' in t1:
        f[t](a,b.view,c.view)
    elif 'scalar' in t2:
        f[t](a.view,b,c.view)
    else:
        f[t](a.view,b.view,c.view)
    return c
def mul(a,b,c):
    """
    The mul function includes view+view muls and scalar+view muls.
    """
    f={'cmview_dcmview_dcmview_d':vsip_cmmul_d, 'cmview_fcmview_fcmview_f':vsip_cmmul_f,
       'cscalarcmview_dcmview_d':vsip_csmmul_d, 'cscalarcmview_fcmview_f':vsip_csmmul_f,
       'cscalarcvview_dcvview_d':vsip_csvmul_d, 'cscalarcvview_fcvview_f':vsip_csvmul_f,
       'cvview_dcvview_dcvview_d':vsip_cvmul_d, 'cvview_fcvview_fcvview_f':vsip_cvmul_f,
       'mview_dmview_dmview_d':vsip_mmul_d, 'mview_fmview_fmview_f':vsip_mmul_f,
       'mview_dcmview_dcmview_d':vsip_rcmmul_d, 'mview_fcmview_fcmview_f':vsip_rcmmul_f,
       'vview_dcvview_dcvview_d':vsip_rcvmul_d, 'vview_fcvview_fcvview_f':vsip_rcvmul_f,
       'scalarcmview_dcmview_d':vsip_rscmmul_d, 'scalarcmview_fcmview_f':vsip_rscmmul_f,
       'scalarcvview_dcvview_d':vsip_rscvmul_d, 'scalarcvview_fcvview_f':vsip_rscvmul_f,
       'scalarmview_dmview_d':vsip_smmul_d, 'scalarmview_fmview_f':vsip_smmul_f,
       'scalarvview_dvview_d':vsip_svmul_d, 'scalarvview_fvview_f':vsip_svmul_f,
       'scalarvview_ivview_i':vsip_svmul_i, 'scalarvview_sivview_si':vsip_svmul_si,
       'scalarvview_ucvview_uc':vsip_svmul_uc, 'vview_dvview_dvview_d':vsip_vmul_d,
       'vview_fvview_fvview_f':vsip_vmul_f, 'vview_ivview_ivview_i':vsip_vmul_i,
       'vview_sivview_sivview_si':vsip_vmul_si, 'vview_ucvview_ucvview_uc':vsip_vmul_uc}
    assert 'pyJvsip.__View' in repr(b),'Argument two must be a pyJvsip view object in mul'
    assert 'pyJvsip.__View' in repr(c),'Argument three must be a pyJvsip view object in mul'
    assert __isSizeCompatible(b,c),'Size error in mul function'
    if isinstance(a,int) or isinstance(a,long) or isinstance(a,float):
        t='scalar'+b.type+c.type
    elif isinstance(a,complex):
        t='cscalar'+b.type+c.type
    else:
        assert 'pyJvsip.__View' in repr(a),'Argument one must be a scalar or a pyJvsip view object in mul'
        t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:'+t+':> not recognized for mul'
    if 'cscalar' in t:
        if 'view_d' in t:
            f[t](vsip_cmplx_d(a.real,a.imag),b.view,c.view)
        else:
            f[t](vsip_cmplx_f(a.real,a.imag),b.view,c.view)
    elif 'scalar' in t:
        f[t](a,b.view,c.view)
    else:
        f[t](a.view,b.view,c.view)
    return c     
def jmul(a,b,c):
    f={'cmview_dcmview_dcmview_d':vsip_cmjmul_d,'cmview_fcmview_fcmview_f':vsip_cmjmul_f,
       'cvview_dcvview_dcvview_d':vsip_cvjmul_d,'cvview_fcvview_fcvview_f':vsip_cvjmul_f}
    assert __isView(a),'Argument two must be a pyJvsip view object in jmul'
    assert __isView(b),'Argument two must be a pyJvsip view object in jmul'
    assert __isView(c),'Argument two must be a pyJvsip view object in jmul'
    t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:'+t+':> not recognized for jmul'
    assert __isSizeCompatible(a,c), 'Argument one and argument three must be the same size in jmul'
    assert __isSizeCompatible(b,c), 'Argument two and argument three must be the same size in jmul'
    f[t](a.view,b.view,c.view)
    return c    
def vmmul(a,b,c):
    """
    For Vector Matrix multiply along Rows or Along columns in C VSIPL uses a vsip_major argument.
    For pyJvsip if the first arguments major attribute is 'COL' then this is done element-wise along the columns; 
    otherwise it is done element-wise along the rows. It is easier to set the major attribute than to check it.
    Usage
        mmul(a.COL,b,c) is equivalent to vsip_vmmul_f(a,b,VSIP_COL,c)
        mmul(a.ROW,b,c) is equivalent to vsip_vmmul_f(a,b,VSIP_ROW,c)
    """
    err1='The vector length of argument 1 for by column must equal the column length of argument 2'
    err2='The vector length of argument 1 for by row must equal the row length of argument 2'
    f={'cvview_dcmview_dcmview_d':vsip_cvmmul_d,
       'cvview_fcmview_fcmview_f':vsip_cvmmul_f,
       'vview_dmview_dmview_d':vsip_vmmul_d,
       'vview_fmview_fmview_f':vsip_vmmul_f,
       'vview_dcmview_dcmview_d':vsip_rvcmmul_d,
       'vview_fcmview_fcmview_f':vsip_rvcmmul_f}
    assert 'pyJvsip.__View' in repr(a),'Argument one must be a pyJvsip view object in mmul'
    assert 'pyJvsip.__View' in repr(b),'Argument two must be a pyJvsip view object in mmul'
    assert 'pyJvsip.__View' in repr(c),'Argument three must be a pyJvsip view object in mmul'
    t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:'+t+':> not recognized for mmul'
    assert __isSizeCompatible(b,c), 'Argument two and argument three must be the same size in mmul'
    if 'COL' in a.major:
        assert a.length == b.collength, err1
        f[t](a.view,b.view,VSIP_COL,c.view)
    else:
        assert a.length == b.rowlength, err2
        f[t](a.view,b.view,VSIP_ROW,c.view)
    return c
def sub(a,b,c):
    """
    sub(a,b,c) means
    c=arg1-arg2; arg1 may be a scalar or a view
    It is the responsibility of the user to ensure data is properly sized when using scalars.
    For instance subtracting a short int vector from a large integer value and placing the results
    in a short int vector will result in overflows and unpredictable results. 
    """
    f={ 'cmview_dcmview_dcmview_d':vsip_cmsub_d, 'cmview_fcmview_fcmview_f':vsip_cmsub_f,
        'cmview_dmview_dcmview_d':vsip_crmsub_d, 'cmview_fmview_fcmview_f':vsip_crmsub_f,
        'cvview_dvview_dcvview_d':vsip_crvsub_d, 'cvview_fvview_fcvview_f':vsip_crvsub_f,
        'cscalarcmview_dcmview_d':vsip_csmsub_d, 'cscalarcmview_fcmview_f':vsip_csmsub_f,
        'cscalarcvview_dcvview_d':vsip_csvsub_d, 'cscalarcvview_fcvview_f':vsip_csvsub_f,
        'cvview_dcvview_dcvview_d':vsip_cvsub_d, 'cvview_fcvview_fcvview_f':vsip_cvsub_f,
        'mview_dmview_dmview_d':vsip_msub_d, 'mview_fmview_fmview_f':vsip_msub_f,
        'mview_imview_imview_i':vsip_msub_i, 'mview_simview_simview_si':vsip_msub_si,
        'mview_dcmview_dcmview_d':vsip_rcmsub_d, 'mview_fcmview_fcmview_f':vsip_rcmsub_f,
        'vview_dcvview_dcvview_d':vsip_rcvsub_d, 'vview_fcvview_fcvview_f':vsip_rcvsub_f,
        'scalarcmview_dcmview_d':vsip_rscmsub_d, 'scalarcmview_fcmview_f':vsip_rscmsub_f,
        'scalarcvview_dcvview_d':vsip_rscvsub_d, 'scalarcvview_fcvview_f':vsip_rscvsub_f,
        'scalarmview_dmview_d':vsip_smsub_d, 'scalarmview_fmview_f':vsip_smsub_f,
        'scalarmview_imview_i':vsip_smsub_i, 'scalarmview_simview_si':vsip_smsub_si,
        'scalarmview_simview_si':vsip_smsub_si, 'scalarvview_dvview_d':vsip_svsub_d,
        'scalarvview_fvview_f':vsip_svsub_f, 'scalarvview_ivview_i':vsip_svsub_i,
        'scalarvview_sivview_si':vsip_svsub_si, 'scalarvview_ucvview_uc':vsip_svsub_uc,
        'scalarvview_vivview_vi':vsip_svsub_vi, 'vview_dvview_dvview_d':vsip_vsub_d,
        'vview_fvview_fvview_f':vsip_vsub_f, 'vview_ivview_ivview_i':vsip_vsub_i,
        'vview_sivview_sivview_si':vsip_vsub_si, 'vview_ucvview_ucvview_uc':vsip_vsub_uc}
    assert 'pyJvsip.__View' in repr(b),'Argument two must be a pyJvsip view object in sub'
    assert 'pyJvsip.__View' in repr(c),'Argument three must be a pyJvsip view object in sub'
    assert __isSizeCompatible(b,c),'Size error in sub function'
    if isinstance(a,int) or isinstance(a,long) or isinstance(a,float):
        t='scalar'+b.type+c.type
    elif isinstance(a,complex):
        t='cscalar'+b.type+c.type
    else:
        assert 'pyJvsip.__View' in repr(a),'Argument one must be a scalar or a pyJvsip view object in sub'
        t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:'+t+':> not recognized for add'
    if 'cscalar' in t:
        if 'view_d' in t:
            f[t](vsip_cmplx_d(a.real,a.imag),b.view,c.view)
        else:
            f[t](vsip_cmplx_f(a.real,a.imag),b.view,c.view)
    elif 'scalar' in t:
        f[t](a,b.view,c.view)
    else:
        f[t](a.view,b.view,c.view)
    return c
def expoavg(a,b,c):
    """
    Usage:
       expoavg(a,b,c)
    Where:
       a is a real, float, scalar
       b is a vector view of type float, real or complex
       c is a vector view of the same type as b 
    See VSIPL manual for additional information
    """
    f={'scalarcmview_dcmview_d':vsip_cmexpoavg_d,
       'scalarcmview_fcmview_f':vsip_cmexpoavg_f,
       'scalarcvview_dcvview_d':vsip_cvexpoavg_d,
       'scalarcvview_fcvview_f':vsip_cvexpoavg_f,
       'scalarmview_dmview_d':vsip_mexpoavg_d,
       'scalarmview_fmview_f':vsip_mexpoavg_f,
       'scalarvview_dvview_d':vsip_vexpoavg_d,
       'scalarvview_fvview_f':vsip_vexpoavg_f}
    assert isinstance(a,int) or isinstance(a,float),'Argument one of expoavg is a scalar float'
    assert 'pyJvsip.__View' in repr(b) and 'vview' in b.type,'Argument two of expoavg should b a vector view'
    assert 'pyJvsip.__View' in repr(c),'Argument three must be a pyJvsip view in expoavg'
    assert __isSizeCompatible(b,c),'Arguments two and three must be the same size in expoavg'
    assert c.type == b.type, 'Arguments two and three must be views of the same type'
    t='scalar'+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not recognized for expoavg'
    f[t](a,b.view,c.view)
    return c
def hypot(a,b,c):
    """
    See VSIP specification for information on hypot.
    """
    t0='pyJvsip.__View'
    err1='Arguments must be a pyJvsip view'
    err2='Arguments are not of the same size'
    f={'mview_dmview_dmview_d':vsip_mhypot_d,
       'mview_fmview_fmview_f':vsip_mhypot_f,
       'vview_dvview_dvview_d':vsip_vhypot_d,
       'vview_fvview_fvview_f':vsip_vhypot_f}
    assert t0 in repr(a) and t0 in repr(b) and t0 in repr(c),err1
    assert __isSizeCompatible(a,c) and __isSizeCompatible(b,c),err2
    t=a.type+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not recognized for hypot'
    f[t](a.view,b.view,c.view)
    return c

