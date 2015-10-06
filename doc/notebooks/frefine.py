def frefine(a,rs):
    """
    % f = frefine(a,rs);
    % refine local minima and maxima of H using Newton's method
    % H  : H = a(1)+a(2)*cos(w)+...+a(n+1)*cos(n*w)
    % rs : initial values for the extrema of H
    % see also : frefine.m, frefine_e.m
    """ 
    w = rs.copy
    m = a.empty.ramp(0.0,1.0)
    for k in range(12):
        H = w.outer(m).cos.prod(a)
        H1 = (w.outer(m).sin.neg).prod(m * a);
        H2 = (w.outer(m).cos.neg).prod(m.copy.sq * a)
        w -= H1*H2.recip;
    return w
