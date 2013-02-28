#include"VU_svdUtils.h"
/* for SVD Givens Coefficients are only calculated for real numbers */
givensObj_f givensCoef_f(vsip_scalar_f x1, vsip_scalar_f x2)
{
    givensObj_f retval;
    vsip_scalar_f t = vsip_hypot_f(x1,x2);
    if (x2 == 0.0){
        retval.c=1.0;retval.s=0.0;retval.r=x1;
    } else if (x1 == 0.0) {
        retval.c=0.0;retval.s=sign_f(x2);retval.r=t;
    }else{
        vsip_scalar_f sn = sign_f(x1);
        retval.c=vsip_mag_f(x1)/t;retval.s=sn*x2/t; retval.r=sn*t;
    }
    return retval;
}
givensObj_d givensCoef_d(vsip_scalar_d x1, vsip_scalar_d x2)
{
    givensObj_d retval;
    vsip_scalar_d t = vsip_hypot_d(x1,x2);
    if (x2 == 0.0){
        retval.c=1.0;retval.s=0.0;retval.r=x1;
    } else if (x1 == 0.0) {
        retval.c=0.0;retval.s=sign_d(x2);retval.r=t;
    }else{
        vsip_scalar_d sn = sign_d(x1);
        retval.c=vsip_mag_d(x1)/t;retval.s=sn * x2/t; retval.r=sn*t;
    }
    return retval;
}
svdCorner svdCorners_f(vsip_vview_f* f)
{
    svdCorner crnr;
    vsip_index j=vsip_vgetlength_f(f)-1;
    vsip_index i;
    while((j > 0) && (vsip_vget_f(f,j) == 0.0))
        j-=1;
    if(j == 0 && vsip_vget_f(f,0) == 0.0){
        crnr.i=0;
        crnr.j=0;
    } else {
        i = j;
        j += 1;
        while((i > 0) && (vsip_vget_f(f,i) != 0.0))
            i -= 1;
        if((i == 0) && (vsip_vget_f(f,0)== 0.0)){
            crnr.i=1;
            crnr.j=j+1;
        } else if (i==0){
            crnr.i=0;
            crnr.j=j+1;
        } else {
            crnr.i=i+1;
            crnr.j=j+1;
        }
    }
    return crnr;
}
svdCorner svdCorners_d(vsip_vview_d* f)
{
    svdCorner crnr;
    vsip_index j=vsip_vgetlength_d(f)-1;
    vsip_index i;
    while((j > 0) && (vsip_vget_d(f,j) == 0.0))
        j-=1;
    if(j == 0 && vsip_vget_d(f,0) == 0.0){
        crnr.i=0;
        crnr.j=0;
    } else {
        i = j;
        j += 1;
        while((i > 0) && (vsip_vget_d(f,i) != 0.0))
            i -= 1;
        if((i == 0) && (vsip_vget_d(f,0)== 0.0)){
            crnr.i=1;
            crnr.j=j+1;
        } else if (i==0){
            crnr.i=0;
            crnr.j=j+1;
        } else {
            crnr.i=i+1;
            crnr.j=j+1;
        }
    }
    return crnr;
}
void phaseCheck_f(vsip_mview_f* L,vsip_vview_f* d,vsip_vview_f* f,vsip_mview_f* R,vsip_scalar_f eps0)
{
    biDiagPhaseToZero_f(L,d,f,R,eps0);
}
void cphaseCheck_f(vsip_cmview_f* L, vsip_vview_f* d, vsip_vview_f* f,vsip_cmview_f* R, vsip_scalar_f eps0)
{
   vsip_length nf=vsip_vgetlength_f(f);
   vsip_index i,j;
   vsip_scalar_f ps;
   vsip_scalar_f m;
   vsip_cvview_f *l = vsip_cmcolview_f(L,0);
   vsip_cvview_f *r = vsip_cmrowview_f(R,0);
   for(i=0; i<vsip_vgetlength_f(d); i++){
        ps=vsip_vget_f(d,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        if(m > eps0){
            ccol_sv_f(L,l,i);vsip_rscvmul_f(ps,l,l);
            vsip_vput_f(d,i,m);
            if (i < nf)
                vsip_vput_f(f,i,ps*vsip_vget_f(f,i));
        } else {
            vsip_vput_f(d,i,0.0);
        }
    }
    svdZeroCheckAndSet_f(eps0,d,f);          
    for (i=0; i<nf-1; i++){
        j=i+1;
        ps = vsip_vget_f(f,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        ccol_sv_f(L, l, j);vsip_rscvmul_f(ps,l,l);
        crow_sv_f(R,r,j);vsip_rscvmul_f(ps,r,r);
        vsip_vput_f(f,i,m);
        vsip_vput_f(f,j,ps * vsip_vget_f(f,j));
    }
    j=nf;
    i=j-1;
    ps=vsip_vget_f(f,i);
    m=vsip_mag_f(ps);
    ps=sign_f(ps);
    vsip_vput_f(f,i,m);
    ccol_sv_f(L, l, j);vsip_rscvmul_f(ps,l,l);
    crow_sv_f(R,r,j);vsip_rscvmul_f(ps,r,r);
}
void phaseCheck_d(vsip_mview_d* L,vsip_vview_d* d,vsip_vview_d* f,vsip_mview_d* R,vsip_scalar_d eps0)
{
    biDiagPhaseToZero_d(L,d,f,R,eps0);
}
void cphaseCheck_d(vsip_cmview_d* L, vsip_vview_d* d, vsip_vview_d* f,vsip_cmview_d* R, vsip_scalar_d eps0)
{
   vsip_length nf=vsip_vgetlength_d(f);
   vsip_index i,j;
   vsip_scalar_d ps;
   vsip_scalar_d m;
   vsip_cvview_d *l = vsip_cmcolview_d(L,0);
   vsip_cvview_d *r = vsip_cmrowview_d(R,0);
   for(i=0; i<vsip_vgetlength_d(d); i++){
        ps=vsip_vget_d(d,i);
        m = vsip_mag_f(ps);
        ps=sign_d(ps);
        if(m > eps0){
            ccol_sv_d(L,l,i);vsip_rscvmul_d(ps,l,l);
            vsip_vput_d(d,i,m);
            if (i < nf)
                vsip_vput_d(f,i,ps*vsip_vget_d(f,i));
        } else {
            vsip_vput_d(d,i,0.0);
        }
    }
    svdZeroCheckAndSet_d(eps0,d,f);          
    for (i=0; i<nf-1; i++){
        j=i+1;
        ps = vsip_vget_d(f,i);
        m = vsip_mag_d(ps);
        ps=sign_d(ps);
        ccol_sv_d(L, l, j);vsip_rscvmul_d(ps,l,l);
        crow_sv_d(R,r,j);vsip_rscvmul_d(ps,r,r);
        vsip_vput_d(f,i,m);
        vsip_vput_d(f,j,ps * vsip_vget_d(f,j));
    }
    j=nf;
    i=j-1;
    ps=vsip_vget_d(f,i);
    m=vsip_mag_d(ps);
    ps=sign_d(ps);
    vsip_vput_d(f,i,m);
    ccol_sv_d(L, l, j);vsip_rscvmul_d(ps,l,l);
    crow_sv_d(R,r,j);vsip_rscvmul_d(ps,r,r);
}
vsip_index zeroFind_f(vsip_vview_f* d, vsip_scalar_f eps0){
    vsip_index j = vsip_vgetlength_f(d);
    vsip_scalar_f xd=vsip_vget_f(d,j-1);
    while(xd > eps0){
        if (j > 1){ 
            j -= 1;
            xd=vsip_vget_f(d,j-1);
        }else{
            break;
        }
    }
    if(xd <= eps0)
        vsip_vput_f(d,j-1,0.0);
    if (j == 1)
        j=0;
    return j;
}

vsip_index zeroFind_d(vsip_vview_d* d, vsip_scalar_d eps0){
    vsip_index j = vsip_vgetlength_d(d);
    vsip_scalar_d xd=vsip_vget_d(d,j-1);
    while(xd > eps0){
        if (j > 1){ 
            j -= 1;
            xd=vsip_vget_d(d,j-1);
        }else{
            break;
        }
    }
    if(xd <= eps0)
        vsip_vput_d(d,j-1,0.0);
    if (j == 1)
        j=0;
    return j;
}

void zeroRow_f(vsip_mview_f* L,vsip_vview_f *d,vsip_vview_f *f)
{
    vsip_length n = vsip_vgetlength_f(d);
    givensObj_f g;
    vsip_scalar_f xd,xf,t;
    vsip_index i;
    xd=vsip_vget_f(d,0);
    xf=vsip_vget_f(f,0);
    g=givensCoef_f(xd,xf);
    if (n == 1){
        vsip_vput_f(f,0,0.0);
        vsip_vput_f(d,0,g.r);
    }else{
        vsip_vput_f(f,0,0.0);
        vsip_vput_f(d,0,g.r);
        xf=vsip_vget_f(f,1);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_f(f,1,xf);
        prodG_f(L,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=vsip_vget_f(d,i);
            g=givensCoef_f(xd,t);
            prodG_f(L,i+1,0,g.c,g.s);
            vsip_vput_f(d,i,g.r);
            xf=vsip_vget_f(f,i+1);
            t=-xf * g.s; xf *= g.c;
            vsip_vput_f(f,i+1,xf);
        }
        xd=vsip_vget_f(d,n-1);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,n-1,g.r);
        prodG_f(L,n,0,g.c,g.s);
    }
}
void zeroCol_f(vsip_vview_f *d,vsip_vview_f *f, vsip_mview_f* R)
{
    vsip_length n = vsip_vgetlength_f(f);
    givensObj_f g;
    vsip_scalar_f xd,xf,t;
    vsip_index i,j,k;
    if (n == 1){
        xd=vsip_vget_f(d,0);
        xf=vsip_vget_f(f,0);
        g=givensCoef_f(xd,xf);
        vsip_vput_f(d,0,g.r);
        vsip_vput_f(f,0,0.0);
        gtProd_f(0,1,g.c,g.s,R);
    }else if (n == 2){
        xd=vsip_vget_f(d,1);
        xf=vsip_vget_f(f,1);
        g=givensCoef_f(xd,xf);
        vsip_vput_f(d,1,g.r);
        vsip_vput_f(f,1,0.0);
        xf=vsip_vget_f(f,0);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_f(f,0,xf);
        gtProd_f(1,2,g.c,g.s,R);
        xd=vsip_vget_f(d,0);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,0,g.r);
        gtProd_f(0,2,g.c,g.s,R);
    }else{
        i=n-1; j=i-1; k=i;
        xd=vsip_vget_f(d,i);
        xf=vsip_vget_f(f,i);
        g=givensCoef_f(xd,xf);
        xf=vsip_vget_f(f,j);
        vsip_vput_f(f,i,0.0);
        vsip_vput_f(d,i,g.r);
        t=-xf*g.s; xf*=g.c;
        vsip_vput_f(f,j,xf);
        gtProd_f(i,k+1,g.c,g.s,R);
        while (i > 1){
            i = j; j = i-1;
            xd=vsip_vget_f(d,i);
            g=givensCoef_f(xd,t);
            vsip_vput_f(d,i,g.r);
            xf=vsip_vget_f(f,j);
            t= -xf * g.s; xf *= g.c;
            vsip_vput_f(f,j,xf);
            gtProd_f(i,k+1,g.c,g.s,R);
        }
        xd=vsip_vget_f(d,0);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,0,g.r);
        gtProd_f(0,k+1,g.c,g.s,R);
    }
}
void zeroRow_d(vsip_mview_d* L,vsip_vview_d *d,vsip_vview_d *f)
{
}
void zeroCol_d(vsip_vview_d *d,vsip_vview_d *f, vsip_mview_d* R)
{
}
void czeroRow_f(vsip_cmview_f* L,vsip_vview_f *d,vsip_vview_f *f)
{
}
void czeroCol_f(vsip_vview_f *d,vsip_vview_f *f, vsip_cmview_f* R)
{
}
void czeroRow_d(vsip_cmview_d* L,vsip_vview_d *d,vsip_vview_d *f)
{
}
void czeroCol_d(vsip_vview_d *d,vsip_vview_d *f, vsip_cmview_d* R)
{
}
vsip_scalar_f svdMu_f(vsip_scalar_f d2,vsip_scalar_f f1,vsip_scalar_f d3,vsip_scalar_f f2)
{
    vsip_scalar_f mu;
    vsip_scalar_f cu=d2 * d2 + f1 * f1;
    vsip_scalar_f cl=d3 * d3 + f2 * f2;
    vsip_scalar_f cd = d2 * f2;
    vsip_scalar_f D = (cu * cl - cd * cd);
    vsip_scalar_f T = (cu + cl);
    vsip_scalar_f root = vsip_sqrt_f(T*T - 4 * D);
    vsip_scalar_f lambda1 = (T + root)/(2.); 
    vsip_scalar_f lambda2 = (T - root)/(2.);
    if(vsip_mag_f(lambda1 - cl) < vsip_mag_f(lambda2 - cl))
        mu = lambda1;
    else
        mu = lambda2;
    return mu;
}
vsip_scalar_d svdMu_d(vsip_scalar_d d2,vsip_scalar_d f1,vsip_scalar_d d3,vsip_scalar_d f2)
{
    vsip_scalar_d mu;
    vsip_scalar_d cu=d2 * d2 + f1 * f1;
    vsip_scalar_d cl=d3 * d3 + f2 * f2;
    vsip_scalar_d cd = d2 * f2;
    vsip_scalar_d D = (cu * cl - cd * cd);
    vsip_scalar_d T = (cu + cl);
    vsip_scalar_d root = vsip_sqrt_d(T*T - 4 * D);
    vsip_scalar_d lambda1 = (T + root)/(2.); 
    vsip_scalar_d lambda2 = (T - root)/(2.);
    if(vsip_mag_d(lambda1 - cl) < vsip_mag_d(lambda2 - cl))
        mu = lambda1;
    else
        mu = lambda2;
    return mu;
}

