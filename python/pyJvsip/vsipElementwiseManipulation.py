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

def swap(a,b):
    f = {'cmview_d':vsip_cmswap_d, 'cmview_f':vsip_cmswap_f, 'cvview_d':vsip_cvswap_d, \
         'cvview_f':vsip_cvswap_f, 'mview_d':vsip_mswap_d, 'mview_f':vsip_mswap_f,\
         'vview_d':vsip_vswap_d, 'vview_f':vsip_vswap_f, 'vview_i':vsip_vswap_i,\
         'vview_si':vsip_vswap_si, 'vview_uc':vsip_vswap_uc}
    chk, msg = __iscompatible(a,b)
    if chk:
        if f.has_key(a.type):
            f[a.type](a.view,b.view)
        else:
            print('Type <:' +a.type+ ':> not supported for swap')
    else:
        print(msg + ' for swap.')
        
