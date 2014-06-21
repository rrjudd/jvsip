# Elementary Math functions
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
def arg(a,b):
    f={'cvview_fvview_f':vsip_varg_f,
       'cvview_dvview_d':vsip_varg_d,
       'cmview_fmview_f':vsip_marg_f,
       'cmview_dmview_d':vsip_marg_d}
    assert __isView(a) and __isView(b), 'Arguments must be pyJvsip views'
    t=a.type+b.type
    assert f.has_key(t), 'Type <:%s:> not recognized for function arg'%t
    assert __isSizeCompatible(a,b), 'Input views must be the same size'
    f[t](a.view,b.view)
    return b
def conj(a,b):
    f={'cvview_fcvview_f':vsip_cvconj_f,
       'cvview_dcvview_d':vsip_cvconj_d,
       'cmview_fcmview_f':vsip_cmconj_f,
       'cmview_dcmview_d':vsip_cmconj_d}
    assert __isView(a) and __isView(b), 'Arguments must be pyJvsip views'
    t=a.type+b.type
    assert f.has_key(t), 'Type <:%s:> not recognized for function cconj'%t
    assert __isSizeCompatible(a,b), 'Input views must be the same size'
    f[t](a.view,b.view)
    return b
def cumsum(a,b):
    """
    Cumulative sum function (see vsip_dscumsum_f).
    Works for matrix and vectors.
    For matrix does cumulative sum along rows or columns defined by the major
    attribute of the first argument.
    If the major attribute is COL then it is done by column;
    otherwise it is done by row. It is recommended to set the major attribute
    when calling the function since you don't know what it is unless you check it,
    and it is easier to set it than to check it.
    The function cumsum(a,b) may be done in place.
    """
    assert __isView(a) and __isView(b), 'Arguments must be pyJvsip views in function cumsum'
    t=a.type+b.type
    f={'mview_dmview_d':vsip_mcumsum_d, 'mview_fmview_f':vsip_mcumsum_f,
       'mview_imview_i':vsip_mcumsum_i, 'mview_simview_si':vsip_mcumsum_si,
       'vview_dvview_d':vsip_vcumsum_d, 'vview_fvview_f':vsip_vcumsum_f,
       'vview_ivview_i':vsip_vcumsum_i, 'vview_sivview_si':vsip_vcumsum_si}
    assert __isSizeCompatible(a,b), 'Arguments must be the same size for cumsum'
    assert f.has_key(t),'Type <:'+t+':> not supported by cumsum'
    if 'mview' in t:
        if a.major is 'COL':
            f[t](a.view,VSIP_COL,b.view)
        else:
            f[t](a.view,VSIP_ROW,b.view)
    else:
        f[t](a.view,b.view)
        return b
def euler(a,b):
    assert __isView(a) and __isView(b), 'Arguments must be pyJvsip views in function cumsum'
    f={'mview_dcmview_d':vsip_meuler_d,'mview_fcmview_f':vsip_meuler_f,
       'vview_dcvview_d':vsip_veuler_d,'vview_fcvview_f':vsip_veuler_f}
    t=a.type+b.type
    assert __isSizeCompatible(a,b),'Arguments must be the same size for euler'
    assert f.has_key(t),'Type <:'+t+':>not supported by euler'
    f[t](a.view,b.view)
    return b
def mag(a,b):
    f={'cmview_dmview_d':vsip_cmmag_d,'cmview_fmview_f':vsip_cmmag_f,
       'cvview_dvview_d':vsip_cvmag_d,'cvview_fvview_f':vsip_cvmag_f,
       'vview_dmview_d':vsip_mmag_d,'vview_fmview_f':vsip_mmag_f,
        'vview_dvview_d':vsip_vmag_d,'vview_fvview_f':vsip_vmag_f,
        'vview_ivview_i':vsip_vmag_i,'vview_sivview_si':vsip_vmag_si}
    assert __isView(a) and __isView(b), 'Arguments must be pyJvsip views in function mag'
    t=a.type+b.type
    assert __isSizeCompatible(a,b), 'Arguments must be the same size for mag'
    assert f.has_key(t),'Type <:'+t+':> not supported by mag'
    f[t](a.view,b.view)
    return b
def cmagsq(a,b):
    f={'cmview_dmview_d':vsip_mcmagsq_d, 'cmview_fmview_f':vsip_mcmagsq_f,
       'cvview_dvview_d':vsip_vcmagsq_d, 'cvview_fvview_f':vsip_vcmagsq_f}
    assert __isView(a) and __isView(b), 'Arguments must be pyJvsip views in function cmagsq'
    t=a.type+b.type
    assert __isSizeCompatible(a,b), 'Arguments must be the same size for cmagq'
    assert f.has_key(t),'Type <:'+t+':> not supported by cmagsq'
    f[t](a.view,b.view)
    return b
def modulate(a,nu,phi,b):
    """
    See VSIP document for more information on vsip_vmodulate_f
    Modulate takes a frequency and phase argument and returns a phase
    argument that would be used if modulate is called again for the same sequence.
    For pyJvsip modulate returns a tuple of the phase and the output vector.
    phiNew,b=modulate(a,nu,phiOld,b)
    """
    assert __isView(a) and __isView(b), 'First and last arguments must be pyJvsip views in function modulate'
    f={'cvview_dcvview_d':vsip_cvmodulate_d, 'vview_dcvview_d':vsip_vmodulate_d,
       'cvview_fcvview_f':vsip_cvmodulate_f, 'vview_fcvview_f':vsip_vmodulate_f}
    t=a.type+b.type
    assert __isSizeCompatible(a,b), 'Input/Output must be the same size for modulate'
    assert f.has_key(t),'Type <:'+t+':> not supported by modulate'
    phiNew=f[t](a,nu,phi,b)
    return (phiNew,b)
