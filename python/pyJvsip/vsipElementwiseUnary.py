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

def arg(a,b):
    f={'cvview_fvview_f':vsip_varg_f,
       'cvview_dvview_d':vsip_varg_d,
       'cmview_fmview_f':vsip_marg_f,
       'cmview_dmview_d':vsip_marg_d}
    t=a.type+b.type
    if f.has_key(t):
        if __isSizeCompatible(a,b): 
            f[t](a.view,b.view)
            return b
        else:
            print('Arguments must be the same size for arg')
            return
    else:
        print('Argument Types not recognized for arg')
        return

