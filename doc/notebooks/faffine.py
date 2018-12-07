from math import pi,ceil,log,pow
import pyJvsip as pv
from localmax import *
from frefine import * 
from matplotlib import pyplot
def faffine(M,wp,ws,Kp,Ks,eta_p,eta_s):
    """
    Usage:
         ans= faffine(M,wp,ws,Kp,Ks,eta_p,eta_s)
         h=ans[0], rs=ans[1],del_p=ans[2], del_s=ans[3]
    Notes from matlab code below.
    % [h,rs,del_p,del_s] = faffine(M,wp,ws,Kp,Ks,eta_p,eta_s);
    % Lowpass linear phase FIR filter design by a REMEZ-like algorithm
    %  h   : filter of length 2*M+1
    %  rs  : reference set upon convergence
    %  del_p : passband error, del_p = Kp * del + eta_p
    %  del_s : stopband error, del_s = Kp * del + eta_s
    %  wp,ws : band edges
    % EXAMPLE
    %  M  =  17;
    %  wp = 0.30*pi;
    %  ws = 0.37*pi;
    %  Kp = 0; Ks = 1; eta_p = .05; eta_s = 0;
    %  [h,rs,del_p,del_s] = faffine(M,wp,ws,Kp,Ks,eta_p,eta_s);

    % author: IVAN SELESNICK
    %
    % required subprograms : frefine.m, localmax.m
    """
    # ------------------ initialize some constants ------------------------------
    L = int(pow(2,ceil(log(10*M,2))))
    SN = 1e-7 
    w  = pv.create('vview_d',int(L+1)).ramp(0,pi/L)
    S = int(M + 2)
    np = round(S*(wp+ws)/(2*pi))
    np = int(max(np, 1))
    if np == S:
        np = np - 1
    ns = int(S - np)
    r_pass =pv.create('vview_d',np); r_stop=pv.create('vview_d',ns)
    if np > 1:
        r_pass.ramp(0,wp/(np-1))
    else:
        r_pass[0] = wp
    if ns > 1:
        r_stop.ramp(ws,(pi-ws)/(ns-1))
    else:
       r_stop[0] = ws
    rs= pv.create('vview_d',S);rs[0:np]=r_pass; rs[np:]=r_stop #initial ref. set
    D = pv.create('vview_d',int(np+ns)).fill(0.0);D[:np].fill(1.0)
    sp = pv.create('vview_d',int(S)).fill(0.0);
    if np % 2:
        sp[:int(np):2].fill(-1.0);sp[1:int(np):2].fill(1.0)
    else:
        sp[:int(np):2].fill(1.0);sp[1:int(np):2].fill(-1.0)
    ss = sp.empty.fill(0.0);
    ss[int(np):int(S):2].fill(1.0);ss[int(np)+1:int(S):2].fill(-1.0)
    Z = int(2*(L+1-M)-3)
    # begin looping
    Err = 1
    while Err > SN:
       # --------------- calculate cosine coefficients ---------------------------
       x1=pv.create('mview_d',M+4,M+4).fill(0.0)
       x1[M+3,M+3]=-Ks; x1[M+3,M+2]=1.0;x1[M+2,M+1]=1;x1[M+2,M+3]=-Kp
       x1[:S,:M+1]=rs.outer(pv.create('vview_d',M+1).ramp(0,1)).cos
       x1.colview(M+1)[:S]=sp.neg; x1.colview(M+2)[:S]=ss.neg; 
       x2=pv.create('vview_d',D.length+2)
       x2[:D.length]=D;x2[D.length+1]=eta_s;x2[D.length]=eta_p
       x = x1.luSolve(x2)
       a = x[0:M+1].copy
       del_p = x[M+1]
       del_s = x[M+2]
       del_  = x[M+3]
       if (del_p<0) and (del_s<0):
           print('both del_p and del_s are negative!')
       elif del_s < 0:
           # set del_s equal to 0
           print('del_s < 0')
           x1[:S,:M+1]=rs.outer(pv.create('vview_d',M+1).ramp(0,1)).cos
           x1.colview(M+1)[:S]=sp.neg;
           x = x1[:S,:M+2].luSolve(D.copy)
           a = x[0:M+1].copy
           del_p = x[M+1]
           del_s = 0;
       elif del_p < 0:
           # set del_p equal to 0
           print('del_p < 0')
           x1[:S,:M+1]=rs.outer(pv.create('vview_d',M+1).ramp(0,1)).cos
           x1.colview(M+1)[:S]=ss.neg;
           x = x1[:S,:M+2].luSolve(D.copy)
           a = x[0:M+1].copy
           del_p = 0;
           del_s = x[M+1];
       A=pv.create('vview_d',a.length*2-1+Z).fill(0.0)
       A[:a.length]=a; A[1:a.length] *= 0.5; A[a.length+Z:]=A.block.bind(a.length-1,-1,a.length-1)
       Ac=A.rcfft
       A=Ac.realview.copy
       # --------------- determine new reference set-----------------------------
       # Below neg done in place so undo is required
       # Could use A.copy.neg instead but pay a create/destroy penalty
       lmAn=localmax(A.neg);lmA=localmax(A.neg)
       ri=pv.create('vview_d',lmA.length+lmAn.length).fill(0.0)
       ri[:lmA.length]=lmA;ri[lmA.length:]=lmAn;ri.sortip()
       rs=frefine(a,ri*(pi/float(L)))
       rsp=rs.gather(rs.llt(wp).indexbool)
       rss=rs.gather(rs.lgt(ws).indexbool)
       rs=pv.create(rsp.type,rsp.length+rss.length+2).fill(0.0)
       rs[:rsp.length]=rsp;rs[rsp.length:][0]=wp;rs[rsp.length:][1]=ws;
       rs[rsp.length+2:]=rss
       np = rsp.length+1
       ns = rss.length+1
       D = pv.create('vview_d',np+ns).fill(0.0);D[:np].fill(1.0)
       sp = D.empty.fill(0.0)
       if np % 2:
           sp[:int(np):2].fill(-1.0);sp[1:int(np):2].fill(1.0)
       else:
           sp[:int(np):2].fill(1.0);sp[1:int(np):2].fill(-1.0)
       ss = D.empty.fill(0.0);ss[np::2].fill(1.0);ss[np+1::2].fill(-1.0)
       lr = rs.length
       Ar = rs.outer(pv.create(rs.type,M+1).ramp(0,1)).cos.prod(a)

       if lr > M+2:
           sp.putlength(M+2)
           ss.putlength(M+2)
           D.putlength(M+2)
           Ar.putlength(M+2)
           rs.putlength(M+2)
           if A[0] < A[1]:
               cp_ = -1.;
           else:
               cp_ = 1.
           if A[L] < A[L-1]:
               cs = -1.
           else:
               cs = 1.
           if ((A[0]-1.)*cp_ - del_p) < (A[L] * cs - del_s):
               sp.putoffset(1)
               ss.putoffset(1)
               D.putoffset(1)
               Ar.putoffset(1)
               rs.putoffset(1)
       # -------- calculate stopping criterion ------------
       Err = ((Ar - D) - ((Kp*del_+eta_p)*sp + (Ks*del_+eta_s)*ss)).mag.maxval
       print('Err = %20.15f\n'%Err)
    h = pv.create(a.type,2 * a.length -1).fill(0.0)
    a[1:] *= 0.5;a2=a[1:];a1=a.block.bind(a2.length -1 + a2.offset,-1,a2.length);
    h[:a1.length]=a1; h[a1.length]=a[0]; h[a1.length+1:]=a2   # h : filter coefficients
    pi_inv=1.0/pi
    pyplot.figure(1) 
    pyplot.plot((w*pi_inv).list,A.list,'r')
    pyplot.plot((rs*pi_inv).list,Ar.list,'+')
    pyplot.xlabel('w/pi',fontsize=14);pyplot.ylabel('A',fontsize=14)
    pyplot.title('Frequency Response Amplitude',fontsize=16)
    return (h,rs,del_p,del_s)


