/* Created Randall Judd 2013*/
/*********************************************************************
 // This code includes no warranty, express or implied, including     /
 // the warranties of merchantability and fitness for a particular    /
 // purpose.                                                          /
 // No person or entity assumes any legal liability or responsibility /
 // for the accuracy, completeness, or usefulness of any information, /
 // apparatus, product, or process disclosed, or represents that      /
 // its use would not infringe privately owned rights.                /
 *********************************************************************/
/*********************************************************************
 // The MIT License (see copyright for jvsip in top level directory)
 // http://opensource.org/licenses/MIT
 **********************************************************************/
#include<vsip.h>
#include"VI.h"
#include"vsip_blockattributes_f.h"
#include"vsip_cblockattributes_f.h"
#include"vsip_vviewattributes_f.h"
#include"vsip_mviewattributes_f.h"
#include"vsip_cvviewattributes_f.h"
#include"vsip_cmviewattributes_f.h"
#include"VI_vcopy_f_f.h"
#include"VI_cvcopy_f_f.h"
#include"VI_vget_f.h"
#include"VI_cvfill_f.h"

#define scaleV(v) { \
vsip_scalar_f *p = v->block->array + v->offset * v->block->rstride;\
vsip_stride std = v->stride * v->block->rstride;vsip_length n = v->length * std;\
vsip_scalar_f scl = p[0];p[0]=1.0;vsip_index k;for(k=std; k<n; k+=std) p[k] /= scl; \
}

#define CMAG_F(re,im) ((re == 0.0) ? im:(im< re) ? re * (vsip_scalar_f)sqrt(1.0 + (im/re) * (im/re)): \
im * (vsip_scalar_f)sqrt(1.0 + (re/im) * (re/im)))
static void mprint_f(vsip_mview_f *A){
    vsip_length n=vsip_mgetrowlength_f(A);
    vsip_length m=vsip_mgetcollength_f(A);
    vsip_index i,j;
    printf("[");
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            printf("%+.5f ",vsip_mget_f(A,i,j));
        }
        printf(";\n") ;
    }
    printf("]\n");
}
static vsip_scalar_f hypot_f(vsip_scalar_f a,vsip_scalar_f b){
    if (a == 0.0)
        return b;
    else if (b == 0.0)
        return a;
    else if (b < a)
        return a * (vsip_scalar_f)sqrt(1.0 + (b/a) * (b/a));
    else
        return b * (vsip_scalar_f)sqrt(1.0 + (a/b) * (a/b));
}

typedef struct {vsip_index i; vsip_index j;} svdCorner;
typedef struct {vsip_scalar_f c; vsip_scalar_f s; vsip_scalar_f r;}givensObj_f ;
typedef struct {vsip_vview_f* t; vsip_vview_f ts;
    vsip_vview_f* w;
    vsip_mview_f* B; vsip_mview_f Bs; vsip_vview_f bs;
    vsip_mview_f* L; vsip_mview_f Ls; vsip_vview_f ls_one; vsip_vview_f ls_two;
    vsip_vview_f* d; vsip_vview_f ds;
    vsip_vview_f* f; vsip_vview_f fs;
    vsip_mview_f* R; vsip_mview_f Rs; vsip_vview_f rs_one; vsip_vview_f rs_two;
    vsip_scalar_f eps0;int init;
    vsip_vview_vi *indx_L; vsip_vview_vi *indx_R;} svdObj_f;
typedef struct {vsip_cvview_f* t; vsip_cvview_f ts;
    vsip_cvview_f* w;
    vsip_cmview_f* B; vsip_cmview_f Bs; vsip_cvview_f bs; vsip_cvview_f bfs; vsip_vview_f rbs;
    vsip_cmview_f* L; vsip_cmview_f Ls; vsip_cvview_f ls_one; vsip_cvview_f ls_two;
    vsip_vview_f* d; vsip_vview_f ds;
    vsip_vview_f* f; vsip_vview_f fs;
    vsip_cmview_f* R; vsip_cmview_f Rs; vsip_cvview_f rs_one; vsip_cvview_f rs_two;
    vsip_scalar_f eps0;int init;
    vsip_vview_vi *indx_L; vsip_vview_vi *indx_R;} csvdObj_f;

static svdObj_f *svdInit_f(vsip_length, vsip_length);
static void svdFinalize_f(svdObj_f*);
static void svd_f(svdObj_f*);

static csvdObj_f *csvdInit_f(vsip_length, vsip_length);
static void csvdFinalize_f(csvdObj_f*);
static void csvd_f(csvdObj_f*);

static vsip_vview_f *vsv_f(vsip_vview_f *v, vsip_vview_f *vs, vsip_index i)
{
    *vs=*v;
    vs->offset += i * vs->stride;
    vs->length -= i;
    return vs;
}
static vsip_mview_f* msv_f(vsip_mview_f *B,vsip_mview_f *BS, vsip_index i,vsip_index j)
{
    *BS = *B;
    BS->row_length -= j;
    BS->col_length -= i;
    BS->offset += j * BS->row_stride + i * BS->col_stride;
    return BS;
}
static vsip_mview_f* imsv_f( vsip_mview_f *B, vsip_mview_f *BS, vsip_index i1,vsip_index j1,
                            vsip_index i2, vsip_index j2)
{
    *BS=*B;
    if(j1 == 0) j1 =B->col_length;
    if(j2 == 0) j2 =B->row_length;
    BS->col_length = (j1 - i1);
    BS->row_length = (j2 - i2);
    BS->offset += i2 * B->row_stride + i1 * B->col_stride;
    return BS;
}
static vsip_vview_f *ivsv_f( vsip_vview_f *v, vsip_vview_f *vs, vsip_index i,vsip_index j)
{
    *vs=*v;
    if(j==0) j=v->length;
    vs->offset += i * v->stride;
    vs->length = j-i;
    return vs;
}
static vsip_vview_f *col_sv_f(vsip_mview_f*Am,vsip_vview_f* vv,vsip_index col)
{
    vv->block = Am->block;
    vv->offset = Am->offset + col * Am->row_stride;
    vv->stride = Am->col_stride;
    vv->length = Am->col_length;
    return vv;
}
static vsip_vview_f *row_sv_f(vsip_mview_f*Am,vsip_vview_f* vv,vsip_index row)
{
    vv->block = Am->block;
    vv->offset = Am->offset + row * Am->col_stride;
    vv->stride = Am->row_stride;
    vv->length = Am->row_length;
    return vv;
}
static vsip_vview_f *diag_sv_f(vsip_mview_f* Am,vsip_vview_f* a, vsip_stride i)
{
    a->block = Am->block;
    a->stride=Am->row_stride + Am->col_stride;
    if(i==0){
        a->length = Am->row_length;
        a->offset = Am->offset;
    } else if (i == 1){
        a->offset = Am->offset + Am->row_stride;
        a->length = Am->row_length - 1;
    } else {
        printf("Failed in diag_sv_f\n");
        exit(0);
    }
    return a;
}

static vsip_cmview_f* cimsv_f( vsip_cmview_f *B, vsip_cmview_f *BS, vsip_index i1,vsip_index j1,
                              vsip_index i2, vsip_index j2)
{
    *BS=*B;
    if(j1 == 0) j1 =B->col_length;
    if(j2 == 0) j2 =B->row_length;
    BS->col_length = (j1 - i1);
    BS->row_length = (j2 - i2);
    BS->offset += i2 * B->row_stride + i1 * B->col_stride;
    return BS;
}
static vsip_cvview_f *ccol_sv_f(vsip_cmview_f*Am,vsip_cvview_f* vv,vsip_index col)
{
    vv->block = Am->block;
    vv->offset = Am->offset + col * Am->row_stride;
    vv->stride = Am->col_stride;
    vv->length = Am->col_length;
    return vv;
}
static vsip_cvview_f *crow_sv_f(vsip_cmview_f*Am,vsip_cvview_f* vv,vsip_index row)
{
    vv->block=Am->block;
    vv->offset = Am->offset + row * Am->col_stride;
    vv->stride = Am->row_stride;
    vv->length = Am->row_length;
    return vv;
}
static vsip_cvview_f *cdiag_sv_f(vsip_cmview_f* Am,vsip_cvview_f* a, vsip_stride i)
{
    a->block = Am->block;
    a->stride=Am->row_stride + Am->col_stride;
    if(i==0){
        a->length = Am->row_length;
        a->offset = Am->offset;
    } else if (i == 1){
        a->offset = Am->offset + Am->row_stride;
        a->length = Am->row_length - 1;
    } else {
        printf("Failed in diag_sv_f\n");
        exit(0);
    }
    return a;
}

static vsip_vview_f* vclone_f(vsip_vview_f*x, vsip_vview_f *v)
{
    v->length = x->length;
    VI_vcopy_f_f(x,v);
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
    vsip_vview_f d;
    vsip_mview_f *retval = vsip_mcreate_f(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval){
        d.block = retval->block; d.length = n; d.stride = n+1; d.offset = 0;
        vsip_mfill_f(0.0,retval);
        vsip_vfill_f(1.0,&d);
    }
    return retval;
}

static void svdZeroCheckAndSet_f(vsip_scalar_f e, vsip_vview_f *d, vsip_vview_f *f)
{
    vsip_index i;
    vsip_length n = f->length;
    vsip_stride fstd=f->stride*f->block->rstride;
    vsip_stride dstd=d->stride*d->block->rstride;
    vsip_scalar_f *fptr=f->block->array+f->offset*f->block->rstride;
    vsip_scalar_f *dptr=d->block->array+d->offset*d->block->rstride;
    for(i=0; i<n; i++){
        vsip_scalar_f *fi=fptr+i*fstd,*di=dptr+i*fstd;
        if((*fi<0 ? -*fi:*fi) < (e*(*di<0 ? -*di:*di + *(di+dstd)<0 ? -*(di+dstd):*(di+dstd)))) *fi=0.0;
    }
}

