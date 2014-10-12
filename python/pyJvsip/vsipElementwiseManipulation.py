# Elementary Math functions
from vsip import *
def __iscompatible(a,b):
    chk = True
    msg='None'
    if ('pyJvsip.__View' not in repr(a)) or ('pyJvsip.__View' not in repr(b)):
        chk = False
        msg='Input must be a pyJvsip View'
    elif a.type != b.type:
        chk = False
        msg = 'Inputs must be the same type'
    elif 'mview' in a.type:
        if (a.rowlength != b.rowlength) or (a.collength != b.collength):
            chk = False
            msg = 'Inputs must be the same size'
    else:
        if a.length != b.length:
            chk = False
            msg = 'Inputs must be the same size'         
    return (chk,msg)
def __isSizeCompatible(a,b):
    if 'mview' in a.type and  'mview' in b.type:
        if (a.rowlength == b.rowlength) and (a.collength == b.collength):
            return True
    elif 'vview' in a.type and 'vview' in b.type:
        if a.length == b.length:
            return True
    else:
        return False
# vsip_dsswap_p
def swap(a,b):
    """
    See VSIP specification for Information
    """
    f = {'cmview_d':vsip_cmswap_d, 'cmview_f':vsip_cmswap_f, 'cvview_d':vsip_cvswap_d, \
         'cvview_f':vsip_cvswap_f, 'mview_d':vsip_mswap_d, 'mview_f':vsip_mswap_f,\
         'vview_d':vsip_vswap_d, 'vview_f':vsip_vswap_f, 'vview_i':vsip_vswap_i,\
         'vview_si':vsip_vswap_si, 'vview_uc':vsip_vswap_uc}
    chk, msg = __iscompatible(a,b)
    assert chk, msg
    t=a.type
    assert f.has_key(t), 'Type <:' +t+ ':> not supported for swap'
    f[a.type](a.vsip,b.vsip)

# vsip_dsgather_p 
def gather(a,b,c):
    """
    See VSIP specification for Information
    """
    f={'cmview_dvview_micvview_d':vsip_cmgather_d, 'cmview_fvview_micvview_f':vsip_cmgather_f,
       'cvview_dvview_vicvview_d':vsip_cvgather_d, 'cvview_fvview_vicvview_f':vsip_cvgather_f,
       'mview_dvview_mivview_d':vsip_mgather_d, 'mview_fvview_mivview_f':vsip_mgather_f,
       'vview_dvview_vivview_d':vsip_vgather_d, 'vview_fvview_vivview_f':vsip_vgather_f,
       'vview_ivview_vivview_i':vsip_vgather_i, 'vview_sivview_vivview_si':vsip_vgather_si,
       'vview_ucvview_vivview_uc':vsip_vgather_uc, 'vview_mivview_vivview_mi':vsip_vgather_mi,
       'vview_vivview_vivview_vi':vsip_vgather_vi}
    assert 'pyJvsip.__View' in repr(a),'Argument one must be a pyJvsip view object in function gather'
    assert 'pyJvsip.__View' in repr(b),'Argument two must be a pyJvsip view object in function gather'
    assert 'pyJvsip.__View' in repr(c),'Argument three must be a pyJvsip view object in function gather'
    t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:' +t+ ':> not supported for gather'
    assert __isSizeCompatible(b,c),'Index vector must be the same length as output vector'
    f[t](a.vsip,b.vsip,c.vsip)
    return c

# vsip_dsscatter_p
def scatter(a,b,c):
    """
    See VSIP specification for Information
    """
    f={'cvview_dcmview_dvview_mi':vsip_cmscatter_d, 'cvview_fcmview_fvview_mi':vsip_cmscatter_f,
       'cvview_dcvview_dvview_vi':vsip_cvscatter_d, 'cvview_fcvview_fvview_vi':vsip_cvscatter_f,
       'vview_dmview_dvview_mi':vsip_mscatter_d, 'vview_fmview_fvview_mi':vsip_mscatter_f,
       'vview_dvview_dvview_vi':vsip_vscatter_d, 'vview_fvview_fvview_vi':vsip_vscatter_f,
       'vview_i,vview_i,vview_vi':vsip_vscatter_i, 'vview_sivview_sivview_vi':vsip_vscatter_si,
       'vview_ucvview_ucvview_vi':vsip_vscatter_uc}
    assert 'pyJvsip.__View' in repr(a),'Argument one must be a pyJvsip view object in function scatter'
    assert 'pyJvsip.__View' in repr(b),'Argument two must be a pyJvsip view object in function scatter'
    assert 'pyJvsip.__View' in repr(c),'Argument three must be a pyJvsip view object in function scatter'
    t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:' +t+ ':> not supported for scatter'
    assert __isSizeCompatible(a,c),'Index vector must be the same length as input vector'
    f[t](a.vsip,b.vsip,c.vsip)
    return c

