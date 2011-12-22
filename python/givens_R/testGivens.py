from vsip import *
import vsiputils as vsip
import vsipUser as VU
from VI_givens_d import *

def mprint(m,fmt):
    """ 
        This function will print a VSIPL matrix or vector suitable for pasting into Octave or Matlab.
        usage: mprint(<vsip matrix/vector>, fmt)
        fmt will be a string corresponding to a pthon fmt statement. For instance '%6.5f' prints as
        6 characters wide with 5 decimal digits.
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
        V=[_fmtfunc(fmt1,vsip.get(m,i)) for i in range(l)]
        print("[" + " ".join(V) + "]")
    else:
        print('Object not VSIP vector or matrix')

def testGivens(): 
   A = vsip.create('cmview_d',(10,6,VSIP_ROW,VSIP_MEM_NONE));
   czero = vsip_cmplx_d(0.0,0.0);
   vsip.fill(czero,A);
   for i in range(vsip.getrowlength(A)):
       ac = vsip.colview(A,i);
       ac_r= vsip.realview(ac);
       ac_i = vsip.imagview(ac);
       vsip.ramp(-1.3,1.1,ac_r);
       vsip.ramp(+1.3,-1.1,ac_i);
       vsip.destroy(ac_r); vsip.destroy(ac_i);
       vsip.destroy(ac);
   ad = vsip_cmdiagview_d(A,0);
   ad_r = vsip_vrealview_d(ad);
   ad_i = vsip_vimagview_d(ad);
   vsip.ramp(3,1.2,ad_r);
   vsip.ramp(3,-1.2,ad_i);
   vsip.destroy(ad_i);
   vsip.destroy(ad_r);
   vsip.destroy(ad);
   print("Input data \n");
   print("A = " + VU.mstring(A,"%6.4f"))
   VI_cgivens_r_d(A)
   print("R = " + VU.mstring(A,"%7.4f"))
   vsip.allDestroy(A);

testGivens()
