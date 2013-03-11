/* Created RJudd March 2013 */
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
#include"csvd_d.h"
static vsip_cvview_d *cvsv_d(vsip_cvview_d *v,vsip_cvview_d *vs,vsip_index i)
{
     vsip_cvattr_d attr;
     vsip_cvgetattrib_d(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_cvputattrib_d(vs,&attr);
     return vs;
}
static vsip_cmview_d* cmsv_d(vsip_cmview_d *B, vsip_cmview_d *BS, vsip_index i,vsip_index j)
{
    vsip_cmattr_d attr;
    vsip_cmgetattrib_d(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_cmputattrib_d(BS,&attr);
    return BS;
}
static vsip_cmview_d* cimsv_d( vsip_cmview_d *B, vsip_cmview_d *BS, vsip_index i1,vsip_index j1, 
                                                                    vsip_index i2, vsip_index j2)
{
    vsip_cmattr_d attr;
    vsip_cmgetattrib_d(B,&attr);
    if(j1 == 0) j1 =attr.col_length;
    if(j2 == 0) j2 =attr.row_length;
    attr.col_length = (j1 - i1);
    attr.row_length = (j2 - i2);
    attr.offset += i2 * attr.row_stride + i1 * attr.col_stride;
    vsip_cmputattrib_d(BS,&attr);
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
static vsip_cvview_d *ccol_sv_d(vsip_cmview_d*Am,vsip_cvview_d* vv,vsip_index col)
{
    vsip_cmattr_d A; vsip_cvattr_d v;
    vsip_cmgetattrib_d(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_cvputattrib_d(vv,&v);
    return vv;
}
static vsip_cvview_d *crow_sv_d(vsip_cmview_d*Am,vsip_cvview_d* vv,vsip_index row)
{
    vsip_cmattr_d A; vsip_cvattr_d v;
    vsip_cmgetattrib_d(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_cvputattrib_d(vv,&v);
    return vv;
}
static vsip_cvview_d *cdiag_sv_d(vsip_cmview_d* Am,vsip_cvview_d* a, vsip_stride i)
{
    vsip_cmattr_d A; vsip_cvattr_d v;
    vsip_cmgetattrib_d(Am,&A);
    vsip_cvgetattrib_d(a,&v);
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
    vsip_cvputattrib_d(a,&v);
    return a;
}
static vsip_cvview_d* cvclone_d(vsip_cvview_d*x, vsip_cvview_d *v)
{
    vsip_cvputoffset_d(v,0);
    vsip_cvputlength_d(v,vsip_cvgetlength_d(x));
    vsip_cvputstride_d(v, 1);
    vsip_cvcopy_d_d(x,v);
    return v;
}
static vsip_vview_d *vreal_sv_d(vsip_cvview_d *cv,vsip_vview_d*v)
{
    vsip_cvattr_d cattr; vsip_vattr_d attr;
    vsip_cvgetattrib_d(cv,&cattr);
    attr.offset=cattr.offset; attr.length=cattr.length; attr.stride=cattr.stride;
    vsip_vputattrib_d(v,&attr);
    return v;
}

static vsip_scalar_d cvnorm2_d(vsip_cvview_d *v)
{
    return vsip_sqrt_d(vsip_cvjdot_d(v,v).r);
}
static vsip_scalar_d cmnormFro_d(vsip_cmview_d *v)
{
    vsip_mview_d* re=vsip_mrealview_d(v); 
    vsip_mview_d* im=vsip_mimagview_d(v);
    return vsip_sqrt_d(vsip_msumsqval_d(re)+vsip_msumsqval_d(im));
    vsip_mdestroy_d(re);vsip_mdestroy_d(im);
}
static vsip_cmview_d* cmeye_d(vsip_length n)
{
    vsip_cvview_d *d = (vsip_cvview_d*) NULL;
    vsip_cmview_d *retval = (vsip_cmview_d*)NULL;
    retval = vsip_cmcreate_d(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval) d = vsip_cmdiagview_d(retval,0);
    if(d){
        vsip_cmfill_d(vsip_cmplx_d(0.0,0.0),retval);
        vsip_cvfill_d(vsip_cmplx_d(1.0,0.0),d);
        vsip_cvdestroy_d(d);
    } else {
        vsip_cmalldestroy_d(retval);
        retval = (vsip_cmview_d*) NULL;
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
} /*same */
static void csvdZeroCheckAndSet_d(vsip_scalar_d e, vsip_cvview_d *b0, vsip_cvview_d *b1)
{
    vsip_index i;
    vsip_length n = vsip_cvgetlength_d(b1);
    vsip_cscalar_d z = vsip_cmplx_d(0.0,0.0);
    for(i=0; i<n; i++){
        vsip_scalar_d b = vsip_cmag_d(vsip_cvget_d(b1,i));
        vsip_scalar_d a = e*(vsip_cmag_d(vsip_cvget_d(b0,i))
                        +    vsip_cmag_d(vsip_cvget_d(b0,i+1)));
        if( b < a ) vsip_cvput_d(b1,i,z);
    }
} 

/* sign function as defined in http://www.netlib.org/lapack/lawnspdf/lawn148.pdf */
static vsip_scalar_d sign_d(vsip_scalar_d a_in)
{
    if(a_in < 0.0)
       return -1.0;
    else 
       return 1.0;
} /* same */
static vsip_cscalar_d csign_d(vsip_cscalar_d a_in)
{
    vsip_scalar_d re = a_in.r;
    vsip_scalar_d im = a_in.i;
    vsip_scalar_d t=vsip_hypot_d(re,im);
    vsip_cscalar_d retval;
    retval.r=0.0; retval.i = 0.0;
    if(t == 0.0){
        retval.r = 1.0;
        return retval;
    } else if (im==0.0) {
        retval.r = sign_d(re);
        return retval;
    } else {
        retval.r = re/t;
        retval.i = im/t;
        return retval;
    }
}
static void cbiDiagPhaseToZero_d( csvdObj_d *svd)
{
    vsip_cmview_d *L = svd->L;
    vsip_cvview_d *d = cdiag_sv_d(svd->B,svd->bs,0);
    vsip_cvview_d *f = cdiag_sv_d(svd->B,svd->bfs,1);
    vsip_cmview_d *R = svd->R;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_length n_d=vsip_cvgetlength_d(d);
    vsip_length n_f=vsip_cvgetlength_d(f);
    vsip_index i,j;
    vsip_cscalar_d ps;
    vsip_scalar_d m;
    vsip_cvview_d *l = svd->ls_one;
    vsip_cvview_d *r = svd->rs_one;
    for(i=0; i<n_d; i++){
        ps=vsip_cvget_d(d,i);
        if(ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps=vsip_cmplx_d(-1.0,0.0);
            else
                ps= vsip_cmplx_d(1.0,0.0);
            m = vsip_mag_d(m); 
        } else {
            m=vsip_cmag_d(ps);
            ps.r /= m; ps.i/=m;
        }
        if(m > eps0){
            ccol_sv_d(L,l,i);vsip_csvmul_d(ps,l,l);
            vsip_cvput_d(d,i,vsip_cmplx_d(m,0));
            if (i < n_f)
                vsip_cvput_d(f,i,vsip_cjmul_d(vsip_cvget_d(f,i),ps));
        }else{
            vsip_cvput_d(d,i,vsip_cmplx_d(0.0,0.0));
        }
    }
    csvdZeroCheckAndSet_d(eps0,d,f);          
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = vsip_cvget_d(f,i);
        if (ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps=vsip_cmplx_d(-1.0,0.0);
            else
                ps= vsip_cmplx_d(1.0,0.0);
            m = vsip_mag_d(m);
        }else{
            m=vsip_cmag_d(ps);
            ps.r /= m; ps.i/=m;
        }
        ccol_sv_d(L, l, j);vsip_csvmul_d(vsip_conj_d(ps),l,l);
        crow_sv_d(R,r,j);vsip_csvmul_d(ps,r,r);
        vsip_cvput_d(f,i,vsip_cmplx_d(m,0));
        vsip_cvput_d(f,j,vsip_cmul_d(vsip_cvget_d(f,j),ps));
    }
    j=n_f;
    i=j-1;
    ps=vsip_cvget_d(f,i);
    if (ps.i == 0.0){
        m = ps.r;
        if(m < 0.0)
            ps=vsip_cmplx_d(-1.0,0.0);
        else
            ps= vsip_cmplx_d(1.0,0.0);
        m = vsip_mag_d(m);
    }else{
        m=vsip_cmag_d(ps);
        ps.r /= m; ps.i/=m;
    }
    vsip_cvput_d(f,i,vsip_cmplx_d(m,0.0));
    ccol_sv_d(L, l, j);vsip_csvmul_d(vsip_conj_d(ps),l,l);
    crow_sv_d(R,r,j);vsip_csvmul_d(ps,r,r);
}
static void cphaseCheck_d(csvdObj_d *svd)
{
   vsip_cmview_d *L = svd->L;
   vsip_vview_d *d = svd->d;
   vsip_vview_d *f = svd->f;
   vsip_cmview_d *R = svd->R;
   vsip_scalar_d eps0 = svd->eps0;
   vsip_length nf=vsip_vgetlength_d(f);
   vsip_index i,j;
   vsip_scalar_d ps;
   vsip_scalar_d m;
   vsip_cvview_d *l = svd->ls_one;
   vsip_cvview_d *r = svd->rs_one;
   for(i=0; i<vsip_vgetlength_d(d); i++){
        ps=vsip_vget_d(d,i);
        m = vsip_mag_d(ps);
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

void chouseProd_d(vsip_cvview_d *v, vsip_cmview_d *A)
{
    vsip_cmattr_d a_atr; 
    vsip_cvview_d *w;
    vsip_cmview_d *B;
    vsip_scalar_d beta = 2.0/vsip_cvjdot_d(v,v).r;
    vsip_cmgetattrib_d(A,&a_atr);
    B=vsip_cmcreate_d(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_cvcreate_d(a_atr.row_length,VSIP_MEM_NONE);
    vsip_cvconj_d(v,v);
    vsip_cvmprod_d(v,A,w);vsip_cvconj_d(w,w);
    vsip_cvconj_d(v,v);
    vsip_cvouter_d(vsip_cmplx_d(beta,0.0),v,w,B);
    vsip_cmsub_d(A,B,A);
    vsip_cvalldestroy_d(w);
    vsip_cmalldestroy_d(B);
} /* needs work on OPU*/
void cprodHouse_d(vsip_cmview_d *A, vsip_cvview_d *v)
{
    vsip_cmattr_d a_atr; 
    vsip_cvview_d *w;
    vsip_cmview_d *B;
    vsip_scalar_d beta = 2.0/vsip_cvjdot_d(v,v).r;
    vsip_cmgetattrib_d(A,&a_atr);
    B=vsip_cmcreate_d(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_cvcreate_d(a_atr.col_length,VSIP_MEM_NONE);
    vsip_cmvprod_d(A,v,w);
    vsip_cvouter_d(vsip_cmplx_d(beta,0.0),w,v,B);
    vsip_cmsub_d(A,B,A);
    vsip_cvalldestroy_d(w);
    vsip_cmalldestroy_d(B);
} /* needs work on OPU*/
static vsip_cvview_d *chouseVector_d(vsip_cvview_d* x)
{
    vsip_cscalar_d t = vsip_cvget_d(x,0); /*x[0]*/
    vsip_scalar_d nrm=cvnorm2_d(x); /* x.norm2 */
    vsip_cscalar_d s = vsip_cadd_d(t, vsip_cmul_d(csign_d(t), vsip_cmplx_d(nrm, 0.0)));
    vsip_cvput_d(x,0,s);
    nrm = cvnorm2_d(x);
    if (nrm == 0.0)
        vsip_cvput_d(x,0,vsip_cmplx_d(1.0,0.0));
    else
        vsip_rscvmul_d(1.0/nrm,x,x);
    return x;
}
static void cVHmatExtract_d(csvdObj_d *svd)
{
    vsip_cmview_d*B = svd->B;
    vsip_index i,j;
    vsip_length n = vsip_cmgetrowlength_d(B);
    vsip_cmview_d *Bs=svd->Bs;
    vsip_cmview_d *V=svd->R;
    vsip_cmview_d *Vs=svd->Rs;
    vsip_cvview_d *v;
    vsip_cscalar_d t;
    if(n < 3)
        return;
    v = crow_sv_d(B,svd->bs,0);
    for(i=n-3; i>0; i--){
        j=i+1;
        crow_sv_d(cmsv_d(B,Bs,i,j),v,0);
        t=vsip_cvget_d(v,0);vsip_cvput_d(v,0,vsip_cmplx_d(1.0,0.0));
        cprodHouse_d(cmsv_d(V,Vs,j,j),v);
        vsip_cvput_d(v,0,t);
    }
    crow_sv_d(cmsv_d(B,Bs,0,1),v,0);
    t=vsip_cvget_d(v,0);vsip_cvput_d(v,0,vsip_cmplx_d(1.0,0.0));
    cprodHouse_d(cmsv_d(V,Vs,1,1),v);
    vsip_cvput_d(v,0,t);       
} 
static void cUmatExtract_d(csvdObj_d *svd)
{
    vsip_cmview_d* B=svd->B;
    vsip_cmview_d *U=svd->L;
    vsip_index i;
    vsip_length m = vsip_cmgetcollength_d(B);
    vsip_length n = vsip_cmgetrowlength_d(B);
    vsip_cmview_d *Bs=svd->Bs;
    vsip_cmview_d *Us=svd->Ls;
    vsip_cvview_d *v;
    vsip_cscalar_d t;
    v = ccol_sv_d(B,svd->bs,0);
    if (m > n){
        i=n-1;
        ccol_sv_d(cmsv_d(B,Bs,i,i),v,0);
        t=vsip_cvget_d(v,0); vsip_cvput_d(v,0,vsip_cmplx_d(1.0,0.0));
        chouseProd_d(v,cmsv_d(U,Us,i,i));
        vsip_cvput_d(v,0,t);
    }
    for(i=n-2; i>0; i--){
        ccol_sv_d(cmsv_d(B,Bs,i,i),v,0);
        t=vsip_cvget_d(v,0); vsip_cvput_d(v,0,vsip_cmplx_d(1.0,0.0));
        chouseProd_d(v,cmsv_d(U,Us,i,i));
        vsip_cvput_d(v,0,t);
    } 
    ccol_sv_d(cmsv_d(B,Bs,0,0),v,0);
    t=vsip_cvget_d(v,0); vsip_cvput_d(v,0,vsip_cmplx_d(1.0,0.0));
    chouseProd_d(v,cmsv_d(U,Us,0,0));
    vsip_cvput_d(v,0,t);
} 
static void cbidiag_d(csvdObj_d *svd)
{
    vsip_cmview_d *B = svd->B;
    vsip_cmview_d *Bs = svd->Bs;
    vsip_length m = vsip_cmgetcollength_d(B);
    vsip_length n = vsip_cmgetrowlength_d(B);
    vsip_cvview_d *x=ccol_sv_d(B,svd->bs,0);
    vsip_cvview_d *v=cvclone_d(x,svd->t);
    vsip_cvview_d *vs = svd->ts;
    vsip_index i,j;
    for(i=0; i<n-1; i++){
        vsip_cvputlength_d(v,m-i);
        vsip_cvcopy_d_d(ccol_sv_d(cmsv_d(B,Bs,i,i),x,0),v);
        chouseVector_d(v);
        vsip_csvmul_d(vsip_cdiv_d(vsip_cmplx_d(1.0,0.0),vsip_cvget_d(v,0)),v,v);
        chouseProd_d(v,Bs);
        vsip_cvcopy_d_d(cvsv_d(v,vs,1),cvsv_d(x,x,1));
        if(i < n-2){
            j = i+1;
            vsip_cvputlength_d(v,n-j);
            vsip_cvcopy_d_d(crow_sv_d(cmsv_d(B,Bs,i,j),x,0),v);
            chouseVector_d(v);vsip_cvconj_d(v,v);
            vsip_csvmul_d(vsip_cdiv_d(vsip_cmplx_d(1.0,0.0),vsip_cvget_d(v,0)),v,v);
            cprodHouse_d(Bs,v);
            vsip_cvcopy_d_d(cvsv_d(v,vs,1),cvsv_d(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_cvputlength_d(v,m-i);
        vsip_cvcopy_d_d(ccol_sv_d(cmsv_d(B,Bs,i,i),x,0),v);
        chouseVector_d(v);
        vsip_csvmul_d(vsip_cdiv_d(vsip_cmplx_d(1.0,0.0),vsip_cvget_d(v,0)),v,v);
        chouseProd_d(v,Bs);
        vsip_cvcopy_d_d(cvsv_d(v,vs,1),cvsv_d(x,x,1));
    }
}
static void csvdBidiag_d(csvdObj_d *svd)
{
    vsip_cmview_d *B = svd->B;
    svd->eps0=(cmnormFro_d(B)/(vsip_scalar_d)vsip_cmgetrowlength_d(B))*1E-10;
    cbidiag_d(svd);
    cUmatExtract_d(svd);
    cVHmatExtract_d(svd);
    cbiDiagPhaseToZero_d(svd);
    vsip_vcopy_d_d(vreal_sv_d(cdiag_sv_d(svd->B, svd->bs, 0),svd->rbs),svd->d);
    vsip_vcopy_d_d(vreal_sv_d(cdiag_sv_d(svd->B, svd->bs, 1),svd->rbs),svd->f);
}

static void cgtProd_d(vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s,csvdObj_d *svd)
{
    vsip_cmview_d* R=svd->R;
    vsip_cvview_d *a1= crow_sv_d(R,svd->rs_one,i);
    vsip_cvview_d *a2= crow_sv_d(R,svd->rs_two,j);
    vsip_cvview_d *a1c=cvclone_d(a1,svd->ts);
    vsip_cvattr_d a1attr,tsattr;
    vsip_cvgetattrib_d(a1, &a1attr);
    vsip_cvgetattrib_d(a1c,&tsattr);
    vsip_rscvmul_d(c,a1c,a1);
    vsip_cvsma_d(a2,vsip_cmplx_d(s,0.0),a1,a1);
    vsip_rscvmul_d(-s,a1c,a1c);
    vsip_cvsma_d(a2,vsip_cmplx_d(c,0.0),a1c,a2);
}
static void cprodG_d(csvdObj_d *svd,vsip_index i, vsip_index j,vsip_scalar_d c, vsip_scalar_d s)
{
    vsip_cmview_d* L=svd->L;
    vsip_cvview_d *a1= ccol_sv_d(L,svd->ls_one,i);
    vsip_cvview_d *a2= ccol_sv_d(L,svd->ls_two,j);
    vsip_cvview_d *a1c=cvclone_d(a1,svd->ts);
    vsip_rscvmul_d(c,a1c,a1); vsip_cvsma_d(a2,vsip_cmplx_d(s,0.0),a1,a1);
    vsip_rscvmul_d(-s,a1c,a1c);vsip_cvsma_d(a2,vsip_cmplx_d(c,0.0),a1c,a2);
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

static void czeroCol_d(csvdObj_d *svd)
{
    vsip_vview_d *d = svd->ds;
    vsip_vview_d *f = svd->fs;
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
        cgtProd_d(0,1,g.c,g.s,svd);
    }else if (n == 2){
        xd=vsip_vget_d(d,1);
        xf=vsip_vget_d(f,1);
        g=givensCoef_d(xd,xf);
        vsip_vput_d(d,1,g.r);
        vsip_vput_d(f,1,0.0);
        xf=vsip_vget_d(f,0);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_d(f,0,xf);
        cgtProd_d(1,2,g.c,g.s,svd);
        xd=vsip_vget_d(d,0);
        g=givensCoef_d(xd,t);
        vsip_vput_d(d,0,g.r);
        cgtProd_d(0,2,g.c,g.s,svd);
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
        cgtProd_d(i,k+1,g.c,g.s,svd);
        while (i > 1){
            i = j; j = i-1;
            xd=vsip_vget_d(d,i);
            g=givensCoef_d(xd,t);
            vsip_vput_d(d,i,g.r);
            xf=vsip_vget_d(f,j);
            t= -xf * g.s; xf *= g.c;
            vsip_vput_d(f,j,xf);
            cgtProd_d(i,k+1,g.c,g.s,svd);
        }
        xd=vsip_vget_d(d,0);
        g=givensCoef_d(xd,t);
        vsip_vput_d(d,0,g.r);
        cgtProd_d(0,k+1,g.c,g.s,svd);
    }
}
static void czeroRow_d(csvdObj_d *svd)
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
        cprodG_d(svd,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=vsip_vget_d(d,i);
            g=givensCoef_d(xd,t);
            cprodG_d(svd,i+1,0,g.c,g.s);
            vsip_vput_d(d,i,g.r);
            xf=vsip_vget_d(f,i+1);
            t=-xf * g.s; xf *= g.c;
            vsip_vput_d(f,i+1,xf);
        }
        xd=vsip_vget_d(d,n-1);
        g=givensCoef_d(xd,t);
        vsip_vput_d(d,n-1,g.r);
        cprodG_d(svd,n,0,g.c,g.s);
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

static void csvdStep_d(csvdObj_d *svd)
{
    vsip_vview_d *d = svd->ds;
    vsip_vview_d *f = svd->fs;
    givensObj_d g;
    vsip_length n = vsip_vgetlength_d(d);
    vsip_scalar_d mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_d t=0.0;
    vsip_index i,j,k;
    vsip_scalar_d d2,f1,d3,f2;  
     /* this if list section below needs some more thought */
     /* we probably should never have n=1 */
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
    cgtProd_d(0,1,g.c,g.s,svd);
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
        cprodG_d(svd,i, j, g.c, g.s);
        g=givensCoef_d(vsip_vget_d(f,i),t);
        vsip_vput_d(f,i,g.r);
        x1=vsip_vget_d(d,j); x2=vsip_vget_d(f,j);
        vsip_vput_d(d,j,g.c * x1 + g.s * x2); vsip_vput_d(f,j,g.c * x2 - g.s * x1);
        x1=vsip_vget_d(d,k);
        t=g.s * x1; vsip_vput_d(d,k,x1*g.c);
        cgtProd_d(j,k, g.c, g.s,svd);
    }
    i=n-2; j=n-1;
    g = givensCoef_d(vsip_vget_d(d,i),t);
    vsip_vput_d(d,i,g.r);
    x1=vsip_vget_d(d,j)*g.c; x2=vsip_vget_d(f,i)*g.s;
    t=x1 - x2;
    x1 = vsip_vget_d(f,i) * g.c; x2=vsip_vget_d(d,j) * g.s;
    vsip_vput_d(f,i,x1+x2);
    vsip_vput_d(d,j,t);
    cprodG_d(svd,i, j, g.c, g.s);
}
static void csvdIteration_d(csvdObj_d *svd)
{
    vsip_cmview_d *L0=svd->L;
    vsip_vview_d *d0 = svd->d;
    vsip_vview_d *f0 = svd->f;
    vsip_cmview_d *R0 = svd->R;
    vsip_scalar_d eps0 = svd->eps0;
    vsip_vview_d *d=svd->ds;
    vsip_vview_d *f=svd->fs;
    vsip_cmview_d *L=svd->Ls;
    vsip_cmview_d *R=svd->Rs;
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=20*vsip_vgetlength_d(d0);
    while (cntr++ < maxcntr){
        cphaseCheck_d(svd);
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
                czeroCol_d(svd);
            }else{
                cimsv_d(L,L,0,0,k-1,0);
                ivsv_d(d0,d,k,0);
                ivsv_d(f0,f,k-1,0);
                czeroRow_d(svd);
            }
        }else{
            csvdStep_d(svd);
        }
    }
}
static void csvdSort_d(csvdObj_d *svd)
{
    vsip_cmview_d* L0 = svd->L;
    vsip_vview_d* d = svd->d;
    vsip_cmview_d* R0 = svd->R;
    vsip_length n=vsip_vgetlength_d(d);
    vsip_vview_vi* indx_L = svd->indx_L;
    vsip_vview_vi* indx_R = svd->indx_R;
    vsip_cmview_d *L=svd->Ls;
    vsip_vsortip_d(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vsip_vcopy_vi_vi(indx_L,indx_R);
    cimsv_d( L0, L, 0,0, 0, n);
    vsip_cmpermute_once_d(L,VSIP_COL,indx_L,L);
    vsip_cmpermute_once_d(R0,VSIP_ROW,indx_R,R0);
}

csvdObj_d* csvdInit_d(vsip_length m, vsip_length n)
{
    csvdObj_d *s=malloc(sizeof(csvdObj_d));
    if(m < n){
        printf("Column length must not be less than row length");
        return NULL;
    }
    if(!s) {
        printf("\nfailed to allocate svd object\n");
        return NULL;
    }
    s->init=0;
    if(!(s->t = vsip_cvcreate_d(m,VSIP_MEM_NONE))){
        s->ts = NULL; s->init++;
    } else {
        if(!(s->ts = vsip_cvcloneview_d(s->t))) s->init++;
    }
    if(!(s->B=vsip_cmcreate_d(m,n,VSIP_ROW,VSIP_MEM_NONE))){ 
        s->Bs = NULL; s->bs=NULL; s->init++;
    } else {
        if(!(s->Bs =vsip_cmcloneview_d(s->B))) s->init++;
        if(!(s->bs =vsip_cmrowview_d(s->B,0))) s->init++;
        if(!(s->rbs=vsip_vrealview_d(s->bs ))) s->init++;
        if(!(s->bfs=vsip_cvcloneview_d(s->bs))) s->init++;
    }
    if(!(s->L=cmeye_d(m))){ 
        s->Ls=NULL; s->init++;
    } else {
        if(!(s->Ls = vsip_cmcloneview_d(s->L))) s->init++;
        if(!(s->ls_two = vsip_cmrowview_d(s->Ls,0))) s->init++;
        if(!(s->ls_one = vsip_cmrowview_d(s->Ls,0))) s->init++;
    }
    if(!(s->R=cmeye_d(n))){
        s->Rs=NULL; s->init++;
    } else {
        if(!(s->Rs = vsip_cmcloneview_d(s->R))) s->init++;
        if(!(s->rs_two = vsip_cmrowview_d(s->Rs,0))) s->init++;
        if(!(s->rs_one = vsip_cmrowview_d(s->Rs,0))) s->init++;
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
    if(s->init) csvdFinalize_d(s);
    return s;
}
void csvdFinalize_d(csvdObj_d *s)
{
    vsip_cvdestroy_d(s->ts);
    vsip_cvalldestroy_d(s->t);
    vsip_cvdestroy_d(s->rs_one);
    vsip_cvdestroy_d(s->rs_two);
    vsip_cmdestroy_d(s->Rs);
    vsip_cvdestroy_d(s->ls_one);
    vsip_cvdestroy_d(s->ls_two);
    vsip_cmdestroy_d(s->Ls);
    vsip_cmdestroy_d(s->Bs);
    vsip_cvdestroy_d(s->bs);
    vsip_cvdestroy_d(s->bfs);
    vsip_vdestroy_d(s->rbs);
    vsip_cmalldestroy_d(s->B);
    vsip_cmalldestroy_d(s->R);
    vsip_cmalldestroy_d(s->L);
    vsip_valldestroy_vi(s->indx_L);
    vsip_valldestroy_vi(s->indx_R);
    vsip_vdestroy_d(s->ds);
    vsip_valldestroy_d(s->d);
    vsip_vdestroy_d(s->fs);
    vsip_valldestroy_d(s->f);
    s=NULL;
}
csvdObj_d *csvd_d(vsip_cmview_d *A)
{
    csvdObj_d *svd = csvdInit_d(vsip_cmgetcollength_d(A),vsip_cmgetrowlength_d(A));
    if(!svd){ printf("malloc failure for SVD"); exit(0);}
    vsip_cmcopy_d_d(A,svd->B);
    csvdBidiag_d(svd);
    csvdIteration_d(svd);
    csvdSort_d(svd);
    return svd;
}
