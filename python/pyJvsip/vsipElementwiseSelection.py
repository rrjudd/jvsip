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
# DON'T know how to implement yet
# vsip_svfirst_p

# Functions that return a value are only supported as properties on views
# vsip_scminmgsqval_p
# vsip_sminmgval_p
# vsip_sminval_p
# vsip_scmaxmgsqval_p
# vsip_smaxmgval_p
# vsip_smaxval_p

# vsip_sclip_p
def clip(a,t1,t2,c1,c2,r):
    """
    Function clip may be done in-place
    """
    f={'mview_d':vsip_mclip_d,
       'mview_f':vsip_mclip_f,
       'mview_i':vsip_mclip_i,
       'mview_si':vsip_mclip_si,
       'vview_d':vsip_vclip_d,
       'vview_f':vsip_vclip_f,
       'vview_i':vsip_vclip_i,
       'vview_si':vsip_vclip_si,
       'vview_uc':vsip_vclip_uc}
    assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object in clip'
    assert 'pyJvsip.__View' in repr(r),\
           'Argument six must be a pyJvsip view object in clip'
    assert a.type == r.type,'Input and output views for clip must be the same type'
    assert __isSizeCompatible(a,r),'Input and output views for clip must be the same size'
    assert f.has_key(a.type),'Type <:'+a.type+':> not supported for clip'
    assert isinstance(t1,int) or isinstance(t1,float) or isinstance(t1,long)
    assert isinstance(t2,int) or isinstance(t2,float) or isinstance(t2,long)
    assert isinstance(c1,int) or isinstance(c1,float) or isinstance(c1,long)
    assert isinstance(c2,int) or isinstance(c2,float) or isinstance(c2,long)
    f[a.type](a.view,t1,t2,c1,c2,r.view)
    return r
# vsip_sinvclip_p
def invclip(a,t1,t2,t3,c1,c2,r):
    """
    Function invclip may be done in-place
    """
    f={'mview_d':vsip_minvclip_d,
       'mview_f':vsip_minvclip_f,
       'vview_d':vsip_vinvclip_d,
       'vview_f':vsip_vinvclip_f,
       'vview_i':vsip_vinvclip_i,
       'vview_si':vsip_vinvclip_si,
       'vview_uc':vsip_vinvclip_uc}
    assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object in invclip'
    assert 'pyJvsip.__View' in repr(r),\
           'Argument seven must be a pyJvsip view object in invclip'
    assert a.type == r.type,'Input and output views for invclip must be the same type'
    assert __isSizeCompatible(a,r),'Input and output views for invclip must be the same size'
    assert f.has_key(a.type),'Type <:'+a.type+':> not supported for invclip'
    assert isinstance(t1,int) or isinstance(t1,float) or isinstance(t1,long)
    assert isinstance(t2,int) or isinstance(t2,float) or isinstance(t2,long)
    assert isinstance(t3,int) or isinstance(t3,float) or isinstance(t3,long)
    assert isinstance(c1,int) or isinstance(c1,float) or isinstance(c1,long)
    assert isinstance(c2,int) or isinstance(c2,float) or isinstance(c2,long)
    f[a.type](a.view,t1,t2,t3,c1,c2,r.view)
    return r

# vsip_sindexbool
def indexbool(a,b):
    """
    Ussage:
        L=indexbool(a,b):
    Where
        a is a vector or matrix view of type _bl
        b is a vector of type _vi if a is a vector and _mi if a is a matrix
    Returns
        L is a length indicating number of non-false entries in input view a
    See VSIPL specification for more details.
    """
    f={'mview_blvview_mi':vsip_mindexbool,
       'vview_blvview_vi':vsip_vindexbool }
    assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object in indexbool'
    assert 'pyJvsip.__View' in repr(b),\
           'Argument two must be a pyJvsip view object in indexbool'
    t=a.type+b.type
    assert f.has_key(t),'Type <:'+t+':> not supported by indexbool'
    return f[t](a.view,b.view)

# vsip_smax_p
def max(a,b,c):
    """
    """
    f={'mview_dmview_dmview_d':vsip_mmax_d,
       'mview_fmview_fmview_f':vsip_mmax_f,
       'vview_dvview_dvview_d':vsip_vmax_d,
       'vview_fvview_fvview_f':vsip_vmax_f}
    assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object in max'
    assert 'pyJvsip.__View' in repr(a),\
           'Argument two must be a pyJvsip view object in max'
    assert 'pyJvsip.__View' in repr(a),\
           'Argument three must be a pyJvsip view object in max'
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c),\
           'Size error in max'
    t=a.type+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not supported by max'
    f[t](a.view,b.view,c.view)
    return c

