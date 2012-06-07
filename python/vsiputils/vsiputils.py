from vsip import *

# Python support functions
def init():
    return vsip_init(None)
def finalize():
    return vsip_finalize(None)
def getType(v):
    """
        Returns a tuple with True if a vsip type is found, plus a string indicating the type.
        For instance for
        a = vsip_vcreate_f(10,VSIP_MEM_NONE)
        will return for the call getType(a) (True,'vview_f')     
        also returns types of scalars derived from structure. for instance
        c = vsip_cscalar_d() will return for getType(c) the tuple (True, 'cscalar_d').
        attr = vsip_mattr_d() will return for getType(attr) the tuple (True, 'mattr_d')
        If float or int type is passed in returns (True,'scalar')
        If called with a non VSIPL type returns (False, 'Not a VSIPL Type')
        """
    t = repr(v).rpartition('vsip_')
    if t[1] == 'vsip_':
        return(True,t[2].partition(" ")[0])
    elif isinstance(v,float):
        return(True,'scalar')
    elif isinstance(v,int):
        return(True,'scalar')
    else:
        return(False,'Not a VSIPL Type')
def cscalarToComplex(a):
    """
      for a scalar of type vsip_cscalar return a python complex scalar value
    """
    t=['cscalar_f','cscalar_d']
    if getType(a)[1] in t:
        return (a.r + a.i * 1j)
    elif type(a) == float or type(a) == int:
        return a
    else:
        print('Type not supported by cscalarToComplex')
        return False
def complexToCscalar(t,a):
    if t == 'cscalar_d':
       x=vsip_cscalar_d()
       x.r=a.real
       x.i=a.imag
       return x
    elif t == 'cscalar_f':
       x=vsip_cscalar_f()
       x.r=a.real
       x.i=a.imag
       return x
    elif type(a) == float or type(a) == int:
       return a
    else:
       print('Type ' + t + ' not supported by complexToCscalar')
       return False

def miToTuple(a):
   return (a.r,a.c)
def index(a):
    t = getType(a)[1]
    tm=['mview_d','mview_f','cmview_f','cmview_d','mview_i','mview_si',
        'mview_uc','mview_bl']
    tv=['vview_d','vview_f','cvview_f','cvview_d','vview_i','vview_si',
        'vview_uc','vview_mi','vview_vi','vview_bl']
    if t in tm:
        return vsip_scalar_mi()
    elif t in tv:
        return vindexptr()
    else:
        print('Type ' + t + ' not supported by index')
        return False
def pyIndex(a):
    t=getType(a)[1]
    if t == 'scalar_mi':
        return (a.r, a.c)
    elif t == 'scalar_vi':
        return vindexptrToInt(a)
    else:
        print('Type '  + t + ' not suported by pyIndex')
        return False
def create(atype,atuple):
    """
    Create a vsipl object associated with a type. 

    Note that scalar types and attribute types are not created here. The argument 'atuple' 
    is a tuple containing necessary data to create the object defined by atype. The contents 
    of the tuple are the same as the arguments described in the prototypes of the C VSIPL document. 
    For instance
        create('block_f',(10000,VSIP_MEM_NONE)) 
    is the same as
        vsip_blockcreate_f(10000,VSIP_MEM_NONE);
    """
    if type(atuple) == int:
        l=(atuple,)
    elif type(atuple) == tuple:
        l=atuple
    else:
        print('Second argument must be int or tuple corresponding to C VSIPL argument list');
        return False
    f={'block_f':'vsip_blockcreate_f(l[0],l[1])',
       'block_d':'vsip_blockcreate_d(l[0],l[1])',
       'cblock_f':'vsip_cblockcreate_f(l[0],l[1])',
       'cblock_d':'vsip_cblockcreate_d(l[0],l[1])',
       'block_i':'vsip_blockcreate_i(l[0],l[1])',
       'block_si':'vsip_blockcreate_si(l[0],l[1])',
       'block_uc':'vsip_blockcreate_uc(l[0],l[1])',
       'block_vi':'vsip_blockcreate_vi(l[0],l[1])',
       'block_mi':'vsip_blockcreate_mi(l[0],l[1])',
       'block_bl':'vsip_blockcreate_bl(l[0],l[1])',
       'blackman_d':'vsip_vcreate_blackman_d(l[0], l[1])',
       'hanning_d':'vsip_vcreate_hanning_d(l[0], l[1])',
       'kaiser_d':'vsip_vcreate_kaiser_d(l[0], l[1], l[2])',
       'cheby_d':'vsip_vcreate_cheby_d(l[0], l[1], l[2])',
       'blackman_f':'vsip_vcreate_blackman_f(l[0], l[1])',
       'hanning_f':'vsip_vcreate_hanning_f(l[0], l[1])',
       'kaiser_f':'vsip_vcreate_kaiser_f(l[0],l[1],l[2])',
       'cheby_f':'vsip_vcreate_cheby_f(l[0], l[1], l[2])',
       'vview_f':'vsip_vcreate_f(l[0],l[1])',
       'vview_d':'vsip_vcreate_d(l[0],l[1])',
       'cvview_f':'vsip_cvcreate_f(l[0],l[1])',
       'cvview_d':'vsip_cvcreate_d(l[0],l[1])',
       'vview_i':'vsip_vcreate_i(l[0],l[1])',
       'vview_si':'vsip_vcreate_si(l[0],l[1])',
       'vview_uc':'vsip_vcreate_uc(l[0],l[1])',
       'vview_bl':'vsip_vcreate_bl(l[0],l[1])',
       'vview_vi':'vsip_vcreate_vi(l[0],l[1])',
       'vview_mi':'vsip_vcreate_mi(l[0],l[1])',
       'mview_f':'vsip_mcreate_f(l[0],l[1],l[2],l[3])',
       'mview_d':'vsip_mcreate_d(l[0],l[1],l[2],l[3])',
       'cmview_f':'vsip_cmcreate_f(l[0],l[1],l[2],l[3])',
       'cmview_d':'vsip_cmcreate_d(l[0],l[1],l[2],l[3])',
       'mview_i':'vsip_mcreate_i(l[0],l[1],l[2],l[3])',
       'mview_si':'vsip_mcreate_si(l[0],l[1],l[2],l[3])',
       'mview_uc':'vsip_mcreate_uc(l[0],l[1],l[2],l[3])',
       'mview_bl':'vsip_mcreate_bl(l[0],l[1],l[2],l[3])',
       'lu_d':'vsip_lud_create_d(l[0])',
       'lu_f':'vsip_lud_create_f(l[0])',
       'clu_d':'vsip_clud_create_d(l[0])',
       'clu_f':'vsip_clud_create_f(l[0])',
       'qr_d':'vsip_qrd_create_d(l[0],l[1],l[2])',
       'qr_f':'vsip_qrd_create_f(l[0],l[1],l[2])',
       'cqr_d':'vsip_cqrd_create_d(l[0],l[1],l[2])',
       'cqr_f':'vsip_cqrd_create_f(l[0],l[1],l[2])',
       'ccfftip_f':'vsip_ccfftip_create_f(l[0],l[1],l[2],l[3],l[4])',
       'ccfftop_f':'vsip_ccfftop_create_f(l[0],l[1],l[2],l[3],l[4])',
       'rcfftop_f':'vsip_rcfftop_create_f(l[0],l[1],l[2],l[3])',
       'crfftop_f':'vsip_crfftop_create_f(l[0],l[1],l[2],l[3])',
       'ccfftip_d':'vsip_ccfftip_create_d(l[0],l[1],l[2],l[3],l[4])',
       'ccfftop_d':'vsip_ccfftop_create_d(l[0],l[1],l[2],l[3],l[4])',
       'rcfftop_d':'vsip_rcfftop_create_d(l[0],l[1],l[2],l[3])',
       'crfftop_d':'vsip_crfftop_create_d(l[0],l[1],l[2],l[3])',
       'ccfftmip_f':'vsip_ccfftmip_create_f(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
       'ccfftmop_f':'vsip_ccfftmop_create_f(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
       'rcfftmop_f':'vsip_rcfftmop_create_f(l[0],l[1],l[2],l[3],l[4],l[5])',
       'crfftmop_f':'vsip_crfftmop_create_f(l[0],l[1],l[2],l[3],l[4],l[5])',
       'ccfftmip_d':'vsip_ccfftmip_create_d(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
       'ccfftmop_d':'vsip_ccfftmop_create_d(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
       'rcfftmop_d':'vsip_rcfftmop_create_d(l[0],l[1],l[2],l[3],l[4],l[5])',
       'crfftmop_d':'vsip_crfftmop_create_d(l[0],l[1],l[2],l[3],l[4],l[5])',
       'chol_f':'vsip_chold_create_f(l[0],l[1])',
       'chol_d':'vsip_chold_create_d(l[0],l[1])',
       'cchol_f':'vsip_cchold_create_f(l[0],l[1])',
       'cchol_d':'vsip_cchold_create_d(l[0],l[1])',
       'sv_f':'vsip_svd_create_f(l[0],l[1],l[2],l[3])',
       'sv_d':'vsip_svd_create_d(l[0],l[1],l[2],l[3])',
       'fir_f':'vsip_fir_create_f(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
       'fir_d':'vsip_fir_create_d(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
       'cfir_f':'vsip_cfir_create_f(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
       'cfir_d':'vsip_cfir_create_d(l[0],l[1],l[2],l[3],l[4],l[5],l[6])',
       'randstate':'vsip_randcreate(l[0],l[1],l[2],l[3])'}
    if f.has_key(atype):
        return eval(f[atype])
    else:
        print('Type ' + atype + ' Not a valid type for create')
        return False
def destroy(obj):
    """
    Free memory associated with a vsipl object created by the "create" function.

    Note that view creates also create a block object. To properly destroy all data
    associated with the view both the view and the block must be destroyed. However
    a block may have several views associated with it. Destroying the block before
    all associated views are destroyed is an error. Note the view destroy returns
    the block object it is associated with. so destroy(destroy(view)) is the same as
    an all destroy. For this module it is up to the user to keep track of when an all destroy
    can be done and when a block reference needs to be maintained.
    """
    f={'block_f'   :vsip_blockdestroy_f,
       'block_d'   :vsip_blockdestroy_d,
       'cblock_f'  :vsip_cblockdestroy_f,
       'cblock_d'  :vsip_cblockdestroy_d,
       'block_i'   :vsip_blockdestroy_i,
       'block_si'  :vsip_blockdestroy_si,
       'block_uc'  :vsip_blockdestroy_uc,
       'block_vi'  :vsip_blockdestroy_vi,
       'block_mi'  :vsip_blockdestroy_mi,
       'block_bl'  :vsip_blockdestroy_bl,
       'vview_f'   :vsip_vdestroy_f,
       'vview_d'   :vsip_vdestroy_d,
       'cvview_f'  :vsip_cvdestroy_f,
       'cvview_d'  :vsip_cvdestroy_d,
       'vview_i'   :vsip_vdestroy_i,
       'vview_si'  :vsip_vdestroy_si,
       'vview_uc'  :vsip_vdestroy_uc,
       'vview_bl'  :vsip_vdestroy_bl,
       'vview_vi'  :vsip_vdestroy_vi,
       'vview_mi'  :vsip_vdestroy_mi,
       'mview_f'   :vsip_mdestroy_f,
       'mview_d'   :vsip_mdestroy_d,
       'cmview_f'  :vsip_cmdestroy_f,
       'cmview_d'  :vsip_cmdestroy_d,
       'mview_i'   :vsip_mdestroy_i,
       'mview_si'  :vsip_mdestroy_si,
       'mview_uc'  :vsip_mdestroy_uc,
       'mview_bl'  :vsip_mdestroy_bl,
       'lu_d'      :vsip_lud_destroy_d,
       'lu_f'      :vsip_lud_destroy_f,
       'clu_d'     :vsip_clud_destroy_d,
       'clu_f'     :vsip_clud_destroy_f,
       'qr_d'      :vsip_qrd_destroy_d,
       'qr_f'      :vsip_qrd_destroy_f,
       'cqr_d'     :vsip_cqrd_destroy_d,
       'cqr_f'     :vsip_cqrd_destroy_f,
       'fft_f'     :vsip_fft_destroy_f,
       'fft_d'     :vsip_fft_destroy_d,
       'fftm_f'    :vsip_fftm_destroy_f,
       'fftm_d'    :vsip_fftm_destroy_d,
       'chol_f'    :vsip_chold_destroy_f,
       'chol_d'    :vsip_chold_destroy_d,
       'cchol_f'   :vsip_cchold_destroy_f,
       'cchol_d'   :vsip_cchold_destroy_d,
       'sv_f'      :vsip_svd_destroy_f,
       'sv_d'      :vsip_svd_destroy_d,
       'fir_f'     :vsip_fir_destroy_f,
       'fir_d'     :vsip_fir_destroy_d,
       'cfir_f'    :vsip_cfir_destroy_f,
       'cfir_d'    :vsip_cfir_destroy_d,
       'randstate' :vsip_randdestroy}
    t=getType(obj)[1]
    if f.has_key(t):
        return f[t](obj)
    else:
        print('Type ' + t + ' not supported by destroy')
        return False
     
# VSIPL scalar functions
# s on front denotes scalar and prevents conflict with overloaded view functions
def sconj(a):
    t=getType(a)[1]
    f={'cscalar_f':vsip_conj_f,
       'cscalar_d':vsip_conj_d}
    if f.has_key(t):
        return f[t](a)
    else:
        print('Type ' + t + ' not supported by sconj')
def scmplx(p,a,b):
    """
       p is a string designating a type, either scalar_f or scalar_d.
    """
    if p == 'scalar_f':
        return vsip_cmplx_f(a,b)
    elif p == 'scalar_d':
        return vsip_cmplx_d(a,b)
    else:
        print('Type ' + p + ' not defined for cmplx');
        return False
def scsub(a,b):
    t=getType(a)[1]
    if t != getType(b)[1]:
        print('Type of arguments must agree')
        return False
    if t == 'cscalar_f':
        return vsip_csub_f(a,b)
    elif t == 'cscalar_d':
        return vsip_csub_d(a,b)
    else:
        print('Type ' + p + ' not defined for complex subtraction')
        return False
def smag(a):
    if type(a) == float or type(a) == int:
        if(a < 0):
            return -a
        else:
            return a
    t = getType(a)[1]
    if t == 'cscalar_f':
        return vsip_cmag_f(a)
    elif t == 'cscalar_d':
        return vsip_cmag_d(a)
    else:
        print('Type ' + t + ' not recognized by mag');
        return False

def _vget(a,b): # used internal to this module
    f={ 'vview_f':vsip_vget_f,
        'vview_d':vsip_vget_d,
        'vview_i':vsip_vget_i,
        'vview_si':vsip_vget_si,
        'vview_uc':vsip_vget_uc,
        'vview_vi':vsip_vget_vi}
    if f.has_key(b):
        return [f[b](a,i) for i in range(getlength(a))]
    else:
        return False
def _cvget(a,b): # used internal to this module
   f={'cvview_f':vsip_cvget_f,
      'cvview_d':vsip_cvget_d}
   retval = []
   for i in range(getlength(a)):
       val=f[b](a,i)
       retval.append(complex(val.r,val.i))
   return retval
def _mget(a,b): # used internal to this module
   retval=list()
   attr = getattrib(a)
   f={ 'mview_f':vsip_mget_f,
       'mview_d':vsip_mget_d,
       'mview_i':vsip_mget_f,
       'mview_si':vsip_mget_si,
       'mview_uc':vsip_mget_uc}
   for i in range(attr.col_length):
      retval +=[f[b](a,i,j) for j in range(attr.row_length)]
   return retval
def _cvget(a,b): # used internal to this module
   f={'cvview_f':vsip_cvget_f,
      'cvview_d':vsip_cvget_d}
   return [cscalarToComplex(f[b](a,i)) for i in range(getlength(a))]
def _cmget(a,b): # used internal to this module
   retval=list()
   attr = getattrib(a)
   f={ 'cmview_f':vsip_cmget_f,
       'cmview_d':vsip_cmget_d}
   for i in range(attr.col_length):
      retval +=[cscalarToComplex(f[b](a,i,j)) for j in range(attr.row_length)]
   return retval
def _bl(a): # used internal to this module
   if a == 0:
      return False
   else:
      return True
def _vget_bl(a,b):
   return [_bl(vsip_vget_bl(a,i)) for i in range(getlength(a))]
def _mget_bl(a,b): # used internal to this module
   retval=list()
   attr=getattrib(a)
   for i in range(attr.col_length):
      retval += [_bl(vsip_mget_bl(a,i,j)) for j in range(attr.row_length)]
def _vget_mi(a,b): # used internal to this module
   return [miToTuple(vsip_vget_mi(a,i)) for i in range(getlength(a))]

def vList(v):
   """ 
      This function copies the data from a VSIPL view into a flat list. If
      the view is a matrix view it copies the data by row (flattens it). VSIP complex
      is copied into python complex. Type _bl (bool) is copied into True, False
      """
   t=getType(v)
   f={ 'vview_f': _vget,
       'vview_d': _vget,
       'mview_f': _mget,
       'mview_d': _mget,
       'cvview_f': _cvget,
       'cvview_d': _cvget,
       'cmview_f': _cmget,
       'cmview_d': _cmget,
       'vview_i':  _vget,
       'mview_i': _mget,
       'vview_si': _vget,
       'mview_si': _mget,
       'vview_uc': _vget,
       'mview_uc': _mget,
       'vview_vi': _vget,
       'vview_bl': _vget_bl,
       'mview_bl': _mget_bl,
       'vview_mi': _vget_mi}
   if t[0]:
      return f[t[1]](v,t[1])
   else:
      return list()
def mList(m):
    f={'mview_f':(),
       'mview_d':(),
       'cmview_f':(),
       'cmview_d':(),
       'mview_i':(),
       'mview_si':(),
       'mview_uc':(),
       'mview_bl':()}
    t=getType(m)
    l=[]
    if f.has_key(t[1]):
        attr=getattrib(m)
        attr0=getattrib(m)
        n=range(attr.col_length)
        attr.col_length=1
        putattrib(m,attr)
        for i in n:
            l.append(vList(m))
            attr.offset += attr.col_stride
            putattrib(m,attr)
        putattrib(m,attr0)
        return l
    else:
        print('not a supported type')
        return []
def listV(t,v):
    """
       This function is not very 'smart'
       This function creates a vsipl double or integer vector and copies a list into VSIPL. 
       It will only copy into vectors of type double (real or complex) or of type int.
       That is to say vectors of type vsip_vview_d, vsip_cvview_d, and vsip_vview_i.
       The list is expected to be of a float, integer, or Python complex type.
       It is expected to be flat. List of lists is not allowed here. No error 
       checking is done. 
       The input list must be of a single type (integer, complex, float). The first element
       of the list is checked and depending on the result a vsipl vector is created and list
       comprehension is used to copy it into VSIPL.
       If things don't work out python will probably complain.
       """
    n=len(v)
    f={'vview_d':vsip_vcreate_d,
       'vview_f':vsip_vcreate_f}
    if isinstance(v[0],float) and f.has_key(t):
        retval=f[t](n,VSIP_MEM_NONE)
        [put(retval,i,v[i]) for i in range(n)]
        return retval
    elif isinstance(v[0],int):
        retval=vsip_vcreate_i(n,VSIP_MEM_NONE)
        [put(retval,i,v[i]) for i in range(n)]
        return retval
    elif isinstance(v[0],complex):
        retval=vsip_cvcreate_d(n,VSIP_MEM_NONE)
        [put(retval,i,v[i]) for i in range(n)]
        return retval
    else:
        print('listV failed')
        return False