/* sign function as defined in http://www.netlib.org/lapack/lawnspdf/lawn148.pdf */
static vsip_scalar_f sign_f(vsip_scalar_f a_in)
{
    return (a_in < 0.0) ? -1.0:1.0;
}
static vsip_cscalar_f csign_f(vsip_cscalar_f a_in)
{
    vsip_scalar_f re = a_in.r < 0.0 ? -a_in.r:a_in.r;
    vsip_scalar_f im = a_in.i < 0.0 ? -a_in.i:a_in.i;
    vsip_scalar_f t= (re==0.0) ? im: ((im==0.0) ? re:((re<im) ? im*sqrt(1.0 + re/im*re/im):re*sqrt(1.0+im/re*im/re)));//vsip_hypot_f(re,im);
    vsip_cscalar_f retval;
    retval.r=0.0; retval.i = 0.0;
    if(t == 0.0){
        retval.r = 1.0;
        return retval;
    } else if (im==0.0) {
        retval.r = (a_in.r < 0.0) ? -1.0:1.0;
        return retval;
    } else {
        retval.r = a_in.r/t;
        retval.i = a_in.i/t;
        return retval;
    }
}

static void phaseCheck_f(svdObj_f *svd)
{
    vsip_scalar_f *fptr, *dptr;
    vsip_mview_f *L = svd->L;
    vsip_vview_f *d = svd->d;
    vsip_vview_f *f = svd->f;
    vsip_mview_f *R = svd->R;
    vsip_scalar_f eps0 = svd->eps0;
    vsip_length n_d=d->length;
    vsip_length n_f=f->length;
    vsip_index i,j;
    vsip_scalar_f ps;
    vsip_scalar_f m;
    vsip_vview_f *l = &svd->ls_one;
    vsip_vview_f *r = &svd->rs_one;
    vsip_stride fstrd=f->stride * d->block->rstride;
    vsip_stride dstrd=d->stride * d->block->rstride;
    dptr=d->block->array +d->offset * d->block->rstride;
    fptr=f->block->array + f->offset * f->block->rstride;
    for(i=0; i<n_d; i++){
        ps=*dptr;
        m = (ps<0) ? -ps:ps;
        ps=sign_f(ps);
        if(m > eps0){
            col_sv_f(L,l,i);
            {   //vsip_svmul_f(ps,l,l);
                vsip_scalar_f *p = l->block->array + l->offset * l->block->rstride;
                vsip_stride std = l->stride * l->block->rstride;
                vsip_length n = l->length * std;
                vsip_index k;
                for(k=0; k<n; k+=std) p[k] *= ps;
            }
            *dptr=m;
            if (i < n_f)
                *fptr *= ps;
        } else {
            *dptr = 0.0;
        }
        dptr+=dstrd;fptr+=fstrd;
    }
    svdZeroCheckAndSet_f(eps0,d,f);
    fptr=f->block->array + f->offset * f->block->rstride;
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = *fptr;
        m = (ps<0) ? -ps:ps;
        ps=sign_f(ps);
        *fptr=m;
        col_sv_f(L, l, j);
        {
            vsip_scalar_f *p = l->block->array + l->offset * l->block->rstride;
            vsip_stride std = l->stride * l->block->rstride;
            vsip_length n = l->length * std;
            vsip_index k;
            for(k=0; k<n; k+=std) p[k] *= ps;
        }
        row_sv_f(R,r,j);
        {
            vsip_scalar_f *p = r->block->array + r->offset * r->block->rstride;
            vsip_stride std = r->stride * r->block->rstride;
            vsip_length n = r->length * std;
            vsip_index k;
            for(k=0; k<n; k+=std) p[k] *= ps;
        }
        fptr+=fstrd;
        *fptr *= ps;
    }
    j=n_f;
    ps=*fptr;
    m=(ps<0) ? -ps:ps;
    ps=sign_f(ps);
    *fptr=m;
    col_sv_f(L, l, j);
    {//vsip_svmul_f(ps,l,l);
        vsip_scalar_f *p = l->block->array + l->offset * l->block->rstride;
        vsip_stride std = l->stride * l->block->rstride;
        vsip_length n = l->length * std;
        vsip_index k;
        for(k=0; k<n; k+=std) p[k] *= ps;
    }
    row_sv_f(R,r,j);
    {//vsip_svmul_f(ps,r,r);
        vsip_scalar_f *p = r->block->array + r->offset * r->block->rstride;
        vsip_stride std = r->stride * r->block->rstride;
        vsip_length n = r->length * std;
        vsip_index k;
        for(k=0; k<n; k+=std) p[k] *= ps;
    }
}

static void biDiagPhaseToZero_f( svdObj_f *svd)
{
    VI_vcopy_f_f(diag_sv_f(svd->B,&svd->bs,0),svd->d);
    VI_vcopy_f_f(diag_sv_f(svd->B,&svd->bs,1),svd->f);
    phaseCheck_f(svd);
}

static void opu_f(
                  vsip_mview_f *A,
                  vsip_vview_f *x,
                  vsip_vview_f *y)
{
    vsip_length m = A->col_length;
    vsip_length n = A->row_length;
    vsip_index i,ii,j,jj;
    vsip_scalar_f *ap=A->block->array + A->offset * A->block->rstride;
    vsip_scalar_f *xp=x->block->array + x->offset * x->block->rstride;
    vsip_scalar_f *yp=y->block->array + y->offset * y->block->rstride;
    vsip_stride xstd = x->block->rstride * x->stride;
    vsip_stride ystd = y->block->rstride * y->stride;
    vsip_stride r_std = A->block->rstride * A->row_stride;
    vsip_stride c_std = A->block->rstride * A->col_stride;
    m *= c_std;
    n *= r_std;
    for(i=0, ii=0; i<m; i+=c_std, ii+=xstd){
        vsip_scalar_f c = xp[ii];
        vsip_scalar_f *app=ap+i;
        for(j=0, jj=0; j<n; j+=r_std, jj+=ystd){
            app[j] = app[j] + c * yp[jj];
        }
    }
}

static void houseProd_f(vsip_vview_f *v, vsip_mview_f *A,vsip_vview_f *w)
{
    vsip_scalar_f beta = 2.0/vsip_vdot_f(v,v);
    w->length = A->row_length;
    vsip_vmprod_f(v,A,w);
    vsip_svmul_f(-beta,w,w);
    opu_f(A,v,w);
}
static void prodHouse_f(vsip_mview_f *A, vsip_vview_f *v, vsip_vview_f *w)
{
    vsip_scalar_f beta = 2.0/vsip_vdot_f(v,v);
    w->length = A->col_length;
    vsip_mvprod_f(A,v,w);
    vsip_svmul_f(-beta,w,w);
    opu_f(A,w,v);
}
static vsip_vview_f *houseVector_f(vsip_vview_f* x)
{
    vsip_scalar_f *p=x->block->array + x->offset * x->block->rstride;
    vsip_scalar_f nrm=vnorm2_f(x);
    vsip_scalar_f t = *p;
    vsip_scalar_f s = t +  sign_f(t) * nrm;
    *p=s;
    nrm = vnorm2_f(x);
    if (nrm == 0.0)
        *p=1.0;
    else {
        vsip_stride std = x->stride * x->block->rstride;
        vsip_length n = x->length * std;
        vsip_index k;
        for(k=0; k<n; k+=std) p[k] /= nrm;
    }
    return x;
}
static void VHmatExtract_f(svdObj_f *svd)
{
    vsip_mview_f*B = svd->B;
    vsip_index i,j;
    vsip_length n = B->row_length;
    vsip_mview_f *Bs=&svd->Bs;
    vsip_mview_f *V=svd->R;
    vsip_mview_f *Vs=&svd->Rs;
    vsip_vview_f *v;
    vsip_scalar_f t;
    vsip_scalar_f *vptr;
    if(n < 3)
        return;
    v = row_sv_f(B,&svd->bs,0);
    for(i=n-3; i>0; i--){
        j=i+1;
        row_sv_f(msv_f(B,Bs,i,j),v,0);
        vptr=v->block->array+v->offset*v->block->rstride;
        t=*vptr; *vptr = 1.0;
        prodHouse_f(msv_f(V,Vs,j,j),v,svd->w);
        *vptr = t;
    }
    row_sv_f(msv_f(B,Bs,0,1),v,0);
    vptr=v->block->array+v->offset*v->block->rstride;
    t=*vptr; *vptr = 1.0;
    prodHouse_f(msv_f(V,Vs,1,1),v,svd->w);
    *vptr = t;
}
static void UmatExtract_f(svdObj_f *svd)
{
    vsip_mview_f* B=svd->B;
    vsip_mview_f *U=svd->L;
    vsip_index i;
    vsip_length m = B->col_length;
    vsip_length n = B->row_length;
    vsip_mview_f *Bs=&svd->Bs;
    vsip_mview_f *Us=&svd->Ls;
    vsip_vview_f *v;
    vsip_scalar_f t;
    vsip_scalar_f *vptr;
    v = col_sv_f(B,&svd->bs,0);
    if (m > n){
        i=n-1;
        col_sv_f(msv_f(B,Bs,i,i),v,0);
        vptr=v->block->array+v->offset*v->block->rstride;
        t=*vptr; *vptr = 1.0;
        houseProd_f(v,msv_f(U,Us,i,i),svd->w);
        *vptr = t;
    }
    for(i=n-2; i>0; i--){
        col_sv_f(msv_f(B,Bs,i,i),v,0);
        vptr=v->block->array+v->offset*v->block->rstride;
        t=*vptr; *vptr = 1.0;
        houseProd_f(v,msv_f(U,Us,i,i),svd->w);
        *vptr = t;
    }
    col_sv_f(msv_f(B,Bs,0,0),v,0);
    vptr=v->block->array+v->offset*v->block->rstride;
    t=*vptr; *vptr = 1.0;
    houseProd_f(v,msv_f(U,Us,0,0),svd->w);
    *vptr= t;
}

