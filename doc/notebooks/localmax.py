import pyJvsip as pv
def localmax(A):
    """
    Note A is a vector of type real float
    % k = localmax(x)
    % finds location of local maxima
    """
    sptd=['vview_d','vview_f']
    assert A.type in sptd, 'local max only works with real vectors of type float'
    x=A 
    N = x.length
    b1=x[:N-1].lle(x[1:N]); b2=x[:N-1].lgt(x[1:N])
    k = b1[0:N-2].bband(b2[1:N-1]).indexbool
    k+=1
    if x[0] > x[1]:
        t=pv.create(k.type,k.length+1)
        t[:k.length]=k
        t[k.length]=0
        k=t.copy
    if x[N-1]>x[N-2]:
        t=pv.create(k.type,k.length+1)
        t[:k.length]=k
        t[k.length]=N-1
        k=t.copy
    k.sort()
    return k

