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
        prodHouse(V[j:,j:],v)
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
def svdZeroCheckAndSet(e,b0,b1):
    """ 
     Usage:
        svdZeroCheckAndSet(eps,d,f)
     Where:
        eps0 is a small number we consider to be (close to) zero
        d is a vector view representing the main diagonal of an upper bidiagonal matrix
        f is a vector view representing the superdiagonal in an upper bidiagonal matrix.
      In the svd algorithm this checks the superdiagonal for small numbers which 
      may be set to zero. If found, set to zero.
    """
    s=e * (b0[0:b1.length].mag + b0[1:].mag)
    indx_bool = b1.mag.llt(s)
    if indx_bool.anytrue: #check super diagonal
        b1.indxFill(indx_bool.indexbool,0.0)
def svdCorners(b1):
    """
       Functionality
           i,j = svdCorners(v)
       where 
           v is a real vector of type float or double
           i,j are indices. 
       i,j; as returned 
           v[i:j-1] will be vector with no zero elements
           v[j-1:] will be a vector with all zero elements
       Note v is the first super-diagonal of a bidiagonal matrix.
       The corresponding main diagonal, d, will be d[i:j]
    """
    v_bool=b1.leq(0.0)
    j=v_bool.length-1
    while j >= 0 and v_bool[j] == 1:
        j -= 1
    if j == -1:
        return(0,0) #all of b1 is zero
    i=j  #index of non-zero
    j+=1 #index of zero
    while i >= 0 and v_bool[i] == 0:
        i -= 1
    return(i+1,j+1)
def diagPhaseToZero(L,B):
    """ 
       To phase shift the main diagonal entries of a matrix B so entries 
       are real (imaginary zero) use this routine.
    """
    d = B.diagview(0)
    for i in range(d.length):
        ps=d[i] #phase shift
        if ps.imag != 0.0: #ignore if already real
            m = pv.vsip_hypot_d(ps.real,ps.imag)
            ps /= m
            L.colview(i)[:] *= ps
            B.rowview(i)[:] *= ps # if B is strictly diagonal don't need this step
            d[i] = m 
def biDiagPhaseToZero(L,d,f,R,eps0):
    """ 
    For a Bidiagonal matrix B This routine uses subview vectors
      `d=B.diagview(0)`
    and 
      `f=B.diagview(1)`
    and phase shifts vectors d and f so that B has zero complex part.
    Matrices L and R are update matrices.
    eps0 is a small real number used to check for zero. If an element meets a zero
    check then that element is set to zero.
    """
    for i in range(d.length):
        ps=d[i]
        if ps.imag == 0.0:
            m = ps.real
            if m < 0.0:
                ps=-1.0
            else:
                ps= 1.0
            m = abs(m) 
        else:
            m=pv.vsip_hypot_d(ps.real,ps.imag)
            ps /= m
        if m > eps0:
            L.colview(i)[:] *= ps
            d[i] = m
            if i < f.length:
                f[i] *= ps.conjugate()
        else:
            d[i] = 0.0
    svdZeroCheckAndSet(eps0,d,f)          
    for i in range(f.length-1):
        j=i+1
        ps = f[i]
        if ps.imag == 0.0:
            m = ps.real
            if m < 0.0:
                ps=-1.0
            else:
                ps= 1.0
            m = abs(m) 
        else:
            m=pv.vsip_hypot_d(ps.real,ps.imag)
            ps /= m
        L.colview(j)[:] *= ps.conjugate()
        R.rowview(j)[:] *= ps
        f[i] = m;
        f[j] *= ps
    j=f.length
    i=j-1
    ps=f[i]
    if ps.imag == 0.0:
        m = ps.real
        if m < 0.0:
            ps=-1.0
        else:
            ps= 1.0
        m = abs(m) 
    else:
        m=pv.vsip_hypot_d(ps.real,ps.imag)
        ps /= m
    f[i]=m
    L.colview(j)[:] *= ps.conjugate()
    R.rowview(j)[:] *= ps
