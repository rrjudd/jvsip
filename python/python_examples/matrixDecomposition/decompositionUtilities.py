import pyJvsip as pv
def eye(t,n): # create and return an identity matrix of size n and type t
    return pv.create(t,n,n).identity
def sign(a_in): # see  LAPACK Working Notes 148 for definition of sign
    """
    Function sign(alpha) returns the sign of scalar (real or complex) alpha.
    """
    if type(a_in) is int:
        a=float(a_in)
    else:
        a=a_in
    if type(a) is float or type(a) is complex:
        t=pv.vsip_hypot_d(a.real,a.imag)
        if t == 0.0:
            return 1.0
        elif a.imag==0.0:
            if a.real < 0.0:
                return -1.0
            else:
                return 1.0
        else:
            return a/t
    else:
        print('sign function only works on scalars')
        return
def houseVector(x): 
    """
     This algorithm returns a normalized householder vector 'v' such that
     the householder projection matrix 'H' is:
     H = I - 2 v v*
    """
    if 'vview' not in x.type:
        print('Function houseVector only works on vector views')
        return
    v=x.copy
    v[0] += (sign(x[0]) * x.norm2)
    n = v.norm2
    if n == 0.0:
        v[0] = 1.0
    else:
        v /= n
    return v
def house(v): # create and return househoulder rotation matrix for householder
              # vector v; works for any valid househoulder vector
    """
    Usage:
        H=house(v)
    Create and return a householder projector matrix given input householder vector v.
    """
    t={'vview_f':'mview_f','vview_d':'mview_d','cvview_f':'cmview_f','cvview_d':'cmview_d'}
    return(eye(t[v.type],v.length) - v.outer(2.0/v.jdot(v),v))
def houseProd(v,A):
    """
    Usage:
        houseProd(v,A)
        using a householder vector V with a matrix of the proper size return HA
        Note A is modified in-place; but there are create/destroy penalties with this function
        Note a convenience reference to A is returned
    """
    beta = 2.0/v.jdot(v)
    v.conj;w=v.prod(A).conj;v.conj
    A -= v.outer(beta,w)
    return A
def prodHouse(A,v):
    """
    Usage:
        prodHouse(A,v)
        using a householder vector V with a matrix of the proper size return AH
        Note A is modified in-place; but there are create/destroy penalties with this function
        Note a convenience reference to A is returned
    """

    beta = 2.0/v.jdot(v)
    w=A.prod(v)
    A-=w.outer(beta,v)
    return A
#Givens
def givensCoef(x1_in,x2_in):
    """ Code adapted from Algorithm 1 of LAPACK working Notes lawn148
    """
    if type(x1_in) is int:
        x1=float(x1_in)
    else:
        x1 = x1_in
    if type(x2_in) is int:
        x2=float(x2_in)
    else:
        x2 = x2_in
    if type(x1) is float and type(x2) is float:
        t=pv.vsip_hypot_d(x1,x2)
        if x2 == 0.0:
            return (1.0,0.0,x1)
        elif x1 == 0.0:
            return (0.0,sign(x2),t)
        else: # return (c,s,r)
            sn=sign(x1)
            return(pv.vsip_mag_d(x1)/t,sn*x2/t,sn*t)
    elif type(x1) is complex or type(x2) is complex:
        mx1=pv.vsip_hypot_d(x1.real,x1.imag)
        mx2=pv.vsip_hypot_d(x2.real,x2.imag)
        if mx2 == 0.0:
            return(1.0,0.0,x1)
        elif mx1 == 0.0:
            return(0,sign(x2.conjugate()),mx2)
        else:
            t=pv.vsip_hypot_d(mx1,mx2)
            c=mx1/t
            sn=sign(x1)
            s=(sn * x2.conjugate())/t
            r=sn * t
            return(c,s,r)
    else:
        print('Type <:'+repr(type(x1)) + ':> or <:'+ \
             repr(type(x2))+':> not recognized by givensCoef')
        return