void gtProd_f(vsip_index i, vsip_index j, vsip_scalar_f c,vsip_scalar_f s, vsip_mview_f* R)
{
    vsip_vview_f *a1= vsip_mrowview_f(R,i);
    vsip_vview_f *a2= vsip_mrowview_f(R,j);
    vsip_vview_f *a1c=vclone_f(a1);
    vsip_vview_f *a2c=vclone_f(a2);
    vsip_svmul_f(c,a1c,a1); vsip_vsma_f(a2c,s,a1,a1); 
    vsip_svmul_f(c,a2c,a2); vsip_vsma_f(a1c,-s,a2,a2);
    vsip_vdestroy_f(a1);vsip_vdestroy_f(a2);
    vsip_valldestroy_f(a1c); vsip_valldestroy_f(a2c);
}
void gtProd_d(vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s,vsip_mview_d*R)
{
    vsip_vview_d *a1= vsip_mrowview_d(R,i);
    vsip_vview_d *a2= vsip_mrowview_d(R,j);
    vsip_vview_d *a1c=vclone_d(a1);
    vsip_vview_d *a2c=vclone_d(a2);
    vsip_svmul_d(c,a1c,a1); vsip_vsma_d(a2c,s,a1,a1); 
    vsip_svmul_d(c,a2c,a2); vsip_vsma_d(a1c,-s,a2,a2);
    vsip_vdestroy_d(a1);vsip_vdestroy_d(a2);
    vsip_valldestroy_d(a1c); vsip_valldestroy_d(a2c);
}
void cgtProd_f(vsip_index i, vsip_index j,vsip_scalar_f c, vsip_scalar_f s,vsip_cmview_f*R)
{
    vsip_cvview_f *a1= vsip_cmrowview_f(R,i);
    vsip_cvview_f *a2= vsip_cmrowview_f(R,j);
    vsip_cvview_f *a1c=cvclone_f(a1);
    vsip_cvview_f *a2c=cvclone_f(a2);
    vsip_rscvmul_f(c,a1c,a1);  vsip_rscvmul_f(c,a2c,a2);
    vsip_rscvmul_f(s,a2c,a2c); vsip_rscvmul_f(-s,a1c,a1c);
    vsip_cvadd_f(a1,a2c,a1); vsip_cvadd_f(a2,a1c,a2);
    vsip_cvdestroy_f(a1);vsip_cvdestroy_f(a2);
    vsip_cvalldestroy_f(a1c); vsip_cvalldestroy_f(a2c);
}
void cgtProd_d(vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s,vsip_cmview_d*R)
{
    vsip_cvview_d *a1= vsip_cmrowview_d(R,i);
    vsip_cvview_d *a2= vsip_cmrowview_d(R,j);
    vsip_cvview_d *a1c=cvclone_d(a1);
    vsip_cvview_d *a2c=cvclone_d(a2);
    vsip_rscvmul_d(c,a1c,a1);  vsip_rscvmul_d(c,a2c,a2);
    vsip_rscvmul_d(s,a2c,a2c); vsip_rscvmul_d(-s,a1c,a1c);
    vsip_cvadd_d(a1,a2c,a1); vsip_cvadd_d(a2,a1c,a2);
    vsip_cvdestroy_d(a1);vsip_cvdestroy_d(a2);
    vsip_cvalldestroy_d(a1c); vsip_cvalldestroy_d(a2c);
}

