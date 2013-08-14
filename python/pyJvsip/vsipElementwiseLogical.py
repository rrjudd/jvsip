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
#  alltrue and anytrue are done only as properties on a view
# vsip_salltrue_bl 
# vsip_sanytrue_bl 

# vsip_dsleq_p 
# vsip_dssleq_p 
def leq(a,b,c):
    f={'mview_dmview_dmview_bl':vsip_mleq_d,
       'mview_fmview_fmview_bl':vsip_mleq_f,
       'scalarvview_fvview_bl':vsip_svleq_f,              
       'scalarvview_dvview_bl':vsip_svleq_d,              
       'vview_dvview_dvview_bl':vsip_vleq_d,
       'vview_fvview_fvview_bl':vsip_vleq_f,
       'vview_ivview_ivview_bl':vsip_vleq_i,
       'vview_sivview_sivview_bl':vsip_vleq_si,
       'vview_ucvview_ucvview_bl':vsip_vleq_uc}
    assert 'pyJvsip.__View' in repr(b),\
           'Argument two must be a pyJvsip view object in leq'
    assert 'pyJvsip.__View' in repr(c),\
           'Argument three must be a pyJvsip view object in leq'
    assert __isSizeCompatible(b,c),'Size error in leq'
    assert 'view_bl' in c.type, 'Argument c must be a boolean'
    if isinstance(a,int) or isinstance(a,long) or isinstance(a,float):
        t1='scalar'
        a0=a
    else:
        assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object or scalar in leq'
        assert __isSizeCompatible(a,c),'Size error in leq'
        t1=a.type
        a0=a.view
    t=t1+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not recognized for leq'
    f[t](a0,b.view,c.view)
    return c

# vsip_slge_p 
# vsip_sslge_p     
def lge(a,b,c):
    f={'mview_dmview_dmview_bl':vsip_mlge_d,
       'mview_fmview_fmview_bl':vsip_mlge_f,
       'scalarvview_fvview_bl':vsip_svlge_f,              
       'scalarvview_dvview_bl':vsip_svlge_d,               
       'vview_dvview_dvview_bl':vsip_vlge_d,
       'vview_fvview_fvview_bl':vsip_vlge_f,
       'vview_ivview_ivview_bl':vsip_vlge_i,
       'vview_sivview_sivview_bl':vsip_vlge_si,
       'vview_ucvview_ucvview_bl':vsip_vlge_uc}
    assert 'pyJvsip.__View' in repr(b),\
           'Argument two must be a pyJvsip view object in lge'
    assert 'pyJvsip.__View' in repr(c),\
           'Argument three must be a pyJvsip view object in lge'
    assert __isSizeCompatible(b,c),'Size error in lge'
    assert 'view_bl' in c.type, 'Argument c must be a boolean'
    if isinstance(a,int) or isinstance(a,long) or isinstance(a,float):
        t1='scalar'
        a0=a
    else:
        assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object or scalar in lge'
        assert __isSizeCompatible(a,c),'Size error in lge'
        t1=a.type
        a0=a.view
    t=t1+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not recognized for lge'
    f[t](a0,b.view,c.view)
    return c 

# vsip_slgt_p 
# vsip_sslgt_p 
def lgt(a,b,c):
    f={'mview_dmview_dmview_bl':vsip_mlgt_d,
       'mview_fmview_fmview_bl':vsip_mlgt_f,
       'scalarvview_fvview_bl':vsip_svlgt_f,              
       'scalarvview_dvview_bl':vsip_svlgt_d,              
       'vview_dvview_dvview_bl':vsip_vlgt_d,
       'vview_fvview_fvview_bl':vsip_vlgt_f,
       'vview_ivview_ivview_bl':vsip_vlgt_i,
       'vview_sivview_sivview_bl':vsip_vlgt_si,
       'vview_ucvview_ucvview_bl':vsip_vlgt_uc}
    assert 'pyJvsip.__View' in repr(b),\
           'Argument two must be a pyJvsip view object in lgt'
    assert 'pyJvsip.__View' in repr(c),\
           'Argument three must be a pyJvsip view object in lgt'
    assert __isSizeCompatible(b,c),'Size error in lgt'
    assert 'view_bl' in c.type, 'Argument c must be a boolean'
    if isinstance(a,int) or isinstance(a,long) or isinstance(a,float):
        t1='scalar'
        a0=a
    else:
        assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object or scalar in lgt'
        assert __isSizeCompatible(a,c),'Size error in lgt'
        t1=a.type
        a0=a.view
    t=t1+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not recognized for lgt'
    f[t](a0,b.view,c.view)
    return c 