def givens(t,i,j,c,s,size):
    """
       Return an extended givens matrix.
       An extended givens matrix is an identity matrix of size 'size'
       with elements at (i,i) and (j,j) replaced with c,
       the element at (i,j) replaced with s,
       and the element at (j,i) replaced with -conjugate(s)
       Usage:
         G=givens(t,i,j,c,s,size)
       Where:
         t = type 
         i,j are index values for placement of 
         c,s which are obtained (probably) from function givensCoef. 
         size is an integer
    """
    G=eye(t,size)
    G[i,i]=c;G[j,j]=c;G[i,j]=s;G[j,i]=-s.conjugate()
    return G
def gProd(i,j,c,s,A):
    """
    Done in-place (A is modified)
    Usage:
        gProd(i,j,c,s,A)
    where:
        A is a matrix of size (m,n)
        i,j,c,s are equivalent to a givens matrix G = givens(A.type,i,j,c,s,m)
    does:
        A = G A
    returns:
        reference to A as a convenience
    """
    a1=A.rowview(i).copy
    a2=A.rowview(j).copy
    A.rowview(i)[:]= c * a1 + s * a2 
    A.rowview(j)[:]= c * a2 - s.conjugate() * a1
    return A
def prodG(A,i,j,c,s):
    """
    Done in-place (A is modified)
    Usage:
        prodG(A,i,j,c,s)
    where:
        A is a matrix of size (m,n)
        i,j,c,s are equivalent to a givens matrix GH = givens(A.type,i,j,c,s,m).herm
    does:
        A = A GH
    returns:
        reference to A as a convenience
    """
    a_i=A.colview(i).copy
    a_j=A.colview(j).copy
    A.colview(i)[:]= c * a_i + s.conjugate() * a_j 
    A.colview(j)[:]= c * a_j - s * a_i
    return A
def gtProd(i,j,c,s,A):
    """
    Done in-place (A is modified)
    Usage:
        gtProd(i,j,c,s,A)
    where:
        A is a matrix of size (m,n)
        i,j,c,s are equivalent to a givens matrix G_TH = givens(A.type,i,j,c,s,m).transview.herm
    does:
        A = G_TH A
    returns:
        reference to A as a convenience
    """
    a_i=A.rowview(i).copy
    a_j=A.rowview(j).copy
    A.rowview(i)[:]= c * a_i + s.conjugate() * a_j 
    A.rowview(j)[:]= c * a_j - s * a_i
    return A
def prodGT(A,i,j,c,s):
    """
    Done in-place (A is modified)
    Usage:
        prodG(A,i,j,c,s)
    where:
        A is a matrix of size (m,n)
        i,j,c,s are equivalent to a givens matrix G_T = givens(A.type,i,j,c,s,m).transview
    does:
        A = A G_T
    returns:
        reference to A as a convenience
    """

    a1 = A.colview(i).copy
    a2 = A.colview(j).copy
    A.colview(i)[:] = c * a1 + s * a2
    A.colview(j)[:] = c * a2 -s.conjugate() * a1
    return A

# householder routines
def QRD_inPlace(A):
    """
    The function QRD_inPlace(A) is done in-place on matrix A. If you want to retain A make a copy first.
    Usage:
        QRD_inPlace(A)
    Note that the decomposition represented is A=QR.
    Matrix R is stored in the upper triangular portion of A.
    Householder vectors are stored in the lower sub-triangular portion of A.
    Householder vectors are normalized so that v[0] is 1.0;
    """
    m=A.collength
    n=A.rowlength
    if m < n:
        print('The input matrix must have collength >= rowlength.')
        print('For matrices where rowlength > collength work with the transpose.')
    for i in range(n-1):
        x=A[i:,i:].colview(0)
        v=houseVector(x)
        v /= v[0]
        A[i:,i:]=house(v).prod(A[i:,i:])
        x[1:]=v[1:]
    if m > n: #do last column if matrix not square
        i=n-1
        x=A[i:,i:].colview(0)
        v=houseVector(x)
        v /= v[0]
        A[i:,i:]=house(v).prod(A[i:,i:])
        x[1:]=v[1:]