static void bidiag_f(svdObj_f *svd)
{
    vsip_mview_f *B = svd->B;
    vsip_mview_f *Bs = &svd->Bs;
    vsip_length m = B->col_length;
    vsip_length n = B->row_length;
    vsip_vview_f *x=col_sv_f(B,&svd->bs,0);
    vsip_vview_f *v=vclone_f(x,svd->t);
    vsip_vview_f *vs = &svd->ts;
    vsip_index i,j;
    for(i=0; i<n-1; i++){
        v->length=m-i;
        VI_vcopy_f_f(col_sv_f(msv_f(B,Bs,i,i),x,0),v);
        houseVector_f(v);
        scaleV(v)         /*vsip_svmul_f(1.0/VI_VGET_F(v,0),v,v);*/
        houseProd_f(v,Bs,svd->w);
        VI_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
        if(i < n-2){
            j = i+1;
            v->length = n-j;
            VI_vcopy_f_f(row_sv_f(msv_f(B,Bs,i,j),x,0),v);
            houseVector_f(v);
            scaleV(v)         /*   vsip_svmul_f(1.0/VI_VGET_F(v,0),v,v);*/
            prodHouse_f(Bs,v,svd->w);
            VI_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        v->length=m-i;
        vsip_vcopy_f_f(col_sv_f(msv_f(B,Bs,i,i),x,0),v);
        houseVector_f(v);
        scaleV(v)         /*vsip_svmul_f(1.0/VI_VGET_F(v,0),v,v); */
        houseProd_f(v,Bs,svd->w);
        VI_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
    }
}
static void svdBidiag_f(svdObj_f *svd)
{
    vsip_mview_f *B = svd->B;
    /* eps0 is a number << maximum singular value */
    svd->eps0=mnormFro_f(B)/(vsip_scalar_f)B->row_length * 1E-10;
    bidiag_f(svd);
    UmatExtract_f(svd);
    VHmatExtract_f(svd);
    biDiagPhaseToZero_f(svd);
}

static void gtProd_f(vsip_index i, vsip_index j, vsip_scalar_f c,vsip_scalar_f s, svdObj_f* svd)
{
    vsip_mview_f* R = &svd->Rs;
    vsip_vview_f *a1= row_sv_f(R,&svd->rs_one, i);
    vsip_vview_f *a2= row_sv_f(R,&svd->rs_two, j);
    vsip_index k;
    vsip_scalar_f *t1 = a1->block->array + (a1->offset) * a1->block->rstride;
    vsip_scalar_f *t2 = a2->block->array + (a2->offset) * a2->block->rstride;
    vsip_stride std = a1->stride * a1->block->rstride;
    vsip_length n = a1->length * std;
    for(k=0; k<n; k+=std){
        register vsip_scalar_f b1 = t1[k];
        register vsip_scalar_f b2 = t2[k];
        t1[k] = c * b1 + s * b2;
        t2[k] = c * b2 - s * b1;
    }
}
static void prodG_f(svdObj_f* svd,vsip_index i, vsip_index j,vsip_scalar_f c, vsip_scalar_f s)
{
    vsip_mview_f* L = &svd->Ls;
    vsip_vview_f *a1= col_sv_f(L,&svd->ls_one,i);
    vsip_vview_f *a2= col_sv_f(L,&svd->ls_two,j);
    vsip_index k;
    vsip_scalar_f *t1 = a1->block->array + (a1->offset) * a1->block->rstride;
    vsip_scalar_f *t2 = a2->block->array + (a2->offset) * a2->block->rstride;
    vsip_stride std = a1->stride * a1->block->rstride;
    vsip_length n = a1->length * std;
    for(k=0; k<n; k+=std){
        register vsip_scalar_f b1 = t1[k];
        register vsip_scalar_f b2 = t2[k];
        t1[k] = c * b1 + s * b2;
        t2[k] = c * b2 - s * b1;
    }
}
static givensObj_f givensCoef_f(vsip_scalar_f x1, vsip_scalar_f x2)
{
    givensObj_f retval;
    vsip_scalar_f t = hypot_f(x1,x2);
    if (x2 == 0.0 ){
        retval.c=1.0;retval.s=0.0;retval.r=x1;
    } else if (x1 == 0.0  || t == 0.0) {
        retval.c=0.0;retval.s=sign_f(x2);retval.r=t;
    }else{
        vsip_scalar_f sn = sign_f(x1);
        retval.c=vsip_mag_f(x1)/t;retval.s=sn*x2/t; retval.r=sn*t;
    }
    return retval;
} /* same */

static void zeroCol_f(svdObj_f *svd)
{
    vsip_vview_f *d=&svd->ds;
    vsip_vview_f *f=&svd->fs;
    vsip_length n = f->length;
    givensObj_f g;
    vsip_scalar_f xd,xf,t;
    vsip_index i,j,k;
    //printf("In zeroCol\n");
    if (n == 1){
        xd=*(d->block->array + d->offset * d->block->rstride);
        xf=*(f->block->array + f->offset * f->block->rstride);
        g=givensCoef_f(xd,xf);
        *(d->block->array + d->offset * d->block->rstride)=g.r;
        *(f->block->array + f->offset * f->block->rstride)=0.0;
        gtProd_f(0,1,g.c,g.s,svd);
    }else if (n == 2){
        xd=VI_VGET_F(d,1);
        xf=VI_VGET_F(f,1);
        g=givensCoef_f(xd,xf);
        *(d->block->array + (d->offset+1) * d->block->rstride)=g.r;/*vsip_vput_f(d,1,g.r);*/
        *(f->block->array + (f->offset+1) * f->block->rstride)=0.0;/*vsip_vput_f(f,1,0.0);*/
        xf=VI_VGET_F(f,0);
        t= -xf * g.s; xf *= g.c;
        *(f->block->array + (f->offset) * f->block->rstride)=xf;/*vsip_vput_f(f,0,xf);*/
        gtProd_f(1,2,g.c,g.s,svd);
        xd=VI_VGET_F(d,0);
        g=givensCoef_f(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;/*vsip_vput_f(d,0,g.r);*/
        gtProd_f(0,2,g.c,g.s,svd);
    }else{
        i=n-1; j=i-1; k=i;
        xd=*(d->block->array + (d->offset+i) * d->block->rstride);
        xf=*(f->block->array + (f->offset+i) * f->block->rstride);
        g=givensCoef_f(xd,xf);
        xf=*(f->block->array + (f->offset+j) * f->block->rstride);
        *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;/*vsip_vput_f(d,i,g.r);*/
        *(f->block->array + (f->offset+i) * f->block->rstride)=0.0;/*vsip_vput_f(f,i,0.0);*/
        t=-xf*g.s; xf*=g.c;
        *(f->block->array + (f->offset+j) * f->block->rstride)=xf;/*vsip_vput_f(f,j,xf);*/
        gtProd_f(i,k+1,g.c,g.s,svd);
        while (i > 1){
            i = j; j = i-1;
            xd=*(d->block->array + (d->offset+i) * d->block->rstride);
            g=givensCoef_f(xd,t);
            *(d->block->array + (d->offset+i) * d->block->rstride)=g.r;/*vsip_vput_f(d,i,g.r);*/
            xf=*(f->block->array + (f->offset+j) * f->block->rstride);
            t= -xf * g.s; xf *= g.c;
            *(f->block->array + (f->offset+j) * f->block->rstride)=xf;/*vsip_vput_f(f,j,xf);*/
            gtProd_f(i,k+1,g.c,g.s,svd);
        }
        xd=*(d->block->array + d->offset * d->block->rstride);
        g=givensCoef_f(xd,t);
        *(d->block->array + d->offset * d->block->rstride)=g.r;/*vsip_vput_f(d,0,g.r);*/
        gtProd_f(0,k+1,g.c,g.s,svd);
    }
}
static void zeroRow_f(svdObj_f *svd)
{
    vsip_vview_f *d = &svd->ds;
    vsip_vview_f *f = &svd->fs;
    vsip_scalar_f *dptr=d->block->array+d->offset*d->block->rstride;
    vsip_scalar_f *fptr=f->block->array + f->offset*d->block->rstride;
    vsip_stride dstd=d->stride*d->block->rstride;
    vsip_stride fstd=f->stride*f->block->rstride;
    vsip_length n = d->length;
    givensObj_f g;
    vsip_scalar_f xd,xf,t;
    vsip_index i;
    xd=*dptr;
    xf=*fptr;
    g=givensCoef_f(xd,xf);
    if (n == 1){
        *dptr=g.r;
        *fptr=0.0;
        prodG_f(svd,n,0,g.c,g.s);
    }else{
        *dptr=g.r;
        *fptr=0.0;
        xf=*(fptr+fstd);
        t= -xf * g.s; xf *= g.c;
        *(fptr+fstd)=xf;
        prodG_f(svd,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=*(dptr+dstd*i);
            g=givensCoef_f(xd,t);
            prodG_f(svd,i+1,0,g.c,g.s);
            *(dptr+dstd*i)=g.r;
            xf=*(fptr+fstd*(i+1));
            t=-xf * g.s; xf *= g.c;
            *(fptr+fstd*(i+1))=xf;
        }
        xd=*(dptr+dstd*(n-1));
        g=givensCoef_f(xd,t);
        *(dptr+dstd*(n-1))=g.r;
        prodG_f(svd,n,0,g.c,g.s);
    }
}

static vsip_scalar_f svdMu_f(vsip_scalar_f d2,vsip_scalar_f f1,vsip_scalar_f d3,vsip_scalar_f* f2)
{
    vsip_scalar_f mu;
    vsip_scalar_f cu=d2 * d2 + f1 * f1;
    vsip_scalar_f cl=d3 * d3 + *f2 * *f2;
    vsip_scalar_f cd = d2 * *f2;
    vsip_scalar_f T = (cu + cl);
    vsip_scalar_f D = (cu * cl - cd * cd)/(T*T);
    vsip_scalar_f root = T * vsip_sqrt_f(1.0 - ((4 * D)>1.0 ? 1.0:4*D));
    vsip_scalar_f lambda1 = (T + root)/(2.);
    vsip_scalar_f lambda2 = (T - root)/(2.);
    if(root == 0.0)
        if(*f2 < (d2 + d3)/1E6)
            *f2=0.0;
    if(vsip_mag_f(lambda1 - cl) < vsip_mag_f(lambda2 - cl))
        mu = lambda1;
    else
        mu = lambda2;
    return mu;
}
static vsip_index zeroFind_f(vsip_vview_f* d, vsip_scalar_f eps0)
{
    vsip_scalar_f *dptr=d->block->array + d->offset*d->block->rstride;
    vsip_stride dstrd=d->stride*d->block->rstride;
    vsip_index j = d->length;
    vsip_scalar_f xd=*(dptr+(j-1)*dstrd);
    while(xd > eps0){
        if (j > 1){
            j -= 1;
            xd=*(dptr+(j-1)*dstrd);
        }else if(j==1)
            return 0;
    }
    *(dptr+(j-1)*dstrd)=0.0;
    return j;
}
static svdCorner svdCorners_f(vsip_vview_f* f)
{
    svdCorner crnr;
    vsip_scalar_f *fptr=f->block->array + f->offset*f->block->rstride;
    vsip_stride fstrd=f->stride*f->block->rstride;
    vsip_index j=f->length-1;
    vsip_index i;
    while((j > 0) && *(fptr+j*fstrd) == 0.0)
        j-=1;
    if(j == 0 && *fptr == 0.0){
        crnr.i=0;
        crnr.j=0;
    } else {
        i = j;
        while((i > 0) && *(fptr+i*fstrd) != 0.0)
            i -= 1;
        if(i==0 && *fptr == 0.0){
            crnr.i = 1;
            crnr.j = j+2;
        } else if(i == 0 && *fptr != 0.0){
            crnr.i = 0;
            crnr.j= j+2;
        
        }else{
            crnr.i = i+1;
            crnr.j = j+2;
        }
    } /* index and length of f != 0 */
    return crnr;
}

static void svdStep_f(svdObj_f *svd)
{
    vsip_vview_f *d = &svd->ds;
    vsip_vview_f *f = &svd->fs;
    givensObj_f g;
    vsip_length n = d->length;
    vsip_scalar_f mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_f t=0.0;
    vsip_index i,j,k;
    vsip_scalar_f d2=0.0,f1=0.0,d3=0.0,f2=0.0;
    vsip_scalar_f *fptr,*dptr;
    vsip_stride fstd=f->stride*f->block->rstride, dstd=d->stride*d->block->rstride;
    dptr=d->block->array+d->offset*d->block->rstride;
    fptr=f->block->array+f->offset*f->block->rstride;
    if(n >= 3){
        d2=*(dptr+dstd*(n-2));f1= *(fptr+fstd*(n-3));d3 = *(dptr+dstd*(n-1));f2= *(fptr+fstd*(n-2));
    } else if(n == 2){
        d2=*dptr; d3=*(dptr+dstd); f1=0; f2=*fptr;
    } else {
        printf("should not be here (see svdStep_f)\n");
        exit(-1);
    }
    mu = svdMu_f(d2,f1,d3,&f2);
    if(f2 == 0.0) *(fptr+fstd*(n-2)) = 0.0;
    x1=*dptr;
    x2 = x1 * *fptr;
    x1 *= x1; x1 -= mu;
    g=givensCoef_f(x1,x2);
    x1=*dptr;x2=*fptr;
    *fptr=g.c*x2-g.s*x1;
    *dptr=g.c*x1+g.s*x2;
    t=*(dptr+dstd);
    *(dptr+dstd) *= g.c;
    t*=g.s;
    gtProd_f(0,1,g.c,g.s,svd);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_f(*(dptr+i*dstd),t);
        *(dptr+i*dstd)=g.r;  //vsip_vput_f(d,i,g.r);
        x1=*(dptr+j*dstd)*g.c;
        x2=*(fptr+i*fstd)*g.s;
        t= x1 - x2;
        x1=*(fptr+i*fstd) * g.c;
        x2=*(dptr+j*dstd) * g.s ;
        *(f->block->array+(i*f->stride+f->offset)*f->block->rstride) = x1+x2;
        *(d->block->array+(j*d->stride+d->offset)*d->block->rstride) = t;
        x1=*(fptr+j*fstd);
        t=g.s * x1;
        *(fptr+j*fstd)=x1*g.c;
        prodG_f(svd,i, j, g.c, g.s);
        g=givensCoef_f(*(fptr+i*fstd),t);
        *(fptr+i*fstd)=g.r;
        x1=*(dptr+j*dstd); x2=*(fptr+j*fstd);
        *(dptr+j*dstd)=g.c * x1 + g.s * x2; *(fptr+j*fstd)=g.c * x2 - g.s * x1;
        x1=*(dptr+k*dstd);
        t=g.s * x1; *(dptr+k*dstd)=x1*g.c;
        gtProd_f(j,k, g.c, g.s,svd);
    }
    i=n-2; j=n-1;
    g = givensCoef_f(*(dptr+i*dstd),t);
    *(d->block->array+(i*d->stride+d->offset)*d->block->rstride) = g.r;
    x1=*(dptr+j*dstd)*g.c; x2=*(fptr+i*fstd)*g.s;
    t=x1 - x2;
    x1 = *(fptr+i*fstd) * g.c; x2=*(dptr+j*dstd) * g.s;
    *(f->block->array+(i*f->stride+f->offset)*f->block->rstride) = x1+x2;
    *(d->block->array+(j*d->stride+d->offset)*d->block->rstride) = t;
    prodG_f(svd,i, j, g.c, g.s);
}
static void svdIteration_f(svdObj_f* svd)
{
    vsip_mview_f *L0 = svd->L; vsip_mview_f *L = &svd->Ls;
    vsip_vview_f *d0 = svd->d; vsip_vview_f *d = &svd->ds;
    vsip_vview_f *f0 = svd->f; vsip_vview_f *f = &svd->fs;
    vsip_mview_f *R0 = svd->R; vsip_mview_f *R= &svd->Rs;
    vsip_scalar_f eps0 = svd->eps0;
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=5*d0->length;
    while (cntr++ < maxcntr){
        phaseCheck_f(svd);
        cnr=svdCorners_f(f0);
        if (cnr.j == 0)
            break;
        ivsv_f(d0,d,cnr.i,cnr.j);
        ivsv_f(f0,f,cnr.i,cnr.j-1);
        imsv_f(L0,L,0,0,cnr.i,cnr.j);
        imsv_f(R0,R,cnr.i,cnr.j,0,0);
        n=f->length;
        k=zeroFind_f(d,eps0);
        if (k > 0 ){
            k=k-1;
            if(VI_VGET_F(d,n) == 0.0){
                zeroCol_f(svd);
                //printf("zeroCol\n");
            }else{
                imsv_f(L,L,0,0,k,0);
                d->length-=k+1;
                d->offset += k+1;
                f->length -= k;
                f->offset += k;
                zeroRow_f(svd);
                //printf("zeroRow\n");
            }
        }else{
            //printf("svdStep_f\n");
            svdStep_f(svd);
        }
        
    }
    //mprint_f(svd->R);
    printf("maxcounter %lu, count %lu\n",maxcntr,cntr);
}

static vsip_cvview_f *cvsv_f(vsip_cvview_f *v,vsip_cvview_f *vs,vsip_index i)
{
    *vs=*v;
    vs->offset += i * vs->stride;
    vs->length -= i;
    return vs;
}
static vsip_cmview_f* cmsv_f(vsip_cmview_f *B, vsip_cmview_f *BS, vsip_index i,vsip_index j)
{
    *BS=*B;
    BS->row_length -= j;
    BS->col_length -= i;
    BS->offset += j * BS->row_stride + i * BS->col_stride;
    return BS;
}

static vsip_cvview_f* cvclone_f(vsip_cvview_f*x, vsip_cvview_f *v)
{
    v->length = x->length;
    VI_cvcopy_f_f(x,v);
    return v;
}
static vsip_vview_f *vreal_sv_f(vsip_cvview_f *cv,vsip_vview_f*v)
{
    v->block=cv->block->R;
    v->offset = cv->offset; v->length=cv->length;v->stride= cv->stride;
    v->markings = VSIP_VALID_STRUCTURE_OBJECT;
    return v;
}

static vsip_scalar_f cvnorm2_f(vsip_cvview_f *v)
{
    return vsip_sqrt_f(vsip_cvjdot_f(v,v).r);
}
static vsip_scalar_f cmnormFro_f(vsip_cmview_f *v)
{
    vsip_mview_f* re=vsip_mrealview_f(v);
    vsip_mview_f* im=vsip_mimagview_f(v);
    return vsip_sqrt_f(vsip_msumsqval_f(re)+vsip_msumsqval_f(im));
    vsip_mdestroy_f(re);vsip_mdestroy_f(im);
}
static vsip_cmview_f* cmeye_f(vsip_cmview_f *retval, vsip_length n)
{
    vsip_cvview_f d;
    retval = vsip_cmcreate_f(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval){
        d.block = retval->block; d.length = n; d.stride = n+1; d.offset = 0;
        vsip_cmfill_f(retval->block->a_zero,retval);
        VI_cvfill_f(retval->block->a_one,&d);
    }
    return retval;
}

static void csvdZeroCheckAndSet_f(vsip_scalar_f e, vsip_cvview_f *d, vsip_cvview_f *f)
{
    vsip_index i;
    vsip_stride std = f->stride * f->block->R->rstride;
    vsip_length n = f->length * std;
    vsip_scalar_f *f_i = f->block->I->array + f->offset * f->block->R->rstride;
    vsip_scalar_f *f_r = f->block->R->array + f->offset * f->block->R->rstride;
    vsip_scalar_f *d_i = d->block->I->array + d->offset * d->block->R->rstride;
    vsip_scalar_f *d_r = d->block->R->array + d->offset * d->block->R->rstride;
    vsip_scalar_f re_f, re_d, im_f, im_d,a0,a1,a,b;
    re_d=fabs(*d_r); im_d=fabs(*d_i);
    a0=CMAG_F(re_d,im_d);
    d_r+=std; d_i+=std;
    for(i=0; i<n; i+=std){
        re_f=fabs(f_r[i]); im_f=fabs(f_i[i]);
        re_d=fabs(d_r[i]), im_d=fabs(d_i[i]);
        b = CMAG_F(re_f,im_f);
        a1=CMAG_F(re_d,im_d);
        a = e*(a0+a1);a0=a1;
        if( b < a ){ *f_r = 0.0; *f_i = 0.0;}
    }
}
static void cbiDiagPhaseToZero_f( csvdObj_f *svd)
{
    vsip_cmview_f *L = svd->L;
    vsip_cvview_f *d = cdiag_sv_f(svd->B,&svd->bs,0);
    vsip_cvview_f *f = cdiag_sv_f(svd->B,&svd->bfs,1);
    vsip_cmview_f *R = svd->R;
    vsip_scalar_f eps0 = svd->eps0;
    vsip_length n_d=d->length;
    vsip_length n_f=f->length;
    vsip_index i,j;
    vsip_cscalar_f ps;
    vsip_scalar_f m;
    vsip_cvview_f *l = &svd->ls_one;
    vsip_cvview_f *r = &svd->rs_one;
    vsip_scalar_f *dptr_r=d->block->R->array+d->block->R->rstride*d->offset;
    vsip_scalar_f *dptr_i=d->block->I->array+d->block->R->rstride*d->offset;
    vsip_scalar_f *fptr_r=f->block->R->array+f->block->R->rstride*f->offset;
    vsip_scalar_f *fptr_i=f->block->I->array+f->block->R->rstride*f->offset;
    vsip_stride dstrd=d->stride*d->block->R->rstride;
    vsip_stride fstrd=f->stride*f->block->R->rstride;
    vsip_scalar_f re,im;
    for(i=0; i<n_d; i++){
        ps.r=*(dptr_r+i*dstrd);
        ps.i=*(dptr_i+i*dstrd);
        if(ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps.r=-1.0;
            else
                ps.r=1.0;
            m = (m<0) ? -m:m;
        } else {
            re=fabs(ps.r), im=fabs(ps.i);
            m = CMAG_F(re,im);
            ps.r /= m; ps.i/=m;
        }
        if(m > eps0){
            ccol_sv_f(L,l,i);vsip_csvmul_f(ps,l,l);
            vsip_cvput_f(d,i,vsip_cmplx_f(m,0));
            if (i < n_f){
                vsip_scalar_f *fr=fptr_r+i*fstrd;
                vsip_scalar_f *fi=fptr_i+i*fstrd;
                re=*fr,im=*fi;
                *fr=re*ps.r+im*ps.i;
                *fi=-ps.i*re+ps.r*im;
            }
        }else{
            *(dptr_r+i*dstrd)=0.0;
            *(dptr_i+i*dstrd)=0.0;
        }
    }
    csvdZeroCheckAndSet_f(eps0,d,f);
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps.r=*(fptr_r+i*fstrd);
        ps.i=*(fptr_i+i*fstrd);
        if (ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps.r =-1.0;
            else
                ps.r = 1.0;
            m = (m < 0.0) ? -m:m;
        }else{
            re=fabs(ps.r), im=fabs(ps.i);
            m = CMAG_F(re,im);
            ps.r /= m; ps.i/=m;
        }
        ccol_sv_f(L, l, j);vsip_csvmul_f(vsip_conj_f(ps),l,l);
        crow_sv_f(R,r,j);vsip_csvmul_f(ps,r,r);
        *(fptr_r+i*fstrd)=m;
        *(fptr_i+i*fstrd)=0.0;
        re=*(fptr_r+ j * fstrd);
        im=*(fptr_i+ j * fstrd);
        *(fptr_r+ j * fstrd)=re*ps.r-im*ps.i;
        *(fptr_i+ j * fstrd)=re*ps.i+im*ps.r;
    }
    j=n_f;
    i=j-1;
    ps.r=*(fptr_r+i*fstrd);
    ps.i=*(fptr_i+i*fstrd);
    if (ps.i == 0.0){
        m = ps.r;
        if(m < 0.0)
            ps.r =-1.0;
        else
            ps.r = 1.0;
        m = (m<0) ? -m:m;
    }else{
        re=fabs(ps.r), im=fabs(ps.i);
        m = CMAG_F(re,im);
        ps.r /= m; ps.i/=m;
    }
    *(fptr_r+i*fstrd)=m;
    *(fptr_i+i*fstrd)=0.0;
    ccol_sv_f(L, l, j);vsip_csvmul_f(vsip_conj_f(ps),l,l);
    crow_sv_f(R,r,j);vsip_csvmul_f(ps,r,r);
}
static void cphaseCheck_f(csvdObj_f *svd)
{
    vsip_cmview_f *L = svd->L;
    vsip_vview_f *d = svd->d;
    vsip_vview_f *f = svd->f;
    vsip_cmview_f *R = svd->R;
    vsip_scalar_f eps0 = svd->eps0;
    vsip_length nf=f->length;
    vsip_index i,j,k;
    vsip_scalar_f ps;
    vsip_scalar_f m;
    vsip_cvview_f *l = &svd->ls_one;
    vsip_cvview_f *r = &svd->rs_one;
    vsip_scalar_f*fptr=f->block->array;
    vsip_scalar_f*dptr=d->block->array;
    vsip_scalar_f *re,*im;
    vsip_stride strd;
    for(i=0; i<d->length; i++){
        ps=dptr[i];
        m = (ps<0) ? -ps:ps;
        ps=sign_f(ps);
        if(m > eps0){
            ccol_sv_f(L,l,i);
            strd=l->stride*l->block->R->rstride;
            re=l->block->R->array+l->offset*l->block->R->rstride;
            im=l->block->I->array+l->offset*l->block->R->rstride;
            for(k=0; k<l->length*strd; k+=strd){
                re[k]*=ps;
                im[k]*=ps;
            }
            dptr[i]=m;
            if (i < nf)
                fptr[i]*=ps;
        } else {
            dptr[i]=0.0;
        }
    }
    svdZeroCheckAndSet_f(eps0,d,f);
    for (i=0; i<nf-1; i++){
        j=i+1;
        ps = fptr[i];
        m = (ps<0) ? -ps:ps;;
        ps=sign_f(ps);
        ccol_sv_f(L, l, j);
        strd=l->stride*l->block->R->rstride;
        re=l->block->R->array+l->offset*l->block->R->rstride;
        im=l->block->I->array+l->offset*l->block->R->rstride;
        for(k=0; k<l->length*strd; k+=strd){
            re[k]*=ps;
            im[k]*=ps;
        }
        crow_sv_f(R,r,j);
        strd=r->stride*r->block->R->rstride;
        re=r->block->R->array+r->offset*r->block->R->rstride;
        im=r->block->I->array+r->offset*r->block->R->rstride;
        for(k=0; k<r->length*strd; k+=strd){
            re[k]*=ps;
            im[k]*=ps;
        }
        fptr[i]=m;
        fptr[j]*=ps;
    }
    j=nf;
    i=j-1;
    ps=fptr[i];
    m=(ps<0) ? -ps:ps;
    ps=sign_f(ps);
    fptr[i]=m;
    ccol_sv_f(L, l, j);
    strd=l->stride*l->block->R->rstride;
    re=l->block->R->array+l->offset*l->block->R->rstride;
    im=l->block->I->array+l->offset*l->block->R->rstride;
    for(k=0; k<l->length*strd; k+=strd){
        re[k]*=ps;
        im[k]*=ps;
    }
    crow_sv_f(R,r,j);
    strd=r->stride*r->block->R->rstride;
    re=r->block->R->array+r->offset*r->block->R->rstride;
    im=r->block->I->array+r->offset*r->block->R->rstride;
    for(k=0; k<r->length*strd; k+=strd){
        re[k]*=ps;
        im[k]*=ps;
    }
}
void chouseProd_f(vsip_cvview_f *v, vsip_cmview_f *A, vsip_cvview_f*w)
{
    vsip_scalar_f *Aptr_r = A->block->R->array+A->offset * A->block->R->rstride;
    vsip_scalar_f *Aptr_i = A->block->I->array+A->offset * A->block->R->rstride;
    vsip_scalar_f *vptr_r = v->block->R->array+v->offset * v->block->R->rstride;
    vsip_scalar_f *vptr_i = v->block->I->array+v->offset * v->block->R->rstride;
    vsip_scalar_f *wptr_r = w->block->R->array+w->offset * w->block->R->rstride;
    vsip_scalar_f *wptr_i = w->block->I->array+w->offset * w->block->R->rstride;
    vsip_stride vstrd=v->stride * v->block->R->rstride;
    vsip_stride wstrd=w->stride * w->block->R->rstride;
    vsip_stride AcStrd=A->col_stride*A->block->R->rstride;
    vsip_stride ArStrd=A->row_stride*A->block->R->rstride;
    vsip_scalar_f beta = 2.0/vsip_cvjdot_f(v,v).r;
    vsip_index i,j,vi,wi;
    vsip_length M = A->col_length * A->col_stride * A->block->R->rstride;
    vsip_length N = A->row_length * A->row_stride * A->block->R->rstride;
    w->length = A->row_length;
    for(i=0,wi=0; i<N; i+=ArStrd,wi+=wstrd){//cvmprod
        vsip_scalar_f *ar_r=&Aptr_r[i], *ar_i=&Aptr_i[i];
        vsip_scalar_f re=0.0,im=0.0;
        for(j=0,vi=0; j<M; j+=AcStrd, vi+=vstrd){
            re +=  ar_r[j] * vptr_r[vi] + ar_i[j] * vptr_i[vi];
            im += -ar_r[j] * vptr_i[vi] + ar_i[j] * vptr_r[vi];
        }
        wptr_r[wi] = re;
        wptr_i[wi] = -im;
    }
    for(i=0, vi=0; i<M; i+=AcStrd, vi+=vstrd){
        vsip_scalar_f cr = beta * vptr_r[vi];
        vsip_scalar_f ci = beta * vptr_i[vi];
        vsip_scalar_f *aprp=Aptr_r+i;
        vsip_scalar_f *apip=Aptr_i+i;
        for(j=0, wi=0; j<N; j+=ArStrd, wi+=wstrd){
            vsip_scalar_f yr =  wptr_r[wi];
            vsip_scalar_f yi = -wptr_i[wi];
            aprp[j] -= (cr * yr - ci * yi);
            apip[j] -= (cr * yi + ci * yr);
        }
    }
}
static void cprodHouse_f(vsip_cmview_f *A, vsip_cvview_f *v, vsip_cvview_f *w)
{
    vsip_scalar_f *Aptr_r = A->block->R->array+A->offset * A->block->R->rstride;
    vsip_scalar_f *Aptr_i = A->block->I->array+A->offset * A->block->R->rstride;
    vsip_scalar_f *vptr_r = v->block->R->array+v->offset * v->block->R->rstride;
    vsip_scalar_f *vptr_i = v->block->I->array+v->offset * v->block->R->rstride;
    vsip_scalar_f *wptr_r = w->block->R->array+w->offset * w->block->R->rstride;
    vsip_scalar_f *wptr_i = w->block->I->array+w->offset * w->block->R->rstride;
    vsip_stride vstrd=v->stride * v->block->R->rstride;
    vsip_stride wstrd=w->stride * w->block->R->rstride;
    vsip_stride AcStrd=A->col_stride*A->block->R->rstride;
    vsip_stride ArStrd=A->row_stride*A->block->R->rstride;
    vsip_scalar_f beta = 2.0/vsip_cvjdot_f(v,v).r;
    vsip_index i,j,vi,wi;
    vsip_length M = A->col_length * A->col_stride * A->block->R->rstride;
    vsip_length N = A->row_length * A->row_stride * A->block->R->rstride;
    w->length = A->col_length;
    for(i=0,wi=0; i<M; i+=AcStrd,wi+=wstrd){//cvmprod
        vsip_scalar_f *ac_r=&Aptr_r[i], *ac_i=&Aptr_i[i];
        vsip_scalar_f re=0.0,im=0.0;
        for(j=0,vi=0; j<N; j+=ArStrd, vi+=vstrd){
            re += ac_r[j] * vptr_r[vi] - ac_i[j] * vptr_i[vi];
            im += ac_r[j] * vptr_i[vi] + ac_i[j] * vptr_r[vi];
        }
        wptr_r[wi] = -beta * re;
        wptr_i[wi] = -beta * im;
    }
    for(i=0, wi=0; i<M; i+=AcStrd, wi+=wstrd){
        vsip_scalar_f cr = wptr_r[wi];
        vsip_scalar_f ci = wptr_i[wi];
        vsip_scalar_f *aprp=Aptr_r+i;
        vsip_scalar_f *apip=Aptr_i+i;
        for(j=0, vi=0; j<N; j+=ArStrd, vi+=vstrd){
            vsip_scalar_f yr =  vptr_r[vi];
            vsip_scalar_f yi = -vptr_i[vi];
            aprp[j] += (cr * yr - ci * yi);
            apip[j] += (cr * yi + ci * yr);
        }
    }
}
static vsip_cvview_f *chouseVector_f(vsip_cvview_f* x)
{
    vsip_scalar_f *x0r=x->block->R->array + x->offset * x->block->R->rstride;
    vsip_scalar_f *x0i=x->block->I->array + x->offset * x->block->R->rstride;
    vsip_scalar_f nrm=cvnorm2_f(x);
    vsip_cscalar_f t,s;
    t.r=*x0r;t.i=*x0i;
    s=csign_f(t);
    s.r *= nrm; s.i *= nrm;
    s.r += t.r; s.i +=t.i;
    *x0r = s.r;*x0i=s.i;
    nrm = cvnorm2_f(x);
    if (nrm == 0.0){
        *x0r=1.0;*x0i=0.0;
    }else{
        vsip_index i;
        vsip_stride str=x->stride * x->block->R->rstride;
        vsip_length n = x->length * str;
        for(i=0; i<n; i+=str){
            x0r[i] /= nrm;
            x0i[i] /= nrm;
        }
    }
    return x;
}
static void cVHmatExtract_f(csvdObj_f *svd)
{
    vsip_cmview_f*B = svd->B;
    vsip_index i,j;
    vsip_length n = B->row_length;
    vsip_cmview_f *Bs=&svd->Bs;
    vsip_cmview_f *V=svd->R;
    vsip_cmview_f *Vs=&svd->Rs;
    vsip_cvview_f *v;
    vsip_cscalar_f t;
    if(n < 3)
        return;
    v = crow_sv_f(B,&svd->bs,0);
    for(i=n-3; i>0; i--){
        j=i+1;
        crow_sv_f(cmsv_f(B,Bs,i,j),v,0);
        t=vsip_cvget_f(v,0);vsip_cvput_f(v,0,v->block->a_one);
        cprodHouse_f(cmsv_f(V,Vs,j,j),v,svd->w);
        vsip_cvput_f(v,0,t);
    }
    crow_sv_f(cmsv_f(B,Bs,0,1),v,0);
    t=vsip_cvget_f(v,0);vsip_cvput_f(v,0,v->block->a_one);
    cprodHouse_f(cmsv_f(V,Vs,1,1),v,svd->w);
    vsip_cvput_f(v,0,t);
}
static void cUmatExtract_f(csvdObj_f *svd)
{
    vsip_cmview_f* B=svd->B;
    vsip_cmview_f* U=svd->L;
    vsip_index i;
    vsip_length m = B->col_length;
    vsip_length n = B->row_length;
    vsip_cmview_f *Bs=&svd->Bs;
    vsip_cmview_f *Us=&svd->Ls;
    vsip_cvview_f *v;
    vsip_cscalar_f t;
    v = ccol_sv_f(B,&svd->bs,0);
    if (m > n){
        i=n-1;
        ccol_sv_f(cmsv_f(B,Bs,i,i),v,0);
        t=vsip_cvget_f(v,0); vsip_cvput_f(v,0,v->block->a_one);
        chouseProd_f(v,cmsv_f(U,Us,i,i),svd->w);
        vsip_cvput_f(v,0,t);
    }
    for(i=n-2; i>0; i--){
        ccol_sv_f(cmsv_f(B,Bs,i,i),v,0);
        t=vsip_cvget_f(v,0); vsip_cvput_f(v,0,v->block->a_one);
        chouseProd_f(v,cmsv_f(U,Us,i,i),svd->w);
        vsip_cvput_f(v,0,t);
    }
    ccol_sv_f(cmsv_f(B,Bs,0,0),v,0);
    t=vsip_cvget_f(v,0); vsip_cvput_f(v,0,v->block->a_one);
    chouseProd_f(v,cmsv_f(U,Us,0,0),svd->w);
    vsip_cvput_f(v,0,t);
}
static void cbidiag_f(csvdObj_f *svd)
{
    vsip_cmview_f *B = svd->B;
    vsip_cmview_f *Bs = &svd->Bs;
    vsip_length m = B->col_length;
    vsip_length n = B->row_length;
    vsip_cvview_f *x=ccol_sv_f(B,&svd->bs,0);
    vsip_cvview_f *v=cvclone_f(x,svd->t);
    vsip_cvview_f *vs = &svd->ts;
    vsip_index i,j;
    for(i=0; i<n-1; i++){
        v->length=m-i;
        vsip_cvcopy_f_f(ccol_sv_f(cmsv_f(B,Bs,i,i),x,0),v);
        chouseVector_f(v);
        vsip_csvmul_f(vsip_cdiv_f(v->block->a_one,vsip_cvget_f(v,0)),v,v);
        chouseProd_f(v,Bs,svd->w);
        vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
        if(i < n-2){
            j = i+1;
            v->length=n-j;
            vsip_cvcopy_f_f(crow_sv_f(cmsv_f(B,Bs,i,j),x,0),v);
            chouseVector_f(v);vsip_cvconj_f(v,v);
            vsip_csvmul_f(vsip_cdiv_f(v->block->a_one,vsip_cvget_f(v,0)),v,v);
            cprodHouse_f(Bs,v,svd->w);
            vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        v->length=m-i;
        vsip_cvcopy_f_f(ccol_sv_f(cmsv_f(B,Bs,i,i),x,0),v);
        chouseVector_f(v);
        vsip_csvmul_f(vsip_cdiv_f(v->block->a_one,vsip_cvget_f(v,0)),v,v);
        chouseProd_f(v,Bs,svd->w);
        vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
    }
}
static void csvdBidiag_f(csvdObj_f *svd)
{
    svd->eps0=cmnormFro_f(svd->B)/(vsip_scalar_f)(svd->B->row_length) * 1E-10;
    cbidiag_f(svd);
    cUmatExtract_f(svd);
    cVHmatExtract_f(svd);
    cbiDiagPhaseToZero_f(svd);
    vsip_vcopy_f_f(vreal_sv_f(cdiag_sv_f(svd->B, &svd->bs, 0),&svd->rbs),svd->d);
    vsip_vcopy_f_f(vreal_sv_f(cdiag_sv_f(svd->B, &svd->bs, 1),&svd->rbs),svd->f);
}

static void cgtProd_f(vsip_index i, vsip_index j,vsip_scalar_f c, vsip_scalar_f s,csvdObj_f *svd)
{
    vsip_cmview_f* R=&svd->Rs;
    vsip_cvview_f *a1= crow_sv_f(R,&svd->rs_one,i);
    vsip_cvview_f *a2= crow_sv_f(R,&svd->rs_two,j);
    vsip_index k;
    vsip_offset o = a1->block->R->rstride * a1->offset;
    vsip_stride std=a1->stride * a1->block->R->rstride;
    vsip_length n = a1->length;
    register vsip_scalar_f *a1r= a1->block->R->array;
    register vsip_scalar_f *a1i= a1->block->I->array;
    register vsip_scalar_f *a2r= a1r;
    register vsip_scalar_f *a2i= a1i;
    register vsip_scalar_f b1r,b1i,b2r,b2i;
    a1r+=o; a1i+=o;
    o=a2->block->R->rstride * a2->offset;
    a2r+=o; a2i+=o;
    for(k=0; k<n; k++){
        b1r = *a1r, b1i=*a1i, b2r=*a2r, b2i=*a2i;
        *a1r =c * b1r + s * b2r;
        *a1i =c * b1i + s * b2i;
        *a2r =c * b2r - s * b1r;
        *a2i =c * b2i - s * b1i;
        a1r+=std;a1i+=std;a2r+=std;a2i+=std;
    }
}
static void cprodG_f(csvdObj_f *svd,vsip_index i, vsip_index j,vsip_scalar_f c, vsip_scalar_f s)
{
    vsip_cmview_f* L=&svd->Ls;
    vsip_cvview_f *a1= ccol_sv_f(L,&svd->ls_one,i);
    vsip_cvview_f *a2= ccol_sv_f(L,&svd->ls_two,j);
    vsip_index k;
    vsip_offset o = a1->block->R->rstride * a1->offset;
    register vsip_stride std=a1->stride * a1->block->R->rstride;
    vsip_length n = a1->length;
    register vsip_scalar_f *a1r= a1->block->R->array;
    register vsip_scalar_f *a1i= a1->block->I->array;
    register vsip_scalar_f *a2r= a1r;
    register vsip_scalar_f *a2i= a1i;
    register vsip_scalar_f b1r,b1i,b2r,b2i;
    a1r+=o; a1i+=o;
    o=a2->block->R->rstride * a2->offset;
    a2r+=o; a2i+=o;
    for(k=0; k<n; k++){
        b1r = *a1r, b1i=*a1i, b2r=*a2r, b2i=*a2i;
        *a1r =c * b1r + s * b2r;
        *a1i =c * b1i + s * b2i;
        *a2r =c * b2r - s * b1r;
        *a2i =c * b2i - s * b1i;
        a1r+=std;a1i+=std;a2r+=std;a2i+=std;
    }
}
static void czeroCol_f(csvdObj_f *svd)
{
    vsip_vview_f *d = &svd->ds;
    vsip_vview_f *f = &svd->fs;
    vsip_length n = f->length;
    givensObj_f g;
    vsip_scalar_f xd,xf,t;
    vsip_index i,j,k;
    if (n == 1){
        xd=VI_VGET_F(d,0);
        xf=VI_VGET_F(f,0);
        g=givensCoef_f(xd,xf);
        vsip_vput_f(d,0,g.r);
        vsip_vput_f(f,0,0.0);
        cgtProd_f(0,1,g.c,g.s,svd);
    }else if (n == 2){
        xd=VI_VGET_F(d,1);
        xf=VI_VGET_F(f,1);
        g=givensCoef_f(xd,xf);
        vsip_vput_f(d,1,g.r);
        vsip_vput_f(f,1,0.0);
        xf=VI_VGET_F(f,0);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_f(f,0,xf);
        cgtProd_f(1,2,g.c,g.s,svd);
        xd=VI_VGET_F(d,0);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,0,g.r);
        cgtProd_f(0,2,g.c,g.s,svd);
    }else{
        i=n-1; j=i-1; k=i;
        xd=VI_VGET_F(d,i);
        xf=VI_VGET_F(f,i);
        g=givensCoef_f(xd,xf);
        xf=VI_VGET_F(f,j);
        vsip_vput_f(f,i,0.0);
        vsip_vput_f(d,i,g.r);
        t=-xf*g.s; xf*=g.c;
        vsip_vput_f(f,j,xf);
        cgtProd_f(i,k+1,g.c,g.s,svd);
        while (i > 1){
            i = j; j = i-1;
            xd=VI_VGET_F(d,i);
            g=givensCoef_f(xd,t);
            vsip_vput_f(d,i,g.r);
            xf=VI_VGET_F(f,j);
            t= -xf * g.s; xf *= g.c;
            vsip_vput_f(f,j,xf);
            cgtProd_f(i,k+1,g.c,g.s,svd);
        }
        xd=VI_VGET_F(d,0);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,0,g.r);
        cgtProd_f(0,k+1,g.c,g.s,svd);
    }
}

