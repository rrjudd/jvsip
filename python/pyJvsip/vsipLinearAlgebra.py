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

# vsip_cvjdot_p
# vsip_dvdot_p
# jdot and dot are not supported as functions. Use the view method jdot and dot instead.

#vsip_cmherm_p
def herm(a,b):
    """
    Returns the N by M matrix C, which is the Hermitian (conjugate transpose)
    of an M by N matrix. If N==M (the matrix is square) then this may be done in-place.
    """
    f={'cmview_dcmview_d':vsip_cmherm_d, 'cmview_fcmview_f':vsip_cmherm_f}
    assert 'pyJvsip.__View' in repr(a) and 'pyJvsip.__View' in repr(b),\
       'Arguments one must by pyJvsip views for function herm'
    assert __isSizeCompatible(a,b), 'Arguments must be the same size for function herm'
    t=a.type+b.type
    assert f.has_key(t), 'Type <:'+t+':> not supported for function herm'
    f[t](a.view,b.view)
    return b

# vsip_dgemp_p
def gemp(alpha,a,op_a,b,op_b,beta,c):
    """
    General Matrix Product C = alpha * op_a(a).prod(op_b(b)) + beta * C
    See VSIP specification for additional information.
    This function is always in place into C.
    Usage:
       gemp(alpha, a, op_a, b, op_b, beta, c)
    Where:
        alpha is a scalar multiplier on view op_a(a)
        a is a matrix view of type (real or complex) float
        op_a is a matrix operation on view a
        b is a matrix view of the same type as a
        op_b is a matrix operation on view b
        beta is a scalar multiplier on view c
        c is a view of the same type as a (input/output) 
    op_a and op_b may be 'NTRANS', 'TRANS', 'HERM', or 'CONJ'
    if a and b are real then 'HERM' is the same as 'TRANS' and 'CONJ' is 
    the same as 'NTRANS'
    """
    opc={0:VSIP_MAT_NTRANS,1:VSIP_MAT_TRANS,2:VSIP_MAT_HERM,3:VSIP_MAT_CONJ,
         'NTRANS':VSIP_MAT_NTRANS,'TRANS':VSIP_MAT_TRANS,'HERM':VSIP_MAT_HERM,
         'CONJ':VSIP_MAT_CONJ} 
    opr={0:VSIP_MAT_NTRANS,1:VSIP_MAT_TRANS,2:VSIP_MAT_TRANS,3:VSIP_MAT_NTRANS,
         'NTRANS':VSIP_MAT_NTRANS,'TRANS':VSIP_MAT_TRANS,'HERM':VSIP_MAT_TRANS,
         'CONJ':VSIP_MAT_NTRANS}
    f={'cmview_d':vsip_cgemp_d,
       'cmview_f':vsip_cgemp_f,
       'mview_d':vsip_gemp_d,
       'mview_f':vsip_gemp_f}
    assert 'pyJvsip.__View' in repr(a) and 'pyJvsip.__View' in repr(b)\
       and 'pyJvsip.__View' in repr(c),\
       'Arguments 2, 4,and 7 must by pyJvsip views for function gemp'
    assert b.type == a.type and c.type == a.type,\
       'Arguments 2, 4 and 7 must be the same type'
    t = a.type
    assert f.has_key(t), 'Type <:'+t+':> not supported by function gemp'
    assert opc.has_key(op_a),'Matrix operation flag not recognized'
    assert opc.has_key(op_b),'Matrix operation flag not recognized'
    assert isinstance(alpha,float) or isinstance(alpha,int) or isinstance(alpha,complex),\
        'Argument one must be a scalar'
    assert isinstance(beta,float) or isinstance(beta,int) or isinstance(beta,complex),\
        'Argument six must be a scalar'
    if t=='cmview_d':
        f[t](vsip_cmplx_d(alpha.real,alpha.imag),a.view,opc[op_a],b.view,opc[op_b],\
             vsip_cmplx_d(beta.real,beta.imag),c.view)
        return c
    elif t == 'cmview_f':
        f[t](vsip_cmplx_f(alpha.real,alpha.imag),a.view,view,opc[op_a],b.view,opc[op_b],\
             vsip_cmplx_f(beta.real,beta.imag),c.view)
        return c
    else:
        assert isinstance(alpha,float) or isinstance(alpha,int), \
          'For type mview_f or mview_d the first argument must be a real scalar'
        assert isinstance(beta,float) or isinstance(beta,int), \
          'For type mview_f or mview_d the sixth argument must be a real scalar'
        f[t](float(alpha),a.view,opr[op_a],b.view,opr[op_b],float(beta),c.view)
        return c

