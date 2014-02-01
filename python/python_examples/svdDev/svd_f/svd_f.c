/* Created RJudd March 2, 2013 */
/*********************************************************************
// This code includes                                                 /
// no warranty, express or implied, including the warranties          /
// of merchantability and fitness for a particular purpose.           /
// No person or entity                                                /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
#include"svd_f.h"

static vsip_vview_f *vsv_f(vsip_vview_f *v, vsip_vview_f *vs, vsip_index i)
{
     vsip_vattr_f attr;
     vsip_vgetattrib_f(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_vputattrib_f(vs,&attr);
     return vs;
}
static vsip_mview_f* msv_f(vsip_mview_f *B,vsip_mview_f *BS, vsip_index i,vsip_index j)
{
    vsip_mattr_f attr;
    vsip_mgetattrib_f(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_mputattrib_f(BS,&attr);
    return BS;
}
static vsip_mview_f* imsv_f( vsip_mview_f *B, vsip_mview_f *BS, vsip_index i1,vsip_index j1,
                                                                vsip_index i2, vsip_index j2)
{
    vsip_mattr_f attr;
    vsip_mgetattrib_f(B,&attr);
    if(j1 == 0) j1 =attr.col_length;
    if(j2 == 0) j2 =attr.row_length;
    attr.col_length = (j1 - i1);
    attr.row_length = (j2 - i2);
    attr.offset += i2 * attr.row_stride + i1 * attr.col_stride;
    vsip_mputattrib_f(BS,&attr);
    return BS;
}
static vsip_vview_f *ivsv_f( vsip_vview_f *v, vsip_vview_f *vs, vsip_index i,vsip_index j)
{
     vsip_vattr_f attr;
     vsip_vgetattrib_f(v,&attr);
     if(j==0) j=attr.length;
     attr.offset += i * attr.stride;
     attr.length = j-i;
     vsip_vputattrib_f(vs,&attr);
     return vs;
} /* same */
static vsip_vview_f *col_sv_f(vsip_mview_f*Am,vsip_vview_f* vv,vsip_index col)
{
    vsip_mattr_f A; vsip_vattr_f v;
    vsip_mgetattrib_f(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_vputattrib_f(vv,&v);
    return vv;
} 
static vsip_vview_f *row_sv_f(vsip_mview_f*Am,vsip_vview_f* vv,vsip_index row)
{
    vsip_mattr_f A; vsip_vattr_f v;
    vsip_mgetattrib_f(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_vputattrib_f(vv,&v);
    return vv;
}
static vsip_vview_f *diag_sv_f(vsip_mview_f* Am,vsip_vview_f* a, vsip_stride i)
{
    vsip_mattr_f A; vsip_vattr_f v;
    vsip_mgetattrib_f(Am,&A);
    vsip_vgetattrib_f(a,&v);
    v.stride=A.row_stride + A.col_stride;
    if(i==0){
       v.length = A.row_length;
       v.offset = A.offset;
    } else if (i == 1){
        v.offset = A.offset + A.row_stride;
        v.length = A.row_length - 1;
    } else {
        printf("Failed in diag_sv_f\n");
        exit(0);
    }
    vsip_vputattrib_f(a,&v);
    return a;
}
static vsip_vview_f* vclone_f(vsip_vview_f*x, vsip_vview_f *v)
{
    vsip_vputlength_f(v,vsip_vgetlength_f(x));
    vsip_vcopy_f_f(x,v);
    return v;
}

static vsip_scalar_f vnorm2_f(vsip_vview_f *v)
{
    return vsip_sqrt_f(vsip_vsumsqval_f(v));
} 
static vsip_scalar_f mnormFro_f(vsip_mview_f *v)
{
    return vsip_sqrt_f(vsip_msumsqval_f(v));
} 
static vsip_mview_f* meye_f(vsip_length n)
{
    vsip_vview_f *d = (vsip_vview_f*) NULL;
    vsip_mview_f *retval = (vsip_mview_f*)NULL;
    retval = vsip_mcreate_f(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval) d = vsip_mdiagview_f(retval,0);
    if(d){
        vsip_mfill_f(0.0,retval);
        vsip_vfill_f(1.0,d);
        vsip_vdestroy_f(d);
    } else {
        vsip_malldestroy_f(retval);
        retval = (vsip_mview_f*) NULL;
    }
    return retval;
}

static void svdZeroCheckAndSet_f(vsip_scalar_f e, vsip_vview_f *b0, vsip_vview_f *b1)
{
    vsip_index i;
    vsip_length n = vsip_vgetlength_f(b1);
    vsip_scalar_f z = 0.0;
    for(i=0; i<n; i++){
        vsip_scalar_f b = vsip_mag_f(vsip_vget_f(b1,i));
        vsip_scalar_f a = e*(vsip_mag_f(vsip_vget_f(b0,i))
                        +    vsip_mag_f(vsip_vget_f(b0,i+1)));
        if( b < a ) vsip_vput_f(b1,i,z);
    }
}  /* same */

/* sign function as defined in http://www.netlib.org/lapack/lawnspdf/lawn148.pdf */
static vsip_scalar_f sign_f(vsip_scalar_f a_in)
{
    if(a_in < 0.0)
       return -1.0;
    else 
       return 1.0;
} /* same */
static void biDiagPhaseToZero_f( svdObj_f *svd)
{
    vsip_mview_f *L = svd->L;
    vsip_vview_f *d = svd->d;
    vsip_vview_f *f = svd->f;
    vsip_mview_f *R = svd->R;
    vsip_scalar_f eps0 = svd->eps0;
    vsip_length n_d=vsip_vgetlength_f(d);
    vsip_length n_f=vsip_vgetlength_f(f);
    vsip_index i,j;
    vsip_scalar_f ps;
    vsip_scalar_f m;
    vsip_vview_f *l = svd->ls_one;
    vsip_vview_f *r = svd->rs_one;
    for(i=0; i<n_d; i++){
        ps=vsip_vget_f(d,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        if(m > eps0){
            col_sv_f(L,l,i);vsip_svmul_f(ps,l,l);
            vsip_vput_f(d,i,m);
            if (i < n_f)
                vsip_vput_f(f,i,ps*vsip_vget_f(f,i));
        } else {
            vsip_vput_f(d,i,0.0);
        }
    }
    svdZeroCheckAndSet_f(eps0,d,f);          
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = vsip_vget_f(f,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        col_sv_f(L, l, j);vsip_svmul_f(ps,l,l);
        row_sv_f(R,r,j);vsip_svmul_f(ps,r,r);
        vsip_vput_f(f,i,m);
        vsip_vput_f(f,j,ps * vsip_vget_f(f,j));
    }
    j=n_f;
    i=j-1;
    ps=vsip_vget_f(f,i);
    m=vsip_mag_f(ps);
    ps=sign_f(ps);
    vsip_vput_f(f,i,m);
    col_sv_f(L, l, j);vsip_svmul_f(ps,l,l);
    row_sv_f(R,r,j);vsip_svmul_f(ps,r,r);
} 
static void phaseCheck_f(svdObj_f *svd)
{
    biDiagPhaseToZero_f(svd);
} 

void houseProd_f(vsip_vview_f *v, vsip_mview_f *A)
{
    vsip_mattr_f a_atr; 
    vsip_vview_f *w;
    vsip_mview_f *B;
    vsip_mgetattrib_f(A,&a_atr);
    B=vsip_mcreate_f(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_vcreate_f(a_atr.row_length,VSIP_MEM_NONE);
    vsip_scalar_f beta = 2.0/vsip_vdot_f(v,v);
    vsip_vmprod_f(v,A,w);
    vsip_vouter_f(beta,v,w,B);
    vsip_msub_f(A,B,A);
    vsip_valldestroy_f(w);
    vsip_malldestroy_f(B);
} /* need to remove create */
void prodHouse_f(vsip_mview_f *A, vsip_vview_f *v)
{
    vsip_mattr_f a_atr; 
    vsip_vview_f *w;
    vsip_mview_f *B;
    vsip_mgetattrib_f(A,&a_atr);
    B=vsip_mcreate_f(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_vcreate_f(a_atr.col_length,VSIP_MEM_NONE);
    vsip_scalar_f beta = 2.0/vsip_vdot_f(v,v);
    vsip_mvprod_f(A,v,w);
    vsip_vouter_f(beta,w,v,B);
    vsip_msub_f(A,B,A);
    vsip_valldestroy_f(w);
    vsip_malldestroy_f(B);
} /* need to remove create */
static vsip_vview_f *houseVector_f(vsip_vview_f* x)
{
    vsip_scalar_f nrm=vnorm2_f(x);
    vsip_scalar_f t = vsip_vget_f(x,0);
    vsip_scalar_f s = t +  sign_f(t) * nrm;
    vsip_vput_f(x,0,s); 
    nrm = vnorm2_f(x);
    if (nrm == 0.0)
        vsip_vput_f(x,0,1.0); 
    else
        vsip_svmul_f(1.0/nrm,x,x);
    return x;
}
static void VHmatExtract_f(svdObj_f *svd)
{
    vsip_mview_f*B = svd->B;
    vsip_index i,j;
    vsip_length n = vsip_mgetrowlength_f(B);
    vsip_mview_f *Bs=svd->Bs;
    vsip_mview_f *V=svd->R;
    vsip_mview_f *Vs=svd->Rs;
    vsip_vview_f *v;
    vsip_scalar_f t;
    if(n < 3)
        return;
    v = row_sv_f(B,svd->bs,0);
    for(i=n-3; i>0; i--){
        j=i+1;
        row_sv_f(msv_f(B,Bs,i,j),v,0);
        t=vsip_vget_f(v,0);vsip_vput_f(v,0,1.0);
        prodHouse_f(msv_f(V,Vs,j,j),v);
        vsip_vput_f(v,0,t);
    }
    row_sv_f(msv_f(B,Bs,0,1),v,0);
    t=vsip_vget_f(v,0);vsip_vput_f(v,0,1.0);
    prodHouse_f(msv_f(V,Vs,1,1),v);
    vsip_vput_f(v,0,t);      
}
static void UmatExtract_f(svdObj_f *svd)
{
    vsip_mview_f* B=svd->B;
    vsip_mview_f *U=svd->L;
    vsip_index i;
    vsip_length m = vsip_mgetcollength_f(B);
    vsip_length n = vsip_mgetrowlength_f(B);
    vsip_mview_f *Bs=svd->Bs;
    vsip_mview_f *Us=svd->Ls;
    vsip_vview_f *v;
    vsip_scalar_f t;
    v = col_sv_f(B,svd->bs,0);
    if (m > n){
        i=n-1;
        col_sv_f(msv_f(B,Bs,i,i),v,0);
        t=vsip_vget_f(v,0); vsip_vput_f(v,0,1.0);
        houseProd_f(v,msv_f(U,Us,i,i));
        vsip_vput_f(v,0,t);
    }
    for(i=n-2; i>0; i--){
        col_sv_f(msv_f(B,Bs,i,i),v,0);
        t=vsip_vget_f(v,0); vsip_vput_f(v,0,1.0);
        houseProd_f(v,msv_f(U,Us,i,i));
        vsip_vput_f(v,0,t);
    }
    col_sv_f(msv_f(B,Bs,0,0),v,0);
    t=vsip_vget_f(v,0); vsip_vput_f(v,0,1.0);
    houseProd_f(v,msv_f(U,Us,0,0));
    vsip_vput_f(v,0,t);
}
static void bidiag_f(svdObj_f *svd)
{
    vsip_mview_f *B = svd->B; 
    vsip_mview_f *Bs = svd->Bs;
    vsip_length m = vsip_mgetcollength_f(B);
    vsip_length n = vsip_mgetrowlength_f(B);
    vsip_vview_f *x=col_sv_f(B,svd->bs,0);
    vsip_vview_f *v=vclone_f(x,svd->t);
    vsip_vview_f *vs = svd->ts;
    vsip_index i,j;
    for(i=0; i<n-1; i++){
        vsip_vputlength_f(v,m-i);
        vsip_vcopy_f_f(col_sv_f(msv_f(B,Bs,i,i),x,0),v);
        houseVector_f(v);
        vsip_svmul_f(1.0/vsip_vget_f(v,0),v,v);
        houseProd_f(v,Bs);
        vsip_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
        if(i < n-2){
            j = i+1;
            vsip_vputlength_f(v,n-j);
            vsip_vcopy_f_f(row_sv_f(msv_f(B,Bs,i,j),x,0),v);
            houseVector_f(v);
            vsip_svmul_f(1.0/vsip_vget_f(v,0),v,v);
            prodHouse_f(Bs,v);
            vsip_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_vputlength_f(v,m-i);
        vsip_vcopy_f_f(col_sv_f(msv_f(B,Bs,i,i),x,0),v);
        houseVector_f(v);
        vsip_svmul_f(1.0/vsip_vget_f(v,0),v,v);
        houseProd_f(v,Bs);
        vsip_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
    }
}
static void svdBidiag_f(svdObj_f *svd)
{
    vsip_mview_f *B = svd->B;
    /* eps0 is a number << maximum singular value */
    svd->eps0=mnormFro_f(B)/(vsip_scalar_f)vsip_mgetrowlength_f(B)*1E-10;
    bidiag_f(svd);
    UmatExtract_f(svd);
    VHmatExtract_f(svd);
    biDiagPhaseToZero_f(svd);
    vsip_vcopy_f_f(diag_sv_f(B,svd->bs,0),svd->d);
    vsip_vcopy_f_f(diag_sv_f(B,svd->bs,1),svd->f);
} 

static void gtProd_f(vsip_index i, vsip_index j, vsip_scalar_f c,vsip_scalar_f s, svdObj_f* svd)
{
    vsip_mview_f* R = svd->Rs;
    vsip_vview_f *a1= row_sv_f(R,svd->rs_one, i);
    vsip_vview_f *a2= row_sv_f(R,svd->rs_two, j);
    vsip_vview_f *a1c=vclone_f(a1,svd->t);
    vsip_svmul_f(c,a1c,a1); vsip_vsma_f(a2,s,a1,a1);
    vsip_svmul_f(-s,a1c,a1c); vsip_vsma_f(a2,c,a1c,a2); 
} 
static void prodG_f(svdObj_f* svd,vsip_index i, vsip_index j,vsip_scalar_f c, vsip_scalar_f s)
{
    vsip_mview_f* L = svd->Ls;
    vsip_vview_f *a1= col_sv_f(L,svd->ls_one,i);
    vsip_vview_f *a2= col_sv_f(L,svd->ls_two,j);
    vsip_vview_f *a1c=vclone_f(a1,svd->t);
    vsip_svmul_f(c,a1c,a1); vsip_vsma_f(a2,s,a1,a1);
    vsip_svmul_f(-s,a1c,a1c);vsip_vsma_f(a2,c,a1c,a2);
}
static givensObj_f givensCoef_f(vsip_scalar_f x1, vsip_scalar_f x2)
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
} /* same */

static void zeroCol_f(svdObj_f *svd)
{
    vsip_vview_f *d=svd->ds;
    vsip_vview_f *f=svd->fs;
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
        gtProd_f(0,1,g.c,g.s,svd);
    }else if (n == 2){
        xd=vsip_vget_f(d,1);
        xf=vsip_vget_f(f,1);
        g=givensCoef_f(xd,xf);
        vsip_vput_f(d,1,g.r);
        vsip_vput_f(f,1,0.0);
        xf=vsip_vget_f(f,0);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_f(f,0,xf);
        gtProd_f(1,2,g.c,g.s,svd);
        xd=vsip_vget_f(d,0);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,0,g.r);
        gtProd_f(0,2,g.c,g.s,svd);
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
        gtProd_f(i,k+1,g.c,g.s,svd);
        while (i > 1){
            i = j; j = i-1;
            xd=vsip_vget_f(d,i);
            g=givensCoef_f(xd,t);
            vsip_vput_f(d,i,g.r);
            xf=vsip_vget_f(f,j);
            t= -xf * g.s; xf *= g.c;
            vsip_vput_f(f,j,xf);
            gtProd_f(i,k+1,g.c,g.s,svd);
        }
        xd=vsip_vget_f(d,0);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,0,g.r);
        gtProd_f(0,k+1,g.c,g.s,svd);
    }
} 
static void zeroRow_f(svdObj_f *svd)
{
    vsip_vview_f *d = svd->ds;
    vsip_vview_f *f = svd->fs;
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
        prodG_f(svd,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=vsip_vget_f(d,i);
            g=givensCoef_f(xd,t);
            prodG_f(svd,i+1,0,g.c,g.s);
            vsip_vput_f(d,i,g.r);
            xf=vsip_vget_f(f,i+1);
            t=-xf * g.s; xf *= g.c;
            vsip_vput_f(f,i+1,xf);
        }
        xd=vsip_vget_f(d,n-1);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,n-1,g.r);
        prodG_f(svd,n,0,g.c,g.s);
    }
} 