static void czeroRow_f(csvdObj_f *svd)
{
    vsip_vview_f *d = &svd->ds;
    vsip_vview_f *f = &svd->fs;
    vsip_length n = d->length;
    givensObj_f g;
    vsip_scalar_f xd,xf,t;
    vsip_index i;
    vsip_scalar_f *dptr=d->block->array+d->block->rstride*d->offset;
    vsip_scalar_f *fptr=f->block->array+f->block->rstride*f->offset;
    vsip_stride dstrd=d->stride*d->block->rstride;
    vsip_stride fstrd=f->stride*f->block->rstride;
    xd=*dptr;
    xf=*fptr;
    g=givensCoef_f(xd,xf);
    if (n == 1){
        *dptr=g.r;/*vsip_vput_f(d,0,g.r);*/
        *fptr=0.0;/*vsip_vput_f(f,0,0.0);*/
        cprodG_f(svd,1,0,g.c,g.s);
    }else{
        *dptr=g.r;/*vsip_vput_f(d,0,g.r);*/
        *fptr=0.0;/*vsip_vput_f(f,0,0.0);*/
        xf=*(fptr+fstrd);
        t= -xf * g.s; xf *= g.c;
        *(fptr+fstrd)=xf;
        cprodG_f(svd,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=*(dptr+i*dstrd);
            g=givensCoef_f(xd,t);
            cprodG_f(svd,i+1,0,g.c,g.s);
            *(dptr+i*dstrd)=g.r;
            xf=*(fptr+(i+1)*fstrd);
            t=-xf * g.s; xf *= g.c;
            *(fptr+(i+1)*fstrd)=xf;
        }
        xd=*(dptr+(n-1)*dstrd);
        g=givensCoef_f(xd,t);
        *(dptr+(n-1)*dstrd)=g.r;
        cprodG_f(svd,n,0,g.c,g.s);
    }
}
static void csvdStep_f(csvdObj_f *svd)
{
    vsip_vview_f *d = &svd->ds;
    vsip_vview_f *f = &svd->fs;
    givensObj_f g;
    vsip_length n = d->length;
    vsip_scalar_f mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_f t=0.0;
    vsip_index i,j,k;
    vsip_scalar_f d2=0.0,f1=0.0,d3=0.0,f2=0.0;
    vsip_scalar_f *fptr,*dptr,*tdptr,*tfptr;
    vsip_stride fstd=f->stride*f->block->rstride, dstd=d->stride*d->block->rstride;
    dptr=d->block->array+d->offset*d->block->rstride;
    fptr=f->block->array+f->offset*f->block->rstride;
    if(n >= 3){
        d2=*(dptr+dstd*(n-2));f1= *(fptr+fstd*(n-3));d3 = *(dptr+dstd*(n-1));f2= *(fptr+fstd*(n-2));
    } else if(n == 2){
        d2=*dptr; d3=*(dptr+dstd); f1=0; f2=*fptr;
    } else {
        printf("should not be here (see svdStep_f");
        exit(-1);
    }
    mu = svdMu_f(d2,f1,d3,&f2);
    if(f2 == 0.0) *(fptr+fstd*(n-2)) = 0.0;
    x1=*dptr;
    x2 = x1 * *fptr;
    x1 *= x1; x1 -= mu;
    g=givensCoef_f(x1,x2);
    x1=*dptr;x2=*fptr;
    *fptr=g.c * x2 - g.s * x1;
    *dptr=x1 * g.c + x2 * g.s;
    tdptr=dptr+dstd;
    t=*tdptr; *tdptr=t*g.c;
    t*=g.s;
    cgtProd_f(0,1,g.c,g.s,svd);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        tdptr=dptr+i*dstd;
        tfptr=fptr+i*fstd;
        g = givensCoef_f(*tdptr,t);
        *tdptr=g.r;
        x1 = *(tdptr+dstd)*g.c;
        x2=*tfptr*g.s;
        t= x1 - x2;
        x1=VI_VGET_F(f,i) * g.c;
        x2=VI_VGET_F(d,j) * g.s ;
        vsip_vput_f(f,i,x1+x2);
        vsip_vput_f(d,j,t);
        x1=VI_VGET_F(f,j);
        t=g.s * x1;
        vsip_vput_f(f,j, x1*g.c);
        cprodG_f(svd,i, j, g.c, g.s);
        g=givensCoef_f(VI_VGET_F(f,i),t);
        vsip_vput_f(f,i,g.r);
        x1=VI_VGET_F(d,j); x2=VI_VGET_F(f,j);
        vsip_vput_f(d,j,g.c * x1 + g.s * x2); vsip_vput_f(f,j,g.c * x2 - g.s * x1);
        x1=VI_VGET_F(d,k);
        t=g.s * x1; vsip_vput_f(d,k,x1*g.c);
        cgtProd_f(j,k, g.c, g.s,svd);
    }
    i=n-2; j=n-1;
    g = givensCoef_f(VI_VGET_F(d,i),t);
    vsip_vput_f(d,i,g.r);
    x1=VI_VGET_F(d,j)*g.c; x2=VI_VGET_F(f,i)*g.s;
    t=x1 - x2;
    x1 = VI_VGET_F(f,i) * g.c; x2=VI_VGET_F(d,j) * g.s;
    vsip_vput_f(f,i,x1+x2);
    vsip_vput_f(d,j,t);
    cprodG_f(svd,i, j, g.c, g.s);
}
static void csvdIteration_f(csvdObj_f *svd)
{
    vsip_cmview_f *L0=svd->L;
    vsip_vview_f *d0 = svd->d;
    vsip_vview_f *f0 = svd->f;
    vsip_cmview_f *R0 = svd->R;
    vsip_scalar_f eps0 = svd->eps0;
    vsip_vview_f *d=&svd->ds;
    vsip_vview_f *f=&svd->fs;
    vsip_cmview_f *L=&svd->Ls;
    vsip_cmview_f *R=&svd->Rs;
    vsip_length n;
    svdCorner cnr;
    vsip_index k;
    vsip_length cntr=0;
    vsip_length maxcntr=5*d0->length;
    *d=*d0;*f=*f0;
    while (cntr++ < maxcntr){
        cphaseCheck_f(svd);
        cnr=svdCorners_f(f0);
        if (cnr.j == 0)
            break;
        ivsv_f(d0,d,cnr.i,cnr.j);
        ivsv_f(f0,f,cnr.i,cnr.j-1);
        cimsv_f(L0,L,0,0,cnr.i,cnr.j);
        cimsv_f(R0,R,cnr.i,cnr.j,0,0);
        n=f->length;
        k=zeroFind_f(d,eps0);
        if (k > 0){
            k=k-1;
            if(VI_VGET_F(d,n) == 0.0){
                czeroCol_f(svd);
                printf("zeroCol\n");
            }else{
                printf("zeroRow\n");
                cimsv_f(L,L,0,0,k,0);
                d->length-=(k+1);
                d->offset += (k+1) * d->stride*d->block->rstride;
                f->length -= k;
                f->offset += k * f->stride*f->block->rstride;
                czeroRow_f(svd);
            }
        }else{
            csvdStep_f(svd);
        }
    }
    printf("maxcounter %lu, count %lu\n",maxcntr,cntr);
}