# vsip_dgems_p
def gems(alpha,a,op_a,beta,c):
    """
    General matrix sum C = alpha * op_a(A) + beta * C
    This function is always in-place into C
    Usage:
        C = gems(alpha,A,op_a,beta,C)
    Where:
        alpha is a scalar multiplier
        A is a matrix
        op_a is a matrix operator on A
        beta is a scalar multiplier of view C
        C is a matrix of the same type as A (input/output)
    op_a may be 'NTRANS', 'TRANS', 'HERM', or 'CONJ'
    if a is real then 'HERM' is the same as 'TRANS' and 'CONJ' is the same as 'NTRANS'
    """
    opc={0:VSIP_MAT_NTRANS,1:VSIP_MAT_TRANS,2:VSIP_MAT_HERM,3:VSIP_MAT_CONJ,
         'NTRANS':VSIP_MAT_NTRANS,'TRANS':VSIP_MAT_TRANS,'HERM':VSIP_MAT_HERM,
         'CONJ':VSIP_MAT_CONJ} 
    opr={0:VSIP_MAT_NTRANS,1:VSIP_MAT_TRANS,2:VSIP_MAT_TRANS,3:VSIP_MAT_NTRANS,
         'NTRANS':VSIP_MAT_NTRANS,'TRANS':VSIP_MAT_TRANS,'HERM':VSIP_MAT_TRANS,
         'CONJ':VSIP_MAT_NTRANS}
    f={'cmview_d':vsip_cgems_d,'cmview_f':vsip_cgems_f,
       'mview_d':vsip_gems_d,'mview_f':vsip_gems_f}
    assert 'pyJvsip.__View' in repr(a) and 'pyJvsip.__View' in repr(c),\
        'Arguments 2, 5 must by pyJvsip views for function gems' 
    assert a.type==c.type, 'View arguments must be the same type for functions gems'
    t=a.type
    assert f.has_key(t), 'Type <:'+t+':> not supported for function gems'
    assert opc.has_key(op_a), 'Matrix operation flag not recognized'
    assert isinstance(alpha,float) or isinstance(alpha,int) or isinstance(alpha,complex),\
        'Argument one must be a scalar'
    assert isinstance(beta,float) or isinstance(beta,int) or isinstance(beta,complex),\
        'Argument four must be a scalar'
    if t == 'cmview_d':
        f[t](vsip_cmplx_d(alpha.real,alpha.imag),a.view,opc[op_a],\
             vsip_cmplx_d(beta.real,beta.imag),c.view)
        return c
    elif t == 'cmview_f':
        f[t](vsip_cmplx_f(alpha.real,alpha.imag),a.view,opc[op_a],\
             vsip_cmplx_f(beta.real,beta.imag),c.view)
        return c
    else:
        f[t](float(alpha),a.view,opc[op_a],float(beta),c.view)
        return c
    