void prodG_f(vsip_mview_f* L,vsip_index i, vsip_index j,vsip_scalar_f c, vsip_scalar_f s)
{
    vsip_vview_f *a1= vsip_mcolview_f(L,i);
    vsip_vview_f *a2= vsip_mcolview_f(L,j);
    vsip_vview_f *a1c=vclone_f(a1);
    vsip_vview_f *a2c=vclone_f(a2);
    vsip_svmul_f(c,a1c,a1); vsip_vsma_f(a2,s,a1,a1);
    vsip_svmul_f(c,a2c,a2); vsip_vsma_f(a1c,-s,a2,a2);
    vsip_vdestroy_f(a1);vsip_vdestroy_f(a2);
    vsip_valldestroy_f(a1c); vsip_valldestroy_f(a2c);
}
void prodG_d(vsip_mview_d* L,vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s)
{
    vsip_vview_d *a1= vsip_mcolview_d(L,i);
    vsip_vview_d *a2= vsip_mcolview_d(L,j);
    vsip_vview_d *a1c=vclone_d(a1);
    vsip_vview_d *a2c=vclone_d(a2);
    vsip_svmul_d(c,a1c,a1); vsip_vsma_d(a2,s,a1,a1);
    vsip_svmul_d(c,a2c,a2); vsip_vsma_d(a1c,-s,a2,a2);
    vsip_vdestroy_d(a1);vsip_vdestroy_d(a2);
    vsip_valldestroy_d(a1c); vsip_valldestroy_d(a2c);
}
void cprodG_f(vsip_cmview_f* L,vsip_index i, vsip_index j,vsip_scalar_f c, vsip_scalar_f s)
{
    vsip_cvview_f *a1= vsip_cmcolview_f(L,i);
    vsip_cvview_f *a2= vsip_cmcolview_f(L,j);
    vsip_cvview_f *a1c=cvclone_f(a1);
    vsip_cvview_f *a2c=cvclone_f(a2);
    vsip_rscvmul_f(c,a1c,a1); vsip_rscvmul_f(-s,a1c,a1c);
    vsip_rscvmul_f(c,a2c,a2); vsip_rscvmul_f(s,a2c,a2c);
    vsip_cvadd_f(a1,a2c,a1); vsip_cvadd_f(a2,a1c,a2);
    vsip_cvdestroy_f(a1);vsip_cvdestroy_f(a2);
    vsip_cvalldestroy_f(a1c); vsip_cvalldestroy_f(a2c);
}
void cprodG_d(vsip_cmview_d* L,vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s)
{
    vsip_cvview_d *a1= vsip_cmcolview_d(L,i);
    vsip_cvview_d *a2= vsip_cmcolview_d(L,j);
    vsip_cvview_d *a1c=cvclone_d(a1);
    vsip_cvview_d *a2c=cvclone_d(a2);
    vsip_rscvmul_d(c,a1c,a1); vsip_rscvmul_d(-s,a1c,a1c);
    vsip_rscvmul_d(c,a2c,a2); vsip_rscvmul_d(s,a2c,a2c);
    vsip_cvadd_d(a1,a2c,a1); vsip_cvadd_d(a2,a1c,a2);
    vsip_cvdestroy_d(a1);vsip_cvdestroy_d(a2);
    vsip_cvalldestroy_d(a1c); vsip_cvalldestroy_d(a2c);
}