def zeroRow(L,d,f):
    """
    To use this we assume a matrix B that is bi-diagonalized.
        Note i,j = svdCorners(B) => i, j=n+1

    Let d0 be B.diagview(0); f0 be B.diagview(1)
    d is a subview of the main diagonal
    f is a subview of the first superdiagonal (diagonal(1)) and has no zeros.
    if f = f0[i:n] then d = d0[i:n+1]

    L is a subview of the left update matrix we call L0 here.
    for the indices shown above
    L = L0[:,i:n+1]
    
    If d contains a zero entry, and the zero entry is not at the end of d,
    then zeroRow is used to zero out the corresponding superdiagonal entry
    in the row. Vector d may contain more than one zero. We zero out the zero 
    with the largest index (we designate k). So d[k] = d0[i+k] is the zero 
    of interest. 
        Note if d[k] is the last entry then the corresponding superdiagonal entry
        in the row is already zero. Use zeroCol to zero out the column.

    Usage:
        zeroRow(L[:,k:],d[k+1:],f[k:])
    """
    if 'cvview' in d.type or 'cvview' in f.type:
        print('zeroRow only works for real vectors')
        return
    if d.length == 1:
        c,s,r=givensCoef(d[0],f[0])
        f[0]=0.0;d[0]=r
    else:
        c,s,r=givensCoef(d[0],f[0])
        f[0]=0;d[0]=r
        t= - f[1] * s; f[1] *= c
        prodG(L,1,0,c,s)
        for i in range(1,d.length-1):
            c,s,r=givensCoef(d[i],t)
            prodG(L,i+1,0,c,s)
            d[i]=r; t=-f[i+1] * s; f[i+1] *= c
        c,s,r=givensCoef(d[d.length-1],t)
        d[d.length-1] = r
        prodG(L,d.length,0,c,s)
def zeroCol(d,f,R):
    """
    To use this we assume a matrix B that is bi-diagonalized.
        Note i,j = svdCorners(B) => i, j=n+1

    Let d0 be B.diagview(0); f0 be B.diagview(1)
    d is a subview of the main diagonal
    f is a subview of the first superdiagonal (diagonal(1)) and has no zeros.
    if f = f0[i:n] then d = d0[i:n+1]

    R is a subview of the right update matrix we call R0 here.
    for the indices shown above
    R = R0[i:n+1,:]

    We assume matrix B has all zeros on row n.
    Usage:
        zeroCol(d,f,R)
    """
    if 'cvview' in d.type or 'cvview' in f.type:
        print('zeroCol only works for real vectors')
        return
    if f.length == 1:
        c,s,r=givensCoef(d[0],f[0])
        d[0]=r; f[0]=0.0
        gtProd(0,1,c,s,R)
    elif f.length == 2:
        c,s,r=givensCoef(d[1],f[1])
        d[1]=r; f[1]=0;
        t= - f[0] * s; f[0] *= c
        gtProd(1,2,c,s,R)
        c,s,r=givensCoef(d[0],t)
        d[0]=r;
        gtProd(0,2,c,s,R)
    else:
        i=f.length-1; j=i-1; k=i
        c,s,r=givensCoef(d[i],f[i])
        f[i]=0; d[i]=r; t=-f[j]*s; f[j]*=c;
        gtProd(i,k+1,c,s,R)
        while i > 1:
            i = j; j = i-1
            c,s,r=givensCoef(d[i],t)
            d[i]=r; t= - f[j] * s; f[j] *= c
            gtProd(i,k+1,c,s,R)
        c,s,r=givensCoef(d[0],t)
        d[0] = r
        gtProd(0,k+1,c,s,R)
def svdMu(d2,f1,d3,f2):
    """
    For this algorithm we expect float or double, real numbers
    """
    cu=d2 * d2 + f1 * f1
    cl=d3 * d3 + f2 * f2
    cd = d2 * f2
    D = (cu * cl - cd * cd)
    T = (cu + cl)
    root = pv.vsip_sqrt_d(T*T - 4 * D)
    lambda1 = (T + root)/(2.); lambda2 = (T - root)/(2.)
    if abs(lambda1 - cl) < abs(lambda2 - cl):
        mu = lambda1
    else:
        mu = lambda2
    return mu 
