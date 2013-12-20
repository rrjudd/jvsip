import pyJvsip as pv
def svdSort(L,d,R):
    index = d.sort('BYVALUE','DESCENDING')
    L[:,:d.length].permute(index.copy,'COL')
    R.permute(index,'ROW')
    return (L,d,R)