def fullQProd(Q,B):
    """
    Usage:
       U=fullQProd(Q,B)
       where Q is a matrix of size M,N where M >= N which was produced by QRD_inPlace(Q)
       B is a matrix of size M,P
       U is the matrix produced by the matrix product Q B where Q is the full Q matrix from a QR decomposition.
    """
    m=Q.collength
    n=B.rowlength
    U=B.copy
    if m > n: #extract last column if matrix is not square
        i=n-1
        v=Q[i:,i:].colview(0).copy
        v[0]=1
        houseProd(v,U[i:,i:])
    for i in range(n-2,-1,-1):
        v=Q[i:,i:].colview(0).copy
        v[0]=1
        houseProd(v,U[i:,i:])
    return U
def QmatExtract(B):
    """ 
    If B is a matrix which has been operated on by QRD_inPlace then
    QmatExtract(B) will return the full Q matrix of the QR decomposition.
    """
    m=B.collength
    n=B.rowlength
    Q=eye(B.type,m)
    if m > n: #extract last column if matrix is not square
        i=n-1
        v=B[i:,i:].colview(0).copy
        v[0]=1
        houseProd(v,Q[i:,i:])
    for i in range(n-2,-1,-1):
        v=B[i:,i:].colview(0).copy
        v[0]=1
        houseProd(v,Q[i:,i:])
    return Q
def RmatExtract(B):
    """
    If B is a matrix which has been operated on by QRD_inPlace then
    RmatExtract(B) returns a new matrix with the (full) R from the QR decomposition.
    """
    R=B.copy
    m=B.collength
    for i in range(1,m):
        R.diagview(-i).fill(0.0)
    return R
def houseQR(A):
    """
       Done out of place
       Usage:
          Q,R=houseQR(A)
       where:
          A is of size M, N; M >= N; A = Q R 
          Q is unitary
          R is upper triangular
    """
    R=A.copy
    m=A.collength
    n=A.rowlength
    if m < n:
        print('The input matrix must have collength >= rowlength.')
        print('for matrices where rowlength > collength work with the transpose')
    for i in range(n-1):
        x=R[i:,i:].colview(0)
        v=houseVector(x)
        v /= v[0]
        houseProd(v,R[i:,i:])
        x[1:]=v[1:]
    if m > n: #do last column if matrix not square
        i=n-1
        x=R[i:,i:].colview(0)
        v=houseVector(x)
        v /= v[0]
        houseProd(v,R[i:,i:])
        x[1:]=v[1:]
    #accumulate Q
    Q = QmatExtract(R)
    #zero entries of R
    for i in range(1,m):
        R.diagview(-i).fill(0.0)
    return (Q,R)
def bidiag(A): # m >= n
    """
      B=bidiag(A)
        returns, out of place, the bidiagonal decomposition of A.
        The esential househoulder vectors are stored in the zeroed entries of B.
    """
    B=A.copy
    m=B.collength
    n=B.rowlength
    if m < n:
        print('The input matrix must have collength >= rowlength.')
        print('for matrices where rowlength > collength work with the transpose')
    for i in range(n-1):
        x=B[i:,i:].colview(0)
        v=houseVector(x)
        v /= v[0]
        houseProd(v,B[i:,i:])
        x[1:]=v[1:]
        if i < n-2:
            j=i+1
            x = B[i:,j:].rowview(0)
            #v=houseVector(x.conj);x.conj 
            v=houseVector(x).conj 
            v /= v[0]
            prodHouse(B[i:,j:],v)#=B[i:,j:].prod(house(v))
            x[1:]=v[1:]
    if m > n: #do last column if matrix not square
        i=n-1
        x=B[i:,i:].colview(0)
        v=houseVector(x)
        v /= v[0]
        houseProd(v,B[i:,i:])
        x[1:]=v[1:]
    return B