def _sizeVattr(a): # used internal to this module
    return a.offset + a.length * abs(a.stride);
def _sizeMattr(a): # used internal to this module
    str_r=abs(a.row_stride)
    str_c=abs(a.col_stride)
    if str_r > str_c:
        return a.offset + str_r * a.row_length
    else:
        return a.offset + str_c * a.col_length
def _sizeAttr(a):
    f={ 'vattr_f': _sizeVattr,
        'vattr_d': _sizeVattr,
        'cvattr_f':_sizeVattr,
        'cvattr_d':_sizeVattr,
        'vattr_vi':_sizeVattr,
        'vattr_mi':_sizeVattr,
        'vattr_bl':_sizeVattr,
        'vattr_i': _sizeVattr,
        'vattr_si':_sizeVattr,
        'vattr_uc':_sizeVattr,
        'mattr_f': _sizeMattr,
        'mattr_d': _sizeMattr,
        'cmattr_f':_sizeMattr,
        'cmattr_d':_sizeMattr,
        'mattr_bl':_sizeMattr,
        'mattr_i': _sizeMattr,
        'mattr_si':_sizeMattr,
        'mattr_uc':_sizeMattr}
    t=getType(a)
    return f[t[1]](a)
def _blocktype(vt): # used internal to this module
    f=f={   'vattr_f':'block_f',
            'vattr_d':'block_d',
            'cvattr_f':'cblock_f',
            'cvattr_d':'cblock_d',
            'mattr_f':'block_f',
            'mattr_d':'block_d',
            'cmattr_f':'cblock_f',
            'cmattr_d':'cblock_d',
            'vattr_vi':'block_vi',
            'vattr_mi':'block_mi', 
            'vattr_bl':'block_bl',
            'vattr_i':'block_i',
            'vattr_si':'block_si',
            'vattr_uc':'block_uc',
            'mattr_bl':'block_bl',
            'mattr_i':'block_i',
            'mattr_si':'block_si',
            'mattr_uc':'block_uc'}
    return f[vt]
def _blockcreate(l,t): # used internal to this module
    f={ 'block_f':vsip_blockcreate_f,
        'block_d':vsip_blockcreate_d,
        'cblock_f':vsip_cblockcreate_f,
        'cblock_d':vsip_cblockcreate_d,
        'block_i':vsip_blockcreate_i,
        'block_si':vsip_blockcreate_si,
        'block_uc':vsip_blockcreate_uc,
        'block_vi':vsip_blockcreate_vi,
        'block_mi':vsip_blockcreate_mi,
        'block_bl':vsip_blockcreate_bl}
    return f[t](l,VSIP_MEM_NONE)
# VU Functions
def dataGen(a):
    print getType(a)[1]
    from math import cos as ccos,sin as ssin,pi
    def _gen(a):
        print getType(a)[1]
        N=int(getlength(a))
        print(repr(N))
        if(N==0):
            return False
        npm=N/2
        c=pi/float(N)
        put(a,0,(float(N) - 1.0)/2.0)
        indx=0;
        if N % 2:
            for i in range(npm):
                indx = i+1
                x = c * float(i) + c
                x = -0.5j * ccos(x)/ssin(x)  - 0.5
                put(a,indx,x)
            for i in range(npm,0,-1):
                indx +=1
                x=get(a,i)
                x.i=-x.i
                put(a,indx,x)
        else:
            npm -= 1
            for i in range(npm):
               indx = i+1
               x = c * float(i) + c
               x = -0.5j * ccos(x)/ssin(x)  - 0.5
               put(a,indx,x)
            x=-0.5
            indx +=1
            put(a,indx,x)
            for i in range(npm,0,-1):
                indx +=1
                x=get(a,i)
                x.i=-x.i
                put(a,indx,x)
    t=getType(a)
    sz=()
    if t[0]:
        sz=size(a)
    if len(sz) == 3 and (t[1] == 'cvview_f' or t[1] == 'cvview_d'):
        _gen(a)
        return a
    else:
        print('Not a supported type. Should be a vsip complex float vector vector')
        return False  
def randCreate(t,seed,length):
    """
       Create a VSIPL vector view and populate it with random numbers.
       type "t" is (for example) 'vview_dnprngU' for double vector ('vview_d') filled with
       uniform ('U') numbers from the non-portable random number generator ('nprng => VSIP_NPRNG').
       Another example would be 'cvview_fprngN' for a complex float vector('cvview_f')
       tilled with a normal distribution ('N') from the VSIP defined portable random number
       generator ('prng' => VSIP_PRNG).
    """
    def rcfn(t,s,f,l):
        a=view('vview_d',l);
        s=rand(s,1,1,f)
        randn(s,a)
        randDestroy(s)
        return a
    def rcfu(t,s,f,l):
        a=view('vview_d',l);
        s=rand(s,1,1,f)
        randu(s,a)
        randDestroy(s)
        return a
    f={'vview_dprngN':"rcfn('vview_d',seed,VSIP_PRNG,length)",
       'vview_fprngN':"rcfn('vview_f',seed,VSIP_PRNG,length)",
       'cvview_dprngN':"rcfn('cvview_d',seed,VSIP_PRNG,length)",
       'cvview_fprngN':"rcfn('cvview_f',seed,VSIP_PRNG,length)",
       'vview_dprngU':"rcfu('vview_d',seed,VSIP_PRNG,length)",
       'vview_fprngU':"rcfu('vview_f',seed,VSIP_PRNG,length)",
       'cvview_dprngU':"rcfu('cvview_d',seed,VSIP_PRNG,length)",
       'cvview_fprngU':"rcfu('cvview_f',seed,VSIP_PRNG,length)",
       'vview_dnprngN':"rcfn('vview_d',seed,VSIP_NPRNG,length)",
       'vview_fnprngN':"rcfn('vview_d',seed,VSIP_NPRNG,length)",
       'cvview_dnprngN':"rcfn('cvview_d',seed,VSIP_NPRNG,length)",
       'cvview_fnprngN':"rcfn('cvview_f',seed,VSIP_NPRNG,length)",
       'vview_dnprngU':"rcfu('vview_d',seed,VSIP_NPRNG,length)",
       'vview_fnprngU':"rcfu('vview_f',seed,VSIP_NPRNG,length)",
       'cvview_dnprngU':"rcfu('cvview_d',seed,VSIP_NPRNG,length)",
       'cvview_fnprngU':"rcfu('cvview_f',seed,VSIP_NPRNG,length)"}
    if f.has_key(t):
        return eval(f[t])
    else:
        print('Type ' + t + ' not supported for randCreate')
        return False

# functions not closely related to VSIPL defined functionality
def viewCreate(a):
    """
        Create a vsip view object. The argument "a" is a view attribute. Use the attribute type 
        and attribute state to create a view object. Return object on success, and False on failure
        NOTE: The size of the underlying block is the magnitutde of the maximum stride times the length
        of dimension associated with the stride plus the offset. This produces a block at least big 
        enough to accomodate the view associated with the attribute. If a particular block size is 
        required first create the block using the standard vsipl block create, and then create the 
        view using vbind or mbind and then (if vbind or mbind are not sufficient) put the attribute 
        using putattrib.
        """
    t=getType(a)
    f={ 'vattr_f':putattrib(vbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1),a),
        'vattr_d':putattrib(vbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1),a),
        'cvattr_f':putattrib(vbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1),a),
        'cvattr_d':putattrib(vbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1),a),
        'vattr_vi':putattrib(vbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1),a),
        'vattr_mi':putattrib(vbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1),a),
        'vattr_bl':putattrib(vbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1),a),
        'vattr_i':putattrib(vbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1),a),
        'vattr_si':putattrib(vbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1),a),
        'vattr_uc':putattrib(vbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1),a),
        'mattr_f':putattrib(mbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1,1,1),a),
        'mattr_d':putattrib(mbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1,1,1),a),
        'cmattr_f':putattrib(mbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1,1,1),a),
        'cmattr_d':putattrib(mbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1,1,1),a),
        'mattr_bl':putattrib(mbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1,1,1),a),
        'mattr_i':putattrib(mbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1,1,1),a),
        'mattr_si':putattrib(mbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1,1,1),a),
        'mattr_uc':putattrib(mbind(_blockcreate(_sizeAttr(a),_blocktype(t[1])),0,1,1,1,1),a)}
    if t[0] and f.has_key(t[1]):
        return f[t[1]]
    else:
        return False
def associatedView(v,attr):
    f={ 'block_fvattr_f':'putattrib(vbind(blk,0,1,1),attr)',
        'block_dvattr_d':'putattrib(vbind(blk,0,1,1),attr)',
        'cblock_fcvattr_f':'putattrib(vbind(blk,0,1,1),attr)',
        'cblock_dcvattr_d':'putattrib(vbind(blk,0,1,1),attr)',
        'block_vivattr_vi':'putattrib(vbind(blk,0,1,1),attr)',
        'block_mivattr_mi':'putattrib(vbind(blk,0,1,1),attr)',
        'block_blvattr_bl':'putattrib(vbind(blk,0,1,1),attr)',
        'block_ivattr_i':'putattrib(vbind(blk,0,1,1),attr)',
        'block_sivattr_si':'putattrib(vbind(blk,0,1,1),attr)',
        'block_ucvattr_uc':'putattrib(vbind(blk,0,1,1),attr)',
        'block_fmattr_f':'putattrib(mbind(blk,0,1,1,1,1),attr)',
        'block_dmattr_d':'putattrib(mbind(blk,0,1,1,1,1),attr)',
        'cblock_fcmattr_f':'putattrib(mbind(blk,0,1,1,1,1),attr)',
        'cblock_dcmattr_d':'putattrib(mbind(blk,0,1,1,1,1),attr)',
        'block_blmattr_bl':'putattrib(mbind(blk,0,1,1,1,1),attr)',
        'block_imattr_i':'putattrib(mbind(blk,0,1,1,1,1),attr)',
        'block_simattr_si':'putattrib(mbind(blk,0,1,1,1,1),attr)',
        'block_ucmattr_uc':'putattrib(mbind(blk,0,1,1,1,1),attr)'}
    t2=getType(attr)
    t=str()
    if(getType(v)[0] and t2[0]):
        vattr=getattrib(v)
        blk=vattr.block
        t1=getType(blk)
        t=t1[1]+t2[1]
    if f.has_key(t):
        return eval(f[t])
    else:
        print('Not a supported type')
        return False
def attr(t,l):
    """
       This function creates and returns an initialized attribute object.
       Note the block attribute is not filled out.
       The Argument "l" is a list or tuple of (offset, stride, length) for a vector
       or (offset, col_stride, col_length, row_stride, row_length) for a matrix
       
       """
    f={'vview_f':'vsip_vattr_f()',
       'vview_vi':'vsip_vattr_vi()',
       'vview_d':  'vsip_vattr_d()',
       'cvview_f':'vsip_cvattr_f()',
       'cvview_d':'vsip_cvattr_d()',
       'vview_bl':'vsip_vattr_bl()',
       'vview_i':  'vsip_vattr_i()',
       'vview_mi':'vsip_vattr_mi()',
       'vview_si':'vsip_vattr_si()',
       'vview_uc':'vsip_vattr_si()',
       'mview_d':  'vsip_mattr_d()',
       'mview_f':  'vsip_mattr_f()',
       'cmview_d':'vsip_cmattr_d()',
       'cmview_f':'vsip_cmattr_f()',
       'mview_i':  'vsip_mattr_i()',
       'mview_si':'vsip_mattr_si()',
       'mview_uc':'vsip_mattr_uc()',
       'mview_bl':  'vsip_mattr_bl'}
    def _vattr(a,l):
        a.offset=l[0]
        a.stride=l[1]
        a.length=l[2]
    def _mattr(a,l):
        a.offset=l[0]
        a.col_stride=l[1]
        a.col_length=l[2]
        a.row_stride=l[3]
        a.col_stride=l[4]
    if f.has_key(t):
        a = eval(f[t])
        if len(l) == 3:
            _vattr(a,l)
            return a
        elif len(l) == 5:
            _mattr(a,l)
            return a
        else:
            print('Incorrect list argument') 
            return False
    else:
       print('not a supported type')
       return False
def size(a):
    f={'vview_d':'_vsize(getattrib(a))',
       'vview_f': '_vsize(getattrib(a))',
       'cvview_d':'_vsize(getattrib(a))',
       'cvview_f':'_vsize(getattrib(a))',
       'vview_vi':'_vsize(getattrib(a))',
       'vview_mi':'_vsize(getattrib(a))',
       'vview_bl':'_vsize(getattrib(a))',
       'vview_i':'_vsize(getattrib(a))',
       'vview_si':'_vsize(getattrib(a))',
       'vview_uc':'_vsize(getattrib(a))',
       'mview_d':'_msize(getattrib(a))',
       'mview_f':'_msize(getattrib(a))',
       'cmview_d':'_msize(getattrib(a))',
       'cmview_f':'_msize(getattrib(a))',
       'mview_bl':'_msize(getattrib(a))',
       'mview_i':'_msize(getattrib(a))',
       'mview_si':'_msize(getattrib(a))',
       'mview_uc':'_msize(getattrib(a))'}
    def _vsize(attr):
        return (attr.offset,attr.stride,attr.length)
    def _msize(attr):
        return (attr.offset,attr.col_stride,attr.col_length,attr.row_stride, attr.col_stride)
    t=getType(a)
    if f.has_key(t[1]):
        return eval(f[t[1]])
    else:
        print('Not a supported type')
        return False

# view => vcreate,mcreate, ..
# block => blockcreate
# bind => vbind, mbind, ...
def block(t,l):
    """
        Function "block(t,l) creates a block of type t and length l
    """
    f={ 'block_f':vsip_blockcreate_f,
        'block_d':vsip_blockcreate_d,
        'cblock_f':vsip_cblockcreate_f,
        'cblock_d':vsip_cblockcreate_d,
        'block_i':vsip_blockcreate_i,
        'block_si':vsip_blockcreate_si,
        'block_uc':vsip_blockcreate_uc,
        'block_vi':vsip_blockcreate_vi,
        'block_mi':vsip_blockcreate_mi,
        'block_bl':vsip_blockcreate_bl}
    if f.has_key(t):
        return f[t](l,VSIP_MEM_NONE)
    else:
        print('Not a supported block type')
        return False
def bind(blk,l_in):
    """
        The function "bind(blk,l)" binds a view to a block.
        The attributes of the view are determined by a tuple "l".
        If the tuple is of length 3 then a vector is assumed.
        If the tupe is of length 5 then a matrix is assumed.
        vector tuple is (offset, stride, length)
        matrix tuple is (offset, col_stride, col_length, row_stride, row_length)
        Precision is determined by the block type.
    """
    f={ 'block_fvector':'vsip_vbind_f(blk,l[0],l[1],l[2])',
        'block_dvector':'vsip_vbind_d(blk,l[0],l[1],l[2])',
        'cblock_fvector':'vsip_cvbind_f(blk,l[0],l[1],l[2])',
        'cblock_dvector':'vsip_cvbind_d(blk,l[0],l[1],l[2])',
        'block_ivector':'vsip_vbind_i(blk,l[0],l[1],l[2])',
        'block_sivector':'vsip_vbind_si(blk,l[0],l[1],l[2])',
        'block_ucvector':'vsip_vbind_uc(blk,l[0],l[1],l[2])',
        'block_vivector':'vsip_vbind_vi(blk,l[0],l[1],l[2])',
        'block_mivector':'vsip_vbind_mi(blk,l[0],l[1],l[2])',
        'block_blvector':'vsip_vbind_bl(blk,l[0],l[1],l[2])',
        'block_fmatrix':'vsip_mbind_f(blk,l[0],l[1],l[2],l[3],l[4])',
        'block_dmatrix':'vsip_mbind_d(blk,l[0],l[1],l[2],l[3],l[4])',
        'cblock_fmatrix':'vsip_cmbind_f(blk,l[0],l[1],l[2],l[3],l[4])',
        'cblock_dmatrix':'vsip_cmbind_d(blk,l[0],l[1],l[2],l[3],l[4])',
        'block_imatrix':'vsip_mbind_i(blk,l[0],l[1],l[2],l[3],l[4])',
        'block_simatrix':'vsip_mbind_si(blk,l[0],l[1],l[2],l[3],l[4])',
        'block_ucmatrix':'vsip_mbind_uc(blk,l[0],l[1],l[2],l[3],l[4])',
        'block_blmatrix':'vsip_mbind_bl(blk,l[0],l[1],l[2],l[3],l[4])'}
    t=getType(blk)[1]
    t_l=type(l_in)
    if t_l == tuple:
        l=[item for item in l_in]
    elif t_l == list:
        l=l_in
    else:
        print("Argument two in bind must be a tuple or list of attribues \
               for a vector or matrix")
        return False
    if len(l) == 3:
        t+='vector'
    elif len(l) == 5:
        t+='matrix'
    if f.has_key(t):
        return eval(f[t])
    else:
        print('Bind has no type ' + t)
        return False
def view(t,l_in):
    """
       This function creates a vector or matrix view including vector views associated
       with a window function (hanning,blackman,kaiser, cheby). 
       Note: To make this as a single call for all view creates the first parameter
       is the type and the second parameter is a tuple with three entries as
       indicated. The value of the entries are the same as for the vsip function call.
       the second and/or third entries may be ignored if the type does not need them.
       See the VSIPL specification for additional clues. 
       The calling convention
       for a float vector is: 
       view('vview_f',(length))
       Note the first argument is a view type with associated precision 
       (_f, _d, _vi, _si, _i, _uc, _mi)
       for a float matrix the call is: 
       view('mview_f',(col_length, row_length,VSIP_ROW))
       for row major. Use VSIP_COL for column major.
       for a window function use: (note _d is also supported):
       view('blackman_f',(length))
       view('hanning_f',(length))
       view('kaiser_f',(length,float parameter))
       view('cheby_f',(length,float parameter))
      
       """
    f={'blackman_d':'vsip_vcreate_blackman_d(l[0], VSIP_MEM_NONE)',
       'hanning_d':'vsip_vcreate_hanning_d(l[0], VSIP_MEM_NONE)',
       'kaiser_d':'vsip_vcreate_kaiser_d(l[0], l[1], VSIP_MEM_NONE)',
       'cheby_d':'vsip_vcreate_cheby_d(l[0], l[1], VSIP_MEM_NONE)',
       'blackman_f':'vsip_vcreate_blackman_f(l[0], VSIP_MEM_NONE)',
       'hanning_f':'vsip_vcreate_hanning_f(l[0], VSIP_MEM_NONE)',
       'kaiser_f':'vsip_vcreate_kaiser_f(l[0],l[1],  VSIP_MEM_NONE)',
       'cheby_f':'vsip_vcreate_cheby_f(l[0], l[1], VSIP_MEM_NONE)',
       'vview_f':'vsip_vcreate_f( l[0], VSIP_MEM_NONE)',
       'vview_vi':'vsip_vcreate_vi( l[0], VSIP_MEM_NONE)',
       'vview_d':'vsip_vcreate_d( l[0], VSIP_MEM_NONE)',
       'cvview_f':'vsip_cvcreate_f( l[0], VSIP_MEM_NONE)',
       'cvview_d':'vsip_cvcreate_d( l[0], VSIP_MEM_NONE)',
       'vview_bl':'vsip_vcreate_bl(l[0], VSIP_MEM_NONE)',
       'vview_i':'vsip_vcreate_i(l[0], VSIP_MEM_NONE)',
       'vview_mi':'vsip_vcreate_mi(l[0], VSIP_MEM_NONE)',
       'vview_si':'vsip_vcreate_si(l[0], VSIP_MEM_NONE)',
       'vview_uc':'vsip_vcreate_uc(l[0], VSIP_MEM_NONE)',
       'mview_d':'vsip_mcreate_d(l[0],l[1],l[2],VSIP_MEM_NONE)',
       'mview_f':'vsip_mcreate_f(l[0],l[1],l[2],VSIP_MEM_NONE)',
       'cmview_d':'vsip_cmcreate_d(l[0],l[1],l[2],VSIP_MEM_NONE)',
       'cmview_f':'vsip_cmcreate_f(l[0],l[1],l[2],VSIP_MEM_NONE)',
       'mview_i':'vsip_mcreate_i(l[0],l[1],l[2],VSIP_MEM_NONE)',
       'mview_si':'vsip_mcreate_si(l[0],l[1],l[2],VSIP_MEM_NONE)',
       'mview_uc':'vsip_mcreate_uc(l[0],l[1],l[2],VSIP_MEM_NONE)',
       'mview_bl':'vsip_mcreate_bl(l[0],l[1],l[2],VSIP_MEM_NONE)'}
    l=[]
    tl = type(l_in)
    if tl == int:
        l.append(l_in)
    elif tl == tuple:
        for item in l_in:
            l.append(item)
    elif t1 == list:
        l=l_in
    else:
        print('Attribute input argument is not list, tuple, or int length')
        return False   
    if f.has_key(t):
        return eval(f[t])
    else:
        print('Type argument not a supported type')
        return False