# vsip_dskron_p
def kron(alpha,a,b,c):
    """
    See VSIP Spec for additional information
    
    """
    f={'cmview_dcmview_dcmview_d':vsip_cmkron_d, 'cmview_fcmview_fcmview_f':vsip_cmkron_f,
       'cvview_dcvview_dcmview_d':vsip_cvkron_d, 'cvview_fcvview_fcmview_f':vsip_cvkron_f,
       'mview_dmview_dmview_d':vsip_mkron_d, 'mview_fmview_fmview_f':vsip_mkron_f,
       'vview_dvview_dmview_d':vsip_vkron_d, 'vview_fvview_fmview_f':vsip_vkron_f}
    assert 'pyJvsip.__View' in repr(a) and 'pyJvsip.__View' in repr(b)\
       and 'pyJvsip.__View' in repr(c),\
       'Arguments 2, 3, and 4 must by pyJvsip views for function kron'
    assert isinstance(alpha,float) or isinstance(alpha,int) or isinstance(alpha,complex),\
        'Argument one must be a scalar'
    t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:'+t+':> not recognized for function kron'
    if 'vview' in a.type:
        N=a.length; M=b.length
    else:
        N = a.rowlength * b.rowlength; M = a.collength * b.collength
    assert c.rowlength == N and c.collength == M, 'Matrix C is not sized properly'
    if 'cmview_d' in t:
        f[t](vsip_cmplx_d(alpha.real,alpha.imag),a.view,b.view,c.view)
        return c
    elif 'cmview_f' in t:
        f[t](vsip_cmplx_f(alpha.real,alpha.imag),a.view,b.view,c.view)
        return c
    else:
        f[t](float(alpha),a.view,b.view,c.view)
        return c

# vsip_dmvprod3_p
# vsip_dmprod3_p
def prod3(a,b,c):
    """
    Matrix Product
    Not in-place
    prod3(a,b,c)
    Argument a is an input matrix view of size (3,3)
    Argument b is an input matrix view of size (3,N) or vector view of length 3
    Argument c is an output matrix view of size (3,N) or vector view of length 3
    """
    f={'cmview_dcmview_dcmview_d':vsip_cmprod3_d, 'cmview_fcmview_fcmview_f':vsip_cmprod3_f,
       'mview_dmview_dmview_d':vsip_mprod3_d, 'mview_fmview_fmview_f':vsip_mprod3_f,
       'cmview_dcvview_dcvview_d':vsip_cmvprod3_d,'cmview_fcvview_fcvview_f':vsip_cmvprod3_f,                                              
       'mview_dvview_dvview_d':vsip_mvprod3_d,'mview_fvview_fvview_f':vsip_mvprod3_f}
    assert 'pyJvsip.__View' in repr(a) and 'pyJvsip.__View' in repr(b)\
       and 'pyJvsip.__View' in repr(c),\
       'Arguments by pyJvsip views for function prod3'
    t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:'+t+':> not supported by prod3'
    assert a.rowlength == 3 and a.collength == 3,\
        'The first argument to prod3 must be size (3,3)'
    if 'vview' in t:
        assert b.length == 3 and c.length == 3, 'Size error in prod3'
    else:
        assert b.collength == 3, 'The second argument to prod3 must have column length of 3'
        assert c.collength == 3, 'The third argument to prod3 must have column length of 3'
        assert c.rowlength == b.rowlength, \
            'The size of the second argument and third argument must be the same for function prod3'
    f[t](a.view,b.view,c.view)
    return c

