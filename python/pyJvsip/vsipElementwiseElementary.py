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

def sin(a,b):
    vf={'vview_f':vsip_vsin_f,'vview_d':vsip_vsin_d}
    mf={'mview_f':vsip_msin_f,'mview_d':vsip_msin_d}
    chk, msg = __iscompatible(a,b)
    if chk:
        if vf.has_key(a.type):
            vf[a.type](a.view,b.view)
        elif mf.has_key(a.type):
            mf[a.type](a.view,b.view)
        else:
            print('Type <:'+a.type+':> not supported for sin')
            return
        return b
    else:
        print(msg + ' for sin')
        return

def cos(a,b):
    vf={'vview_f':vsip_vcos_f,'vview_d':vsip_vcos_d}
    mf={'mview_f':vsip_mcos_f,'mview_d':vsip_mcos_d}
    chk , msg = __iscompatible(a,b)
    if chk:
        if vf.has_key(a.type):
            vf[a.type](a.view,b.view)
        elif mf.has_key(a.type):
            mf[a.type](a.view,b.view)
        else:
            print('Type <:'+a.type+':> not supported for cos')
            return
        return b
    else:
        print(msg + ' for cos')
        return

def tan(a,b):
    vf={'vview_f':vsip_vtan_f,'vview_d':vsip_vtan_d}
    mf={'mview_f':vsip_mtan_f,'mview_d':vsip_mtan_d}
    chk, msg = __iscompatible(a,b)
    if chk:
        if vf.has_key(a.type):
            vf[a.type](a.view,b.view)
        elif mf.has_key(a.type):
            mf[a.type](a.view,b.view)
        else:
            print('Type <:'+a.type+':> not supported for tan')
            return
        return b
    else:
        print(msg + ' for tan')
        return

def asin(a,b):
    vf={'vview_f':vsip_vasin_f,'vview_d':vsip_vasin_d}
    mf={'mview_f':vsip_masin_f,'mview_d':vsip_masin_d}
    chk, msg = __iscompatible(a,b)
    if chk:
        if vf.has_key(a.type):
            vf[a.type](a.view,b.view)
        elif mf.has_key(a.type):
            mf[a.type](a.view,b.view)
        else:
            print('Type <:'+a.type+':> not supported for asin')
            return
        return b
    else:
        print(msg + ' for asin')
        return

def acos(a,b):
    vf={'vview_f':vsip_vacos_f,'vview_d':vsip_vacos_d}
    mf={'mview_f':vsip_macos_f,'mview_d':vsip_macos_d}
    chk , msg = __iscompatible(a,b)
    if chk:
        if vf.has_key(a.type):
            vf[a.type](a.view,b.view)
        elif mf.has_key(a.type):
            mf[a.type](a.view,b.view)
        else:
            print('Type <:'+a.type+':> not supported for acos')
            return
        return b
    else:
        print(msg + ' for acos')
        return

def atan(a,b):
    vf={'vview_f':vsip_vatan_f,'vview_d':vsip_vatan_d}
    mf={'mview_f':vsip_matan_f,'mview_d':vsip_matan_d}
    chk, msg = __iscompatible(a,b)
    if chk:
        if vf.has_key(a.type):
            vf[a.type](a.view,b.view)
        elif mf.has_key(a.type):
            mf[a.type](a.view,b.view)
        else:
            print('Type <:'+a.type+':> not supported for atan')
            return
        return b
    else:
        print(msg + ' for atan')
        return

def exp(a,b):
    vf={'vview_f':vsip_vexp_f,'vview_d':vsip_vexp_d,\
        'cvview_f':vsip_cvexp_f,'cvview_d':vsip_cvexp_d}
    mf={'mview_f':vsip_mexp_f,'mview_d':vsip_mexp_d,\
        'cmview_f':vsip_cmexp_f,'cmview_d':vsip_cmexp_d}
    chk, msg = __iscompatible(a,b)
    if chk:
        if vf.has_key(a.type):
            vf[a.type](a.view,b.view)
        elif mf.has_key(a.type):
            mf[a.type](a.view,b.view)
        else:
            print('Type <:'+a.type+':> not supported for exp')
            return
        return b
    else:
        print(msg + ' for exp')
        return

def exp10(a,b):
    vf={'vview_f':vsip_vexp10_f,'vview_d':vsip_vexp10_d}
    mf={'mview_f':vsip_mexp10_f,'mview_d':vsip_mexp10_d}
    chk, msg = __iscompatible(a,b)
    if chk:
        if vf.has_key(a.type):
            vf[a.type](a.view,b.view)
        elif mf.has_key(a.type):
            mf[a.type](a.view,b.view)
        else:
            print('Type <:'+a.type+':> not supported for exp10')
            return
        return b
    else:
        print(msg + ' for exp10')
        return

def log(a,b):
    vf={'vview_f':vsip_vlog_f,'vview_d':vsip_vlog_d,\
        'cvview_f':vsip_cvlog_f,'cvview_d':vsip_cvlog_d}
    mf={'mview_f':vsip_mlog_f,'mview_d':vsip_mlog_d,\
        'cmview_f':vsip_cmlog_f,'cmview_d':vsip_cmlog_d}
    chk, msg = __iscompatible(a,b)
    if chk:
        if vf.has_key(a.type):
            vf[a.type](a.view,b.view)
        elif mf.has_key(a.type):
            mf[a.type](a.view,b.view)
        else:
            print('Type <:'+a.type+':> not supported for log')
            return
        return b
    else:
        print(msg + ' for log')
        return

def log10(a,b):
    vf={'vview_f':vsip_vlog10_f,'vview_d':vsip_vlog10_d}
    mf={'mview_f':vsip_mlog10_f,'mview_d':vsip_mlog10_d}
    chk, msg = __iscompatible(a,b)
    if chk:
        if vf.has_key(a.type):
            vf[a.type](a.view,b.view)
        elif mf.has_key(a.type):
            mf[a.type](a.view,b.view)
        else:
            print('Type <:'+a.type+':> not supported for log10')
            return
        return b
    else:
        print(msg + ' for log10')
        return