# Other Support Functions
def getblock(v):
    return getattrib(v).block
def mbind(block,o,cs,cl,rs,rl):
    t=getType(block);
    f={   'block_f':vsip_mbind_f,
          'block_d':vsip_mbind_d,
          'cblock_f':vsip_cmbind_f,
          'cblock_d':vsip_cmbind_d,
          'block_i':vsip_mbind_i,
          'block_si':vsip_mbind_si,
          'block_uc':vsip_mbind_uc,
          'block_bl':vsip_mbind_bl}
    if t[0] and f.has_key(t[1]):
        return f[t[1]](block,o,cs,cl,rs,rl)
    else:
        return False
def vbind(block,o,s,l):
    t=getType(block);
    f={ 'block_f':vsip_vbind_f,
          'block_d':vsip_vbind_d,
          'cblock_f':vsip_cvbind_f,
          'cblock_d':vsip_cvbind_d,
          'block_i':vsip_vbind_i,
          'block_si':vsip_vbind_si,
          'block_uc':vsip_vbind_uc,
          'block_vi':vsip_vbind_vi,
          'block_mi':vsip_vbind_mi,
          'block_bl':vsip_vbind_bl}
    if t[0] and f.has_key(t[1]):
        return f[t[1]](block,o,s,l)
    else:
        return False
def getattrib(a):
    """
        Return the attribute of a VSIPL view.
        NOTE:
        Unlike the C vsipl function this function will create the attribute (you don't pass one in).
        This function is shorthand for (for instance in the float case):
        attr = vsip_vattr_f()
        and then using the C VSIPL interface do
        vsip_vgetattrib_f(a,attr)
        which will fill in the attr object.
        Note that the example is typed but this function gets the type by checking the input view.
        """
    t=getType(a)
    f={ 'vview_f': (vsip_vgetattrib_f,vsip_vattr_f),
        'vview_d': (vsip_vgetattrib_d,vsip_vattr_d),
        'mview_f': (vsip_mgetattrib_f,vsip_mattr_f),
        'mview_d': (vsip_mgetattrib_d,vsip_mattr_d),
        'cvview_f':(vsip_cvgetattrib_f,vsip_cvattr_f),
        'cvview_d':(vsip_cvgetattrib_d,vsip_cvattr_d),
        'cmview_f':(vsip_cmgetattrib_f,vsip_cmattr_f),
        'cmview_d':(vsip_cmgetattrib_d,vsip_cmattr_d),
        'vview_i': (vsip_vgetattrib_i,vsip_vattr_i),
        'mview_i': (vsip_mgetattrib_i,vsip_mattr_i),
        'vview_si':(vsip_vgetattrib_si,vsip_vattr_si),
        'mview_si':(vsip_mgetattrib_si,vsip_mattr_si),
        'vview_uc':(vsip_vgetattrib_uc,vsip_vattr_uc),
        'mview_uc':(vsip_mgetattrib_uc,vsip_mattr_uc),
        'vview_vi':(vsip_vgetattrib_vi,vsip_vattr_vi),
        'vview_bl':(vsip_vgetattrib_bl,vsip_vattr_bl),
        'mview_bl':(vsip_mgetattrib_bl,vsip_mattr_bl),
        'vview_mi':(vsip_vgetattrib_mi,vsip_vattr_mi),
        'cfir_d':(vsip_cfir_getattr_d,vsip_cfir_attr),
        'cfir_f':(vsip_cfir_getattr_f,vsip_cfir_attr),
        'fir_d':(vsip_fir_getattr_f,vsip_fir_attr),
        'fir_f':(vsip_fir_getattr_f,vsip_fir_attr),
        'lu_f':(vsip_lud_getattr_f,vsip_lu_attr_f),
        'clu_f':(vsip_clud_getattr_f,vsip_clu_attr_f),
        'lu_d':(vsip_lud_getattr_d,vsip_lu_attr_d),
        'clu_d':(vsip_clud_getattr_d,vsip_clu_attr_d),
        'chol_f':(vsip_chold_getattr_f,vsip_chol_attr_f),
        'cchol_f':(vsip_cchold_getattr_f,vsip_cchol_attr_f),
        'chol_d':(vsip_chold_getattr_d,vsip_chol_attr_d),
        'cchold_d':(vsip_cchold_getattr_d,vsip_cchol_attr_d),
        'qr_f':(  vsip_qrd_getattr_f,vsip_qr_attr_f),
        'cqr_f':(vsip_cqrd_getattr_f,vsip_cqr_attr_f),
        'qr_d':(  vsip_qrd_getattr_d,vsip_qr_attr_d),
        'cqr_d':(vsip_cqrd_getattr_d,vsip_cqr_attr_d)}
    if t[0] and f.has_key(t[1]):
        attr = f[t[1]][1]()
        f[t[1]][0](a,attr)
        return attr
    else:
        print('Type ' + t[1] + ' Not supported for getattrib')
        return False
def putattrib(a,attr):
    """
        Change the attributes of a vector view object
        """
    t1=getType(a)
    t2=getType(attr)
    t=t1[1]+t2[1]
    f={ 'vview_fvattr_f':vsip_vputattrib_f,
        'vview_dvattr_d':vsip_vputattrib_d,
        'cvview_fcvattr_f':vsip_cvputattrib_f,
        'cvview_dcvattr_d':vsip_cvputattrib_d,
        'mview_fmattr_f':vsip_mputattrib_f,
        'mview_dmattr_d':vsip_mputattrib_d,
        'cmview_fcmattr_f':vsip_cmputattrib_f,
        'cmview_dcmattr_d':vsip_cmputattrib_d,
        'vview_vivattr_vi':vsip_vputattrib_vi,
        'vview_mivattr_mi':vsip_vputattrib_mi,
        'vview_blvattr_bl':vsip_vputattrib_bl,
        'vview_ivattr_i':vsip_vputattrib_i,
        'vview_sivattr_si':vsip_vputattrib_si,
        'vview_ucvattr_uc':vsip_vputattrib_uc,
        'mview_blmattr_bl':vsip_mputattrib_bl,
        'mview_imattr_i':vsip_mputattrib_i,
        'mview_simattr_si':vsip_mputattrib_si,
        'mview_ucmattr_uc':vsip_mputattrib_uc}
    if t1[0] and t2[0]:
        if f.has_key(t):
            return f[t](a,attr)
        else:
            return 0
    else:
        return 0
def getoffset(a):
    """
        Get the offset of a view object
        """
    t=getType(a)
    f={'vview_f':vsip_vgetoffset_f,
        'mview_f':vsip_mgetoffset_f,
        'vview_d':vsip_vgetoffset_d,
        'mview_d':vsip_mgetoffset_d,
        'vview_i':vsip_vgetoffset_i,
        'mview_i':vsip_mgetoffset_i,
        'vview_si':vsip_vgetoffset_si,
        'mview_si':vsip_mgetoffset_si,
        'vview_uc':vsip_vgetoffset_uc,
        'mview_uc':vsip_mgetoffset_uc,
        'vview_vi':vsip_vgetoffset_vi,
        'cvview_f':vsip_cvgetoffset_f,
        'cmview_f':vsip_cmgetoffset_f,
        'cvview_d':vsip_cvgetoffset_d,
        'cmview_d':vsip_cmgetoffset_d,
        'vview_mi':vsip_vgetoffset_mi }
    if t[0] and f.has_key(t[1]):
        return f[t[1]](a)
    else:
        print('not a supported type for getoffset')
        return 0
def putoffset(a,s):
    """
        Change the offset of a view object
        """
    t=getType(a)
    f={'vview_f':vsip_vputoffset_f,
        'mview_f':vsip_mputoffset_f,
        'vview_d':vsip_vputoffset_d,
        'mview_d':vsip_mputoffset_d,
        'vview_i':vsip_vputoffset_i,
        'mview_i':vsip_mputoffset_i,
        'vview_si':vsip_vputoffset_si,
        'mview_si':vsip_mputoffset_si,
        'vview_uc':vsip_vputoffset_uc,
        'mview_uc':vsip_mputoffset_uc,
        'vview_vi':vsip_vputoffset_vi,
        'cvview_f':vsip_cvputoffset_f,
        'cmview_f':vsip_cmputoffset_f,
        'cvview_d':vsip_cvputoffset_d,
        'cmview_d':vsip_cmputoffset_d,
        'vview_mi':vsip_vputoffset_mi }
    if t[0] and f.has_key(t[1]):
        return f[t[1]](a,s)
    else:
        print('not a supported type for putoffset')
        return 0
def getstride(a):
    """
        Get the stride of a vector view object
        """
    t=getType(a)
    f={'vview_f':vsip_vgetstride_f,
        'vview_d':vsip_vgetstride_d,
        'vview_i':vsip_vgetstride_i,
        'vview_si':vsip_vgetstride_si,
        'vview_uc':vsip_vgetstride_uc,
        'vview_vi':vsip_vgetstride_vi,
        'cvview_f':vsip_cvgetstride_f,
        'cvview_d':vsip_cvgetstride_d,
        'vview_mi':vsip_vgetstride_mi }
    if t[0]  and f.has_key(t[1]):
        return f[t[1]](a)
    else:
        return 0
def putstride(a,s):
    """
        Change the stride of a vector view object
        """
    t=getType(a)
    f={ 'vview_f':vsip_vputstride_f,
        'vview_d':vsip_vputstride_d,
        'vview_i':vsip_vputstride_i,
        'vview_si':vsip_vputstride_si,
        'vview_uc':vsip_vputstride_uc,
        'vview_vi':vsip_vputstride_vi,
        'cvview_f':vsip_cvputstride_f,
        'cvview_d':vsip_cvputstride_d,
        'vview_mi':vsip_vputstride_mi }
    if t[0]:
        return f[t[1]](a,s)
    else:
        return 0
def getlength(a):
    """
        Get the length of a vector view object
        """
    t=getType(a)
    f={'vview_f':vsip_vgetlength_f,
       'vview_d':vsip_vgetlength_d,
       'vview_i':vsip_vgetlength_i,
       'vview_si':vsip_vgetlength_si,
       'vview_uc':vsip_vgetlength_uc,
       'vview_vi':vsip_vgetlength_vi,
       'cvview_f':vsip_cvgetlength_f,
       'cvview_d':vsip_cvgetlength_d,
       'vview_mi':vsip_vgetlength_mi }
    if t[0]:
        return f[t[1]](a)
    else:
        return 0
def putlength(a,l):
    """
        Change the length of a vector view object
        """
    t=getType(a)
    f={'vview_f':vsip_vputlength_f,
        'vview_d':vsip_vputlength_d,
        'vview_i':vsip_vputlength_i,
        'vview_si':vsip_vputlength_si,
        'vview_uc':vsip_vputlength_uc,
        'vview_vi':vsip_vputlength_vi,
        'cvview_f':vsip_cvputlength_f,
        'cvview_d':vsip_cvputlength_d,
        'vview_mi':vsip_vputlength_mi }
    if t[0]:
        return f[t[1]](a,l)
    else:
        return 0
def getrowstride(a):
    """
        Get the stride of a matrix view object
        """
    t=getType(a)
    f={'mview_f':vsip_mgetrowstride_f,
        'mview_d':vsip_mgetrowstride_d,
        'mview_i':vsip_mgetrowstride_i,
        'mview_si':vsip_mgetrowstride_si,
        'mview_uc':vsip_mgetrowstride_uc,
        'mview_vi':vsip_mgetrowstride_vi,
        'cmview_f':vsip_cmgetrowstride_f,
        'cmview_d':vsip_cmgetrowstride_d }
    if t[0]  and f.has_key(t[1]):
        return f[t[1]](a)
    else:
        print('not a supported type for getrowstride')
        return 0
def getcolstride(a):
    """
        Get the stride of a matrix view object
        """
    t=getType(a)
    f={'mview_f':vsip_mgetcolstride_f,
        'mview_d':vsip_mgetcolstride_d,
        'mview_i':vsip_mgetcolstride_i,
        'mview_si':vsip_mgetcolstride_si,
        'mview_uc':vsip_mgetcolstride_uc,
        'mview_vi':vsip_mgetcolstride_vi,
        'cmview_f':vsip_cmgetcolstride_f,
        'cmview_d':vsip_cmgetcolstride_d }
    if t[0]  and f.has_key(t[1]):
        return f[t[1]](a)
    else:
        print('not a supported type for getcolstride')
        return 0
def getrowlength(a):
    """
        Get the length of a matrix view object
        """
    t=getType(a)
    f={'mview_f':vsip_mgetrowlength_f,
        'mview_d':vsip_mgetrowlength_d,
        'mview_i':vsip_mgetrowlength_i,
        'mview_si':vsip_mgetrowlength_si,
        'mview_uc':vsip_mgetrowlength_uc,
        'cmview_f':vsip_cmgetrowlength_f,
        'cmview_d':vsip_cmgetrowlength_d }
    if t[0]  and f.has_key(t[1]):
        return f[t[1]](a)
    else:
        print('not a supported type for getrowlength')
        return 0
def getcollength(a):
    """
        Get the length of a matrix view object
        """
    t=getType(a)
    f={'mview_f':vsip_mgetcollength_f,
        'mview_d':vsip_mgetcollength_d,
        'mview_i':vsip_mgetcollength_i,
        'mview_si':vsip_mgetcollength_si,
        'mview_uc':vsip_mgetcollength_uc,
        'cmview_f':vsip_cmgetcollength_f,
        'cmview_d':vsip_cmgetcollength_d }
    if t[0]  and f.has_key(t[1]):
        return f[t[1]](a)
    else:
        print('not a supported type for getcollength')
        return 0
def putrowstride(a,s):
    """
        Put the stride of a matrix view object
        """
    t=getType(a)
    f={'mview_f':vsip_mputrowstride_f,
        'mview_d':vsip_mputrowstride_d,
        'mview_i':vsip_mputrowstride_i,
        'mview_si':vsip_mputrowstride_si,
        'mview_uc':vsip_mputrowstride_uc,
        'mview_bl':vsip_mputrowstride_bl,
        'cmview_f':vsip_cmputrowstride_f,
        'cmview_d':vsip_cmputrowstride_d }
    if t[0]  and f.has_key(t[1]):
        return f[t[1]](a,s)
    else:
        print('Not a supported type for putrowstride')
        return 0
def putcolstride(a,s):
    """
        Put the stride of a matrix view object
        """
    t=getType(a)
    f={'mview_f':vsip_mputcolstride_f,
        'mview_d':vsip_mputcolstride_d,
        'mview_i':vsip_mputcolstride_i,
        'mview_si':vsip_mputcolstride_si,
        'mview_uc':vsip_mputcolstride_uc,
        'mview_bl':vsip_mputcolstride_bl,
        'cmview_f':vsip_cmputcolstride_f,
        'cmview_d':vsip_cmputcolstride_d }
    if t[0]  and f.has_key(t[1]):
        return f[t[1]](a,s)
    else:
        print('not a supported type for putcolstride')
        return 0
def putrowlength(a,l):
    """
        Put the length of a matrix view object
        """
    t=getType(a)
    f={'mview_f':vsip_mputrowlength_f,
        'mview_d':vsip_mputrowlength_d,
        'mview_i':vsip_mputrowlength_i,
        'mview_si':vsip_mputrowlength_si,
        'mview_uc':vsip_mputrowlength_uc,
        'cmview_f':vsip_cmputrowlength_f,
        'cmview_d':vsip_cmputrowlength_d }
    if t[0]  and f.has_key(t[1]):
        return f[t[1]](a,l)
    else:
        print('not a supported type for getrowlength')
        return 0
def putcollength(a,l):
    """
        Put the length of a matrix view object
        """
    t=getType(a)
    f={'mview_f':vsip_mputcollength_f,
        'mview_d':vsip_mputcollength_d,
        'mview_i':vsip_mputcollength_i,
        'mview_si':vsip_mputcollength_si,
        'mview_uc':vsip_mputcollength_uc,
        'cmview_f':vsip_cmputcollength_f,
        'cmview_d':vsip_cmputcollength_d }
    if t[0]  and f.has_key(t[1]):
        return f[t[1]](a,l)
    else:
        print('not a supported type for putcollength')
        return 0
def cloneview(a):
    f={'vview_f':vsip_vcloneview_f,
       'vview_d':vsip_vcloneview_d,
       'cvview_f':vsip_cvcloneview_f,
       'cvview_d':vsip_cvcloneview_d,
       'cmview_d':vsip_cmcloneview_d,
       'cmview_f':vsip_cmcloneview_f,
       'mview_bl':vsip_mcloneview_bl,
       'mview_d':vsip_mcloneview_d,
       'mview_f':vsip_mcloneview_f,
       'mview_i':vsip_mcloneview_i,
       'mview_si':vsip_mcloneview_si,
       'mview_uc':vsip_mcloneview_uc,
       'vview_bl':vsip_vcloneview_bl,
       'vview_i':vsip_vcloneview_i,
       'vview_mi':vsip_vcloneview_mi,
       'vview_si':vsip_vcloneview_si,
       'vview_uc':vsip_vcloneview_uc,
       'vview_vi':vsip_vcloneview_vi}
    t=getType(a)
    if f.has_key(t[1]):
        return f[t[1]](a)
    else:
        print('Not a supported type for clone')
        return False
def realview(a):
    t=getType(a)
    f=f={'cmview_d': vsip_mrealview_d,
         'cmview_f': vsip_mrealview_f,
         'cvview_d': vsip_vrealview_d,
         'cvview_f': vsip_vrealview_f}
    if f.has_key(t[1]):
        return f[t[1]](a)
    else:
        print('Type ' +  t[1] + ' not a valid type for real view')
        return False
