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

# vsip_dscopy_p_p
def copy(a,b):
    f={'cmview_dcmview_d':vsip_cmcopy_d_d,
       'cmview_dcmview_f':vsip_cmcopy_d_f, 'cmview_fcmview_d':vsip_cmcopy_f_d,
       'cmview_fcmview_f':vsip_cmcopy_f_f, 'cvview_dcvview_d':vsip_cvcopy_d_d,
       'cvview_dcvview_f':vsip_cvcopy_d_f, 'cvview_fcvview_d':vsip_cvcopy_f_d,
       'cvview_fcvview_f':vsip_cvcopy_f_f, 'mview_blmview_bl':vsip_mcopy_bl_bl,
       'mview_blmview_d':vsip_mcopy_bl_d, 'mview_blmview_f':vsip_mcopy_bl_f,
       'mview_dmview_bl':vsip_mcopy_d_bl, 'mview_dmview_d':vsip_mcopy_d_d,
       'mview_dmview_f':vsip_mcopy_d_f, 'mview_dmview_i':vsip_mcopy_d_i,
       'mview_dmview_uc':vsip_mcopy_d_uc, 'mview_fmview_bl':vsip_mcopy_f_bl,
       'mview_fmview_d':vsip_mcopy_f_d, 'mview_fmview_f':vsip_mcopy_f_f,
       'mview_fmview_i':vsip_mcopy_f_i, 'mview_fmview_uc':vsip_mcopy_f_uc,
       'mview_imview_f':vsip_mcopy_i_f, 'mview_simview_f':vsip_mcopy_si_f,
       'mview_imview_i':vsip_mcopy_i_i,
       'vview_blvview_bl':vsip_vcopy_bl_bl, 'vview_blvview_d':vsip_vcopy_bl_d,
       'vview_blvview_f':vsip_vcopy_bl_f, 'vview_dvview_bl':vsip_vcopy_d_bl,
       'vview_dvview_d':vsip_vcopy_d_d, 'vview_dvview_f':vsip_vcopy_d_f,
       'vview_dvview_i':vsip_vcopy_d_i, 'vview_dvview_si':vsip_vcopy_d_si,
       'vview_dvview_uc':vsip_vcopy_d_uc, 'vview_dvview_vi':vsip_vcopy_d_vi,
       'vview_fvview_bl':vsip_vcopy_f_bl, 'vview_fvview_d':vsip_vcopy_f_d,
       'vview_fvview_f':vsip_vcopy_f_f, 'vview_fvview_i':vsip_vcopy_f_i,
       'vview_fvview_si':vsip_vcopy_f_si, 'vview_fvview_uc':vsip_vcopy_f_uc,
       'vview_fvview_vi':vsip_vcopy_f_vi, 'vview_ivview_d':vsip_vcopy_i_d,
       'vview_ivview_f':vsip_vcopy_i_f, 'vview_ivview_i':vsip_vcopy_i_i,
       'vview_ivview_uc':vsip_vcopy_i_uc, 'vview_ivview_vi':vsip_vcopy_i_vi,
       'vview_mivview_mi':vsip_vcopy_mi_mi, 'vview_sivview_d':vsip_vcopy_si_d,
       'vview_sivview_f':vsip_vcopy_si_f, 'vview_sivview_si':vsip_vcopy_si_si,
       'vview_vivview_i':vsip_vcopy_vi_i, 'vview_vivview_vi':vsip_vcopy_vi_vi,
       'vview_vivview_f':vsip_vcopy_vi_f, 'vview_vivview_d':vsip_vcopy_vi_d}
    assert 'pyJvsip.__View' in repr(a),\
           'Argument one must be a pyJvsip view object in copy'
    assert 'pyJvsip.__View' in repr(b),\
           'Argument two must be a pyJvsip view object in copy'
    assert __isSizeCompatible(a,b),'Input and output for copy must be the same size'
    t = a.type+b.type
    assert f.has_key(t),'Type <:'+t+':> not recognizedfor copy'
    f[t](a.view,b.view)
    return b

 
# copy to and from user space don't seem to make sense for pyJvsip
# see the view list method and jvsipNumpyUtils module for comparable routines
# vsip_dscopyto_user_p vsip_dscopyfrom_user_p 

# fill and ramp are only supported as methods on views
#vsip_dsfill_p vsip_vramp_p
