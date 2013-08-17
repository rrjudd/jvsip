from vsip import *
## for this file we append bb_ before functions to avoid python keywords
def __isSizeCompatible(a,b):
    if 'mview' in a.type and  'mview' in b.type:
        if (a.rowlength == b.rowlength) and (a.collength == b.collength):
            return True
    elif 'vview' in a.type and 'vview' in b.type:
        if a.length == b.length:
            return True
    else:
        return False
#vsip_sand_p 
def bb_and(a,b,c):
    """
    Bitwise and Boolean and (bb_and). See VSIPL and function
    """
    f={'mview_imview_imview_i':vsip_mand_i,
       'mview_simview_simview_si':vsip_mand_si,
       'vview_blvview_blvview_bl':vsip_vand_bl,
       'vview_ivview_ivview_i':vsip_vand_i,
       'vview_sivview_sivview_si':vsip_vand_si,
       'vview_ucvview_ucvview_uc':vsip_vand_uc}
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c),\
        'Size error in function and'
    t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:'+t+':> not supported for function bb_and.'
    f[t](a.view,b.view,c.view)
    return c
#vsip_snot_p
def bb_not(a,b):
    """
    Bitwise and Boolean and (bb_not). See VSIPL not function
    """
    f={'vview_blvview_bl':vsip_vnot_bl,
       'vview_ivview_i':vsip_vnot_i,
       'vview_sivview_si':vsip_vnot_si,
       'vview_ucvview_uc':vsip_vnot_uc}
    assert __isSizeCompatible(a,b),'Size error in function bb_not'
    t=a.type+b.type
    assert f.has_key(t), 'Type <:'+t+':> not supported for function not.'
    f[t](a.view,b.view)
    return b

#vsip_sor_p 
def bb_or(a,b,c):
    """
    Bitwise and Boolean and (bb_or). See VSIPL or function
    """
    f={'vview_blvview_blvview_bl':vsip_vor_bl,
       'vview_ivview_ivview_i':vsip_vor_i,
       'vview_sivview_sivview_si':vsip_vor_si,
       'vview_ucvview_ucvview_uc':vsip_vor_uc}
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c),\
        'Size error in function or'
    t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:'+t+':> not supported for function or.'
    f[t](a.view,b.view,c.view)
    return c
#vsip_sxor_p
def bb_xor(a,b,c):
    """
    Bitwise and Boolean and (bb_xor). See VSIPL xor function
    """
    f={'vview_ivview_ivview_i':vsip_vxor_i,
       'vview_sivview_sivview_si':vsip_vxor_si,
       'vview_ucvview_ucvview_uc':vsip_vxor_uc,
       'vview_blvview_blvview_bl':vsip_vxor_bl}
    assert __isSizeCompatible(a,b) and __isSizeCompatible(a,c),\
        'Size error in function xor'
    t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:'+t+':> not supported for function xor.'
    f[t](a.view,b.view,c.view)
    return c