def imagview(a):
    t=getType(a)
    f = {'cmview_d': vsip_mimagview_d,
         'cmview_f': vsip_mimagview_f,
         'cvview_d': vsip_vimagview_d,
         'cvview_f': vsip_vimagview_f}
    if f.has_key(t[1]):
        return f[t[1]](a)
    else:
        print('Not a valid type for imag view')
        return False
def diagview(a,i):
    t=getType(a)
    f = {'mview_i': vsip_mdiagview_i,
         'mview_si': vsip_mdiagview_si,
         'mview_uc': vsip_mdiagview_uc,
         'cmview_d': vsip_cmdiagview_d,
         'cmview_f': vsip_cmdiagview_f,
         'mview_d': vsip_mdiagview_d,
         'mview_bl': vsip_mdiagview_bl,
         'mview_f': vsip_mdiagview_f}
    if f.has_key(t[1]):
        return f[t[1]](a,i)
    else:
        print('Not a valid type for diagonal view')
        return False
def rowview(A,i):
    f={'mview_i': vsip_mrowview_i,
       'mview_si': vsip_mrowview_si,
       'mview_uc': vsip_mrowview_uc,
       'cmview_d': vsip_cmrowview_d,
       'cmview_f': vsip_cmrowview_f,
       'mview_d': vsip_mrowview_d,
       'mview_f': vsip_mrowview_f,
       'mview_bl': vsip_mrowview_bl}
    t=getType(A)[1]
    if f.has_key(t):
        return f[t](A,i)
    else:
        print('Type ' + t + ' not supported by rowview')
        return False
def colview(A,i):
    f={'mview_i': vsip_mcolview_i,
       'mview_si': vsip_mcolview_si,
       'mview_uc': vsip_mcolview_uc,
       'cmview_d': vsip_cmcolview_d,
       'cmview_f': vsip_cmcolview_f,
       'mview_d': vsip_mcolview_d,
       'mview_f': vsip_mcolview_f,
       'mview_bl': vsip_mcolview_bl}
    t=getType(A)[1]
    if f.has_key(t):
        return f[t](A,i)
    else:
        print('Type ' + t + ' not supported by rowview')
        return False
def subview(v,i):
    """ 
        Usage
            a = subview(A,i)
        where
            a is a new vsip view created by subview.  The new view a is on the same
              block as A.
           i is a tuple corresponding to the index of the starting point in A and
           length of the corresponding dimensions.
        See VSIPL document for additional information.
        Ex: for a vector A of length 10 with elements from 0 to 9 then
            a=subview(A,(3,2))
        returns a vector of length 2 with elements 2,3
        Ex: for a matrix A of size 10,10 with elements 0 to 9 in each row
            a=subview(A,3,3,2,3)
        returns a matrix of size 2,3 with elements 2,3 in each row
    """
    f={'vview_vi':'vsip_vsubview_vi(v, i[0], i[1])',
       'vview_mi':'vsip_vsubview_mi(v, i[0], i[1])',
       'vview_bl':'vsip_vsubview_bl(v, i[0], i[1])',
       'vview_d':'vsip_vsubview_d(v, i[0], i[1])',
       'vview_f':'vsip_vsubview_f(v, i[0], i[1])',
       'vview_i':'vsip_vsubview_i(v, i[0], i[1])',
       'vview_si':'vsip_vsubview_si(v, i[0], i[1])',
       'vview_uc':'vsip_vsubview_uc(v, i[0], i[1])',
       'cvview_d':'vsip_cvsubview_d(v, i[0], i[1])',
       'cvview_f':'vsip_cvsubview_f(v, i[0], i[1])',
       'mview_d':'vsip_msubview_d(v, i[0], i[1], i[2], i[3])',
       'mview_f':'vsip_msubview_f(v, i[0], i[1], i[2], i[3])',
       'cmview_d':'vsip_cmsubview_d(v, i[0], i[1], i[2], i[3])',
       'cmview_f':'vsip_cmsubview_f(v, i[0], i[1], i[2], i[3])',
       'mview_bl':'vsip_msubview_bl(v, i[0], i[1], i[2], i[3])',
       'mview_i':'vsip_msubview_i(v, i[0], i[1], i[2], i[3])',
       'mview_si':'vsip_msubview_si(v, i[0], i[1], i[2], i[3])',
       'mview_uc':'vsip_msubview_uc(v, i[0], i[1], i[2], i[3])'}
    t=getType(v)[1]
    if f.has_key(t):
        return eval(f[t])
    else:
        print('Type ' + t + ' not defined for subview')
        return False
def transview(A):
    """
       Note this function creates a transpose view that should
       be destroyed when it is no longer needed
    """
    f={'mview_bl': vsip_mtransview_bl,
       'mview_i': vsip_mtransview_i,
       'mview_si': vsip_mtransview_si,
       'mview_uc': vsip_mtransview_uc,
       'cmview_d': vsip_cmtransview_d,
       'cmview_f': vsip_cmtransview_f,
       'mview_d': vsip_mtransview_d,
       'mview_f': vsip_mtransview_f}
    t=getType(A)[1]
    if f.has_key(t):
        return f[t](A)
    else:
        print('Type <:' + t + ':> not supported by transview')
        return False
def get(a,i):
    """
       get(aView,aIndex) will return a value from a vsip view. Argument aIndex
       corresponds to a tuple, a single integer, or a vsip_scalar_mi. The argument 
       must make sense for the input view. 
    """
    f={'cvview_dscalar':'vsip_cvget_d(a,i)',
       'cvview_fscalar':'vsip_cvget_f(a,i)',
       'vview_dscalar':'vsip_vget_d(a,i)',
       'vview_fscalar':'vsip_vget_f(a,i)',
       'vview_iscalar':'vsip_vget_i(a,i)',
       'vview_viscalar':'vsip_vget_vi(a,i)',
       'vview_siscalar':'vsip_vget_si(a,i)',
       'vview_ucscalar':'vsip_vget_uc(a,i)',
       'vview_blscalar':'vsip_vget_bl(a,i)',
       'vview_miscalar':'vsip_vget_mi(a,i)',
       'cmview_dtuple':'vsip_cmget_d(a,i[0],i[1])',
       'cmview_ftuple':'vsip_cmget_f(a,i[0],i[1])',
       'mview_dtuple':'vsip_mget_d(a,i[0],i[1])',
       'mview_ftuple':'vsip_mget_f(a,i[0],i[1])',
       'mview_ituple':'vsip_mget_i(a,i[0],i[1])',
       'mview_situple':'vsip_mget_si(a,i[0],i[1])',
       'mview_ucstuple':'vsip_mget_uc(a,i[0],i[1])',
       'mview_blstuple':'vsip_mget_bl(a,i[0],i[1])',
       'cmview_dscalar_mi':'vsip_cmget_d(a,i.r,i.c)',
       'cmview_fscalar_mi':'vsip_cmget_f(a,i.r,i.c)',
       'mview_dscalar_mi':'vsip_mget_d(a,i.r,i.c)',
       'mview_fscalar_mi':'vsip_mget_f(a,i.r,i.c)',
       'mview_iscalar_mi':'vsip_mget_i(a,i.r,i.c)',
       'mview_siscalar_mi':'vsip_mget_si(a,i.r,i.c)',
       'mview_ucscalar_mi':'vsip_mget_uc(a,i.r,i.c)',
       'mview_blscalar_mi':'vsip_mget_bl(a,i.r,i.c)'}
    t=str()
    if getType(a)[0]:
        t=getType(a)[1]
    if type(i) == tuple:
        t += 'tuple'
    elif getType(i)[0]:
        t += getType(i)[1]
    if f.has_key(t):
        return eval(f[t])
    else:
        print('Not a supported type')
        return False
def put(a,i,scl):
    """
       put(aView,aIndex,aScalar) will put aScalar in aView at position aIndex.
       Argument aIndex corresponds to a tuple or a single integer, or a vsip_scalar_mi. 
       aIndex must make sense for the input view. 
    """
    f={'cvview_dscalar':'vsip_cvput_d(a,i,x)',
       'cvview_fscalar':'vsip_cvput_f(a,i,x)',
       'vview_dscalar':'vsip_vput_d(a,i,x)',
       'vview_fscalar':'vsip_vput_f(a,i,x)',
       'vview_iscalar':'vsip_vput_i(a,i,x)',
       'vview_viscalar':'vsip_vput_vi(a,i,x)',
       'vview_siscalar':'vsip_vput_si(a,i,x)',
       'vview_ucscalar':'vsip_vput_uc(a,i,x)',
       'vview_blscalar':'vsip_vput_bl(a,i,x)',
       'vview_miscalar':'vsip_vput_mi(a,i,x)',
       'cmview_dtuple':'vsip_cmput_d(a,i[0],i[1],x)',
       'cmview_ftuple':'vsip_cmput_f(a,i[0],i[1],x)',
       'mview_dtuple':'vsip_mput_d(a,i[0],i[1],x)',
       'mview_ftuple':'vsip_mput_f(a,i[0],i[1],x)',
       'mview_ituple':'vsip_mput_i(a,i[0],i[1],x)',
       'mview_situple':'vsip_mput_si(a,i[0],i[1],x)',
       'mview_ucstuple':'vsip_mput_uc(a,i[0],i[1],x)',
       'mview_blstuple':'vsip_mput_bl(a,i[0],i[1],x)',
       'cmview_dscalar_mi':'vsip_cmput_d(a,i.r,i.c,x)',
       'cmview_fscalar_mi':'vsip_cmput_f(a,i.r,i.c,x)',
       'mview_dscalar_mi':'vsip_mput_d(a,i.r,i.c,x)',
       'mview_fscalar_mi':'vsip_mput_f(a,i.r,i.c,x)',
       'mview_iscalar_mi':'vsip_mput_i(a,i.r,i.c,x)',
       'mview_siscalar_mi':'vsip_mput_si(a,i.r,i.c,x)',
       'mview_ucscalar_mi':'vsip_mput_uc(a,i.r,i.c,x)',
       'mview_blscalar_mi':'vsip_mput_bl(a,i.r,i.c,x)'}
    t=str()
    x=scl
    if getType(a)[0]:
        t=getType(a)[1]
    if t == 'cmview_f' or t=='cvview_f':
        if getType(scl)[1] == 'scalar':
            x=vsip_cmplx_f(scl,0)
        elif getType(scl)[1] == 'cscalar_f':
            x=vsip_cmplx_f(scl.r,scl.i)
        elif type(scl) == complex:
            x=vsip_cmplx_f(scl.real,scl.imag)
    if t == 'cmview_d' or t == 'cvview_d':
        if getType(scl)[1] == 'scalar':
            x=vsip_cmplx_d(scl,0)
        elif getType(scl)[1] == 'cscalar_d':
            x=vsip_cmplx_d(scl.r,scl.i)
        elif type(scl) == complex:
            x=vsip_cmplx_d(scl.real,scl.imag)
    if type(i) == tuple:
        t += 'tuple'
    elif getType(i)[0]:
        t += getType(i)[1]
    if f.has_key(t):
        eval(f[t])
    else:
        print(t + 'Not a supported type')

# Block and View Destroy functions
def viewDestroy(a):
    t=getType(a)
    f = {'mview_bl':vsip_mdestroy_bl,
         'vview_bl':vsip_vdestroy_bl,
         'tview_d':vsip_tdestroy_d,
         'mview_d':vsip_mdestroy_d,
         'vview_d':vsip_vdestroy_d,
         'tview_f':vsip_tdestroy_f,
         'mview_f':vsip_mdestroy_f,
         'vview_f':vsip_vdestroy_f,
         'tview_i':vsip_tdestroy_i,
         'mview_i':vsip_mdestroy_i,
         'vview_i':vsip_vdestroy_i,
         'vview_mi':vsip_vdestroy_mi,
         'tview_si':vsip_tdestroy_si,
         'mview_si':vsip_mdestroy_si,
         'vview_si':vsip_vdestroy_si,
         'tview_uc':vsip_tdestroy_uc,
         'mview_uc':vsip_mdestroy_uc,
         'vview_uc':vsip_vdestroy_uc,
         'vview_vi':vsip_vdestroy_vi,
         'ctview_d':vsip_ctdestroy_d,
         'cmview_d':vsip_cmdestroy_d,
         'cvview_d':vsip_cvdestroy_d,
         'ctview_f':vsip_ctdestroy_f,
         'cmview_f':vsip_cmdestroy_f,
         'cvview_f':vsip_cvdestroy_f}
    if t[0] and f.has_key(t[1]):
        b = f[t[1]](a)
        return b
    else:
        return False
def blockDestroy(a):
    t=getType(a)
    f={  'block_bl':vsip_blockdestroy_bl,
         'block_d':vsip_blockdestroy_d,
         'block_f':vsip_blockdestroy_f,
         'block_i':vsip_blockdestroy_i,
         'block_mi':vsip_blockdestroy_mi,
         'block_si':vsip_blockdestroy_si,
         'block_uc':vsip_blockdestroy_uc,
         'block_vi':vsip_blockdestroy_vi,
         'cblock_d':vsip_cblockdestroy_d,
         'cblock_f':vsip_cblockdestroy_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a)
    else:
        print('blockDestroy Fail')
def allDestroy(a):
    t=getType(a)
    f={ 'cmview_d':vsip_cmalldestroy_d,
        'cmview_f':vsip_cmalldestroy_f,
        'ctview_d':vsip_ctalldestroy_d,
        'ctview_f':vsip_ctalldestroy_f,
        'cvview_d':vsip_cvalldestroy_d,
        'cvview_f':vsip_cvalldestroy_f,
        'mview_bl':vsip_malldestroy_bl,
        'mview_d':vsip_malldestroy_d,
        'mview_f':vsip_malldestroy_f,
        'mview_i':vsip_malldestroy_i,
        'mview_si':vsip_malldestroy_si,
        'mview_uc':vsip_malldestroy_uc,
        'tview_d':vsip_talldestroy_d,
        'tview_f':vsip_talldestroy_f,
        'tview_i':vsip_talldestroy_i,
        'tview_si':vsip_talldestroy_si,
        'tview_uc':vsip_talldestroy_uc,
        'vview_bl':vsip_valldestroy_bl,
        'vview_d':vsip_valldestroy_d,
        'vview_f':vsip_valldestroy_f,
        'vview_i':vsip_valldestroy_i,
        'vview_mi':vsip_valldestroy_mi,
        'vview_si':vsip_valldestroy_si,
        'vview_uc':vsip_valldestroy_uc,
        'vview_vi':vsip_valldestroy_vi}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a)
    else:
        print('allDestroy Fail')

# Random Number Generation
class randcreate(object):
    """
       randcreate defaults to 
           vsip_randcreate(s, 1,1,VSIP_PRNG)
       if an integer is passed in as the argument.
       If the argument type is 'randstate' then this
       object is used to initialize the randcreate object. 
       """
    def __init__(self,s):
        t = getType(s)
        if isinstance(s,int):
            self.rand= vsip_randcreate(s,1,1,VSIP_PRNG)
        elif t[0] and t[1]=='randstate':
            self.rand = s;
        else:
            print('argument must be an integer or a randstate object')

    def get(self):
        return self.rand

    def randu(self,a):
        t=getType(a)
        f = {'cvview_d':vsip_cvrandu_d,
             'cvview_f':vsip_cvrandu_f,
             'vview_d':vsip_vrandu_d,
             'vview_f':vsip_vrandu_f}
        if t[0] and f.has_key(t[1]):
            f[t[1]](self.rand,a)
            return a
        else:
            print('Not a supported type')

    def randn(self,a):
        t=getType(a)
        f = {'cvview_d':vsip_cvrandn_d,
             'cvview_f':vsip_cvrandn_f,
             'vview_d':vsip_vrandn_d,
             'vview_f':vsip_vrandn_f}
        if t[0] and f.has_key(t[1]):
            f[t[1]](self.rand,a)
            return a
        else:
            print('Not a supported type')

    def __del__(self):
        t=getType(self.rand)
        if t[0]:
            vsip_randdestroy(self.rand)
def rand(seed,numprocs,id,rng):
    return vsip_randcreate(seed,numprocs,id,rng)
def randn(state, a):
    f={'cvview_d':vsip_cvrandn_d,
       'cvview_f':vsip_cvrandn_f,
       'vview_d':vsip_vrandn_d,
       'vview_f':vsip_vrandn_f}
    t=getType(a)[1]
    if f.has_key(t):
        f[t](state,a)
        return a
    else:
        print(t + 'not a supported type for randn')
        return False
def randu(state, a):
    f={'cvview_d':vsip_cvrandu_d,
       'cvview_f':vsip_cvrandu_f,
       'vview_d':vsip_vrandu_d,
       'vview_f':vsip_vrandu_f}
    t=getType(a)[1]
    if f.has_key(t):
        f[t](state,a)
        return a
    else:
        print('Type ' + t + ' not a supported type for randu')
        return False
def randDestroy(state):
    return vsip_randdestroy(state)

