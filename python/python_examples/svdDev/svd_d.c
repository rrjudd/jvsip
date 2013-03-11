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
#include"svd_d.h"

static vsip_vview_d *vsv_d(vsip_vview_d *v, vsip_vview_d *vs, vsip_index i)
{
     vsip_vattr_d attr;
     vsip_vgetattrib_d(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_vputattrib_d(vs,&attr);
     return vs;
}
static vsip_mview_d* msv_d(vsip_mview_d *B,vsip_mview_d *BS, vsip_index i,vsip_index j)
{
    vsip_mattr_d attr;
    vsip_mgetattrib_d(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_mputattrib_d(BS,&attr);
    return BS;
}
static vsip_mview_d* imsv_d( vsip_mview_d *B, vsip_mview_d *BS, vsip_index i1,vsip_index j1,
                                                                vsip_index i2, vsip_index j2)
{
    vsip_mattr_d attr;
    vsip_mgetattrib_d(B,&attr);
    if(j1 == 0) j1 =attr.col_length;
    if(j2 == 0) j2 =attr.row_length;
    attr.col_length = (j1 - i1);
    attr.row_length = (j2 - i2);
    attr.offset += i2 * attr.row_stride + i1 * attr.col_stride;
    vsip_mputattrib_d(BS,&attr);
    return BS;
}
static vsip_vview_d *ivsv_d( vsip_vview_d *v, vsip_vview_d *vs, vsip_index i,vsip_index j)
{
     vsip_vattr_d attr;
     vsip_vgetattrib_d(v,&attr);
     if(j==0) j=attr.length;
     attr.offset += i * attr.stride;
     attr.length = j-i;
     vsip_vputattrib_d(vs,&attr);
     return vs;
} /* same */
static vsip_vview_d *col_sv_d(vsip_mview_d*Am,vsip_vview_d* vv,vsip_index col)
{
    vsip_mattr_d A; vsip_vattr_d v;
    vsip_mgetattrib_d(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_vputattrib_d(vv,&v);
    return vv;
} 
static vsip_vview_d *row_sv_d(vsip_mview_d*Am,vsip_vview_d* vv,vsip_index row)
{
    vsip_mattr_d A; vsip_vattr_d v;
    vsip_mgetattrib_d(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_vputattrib_d(vv,&v);
    return vv;
}
static vsip_vview_d *diag_sv_d(vsip_mview_d* Am,vsip_vview_d* a, vsip_stride i)
{
    vsip_mattr_d A; vsip_vattr_d v;
    vsip_mgetattrib_d(Am,&A);
    vsip_vgetattrib_d(a,&v);
    v.stride=A.row_stride + A.col_stride;
    if(i==0){
       v.length = A.row_length;
       v.offset = A.offset;
    } else if (i == 1){
        v.offset = A.offset + A.row_stride;
        v.length = A.row_length - 1;
    } else {
        printf("Failed in diag_sv_d\n");
        exit(0);
    }
    vsip_vputattrib_d(a,&v);
    return a;
}
static vsip_vview_d* vclone_d(vsip_vview_d*x, vsip_vview_d *v)
{
    vsip_vputlength_d(v,vsip_vgetlength_d(x));
    vsip_vcopy_d_d(x,v);
    return v;
}

static vsip_scalar_d vnorm2_d(vsip_vview_d *v)
{
    return vsip_sqrt_d(vsip_vsumsqval_d(v));
} 
static vsip_scalar_d mnormFro_d(vsip_mview_d *v)
{
    return vsip_sqrt_d(vsip_msumsqval_d(v));
} 
static vsip_mview_d* meye_d(vsip_length n)
{
    vsip_vview_d *d = (vsip_vview_d*) NULL;
    vsip_mview_d *retval = (vsip_mview_d*)NULL;
    retval = vsip_mcreate_d(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval) d = vsip_mdiagview_d(retval,0);
    if(d){
        vsip_mfill_d(0.0,retval);
        vsip_vfill_d(1.0,d);
        vsip_vdestroy_d(d);
    } else {
        vsip_malldestroy_d(retval);
        retval = (vsip_mview_d*) NULL;
    }
    return retval;
}

static void svdZeroCheckAndSet_d(vsip_scalar_d e, vsip_vview_d *b0, vsip_vview_d *b1)
{
    vsip_index i;
    vsip_length n = vsip_vgetlength_d(b1);
    vsip_scalar_d z = 0.0;
    for(i=0; i<n; i++){
        vsip_scalar_d b = vsip_mag_d(vsip_vget_d(b1,i));
        vsip_scalar_d a = e*(vsip_mag_d(vsip_vget_d(b0,i))
                        +    vsip_mag_d(vsip_vget_d(b0,i+1)));
        if( b < a ) vsip_vput_d(b1,i,z);
    }
}  /* same */

/* sign function as defined in http://www.netlib.org/lapack/lawnspdf/lawn148.pdf */
static vsip_scalar_d sign_d(vsip_scalar_d a_in)
{
    if(a_in < 0.0)
       return -1.0;
    else 
       return 1.0;
} /* same */
static void biDiagPhaseToZero_d( svdObj_d *svd)
{
    vsip_mview_d *L = svd->L;
    vsip_vview_d *d = svd->d;
    vsip_vview_d *f = svd->f;
    vsip_mview_d *R = svd->R;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length n_d=vsip_vgetlength_d(d);
    vsip_length n_f=vsip_vgetlength_d(f);
    vsip_index i,j;
    vsip_scalar_d ps;
    vsip_scalar_d m;
    vsip_vview_d *l = svd->ls_one;
    vsip_vview_d *r = svd->rs_one;
    for(i=0; i<n_d; i++){
        ps=vsip_vget_d(d,i);
        m = vsip_mag_d(ps);
        ps=sign_d(ps);
        if(m > eps0){
            col_sv_d(L,l,i);vsip_svmul_d(ps,l,l);
            vsip_vput_d(d,i,m);
            if (i < n_f)
                vsip_vput_d(f,i,ps*vsip_vget_d(f,i));
        } else {
            vsip_vput_d(d,i,0.0);
        }
    }
    svdZeroCheckAndSet_d(eps0,d,f);          
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = vsip_vget_d(f,i);
        m = vsip_mag_d(ps);
        ps=sign_d(ps);
        col_sv_d(L, l, j);vsip_svmul_d(ps,l,l);
        row_sv_d(R,r,j);vsip_svmul_d(ps,r,r);
        vsip_vput_d(f,i,m);
        vsip_vput_d(f,j,ps * vsip_vget_d(f,j));
    }
    j=n_f;
    i=j-1;
    ps=vsip_vget_d(f,i);
    m=vsip_mag_d(ps);
    ps=sign_d(ps);
    vsip_vput_d(f,i,m);
    col_sv_d(L, l, j);vsip_svmul_d(ps,l,l);
    row_sv_d(R,r,j);vsip_svmul_d(ps,r,r);
} 
static void phaseCheck_d(svdObj_d *svd)
{
    biDiagPhaseToZero_d(svd);
} 

void houseProd_d(vsip_vview_d *v, vsip_mview_d *A)
{
    vsip_mattr_d a_atr; 
    vsip_vview_d *w;
    vsip_mview_d *B;
    vsip_mgetattrib_d(A,&a_atr);
    B=vsip_mcreate_d(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_vcreate_d(a_atr.row_length,VSIP_MEM_NONE);
    vsip_scalar_d beta = 2.0/vsip_vdot_d(v,v);
    vsip_vmprod_d(v,A,w);
    vsip_vouter_d(beta,v,w,B);
    vsip_msub_d(A,B,A);
    vsip_valldestroy_d(w);
    vsip_malldestroy_d(B);
} /* need to remove create */
void prodHouse_d(vsip_mview_d *A, vsip_vview_d *v)
{
    vsip_mattr_d a_atr; 
    vsip_vview_d *w;
    vsip_mview_d *B;
    vsip_mgetattrib_d(A,&a_atr);
    B=vsip_mcreate_d(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_vcreate_d(a_atr.col_length,VSIP_MEM_NONE);
    vsip_scalar_d beta = 2.0/vsip_vdot_d(v,v);
    vsip_mvprod_d(A,v,w);
    vsip_vouter_d(beta,w,v,B);
    vsip_msub_d(A,B,A);
    vsip_valldestroy_d(w);
    vsip_malldestroy_d(B);
} /* need to remove create */
static vsip_vview_d *houseVector_d(vsip_vview_d* x)
{
    vsip_scalar_d nrm=vnorm2_d(x);
    vsip_scalar_d t = vsip_vget_d(x,0);
    vsip_scalar_d s = t +  sign_d(t) * nrm;
    vsip_vput_d(x,0,s); 
    nrm = vnorm2_d(x);
    if (nrm == 0.0)
        vsip_vput_d(x,0,1.0); 
    else
        vsip_svmul_d(1.0/nrm,x,x);
    return x;
}
static void VHmatExtract_d(svdObj_d *svd)
{
    vsip_mview_d*B = svd->B;
    vsip_index i,j;
    vsip_length n = vsip_mgetrowlength_d(B);
    vsip_mview_d *Bs=svd->Bs;
    vsip_mview_d *V=svd->R;
    vsip_mview_d *Vs=svd->Rs;
    vsip_vview_d *v;
    vsip_scalar_d t;
    if(n < 3)
        return;
    v = row_sv_d(B,svd->bs,0);
    for(i=n-3; i>0; i--){
        j=i+1;
        row_sv_d(msv_d(B,Bs,i,j),v,0);
        t=vsip_vget_d(v,0);vsip_vput_d(v,0,1.0);
        prodHouse_d(msv_d(V,Vs,j,j),v);
        vsip_vput_d(v,0,t);
    }
    row_sv_d(msv_d(B,Bs,0,1),v,0);
    t=vsip_vget_d(v,0);vsip_vput_d(v,0,1.0);
    prodHouse_d(msv_d(V,Vs,1,1),v);
    vsip_vput_d(v,0,t);      
}
static void UmatExtract_d(svdObj_d *svd)
{
    vsip_mview_d* B=svd->B;
    vsip_mview_d *U=svd->L;
    vsip_index i;
    vsip_length m = vsip_mgetcollength_d(B);
    vsip_length n = vsip_mgetrowlength_d(B);
    vsip_mview_d *Bs=svd->Bs;
    vsip_mview_d *Us=svd->Ls;
    vsip_vview_d *v;
    vsip_scalar_d t;
    v = col_sv_d(B,svd->bs,0);
    if (m > n){
        i=n-1;
        col_sv_d(msv_d(B,Bs,i,i),v,0);
        t=vsip_vget_d(v,0); vsip_vput_d(v,0,1.0);
        houseProd_d(v,msv_d(U,Us,i,i));
        vsip_vput_d(v,0,t);
    }
    for(i=n-2; i>0; i--){
        col_sv_d(msv_d(B,Bs,i,i),v,0);
        t=vsip_vget_d(v,0); vsip_vput_d(v,0,1.0);
        houseProd_d(v,msv_d(U,Us,i,i));
        vsip_vput_d(v,0,t);
    }
    col_sv_d(msv_d(B,Bs,0,0),v,0);
    t=vsip_vget_d(v,0); vsip_vput_d(v,0,1.0);
    houseProd_d(v,msv_d(U,Us,0,0));
    vsip_vput_d(v,0,t);
}
static void bidiag_d(svdObj_d *svd)
{
    vsip_mview_d *B = svd->B; 
    vsip_mview_d *Bs = svd->Bs;
    vsip_length m = vsip_mgetcollength_d(B);
    vsip_length n = vsip_mgetrowlength_d(B);
    vsip_vview_d *x=col_sv_d(B,svd->bs,0);
    vsip_vview_d *v=vclone_d(x,svd->t);
    vsip_vview_d *vs = svd->ts;
    vsip_index i,j;
    for(i=0; i<n-1; i++){
        vsip_vputlength_d(v,m-i);
        vsip_vcopy_d_d(col_sv_d(msv_d(B,Bs,i,i),x,0),v);
        houseVector_d(v);
        vsip_svmul_d(1.0/vsip_vget_d(v,0),v,v);
        houseProd_d(v,Bs);
        vsip_vcopy_d_d(vsv_d(v,vs,1),vsv_d(x,x,1));
        if(i < n-2){
            j = i+1;
            vsip_vputlength_d(v,n-j);
            vsip_vcopy_d_d(row_sv_d(msv_d(B,Bs,i,j),x,0),v);
            houseVector_d(v);
            vsip_svmul_d(1.0/vsip_vget_d(v,0),v,v);
            prodHouse_d(Bs,v);
            vsip_vcopy_d_d(vsv_d(v,vs,1),vsv_d(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_vputlength_d(v,m-i);
        vsip_vcopy_d_d(col_sv_d(msv_d(B,Bs,i,i),x,0),v);
        houseVector_d(v);
        vsip_svmul_d(1.0/vsip_vget_d(v,0),v,v);
        houseProd_d(v,Bs);
        vsip_vcopy_d_d(vsv_d(v,vs,1),vsv_d(x,x,1));
    }
}
static void svdBidiag_d(svdObj_d *svd)
{
    vsip_mview_d *B = svd->B;
    /* eps0 is a number << maximum singular value */
    svd->eps0=mnormFro_d(B)/(vsip_scalar_d)vsip_mgetrowlength_d(B)*1E-10;
    bidiag_d(svd);
    UmatExtract_d(svd);
    VHmatExtract_d(svd);
    biDiagPhaseToZero_d(svd);
    vsip_vcopy_d_d(diag_sv_d(B,svd->bs,0),svd->d);
    vsip_vcopy_d_d(diag_sv_d(B,svd->bs,1),svd->f);
} 

static void gtProd_d(vsip_index i, vsip_index j, vsip_scalar_d c,vsip_scalar_d s, svdObj_d* svd)
{
    vsip_mview_d* R = svd->Rs;
    vsip_vview_d *a1= row_sv_d(R,svd->rs_one, i);
    vsip_vview_d *a2= row_sv_d(R,svd->rs_two, j);
    vsip_vview_d *a1c=vclone_d(a1,svd->t);
    vsip_svmul_d(c,a1c,a1); vsip_vsma_d(a2,s,a1,a1);
    vsip_svmul_d(-s,a1c,a1c); vsip_vsma_d(a2,c,a1c,a2); 
} 
static void prodG_d(svdObj_d* svd,vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s)
{
    vsip_mview_d* L = svd->Ls;
    vsip_vview_d *a1= col_sv_d(L,svd->ls_one,i);
    vsip_vview_d *a2= col_sv_d(L,svd->ls_two,j);
    vsip_vview_d *a1c=vclone_d(a1,svd->t);
    vsip_svmul_d(c,a1c,a1); vsip_vsma_d(a2,s,a1,a1);
    vsip_svmul_d(-s,a1c,a1c);vsip_vsma_d(a2,c,a1c,a2);
}
static givensObj_d givensCoef_d(vsip_scalar_d x1, vsip_scalar_d x2)
{
    givensObj_d retval;
    vsip_scalar_d t = vsip_hypot_d(x1,x2);
    if (x2 == 0.0){
        retval.c=1.0;retval.s=0.0;retval.r=x1;
    } else if (x1 == 0.0) {
        retval.c=0.0;retval.s=sign_d(x2);retval.r=t;
    }else{
        vsip_scalar_d sn = sign_d(x1);
        retval.c=vsip_mag_d(x1)/t;retval.s=sn*x2/t; retval.r=sn*t;
    }
    return retval;
} /* same */

static void zeroCol_d(svdObj_d *svd)
{
    vsip_vview_d *d=svd->ds;
    vsip_vview_d *f=svd->fs;
    vsip_length n = vsip_vgetlength_d(f);
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i,j,k;
    if (n == 1){
        xd=vsip_vget_d(d,0);
        xf=vsip_vget_d(f,0);
        g=givensCoef_d(xd,xf);
        vsip_vput_d(d,0,g.r);
        vsip_vput_d(f,0,0.0);
        gtProd_d(0,1,g.c,g.s,svd);
    }else if (n == 2){
        xd=vsip_vget_d(d,1);
        xf=vsip_vget_d(f,1);
        g=givensCoef_d(xd,xf);
        vsip_vput_d(d,1,g.r);
        vsip_vput_d(f,1,0.0);
        xf=vsip_vget_d(f,0);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_d(f,0,xf);
        gtProd_d(1,2,g.c,g.s,svd);
        xd=vsip_vget_d(d,0);
        g=givensCoef_d(xd,t);
        vsip_vput_d(d,0,g.r);
        gtProd_d(0,2,g.c,g.s,svd);
    }else{
        i=n-1; j=i-1; k=i;
        xd=vsip_vget_d(d,i);
        xf=vsip_vget_d(f,i);
        g=givensCoef_d(xd,xf);
        xf=vsip_vget_d(f,j);
        vsip_vput_d(f,i,0.0);
        vsip_vput_d(d,i,g.r);
        t=-xf*g.s; xf*=g.c;
        vsip_vput_d(f,j,xf);
        gtProd_d(i,k+1,g.c,g.s,svd);
        while (i > 1){
            i = j; j = i-1;
            xd=vsip_vget_d(d,i);
            g=givensCoef_d(xd,t);
            vsip_vput_d(d,i,g.r);
            xf=vsip_vget_d(f,j);
            t= -xf * g.s; xf *= g.c;
            vsip_vput_d(f,j,xf);
            gtProd_d(i,k+1,g.c,g.s,svd);
        }
        xd=vsip_vget_d(d,0);
        g=givensCoef_d(xd,t);
        vsip_vput_d(d,0,g.r);
        gtProd_d(0,k+1,g.c,g.s,svd);
    }
} 
static void zeroRow_d(svdObj_d *svd)
{
    vsip_vview_d *d = svd->ds;
    vsip_vview_d *f = svd->fs;
    vsip_length n = vsip_vgetlength_d(d);
    givensObj_d g;
    vsip_scalar_d xd,xf,t;
    vsip_index i;
    xd=vsip_vget_d(d,0);
    xf=vsip_vget_d(f,0);
    g=givensCoef_d(xd,xf);
    if (n == 1){
        vsip_vput_d(f,0,0.0);
        vsip_vput_d(d,0,g.r);
    }else{
        vsip_vput_d(f,0,0.0);
        vsip_vput_d(d,0,g.r);
        xf=vsip_vget_d(f,1);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_d(f,1,xf);
        prodG_d(svd,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=vsip_vget_d(d,i);
            g=givensCoef_d(xd,t);
            prodG_d(svd,i+1,0,g.c,g.s);
            vsip_vput_d(d,i,g.r);
            xf=vsip_vget_d(f,i+1);
            t=-xf * g.s; xf *= g.c;
            vsip_vput_d(f,i+1,xf);
        }
        xd=vsip_vget_d(d,n-1);
        g=givensCoef_d(xd,t);
        vsip_vput_d(d,n-1,g.r);
        prodG_d(svd,n,0,g.c,g.s);
    }
} 

static vsip_scalar_d svdMu_d(vsip_scalar_d d2,vsip_scalar_d f1,vsip_scalar_d d3,vsip_scalar_d f2)
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
} /* same */
static vsip_index zeroFind_d(vsip_vview_d* d, vsip_scalar_d eps0)
{
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
} /* same */
static svdCorner svdCorners_d(vsip_vview_d* f)
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
} /* same */

static void svdStep_d(svdObj_d *svd)
{
    vsip_vview_d *d = svd->ds;
    vsip_vview_d *f = svd->fs;
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
    gtProd_d(0,1,g.c,g.s,svd);
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
        prodG_d(svd,i, j, g.c, g.s);
        g=givensCoef_d(vsip_vget_d(f,i),t);
        vsip_vput_d(f,i,g.r);
        x1=vsip_vget_d(d,j); x2=vsip_vget_d(f,j);
        vsip_vput_d(d,j,g.c * x1 + g.s * x2); vsip_vput_d(f,j,g.c * x2 - g.s * x1);
        x1=vsip_vget_d(d,k);
        t=g.s * x1; vsip_vput_d(d,k,x1*g.c);
        gtProd_d(j,k, g.c, g.s,svd);
    }
    i=n-2; j=n-1;
    g = givensCoef_d(vsip_vget_d(d,i),t);
    vsip_vput_d(d,i,g.r);
    x1=vsip_vget_d(d,j)*g.c; x2=vsip_vget_d(f,i)*g.s;
    t=x1 - x2;
    x1 = vsip_vget_d(f,i) * g.c; x2=vsip_vget_d(d,j) * g.s;
    vsip_vput_d(f,i,x1+x2);
    vsip_vput_d(d,j,t);
    prodG_d(svd,i, j, g.c, g.s);
}
static void svdIteration_d(svdObj_d* svd)
{
    vsip_mview_d *L0 = svd->L; vsip_mview_d *L = svd->Ls;
    vsip_vview_d *d0 = svd->d; vsip_vview_d *d = svd->ds;
    vsip_vview_d *f0 = svd->f; vsip_vview_d *f = svd->fs;
    vsip_mview_d *R0 = svd->R; vsip_mview_d *R= svd->Rs;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=20*vsip_vgetlength_d(d0);
    while (cntr++ < maxcntr){
        phaseCheck_d(svd);
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
                zeroCol_d(svd);
            }else{
                imsv_d(L,L,0,0,k-1,0);
                ivsv_d(d0,d,k,0);
                ivsv_d(f0,f,k-1,0);
                zeroRow_d(svd);
            }
        }else{
            svdStep_d(svd);
        }
    }
}
static void svdSort_d(svdObj_d *svd)
{
    vsip_vview_d *d = svd->d;
    vsip_length n=vsip_vgetlength_d(d);
    vsip_vview_vi* indx_L = svd->indx_L;
    vsip_vview_vi* indx_R = svd->indx_R;
    vsip_mview_d *L0 = svd->L; vsip_mview_d *L=svd->Ls;
    vsip_mview_d *R0 = svd->R;
    vsip_vsortip_d(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vsip_vcopy_vi_vi(indx_L,indx_R);
    imsv_d( L0, L, 0,0, 0, n);
    vsip_mpermute_once_d(L,VSIP_COL,indx_L,L);
    vsip_mpermute_once_d(R0,VSIP_ROW,indx_R,R0);
}

svdObj_d* svdInit_d(vsip_length m, vsip_length n)
{
    svdObj_d *s=malloc(sizeof(svdObj_d));
    if(m < n){
        printf("Column length must not be less than row length");
        return NULL;
    }
    if(!s) {
        printf("\nfailed to allocate svd object\n");
        return NULL;
    }
    s->init=0;
    if(!(s->t = vsip_vcreate_d(m,VSIP_MEM_NONE))){
        s->ts = NULL; s->init++;
    } else {
        if(!(s->ts = vsip_vcloneview_d(s->t))) s->init++;
    }
    if(!(s->B=vsip_mcreate_d(m,n,VSIP_ROW,VSIP_MEM_NONE))){ 
        s->Bs = NULL; s->bs=NULL; s->init++;
    } else {
        if(!(s->Bs=vsip_mcloneview_d(s->B))) s->init++;
        if(!(s->bs=vsip_mrowview_d(s->B,0))) s->init++;
    }
    if(!(s->L=meye_d(m))){ 
        s->Ls=NULL; s->init++;
    } else {
        if(!(s->Ls = vsip_mcloneview_d(s->L))) s->init++;
        if(!(s->ls_two = vsip_mrowview_d(s->Ls,0))) s->init++;
        if(!(s->ls_one = vsip_mrowview_d(s->Ls,0))) s->init++;
    }
    if(!(s->R=meye_d(n))){
        s->Rs=NULL; s->init++;
    } else {
        if(!(s->Rs = vsip_mcloneview_d(s->R))) s->init++;
        if(!(s->rs_two = vsip_mrowview_d(s->Rs,0))) s->init++;
        if(!(s->rs_one = vsip_mrowview_d(s->Rs,0))) s->init++;
    }
    if(!(s->indx_L=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    if(!(s->indx_R=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    if(!(s->d = vsip_vcreate_d(n,VSIP_MEM_NONE))){
        s->init++; s->ds = NULL;
    } else { 
        if(!(s->ds = vsip_vcloneview_d(s->d))) s->init++;
    }
    if(!(s->f = vsip_vcreate_d(n-1,VSIP_MEM_NONE))){
        s->init++; s->fs = NULL;
    } else { 
        if(!(s->fs = vsip_vcloneview_d(s->f))) s->init++;
    }
    if(s->init) svdFinalize_d(s);
    return s;
}
void svdFinalize_d(svdObj_d *s)
{
    vsip_vdestroy_d(s->ts);
    vsip_valldestroy_d(s->t);
    vsip_vdestroy_d(s->rs_one);
    vsip_vdestroy_d(s->rs_two);
    vsip_mdestroy_d(s->Rs);
    vsip_vdestroy_d(s->ls_one);
    vsip_vdestroy_d(s->ls_two);
    vsip_mdestroy_d(s->Ls);
    vsip_mdestroy_d(s->Bs);
    vsip_vdestroy_d(s->bs);
    vsip_malldestroy_d(s->B);
    vsip_malldestroy_d(s->R);
    vsip_malldestroy_d(s->L);
    vsip_valldestroy_vi(s->indx_L);
    vsip_valldestroy_vi(s->indx_R);
    vsip_vdestroy_d(s->ds);
    vsip_valldestroy_d(s->d);
    vsip_vdestroy_d(s->fs);
    vsip_valldestroy_d(s->f);
    s=NULL;
}
svdObj_d *svd_d(vsip_mview_d *A)
{
    svdObj_d *svd = svdInit_d(vsip_mgetcollength_d(A),vsip_mgetrowlength_d(A));
    if(!svd){ printf("malloc failure for SVD"); exit(0);}
    vsip_mcopy_d_d(A,svd->B);
    svdBidiag_d(svd);
    svdIteration_d(svd);
    svdSort_d(svd);
    return svd;
}