# vsip_slle_p 
# vsip_sslle_p 
def lle(a,b,c):
    f={'mview_dmview_dmview_bl':vsip_mlle_d,
       'mview_fmview_fmview_bl':vsip_mlle_f,
       'scalarvview_fvview_bl':vsip_svlle_f,              
       'scalarvview_dvview_bl':vsip_svlle_d,              
       'vview_dvview_dvview_bl':vsip_vlle_d,
       'vview_fvview_fvview_bl':vsip_vlle_f,
       'vview_ivview_ivview_bl':vsip_vlle_i,
       'vview_sivview_sivview_bl':vsip_vlle_si,
       'vview_ucvview_ucvview_bl':vsip_vlle_uc}
    assert 'pyJvsip.__View' in repr(b),\
           'Argument two must be a pyJvsip view object in lle'
    assert 'pyJvsip.__View' in repr(c),\
           'Argument three must be a pyJvsip view object in lle'
    assert __isSizeCompatible(b,c),'Size error in lle'
    assert 'view_bl' in c.type, 'Argument c must be a boolean'
    if isinstance(a,int) or isinstance(a,long) or isinstance(a,float):
        t1='scalar'
        a0=a
    else:
        assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object or scalar in lle'
        assert __isSizeCompatible(a,c),'Size error in lle'
        t1=a.type
        a0=a.view
    t=t1+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not recognized for lle'
    f[t](a0,b.view,c.view)
    return c

# vsip_sllt_p 
# vsip_ssllt_p 
def llt(a,b,c):
    f={'mview_dmview_dmview_bl':vsip_mllt_d,
       'mview_fmview_fmview_bl':vsip_mllt_f, 
       'scalarvview_fvview_bl':vsip_svllt_f,              
       'scalarvview_dvview_bl':vsip_svllt_d,             
       'vview_dvview_dvview_bl':vsip_vllt_d,
       'vview_fvview_fvview_bl':vsip_vllt_f,
       'vview_ivview_ivview_bl':vsip_vllt_i,
       'vview_sivview_sivview_bl':vsip_vllt_si,
       'vview_ucvview_ucvview_bl':vsip_vllt_uc}
    assert 'pyJvsip.__View' in repr(b),\
           'Argument two must be a pyJvsip view object in llt'
    assert 'pyJvsip.__View' in repr(c),\
           'Argument three must be a pyJvsip view object in llt'
    assert __isSizeCompatible(b,c),'Size error in llt'
    assert 'view_bl' in c.type, 'Argument c must be a boolean'
    if isinstance(a,int) or isinstance(a,long) or isinstance(a,float):
        t1='scalar'
        a0=a
    else:
        assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object or scalar in llt'
        assert __isSizeCompatible(a,c),'Size error in llt'
        t1=a.type
        a0=a.view
    t=t1+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not recognized for llt'
    f[t](a0,b.view,c.view)
    return c

# vsip_dslne_p 
# vsip_dsslne_p
def lne(a,b,c):
    f={'mview_dmview_dmview_bl':vsip_mlne_d,
       'mview_fmview_fmview_bl':vsip_mlne_f,  
       'scalarvview_fvview_bl':vsip_svlne_f,              
       'scalarvview_dvview_bl':vsip_svlne_d,            
       'vview_dvview_dvview_bl':vsip_vlne_d,
       'vview_fvview_fvview_bl':vsip_vlne_f,
       'vview_ivview_ivview_bl':vsip_vlne_i,
       'vview_sivview_sivview_bl':vsip_vlne_si,
       'vview_ucvview_ucvview_bl':vsip_vlne_uc}
    assert 'pyJvsip.__View' in repr(b),\
           'Argument two must be a pyJvsip view object in lne'
    assert 'pyJvsip.__View' in repr(c),\
           'Argument three must be a pyJvsip view object in lne'
    assert __isSizeCompatible(b,c),'Size error in lne'
    assert 'view_bl' in c.type, 'Argument c must be a boolean'
    if isinstance(a,int) or isinstance(a,long) or isinstance(a,float):
        t1='scalar'
        a0=a
    else:
        assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object or scalar in lne'
        assert __isSizeCompatible(a,c),'Size error in lne'
        t1=a.type
        a0=a.view
    t=t1+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not recognized for lne'
    f[t](a0,b.view,c.view)
    return c