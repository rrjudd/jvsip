from vsip import *
#Spline, Sort, Permute; Interpolate
#spline is a class in pyJvsip.py

# pyJvsip Functions
def linear(x0,y0,*args):
    major={'ROW':VSIP_ROW,'COL':VSIP_COL,0:VSIP_ROW,1:VSIP_COL}
    f={'vview_fvview_f':vsip_vinterp_linear_f, 'vview_dvview_d':vsip_vinterp_linear_d,
       'vview_fmview_f':vsip_minterp_linear_f, 'vview_dmview_d':vsip_minterp_linear_d}
    n=len(args)
    assert n >= 2 and n <=3,'Argument list error for linear.'
    x=args[n-2];y=args[n-1]
    assert 'pyJvsip' in repr(x0) and 'pyJvsip' in repr(y0) and \
           'pyJvsip' in repr(x) and 'pyJvsip' in repr(y), 'First two and last two arguments must be pyJvsip views.'
    t=x0.type+y0.type
    assert t in f,'View types not recognized for linear interpolations'
    if n == 3:
        dim = arg[0]
    else:
        dim = x0.major
    if 'mview' in y0.type:
        assert dim in major,'Dimension flag not recognized for linear interpolation.'
        if major[dim]==0:
            assert x0.length == y0.collength,'Input data views not compliant.'
            assert x.length  == y.collength,'Output data views not compliant.'
        else:
            assert x0.length == y0.rowlength,'Input data views not compliant.'
            assert x.length  == y.rowlength,'Output data views not compliant.'
        f[t](x0.vsip,y0.vsip,major[dim],x.vsip,y.vsip)
    else:
        assert x0.length == y0.length,'Input data views not compliant.'
        assert y.length  == x.length, 'Output data views not compliant.'
        f[t](x0.vsip,y0.vsip,x.vsip,y.vsip)
    return y
def nearest(x0,y0,*args):
    f={'vview_fvview_f':vsip_vinterp_nearest_f, 'vview_dvview_d':vsip_vinterp_nearest_d,
       'vview_fmview_f':vsip_minterp_nearest_f, 'vview_dmview_d':vsip_minterp_nearest_d}
    major={'ROW':VSIP_ROW,'COL':VSIP_COL,0:VSIP_ROW,1:VSIP_COL}
    n=len(args)
    assert n >= 2 and n <=3,'Argument list error for linear.'
    x=args[n-2];y=args[n-1]
    assert 'pyJvsip' in repr(x0) and 'pyJvsip' in repr(y0) and \
           'pyJvsip' in repr(x) and 'pyJvsip' in repr(y), 'First two and last two arguments must be pyJvsip views.'
    t=x0.type+y0.type
    assert t in f,'View types not recognized for nearest interpolations'
    if n == 3:
        dim = arg[0]
    else:
        dim = x0.major
    if 'mview' in y0.type:
        assert dim in major,'Dimension flag not recognized for nearest interpolation.'
        if major[dim]==0:
            assert x0.length == y0.collength,'Input data views not compliant.'
            assert x.length  == y.collength,'Output data views not compliant.'
        else:
            assert x0.length == y0.rowlength,'Input data views not compliant.'
            assert x.length  == y.rowlength,'Output data views not compliant.'
        f[t](x0.vsip,y0.vsip,major[dim],x.vsip,y.vsip)
    else:
        assert x0.length == y0.length,'Input data views not compliant.'
        assert y.length  == x.length, 'Output data views not compliant.'
        f[t](x0.vsip,y0.vsip,x.vsip,y.vsip)
    return y
def permute_once(inpt,m,indx,outpt):
    major={'ROW':VSIP_ROW,'COL':VSIP_COL,0:VSIP_ROW,1:VSIP_COL}
    f={'cmview_d':vsip_cmpermute_once_d,\
       'cmview_f':vsip_cmpermute_once_f,\
       'mview_d':vsip_mpermute_once_d,\
       'mview_f':vsip_mpermute_once_f}
    assert m in major,"Major argument should be one of 'ROW' or VSIP_ROW;  'COL' or VSIP_COL"
    assert 'vview_vi' == indx.type,'Index vector must be of type vview_vi'
    assert inpt.type==outpt.type,'Input and output matrix must be the same shape'
    assert inpt.size==outpt.size,'Input and output matrix must be the same size'
    assert inpt.type in f,'Input view not supported for permute once'
    if major[m] == VSIP_ROW:
        assert indx.length==inpt.collength,'error in index size'
    else:
        assert indx.length==inpt.rowlength,'error in index size'
    f[inpt.type](inpt.vsip,major[m],indx.vsip,outpt.vsip)
    return outpt
    