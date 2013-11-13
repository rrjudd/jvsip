import pyJvsip as pv
from math import pi, ceil, log, pow, floor
from localmax import localmax
from frefine import frefine
from firfbe import firfbe
from matplotlib.pyplot import figure,plot,hold,axis,xlabel,ylabel,title

def firebp(n,w1,w2,Del):
    """[h,rs,be] = firebp(n,w1,w2,Del);
       Bandpass linear phase FIR filter design with specified ripple sizes.
       - the derivative of the frequency response amplitude at w1 is
         set equal to the negative derivative of the amplitude at w2 -
       author : Ivan Selesnick, Rice University, Dec 94
       parameters
        h   : filter of length 2*n+1
        rs  : reference set upon convergence
        be  : band edges of h
        w1  : first half-magnitude frequency
        w2  : second half-magnitude frequency
       	w1 < w2,  w1,w2 should be in the interval (0,pi)
        Del : [ripple size in first stopband, passband, second stopband]
       subprograms needed
        localmax, frefine, firfbe
         EXAMPLE
        n   =  23;
        w1  = 0.14 * 2*pi;
        w2  = 0.34 * 2*pi;
        Del = [0.01 0.03 0.01];
        [h,rs,be] = firebp(n,w1,w2,Del);
    """
    def rem(a,b):
        return a % b
    try:
        log2
    except:
        def log2(a):
            return log(a,2)

    def mp(t,lngth): #minus_plus vector [-1 1 -1 ... (-1)^lngth]
        assert isinstance(lngth,int),'Length argument to mp must be an integer. '
        assert isinstance(t,str) and t in ['vview_d','vview_f'],\
                     "type argument must be 'vview_d' or 'vview_f'"
        retview = create(t,lngth).fill(1.0)
        retview[:lngth:2].fill(-1.0)
        return retview
    def diff(a):
        assert 'pyJvsip.__View' in repr(a),'diff only works with pyJvsip views'
        assert 'vview' in a.type, 'diff only works with vector views'
        if a.length > 1:
            retview = a[1:a.length] - a[:a.length - 1]
            return retview
        else:
            return None
    def srmp(t,s,e):
        assert isinstance(e,int) and isinstance(s,int),'start and end must be intergers'
        assert e > s, 'simple ramps alwasy go up; end > start '
        return pv.create(t,e-s+1).ramp(s,1)
    def coscoef(rs,n,V,Y):
        f={'vview_d':'mview_d','vview_f':'mview_f'}
        m=rs.length + 1
        y=pv.create(Y.type,m)
        y[:Y.length]=Y;y[m-1]=0.0
        A=pv.create(f[y.type],m,y.length)
        a=A[:rs.length,:n+1]
        a=pv.outer(1,rs,pv.create(rs.type,n+1).ramp(0,1),a).cos
        at=A.rowview(m-1)
        A.rowview(m-1)[:]=V[:]
        return A.luSolve(y)
    # ------------------ initialize constants ---------------------------
    assert 'pyJvsip.__View' in repr(Del) and Del.type in ['vview_f','vview_d'],\
                "last argument is a vector view of type 'vview_f' or 'vview_d'"
    t=Del.type
    L = int(pow(2,int(ceil(log2(10*n)))))
    w = pv.create(t,L+1).ramp(0,pi/float(L))  # frequency axis
    N = n - 2                              # number of _non-specified interpolation points
    SN = 1e-8                              # Small Number (stopping criterion)
    H0 = pv.create(t,2*(L+1-n)+2*n-2).fill(0.0)
    V = pv.create(t,n+1).ramp(0,1);V *= V.empty.ramp(0,w1).sin + V.empty.ramp(0,w2).sin
    ideal = Del.empty.fill(0.0); ideal[1]=1.0
    up = ideal + Del
    lo = ideal - Del
    D1 = 0.5				# half-magnitude value at w1
    D2 = 0.5				# half-magnitude value at w2
    PF = False				# PF : flag : Plot Figures
    # ------------------ initialize reference set ----------------------------
    # n1 : number of reference frequencies in first stopband
    # n2 : number of reference frequencies in passband
    # n3 : number of reference frequencies in second stopband
    n2 = int(round(N*(w2-w1)/pi))
    if rem(n2,2) == 0:
         n2 = n2 - 1
    n1 = int(floor((N-n2)*w1/(pi-(w2-w1))))
    n3 = N-n2-n1
    rs = pv.create(t,n1+n2+n3+2)
    R1 = rs[0:n1].ramp(0,1); R1 *= w1/float(n1)
    R2 = rs[n1+1:n1+1+n2].ramp(1,1);R2 *= (w2-w1)/float(n2+1);R2 += w1
    R3 = rs[n1+n2+2:n1+n2+2+n3].ramp(1,1);R3 *= (pi-w2)/float(n3);R3 += w2
    rs[n1]=w1; rs[n1+1+n2]=w2
    # ------------------ initialize interpolation values ---------------------
    Y=pv.create(t,n1+n2+n3+2).fill(0.0)
    if n1 % 2 == 0:
        Y[0:n1:2].fill(up[0]);Y[1:n1:2].fill(lo[0])
    else:
        Y[0:n1:2].fill(lo[0]);Y[1:n1:2].fill(up[0])
    Y[n1]=D1;o=n1+1;l=n1+1+n2
    Y[o:l:2].fill(up[1]);Y[o+1:l:2].fill(lo[1])
    Y[l]=D2;o=l+1;l=o+n3
    Y[o:l:2].fill(lo[2]);Y[o+1:l:2].fill(up[2])
    # begin looping
    Err = 1
    while Err > SN:
        # --------------- calculate cosine coefficients -----------------------
        a = coscoef(rs,n,V,Y)
        # --------------- calculate frequency response ------------------------
        #H = real(fft([a(1);a(2:n+1)/2;Z;a(n+1:-1:2)/2])); H = H(1:L+1);
        attr=a.attrib; ot=attr['offset'];lt=attr['length'];st=attr['stride'];
        ot+=(lt-1)*st; st=-st;attr['offset']=ot; attr['stride']=st
        a_rev=a.clone;a_rev.putattrib(attr)
        H0.fill(0.0);H0[0]=a[0];H0[1:lt]=a[1:]/2.0; H0[H0.length-n:]=a_rev[:lt-1]/2.0
        Hc=H0.rcfft
        H=Hc.realview[:L+1].copy
        # --------------- determine local max and min -------------------------
        v1 = localmax(H)
        v2 = localmax(H.copy.neg)
        if v1[0] < v2[0]:
            s = 0;
        else:
            s = 1;
        #ri = sort([v1; v2]);
        ri=pv.create(H.type,v1.length+v2.length)
        ri[:v1.length]=v1;ri[v1.length:]=v2
        ri.sort()
        rs = (ri)*pi/L
        rs = frefine(a,rs)
        n1 = rs.llt(w1).sumval
        n2 = pv.bb_and(rs.lgt(w1), rs.llt(w2), pv.create('vview_bl',rs.length)).sumval
        n3 = rs.lgt(w2).sumval
        # --------------- calculate frequency response at local max and min ---
        Hr = rs.outer(srmp(rs.type,0,n)).cos.prod(a)
        Id=pv.create(Del.type,n1+n2+n3);Dr=Id.empty
        Id[:n1].fill(ideal[0]);Id[n1:n1+n2].fill(ideal[1]);Id[n1+n2:].fill(ideal[2])
        Dr[:n1].fill(Del[0]);Dr[n1:n1+n2].fill(Del[1]);Dr[n1+n2:].fill(Del[2])
        Er = (Hr - Id)/Dr;
        # Plot Figures if PF is True
        if PF:
           figure(1)
    	   plot(w/pi,H)
    	   hold(True)
    	   plot(rs/pi,Hr,'o')
    	   hold(False)
    	   axis([0, 1, -.2, 1.2])
       	   figure(2)
           plot(Er)
           hold(True)
           plot(Er,'o'),
           hold(False)
    	   pause(0.05)
        # --------------- calculate new interpolation points  -----------------
        Y=Id.empty
        if n1 % 2 == 0:
            Y[0:n1:2].fill(up[0]);Y[1:n1:2].fill(lo[0])
        else:
            Y[0:n1:2].fill(lo[0]);Y[1:n1:2].fill(up[0])
        Y[n1+1:n1+n2:2].fill(lo[1]);Y[n1:n1+n2:2].fill(up[1])
        Y[n1+n2+1::2].fill(up[2]);Y[n1+n2::2].fill(lo[2])
        # --------------- slim down the set of local max and min --------------
        # --------------- to obtain new reference set of correct size ---------
        if (rs.length-N) == 1: # remove one frequency from the reference set
            if abs(Er[0]-Er[1]) < abs(Er[rs.length-1]-Er[rs.length-2]):
                I = 1; s = s + 1;
            else:
                I = rs.length;
            del rs[I-1]; del Y[I-1]; del Er[I-1]
        elif (rs.length-N) == 2: # remove two frequencies
            # remove either the two endpoints or remove two adjacent points in the ref. set
            k = (diff(Er)*(mp(Er.type,rs.length-1)+s)).minvalindex+1;
            if (k == 1) | (k == (rs.length-1)):
                if k == 1:
                    I = 1; s = s + 1
                else:
                    I = rs.length
                del rs[I-1]; del Y[I-1]; del Er[I-1]
                if abs(Er[0]-Er[1]) < abs(Er[rs.length-1]-Er[rs.length-2]):
                    I = 1; s = s + 1;
                else:
                    I = rs.length;
                del rs[I-1]; del Y[I-1]; del Er[I-1]
            else:
                I = k;
                del rs[I-1]; del Y[I-1]; del Er[I-1]
                del rs[I-1]; del Y[I-1]; del Er[I-1]
        elif (rs.length-N) == 3: # remove three frequencies
            # just use the code for (rs.length-N)==1, followed by the code for (rs.length-N)==2
            if abs(Er[0]-Er[1]) < abs(Er[rs.length-1]-Er[rs.length-2]):
                I = 1; s = s + 1
            else:
                I = rs.length
            del rs[I-1]; del Y[I-1]; del Er[I-1]
            k = (diff(Er)*(mp(Er.type,rs.length-1)+s)).minvalindex+1
            if (k == 1) or (k == (rs.length-1)):
                if k == 1:
                   I = 1; s = s + 1
                else:
                    I = rs.length;
                del rs[I-1]; del Y[I-1]; del Er[I-1]
                if abs(Er[0]-Er[1]) < abs(Er[rs.length-1]-Er[rs.length-2]):
                    I = 1; s = s + 1
                else:
                    I = rs.length;
                del rs[I-1]; del Y[I-1]; del Er[I-1]
            else:
                I = k;
                del rs[I-1]; del Y[I-1]; del Er[I-1]
                del rs[I-1]; del Y[I-1]; del Er[I-1]
        # END IF
        # calculate error
        Err = Er.maxmgval-1 #max(abs(Er))-1
        print('    Err = %20.15f\n'%Err)

        if Err > SN:
            # --------------- update new interpolation points ---------------------
            n1 = rs.llt(w1).sumval
            n2 = pv.bb_and(rs.lgt(w1), rs.llt(w2), pv.create('vview_bl',rs.length)).sumval
            n3 = rs.lgt(w2).sumval
            Y1 = Y[0:n1].copy
            Y2 = Y[n1:n1+n2].copy
            Y3 = Y[n1+n2:].copy
            Y = pv.create(Y1.type,n1+n2+n3+2)
            Y[0:n1]=Y1;Y[n1]=D1;Y[n1+1:n1+n2+1]=Y2;Y[n1+n2+1]=D2;Y[n1+n2+2:]=Y3
            # --------------- update new reference set ----------------------------
            #rs = [rs(1:n1); w1; rs(n1+1:n1+n2); w2; rs(n1+n2+1:n1+n2+n3)]
            rst1=rs[0:n1].copy;rst2=rs[n1:n1+n2].copy;rst3=rs[n1+n2:].copy
            rs=pv.create(rst1.type,rs.length+2)
            rs[:n1]=rst1;rs[n1]=w1;rs[n1+1:n1+n2+1]=rst2;rs[n1+n2+1]=w2;rs[n1+n2+2:]=rst3
    #end while
    # ------------------ calculate band edges ----------------------------
    be = firfbe(a,pv.listToJv(Del.type,[w1,w1,w2,w2]),pv.listToJv(Del.type,[up[0],lo[1],lo[1],up[2]]))
    # ------------------ calcuate filter coefficients ----------------------------
    #h = [a(n+1:-1:2)/2; a(1); a(2:n+1)/2]
    a[1:]/=2.0
    atr=a[1:].attrib
    h=pv.create(Del.type,2*a.length-1)
    h[a.length-1]=a[0]
    h[a.length:]=a[1:]
    atr=a[1:].attrib;atr['offset']=atr['length'];atr['stride']*=-1
    a.putattrib(atr);h[:a.length]=a
    figure(1); plot(w/pi,H); hold(True); plot(rs/pi,Y,'x'); hold(False)
    axis([0, 1, -.2, 1.2])
    xlabel('w'); ylabel('H'); title('Frequency Response Amplitude')
    return(h,rs,be)