# Elementary math functions
def acos(a,b):
    t=getType(a)
    f={  'mview_d':vsip_macos_d,
         'mview_f':vsip_macos_f,
         'vview_d':vsip_vacos_d,
         'vview_f':vsip_vacos_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported type for acos')
def asin(a,b):
    t=getType(a)
    f={  'mview_d':vsip_masin_d,
         'mview_f':vsip_masin_f,
         'vview_d':vsip_vasin_d,
         'vview_f':vsip_vasin_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported type for asin')
        return False
def cos(a,b):
    t=getType(a)
    f={  'mview_d':vsip_mcos_d,
         'mview_f':vsip_mcos_f,
         'vview_d':vsip_vcos_d,
         'vview_f':vsip_vcos_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported type for cos')
def cosh(a,b):
    t=getType(a)
    f={  'mview_d':vsip_mcosh_d,
         'mview_f':vsip_mcosh_f,
         'vview_d':vsip_vcosh_d,
         'vview_f':vsip_vcosh_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported type for cosh')
def exp(a,b):
    """"
        Supported for matrix and vector floats of type real and complex
        """
    t=getType(a)
    f={ 'cmview_d':vsip_cmexp_d,
        'cmview_f':vsip_cmexp_f,
        'cvview_d':vsip_cvexp_d,
        'cvview_f':vsip_cvexp_f,
        'mview_d':vsip_mexp_d,
        'mview_f':vsip_mexp_f,
        'vview_d':vsip_vexp_d,
        'vview_f':vsip_vexp_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported type for exp')
        return False
def exp10(a,b):
    t=getType(a)
    f={  'mview_d':vsip_mexp10_d,
         'mview_f':vsip_mexp10_f,
         'vview_d':vsip_vexp10_d,
         'vview_f':vsip_vexp10_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported type for exp10')
def log(a,b):
    """"
        Supported for matrix and vector floats of type real and complex
        """
    t=getType(a)
    f={ 'cmview_d':vsip_cmlog_d,
        'cmview_f':vsip_cmlog_f,
        'cvview_d':vsip_cvlog_d,
        'cvview_f':vsip_cvlog_f,
        'mview_d':vsip_mlog_d,
        'mview_f':vsip_mlog_f,
        'vview_d':vsip_vlog_d,
        'vview_f':vsip_vlog_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported type for log')
        return False
def log10(a,b):
    t=getType(a)
    f={  'mview_d':vsip_mlog10_d,
         'mview_f':vsip_mlog10_f,
         'vview_d':vsip_vlog10_d,
         'vview_f':vsip_vlog10_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported type for log10')
        return False
def sin(a,b):
    t=getType(a)
    f={  'mview_d':vsip_msin_d,
         'mview_f':vsip_msin_f,
         'vview_d':vsip_vsin_d,
         'vview_f':vsip_vsin_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported type for sin')
        return False
def sinh(a,b):
    t=getType(a)
    f={  'mview_d':vsip_msinh_d,
         'mview_f':vsip_msinh_f,
         'vview_d':vsip_vsinh_d,
         'vview_f':vsip_vsinh_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported type for sinh')
        return False
def sqrt(a,b):
    """"
        Supported for matrix and vector floats of type real and complex
        """
    t=getType(a)
    f={ 'cmview_d':vsip_cmsqrt_d,
        'cmview_f':vsip_cmsqrt_f,
        'cvview_d':vsip_cvsqrt_d,
        'cvview_f':vsip_cvsqrt_f,
        'mview_d':vsip_msqrt_d,
        'mview_f':vsip_msqrt_f,
        'vview_d':vsip_vsqrt_d,
        'vview_f':vsip_vsqrt_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported type for sqrt')
        return False
def tan(a,b):
    t=getType(a)
    f={  'mview_d':vsip_mtan_d,
         'mview_f':vsip_mtan_f,
         'vview_d':vsip_vtan_d,
         'vview_f':vsip_vtan_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported type for tan')
        return False
def tanh(a,b):
    t=getType(a)
    f={  'mview_d':vsip_mtanh_d,
         'mview_f':vsip_mtanh_f,
         'vview_d':vsip_vtanh_d,
         'vview_f':vsip_vtanh_f}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported type for tanh')
        return False

#Unary Operations
def arg(input,output):
    f={'cmview_dmview_d':vsip_marg_d,
       'cmview_fmview_d':vsip_marg_f,
       'cvview_dvview_d':vsip_varg_d,
       'cvview_fvview_f':vsip_varg_f}
    t=getType(input)[1]+getType(output)[1]
    if f.has_key(t):
        f[t](input,output)
        return output
    else:
        print('Not a supported type')
        return False
def conj(input,output):
    f={'cmview_d':vsip_cmconj_d,
       'cmview_f':vsip_cmconj_f,
       'cvview_d':vsip_cvconj_d,
       'cvview_f':vsip_cvconj_f}
    fr=['vview_d','vview_f','mview_d','mview_f']
    t=getType(input)[1]
    if t != getType(output)[1]:
        print('Type of input and output must be the same')
        return False
    if f.has_key(t):
        f[t](input,output)
        return output
    elif t in fr:
        return copy(input,output)
    else:
        print('Type' + t + 'Not a supported type for copy')
        return False
def cumsum(input,output):
    """
        cumsum(input,output)
        input is a vector or matrix.
        output is either a vector for vector inpute 
        or output is a tuple consiting of a vsip_major flag plus a corresponding  matrix;
        For instance
        cumsum(vector_input, vector_output)
        or
        cumsum(matrix_input, (VSIP_ROW, matrix_output))
    """
    f={'mview_dtuple':'vsip_mcumsum_d(input,output[0],output[1])',
       'mview_ftuple':'vsip_mcumsum_f(input,output[0],output[1])',
       'mview_ituple':'vsip_mcumsum_i(input,output[0],output[1])',
       'mview_situple':'vsip_mcumsum_si(input,output[0],output[1])',
       'vview_dvview_d':'vsip_vcumsum_d(input,output)',
       'vview_fvview_f':'vsip_vcumsum_f(input,output)',
       'vview_ivview_i':'vsip_vcumsum_i(input,output)',
       'vview_sivview_si':'vsip_vcumsum_si}(input,output)'}
    t=str()
    if getType(output)[0]:
       if type(output)==tuple :
            t=getType(input)[1]+'tuple'
       else:
            t=getType(input)[1]+getType(output)[1]
    if f.has_key(t):
        eval(f[t])
    else:
        print('Not a supported type')        
def euler(input,output):
    f={'mview_dcmview_d':vsip_meuler_d,
       'mview_fcmview_f':vsip_meuler_f,
       'vview_dcvview_d':vsip_veuler_d,
       'vview_fcvview_f':vsip_veuler_f}
    t=getType(input)[1]+getType(output)[1]
    if f.has_key(t):
        f[t](input,output)
        return output
    else:
        print('Type <:' + t + ':> a supported type')
        return False
def mag(input,output):
    f={'cmview_d':vsip_cmmag_d,
       'cmview_f':vsip_cmmag_f,
       'cvview_d':vsip_cvmag_d,
       'cvview_f':vsip_cvmag_f,
       'mview_d':vsip_mmag_d,
       'mview_f':vsip_mmag_f,
       'vview_d':vsip_vmag_d,
       'vview_f':vsip_vmag_f,
       'vview_i':vsip_vmag_i,
       'vview_si':vsip_vmag_si} 
    t = getType(input)[1]
    if f.has_key(t):
        f[t](input,output)
        return output;
    else:
        print(t + ' Is not a supported type for mag')
        return False
def magsq(input,output):
    f={'cmview_d':vsip_mcmagsq_d,
       'cmview_f':vsip_mcmagsq_f,
       'cvview_d':vsip_vcmagsq_d,
       'cvview_f':vsip_vcmagsq_f}
    t = getType(input)[1]
    if f.has_key(t):
        f[t](input,output)
        return output;
    else:
        print(t + ' Is not a supported type for magsq')
        return False
def meanval(input):
    f={'cmview_d':vsip_cmmeanval_d,
       'cvview_d':vsip_cvmeanval_d,
       'cmview_f':vsip_cmmeanval_f,
       'cvview_f':vsip_cvmeanval_f,
       'mview_d':vsip_mmeanval_d,
       'vview_d':vsip_vmeanval_d,
       'mview_f':vsip_mmeanval_f,
       'vview_f':vsip_vmeanval_f}
    t=getType(input)[1]
    if f.has_key(t):
        return f[t](input)
    else:
        print(t + ' Is not a supported type for meanval')
        return False
def meansqval(input):
    f={'cmview_d':vsip_cmmeansqval_d,
       'cvview_d':vsip_cvmeansqval_d,
       'cmview_f':vsip_cmmeansqval_f,
       'cvview_f':vsip_cvmeansqval_f,
       'mview_d':vsip_mmeansqval_d,
       'vview_d':vsip_vmeansqval_d,
       'mview_f':vsip_mmeansqval_f,
       'vview_f':vsip_vmeansqval_f}
    t=getType(input)[1]
    if f.has_key(t):
        return f[t](input)
    else:
        print(t + ' Is not a supported type for meanval')
        return False
def modulate(input,nu,phi,output):
    f={'cvview_d':vsip_cvmodulate_d,
       'vview_d':vsip_vmodulate_d,
       'cvview_f':vsip_cvmodulate_f,
       'vview_f':vsip_vmodulate_f}
    t=getType(input)[1]
    if f.has_key(t):
        return f[t](input,nu,phi,output)
    else:
        print(t + 'Not a supported type for modulate')
        return False
def neg(a,b):
    """
        Elementwise place the negative values of a in b. May be done in place using neg(a,a)
        Returns the result as a convinience.
        """
    t=getType(a)
    f= {'cmview_f':vsip_cmneg_d,
        'cmview_f':vsip_cmneg_f,
        'cvview_d':vsip_cvneg_d,
        'cvview_f':vsip_cvneg_f,
        'mview_d':vsip_mneg_d,
        'mview_f':vsip_mneg_f,
        'vview_d':vsip_vneg_d,
        'vview_f':vsip_vneg_f,
        'vview_i':vsip_vneg_i,
        'vview_si':vsip_vneg_si}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        return False
def recip(a,b):
    f={'cmview_d':vsip_cmrecip_d,
       'cmview_f':vsip_cmrecip_f,
       'cvview_d':vsip_cvrecip_d,
       'cvview_f':vsip_cvrecip_f,
       'mview_d':vsip_mrecip_d,
       'mview_f':vsip_mrecip_f,
       'vview_d':vsip_vrecip_d,
       'vview_f':vsip_vrecip_f}
    t = getType(input)[1]
    if f.has_key(t):
        f[t](input,output)
        return output;
    else:
        print(t + ' Is not a supported type for mag')
        return False
def rsqrt(a,b):
    f={'mview_d':vsip_mrsqrt_d,
       'mview_f':vsip_mrsqrt_f,
       'vview_d':vsip_vrsqrt_d,
       'vview_f':vsip_vrsqrt_f} 
    t = getType(input)[1]
    if f.has_key(t):
        f[t](input,output)
        return output;
    else:
        print(t + ' Is not a supported type for rsqrt')
        return False
def sq(a,b):
    f={'mview_d':vsip_msq_d,
       'mview_f':vsip_msq_f,
       'vview_d':vsip_vsq_d,
       'vview_f':vsip_vsq_f}
    t = getType(input)[1]
    if f.has_key(t):
        f[t](input,output)
        return output;
    else:
        print(t + ' Is not a supported type for rsqrt')
        return False
def sumval(input):
    f={'cmview_d':'cscalarToComplex(vsip_cmsumval_d ( input ))',
       'cvview_d':'cscalarToComplex(vsip_cvsumval_d ( input ))',
       'cmview_f':'cscalarToComplex(vsip_cmsumval_f ( input ))',
       'cvview_f':'cscalarToComplex(vsip_cvsumval_f ( input ))',
       'mview_d':'vsip_msumval_d ( input )',
       'vview_d':'vsip_vsumval_d ( input )',
       'mview_f':'vsip_msumval_f ( input )',
       'vview_f':'vsip_vsumval_f ( input )',
       'vview_i':'vsip_vsumval_i ( input )',
       'vview_si':'vsip_vsumval_si ( input )',
       'vview_uc':'vsip_vsumval_uc ( input )',
       'mview_bl':'vsip_msumval_bl ( input )',
       'vview_bl':'vsip_vsumval_bl ( input )'}
    t=getType(input)[1]
    if f.has_key(t):
        return eval(f[t])
    else:
        print(t + ' Is not a supported type for sumval')
        return False
def sumsqval(input):
    f={'mview_d':vsip_msumsqval_d,
       'mview_f':vsip_msumsqval_f,
       'vview_d':vsip_vsumsqval_d,
       'vview_f':vsip_vsumsqval_f}
    t=getType(input)[1]
    if f.has_key(t):
        return f[t](input)
    else:
        print(t + ' Is not a supported type for sumsqval')
        return False

#Binary Operations
def add(a,b,c):
    """
        Through introspection add two vsipl objects.
        add(a,b,c) adds a to b elementwise returning the answer in c.
        Unlike VSIPL this add will return c as a convenience.
        note not every combination is supported. Currently supported are
        vsip_vadd_f, vsip_vadd_d, vsip_madd_f, vsip_madd_d, vsip_cvadd_f, 
        vsip_cvadd_d, vsip_cmadd_f, vsip_cmadd_d, vsip_vadd_i, vsip_madd_i,
        vsip_vadd_si, vsip_madd_si, vsip_vadd_vi, vsip_vadd_uc, vsip_rcvadd_f,
        vsip_rcvadd_d, vsip_rcmadd_f, vsip_rcmadd_d, vsip_csmadd_d, vsip_csmadd_f,
        vsip_csvadd_d, vsip_csvadd_f, vsip_rscmadd_d, vsip_rscmadd_f, vsip_rscvadd_d,
        vsip_rscvadd_f, vsip_smadd_d, vsip_smadd_f, vsip_svadd_d, vsip_svadd_f,
        vsip_svadd_i, vsip_svadd_si, vsip_svadd_uc, vsip_svadd_vi
        to decode read about vsipl naming conventions in VSIPL specification.
        """
    t0=getType(a)
    t1=getType(b)
    t = str()
    if t0[0] and t1[0]:
       t= t0[1] + t1[1]
    f={ 'vview_fvview_f': vsip_vadd_f,
          'vview_dvview_d': vsip_vadd_d,
          'mview_fmview_f': vsip_madd_f,
          'mview_dmview_d': vsip_madd_d,
          'cvview_fcvview_f': vsip_cvadd_f,
          'cvview_dcvview_d': vsip_cvadd_d,
          'cmview_fcmview_f': vsip_cmadd_f,
          'cmview_dcmview_d': vsip_cmadd_d,
          'vview_ivview_i': vsip_vadd_i,
          'mview_imview_i': vsip_madd_i,
          'vview_sivview_si': vsip_vadd_si,
          'mview_simview_si': vsip_madd_si,
          'vview_vivview_vi': vsip_vadd_vi,
          'vview_ucvview_uc': vsip_vadd_uc,
          'vview_fcvview_f': vsip_rcvadd_f,
          'vview_dcvview_d':vsip_rcvadd_d,
          'mview_fcmview_f': vsip_rcmadd_f,
          'vview_dcvview_d':vsip_rcmadd_d,
          'cscalar_dcmview_d':vsip_csmadd_d,
          'cscalar_fcmview_f':vsip_csmadd_f,
          'cscalar_dcvview_d':vsip_csvadd_d,
          'cscalar_fcvview_f':vsip_csvadd_f,
          'scalarcmview_d':vsip_rscmadd_d,
          'scalarcmview_f':vsip_rscmadd_f,
          'scalarcvview_d':vsip_rscvadd_d,
          'scalarcvview_f':vsip_rscvadd_f,
          'scalarmview_d':vsip_smadd_d,
          'scalarmview_f':vsip_smadd_f,
          'scalarvview_d':vsip_svadd_d,
          'scalarvview_f':vsip_svadd_f,
          'scalarvview_i':vsip_svadd_i,
          'scalarvview_si':vsip_svadd_si,
          'scalarvview_uc':vsip_svadd_uc,
          'scalarvview_vi':vsip_svadd_vi}
    if f.has_key(t):
       f[t](a,b,c)
       return c
    else:
       return False
def expoavg(alpha,b,c):
    f={'cmview_d':vsip_cmexpoavg_d,
       'cmview_f':vsip_cmexpoavg_f,
       'cvview_d':vsip_cvexpoavg_d,
       'cvview_f':vsip_cvexpoavg_f,
       'mview_d':vsip_mexpoavg_d,
       'mview_f':vsip_mexpoavg_f,
       'vview_d':vsip_vexpoavg_d,
       'vview_f':vsip_vexpoavg_f}
    t=getType(b)[1]
    if f.has_key(t):
        f[t](alpha,b,c)
        return c
    else:
        print('Type ' + t + ' not supported for expoavg')
        return False
def hypot(a,b,c):
    f={'mview_d':vsip_mhypot_d,
       'mview_f':vsip_mhypot_f,
       'vview_d':vsip_vhypot_d,
       'vview_f':vsip_vhypot_f}
    t=getType(a)[1]
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t + ' not supported for hypot')
        return False
def sub(a,b,c):
    """
        sub(a,b,c) does a-b returning the result in c. View c is returned as a convenience.
        The first argument, a may be a scalar, Otherwise a and b must be of the same size.
        VSIPL functions supported are
        vsip_cmsub_d, vsip_cmsub_f, vsip_crmsub_d, vsip_crmsub_f, vsip_crvsub_d, vsip_crvsub_f, 
        vsip_csmsub_d, vsip_csmsub_f, vsip_csvsub_d, vsip_csvsub_f, vsip_cvsub_d, vsip_cvsub_f, 
        vsip_msub_d, vsip_msub_f, vsip_msub_i, vsip_msub_si, vsip_rcmsub_d, vsip_rcmsub_f, 
        vsip_rcvsub_d, vsip_rcvsub_f,vsip_rscmsub_d, vsip_rscmsub_f, vsip_rscvsub_d, vsip_rscvsub_f,
        vsip_smsub_d, vsip_smsub_f, vsip_smsub_i, vsip_smsub_si, vsip_svsub_d, vsip_svsub_f, 
        vsip_svsub_i, vsip_svsub_si, vsip_svsub_uc, vsip_svsub_vi, vsip_vsub_d, vsip_vsub_f, 
        vsip_vsub_i, vsip_vsub_si, vsip_vsub_uc
        """
    t0=getType(a)
    t1=getType(b)
    t = str()
    if t0[0] and t1[0]:
        t= t0[1] + t1[1]
    f={'cmview_dcmview_d':vsip_cmsub_d,
       'cmview_fcmview_f':vsip_cmsub_f,
       'cmview_dmview_d':vsip_crmsub_d,
       'cmview_fmview_f':vsip_crmsub_f,
       'cvview_dvview_d':vsip_crvsub_d,
       'cvview_fvview_f':vsip_crvsub_f,
       'cscalar_dcmview_d':vsip_csmsub_d,
       'cscalar_fcmview_f':vsip_csmsub_f,
       'cscalar_fcvview_d':vsip_csvsub_d,
       'cscalar_fcvview_f':vsip_csvsub_f,
       'cvview_dcvview_d':vsip_cvsub_d,
       'cvview_fcvview_f':vsip_cvsub_f,
       'mview_dmview_d':vsip_msub_d,
       'mview_fmview_f':vsip_msub_f,
       'mview_imview_i':vsip_msub_i,
       'mview_simview_si':vsip_msub_si,
       'mview_dcmview_d':vsip_rcmsub_d,
       'mview_fcmview_f':vsip_rcmsub_f,
       'vview_dcvview_d':vsip_rcvsub_d,
       'vview_fcvview_f':vsip_rcvsub_f,
       'scalarcmview_d':vsip_rscmsub_d,
       'scalarcmview_f':vsip_rscmsub_f,
       'scalarcvview_d':vsip_rscvsub_d,
       'scalarcvview_f':vsip_rscvsub_f,
       'scalarmview_d':vsip_smsub_d,
       'scalarmview_f':vsip_smsub_f,
       'scalarmview_i':vsip_smsub_i,
       'scalarmview_si':vsip_smsub_si,
       'scalarvview_d':vsip_svsub_d,
       'scalarvview_f':vsip_svsub_f,
       'scalarvview_i':vsip_svsub_i,
       'scalarvview_si':vsip_svsub_si,
       'scalarvview_uc':vsip_svsub_uc,
       'scalarvview_vi':vsip_svsub_vi,
       'vview_dvview_d':vsip_vsub_d,
       'vview_fvview_f':vsip_vsub_f,
       'vview_ivview_i':vsip_vsub_i,
       'vview_sivview_si':vsip_vsub_si,
       'vview_ucvview_uc':vsip_vsub_uc}
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        return False
def mul(a,b,c):
    """
        Through introspection multiply elementwise two vsipl objects.
        mul(a,b,c) multiplies a times b elementwise returning the answer in c.
        Unlike VSIPL this mul returns the answer as a convenience. May be done
        in-place if a or b is the same type as c.
        VSIPL functions supported are
        vsip_vmul_d, vsip_vmul_f, vsip_vmul_i, vsip_vmul_si, vsip_vmul_uc, vsip_cmmul_d, 
        vsip_cmmul_f, vsip_cvmul_d, vsip_cvmul_f, vsip_mmul_d, vsip_mmul_f, vsip_rcmmul_d, 
        vsip_rcmmul_f, vsip_rcvmul_d, vsip_rcvmul_f, vsip_rscmmul_d, vsip_rscmmul_f, 
        vsip_rscvmul_d, vsip_rscvmul_f, vsip_smmul_d, vsip_smmul_f, vsip_svmul_d, vsip_svmul_f, 
        vsip_svmul_i, vsip_svmul_si, vsip_svmul_uc, vsip_csmmul_d, vsip_csmmul_f, vsip_csvmul_d, 
        vsip_csvmul_f
        To decode read about vsipl naming conventions in VSIPL specification.
        Note there are other muls which could not be included because the API was not the same,
        or conflicted. For instance vsip_cjmul_d has the same type inputs as vsip_cmul_d. 
        """
    t0=getType(a)
    t1=getType(b)
    t = str()
    if t0[0] and t1[0]:
      t= t0[1] + t1[1]
    f={ 'vview_dvview_d':vsip_vmul_d,
          'vview_fvview_f':vsip_vmul_f,
          'vview_ivview_i':vsip_vmul_i,
          'vview_sivview_si':vsip_vmul_si,
          'vview_ucvview_uc':vsip_vmul_uc,
          'cmview_dvview_d':vsip_cmmul_d,
          'cmview_fcmview_f':vsip_cmmul_f,
          'cvview_dcvview_d':vsip_cvmul_d,
          'cvview_fcvview_f':vsip_cvmul_f,
          'mview_dmview_d':vsip_mmul_d,
          'mview_fmview_f':vsip_mmul_f,
          'mview_dcmview_d':vsip_rcmmul_d,
          'mview_fcmview_f':vsip_rcmmul_f,
          'vview_dcvview_d':vsip_rcvmul_d,
          'vview_fcvview_f':vsip_rcvmul_f,
          'scalarcmview_d':vsip_rscmmul_d,
          'scalarcmview_f':vsip_rscmmul_f,
          'scalarcvview_d':vsip_rscvmul_d,
          'scalarcvview_f':vsip_rscvmul_f,
          'scalarmview_d':vsip_smmul_d,
          'scalarmview_f':vsip_smmul_f,
          'scalarvview_d':vsip_svmul_d,
          'scalarvview_f':vsip_svmul_f,
          'scalarvview_i':vsip_svmul_i,
          'scalarvview_si':vsip_svmul_si,
          'scalarvview_uc':vsip_svmul_uc,
          'cscalar_dcmview_d':vsip_csmmul_d,
          'cscalar_fcmview_f':vsip_csmmul_f,
          'cscalar_dcvview_d':vsip_csvmul_d,
          'cscalar_fcvview_f':vsip_csvmul_f}
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        return False
def vmmul(a,b,flg,c):
    """
       This function does vmmul, -cvmmul, and rvcmmul
    """
    f={'cvview_dcmview_d':vsip_cvmmul_d,
       'cvview_fcmview_f':vsip_cvmmul_f,
       'vview_dcmview_d':vsip_rvcmmul_d,
       'vview_fcmview_f':vsip_rvcmmul_f,
       'vview_dmview_d':vsip_vmmul_d,
       'vview_fmview_f':vsip_vmmul_f}
    t=getType(a)[1]+getType(b)[1]
    if f.has_key(t):
        f[t](a,b,flg,c)
        return c
    else:
        print('Type ' + t + ' not supported for vmmul')
        return False
def jmul(a,b,c):
    f={'cmview_d':vsip_cmjmul_d,
       'cmview_f':vsip_cmjmul_f,
       'cvview_d':vsip_cvjmul_d,
       'cvview_f':vsip_cvjmul_f}
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t +' Not a valid type for jmul')
        return False
def div(a,b,c):
    """
        Divide a by b puting result in c. Here c is returned as a convenience.
        Arguments a or b (not both) may be a scalar. Otherwise all arguments are the same size.
        VSIPL functions supported are
        vsip_cmdiv_d, vsip_cmdiv_f, vsip_cmrsdiv_d, vsip_cmrsdiv_f, vsip_crmdiv_d, vsip_crmdiv_f,
        vsip_crvdiv_d, vsip_crvdiv_f, vsip_csmdiv_d, vsip_csmdiv_f, vsip_csvdiv_d, vsip_csvdiv_f,
        vsip_cvdiv_d, vsip_cvdiv_f, vsip_cvrsdiv_d, vsip_cvrsdiv_f, vsip_mdiv_d, vsip_mdiv_f,
        vsip_msdiv_d, vsip_msdiv_f, vsip_rcmdiv_d, vsip_rcmdiv_f, vsip_rcvdiv_d, vsip_rcvdiv_f,
        vsip_rscmdiv_d, vsip_rscmdiv_f, vsip_rscvdiv_d, vsip_rscvdiv_f, vsip_smdiv_d, vsip_smdiv_f,
        vsip_svdiv_d, vsip_svdiv_f, vsip_vdiv_d, vsip_vdiv_f, vsip_vsdiv_d, vsip_vsdiv_f
       """
    t0=getType(a)
    t1=getType(b)
    t=str()
    if(t0[0]) and t1[0]:
        t=t0[1]+t1[1]
    f = {'cmview_dcmview_d':vsip_cmdiv_d,
         'cmview_fcmview_f':vsip_cmdiv_f,
         'cmview_dscalar':vsip_cmrsdiv_d,
         'cmview_fscalar':vsip_cmrsdiv_f,
         'cmview_dmview_d':vsip_crmdiv_d,
         'cmview_fmview_f':vsip_crmdiv_f,
         'cvview_dvview_d':vsip_crvdiv_d,
         'cvview_fvview_f':vsip_crvdiv_f,
         'cscalar_dcmview_d':vsip_csmdiv_d,
         'cscalar_fcmview_f':vsip_csmdiv_f,
         'cscalar_dcvview_d':vsip_csvdiv_d,
         'cscalar_fcvview_f':vsip_csvdiv_f,
         'cvview_dcvview_d':vsip_cvdiv_d,
         'cvview_fcvview_f':vsip_cvdiv_f,
         'cvview_dscalar_d':vsip_cvrsdiv_d,
         'cvview_fscalar_f':vsip_cvrsdiv_f,
         'mview_dmview_d':vsip_mdiv_d,
         'mview_fmview_d':vsip_mdiv_f,
         'mview_dscalar':vsip_msdiv_d,
         'mview_fscalar':vsip_msdiv_f,
         'mviwew_dcmview_d':vsip_rcmdiv_d,
         'mview_fcmview_f':vsip_rcmdiv_f,
         'vview_dcvview_d':vsip_rcvdiv_d,
         'vview_fcvview_f':vsip_rcvdiv_f,
         'scalarcmview_d':vsip_rscmdiv_d,
         'scalarcmview_f':vsip_rscmdiv_f,
         'scalarcvview_d':vsip_rscvdiv_d,
         'scalarcvview_f':vsip_rscvdiv_f,
         'scalarmview_d':vsip_smdiv_d,
         'scalarmview_f':vsip_smdiv_f,
         'scalarvview_d':vsip_svdiv_d,
         'scalarvview_f':vsip_svdiv_f,
         'vview_dvview_d':vsip_vdiv_d,
         'vview_fvview_f':vsip_vdiv_f,
         'vview_dscalar':vsip_vsdiv_d,
         'vview_fscalar':vsip_vsdiv_f}
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        return False

# Ternary Operations
# Logical Operations
# Selection Operations
# Bitwise and Boolean 
def am(a,b,c,d):
    """
       add and multiply
       (a+b) * c
       am(a,b,c,d) adds a to b and then multiplies c putting result in d
    """
    f={'cvview_dcvview_dcvview_d':vsip_cvam_d,
       'cvview_fcvview_fcvview_f':vsip_cvam_f,
       'cvview_dcscalar_dcvview_d':vsip_cvsam_d,
       'cvview_fcscalar_fcvview_f':vsip_cvsam_f,
       'vview_dvview_dvview_d':vsip_vam_d,
       'vview_fvview_fvview_f':vsip_vam_f,
       'vview_dscalarvview_d':vsip_vsam_d,
       'vview_fscalarvview_f':vsip_vsam_f}
    t=getType(a)[1]+getType(b)[1]+getType(c)[1]
    if f.has_key(t):
        f[t](a,b,c,d)
        return d
    else:
        print('Type ' + t + ' not supported by am')
        return False
def ma(a,b,c,d):
    """
        multiply add
        (a*b) + c
        ma(a,b,c,d) multiplies a * b and adds c
    """
    f={'cvview_dcscalar_dcscalar_d':vsip_cvsmsa_d,
       'cvview_fcscalar_fcscalar_f':vsip_cvsmsa_f,
       'vview_dscalarscalar':vsip_vsmsa_d,
       'vview_fscalar_fscalar_f':vsip_vsmsa_f,
       'cvview_dcscalar_dcvview_d':vsip_cvsma_d,
       'cvview_fcscalar_fcscalar_f':vsip_cvsma_f,
       'vview_dscalarvview_d':vsip_vsma_d,
       'vview_fscalar_fvview_f':vsip_vsma_f,
       'cvview_dcvview_dcvview_d':vsip_cvma_d,
       'cvview_fcvview_fcvview_f':vsip_cvma_f,
       'vview_dvview_dvview_d':vsip_vma_d,
       'vview_fvview_fvview_f':vsip_vma_f,
       'cvview_dcvview_dcscalar_d':vsip_cvmsa_d,
       'cvview_fcvview_fcscalar_f':vsip_cvmsa_f,
       'vview_dvview_dscalar':vsip_vmsa_d,
       'vview_fvview_fscalar':vsip_vmsa_f}
    t=getType(a)[1]+getType(b)[1]+getType(c)[1]
    if f.has_key(t):
        f[t](a,b,c,d)
        return d
    else:
        print('Type ' + t + ' not supported by ma')
        return False
def msb(a,b,c,d):
    """
       multiply subtract
       (a*b) -c
    """
    f={'cvview_dcvview_dcvview_d':vsip_cvmsb_d,
       'cvview_fcvview_fcvview_f':vsip_cvmsb_f,
       'vview_dvview_dvview_d':vsip_vmsb_d,
       'vview_fvview_fvview_f':vsip_vmsb_f}
    t=getType(a)[1]+getType(b)[1]+getType(c)[1]
    if f.has_key(t):
        f[t](a,b,c,d)
        return d
    else:
        print('Type ' + t + ' not supported by msb')
        return False
def sbm(a,b,c,d):
    """
       subtract multiply
       (a-b) * c
    """
    f={'cvview_dcvview_dcvview_d':vsip_cvsbm_d,
       'cvview_fcvview_fcvview_f':vsip_cvsbm_f,
       'vview_dvview_dvview_d':vsip_vsbm_d,
       'vview_fvview_fvview_f':vsip_vsbm_f}
    t=getType(a)[1]+getType(b)[1]+getType(c)[1]
    if f.has_key(t):
        f[t](a,b,c,d)
        return d
    else:
        print('Type ' + t + ' not supported by sbm')
        return False
# Logical Operations
def alltrue(a):
    f={'mview_bl':vsip_malltrue_bl,
       'vview_bl':vsip_valltrue_bl}
    t=getType(a)[1]
    if f.has_key(t):
        return 1 == f[1](a)
    else:
        print('Type ' + t + ' not a defined type for alltrue')
        return False
def anytrue(a):
    f={'mview_bl':vsip_manytrue_bl,
       'vview_bl':vsip_vanytrue_bl}
    t=getType(a)[1]
    if f.has_key(t):
        return 1 == f[1](a)
    else:
        print('Type ' + t + ' not a defined type for anytrue')
        return False
def leq(a,b,c):
    f={'mview_dmview_d':vsip_mleq_d,
       'mview_fmview_f':vsip_mleq_f,
       'vview_dvview_d':vsip_vleq_d,
       'vview_fvview_f':vsip_vleq_f,
       'vview_ivview_i':vsip_vleq_i,
       'vview_sivview_si':vsip_vleq_si,
       'vview_ucvview_uc':vsip_vleq_uc}
    t=getType(a)[1]+getType(b)[1]
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t + ' not supported for leq')
        return False
def lge(a,b,c):
    f={'mview_dmview_d':vsip_mlge_d,
       'mview_fmview_f':vsip_mlge_f,
       'vview_dvview_d':vsip_vlge_d,
       'vview_fvview_f':vsip_vlge_f,
       'vview_ivview_i':vsip_vlge_i,
       'vview_sivview_si':vsip_vlge_si,
       'vview_ucvview_uc':vsip_vlge_uc}
    t=getType(a)[1]+getType(b)[1]
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t + ' not supported for lge')
        return False
def lgt(a,b,c):
    f={'mview_dmview_d':vsip_mlgt_d,
       'mview_fmview_f':vsip_mlgt_f,
       'vview_dvview_d':vsip_vlgt_d,
       'vview_fvview_f':vsip_vlgt_f,
       'vview_ivview_i':vsip_vlgt_i,
       'vview_sivview_si':vsip_vlgt_si,
       'vview_ucvview_uc':vsip_vlgt_uc}
    t=getType(a)[1]+getType(b)[1]
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t + ' not supported for lgt')
        return False
def lle(a,b,c):
    f={'mview_dmview_d':vsip_mlle_d,
       'mview_fmview_f':vsip_mlle_f,
       'vview_dvview_d':vsip_vlle_d,
       'vview_fvview_f':vsip_vlle_f,
       'vview_ivview_i':vsip_vlle_i,
       'vview_sivview_si':vsip_vlle_si,
       'vview_ucvview_uc':vsip_vlle_uc}
    t=getType(a)[1]+getType(b)[1]
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t + ' not supported for lle')
        return False
def llt(a,b,c):
    f={'mview_dmview_d':vsip_mllt_d,
       'mview_fmview_f':vsip_mllt_f,
       'vview_dvview_d':vsip_vllt_d,
       'vview_fvview_f':vsip_vllt_f,
       'vview_ivview_i':vsip_vllt_i,
       'vview_sivview_si':vsip_vllt_si,
       'vview_ucvview_uc':vsip_vllt_uc}
    t=getType(a)[1]+getType(b)[1]
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t + ' not supported for llt')
        return False
def lne(a,b,c):
    f={'mview_dmview_d':vsip_mlne_d,
       'mview_fmview_f':vsip_mlne_f,
       'vview_dvview_d':vsip_vlne_d,
       'vview_fvview_f':vsip_vlne_f,
       'vview_ivview_i':vsip_vlne_i,
       'vview_sivview_si':vsip_vlne_si,
       'vview_ucvview_uc':sip_vlne_uc}
    t=getType(a)[1]+getType(b)[1]
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t + ' not supported for lne')
        return False
# Element Generation and Copy
def fill(a_scalar,a_view):
    """
        Fill view object b with scalar object a
        VSIPL functions supported are
        vsip_cmfill_d, vsip_cmfill_f, vsip_cvfill_d, vsip_cvfill_f, vsip_mfill_d, vsip_mfill_f,
        vsip_mfill_i, vsip_mfill_si, vsip_vfill_d, vsip_vfill_f, vsip_vfill_i, vsip_vfill_si, 
        vsip_vfill_uc
        """
    t1=getType(a_scalar)
    t2=getType(a_view)
    t=str()
    x=a_scalar
    ct=['cmview_f','cmview_d','cvview_f','cvview_d']
    f={ 'cscalar_dcmview_d':vsip_cmfill_d,
            'cscalar_fcmview_f':vsip_cmfill_f,
            'cscalar_dcvview_d':vsip_cvfill_d,
            'cscalar_fcvview_f':vsip_cvfill_f,
            'scalarmview_d':vsip_mfill_d,
            'scalarmview_f':vsip_mfill_f,
            'scalarmview_i':vsip_mfill_i,
            'scalarmview_si':vsip_mfill_si,
            'scalarvview_d':vsip_vfill_d,
            'scalarvview_f':vsip_vfill_f,
            'scalarvview_i':vsip_vfill_i,
            'scalarvview_vi':vsip_vfill_si,
            'scalarvview_uc':vsip_vfill_uc}
    if t2[1] in ct: #do complex
        myType=str()
        if t2[1] == 'cmview_d' or t2[1] == 'cvview_d':
            myType='cscalar_d'
        else:
            myType='cscalar_f'
        if t1[1] == 'scalar' or type(a_view) == complex:
            x=complexToCscalar(myType,a_scalar)
    t=getType(x)[1] + t2[1]
    if f.has_key(t):
        f[t](x,a_view)
        return a_view
    else:
        print('Type ' + t + ' not supported by fill') 

def ramp(a,b,c):
    """
        A ramp is supported for real vector types.
        called as ramp(start, increment, vector).
        Note the length is determined by the vector.
        returns the result as a convienience.
        """
    t=getType(c)
    f={'vview_f':vsip_vramp_f,
       'vview_d':vsip_vramp_d,
       'vview_i':vsip_vramp_i,
       'vview_si':vsip_vramp_si,
       'vview_uc':vsip_vramp_uc,
       'vview_vi':vsip_vramp_vi}
    if t[0] and f.has_key(t[1]):
        f[t[1]](a,b,c)
        return c
    else:
        print('Type ' + t + ' not supported by ramp')
        return False
def copy(a,b):
    f={'cmview_dcmview_d':vsip_cmcopy_d_d,
    'cmview_dcmview_f':vsip_cmcopy_d_f,
    'cmview_fcmview_d':vsip_cmcopy_f_d,
    'cmview_fcmview_f':vsip_cmcopy_f_f,
    'cvview_dcvview_d':vsip_cvcopy_d_d,
    'cvview_dcvview_f':vsip_cvcopy_d_f,
    'cvview_fcvview_d':vsip_cvcopy_f_d,
    'cvview_fcvview_f':vsip_cvcopy_f_f,
    'mview_blmview_bl':vsip_mcopy_bl_bl,
    'mview_blmview_d':vsip_mcopy_bl_d,
    'mview_blmview_f':vsip_mcopy_bl_f,
    'mview_dmview_bl':vsip_mcopy_d_bl,
    'mview_dmview_d':vsip_mcopy_d_d,
    'mview_dmview_f':vsip_mcopy_d_f,
    'mview_dmview_i':vsip_mcopy_d_i,
    'mview_dmview_uc':vsip_mcopy_d_uc,
    'mview_fmview_bl':vsip_mcopy_f_bl,
    'mview_fmview_d':vsip_mcopy_f_d,
    'mview_fmview_f':vsip_mcopy_f_f,
    'mview_fmview_i':vsip_mcopy_f_i,
    'mview_fmview_uc':vsip_mcopy_f_uc,
    'mview_imview_f':vsip_mcopy_i_f,
    'mview_simview_f':vsip_mcopy_si_f,
    'vview_blvview_bl':vsip_vcopy_bl_bl,
    'vview_blvview_d':vsip_vcopy_bl_d,
    'vview_blvview_f':vsip_vcopy_bl_f,
    'vview_dvview_bl':vsip_vcopy_d_bl,
    'vview_dvview_d':vsip_vcopy_d_d,
    'vview_dvview_f':vsip_vcopy_d_f,
    'vview_dvview_i':vsip_vcopy_d_i,
    'vview_dvview_si':vsip_vcopy_d_si,
    'vview_dvview_uc':vsip_vcopy_d_uc,
    'vview_dvview_vi':vsip_vcopy_d_vi,
    'vview_fvview_bl':vsip_vcopy_f_bl,
    'vview_fvview_d':vsip_vcopy_f_d,
    'vview_fvview_f':vsip_vcopy_f_f,
    'vview_fvview_i':vsip_vcopy_f_i,
    'vview_fvview_si':vsip_vcopy_f_si,
    'vview_fvview_uc':vsip_vcopy_f_uc,
    'vview_fvview_vi':vsip_vcopy_f_vi,
    'vview_ivview_d':vsip_vcopy_i_d,
    'vview_ivview_f':vsip_vcopy_i_f,
    'vview_ivview_i':vsip_vcopy_i_i,
    'vview_ivview_uc':vsip_vcopy_i_uc,
    'vview_ivview_vi':vsip_vcopy_i_vi,
    'vview_mivview_mi':vsip_vcopy_mi_mi,
    'vview_sivview_d':vsip_vcopy_si_d,
    'vview_sivview_f':vsip_vcopy_si_f,
    'vview_sivview_si':vsip_vcopy_si_si,
    'vview_vivview_i':vsip_vcopy_vi_i,
    'vview_vivview_vi':vsip_vcopy_vi_vi}
    f1v={'cvview_d':get, 'cvview_f':get, 'vview_d':get, 
         'vview_f':get, 'vview_i':get, 'vview_si':get, 
         'vview_uc':get, 'vview_vi':get, 'vview_bl':get, 'vview_mi':get}
    f1m={'cmview_d':get, 'cmview_f':get, 'mview_d':get, 'mview_f':get, 
         'mview_i':get, 'mview_si':get, 'mview_uc':get, 'mview_bl':get}
    t1=getType(a)[1]
    t2=getType(b)[1]
    t=t1+t2
    if f.has_key(t):
        f[t](a,b)
        return b
    elif f1v.has_key(t1) and f1v.has_key(t2):
        for i in range(getlength(a)):
            put(b,i,get(a,i))
        return b
    elif f1m.has_key(t1) and f1m.has_key(t2):
        for i in range(getcollength(a)):
            for j in range(getrowlength(a)): 
                put(b,[i,j],get(a,[i,j]))
        return b
    else:
        print('Type <:' + t1 + t2 + ':> not supported by copy')
        return False    

# Selection Operations
# Selection Operations
def clip(a,t1,t2,c1,c2,r):
    f = {'mview_d':vsip_mclip_d, 
         'mview_f':vsip_mclip_f, 
         'mview_i':vsip_mclip_i, 
         'mview_si':vsip_mclip_si, 
         'vview_d':vsip_vclip_d, 
         'vview_f':vsip_vclip_f, 
         'vview_i':vsip_vclip_i, 
         'vview_si':vsip_vclip_si, 
         'vview_uc':vsip_vclip_uc}
    t=getType(a)[1]
    if f.has_key(t):
        f[t](a,t1,t2,c1,c2,r)
        return r
    else:
        print('Not a supported type for clip')
        return False
def invclip(a,t1,t2,t3,c1,c2,r):
    f={'mview_d':vsip_minvclip_d,
       'mview_f':vsip_minvclip_f,
       'vview_d':vsip_vinvclip_d,
       'vview_f':vsip_vinvclip_f,
       'vview_i':vsip_vinvclip_i,
       'vview_si':vsip_vinvclip_si,
       'vview_uc':vsip_vinvclip_uc}
    t=getType(a)[1]
    if f.has_key(t):
        f[t](a,t1,t2,t3,c1,c2,r)
        return r
    else:
        print('Type ' + t + ' not supported for indexbool')
        return False
def indexbool(a,b):
    f={'mview_bl':vsip_mindexbool,
       'vview_bl':vsip_vindexbool}
    t=getType(a)[1]
    if f.has_key(t):
        return f[t](a,b)
    else:
        print('Type ' + t + ' not supported for indexbool')
        return False
def max(a,b,c):
    f={'mview_d':vsip_mmax_d,
       'mview_f':vsip_mmax_f,
       'vview_d':vsip_vmax_d,
       'vview_f':vsip_vmax_f}
    t=getType(a)[1]
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t + ' not supported for max')
        return False
def maxmg(a,b,c):
    f={'mview_d':vsip_mmaxmg_d,
       'mview_f':vsip_mmaxmg_f,
       'vview_d':vsip_vmaxmg_d,
       'vview_f':vsip_vmaxmg_f}
    t=getType(a)[1]
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t + ' not a supported type for maxmg')
        return False
def maxmgsq(a,b,c):
    f={'cmview_d':vsip_mcmaxmgsq_d,
       'cmview_f':vsip_mcmaxmgsq_f,
       'cvview_d':vsip_vcmaxmgsq_d,
       'cvview_f':vsip_vcmaxmgsq_f}
    t=getType(a)[1]
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t + ' not a supported type for maxmgsq')
        return False
def maxmgsqval(a,idx):
    f={'cmview_dscalar_mi':'vsip_mcmaxmgsqval_d(a,idx)',
       'cvview_dscalar_vi':'vsip_vcmaxmgsqval_d(a,idx)',
       'cmview_fscalar_mi':'vsip_mcmaxmgsqval_f(a,idx)',
       'cvview_fscalar_vi':'vsip_vcmaxmgsqval_f(a,idx)'}
    t=getType(a)[1]+getType(idx)[1]
    if f.has_key(t):
        return eval(f[t])
    else:
        print('Type ' + t + ' not supported for maxmgsqval')
        return False
def maxmgval(a,idx):
    f={'mview_dscalar_mi':'vsip_mmaxmgval_d(a,idx)',
       'vview_dscalar_vi':'vsip_vmaxmgval_d(a,idx)',
       'mview_fscalar_mi':'vsip_mmaxmgval_f(a,idx)',
       'vview_fscalar_vi':'vsip_vmaxmgval_f(a,idx)'}
    t=getType(a)[1]+getType(idx)[1]
    if f.has_key(t):
        return eval(f[t])
    else:
        print('Type ' + t + ' not supported for maxmgval')  
def maxval(a,idx):
    f={'mview_d':'vsip_mmaxval_d(a,idx)',
       'vview_d':'vsip_vmaxval_d(a,idx)',
       'mview_f':'vsip_mmaxval_f(a,idx)',
       'vview_f':'vsip_vmaxval_f(a,idx)',
       'mview_i':'vsip_mmaxval_i(a,idx)',
       'vview_i':'vsip_vmaxval_i(a,idx)',
       'mview_si':'vsip_mmaxval_si(a,idx)',
       'vview_si':'vsip_vmaxval_si(a,idx)'}
    t=getType(a)[1]
    if f.has_key(t):
        return eval(f[t])
    else:
        print('Type ' + t + ' not suppqorted for maxval')
def min(a,b,c):
    f={'mview_d':vsip_mmin_d,
       'mview_f':vsip_mmin_f,
       'vview_d':vsip_vmin_d,
       'vview_f':vsip_vmin_f}
    t=getType(a)[1]
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t + ' not a supported type for min')
        return False
