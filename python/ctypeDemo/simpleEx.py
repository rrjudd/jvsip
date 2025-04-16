import ctypes
lib=ctypes.CDLL("./libvsip.so")

memory_hint = {
    "VSIP_MEM_NONE":ctypes.c_int(0),
    "VSIP_MEM_RDONLY":ctypes.c_int(1),
    "VSIP_MEM_CONST":ctypes.c_int(2),
    "VSIP_MEM_SHARED":ctypes.c_int(3),
    "VSIP_MEM_SHARED_RDONLY":ctypes.c_int(4),
    "VSIP_MEM_SHARED_CONST":ctypes.c_int(5)}

def vsipInit():
    lib.vsip_init.restype=ctypes.c_int
    return lib.vsip_init(ctypes.c_void_p(0))
    
    
def vsipFinalize():
    lib.vsip_finalize.restype=ctypes.c_int
    return lib.vsip_finalize(ctypes.c_void_p(0))


def vcreate_f(len):
    lib.vsip_vcreate_f.restype = ctypes.c_void_p
    return lib.vsip_vcreate_f(ctypes.c_ulong(len),memory_hint["VSIP_MEM_NONE"])


def vdestroy_f(v):
    lib.vsip_valldestroy_f(ctypes.c_void_p(v))

def vramp_f(start,step,v):
    lib.vsip_vramp_f(ctypes.c_float(start), ctypes.c_float(step), ctypes.c_void_p(v))

def vget_f(i,v):
    lib.vsip_vget_f.restype = ctypes.c_float
    return lib.vsip_vget_f(ctypes.c_void_p(v),ctypes.c_ulong(i))
