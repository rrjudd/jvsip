from vsip import *

N=8 #length of vector
init = vsip_init(None)

def VU_vprint_f(a):
    print(" ".join(["%4.0f" % vsip_vget_f(a,i) for i in range(vsip_vgetlength_f(a))]))

A = vsip_vcreate_f(N,0)
B = vsip_vcreate_f(N,0)
C = vsip_vcreate_f(N,0)
vsip_vramp_f(0,1,A)
print("A = \n"); VU_vprint_f(A)
vsip_vfill_f(5,B)
print("B = \n"); VU_vprint_f(B)
vsip_vadd_f(A,B,C)
print("C = \n"); VU_vprint_f(C)
vsip_valldestroy_f(A)
vsip_valldestroy_f(B)
vsip_valldestroy_f(C)
vsip_finalize(None)
