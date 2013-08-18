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

# vsip_shisto_p 
def histo(a,b_min,b_max,op,b):
    """
    See VSIP specification for mor info.
    Usage:
       histo(in,b_min,b_max,op,out)
    where:
        in is a VSIP matrix or vector view
        b_min is a scalar of the same type as b indicating the minimum bin threshold
        b_max is a scalar of the same type as b indicating the maximum bin threshold
        op indicates if data is being accumulated. It should be a string either 'RESET' or 'ACCUM'.
        out is a vector view of the same precision as the in view.
    """
    f={'mview_dvview_d':vsip_mhisto_d,
       'mview_fvview_f':vsip_mhisto_f,
       'mview_ivview_i':vsip_mhisto_i,
       'mview_sivview_si':vsip_mhisto_si,
       'vview_dvview_d':vsip_vhisto_d,
       'vview_fvview_f':vsip_vhisto_f,
       'vview_ivview_i':vsip_vhisto_i,
       'vview_sivview_si':vsip_vhisto_si}
    assert 'pyJvsip.__View' in repr(a),\
           'Input argument must be a pyJvsip view object for function histo'
    assert 'pyJvsip.__View' in repr(b),\
           'Output argument must be a pyJvsip view object for function histo'
    t=a.type+b.type
    assert f.has_key(t),'Type <:'+t+':> not supported for freqswap'
    assert (isinstance(b_min,float) or isinstance(b_min,int)) and \
           (isinstance(b_max,float) or isinstance(b_max,int))
    if op == 1:
        vsipOp=VSIP_HIST_RESET
    elif op == 2:
        vsipOp=VSIP_HIST_ACCUM
    elif 'RESET' in op:
        vsipOp=VSIP_HIST_RESET
    elif 'ACCUM' in op:
        vsipOp=VSIP_HIST_ACCUM
    else:
        print('Operator flag not recognized')
        return
    if '_i' in t or '_si' in t:
        assert isinstance(b_min,int) and isinstance(b_max,int), \
          'Type <:'+t+':> requires int max and min bin arguments'
        f[t](a.view,int(b_min),int(b_max),vsipOp,b.view)
        return b
    else:
        f[t](a.view,float(b_min),float(b_max),vsipOp,b.view)
        return b

# vsip_dsfreqswap_f
def freqswap(a):
    """
    See VSIP specification for more details.
    """
    f={'cvview_d':vsip_cvfreqswap_d,
       'vview_d':vsip_vfreqswap_d,
       'cmview_d':vsip_cmfreqswap_d,
       'mview_d':vsip_mfreqswap_d,
       'cvview_f':vsip_cvfreqswap_f,
       'vview_f':vsip_vfreqswap_f,
       'cmview_f':vsip_cmfreqswap_f,
       'mview_f':vsip_mfreqswap_f}
    assert 'pyJvsip.__View' in repr(a),\
           'Argument must be a pyJvsip view object for function freqswap'
    t=a.type
    assert f.has_key(t),'Type <:'+t+':> not supported for freqswap'
    f[t](a.view)
    return a