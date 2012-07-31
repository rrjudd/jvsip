# Elementary Math functions
from vsip import *
def sin(a,b):
    vf={'vview_f':vsip_vsin_f,'vview_d':vsip_vsin_d}
    mv={'mview_f':vsip_msin_f,'mview_d':vsip_msin_d}
    if a.type==b.type:
        if vf.has_key(a.type) and (a.length==b.length):
            vf[a.type](a.view,b.view)
            return b
        elif mf.has_key(a.type) and (a.rowlength == b.rowlength)\
                               and (a.collength == b.collength):
            mf[a.type](a.view,b.view)
            return b
        else:
            print('Sizes of input views must agree for sin')
            return
    else:
        print('Input types must be the same for sine')
        return
def cos(a,b):
    vf={'vview_f':vsip_vcos_f,'vview_d':vsip_vcos_d}
    mv={'mview_f':vsip_mcos_f,'mview_d':vsip_mcos_d}
    if a.type==b.type:
        if vf.has_key(a.type) and (a.length==b.length):
            vf[a.type](a.view,b.view)
            return b
        elif mf.has_key(a.type) and (a.rowlength == b.rowlength)\
                               and (a.collength == b.collength):
            mf[a.type](a.view,b.view)
            return b
        else:
            print('Sizes of input views must agree for cos')
            return
    else:
        print('Input types must be the same for cos')
        return