def neg(a,b):
    f={'cmview_d:cmview_d':vsip_cmneg_d, 'cmview_fcmview_f':vsip_cmneg_f,
       'cvview_dcvview_d':vsip_cvneg_d, 'cvview_fcvview_f':vsip_cvneg_f,
       'mview_dmview_d':vsip_mneg_d, 'mview_fmview_f':vsip_mneg_f,
       'vview_dvview_d':vsip_vneg_d, 'vview_fvview_f':vsip_vneg_f,
       'vview_ivview_i':vsip_vneg_i, 'vview_sivview_si':vsip_vneg_si}
    assert __isView(a) and __isView(b), 'Arguments must be pyJvsip views in function neg'
    t=a.type+b.type
    assert __isSizeCompatible(a,b),'Input/Output views must be the same size for neg'
    assert f.has_key(t),'Type <:'+t+':> not supported for neg'
    f[t](a.view,b.view)
    return b
def recip(a,b):
    f={'cmview_dcmview_d':vsip_cmrecip_d, 'cmview_fcmview_f':vsip_cmrecip_f,
       'cvview_dcvview_d':vsip_cvrecip_d, 'cvview_fcvview_f':vsip_cvrecip_f,
       'mview_dmview_d':vsip_mrecip_d, 'mview_fmview_f':vsip_mrecip_f,
       'vview_dvview_d':vsip_vrecip_d, 'vview_fvview_f':vsip_vrecip_f}
    assert __isView(a) and __isView(b), 'Arguments must be pyJvsip views in function recip'
    t=a.type+b.type
    assert __isSizeCompatible(a,b),'Input/Output views must be the same size for recip'
    assert f.has_key(t),'Type <:'+t+':> not supported for recip'
    f[t](a.view,b.view)
    return b
def rsqrt(a,b):
    f={'mview_dmview_d':vsip_mrsqrt_d, 'mview_fmview_f':vsip_mrsqrt_f,
       'vview_dvview_d':vsip_vrsqrt_d, 'vview_fvview_f':vsip_vrsqrt_f}
    assert __isView(a) and __isView(b), 'Arguments must be pyJvsip views in function rsqrt'
    t=a.type+b.type
    assert __isSizeCompatible(a,b),'Input/Output views must be the same size for rsqrt'
    assert f.has_key(t),'Type <:'+t+':> not supported for rsqrt'
    f[t](a.view,b.view)
    return b
def sq(a,b):
    f={'mview_dmview_d':vsip_msq_d, 'mview_fmview_f':vsip_msq_f,
       'vview_dvview_d':vsip_vsq_d, 'vview_fvview_f':vsip_vsq_f}
    assert __isView(a) and __isView(b), 'Arguments must be pyJvsip views in function sq'
    t=a.type+b.type
    assert __isSizeCompatible(a,b),'Input/Output views must be the same size for sq'
    assert f.has_key(t),'Type <:'+t+':> not supported for sq'
    f[t](a.view,b.view)
    return b
#vsip_sfloor_p_p
def floor(a,r):
    f={'mview_dmview_d':vsip_mfloor_d_d, 'mview_fmview_f':vsip_mfloor_f_f,
        'vview_dvview_d':vsip_vfloor_d_d, 'vview_fvview_f':vsip_vfloor_f_f,
        'mview_dmview_i':vsip_mfloor_d_i, 'mview_fmview_i':vsip_mfloor_f_i,
        'vview_dvview_i':vsip_vfloor_d_i, 'vview_fvview_i':vsip_vfloor_f_i}
    assert __isView(a) and __isView(r), 'Arguments must be pyJvsip views in function floor'
    t=a.type+r.type
    assert __isSizeCompatible(a,r),'Input/Output views must be the same size for floor'
    assert f.has_key(t),'Type <:%s:> not supported for floor'%t
    f[t](a.view,r.view)
    return r
# vsip_sceil_p_p
def ceil(a,r):
    f={'mview_dmview_d':vsip_mceil_d_d, 'mview_fmview_f':vsip_mceil_f_f,
        'vview_dvview_d':vsip_vceil_d_d, 'vview_fvview_f':vsip_vceil_f_f,
        'mview_dmview_i':vsip_mceil_d_i, 'mview_fmview_i':vsip_mceil_f_i,
        'vview_dvview_i':vsip_vceil_d_i, 'vview_fvview_i':vsip_vceil_f_i}
    assert __isView(a) and __isView(r), 'Arguments must be pyJvsip views in function ceil'
    t=a.type+r.type
    assert __isSizeCompatible(a,r),'Input/Output views must be the same size for ceil'
    assert f.has_key(t),'Type <:%s:> not supported for ceil'%t
    f[t](a.view,r.view)
    return r
# vsip_sround_p_p
def round(a,r):
    f={'mview_dmview_d':vsip_mround_d_d, 'mview_fmview_f':vsip_mround_f_f,
        'vview_dvview_d':vsip_vround_d_d, 'vview_fvview_f':vsip_vround_f_f,
        'mview_dmview_i':vsip_mround_d_i, 'mview_fmview_i':vsip_mround_f_i,
        'vview_dvview_i':vsip_vround_d_i, 'vview_fvview_i':vsip_vround_f_i}
    assert __isView(a) and __isView(r), 'Arguments must be pyJvsip views in function round'
    t=a.type+r.type
    assert __isSizeCompatible(a,r),'Input/Output views must be the same size for round'
    assert f.has_key(t),'Type <:%s:> not supported for round'%t
    f[t](a.view,r.view)
    return r