def minmg(a,b,c):
    f={'mview_d':vsip_mminmg_d,
       'mview_f':vsip_mminmg_f,
       'vview_d':vsip_vminmg_d,
       'vview_f':vsip_vminmg_f}
    t=getType(a)[1]
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t + ' not a supported type for minmg')
        return False
def minmgsq(a,b,c):
    f={'cmview_d':vsip_mcminmgsq_d,
       'cmview_f':vsip_mcminmgsq_f,
       'cvview_d':vsip_vcminmgsq_d,
       'cvview_f':vsip_vcminmgsq_f}
    t=getType(a)[1]
    if f.has_key(t):
        f[t](a,b,c)
        return c
    else:
        print('Type ' + t + ' not a supported type for minmgsq')
        return False
def minmgval(a,idx):
    f={'mview_dscalar_mi':'vsip_mminmgval_d(a,idx)',
       'vview_dscalar_vi':'vsip_vminmgval_d(a,idx)',
       'mview_fscalar_mi':'vsip_mminmgval_f(a,idx)',
       'vview_fscalar_vi':'vsip_vminmgval_f(a,idx)'}
    t=getType(a)[1]+getType(idx)[1]
    if f.has_key(t):
        return eval(f[t])
    else:
        print('Type ' + t + ' not supported for minmgval')
        return False
