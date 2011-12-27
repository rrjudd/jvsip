import vsiputils as vsip

# VU Functions
def size(a):
    """
       size(view) will return a tuple of
           (offset,stride,length)
       if view is a vsipl vector or
           (offset, col_stride, col_length, row_stride, row_length)
       if view is a vsipl matrix
    """
    f={'vview_d':'_vsize(vsip.getattrib(a))',
       'vview_f': '_vsize(vsip.getattrib(a))',
       'cvview_d':'_vsize(vsip.getattrib(a))',
       'cvview_f':'_vsize(vsip.getattrib(a))',
       'vview_vi':'_vsize(vsip.getattrib(a))',
       'vview_mi':'_vsize(vsip.getattrib(a))',
       'vview_bl':'_vsize(vsip.getattrib(a))',
       'vview_i':'_vsize(vsip.getattrib(a))',
       'vview_si':'_vsize(vsip.getattrib(a))',
       'vview_uc':'_vsize(vsip.getattrib(a))',
       'mview_d':'_msize(vsip.getattrib(a))',
       'mview_f':'_msize(vsip.getattrib(a))',
       'cmview_d':'_msize(vsip.getattrib(a))',
       'cmview_f':'_msize(vsip.getattrib(a))',
       'mview_bl':'_msize(vsip.getattrib(a))',
       'mview_i':'_msize(vsip.getattrib(a))',
       'mview_si':'_msize(vsip.getattrib(a))',
       'mview_uc':'_msize(vsip.getattrib(a))'}
    def _vsize(attr):
        return (attr.offset,attr.stride,attr.length)
    def _msize(attr):
        return (attr.offset,attr.col_stride,attr.col_length,attr.row_stride, attr.row_length)
    t=vsip.getType(a)
    if f.has_key(t[1]):
        return eval(f[t[1]])
    else:
        print('Not a supported type')
        return False
def FFTdataGenRamp(a):
    """ FFTdataGenRamp(v) expects argument 'v' to ba a complex VSIPL vector.
        The vector is filled with data which, when the fft is applied,
        should turn into a ramp starting a 0 with increment 1.
        This function is normally used for testing FFT codes.
    """
    from math import cos as ccos,sin as ssin,pi
    def _gen(a):
        N=int(vsip.getlength(a))
        npm=N/2
        c=pi/float(N)
        vsip.put(a,0,(float(N) - 1.0)/2.0)
        indx=0;
        if N % 2:
            for i in range(npm):
                indx = i+1
                x = c * float(i) + c
                x = -0.5j * ccos(x)/ssin(x)  - 0.5
                vsip.put(a,indx,x)
            for i in range(npm,0,-1):
                indx +=1
                x=vsip.get(a,i)
                x.i=-x.i
                vsip.put(a,indx,x)
        else:
            npm -= 1
            for i in range(npm):
               indx = i+1
               x = c * float(i) + c
               x = -0.5j * ccos(x)/ssin(x)  - 0.5
               vsip.put(a,indx,x)
            x=-0.5
            indx +=1
            vsip.put(a,indx,x)
            for i in range(npm,0,-1):
                indx +=1
                x=vsip.get(a,i)
                x.i=-x.i
                vsip.put(a,indx,x)
    t=vsip.getType(a)
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
        a=vsip.create(t,l);
        s=vsip.create('rand',(s,1,1,f))
        vsip.randn(s,a)
        vsip.destroy(s)
        return a
    def rcfu(t,s,f,l):
        a=vsip.create(t,l);
        s=vsip.create('rand',(s,1,1,f))
        vsip.randu(s,a)
        vsip.destroy(s)
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
def mprint(m,fmt):
    """ 
        This function will print a VSIPL matrix or vector suitable for pasting into Octave or Matlab.
        usage: mprint(<vsip matrix/vector>, fmt)
        fmt is a string corresponding to a simple fmt statement. 
        For instance '%6.5f' prints as 6 characters wide with 5 decimal digits.
        Note format converts this statement to '% 6.5f' or '%+6.5f' so keep
        the input simple.
    """
    def _fmt1(c):
        if c != '%':
            return c
        else:
            return '% '
    def _fmt2(c):
        if c != '%':
            return c
        else:
            return '%+'
    def _fmtfunc(fmt1,fmt2,y):
        x = vsip.cscalarToComplex(y)
        if type(x) == complex:
            return fmt1 % x.real + fmt2 % x.imag + "i"
        else:
            return fmt % x
    tm=['mview_d','mview_f','cmview_d','cmview_f','mview_i','mview_uc','mview_si','mview_bl']
    tv=['vview_d','vview_f','cvview_d','cvview_f','vview_i','vview_uc','vview_si','vview_bl','vview_vi','vview_mi']
    t=vsip.getType(m)[1]
    tfmt=[_fmt1(c) for c in fmt]
    fmt1 = "".join(tfmt)
    tfmt=[_fmt2(c) for c in fmt]
    fmt2 = "".join(tfmt)
    if t in tm:
        cl=vsip.getcollength(m)
        rl=vsip.getrowlength(m)
        for i in range(cl):
            M=[]
            for j in range(rl):
                M.append(_fmtfunc(fmt1,fmt2,vsip.get(m,(i,j))))
            if i == 0:
                print("["+" ".join(M) + ";")
            elif i < cl-1:
                print(" "+" ".join(M) + ";")
            else:
                print(" "+" ".join(M) + "]")
    elif t in tv:
        l=vsip.getlength(m)
        V=[_fmtfunc(fmt1,fmt2,vsip.get(m,i)) for i in range(l)]
        print("[" + " ".join(V) + "]")
    else:
        print('Object not VSIP vector or matrix')
