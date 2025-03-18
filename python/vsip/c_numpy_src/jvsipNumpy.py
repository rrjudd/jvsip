from numpy import complex128, complex64, float64, float32, empty
from pyJvsip import getType, create
from jvsipNumpyUtils import *

def jvToNp(v):
    """
    Usage:
       from jvsipNumpy import jvCopyToNp
       # get a vsip view 'V' of type (c)vview_f, (c)vview_d, (c)mview_f, (c)mview_d
       ar=jvCopyToNp(V)
    This should produce a new numpy array ar of the proper type with a copy of the data in V.
    """
    def myarray(v):
        if ('cmview_d' in v.type) or ('cvview_d' in v.type):
            p = complex128
        elif ('cmview_f' in v.type) or ('cvview_f' in v.type):
            p = complex64
        elif ('mview_d' in v.type) or ('vview_d' in v.type):
            p = float64
        else:
            p = float32
        aryt='C'
        mjr=0
        if('mview' in v.type):
            if 'COL' in v.major:
                aryt='F'
                mjr=1
            ary=empty([v.collength,v.rowlength],p,aryt)
        else:
            ary=empty(v.length,p)
        return (ary,mjr)
    assert 'pyJvsip' in getType(v)[0], "Input does not appear to be a pyJvsip type."
    assert ('view_d' in v.type) or ('view_f' in v.type), \
                "Type %s not supported by jvToNp"%v.type
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

def npToJv(a):
    """
    Usage:
       from jvsipNumpy import npCopyToJv
       # get a numpy array 'ar' of type float32, float64, complex64, complex128
       V=npCopyToJv(ar)
    This should produce a new pyJvsip vector or matrix 'V' with a copy of the data in ar.
    """
    def myView(a):
        fv={'float32':'vview_f','float64':'vview_d','complex64':'cvview_f','complex128':'cvview_d'}
        fm={'float32':'mview_f','float64':'mview_d','complex64':'cmview_f','complex128':'cmview_d'}
        ashp=a.shape
        t=a.dtype.name
        if len(a.shape) == 1: # create a vector
            v=create(fv[t],ashp[0])
        else: #create a matrix
            if a.flags.f_contiguous:
                v=create(fm[t],ashp[0],ashp[1],'COL')
            else:
                v=create(fm[t],ashp[0],ashp[1])
        return v
    sptd=['float32','float64','complex64','complex128']
    assert a.dtype.name in sptd, a.dtype.name + ' not supported by npToJv.'
    assert 0 < len(a.shape) < 3, 'Only arrays of dimension 1 or 2 supported.'
    assert (a.flags.c_contiguous or a.flags.f_contiguous) and a.flags.aligned, \
                'Only contiguous aligned arrays supported'
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