def minval(a,idx):
    f={'mview_d':'vsip_mminval_d(a,idx)',
       'vview_d':'vsip_vminval_d(a,idx)',
       'mview_f':'vsip_mminval_f(a,idx)',
       'vview_f':'vsip_vminval_f(a,idx)'}
    t=getType(a)[1]
    if f.has_key(t):
        return eval(f[t])
    else:
        print('Type ' + t + ' not supported for minval')
        return False

# Bitwise and Boolean
def andd(a,b,c):
    """
        renamed 'andd' to avoid collision with python keyword
    """
    f={'mview_i':'vsip_mand_i(a,b,c)',
       'mview_si':'vsip_mand_si(a,b,c)',
       'vview_bl':'vsip_vand_bl(a,b,c)',
       'vview_i':'vsip_vand_i(a,b,c)',
       'vview_si':'vsip_vand_si(a,b,c)',
       'vview_uc':'vsip_vand_uc(a,b,c)' }
    t=getType(a)[1]
    if f.has_key(t):
        eval(f[t])
        return c
    else:
        print('Type ' + t + ' not a supported type for and')
        return False
def nott(a,b):
    """
       renamed 'nott' to avoid collision with python keyword
    """
    f={'vview_bl':'vsip_vnot_bl(a,b)',
       'vview_i':'vsip_vnot_i(a,b)',
       'vview_si':'vsip_vnot_si(a,b)',
       'vview_uc':'vsip_vnot_uc(a,b)'}
    t=getType(a)[1]
    if f.has_key(t):
        eval(f[t])
        return b
    else:
        print('Type ' + t + ' not a supported type for not')
        return False
def orr(a,b,c):
    """
       renamed 'orr' to avoid collision with python keyword.
    """
    f={'vview_bl':'vsip_vor_bl(a,b,c)',
       'vview_i':'vsip_vor_i(a,b,c)',
       'vview_si':'vsip_vor_si(a,b,c)',
       'vview_uc':'vsip_vor_uc(a,b,c)'}
    t=getType(a)[1]
    if f.has_key(t):
        eval(f[t])
        return c
    else:
        print('Type ' + t + ' not a supported type for or')
        return False
def xor(a,b,c):
    f={'vview_bl':'vsip_vxor_bl(a,b,c)',
       'vview_i':'vsip_vxor_i(a,b,c)',
       'vview_si':'vsip_vxor_si(a,b,c)',
       'vview_uc':'vsip_vxor_uc(a,b,c)'}
    t=getType(a)[1]
    if f.has_key(t):
        eval(f[t])
        return c
    else:
        print('Type ' + t + ' not a supported type for xor')
        return False

# Manipulation
def cmplx(r,i,c):
    f={'vview_d':'vsip_vcmplx_d(r,i,c)',
       'vview_f':'vsip_vcmplx_f(r,i,c)'}
    t=getType(r)[1]
    if f.has_key(t):
        eval(f[t])
        return c
    else:
        print('Type ' + t + ' not supported by cmplx')
        return False
def gather(input,indx,output):
    f={'cmview_d':'vsip_cmgather_d(input,indx,output)',
       'cmview_f':'vsip_cmgather_f(input,indx,output)',
       'cvview_d':'vsip_cvgather_d(input,indx,output)',
       'cvview_f':'vsip_cvgather_f(input,indx,output)',
       'mview_d':'vsip_mgather_d(input,indx,output)',
       'mview_f':'vsip_mgather_f(input,indx,output)',
       'vview_d':'vsip_vgather_d(input,indx,output)',
       'vview_f':'vsip_vgather_f(input,indx,output)',
       'vview_i':'vsip_vgather_i(input,indx,output)',
       'vview_si':'vsip_vgather_si(input,indx,output)',
       'vview_uc':'vsip_vgather_uc(input,indx,output)',
       'vview_mi':'vsip_vgather_mi(input,indx,output)',
       'vview_vi':'vsip_vgather_vi(input,indx,output)'}
    t=getType(input)[1]
    if f.has_key(t):
        eval(f[t])
        return output
    else:
        print('Type ' + t + ' not supported by gather')
        return False
def scatter(input,output,indx):
    f={'cvview_d':'vsip_cmscatter_d(input,output,indx)',
       'cvview_f':'vsip_cmscatter_f(input,output,indx)',
       'cvview_d':'vsip_cvscatter_d(input,output,indx)',
       'cvview_f':'vsip_cvscatter_f(input,output,indx)',
       'vview_d':'vsip_mscatter_d(input,output,indx)',
       'vview_f':'vsip_mscatter_f(input,output,indx)',
       'vview_d':'vsip_vscatter_d(input,output,indx)',
       'vview_f':'vsip_vscatter_f(input,output,indx)',
       'vview_i':'vsip_vscatter_i(input,output,indx)',
       'vview_si':'vsip_vscatter_si(input,output,indx)',
       'vview_uc':'vsip_vscatter_uc(input,output,indx)'}
    t=getType(input)[1]
    if f.has_key(t):
        eval(f[t])
        return output
    else:
        print('Type ' + t + ' not supported by scatter')
        return False
def polar(input,r,phi):
    f={'cvview_d':'vsip_vpolar_d(input,r,phi)',
       'cvview_f':'vsip_vpolar_f(input,r,phi)'}
    t=getType(input)[1]
    if f.has_key(t):
        eval(f[t])
        return(r,phi)
    else:
        print('Type ' + t + ' not supported for polar')
        return False
def rect(r,phi,ouput):
    f={'vview_d':'vsip_vrect_d(r,phi,output)',
       'vview_f':'vsip_vrect_f(r,phi,output)'}
    t=getType(r)[1]
    if f.has_key(t):
        eval(f[t])
        return output
    else:
        print('Type ' + t + ' not supported for rect')
        return False
def real(c,r):
    f={'cvview_d':'vsip_vreal_d(c,r)',
      'cvview_f':'vsip_vreal_f(c,r)'}
    t=getType(c)[1]
    if f.has_key(t):
        eval(f[t])
        return r
    else:
        print('Type ' + t + ' not supported for real')
        return False
def imag(c,i):
    f={'cvview_d':'vsip_vreal_d(c,i)',
      'cvview_f':'vsip_vreal_f(c,i)'}
    t=getType(c)[1]
    if f.has_key(t):
        eval(f[t])
        return i
    else:
        print('Type ' + t + ' not supported for imag')
        return False
def swap(a,b):
    f={'cmview_d':vsip_cmswap_d,
       'cmview_f':vsip_cmswap_f,
       'cvview_d':vsip_cvswap_d,
       'cvview_f':vsip_cvswap_f,
       'mview_d':vsip_mswap_d,
       'mview_f':vsip_mswap_f,
       'vview_d':vsip_vswap_d,
       'vview_f':vsip_vswap_f,
       'vview_i':vsip_vswap_i,
       'vview_si':vsip_vswap_si,
       'vview_uc':vsip_vswap_uc}
    t=getType(a)[1]
    if f.has_key(t):
        f[t](a,b)
        return(a,b)
    else:
        print('Type ' + t + ' not supported by swap');
        return False

# FFT Functions
def fftCreate(t,arg):
    """
       This function creates a VSIPL fft Object. It takes a type argument as a string,
       and a tuple argument that corresponds to the VSIPL function call argument list.
       The first argument for fftCreate corresponds to the supported types for fft call
       input and output views. For out-of-place this would be (for instance)
       'cvview_dcvview_d' for ccfftop with double precision and 
       'vview_fcvview_f for 'rcfftop' for float precision. 
       For in-place calls only the type of the input/output view is called for.
       'if the views are matrix views then the multiple fft object is created.
        If the type FFT requested is not supported then a message is printed and False
        is returned'
    """
    if type(arg) != tuple:
        print('second argument must be a tuple coresponding to VSIP fft create call')
    f={ 'cvview_d':'vsip_ccfftip_create_d(arg[0] , arg[1] , arg[2] , arg[3] , arg[4])',
        'cvview_f':'vsip_ccfftip_create_f(arg[0] , arg[1] , arg[2] , arg[3] , arg[4])',
        'cvview_dcvview_d':'vsip_ccfftop_create_d(arg[0] , arg[1] , arg[2] , arg[3] , arg[4])',
        'cvview_fcvview_f':'vsip_ccfftop_create_f(arg[0] , arg[1] , arg[2] , arg[3] , arg[4])',
        'vview_dcvview_d':'vsip_rcfftop_create_d(arg[0] , arg[1] , arg[2] , arg[3])', 
        'vview_fcvview_f':'vsip_rcfftop_create_f(arg[0] , arg[1] , arg[2] , arg[3])',
        'cvview_dvview_d':'vsip_crfftop_create_d(arg[0] , arg[1] , arg[2] , arg[3])', 
        'cvview_dvview_f':'vsip_crfftop_create_f(arg[0] , arg[1] , arg[2] , arg[3])',
        'cmview_d':'vsip_ccfftmip_create_d(arg[0] , arg[1] , arg[2] , arg[3] , arg[4] , arg[5] , arg[6])',
        'cmview_f':'vsip_ccfftmip_create_f(arg[0] , arg[1] , arg[2] , arg[3] , arg[4] , arg[5] , arg[6])' ,
        'cmview_dcmview_d':'vsip_ccfftmop_create_d(arg[0] , arg[1] , arg[2] , arg[3] , arg[4] , arg[5] , arg[6])' ,
        'cmview_fcmview_f':'vsip_ccfftmop_create_f(arg[0] , arg[1] , arg[2] , arg[3] , arg[4] , arg[5] , arg[6])' ,
        'cmview_dmview_d':'vsip_crfftmop_create_d(arg[0] , arg[1] , arg[2] , arg[3] , arg[4] , arg[5]) ', 
        'cmview_fmview_f':'vsip_crfftmop_create_f(arg[0] , arg[1] , arg[2] , arg[3] , arg[4] , arg[5]) ',
        'mview_dcmview_d':'vsip_rcfftmop_create_d,(arg[0] , arg[1] , arg[2] , arg[3] , arg[4] , arg[5])',  
        'mview_fcmview_f':'vsip_rcfftmop_create_f(arg[0] , arg[1] , arg[2] , arg[3] , arg[4] , arg[5])' }
    if f.has_key(t):
        return eval(f[t])
    else:
        print('Not a valid type for FFT create')
        return False
def fftip(fftobj,a):
    f={ 'cvview_d':vsip_ccfftip_d,
        'cvview_f':vsip_ccfftip_f,
        'cmview_d':vsip_ccfftmip_d,
        'cmview_f':vsip_ccfftmip_f}
    t=getType(a)[1]
    if f.has_key(t):
        return f[t](fftobj,a)
    else:
        print('Not a valid type for fftip')
        return False
def fftop(fftobj,a,b):
    f={ 'cvview_dcvview_d':vsip_ccfftop_d,
        'cvview_fcvview_f':vsip_ccfftop_f,
        'vview_dcvview_d':vsip_rcfftop_d,
        'vview_fcvview_f':vsip_rcfftop_f,
        'cvview_dvview_d':vsip_crfftop_d,
        'cvview_fvview_f':vsip_crfftop_f,
        'cmview_dcmview_d':vsip_ccfftmop_d,
        'cmview_fcmview_f':vsip_ccfftmop_f,
        'cmview_dmview_d':vsip_crfftmop_d,
        'cmview_fmview_f':vsip_crfftmop_f,
        'mview_dcmview_d':vsip_rcfftmop_d,
        'mview_fcmview_f':vsip_rcfftmop_f}
    t=getType(a)[1]+getType(b)[1]
    if f.has_key(t):
        return f[t](fftobj,a,b)
    else:
        print('Not a valid type for fftop')
        return False