# vsip_dmvprod4_p
# vsip_dmprod4_p
def prod4(a,b,c):
    """
    Matrix Product
    Not in-place
    prod4(a,b,c)
    Argument a is an input matrix view of size (4,4)
    Argument b is an input matrix view of size (4,N) or vector view of length 4
    Argument c is an output matrix view of size (4,N) or vector view of length 4
    """
    f={'cmview_dcmview_dcmview_d':vsip_cmprod4_d, 'cmview_fcmview_fcmview_f':vsip_cmprod4_f,
       'mview_dmview_dmview_d':vsip_mprod4_d, 'mview_fmview_fmview_f':vsip_mprod4_f,
       'cmview_dcvview_dcvview_d':vsip_cmvprod4_d,'cmview_fcvview_fcvview_f':vsip_cmvprod4_f,                                              
       'mview_dvview_dvview_d':vsip_mvprod4_d,'mview_fvview_fvview_f':vsip_mvprod4_f}
    assert 'pyJvsip.__View' in repr(a) and 'pyJvsip.__View' in repr(b)\
       and 'pyJvsip.__View' in repr(c),\
       'Arguments by pyJvsip views for function prod4'
    t=a.type+b.type+c.type
    assert f.has_key(t), 'Type <:'+t+':> not supported by prod4'
    assert a.rowlength == 4 and a.collength == 4,\
        'The first argument to prod4 must be size (4,4)'
    if 'vview' in t:
        assert b.length == 4 and c.length == 4, 'Size error in prod4'
    else:
        assert b.collength == 4, 'The second argument to prod4 must have column length of 4'
        assert c.collength == 4, 'The third argument to prod4 must have column length of 4'
        assert c.rowlength == b.rowlength, \
            'The size of the second argument and third argument must be the same for function prod4'
    f[t](a.view,b.view,c.view)
    return c


# vsip_dmprod_p
# vsip_dmvprod_p
# vsip_dvmprod_p
def prod(a,b,c):
    """
    Standard matrix product. In-Place not supported.
    prod includes mprod and mvprod and vmprod.
    See specification pages in VSIP spec for more information.
    """
    f={'cmview_dcmview_dcmview_d':vsip_cmprod_d, 'cmview_fcmview_fcmview_f':vsip_cmprod_f,
       'cmview_dcvview_dcvview_d':vsip_cmvprod_d, 'cmview_fcvview_fcvview_f':vsip_cmvprod_f,
       'cvview_dcmview_dcvview_d':vsip_cvmprod_d, 'cvview_fcmview_fcvview_f':vsip_cvmprod_f,
       'mview_dmview_dmview_d':vsip_mprod_d, 'mview_fmview_fmview_f':vsip_mprod_f,
       'vview_dmview_dvview_d':vsip_vmprod_d, 'vview_fmview_fvview_f':vsip_vmprod_f,
       'mview_dvview_dvview_d':vsip_mvprod_d, 'mview_fvview_fvview_f':vsip_mvprod_f}
    assert  'pyJvsip.__View' in repr(a) and 'pyJvsip.__View' in repr(b) \
       and 'pyJvsip.__View' in repr(c), 'Arguments to prod must be pyJvsip views'
    t=a.type+b.type+c.type
    assert f.has_key(t),'Type <:'+t+':> not recognized by function prod'
    if 'mview' in a.type and 'mview' in b.type:
        assert b.collength == a.rowlength and c.collength == a.collength \
               and b.rowlength == c.rowlength, 'Size error in function prod'
        f[t](a.view,b.view,c.view)
        return c
    elif 'mview' in a.type and 'vview' in b.type:
        assert a.rowlength == b.length and a.collength == c.length, \
               'Size error in function prod'
        f[t](a.view,b.view,c.view)
        return c
    else: # a.type is vector and b.type is matrix
        assert a.length == b.collength and b.rowlength == c.length, \
               'Size error in function prod'
        f[t](a.view,b.view,c.view)
        return c

# vsip_dmtrans_p
def trans(a,b):
    """
    Function trans is a corner turn. In-place is not supported.
    """
    f={'cmview_dcmview_d':vsip_cmtrans_d,
       'cmview_fcmview_f':vsip_cmtrans_f,
       'mview_dmview_d':vsip_mtrans_d,
       'mview_fmview_f':vsip_mtrans_f}
    assert 'pyJvsip.__View' in repr(a) and 'pyJvsip.__View' in repr(b),\
            'Argmuments to function trans must be pyJvsip views'
    t=a.type+b.type
    assert f.has_key(t), 'Type <:'+t+':> not recognized for function trans'
    assert a.rowlength == b.collength and a.collength == b.rowlength, \
           'Size error in function trans'
    f[t](a.view,b.view)
    return b

