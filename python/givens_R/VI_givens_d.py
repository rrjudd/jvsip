from vsip import *
import vsiputils as vsip
from numpy import sqrt

def VI_cgivens_d( a, b):
    """
       returns cos, sin, r
    """
    c = vsip_cmplx_d(0.0,0.0)
    s = vsip_cmplx_d(0.0,0.0)
    r = vsip_cmplx_d(0.0,0.0)
    am = vsip_cmag_d(a)
    bm = vsip_cmag_d(b)
    if am == 0.0:
        r.r = b.r; r.i=b.i;
        s.r = 1.0;
    else:
        scale = am + bm;
        alpha = vsip_cmplx_d(a.r/am, a.i/am)
        scalesq = scale * scale
        norm = scale * sqrt((am*am)/scalesq + (bm * bm)/scalesq)
        c.r =am/norm
        s.r =  (alpha.r * b.r + alpha.i * b.i)/norm
        s.i = (-alpha.r * b.i + alpha.i * b.r)/norm
        r.r = alpha.r * norm;  r.i = alpha.i * norm
    return (c,s,r)

def VI_cgivens_r_d(A):
   if vsip.getType(A)[1] != 'cmview_d':
       print("need complex cmview_d for input");
   else:
       m = vsip.getcollength(A)
       n = vsip.getrowlength(A)
       for j in range(n):
          for i in range(m-1,j,-1):
              a=vsip.get(A,(i-1,j))
              b=vsip.get(A,(i,j))
              (c,s01,r)=VI_cgivens_d(a,b);
              # rotate r so the iamginary part is 0
              a0p_r=vsip_cmag_d(r)
              vsip.put(A,(i-1,j),vsip_cmplx_d(a0p_r,0))
              vsip.put(A,(i,j),vsip_cmplx_d(0,0))
              # store a rotation vector in r 
              if a0p_r != 0:
                  r.r =  r.r/a0p_r
                  r.i = -r.i / a0p_r       
              s10 = vsip_cmplx_d(-s01.r,s01.i)
              for k in range(1,n-j):
                  a0=vsip.get(A,(i-1,j+k))
                  a1=vsip.get(A,(i,j+k))
                  a0_r=a0.r; a1_r=a1.r
                  a0_i=a0.i; a1_i=a1.i
                  a0 = vsip_cmplx_d(a0_r * c.r + a1_r * s01.r - a1_i * s01.i, 
                                    a0_i * c.r + s01.r * a1_i + a1_r * s01.i)
                  # correct a0 for rotation and place in matrix
                  a0_p=vsip_cmplx_d(r.r * a0.r - r.i * a0.i, r.r * a0.i + r.i * a0.r)
                  a1_p=vsip_cmplx_d(a1_r * c.r + s10.r * a0_r - s10.i * a0_i,
                                 a1_i * c.r + s10.r * a0_i + s10.i * a0_r)
                  vsip.put(A,(i-1,j+k),a0_p)
                  vsip.put(A,(i,j+k),a1_p)
   return A