void svdStep_f(vsip_mview_f* L, vsip_vview_f* d, vsip_vview_f* f, vsip_mview_f *R)
{
    givensObj_f g;
    vsip_length n = vsip_vgetlength_f(d);
    vsip_scalar_f mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_f t=0.0;
    vsip_index i,j,k;
    vsip_scalar_f d2,f1,d3,f2;  
    if(n >= 3){
        d2=vsip_vget_f(d,n-2);f1= vsip_vget_f(f,n-3);d3 = vsip_vget_f(d,n-1);f2= vsip_vget_f(f,n-2);
    } else if(n == 2){
        d2=vsip_vget_f(d,0);f1= 0.0;d3 = vsip_vget_f(d,1);f2= vsip_vget_f(f,0);
    } else {
        d2=vsip_vget_f(d,0);f1 = 0.0;d3 = 0.0;f2 = 0.0;   
    }
    mu = svdMu_f(d2,f1,d3,f2);
    x1=vsip_vget_f(d,0);
    x2 = x1 * vsip_vget_f(f,0); 
    x1 *= x1; x1 -= mu;   
    g=givensCoef_f(x1,x2);
    x1=vsip_vget_f(d,0);x2=vsip_vget_f(f,0);
    vsip_vput_f(f,0,g.c * x2 - g.s * x1);
    vsip_vput_f(d,0,x1 * g.c + x2 * g.s); 
    t=vsip_vget_f(d,1); vsip_vput_f(d,1,t*g.c);
    t*=g.s;
    gtProd_f(0,1,g.c,g.s,R);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_f(vsip_vget_f(d,i),t);
        vsip_vput_f(d,i,g.r);      
        x1=vsip_vget_f(d,j)*g.c; 
        x2=vsip_vget_f(f,i)*g.s;
        t= x1 - x2;       
        x1=vsip_vget_f(f,i) * g.c;
        x2=vsip_vget_f(d,j) * g.s ;      
        vsip_vput_f(f,i,x1+x2);
        vsip_vput_f(d,j,t);       
        x1=vsip_vget_f(f,j);
        t=g.s * x1; 
        vsip_vput_f(f,j, x1*g.c);
        prodG_f(L,i, j, g.c, g.s);
        g=givensCoef_f(vsip_vget_f(f,i),t);
        vsip_vput_f(f,i,g.r);
        x1=vsip_vget_f(d,j); x2=vsip_vget_f(f,j);
        vsip_vput_f(d,j,g.c * x1 + g.s * x2); vsip_vput_f(f,j,g.c * x2 - g.s * x1);
        x1=vsip_vget_f(d,k);
        t=g.s * x1; vsip_vput_f(d,k,x1*g.c);
        gtProd_f(j,k, g.c, g.s,R);
    }
    i=n-2; j=n-1;
    g = givensCoef_f(vsip_vget_f(d,i),t);
    vsip_vput_f(d,i,g.r);
    x1=vsip_vget_f(d,j)*g.c; x2=vsip_vget_f(f,i)*g.s;
    t=x1 - x2;
    x1 = vsip_vget_f(f,i) * g.c; x2=vsip_vget_f(d,j) * g.s;
    vsip_vput_f(f,i,x1+x2);
    vsip_vput_f(d,j,t);
    prodG_f(L,i, j, g.c, g.s);
}
void csvdStep_f(vsip_cmview_f* L, vsip_vview_f* d, vsip_vview_f* f, vsip_cmview_f *R)
{
    givensObj_f g;
    vsip_length n = vsip_vgetlength_f(d);
    vsip_scalar_f mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_f t=0.0;
    vsip_index i,j,k;
    vsip_scalar_f d2,f1,d3,f2;  
    if(n >= 3){
        d2=vsip_vget_f(d,n-2);f1= vsip_vget_f(f,n-3);d3 = vsip_vget_f(d,n-1);f2= vsip_vget_f(f,n-2);
    } else if(n == 2){
        d2=vsip_vget_f(d,0);f1= 0.0;d3 = vsip_vget_f(d,1);f2= vsip_vget_f(f,0);
    } else {
        d2=vsip_vget_f(d,0);f1 = 0.0;d3 = 0.0;f2 = 0.0;   
    }
    mu = svdMu_f(d2,f1,d3,f2);
    x1=vsip_vget_f(d,0);
    x2 = x1 * vsip_vget_f(f,0); 
    x1 *= x1; x1 -= mu;   
    g=givensCoef_f(x1,x2);
    x1=vsip_vget_f(d,0);x2=vsip_vget_f(f,0);
    vsip_vput_f(f,0,g.c * x2 - g.s * x1);
    vsip_vput_f(d,0,x1 * g.c + x2 * g.s); 
    t=vsip_vget_f(d,1); vsip_vput_f(d,1,t*g.c);
    t*=g.s;
    cgtProd_f(0,1,g.c,g.s,R);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_f(vsip_vget_f(d,i),t);
        vsip_vput_f(d,i,g.r);      
        x1=vsip_vget_f(d,j)*g.c; 
        x2=vsip_vget_f(f,i)*g.s;
        t= x1 - x2;       
        x1=vsip_vget_f(f,i) * g.c;
        x2=vsip_vget_f(d,j) * g.s ;      
        vsip_vput_f(f,i,x1+x2);
        vsip_vput_f(d,j,t);       
        x1=vsip_vget_f(f,j);
        t=g.s * x1; 
        vsip_vput_f(f,j, x1*g.c);
        cprodG_f(L,i, j, g.c, g.s);
        g=givensCoef_f(vsip_vget_f(f,i),t);
        vsip_vput_f(f,i,g.r);
        x1=vsip_vget_f(d,j); x2=vsip_vget_f(f,j);
        vsip_vput_f(d,j,g.c * x1 + g.s * x2); vsip_vput_f(f,j,g.c * x2 - g.s * x1);
        x1=vsip_vget_f(d,k);
        t=g.s * x1; vsip_vput_f(d,k,x1*g.c);
        cgtProd_f(j,k, g.c, g.s,R);
    }
    i=n-2; j=n-1;
    g = givensCoef_f(vsip_vget_f(d,i),t);
    vsip_vput_f(d,i,g.r);
    x1=vsip_vget_f(d,j)*g.c; x2=vsip_vget_f(f,i)*g.s;
    t=x1 - x2;
    x1 = vsip_vget_f(f,i) * g.c; x2=vsip_vget_f(d,j) * g.s;
    vsip_vput_f(f,i,x1+x2);
    vsip_vput_f(d,j,t);
    cprodG_f(L,i, j, g.c, g.s);
}
void svdStep_d(vsip_mview_d* L, vsip_vview_d* d, vsip_vview_d* f, vsip_mview_d *R)
{
    givensObj_d g;
    vsip_length n = vsip_vgetlength_d(d);
    vsip_scalar_d mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_d t=0.0;
    vsip_index i,j,k;
    vsip_scalar_d d2,f1,d3,f2;  
    if(n >= 3){
        d2=vsip_vget_d(d,n-2);f1= vsip_vget_d(f,n-3);d3 = vsip_vget_d(d,n-1);f2= vsip_vget_d(f,n-2);
    } else if(n == 2){
        d2=vsip_vget_d(d,0);f1= 0.0;d3 = vsip_vget_d(d,1);f2= vsip_vget_d(f,0);
    } else {
        d2=vsip_vget_d(d,0);f1 = 0.0;d3 = 0.0;f2 = 0.0;   
    }
    mu = svdMu_d(d2,f1,d3,f2);
    x1=vsip_vget_d(d,0);
    x2 = x1 * vsip_vget_d(f,0); 
    x1 *= x1; x1 -= mu;   
    g=givensCoef_d(x1,x2);
    x1=vsip_vget_d(d,0);x2=vsip_vget_d(f,0);
    vsip_vput_d(f,0,g.c * x2 - g.s * x1);
    vsip_vput_d(d,0,x1 * g.c + x2 * g.s); 
    t=vsip_vget_d(d,1); vsip_vput_d(d,1,t*g.c);
    t*=g.s;
    gtProd_d(0,1,g.c,g.s,R);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_d(vsip_vget_d(d,i),t);
        vsip_vput_d(d,i,g.r);      
        x1=vsip_vget_d(d,j)*g.c; 
        x2=vsip_vget_d(f,i)*g.s;
        t= x1 - x2;       
        x1=vsip_vget_d(f,i) * g.c;
        x2=vsip_vget_d(d,j) * g.s ;      
        vsip_vput_d(f,i,x1+x2);
        vsip_vput_d(d,j,t);       
        x1=vsip_vget_d(f,j);
        t=g.s * x1; 
        vsip_vput_d(f,j, x1*g.c);
        prodG_d(L,i, j, g.c, g.s);
        g=givensCoef_d(vsip_vget_d(f,i),t);
        vsip_vput_d(f,i,g.r);
        x1=vsip_vget_d(d,j); x2=vsip_vget_d(f,j);
        vsip_vput_d(d,j,g.c * x1 + g.s * x2); vsip_vput_d(f,j,g.c * x2 - g.s * x1);
        x1=vsip_vget_d(d,k);
        t=g.s * x1; vsip_vput_d(d,k,x1*g.c);
        gtProd_d(j,k, g.c, g.s,R);
    }
    i=n-2; j=n-1;
    g = givensCoef_d(vsip_vget_d(d,i),t);
    vsip_vput_d(d,i,g.r);
    x1=vsip_vget_d(d,j)*g.c; x2=vsip_vget_d(f,i)*g.s;
    t=x1 - x2;
    x1 = vsip_vget_d(f,i) * g.c; x2=vsip_vget_d(d,j) * g.s;
    vsip_vput_d(f,i,x1+x2);
    vsip_vput_d(d,j,t);
    prodG_d(L,i, j, g.c, g.s);
}
void csvdStep_d(vsip_cmview_d* L, vsip_vview_d* d, vsip_vview_d* f, vsip_cmview_d *R)
{
    givensObj_d g;
    vsip_length n = vsip_vgetlength_d(d);
    vsip_scalar_d mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_d t=0.0;
    vsip_index i,j,k;
    vsip_scalar_d d2,f1,d3,f2;  
    if(n >= 3){
        d2=vsip_vget_d(d,n-2);f1= vsip_vget_d(f,n-3);d3 = vsip_vget_d(d,n-1);f2= vsip_vget_d(f,n-2);
    } else if(n == 2){
        d2=vsip_vget_d(d,0);f1= 0.0;d3 = vsip_vget_d(d,1);f2= vsip_vget_d(f,0);
    } else {
        d2=vsip_vget_d(d,0);f1 = 0.0;d3 = 0.0;f2 = 0.0;   
    }
    mu = svdMu_d(d2,f1,d3,f2);
    x1=vsip_vget_d(d,0);
    x2 = x1 * vsip_vget_d(f,0); 
    x1 *= x1; x1 -= mu;   
    g=givensCoef_d(x1,x2);
    x1=vsip_vget_d(d,0);x2=vsip_vget_d(f,0);
    vsip_vput_d(f,0,g.c * x2 - g.s * x1);
    vsip_vput_d(d,0,x1 * g.c + x2 * g.s); 
    t=vsip_vget_d(d,1); vsip_vput_d(d,1,t*g.c);
    t*=g.s;
    cgtProd_d(0,1,g.c,g.s,R);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_d(vsip_vget_d(d,i),t);
        vsip_vput_d(d,i,g.r);      
        x1=vsip_vget_d(d,j)*g.c; 
        x2=vsip_vget_d(f,i)*g.s;
        t= x1 - x2;       
        x1=vsip_vget_d(f,i) * g.c;
        x2=vsip_vget_d(d,j) * g.s ;      
        vsip_vput_d(f,i,x1+x2);
        vsip_vput_d(d,j,t);       
        x1=vsip_vget_d(f,j);
        t=g.s * x1; 
        vsip_vput_d(f,j, x1*g.c);
        cprodG_d(L,i, j, g.c, g.s);
        g=givensCoef_d(vsip_vget_d(f,i),t);
        vsip_vput_d(f,i,g.r);
        x1=vsip_vget_d(d,j); x2=vsip_vget_d(f,j);
        vsip_vput_d(d,j,g.c * x1 + g.s * x2); vsip_vput_d(f,j,g.c * x2 - g.s * x1);
        x1=vsip_vget_d(d,k);
        t=g.s * x1; vsip_vput_d(d,k,x1*g.c);
        cgtProd_d(j,k, g.c, g.s,R);
    }
    i=n-2; j=n-1;
    g = givensCoef_d(vsip_vget_d(d,i),t);
    vsip_vput_d(d,i,g.r);
    x1=vsip_vget_d(d,j)*g.c; x2=vsip_vget_d(f,i)*g.s;
    t=x1 - x2;
    x1 = vsip_vget_d(f,i) * g.c; x2=vsip_vget_d(d,j) * g.s;
    vsip_vput_d(f,i,x1+x2);
    vsip_vput_d(d,j,t);
    cprodG_d(L,i, j, g.c, g.s);
}