def mstring(m,fmt):
    """ 
        This function will print a VSIPL matrix or vector suitable for pasting into Octave or Matlab.
        usage: mprint(<vsip matrix/vector>, fmt)
        fmt is a string corresponding to a simple fmt statement. 
        For instance '%6.5f' prints as 6 characters wide with 5 decimal digits.
        Note format converts this statement to '% 6.5f' or '%+6.5f' so keep
        the input simple.
    """
    def _fmt1(c):
        if c != '%':
            return c
        else:
            return '% '
    def _fmt2(c):
        if c != '%':
            return c
        else:
            return '%+'
    def _fmtfunc(fmt1,fmt2,y):
        x = vsip.cscalarToComplex(y)
        if type(x) == complex:
            s = fmt1 % x.real
            s += fmt2 % x.imag
            s += "i"
            return s
        else:
            return fmt1 % x
    tm=['mview_d','mview_f','cmview_d','cmview_f','mview_i','mview_uc','mview_si','mview_bl']
    tv=['vview_d','vview_f','cvview_d','cvview_f','vview_i','vview_uc','vview_si','vview_bl','vview_vi','vview_mi']
    t=vsip.getType(m)[1]
    tfmt=[_fmt1(c) for c in fmt]
    fmt1 = "".join(tfmt)
    tfmt=[_fmt2(c) for c in fmt]
    fmt2 = "".join(tfmt)
    if t in tm:
        cl=vsip.getcollength(m)
        rl=vsip.getrowlength(m)
        s=str()
        for i in range(cl):
            M=[]
            for j in range(rl):
                M.append(_fmtfunc(fmt1,fmt2,vsip.get(m,(i,j))))
            if i == 0:
                s += "["+" ".join(M) + ";\n"
            elif i < cl-1:
                s += " "+" ".join(M) + ";\n"
            else:
                s += " "+" ".join(M) + "]\n"
        return s
    elif t in tv:
        l=vsip.getlength(m)
        V=[_fmtfunc(fmt1,fmt2,vsip.get(m,i)) for i in range(l)]
        return "[" + " ".join(V) + "]\n"
    else:
        print('Object not VSIP vector or matrix')
def vView(x,o,s,l):
    """ vView(x,o,s,l) returns the view x with offset, stride and
        length (o,s,l) .
        This could also be done with vsiputils using
        bind(vsip.block(x),(o,s,l))
        except that bind will create a new object that will need to 
        be allocated and destroyed.
        vView will modify the supplied object x.
    """
    t=['vview_f', 'vview_d',
       'cvview_f','cvview_d',
       'vview_i','vview_si','vview_uc','vview_vi',
       'vview_bl','vview_mi']
    myT=vsip.getType(x)[1]
    if myT in t:
        attr=vsip.getattrib(x)
        attr.offset=o; attr.stride=s; attr.length=l
        return vsip.putattrib(x,attr)
    else:
        print('type ' + myT + ' not supported by vView')