static vsip_scalar_f svdMu_f(vsip_scalar_f d2,vsip_scalar_f f1,vsip_scalar_f d3,vsip_scalar_f f2)
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
} /* same */
static vsip_index zeroFind_f(vsip_vview_f* d, vsip_scalar_f eps0)
{
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
} /* same */
static svdCorner svdCorners_f(vsip_vview_f* f)
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
} /* same */

static void svdStep_f(svdObj_f *svd)
{
    vsip_vview_f *d = svd->ds;
    vsip_vview_f *f = svd->fs;
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
    gtProd_f(0,1,g.c,g.s,svd);
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
        prodG_f(svd,i, j, g.c, g.s);
        g=givensCoef_f(vsip_vget_f(f,i),t);
        vsip_vput_f(f,i,g.r);
        x1=vsip_vget_f(d,j); x2=vsip_vget_f(f,j);
        vsip_vput_f(d,j,g.c * x1 + g.s * x2); vsip_vput_f(f,j,g.c * x2 - g.s * x1);
        x1=vsip_vget_f(d,k);
        t=g.s * x1; vsip_vput_f(d,k,x1*g.c);
        gtProd_f(j,k, g.c, g.s,svd);
    }
    i=n-2; j=n-1;
    g = givensCoef_f(vsip_vget_f(d,i),t);
    vsip_vput_f(d,i,g.r);
    x1=vsip_vget_f(d,j)*g.c; x2=vsip_vget_f(f,i)*g.s;
    t=x1 - x2;
    x1 = vsip_vget_f(f,i) * g.c; x2=vsip_vget_f(d,j) * g.s;
    vsip_vput_f(f,i,x1+x2);
    vsip_vput_f(d,j,t);
    prodG_f(svd,i, j, g.c, g.s);
}
static void svdIteration_f(svdObj_f* svd)
{
    vsip_mview_f *L0 = svd->L; vsip_mview_f *L = svd->Ls;
    vsip_vview_f *d0 = svd->d; vsip_vview_f *d = svd->ds;
    vsip_vview_f *f0 = svd->f; vsip_vview_f *f = svd->fs;
    vsip_mview_f *R0 = svd->R; vsip_mview_f *R= svd->Rs;
    vsip_scalar_f eps0 = svd->eps0;
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=20*vsip_vgetlength_f(d0);
    while (cntr++ < maxcntr){
        phaseCheck_f(svd);
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
                zeroCol_f(svd);
            }else{
                imsv_f(L,L,0,0,k-1,0);
                ivsv_f(d0,d,k,0);
                ivsv_f(f0,f,k-1,0);
                zeroRow_f(svd);
            }
        }else{
            svdStep_f(svd);
        }
    }
}
static void svdSort_f(svdObj_f *svd)
{
    vsip_vview_f *d = svd->d;
    vsip_length n=vsip_vgetlength_f(d);
    vsip_vview_vi* indx_L = svd->indx_L;
    vsip_vview_vi* indx_R = svd->indx_R;
    vsip_mview_f *L0 = svd->L; vsip_mview_f *L=svd->Ls;
    vsip_mview_f *R0 = svd->R;
    vsip_vsortip_f(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vsip_vcopy_vi_vi(indx_L,indx_R);
    imsv_f( L0, L, 0,0, 0, n);
    vsip_mpermute_once_f(L,VSIP_COL,indx_L,L);
    vsip_mpermute_once_f(R0,VSIP_ROW,indx_R,R0);
}

svdObj_f* svdInit_f(vsip_length m, vsip_length n)
{
    svdObj_f *s=malloc(sizeof(svdObj_f));
    if(m < n){
        printf("Column length must not be less than row length");
        return NULL;
    }
    if(!s) {
        printf("\nfailed to allocate svd object\n");
        return NULL;
    }
    s->init=0;
    if(!(s->t = vsip_vcreate_f(m,VSIP_MEM_NONE))){
        s->ts = NULL; s->init++;
    } else {
        if(!(s->ts = vsip_vcloneview_f(s->t))) s->init++;
    }
    if(!(s->B=vsip_mcreate_f(m,n,VSIP_ROW,VSIP_MEM_NONE))){ 
        s->Bs = NULL; s->bs=NULL; s->init++;
    } else {
        if(!(s->Bs=vsip_mcloneview_f(s->B))) s->init++;
        if(!(s->bs=vsip_mrowview_f(s->B,0))) s->init++;
    }
    if(!(s->L=meye_f(m))){ 
        s->Ls=NULL; s->init++;
    } else {
        if(!(s->Ls = vsip_mcloneview_f(s->L))) s->init++;
        if(!(s->ls_two = vsip_mrowview_f(s->Ls,0))) s->init++;
        if(!(s->ls_one = vsip_mrowview_f(s->Ls,0))) s->init++;
    }
    if(!(s->R=meye_f(n))){
        s->Rs=NULL; s->init++;
    } else {
        if(!(s->Rs = vsip_mcloneview_f(s->R))) s->init++;
        if(!(s->rs_two = vsip_mrowview_f(s->Rs,0))) s->init++;
        if(!(s->rs_one = vsip_mrowview_f(s->Rs,0))) s->init++;
    }
    if(!(s->indx_L=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    if(!(s->indx_R=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    if(!(s->d = vsip_vcreate_f(n,VSIP_MEM_NONE))){
        s->init++; s->ds = NULL;
    } else { 
        if(!(s->ds = vsip_vcloneview_f(s->d))) s->init++;
    }
    if(!(s->f = vsip_vcreate_f(n-1,VSIP_MEM_NONE))){
        s->init++; s->fs = NULL;
    } else { 
        if(!(s->fs = vsip_vcloneview_f(s->f))) s->init++;
    }
    if(s->init) svdFinalize_f(s);
    return s;
}
void svdFinalize_f(svdObj_f *s)
{
    vsip_vdestroy_f(s->ts);
    vsip_valldestroy_f(s->t);
    vsip_vdestroy_f(s->rs_one);
    vsip_vdestroy_f(s->rs_two);
    vsip_mdestroy_f(s->Rs);
    vsip_vdestroy_f(s->ls_one);
    vsip_vdestroy_f(s->ls_two);
    vsip_mdestroy_f(s->Ls);
    vsip_mdestroy_f(s->Bs);
    vsip_vdestroy_f(s->bs);
    vsip_malldestroy_f(s->B);
    vsip_malldestroy_f(s->R);
    vsip_malldestroy_f(s->L);
    vsip_valldestroy_vi(s->indx_L);
    vsip_valldestroy_vi(s->indx_R);
    vsip_vdestroy_f(s->ds);
    vsip_valldestroy_f(s->d);
    vsip_vdestroy_f(s->fs);
    vsip_valldestroy_f(s->f);
    s=NULL;
}
svdObj_f *svd_f(vsip_mview_f *A)
{
    svdObj_f *svd = svdInit_f(vsip_mgetcollength_f(A),vsip_mgetrowlength_f(A));
    if(!svd){ printf("malloc failure for SVD"); exit(0);}
    vsip_mcopy_f_f(A,svd->B);
    svdBidiag_f(svd);
    svdIteration_f(svd);
    svdSort_f(svd);
    return svd;
}