def svdStep(L,d,f,R):
    if 'cvview' in d.type or 'cvview' in f.type:
        print('Input vector views must be of type real; Fail for svdStep')
        return     
    n=d.length
    #initial step
    if n >= 3:
        mu = svdMu(d[n-2],f[n-3],d[n-1],f[n-2])
    elif n == 2:
        mu = svdMu(d[n-2],0.0,d[n-1],f[n-2])
    else:
        mu = svdMu(d[0],0.0,0.0,0.0)
    x1=d[0]; x1 *= x1; x1 -= mu
    x2 = d[0] * f[0]
    c,s,r=givensCoef(x1,x2)
    t=d[0] * c + s * f[0]; f[0] *= c; f[0] -= s * d[0]; d[0] = t;
    t=s * d[1]; d[1] *= c;
    gtProd(0,1,c,s,R)
    for i in range(n-2):
        j=i+1; k=i+2
        #step
        c,s,r = givensCoef(d[i],t)
        d[i]=r;
        t=c * d[j] - s * f[i]; f[i] *=c ;f[i]+=s*d[j];d[j]=t
        t=s * f[j]; f[j] *= c;
        prodG(L,i,j,c,s)
        #step
        c,s,r=givensCoef(f[i],t)
        f[i]=r
        t=c * d[j] + s * f[j]; f[j] *= c; f[j] -= s * d[j]; d[j] = t
        t=s * d[k]; d[k] *= c;
        gtProd(j,k,c,s,R)
    #final step
    i=n-2; j=n-1
    c,s,r = givensCoef(d[i],t)
    d[i]=r; 
    t= c * d[j] - s * f[i];
    f[i] *= c; f[i] += s * d[j]; 
    d[j]=t
    prodG(L,i,j,c,s)
def zeroFind(d,eps0):
    """
       zeroFind(d) takes vector d and finds the zero element with the 
       largest index and returns the index. If an element is less than
       eps0 the element is considered to be zero and is set to 0.0.
       If no index is found returns -1
    """
    j=d.length - 1
    while d[j] > eps0 and j > 0:
        j -= 1
    if j == 0 and d[j] > eps0:
        return -1
    else:
        d[j]=0.0
        return j
def svd(A):
    """
       The bidiag routine is used in the svd and bidiag is defined out of place, 
       so svd is also out of place. The bidiag routine can be done in-place with
       a simple change, so the svd can also be done in-place.
       Usage:
           U,S,VH = svd(A)
           A is a matrix with column length >= row length
           where U is a unitary matrix of size A.columnlength
           S is a real vector of size A.rowlength containing the singular values of A 
              Note: S is considered here to be a diagonal matrix
           VH is a unitary matrix of size A.rowlength
       Note:
           A = U S VH = U.prod(S.mmul(VH.ROW)) 
    """
    def svdBidiagonal(A):
        if 'mview_f' not in A.type and 'mview_d' not in A.type:
            print('Input must be a matrix of type float for function svd.')
            return
        if A.rowlength > A.collength:
            print('For svd function input matrix A of size (M,N) must have N >= M')
            return(0,0,0,0,0)
        if 'mview_d' in A.type:
            eps0 = A.normFro/A.rowlength * 1.0E16
        else:
            eps0 = A.normFro/A.rowlength * 1.0E7
        if eps0 == 0.0:
            print('Input matrix appears to be zero')
            return(0,0,0,0,0)
        else:
            eps0 = 1.0/eps0
        B=bidiag(A)
        L=UmatExtract(B)
        R=VHmatExtract(B)
        biDiagPhaseToZero(L,B.diagview(0),B.diagview(1),R,eps0)
        if 'cmview' in B.type:
            d0=B.diagview(0).realview.copy
            f0=B.diagview(1).realview.copy
        else:
            d0=B.diagview(0).copy
            f0=B.diagview(1).copy
        return (L,d0,f0,R,eps0)
    def svdIteration(L0,d0,f0,R0,eps0):
        cntr=0
        maxcntr=20*d0.length
        while cntr < maxcntr:
            biDiagPhaseToZero(L0,d0,f0,R0,eps0)
            cntr += 1
            i,j=svdCorners(f0)
            if j == 0:
                break
            d=d0[i:j]
            f=f0[i:j-1]
            L=L0[:,i:j]
            R=R0[i:j,:]
            n=f.length
            k=zeroFind(d,eps0)
            if k >=0:
                if d[n] == 0.0:
                    zeroCol(d,f,R)
                else:
                    zeroRow(L[:,k:],d[k+1:],f[k:])
            else:
                svdStep(L,d,f,R)
    def svdSort(L,d,R):
        indx=d.sort('BYVALUE','DESCENDING')
        if 'cmview' in R.type:
            R.realview.permute(indx,'ROW')
            R.imagview.permute(indx,'ROW')
            U[:,0:d.length].realview.permute(indx,'COL')
            U[:,0:d.length].imagview.permute(indx,'COL')
        else:
            R.permute(indx,'ROW')
            U[:,0:d.length].permute(indx,'COL')
    U,S,f0,VH,eps0 = svdBidiagonal(A)
    svdIteration(U,S,f0,VH,eps0)
    svdSort(U,S,VH)
    return(U,S,VH)