def bidiagExtract(B):
    """
      B=bidiagExtract(B0)
        Returns, out of place, a matrix with the bidiagonal entries. 
        Input matrix is one produced by B0=bidiag(A)
    """
    B0=B.empty.fill(0.0)
    B0.diagview(0)[:] = B.diagview(0)
    B0.diagview(1)[:] = B.diagview(1)
    return B0
def UmatExtract(B):
    """
      U=UmatExtract(B0)
        returns, out of place, the U matrix of the bidiagonal 
        decomposition A=UBV^H given the result of bidiag routine 
        B0=bidiag(A)
    """
    m=B.collength
    n=B.rowlength
    U=eye(B.type,m)
    if m > n: #extract last column if matrix is not square
        i=n-1
        v=B[i:,i:].colview(0).copy
        v[0]=1
        houseProd(v,U[i:,i:])
    for i in range(n-2,-1,-1):
        v=B[i:,i:].colview(0).copy
        v[0]=1
        houseProd(v,U[i:,i:])
    return U
def VHmatExtract(B):
    """
      VH=UmatExtract(B0)
        returns, out of place, the hermtian V matrix of the bidiagonal 
        decomposition A=UBV^H given the result of bidiag routine 
        B0=bidiag(A)
    """
    m=B.collength
    n=B.rowlength
    V=eye(B.type,n)
    for i in range(n-3,-1,-1):
        j=i+1
        v=B[i:,j:].rowview(0).copy
        v[0]=1
        prodHouse(V[j:,j:],v)#=V[j:,j:].prod(house(v))
    return V
def givensCoef(x1_in,x2_in):
    """ Code adapted from Algorithm 1 of LAPACK working Notes lawn148
    """
    if type(x1_in) is int:
        x1=float(x1_in)
    else:
        x1 = x1_in
    if type(x2_in) is int:
        x2=float(x2_in)
    else:
        x2 = x2_in
    if type(x1) is float and type(x2) is float:
        t=pv.vsip_hypot_d(x1,x2)
        if x2 == 0.0:
            return (1.0,0.0,x1)
        elif x1 == 0.0:
            return (0.0,sign(x2),t)
        else: # return (c,s,r)
            sn=sign(x1)
            return(pv.vsip_mag_d(x1)/t,sn*x2/t,sn*t)
    elif type(x1) is complex or type(x2) is complex:
        mx1=pv.vsip_hypot_d(x1.real,x1.imag)
        mx2=pv.vsip_hypot_d(x2.real,x2.imag)
        if mx2 == 0.0:
            return(1.0,0.0,x1)
        elif mx1 == 0.0:
            return(0,sign(x2.conjugate()),mx2)
        else:
            t=pv.vsip_hypot_d(mx1,mx2)
            c=mx1/t
            sn=sign(x1)
            s=(sn * x2.conjugate())/t
            r=sn * t
            return(c,s,r)
    else:
        print('Type <:'+repr(type(x1)) + ':> or <:'+ \
             repr(type(x2))+':> not recognized by givensCoef')
        return
def givensExtract(t,i,j,c,s,size):
    """
       Usage:
         G=givensExtract(t,i,j,c,s,size)
         t = type 
         i,j are index values for placement of 
         c,s which are obtained (probably) from function givensCoef. 
         size is an integer
    """
    G=eye(t,size)
    G[i,i]=c;G[j,j]=c;G[i,j]=s;G[j,i]=-s.conjugate()
    return G
def gProd(i,j,c,s,A):
    a1=A.rowview(i).copy
    a2=A.rowview(j).copy
    A.rowview(i)[:]= c * a1 + s * a2 
    A.rowview(j)[:]= c * a2 - s.conjugate() * a1
    return A