# vsip_smaxmg_p
def maxmg(a,b,c):
    """
    """
    f={'mview_dmview_dmview_d':vsip_mmaxmg_d,
       'mview_fmview_fmview_f':vsip_mmaxmg_f,
       'vview_dvview_dvview_d':vsip_vmaxmg_d,
       'vview_fvview_fvview_f':vsip_vmaxmg_f}
    assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object in maxmg'
    assert 'pyJvsip.__View' in repr(b),\
           'Argument two must be a pyJvsip view object in maxmg'
    assert 'pyJvsip.__View' in repr(c),\
           'Argument three must be a pyJvsip view object in maxmg'
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c),\
           'Size error in maxmg'
    t=a.type+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not supported by maxmg'
    f[t](a.view,b.view,c.view)
    return c

# vsip_scmaxmgsq_p
def cmaxmgsq(a,b,c):
    """
    """
    f={'cmview_dcmview_dmview_d':vsip_mcmaxmgsq_d,
       'cmview_fcmview_fmview_f':vsip_mcmaxmgsq_f,
       'cvview_dcvview_dvview_d':vsip_vcmaxmgsq_d,
       'cvview_fcvview_fvview_f':vsip_vcmaxmgsq_f}
    assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object in cmaxmgsq'
    assert 'pyJvsip.__View' in repr(b),\
           'Argument two must be a pyJvsip view object in cmaxmgsq'
    assert 'pyJvsip.__View' in repr(c),\
           'Argument three must be a pyJvsip view object in cmaxmgsq'
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c),\
           'Size error in cmaxmgsq'
    t=a.type+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not supported by cmaxmgsq'
    f[t](a.view,b.view,c.view)
    return c

# vsip_smin_p
def min(a,b,c):
    """
    """
    f={'mview_dmview_dmview_d':vsip_mmin_d,
       'mview_fmview_fmview_f':vsip_mmin_f,
       'vview_dvview_dvview_d':vsip_vmin_d,
       'vview_fvview_fvview_f':vsip_vmin_f}
    assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object in min'
    assert 'pyJvsip.__View' in repr(b),\
           'Argument two must be a pyJvsip view object in min'
    assert 'pyJvsip.__View' in repr(c),\
           'Argument three must be a pyJvsip view object in min'
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c),\
           'Size error in min'
    t=a.type+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not supported by min'
    f[t](a.view,b.view,c.view)
    return c

# vsip_sminmg_p
def minmg(a,b,c):
    """
    """
    f={'mview_dmview_dmview_d':vsip_mminmg_d,
       'mview_fmview_fmview_f':vsip_mminmg_f,
       'vview_dvview_dvview_d':vsip_vminmg_d,
       'vview_fvview_fvview_f':vsip_vminmg_f}
    assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object in minmg'
    assert 'pyJvsip.__View' in repr(b),\
           'Argument two must be a pyJvsip view object in minmg'
    assert 'pyJvsip.__View' in repr(c),\
           'Argument three must be a pyJvsip view object in minmg'
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c),\
           'Size error in minmg'
    t=a.type+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not supported by minmg'
    f[t](a.view,b.view,c.view)
    return c

# vsip_scminmgsq_p
def cminmgsq(a,b,c):
    """
    """
    f={'cmview_dcmview_dmview_d':vsip_mcminmgsq_d,
       'cmview_fcmview_fmview_f':vsip_mcminmgsq_f,
       'cvview_dcvview_dvview_d':vsip_vcminmgsq_d,
       'cvview_fcvview_fvview_f':vsip_vcminmgsq_f}
    assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object in cminmgsq'
    assert 'pyJvsip.__View' in repr(b),\
           'Argument two must be a pyJvsip view object in cminmgsq'
    assert 'pyJvsip.__View' in repr(c),\
           'Argument three must be a pyJvsip view object in cminmgsq'
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c),\
           'Size error in minmgsq'
    t=a.type+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not supported by cminmgsq'
    f[t](a.view,b.view,c.view)
    return c