# vsip_srect_p 
def rect(a,b,*vars):
    """
    See VSIP specification for Information
    Convert polar to rectangular represenation
    Usage:
       rect(a,b,c)
    where
        a and b are views of type ?view_f or ?view_d
        c is a compliant view of type c?view_f or c?view_d
    OR:
        c = rect(a,b)
        compliant output c is created by function call.
    """
    f={'vview_dvview_dcvview_d':vsip_vrect_d, 'vview_fvview_fcvview_f':vsip_vrect_f,
       'mview_dmview_dcmview_d':vsip_mrect_d, 'mview_fmview_fcmview_f':vsip_mrect_f}
    assert 'pyJvsip.__View' in repr(a),'Argument one must be a pyJvsip view object in function rect'
    assert 'pyJvsip.__View' in repr(b),'Argument two must be a pyJvsip view object in function rect'
    assert len(vars) < 2, 'To many arguments to rect function'
    if len(vars) == 1:
        c = vars[0]
    else:
        c = a.otherEmpty
    assert 'pyJvsip.__View' in repr(c),'Argument three must be a pyJvsip view object in function rect'
    t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:' +t+ ':> not supported for rect'
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c),'Size error in rect'
    f[t](a.vsip,b.vsip,c.vsip)
    return c

# vsip_sreal_p 
def real(a,b):
    """
    See VSIP specification for Information
    real part
    a is of type complex; b is of corresponding type real
    """
    f={'cvview_dvview_d':vsip_vreal_d, 'cvview_fvview_f':vsip_vreal_f,
       'cmview_dmview_d':vsip_mreal_d, 'cmview_fmview_f':vsip_mreal_f}
    assert 'pyJvsip.__View' in repr(a),'Argument one must be a pyJvsip view object in function real'
    assert 'pyJvsip.__View' in repr(b),'Argument two must be a pyJvsip view object in function real'
    t=a.type+b.type
    assert f.has_key(t), 'Type <:' +t+ ':> not supported for real'
    assert __isSizeCompatible(a,b),'Size error in real'
    f[t](a.vsip,b.vsip)
    return b

# vsip_simag_p 
def imag(a,b):
    """
    See VSIP specification for Information
    Imaginary part
    a is of type complex; b is of corresponding type imaginary.
    """
    f={'cvview_dvview_d':vsip_vimag_d, 'cvview_fvview_f':vsip_vimag_f,
       'cmview_dmview_d':vsip_mimag_d, 'cmview_fmview_f':vsip_mimag_f}
    assert 'pyJvsip.__View' in repr(a),'Argument one must be a pyJvsip view object in function imag'
    assert 'pyJvsip.__View' in repr(b),'Argument two must be a pyJvsip view object in function imag'
    t=a.type+b.type
    assert f.has_key(t), 'Type <:' +t+ ':> not supported for imag'
    assert __isSizeCompatible(a,b),'Size error in imag'
    f[t](a.vsip,b.vsip)
    return b

# vsip_scmplx_p 
def cmplx(a,b,*vars):
    """
    See VSIP specification for Information
    Convert Convert real, imaginary (a,b) into complex
    Usage:
       rect(a,b,c)
    where
        a and b are views of type vview_f or vview_d
        c is a compliant view of type cvview_f or cvview_d
    OR:
        c = rect(a,b)
        compliant output c is created by function call.
    """

    f={'vview_dvview_dcvview_d':vsip_vcmplx_d,
       'vview_fvview_fcvview_f':vsip_vcmplx_f,
       'mview_dmview_dcmview_d':vsip_mcmplx_d,
       'mview_fmview_fcmview_f':vsip_mcmplx_f}
    assert 'pyJvsip.__View' in repr(a),'Argument one must be a pyJvsip view object in function cmplx'
    assert 'pyJvsip.__View' in repr(b),'Argument two must be a pyJvsip view object in function cmplx'
    assert len(vars) < 2, 'To many arguments to rect function'
    if len(vars) == 1:
        c = vars[0]
    else:
        c = a.otherEmpty
    assert 'pyJvsip.__View' in repr(c),'Argument three must be a pyJvsip view object in function cmplx'
    t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:' +t+ ':> not supported for cmplx'
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c),'Size error in cmplx'
    f[t](a.vsip,b.vsip,c.vsip)
    return c

# vsip_spolar_p
def polar(a,*vars):
    """
    See VSIP specification for Information
    Convert polar (complex vector) to rectangular (real vectors of radius and angle)
    Usage:
        polar(a,r,phi)
    or:
        (r,phi) = polar(a)
    where:
         a is a complex vector/matrix pyJvsip view
         r is a radius of type real (vector/matrix pyJvsip view)
         phi is an angle (vector/matrix pyJvsip view)
    """
    f={'cvview_dvview_dvview_d':vsip_vpolar_d,
       'cvview_fvview_fvview_f':vsip_vpolar_f,
       'cmview_dmview_dmview_d':vsip_mpolar_d,
       'cmview_fmview_fmview_f':vsip_mpolar_f}
    assert 'pyJvsip.__View' in repr(a),'Argument one must be a pyJvsip view object in function polar'
    assert len(vars) < 3, 'To many arguments to function polar'
    assert len(vars) == 2 or len(vars) == 0, 'In Polar argument two and three must both be present or both be absent'
    if len(vars) == 0:
        b = a.otherEmpty
        c = b.empty
    else:
        b=vars[0]
        c=vars[1]
    assert 'pyJvsip.__View' in repr(b),'Argument two must be a pyJvsip view object in function polar'
    assert 'pyJvsip.__View' in repr(c),'Argument three must be a pyJvsip view object in function polar'
    
    t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:' +t+ ':> not supported for polar'
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c),'Size error in polar'
    f[t](a.vsip,b.vsip,c.vsip)
    return(b,c)

# the nary functions are not currently supported in jvsip
# vsip_smary_p
# vsip_snary_p
# vsip_sserialmary_p
# vsip_sunary_p
# vsip_sbool_p
# pyJvsip does not support tensors at this time
# vsip_dtscatter_p 
# vsip_dtgather_p 