static void svdSort_f(svdObj_f *svd)
{
    vsip_vview_f *d = svd->d;
    vsip_length n=d->length;
    vsip_vview_vi* indx_L = svd->indx_L;
    vsip_vview_vi* indx_R = svd->indx_R;
    vsip_mview_f *L0 = svd->L; vsip_mview_f *L=&svd->Ls;
    vsip_mview_f *R0 = svd->R;
    vsip_vsortip_f(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vsip_vcopy_vi_vi(indx_L,indx_R);
    imsv_f( L0, L, 0,0, 0, n);
    vsip_mpermute_once_f(L,VSIP_COL,indx_L,L);
    vsip_mpermute_once_f(R0,VSIP_ROW,indx_R,R0);
}
static void csvdSort_f(csvdObj_f *svd)
{
    vsip_cmview_f* L0 = svd->L;
    vsip_vview_f* d = svd->d;
    vsip_cmview_f* R0 = svd->R;
    vsip_length n=d->length;
    vsip_vview_vi* indx_L = svd->indx_L;
    vsip_vview_vi* indx_R = svd->indx_R;
    vsip_cmview_f *L=&svd->Ls;
    vsip_vsortip_f(d,VSIP_SORT_BYVALUE,VSIP_SORT_DESCENDING,VSIP_TRUE,indx_L);
    vsip_vcopy_vi_vi(indx_L,indx_R);
    cimsv_f( L0, L, 0,0, 0, n);
    vsip_cmpermute_once_f(L,VSIP_COL,indx_L,L);
    vsip_cmpermute_once_f(R0,VSIP_ROW,indx_R,R0);
}

static void svdFinalize_f(svdObj_f *s)
{
    if(s) {
    vsip_valldestroy_f(s->t);
    vsip_valldestroy_f(s->w);
    vsip_malldestroy_f(s->B);
    vsip_malldestroy_f(s->R);
    vsip_malldestroy_f(s->L);
    vsip_valldestroy_vi(s->indx_L);
    vsip_valldestroy_vi(s->indx_R);
    vsip_valldestroy_f(s->d);
    vsip_valldestroy_f(s->f);
    free(s);
    }
    s=NULL;
}
static svdObj_f* svdInit_f(vsip_length m, vsip_length n)
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
    if(!(s->t = vsip_vcreate_f(m,VSIP_MEM_NONE))) s->init++; else s->ts = *s->t;
    if(!(s->w = vsip_vcreate_f(m,VSIP_MEM_NONE))) s->init++;
    if(!(s->B=vsip_mcreate_f(m,n,VSIP_ROW,VSIP_MEM_NONE))) s->init++;
    if(!(s->L=meye_f(m)))s->init++;
    if(!(s->R=meye_f(n)))s->init++;
    if(!(s->indx_L=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    if(!(s->indx_R=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    if(!(s->d = vsip_vcreate_f(n,VSIP_MEM_NONE))) s->init++;
    if(!(s->f = vsip_vcreate_f(n-1,VSIP_MEM_NONE)))s->init++;
    if(s->init){
        svdFinalize_f(s);
        return NULL;
    }
    return s;
}
static void svd_f(svdObj_f *s)
{
    svdBidiag_f(s);
    svdIteration_f(s);
    svdSort_f(s);
}

static void csvdFinalize_f(csvdObj_f *s)
{
    if(s) {
    vsip_cvalldestroy_f((s)->t);
    vsip_cvalldestroy_f((s)->w);
    vsip_cmalldestroy_f((s)->B);
    vsip_cmalldestroy_f((s)->R);
    vsip_cmalldestroy_f((s)->L);
    vsip_valldestroy_vi((s)->indx_L);
    vsip_valldestroy_vi((s)->indx_R);
    vsip_valldestroy_f((s)->d);
    vsip_valldestroy_f((s)->f);
    free(s);
    }
    s=NULL;
}
static csvdObj_f* csvdInit_f(vsip_length m, vsip_length n)
{
    csvdObj_f *s=malloc(sizeof(csvdObj_f));
    if(m < n){
        printf("Column length must not be less than row length");
        return NULL;
    }
    if(!s) {
        printf("\nfailed to allocate svd object\n");
        return NULL;
    }
    s->init=0;
    if(!(s->t = vsip_cvcreate_f(m,VSIP_MEM_NONE)))s->init++;else s->ts = *s->t;
    if(!(s->w = vsip_cvcreate_f(m,VSIP_MEM_NONE)))s->init++;
    if(!(s->B=vsip_cmcreate_f(m,n,VSIP_ROW,VSIP_MEM_NONE)))s->init++;
    s->L = cmeye_f(s->L,m); if(!s->L) s->init++;
    s->R = cmeye_f(s->R,n); if(!s->R) s->init++;
    if(!(s->indx_L=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    if(!(s->indx_R=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    if(!(s->d = vsip_vcreate_f(n,VSIP_MEM_NONE)))s->init++;
    if(!(s->f = vsip_vcreate_f(n-1,VSIP_MEM_NONE)))s->init++;
    if(s->init){
        csvdFinalize_f(s);
        return NULL;
    }
    return s;
}
static void csvd_f(csvdObj_f *s)
{
    csvdBidiag_f(s);
    csvdIteration_f(s);
    csvdSort_f(s);
}