def fftDestroy(fftobj):
    f={ 'fft_d':vsip_fft_destroy_d,
        'fft_f':vsip_fft_destroy_f,
        'fftm_d':vsip_fftm_destroy_d,
        'fftm_f':vsip_fftm_destroy_f}
    t=getType(fftobj)[1]
    if f.has_key(t):
        return f[t](fftobj)
    else:
        print('Not a valid type for fftDestroy')
        return False

#Fir Functions
#TVCPP does not seem to handle the rcfir case. may need to fix that. 
#rcfir case breaks my key-value coding below.
def firCreate(kernel,sym,length,decimation,state,ntimes,alghint):
    """
       create a fir object. Call with same arguments as in VSIPL API document.
       """
    f={ 'cvview_d':vsip_cfir_create_d,
        'cvview_f':vsip_cfir_create_f,
        'vview_d':vsip_fir_create_d,
        'vview_f':vsip_fir_create_f}
    t=getType(kernel)[1]
    if f.has_key(t):
        return f[t](kernel,sym,length,decimation,state,ntimes,alghint)
    else:
        print('Not a supported kernel type for fir Create')
        return False
def firDestroy(fir):
    f={ 'cfir_d':vsip_cfir_destroy_d,
        'cfir_f':vsip_cfir_destroy_f, 
        'fir_d': vsip_fir_destroy_d,
        'fir_f': vsip_fir_destroy_f}
    t=getType(fir)[1]
    if f.has_key(t):
        f[t](fir)
    else:
        print('not a fir object')
def firfilt(fir,input,output):
    f={ 'cfir_d': vsip_cfirflt_d,
        'cfir_f': vsip_cfirflt_f, 
        'fir_d': vsip_firflt_d, 
        'fir_f': vsip_firflt_f}
    t=getType(fir)[1]
    if f.has_key(t):
        return f[t](fir,input,output)
    else:
        print('Not a fir object passed to Fir Filt')
        return False
def firReset(fir):
    f={ 'cfir_d': vsip_cfir_reset_d,
        'cfir_f': vsip_cfir_reset_f,
        'fir_d': vsip_fir_reset_d, 
        'fir_f': vsip_fir_reset_f}
    t=getType(fir)[1]
    if f.has_key(t):
        f[t](fir)
        return fir
    else:
        print('Type ' + t + ' not a fir object')
        return False

# Miscellaneous
def histo(src,min_bin,max_bin,opt,hist):
    t=getType(src)[1]
    f={'mview_d': vsip_mhisto_d,
       'mview_f': vsip_mhisto_f,
       'mview_i': vsip_mhisto_i,
       'mview_si': vsip_mhisto_si,
       'vview_d':vsip_vhisto_d,
       'vview_f':vsip_vhisto_f,
       'vview_i': vsip_vhisto_i,
       'vview_si': vsip_vhisto_si}
    if f.has_key(t):
        f[t](src,min_bin,max_bin,opt,hist)
        return hist
    else:
        print('Type ' + t + ' not supported by histogram')
        return False
def freqswap(x):
    """Swaps halves of a vector, or quadrants of a matrix, to remap zero 
       frequencies from the origin to the middle.
    """
    f = { 'cvview_d':vsip_cvfreqswap_d,
          'vview_d':vsip_vfreqswap_d,
          'cmview_d':vsip_cmfreqswap_d,
          'mview_d':vsip_mfreqswap_d,
          'cvveiw_f':vsip_cvfreqswap_f,
          'vview_f':vsip_vfreqswap_f,
          'cmview_f':vsip_cmfreqswap_f,
          'mview_f':vsip_mfreqswap_f}
    t=getType(x)[1]
    if f.has_key(t):
        f[t](x)
        return x
    else:
        print('Type ' + t + ' not supported for freqswap')
        return(False)

# Matrix and Vector Operations
def herm(a,b):
    f = {   'cmview_d':vsip_cmherm_d, 'cmview_f':vsip_cmherm_f}
    t = getType(a)
    if t[0] and t == getType(b) and f.has_key(t[1]):
        f[t[1]](a,b)
        return b
    else:
        print('Not a supported argument list for cmherm')
        return False
def jdot(a,b):
    f  = {  'cvview_f':vsip_cvjdot_f, 'cvview_d':vsip_cvjdot_f}
    t=getType(a)
    if t[0] and t == getType(b) and f.has_key(t[1]):
        return f[t[1]](a,b)
    else:
        print('Not a supported argument list for cvjdot')
        return False
def gemp(alpha,A,opa,B,opB,beta,C):
    f = {   'mview_f':vsip_gemp_f,
            'mview_d':vsip_gemp_d,
            'cmview_d':vsip_cgemp_d,
            'cmview_f':vsip_cgemp_f}
    t=getType(A)
    if t == getType(B) and t == getType(C) and t[0] and f.has_key(t[1]):
        f[t[1]](alpha,A,opa,B,opb,beta,C)
        return C
    else:
        print('Not a supported argument type for gemp')
        return False
def gems(alpha,A,opa,beta,C):
    f = {   'mview_f':vsip_gems_f,
            'mview_d':vsip_gems_d,
            'cmview_d':vsip_cgems_d,
            'cmview_f':vsip_cgems_f}
    t=getType(A)
    if t == getType(C) and t[0] and f.has_key(t[1]):
        f[t[1]](alpha,A,opa,beta,C)
        return C
    else:
        print('Not a supported argument list for gems')
        return False
def kron(alpha,a,b,C):
    f={ 'cmview_dcmview_d':vsip_cmkron_d,
        'cmview_fcmview_f':vsip_cmkron_f,
        'cvview_dcmview_d':vsip_cvkron_d,
        'cvview_fcmview_f':vsip_cvkron_f,
        'mview_dmview_d':vsip_mkron_d,
        'mview_fmview_f':vsip_mkron_f,
        'vview_dmview_d':vsip_vkron_d,
        'vview_fmview_f':vsip_vkron_f}
    t1=getType(a)
    t2=getType(C)
    t=str()
    if t1[0]:
        t=t1[1]+t2[1]
    if f.has_key(t):
        f[t](alpha,a,b,C)
        return C
    else:
        print('Not a supported type')
        return False
def prod3(A,B,C):
    f = {   'mview_fmview_f':vsip_mprod3_f,
            'mview_dmview_d':vsip_mprod3_d,
            'cmview_dcmview_d':vsip_cmprod3_d,
            'cmview_fcmview_f':vsip_cmprod3_f,
            'mview_fvview_f':vsip_mvprod3_f,
            'mview_dvview_d':vsip_mvprod3_d,
            'cmview_fcvview_f':vsip_cmvprod3_f,
            'cmview_dcvview_d':vsip_cmvprod3_d}
    t1=getType(A)
    t2=getType(B)
    t=str()
    if t1[0]:
        t=t1[1]+t2[1]
    if f.has_key(t):
        f[t](A,B,C)
        return C
    else:
        print('Not a supported type for prod3')
        return False
def prod4(A,B,C):
    f = {   'mview_fmview_f':vsip_mprod4_f,
            'mview_dmview_d':vsip_mprod4_d,
            'cmview_dcmview_d':vsip_cmprod4_d,
            'cmview_fcmview_f':vsip_cmprod4_f,
            'mview_fvview_f':vsip_mvprod4_f,
            'mview_dvview_d':vsip_mvprod4_d,
            'cmview_fcvview_f':vsip_cmvprod4_f,
            'cmview_dcvview_d':vsip_cmvprod4_d}
    t1=getType(A)
    t2=getType(B)
    t=str()
    if t1[0]:
        t=t1[1]+t2[1]
    if f.has_key(t):
        f[t](A,B,C)
        return C
    else:
        print('Not a supported type for prod4')
        return False
def prod(A,B,C):
    f={ 'mview_dmview_d':vsip_mprod_d,
        'mview_fmview_f':vsip_mprod_f,
        'cmview_dcmview_d':vsip_cmprod_d,
        'cmview_fcmview_f':vsip_cmprod_f,
        'mview_dvview_d':vsip_mvprod_d,
        'mview_fvview_f':vsip_mvprod_f,
        'cmview_dcvview_f':vsip_cmvprod_d,
        'cmview_dcvview_f':vsip_cmvprod_f,
        'vview_dmview_d':vsip_vmprod_d,
        'vview_fmview_f':vsip_vmprod_f,
        'cvview_dcmview_d':vsip_cvmprod_d,
        'cvview_fcmview_f':vsip_cvmprod_f}
    t1=getType(A)
    t2=getType(B)
    t=str()
    if t1[0]:
        t=t1[1]+t2[1]
    if f.has_key(t):
        f[t](A,B,C)
        return C
    else:
        print('Not a supported type')
        return False
def prodh(A,B,C):
    f = {'cmview_d':vsip_cmprodh_d,'cmview_f':vsip_cmprodh_f}
    t=getType(A)
    if t[0] and t==getType(B) and t==getType(C) and f.has_key(t[1]):
        f[t[1]](A,B,C)
        return C
    else:
        print('Not a supported argument type for prodh')
        return False
def prodj(A,B,C):
    f = {'cmview_d':vsip_cmprodj_d,'cmview_f':vsip_cmprodj_f}
    t=getType(A)
    if t[0] and t==getType(B) and t==getType(C) and f.has_key(t[1]):
        f[t[1]](A,B,C)
        return C
    else:
        print('Not a supported argument type for prodj')
        return False
def prodt(A,B,C):
    f = {'cmview_d':vsip_cmprodt_d,'cmview_f':vsip_cmprodt_f,
         'mview_d':vsip_mprodt_d,'mview_f':vsip_mprodt_f}
    t=getType(A)
    if t[0] and t==getType(B) and t==getType(C) and f.has_key(t[1]):
        f[t[1]](A,B,C)
        return C
    else:
        print('Not a supported argument type for prodt')
        return False
def trans(A,C):
    f = {'cmview_d':vsip_cmtrans_d,'cmview_f':vsip_cmtrans_f,
         'mview_d':vsip_mtrans_d,  'mview_f':vsip_mtrans_f}
    t=getType(A)
    if t[0] and t==getType(C) and f.has_key(t[1]):
        f[t[1]](A,C)
        return C
    else:
        print('Not a supported argument type for trans')
        return False
def outer(alpha,x,y,C):
    f = {   'scalarvview_f':vsip_vouter_f,
            'scalarvview_d':vsip_vouter_d,
            'cscalar_dcvview_d':vsip_cvouter_d,
            'cscalar_fcvview_f':vsip_cvouter_f}
    t1=getType(alpha)
    t2=getType(x)
    t=str()
    if t2[0] and t1[0]:
        t=t1[1] + t2[1]
    if f.has_key(t):
        f[t](alpha,x,y,C)
        return C
    else:
        print('Not a supported argument list for outer product')
        return False
def dot(a,b):
    """
       The dot product can be done on vview_f, vview_d, cvview_f and cvview_d.
       It returns a scalar or cscalar of the appropriate type.
       s = dot(a,b)
       """
    f  = {  'vview_f':vsip_vdot_f,
            'vview_d':vsip_vdot_d,
            'cvview_f':vsip_cvdot_f,
            'cvview_d':vsip_cvdot_f}
    t=getType(a)
    if t[0] and t == getType(b) and f.has_key(t[1]):
        return f[t[1]](a,b)
    else:
        print('Not a supported argument list for dot')
        return False

# General Square System Solver (LU Decompositon)
def lud_create(t,N):
    """
       lu = lud_create(t,N)
       where
            t is a type 
            N is the size
       types supported are 'lu_f', 'clu_f', 'lu_d', 'clu_d'
    """
    f={'lu_f':vsip_lud_create_f,
       'clu_f':vsip_clud_create_f,
       'lu_d':vsip_lud_create_d,
       'clu_d':vsip_clud_create_d}
    if f.has_key(t):
        return f[t](N)
    else:
        print('Type ' + t + ' not supported by lud_create')
        return False
def lud_destroy(lu):
    t=getType(lu)[1]
    f=f={'lu_f':vsip_lud_destroy_f,
         'clu_f':vsip_clud_destroy_f,
         'lu_d':vsip_lud_destroy_d,
         'clu_d':vsip_clud_destroy_d}
    if f.has_key(t):
        return f[t](lu)
    else:
        print('Type ' + t + ' not supported by lud_destroy')
def lud(lu,A):
    f=f={'lu_fmview_f':vsip_lud_f,
         'clu_fcmview_f':vsip_clud_f,
         'lu_dmview_d':vsip_lud_d,
         'clu_dcmview_d':vsip_clud_d}
    t=getType(lu)[1] + getType(A)[1]
    if f.has_key(t):
        ret= f[t](lu,A)
        return (ret,lu)
    else:
        print('Type ' + t + ' not supported by lud')
        return False
def lusol(lu,op,A):
    f=f={'lu_fmview_f':vsip_lusol_f,
         'clu_fcmview_f':vsip_clusol_f,
         'lu_dmview_d':vsip_lusol_d,
         'clu_dcmview_d':vsip_clusol_d}
    t=getType(lu)[1] + getType(A)[1]
    if f.has_key(t):
        ret= f[t](lu,op,A)
        return (ret,A)
    else:
        print('Type ' + t + ' not supported by lusol')
        return False

# Symetric square system solver (Cholesky decomposition)
def chold(ch,A):
    f={'chol_fmview_f':vsip_chold_f,
       'cchol_fcmview_f':vsip_cchold_f,
       'chol_dmview_d':vsip_chold_d,
       'cchol_dcmview_d':vsip_cchold_d}
    t=getType(ch)[1]+getType(A)[1]
    if f.has_key(t):
        ret= f[t](ch,A)
        return(ret,ch)
    else:
        print('Type ' + t + ' not supported by chold')
        return False
def chold_create(t,op,N):
    f={'chol_f':vsip_chold_create_f,
       'cchol_f':vsip_cchold_create_f,
       'chol_d':vsip_chold_create_d,
       'cchold_d':vsip_cchold_create_d}
    if f.has_key(t):
        return f[t](op,N)
    else:
        print('Type ' + t + ' not supported by chold_create')
        return False
def chold_destroy(ch):
    t=getType(ch)[1]
    f=f={'chol_f':vsip_chold_destroy_f,
         'cchol_f':vsip_cchold_destroy_f,
         'chol_d':vsip_chold_destroy_d,
         'cchol_d':vsip_cchold_destroy_d}
    if f.has_key(t):
        return f[t](ch)
    else:
        print('Type ' + t + ' not supported by chold_destroy')
        return False
def cholsol(ch,XB):
    f={'chol_fmview_f':vsip_cholsol_f,
       'cchol_fcmview_f':vsip_ccholsol_f,
       'chol_dmview_d':vsip_cholsol_d,
       'cchol_dcmview_d':vsip_ccholsol_d}
    t=getType(ch)[1]+getType(XB)[1]
    if f.has_key(t):
        ret= f[t](ch,XB)
        return(ret,XB)
    else:
        print('Type ' + t + ' not supported by cholsol')
        return False

# Over-determined  Linear System Solver (QR Decomposition)
def qrd(qr,A):
    f={'qr_fmview_f':vsip_qrd_f,
       'cqr_fcmview_f':vsip_cqrd_f,
       'qr_dmview_d':vsip_qrd_d,
       'cqr_dcmview_d':vsip_cqrd_d}
    t=getType(qr)[1]+getType(A)[1]
    if f.has_key(t):
        ret= f[t](qr,A)
        return(ret,qr)
    else:
        print('Type ' + t + ' not supported by qrd')
        return False
def qrd_create(t,M,N,op):
    f={'qr_f':vsip_qrd_create_f,
       'cqr_f':vsip_cqrd_create_f,
       'qr_d':vsip_qrd_create_d,
       'cqr_d':vsip_cqrd_create_d}
    if f.has_key(t):
        return f[t](M,N,op)
    else:
        print('Type ' + t + ' not supported by qrd_create')
        return False
def qrd_destroy(qr):
    t=getType(qr)[1]
    f=f={'qr_f':vsip_qrd_destroy_f,
         'cqr_f':vsip_cqrd_destroy_f,
         'qr_d':vsip_qrd_destroy_d,
         'cqr_d':vsip_cqrd_destroy_d}
    if f.has_key(t):
        return f[t](qr)
    else:
        print('Type ' + t + ' not supported by chold_destroy')
        return False
def qrdprodq(qr,op,side,A):
    f={'qr_fmview_f':vsip_qrdprodq_f,
       'cqr_fcmview_f':vsip_cqrdprodq_f,
       'qr_dmview_d':vsip_qrdprodq_d,
       'cqr_dcmview_d':vsip_cqrdprodq_d}
    t=getType(qr)[1] + getType(A)[1]
    if f.has_key(t):
        ret=f[t](qr,op,side,A)
        return(ret,A)
    else:
        print('Type ' + t + ' not supported by qrdqrodq')
        return False
def qrdsolr(qr,op,scl,XB):
    f={'qr_fmview_f':vsip_qrdsolr_f,
       'cqr_fcmview_f':vsip_cqrdsolr_f,
       'qr_dmview_d':vsip_qrdsolr_d,
       'cqr_dcmview_d':vsip_cqrdsolr_d}
    t=getType(qr)[1] + getType(XB)[1]
    if f.has_key(t):
        ret=f[t](qr,op,scl,XB)
        return(ret,XB)
    else:
        print('Type ' + t + ' not supported by qrdsolr')
        return False
def qrsol(qr,op,XB):
    f={'qr_fmview_f':vsip_qrsol_f,
       'cqr_fcmview_f':vsip_cqrsol_f,
       'qr_dmview_d':vsip_qrsol_d,
       'cqr_dcmview_d':vsip_cqrsol_d}
    t=getType(qr)[1] + getType(XB)[1]
    if f.has_key(t):
        ret=f[t](qr,op,XB)
        return(ret,XB)
    else:
        print('Type ' + t + ' not supported by qrdsol')
        return False

# Singular Value Decomposition
def svd_create(t,M,N,Usave,Vsave):
    f={'sv_f':vsip_svd_create_f,
       'sv_d':vsip_svd_create_d}
    if f.has_key(t):
        return f[t](M,N,Usave,Vsave)
    else:
        print('Type ' + t + ' not supported by svd_create')
        return False
def svd_destroy(sv):
    f={'sv_f':vsip_svd_destroy_f,
       'sv_d':vsip_svd_destroy_d}
    t=getType(sv)
    if f.has_key(t):
        return f[t](sv)
    else:
        print('Type ' + t + ' not supported by svd_destroy')
        return False
def svd(sv,A,s):
    f={'sv_f':vsip_svd_f,
       'sv_d':vsip_svd_d}
    t=getType(sv)
    if f.has_key(t):
        ret= f[t](sv,A,s)
        return (ret,A,s)
    else:
        print('Type ' + t + ' not supported by svd')
        return False
def svdmatu(sv,low,high,C):
    f={'sv_f':vsip_svdmatu_f,
       'sv_d':vsip_svdmatu_d}
    t=getType(sv)
    if f.has_key(t):
        ret= f[t](sv,low,high,C)
        return (ret,C)
    else:
        print('Type ' + t + ' not supported by svdmatu')
        return False
def svdmatv(svd,low,high,C):
    f={'sv_f':vsip_svdmatv_f,
       'sv_d':vsip_svdmatv_d}
    t=getType(sv)
    if f.has_key(t):
        ret= f[t](sv,low,high,C)
        return (ret,C)
    else:
        print('Type ' + t + ' not supported by svdmatv')
        return False