void svdIteration_f(vsip_mview_f* L0, vsip_vview_f* d0, vsip_vview_f* f0, vsip_mview_f* R0, vsip_scalar_f eps0)
{
    vsip_vview_f *d=vsip_vcloneview_f(d0);
    vsip_vview_f *f=vsip_vcloneview_f(f0);
    vsip_mview_f *L=vsip_mcloneview_f(L0);
    vsip_mview_f *R=vsip_mcloneview_f(R0);
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=20*vsip_vgetlength_f(d0);
    while (cntr++ < maxcntr){
        phaseCheck_f(L0,d0,f0,R0,eps0);
        cnr=svdCorners_f(f0);
        if (cnr.j == 0)
            break;
        ivsv_f(d0,d,cnr.i,cnr.j);
        ivsv_f(f0,f,cnr.i,cnr.j-1);
        imsv_f(L0,L,0,0,cnr.i,cnr.j);
        imsv_f(R0,R,cnr.i,cnr.j,0,0);
        n=vsip_vgetlength_f(f);
        k=zeroFind_f(d,eps0);
        if (k > 0){
            if(vsip_vget_f(d,n) == 0.0){
                zeroCol_f(d,f,R);
            }else{
                imsv_f(L,L,0,0,k-1,0);
                ivsv_f(d0,d,k,0);
                ivsv_f(f0,f,k-1,0);
                zeroRow_f(L,d,f);
            }
        }else{
            svdStep_f(L,d,f,R);
        }
    }
}
void svdIteration_d(vsip_mview_d* L0, vsip_vview_d* d0, vsip_vview_d* f0, vsip_mview_d* R0, vsip_scalar_d eps0)
{
    vsip_vview_d *d=vsip_vcloneview_d(d0);
    vsip_vview_d *f=vsip_vcloneview_d(f0);
    vsip_mview_d *L=vsip_mcloneview_d(L0);
    vsip_mview_d *R=vsip_mcloneview_d(R0);
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=20*vsip_vgetlength_d(d0);
    while (cntr++ < maxcntr){
        phaseCheck_d(L0,d0,f0,R0,eps0);
        cnr=svdCorners_d(f0);
        if (cnr.j == 0)
            break;
        ivsv_d(d0,d,cnr.i,cnr.j);
        ivsv_d(f0,f,cnr.i,cnr.j-1);
        imsv_d(L0,L,0,0,cnr.i,cnr.j);
        imsv_d(R0,R,cnr.i,cnr.j,0,0);
        n=vsip_vgetlength_d(f);
        k=zeroFind_d(d,eps0);
        if (k > 0){
            if(vsip_vget_d(d,n) == 0.0){
                zeroCol_d(d,f,R);
            }else{
                imsv_d(L,L,0,0,k-1,0);
                ivsv_d(d0,d,k,0);
                ivsv_d(f0,f,k-1,0);
                zeroRow_d(L,d,f);
            }
        }else{
            svdStep_d(L,d,f,R);
        }
    }
}
void csvdIteration_f(vsip_cmview_f* L0, vsip_vview_f* d0, vsip_vview_f* f0, vsip_cmview_f* R0, vsip_scalar_f eps0)
{
    vsip_vview_f *d=vsip_vcloneview_f(d0);
    vsip_vview_f *f=vsip_vcloneview_f(f0);
    vsip_cmview_f *L=vsip_cmcloneview_f(L0);
    vsip_cmview_f *R=vsip_cmcloneview_f(R0);
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=20*vsip_vgetlength_f(d0);
    while (cntr++ < maxcntr){
        cphaseCheck_f(L0,d0,f0,R0,eps0);
        cnr=svdCorners_f(f0);
        if (cnr.j == 0)
            break;
        ivsv_f(d0,d,cnr.i,cnr.j);
        ivsv_f(f0,f,cnr.i,cnr.j-1);
        cimsv_f(L0,L,0,0,cnr.i,cnr.j);
        cimsv_f(R0,R,cnr.i,cnr.j,0,0);
        n=vsip_vgetlength_f(f);
        k=zeroFind_f(d,eps0);
        if (k > 0){
            if(vsip_vget_f(d,n) == 0.0){
                czeroCol_f(d,f,R);
            }else{
                cimsv_f(L,L,0,0,k-1,0);
                ivsv_f(d0,d,k,0);
                ivsv_f(f0,f,k-1,0);
                czeroRow_f(L,d,f);
            }
        }else{
            csvdStep_f(L,d,f,R);
        }
    }
}
void csvdIteration_d(vsip_cmview_d* L0, vsip_vview_d* d0, vsip_vview_d* f0, vsip_cmview_d* R0, vsip_scalar_d eps0)
{
    vsip_vview_d *d=vsip_vcloneview_d(d0);
    vsip_vview_d *f=vsip_vcloneview_d(f0);
    vsip_cmview_d *L=vsip_cmcloneview_d(L0);
    vsip_cmview_d *R=vsip_cmcloneview_d(R0);
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=20*vsip_vgetlength_d(d0);
    while (cntr++ < maxcntr){
        cphaseCheck_d(L0,d0,f0,R0,eps0);
        cnr=svdCorners_d(f0);
        if (cnr.j == 0)
            break;
        ivsv_d(d0,d,cnr.i,cnr.j);
        ivsv_d(f0,f,cnr.i,cnr.j-1);
        cimsv_d(L0,L,0,0,cnr.i,cnr.j);
        cimsv_d(R0,R,cnr.i,cnr.j,0,0);
        n=vsip_vgetlength_d(f);
        k=zeroFind_d(d,eps0);
        if (k > 0){
            if(vsip_vget_d(d,n) == 0.0){
                czeroCol_d(d,f,R);
            }else{
                cimsv_d(L,L,0,0,k-1,0);
                ivsv_d(d0,d,k,0);
                ivsv_d(f0,f,k-1,0);
                czeroRow_d(L,d,f);
            }
        }else{
            csvdStep_d(L,d,f,R);
        }
    }
}