# vsip_cmprodh_p
def prodh(a,b,c):
    assert 'pyJvsip.__View' in repr(a) and 'pyJvsip.__View' in repr(b)\
       and 'pyJvsip.__View' in repr(c),\
       'Arguments must by pyJvsip views for function prodh'
    assert a.type == b.type and a.type == c.type,'View types must agree for prodh'
    f={'cmview_d':vsip_cmprodh_d,'cmview_f':vsip_cmprodh_f}
    t=a.type
    assert f.has_key(t),'Type <:'+t+':> not recognized for function prodh'
    assert a.collength == c.collength and a.rowlength == b.rowlength \
       and b.collength == c.rowlength, 'Size error in prodh'
    f[t](a.view,b.view,c.view)
    return c

# vsip_cmprodj_p
def prodj(a,b,c):
    assert 'pyJvsip.__View' in repr(a) and 'pyJvsip.__View' in repr(b)\
       and 'pyJvsip.__View' in repr(c),\
       'Arguments must by pyJvsip views for function prodj'
    assert a.type == b.type and a.type == c.type,'View types must agree for prodt'
    f={'cmview_d':vsip_cmprodj_d, 'cmview_f':vsip_cmprodj_f}
    t=a.type
    assert f.has_key(t),'Type <:'+t+':> not recognized for function prodh'
    assert a.collength == c.collength and a.rowlength == b.collength \
       and b.rowlength == c.rowlength, 'Size error in prodj'
    f[t](a.view,b.view,c.view)
    return c               

# vsip_dmprodt_p
def prodt(a,b,c):
    assert 'pyJvsip.__View' in repr(a) and 'pyJvsip.__View' in repr(b)\
       and 'pyJvsip.__View' in repr(c),\
       'Arguments must by pyJvsip views for function prodt'
    assert a.type == b.type and a.type == c.type,'View types must agree for prodt'
    f={'cmview_d':vsip_cmprodt_d, 'cmview_f':vsip_cmprodt_f,                
       'mview_d':vsip_mprodt_d, 'mview_f':vsip_mprodt_f}           
    t=a.type
    assert f.has_key(t),'Type <:'+t+':> not recognized for function prodh'
    assert a.collength == c.collength and a.rowlength == b.rowlength \
       and b.collength == c.rowlength, 'Size error in prodt'
    f[t](a.view,b.view,c.view)
    return c               

# vsip_dvouter_p
def outer(alpha,a,b,c):
    """
    Outer Product. See VSIPL spec for more Information.
    Usage:
        outer(alpha,a,b,c)
    Where:
        alpha is a scalar multiplier. If a,b,c are real views then alpha may not be complex.
        a is a pyJvsip vector view
        b is a pyJvsip vector view
        c is a pyJvsip matrix view 
    """
    f={'cvview_dcvview_dcmview_d':vsip_cvouter_d,'cvview_fcvview_fcmview_f':vsip_cvouter_f,
       'vview_dvview_dmview_d':vsip_vouter_d,'vview_fvview_fmview_f':vsip_vouter_f}
    assert isinstance(alpha,float) or isinstance(alpha,int) or isinstance(alpha,complex),\
        'Argument one must be a scalar'
    assert 'pyJvsip.__View' in repr(a) and 'pyJvsip.__View' in repr(b)\
       and 'pyJvsip.__View' in repr(c),\
       'Arguments 2,3 & 4 must be pyJvsip views for function outer'
    t=a.type+b.type+c.type
    assert f.has_key(t)
    assert c.collength == a.length and c.rowlength == b.length, 'Size error in function outer'
    if 'cvview_d' in t:
        f[t](vsip_cmplx_d(alpha.real,alpha.imag),a.view,b.view,c.view)
    elif 'cvview_f' in t:
        f[t](vsip_cmplx_f(alpha.real,alpha.imag),a.view,b.view,c.view)
    else:
        assert not isinstance(alpha,complex), \
            'For real views the scalar multiplier must be real for function outer'
        f[t](float(alpha),a.view,b.view,c.view)
    return c

