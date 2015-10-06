def firfbe(a,wi,Abe):
    """
    FIR Find Band Edges
    % w = fir_fbe(a,wi,Abe);
    % find band edges of an FIR filter using Newton's method
    % using initial estimates
    %
    % A   : a(1)+a(2)*cos(w)+...+a(n+1)*cos(n*w)
    % wi  : initial values for the band edges
    % Abe : value of H at the band edges
    """
    m=a.empty.ramp(0,1)
    w = wi.copy
    for k in range(15):
        A = w.outer(m).cos.prod(a)-Abe
        A1 = w.outer(m).sin.neg.prod(m*a)
        w -=  A*A1.recip
    return w