void svdSort_f(vsip_mview_f* L0,vsip_vview_f* d,vsip_mview_f* R0){
    vsip_length n=vsip_vgetlength_f(d);
    vsip_vview_vi* indx_L = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_vview_vi* indx_R = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_mview_f *L=vsip_mcloneview_f(L0);
    vsip_vsortip_f(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vsip_vcopy_vi_vi(indx_L,indx_R);
    imsv_f( L0, L, 0,0, 0, n);
    vsip_mpermute_once_f(L,VSIP_COL,indx_L,L);
    vsip_mpermute_once_f(R0,VSIP_ROW,indx_R,R0);
    vsip_valldestroy_vi(indx_L);
    vsip_valldestroy_vi(indx_R);
    vsip_mdestroy_f(L);   
}
void csvdSort_f(vsip_cmview_f* L0,vsip_vview_f* d,vsip_cmview_f* R0){
    vsip_length n=vsip_vgetlength_f(d);
    vsip_vview_vi* indx_L = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_vview_vi* indx_R = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_cmview_f *L=vsip_cmcloneview_f(L0);
    vsip_vsortip_f(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vsip_vcopy_vi_vi(indx_L,indx_R);
    cimsv_f( L0, L, 0,0, 0, n);
    vsip_cmpermute_once_f(L,VSIP_COL,indx_L,L);
    vsip_cmpermute_once_f(R0,VSIP_ROW,indx_R,R0);
    vsip_valldestroy_vi(indx_L);
    vsip_valldestroy_vi(indx_R);
    vsip_cmdestroy_f(L);
}
void svdSort_d(vsip_mview_d* L0,vsip_vview_d* d,vsip_mview_d* R0){
    vsip_length n=vsip_vgetlength_d(d);
    vsip_vview_vi* indx_L = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_vview_vi* indx_R = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_mview_d *L=vsip_mcloneview_d(L0);
    vsip_vsortip_d(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vsip_vcopy_vi_vi(indx_L,indx_R);
    imsv_d( L0, L, 0,0, 0, n);
    vsip_mpermute_once_d(L,VSIP_COL,indx_L,L);
    vsip_mpermute_once_d(R0,VSIP_ROW,indx_R,R0);
    vsip_valldestroy_vi(indx_L);
    vsip_valldestroy_vi(indx_R);
    vsip_mdestroy_d(L);
}
void csvdSort_d(vsip_cmview_d* L0,vsip_vview_d* d,vsip_cmview_d* R0){
    vsip_length n=vsip_vgetlength_d(d);
    vsip_vview_vi* indx_L = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_vview_vi* indx_R = vsip_vcreate_vi(n,VSIP_MEM_NONE);
    vsip_cmview_d *L=vsip_cmcloneview_d(L0);
    vsip_vsortip_d(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vsip_vcopy_vi_vi(indx_L,indx_R);
    cimsv_d( L0, L, 0,0, 0, n);
    vsip_cmpermute_once_d(L,VSIP_COL,indx_L,L);
    vsip_cmpermute_once_d(R0,VSIP_ROW,indx_R,R0);
    vsip_valldestroy_vi(indx_L);
    vsip_valldestroy_vi(indx_R);
    vsip_cmdestroy_d(L);
}

svdObj_f svd_f(vsip_mview_f *A){
    svdObj_f svd = svdBidiag_f(A);
    svdIteration_f(svd.L,svd.d,svd.f,svd.R,svd.eps0);
    svdSort_f(svd.L,svd.d,svd.R);
    return svd;
}
csvdObj_f csvd_f(vsip_cmview_f *A){
    csvdObj_f svd = csvdBidiag_f(A);
    csvdIteration_f(svd.L,svd.d,svd.f,svd.R,svd.eps0);
    csvdSort_f(svd.L,svd.d,svd.R);
    return svd;
}
svdObj_d svd_d(vsip_mview_d *A){
    svdObj_d svd = svdBidiag_d(A);
    svdIteration_d(svd.L,svd.d,svd.f,svd.R,svd.eps0);
    svdSort_d(svd.L,svd.d,svd.R);
    return svd;
}
csvdObj_d csvd_d(vsip_cmview_d *A){
    csvdObj_d svd = csvdBidiag_d(A);
    csvdIteration_d(svd.L,svd.d,svd.f,svd.R,svd.eps0);
    csvdSort_d(svd.L,svd.d,svd.R);
    return svd;
}