# vsip_dcovsol_p
def covsol(A,XB):
    """
    See VSIPL spec for more information
    Usage:
        x=covsol(A,XB)
    Where:
        x = 0 on success
        A is a matrix view. A is overwritten by the calculation.
        XB is a the input/output view.
    """
    f={'cmview_d':vsip_ccovsol_d, 'cmview_f':vsip_ccovsol_f,
       'mview_d':vsip_covsol_d, 'mview_f':vsip_covsol_f}
    assert 'pyJvsip.__View' in repr(A) and 'pyJvsip.__View' in repr(XB),\
       'Arguments must by pyJvsip views for function covsol'
    t=A.type
    assert f.has_key(t), 'Type <:'+t+':> not recognized for function covsol'
    if 'mview' in XB.type:
        C = XB
    else:
        C=XB.block.bind(inOut.offset,inOut.stride,inOut.length,1,1)
    assert t == C.type, 'Arguments in function covsol must be the same type'
    assert A.rowlength == C.collength, 'Size error in function covsol'
    x=f[t](A.view,C.view)
    return x

# vsip_dllsqsol_p 
def llsqsol(A,XB):
    """
    See VSIPL spec for more information
    Usage:
        x=llsqsol(A,XB)
    Where:
        x = 0 on success
        A is a matrix view. A is overwritten by the calculation.
        XB is a the input/output view.
    """
    f={'cmview_d':vsip_cllsqsol_d, 'cmview_f':vsip_cllsqsol_f,
       'mview_d':vsip_llsqsol_d, 'mview_f':vsip_llsqsol_f}
    assert 'pyJvsip.__View' in repr(A) and 'pyJvsip.__View' in repr(XB),\
       'Arguments must by pyJvsip views for function llsqsol'
    t=A.type
    assert f.has_key(t), 'Type <:'+t+':> not recognized for function llsqsol'
    if 'mview' in XB.type:
        C = XB
    else:
        C=XB.block.bind(inOut.offset,inOut.stride,inOut.length,1,1)
    assert t == C.type, 'Arguments in function llsqsol must be the same type'
    assert A.rowlength == C.collength, 'Size error in function llsqsol'
    x=f[t](A.view,C.view)
    return x

# vsip_dtoepsol_p
def toepsol(t,b,w,x):
    """
    See VSIPL spec for more information
    Usage:
        x=toepsol(t,b,w,x)
    Where:
        x == 0 on success
        t View of input vector, t, of length N, the first row of the Toeplitz matrix.
        b View of input vector, b, of length N.
        w View of vector, w, of length N used for temporary workspace.
        x View of output vector, x, of length N.
    """
    f={'cvview_d':vsip_ctoepsol_d,'cvview_f':vsip_ctoepsol_f,
       'vview_d':vsip_toepsol_d,'vview_f':vsip_toepsol_f}
    assert 'pyJvsip.__View' in repr(t) and 'pyJvsip.__View' in repr(b) \
        and'pyJvsip.__View' in repr(w) and 'pyJvsip.__View' in repr(x),\
        'Arguments must be pyJvsip views'
    tp=t.type
    assert f.has_key(tp), 'Type <:'+tp+':> not recognized by toepsol'
    assert tp == b.type and tp == w.type and tp == x.type,\
         'Arguments to toepsol must all be vector views of the same type'
    assert t.length == b.length and t.length == w.length and t.length == x.length, \
         'View lengths must all be the same size for function topsol'
    x=f[tp](t.view,b.view,w.view,x.view)
    return x





