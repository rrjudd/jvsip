import numpy as np
import pyJvsip as pv
from jvsipNumpyUtils import *

def jvCopyToNp(v):
    def myarray(v):
        if ('cmview_d' in v.type) or ('cvview_d' in v.type):
            p = np.complex128
        elif ('cmview_f' in v.type) or ('cvview_f' in v.type):
            p = np.complex64
        elif ('mview_d' in v.type) or ('vview_d' in v.type):
            p = np.float64
        else:
            p = np.float32
        aryt='C'
        mjr=0
        if('mview' in v.type):
            if 'COL' in v.major:
                aryt='F'
                mjr=1
            ary=np.empty([v.collength,v.rowlength],p,aryt)
        else:
            ary=np.empty(v.length,p)
        return (ary,mjr)
    assert 'pyJvsip' in pv.getType(v)[0], "Input does not appear to be a pyJvsip type."
    assert ('view_d' in v.type) or ('view_f' in v.type), v.type + " not supported by jvCopyToNp"
    f= {'vview_f':vcopyToNParray_f,'vview_d':vcopyToNParray_d,
    'cvview_f':cvcopyToNParray_f,'cvview_d':cvcopyToNParray_d,
    'mview_f':mcopyToNParray_f,'mview_d':mcopyToNParray_d,
    'cmview_f':cmcopyToNParray_f,'cmview_d':cmcopyToNParray_d}
    ary,mjr = myarray(v)
    if 'vview' in v.type:
        f[v.type](v.view,ary)
    else:
        f[v.type](v.view,mjr,ary)
    return ary
    
def npCopyToJv(a):
    def myView(a):
        fv={'float32':'vview_f','float64':'vview_d','complex64':'cvview_f','complex128':'cvview_d'}
        fm={'float32':'mview_f','float64':'mview_d','complex64':'cmview_f','complex128':'cmview_d'}
        ashp=a.shape
        t=a.dtype.name
        if len(a.shape) is 1: # create a vector
            v=pv.create(fv[t],ashp[0])
        else: #create a matrix
            if a.flags.f_contiguous:
                v=pv.create(fm[t],ashp[0],ashp[1],'COL')
            else:
                v=pv.create(fm[t],ashp[0],ashp[1])
        return v
    sptd=['float32','float64','complex64','complex128']
    assert a.dtype.name in sptd, a.dtype.name + ' not supported by npCopyToJv.'
    assert 0 < len(a.shape) < 3, 'Only arrays of dimension 1 or 2 supported.'
    assert (a.flags.c_contiguous or a.flags.f_contiguous) and a.flags.aligned, 'Only contiguous aligned arrays supported'
    v=myView(a)
    f= {'vview_f':vcopyFromNParray_f,'vview_d':vcopyFromNParray_d,
        'cvview_f':cvcopyFromNParray_f,'cvview_d':cvcopyFromNParray_d,
        'mview_f':mcopyFromNParray_f,'mview_d':mcopyFromNParray_d,
        'cmview_f':cmcopyFromNParray_f,'cmview_d':cmcopyFromNParray_d}
    if 'vview' in v.type:
        f[v.type](v.view,a)
    else:
        mjr=0
        if a.flags.f_contiguous:
            mjr=1
        f[v.type](v.view,mjr,a)
    return v
