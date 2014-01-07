import pyJvsip as pv
def svdSort(L,d,R):
    """
    Usage:
        L,d,R = svdSort(L,d,R)
    Where:
        matrix A = L.prod(D).prod(R) and D is a diagonal matrix represented
        by vector d.
    Sorts d so that the values go from largest to smallest and updates L and
    R so that A = L.prod(D).prod(R) after sort.
    """
    index = d.sort('BYVALUE','DESCENDING')
    L[:,:d.length].permute(index.copy,'COL')
    R.permute(index,'ROW')
    return (L,d,R)