def prodG(A,i,j,c,s):
    a_i=A.colview(i).copy
    a_j=A.colview(j).copy
    A.colview(i)[:]= c * a_i + s.conjugate() * a_j 
    A.colview(j)[:]= c * a_j - s * a_i
    return A
def gtProd(i,j,c,s,A):
    a_i=A.rowview(i).copy
    a_j=A.rowview(j).copy
    A.rowview(i)[:]= c * a_i + s.conjugate() * a_j 
    A.rowview(j)[:]= c * a_j - s * a_i
    return A
def prodGT(A,i,j,c,s):
    a1 = A.colview(i).copy
    a2 = A.colview(j).copy
    A.colview(i)[:] = c * a1 + s * a2
    A.colview(j)[:] = c * a2 -s.conjugate() * a1
    return A
def givensQR(A):
    M = A.collength
    N = A.rowlength
    R = A.copy
    Q = eye(A.type,M)
    for i in range(N):
        B=R[i:,i:]
        r=B[0,0]
        for j in range(1,B.collength):
            c,s,r=givensCoef(r,B[j,0])
            prodG(Q,i,j+i,c,s)
            gProd(0,j,c,s,B)
    return (Q,R)
def givensBidiag(A):
    M  = A.collength
    N  = A.rowlength
    B  = A.copy
    U  = eye(A.type,M)
    VH = eye(A.type,N)
    for i in range(N-1):
        TC=B[i:,i:]
        if i < N-2:
            TR=B[i:,i+1:]
        r=TC[0,0]
        for j in range(1,TC.collength):
            c,s,r=givensCoef(r,TC[j,0])
            prodG(U,i,j+i,c,s)
            gProd(0,j,c,s,TC)
        if i < N-2:
            r=TR[0,0]
            k=i+1
            for j in range(1,TR.rowlength):
                c,s,r=givensCoef(r,TR[0,j])
                gtProd(k,j+k,c,s,VH)
                prodGT(TR,0,j,c,s)
    if M > N:
        i=N-1
        TC=B[i:,i:]
        r=TC[0,0]
        for j in range(1,TC.collength):
            c,s,r=givensCoef(r,TC[j,0])
            prodG(U,i,j+i,c,s)
            gProd(0,j,c,s,TC)
    return (U,B,VH)
def grs_zero_checkAndSet(e,b0,b1):
    s=e * (b0[0:b1.length].mag + b0[1:].mag)
    indx_bool = b1.mag.llt(s)
    if indx_bool.anytrue:
        b1.indxFill(indx_bool.indexbool,0.0)
def grs_corners(b1):
    """
       Functionality
           i,j = grs_corners(v)
       where 
           v is a real vector of type float or double
           i,j are indices into the vector
       result of 
           v[i,j] will be vector with no zero elements
           v[j:] will be a vector with all zero elements
       Note:
          to use with complex v use
          i,j=grs_corners(v.mag)
       
    """
    v_bool=b1.leq(0.0)
    j=v_bool.length-1
    while j >= 0 and v_bool[j] == 1:
        j -= 1
    if j == -1:
        return(0,0)
    i=j  #index of non-zero
    j+=1 #index of zero
    while i >= 0 and v_bool[i] == 0:
        i -= 1
    return(i+1,j+1)
def grs_zeroChase(L,B,R):
    b=B.diagview(0)
    bm=B.diagview(-1)
    bp=B.diagview(1) 
    for i in range(0,bp.length):
        c,s,r=givensCoef(b[i],bp[i])
        b[i] = r
        bp[i]=0
        bm[i]=s*b[i+1]
        b[i+1]*=c
        gtProd(i,i+1,c,s,R)
    for i in range(0,bm.length-1):
        c,s,r=givensCoef(b[i],bm[i])
        b[i]=r
        bm[i]=0
        bp[i] = b[i+1] * s
        b[i+1] *= c
        prodG(L,i,i+1,c,s)