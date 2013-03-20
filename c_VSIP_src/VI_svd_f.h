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

#define scaleV(v) { vsip_scalar_f *p = v->block->array + v->offset * v->block->rstride;\
vsip_stride std = v->stride * v->block->rstride;vsip_length n = v->length * std;\
vsip_scalar_f scl = p[0];p[0]=1.0;vsip_index k;for(k=std; k<n; k+=std) p[k] /= scl; \
}

typedef struct {vsip_index i; vsip_index j;} svdCorner;
typedef struct {vsip_scalar_f c; vsip_scalar_f s; vsip_scalar_f r;}givensObj_f ;
typedef struct {vsip_vview_f* t; vsip_vview_f ts;
                vsip_mview_f* B; vsip_mview_f Bs; vsip_vview_f bs;
                vsip_mview_f* L; vsip_mview_f Ls; vsip_vview_f ls_one; vsip_vview_f ls_two;
                vsip_vview_f* d; vsip_vview_f ds;
                vsip_vview_f* f; vsip_vview_f fs;
                vsip_mview_f* R; vsip_mview_f Rs; vsip_vview_f rs_one; vsip_vview_f rs_two;
                vsip_scalar_f eps0;int init;
                vsip_vview_vi *indx_L; vsip_vview_vi *indx_R;} svdObj_f;
typedef struct {vsip_cvview_f* t; vsip_cvview_f ts;
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

static void svdZeroCheckAndSet_f(vsip_scalar_f e, vsip_vview_f *b0, vsip_vview_f *b1)
{
    vsip_index i;
    vsip_length n = b1->length;
    vsip_scalar_f z = 0.0;
    for(i=0; i<n; i++){
        vsip_scalar_f b = vsip_mag_f(vsip_vget_f(b1,i));
        vsip_scalar_f a = e*(vsip_mag_f(vsip_vget_f(b0,i))
                        +    vsip_mag_f(vsip_vget_f(b0,i+1)));
        if( b < a ) vsip_vput_f(b1,i,z);
    }
} /* needs work */

/* sign function as defined in http://www.netlib.org/lapack/lawnspdf/lawn148.pdf */
static vsip_scalar_f sign_f(vsip_scalar_f a_in)
{
    if(a_in < 0.0)
       return -1.0;
    else 
       return 1.0;
}
static vsip_cscalar_f csign_f(vsip_cscalar_f a_in)
{
    vsip_scalar_f re = a_in.r;
    vsip_scalar_f im = a_in.i;
    vsip_scalar_f t=vsip_hypot_f(re,im);
    vsip_cscalar_f retval;
    retval.r=0.0; retval.i = 0.0;
    if(t == 0.0){
        retval.r = 1.0;
        return retval;
    } else if (im==0.0) {
        retval.r = sign_f(re);
        return retval;
    } else {
        retval.r = re/t;
        retval.i = im/t;
        return retval;
    }
}

static void biDiagPhaseToZero_f( svdObj_f *svd)
{
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
    for(i=0; i<n_d; i++){
        ps=VI_VGET_F(d,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        if(m > eps0){
            col_sv_f(L,l,i);
            {
                vsip_scalar_f *p = l->block->array + l->offset * l->block->rstride;
                vsip_stride std = l->stride * l->block->rstride;
                vsip_length n = l->length * std;
                vsip_index k;
                for(k=0; k<n; k+=std) p[k] *= ps;
            } /* vsip_svmul_f(ps,l,l); */
            vsip_vput_f(d,i,m);
            if (i < n_f)
                vsip_vput_f(f,i,ps*VI_VGET_F(f,i));
        } else {
            vsip_vput_f(d,i,0.0);
        }
    }
    svdZeroCheckAndSet_f(eps0,d,f);          
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = VI_VGET_F(f,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        col_sv_f(L, l, j);
        {
            vsip_scalar_f *p = l->block->array + l->offset * l->block->rstride;
            vsip_stride std = l->stride * l->block->rstride;
            vsip_length n = l->length * std;
            vsip_index k;
            for(k=0; k<n; k+=std) p[k] *= ps;
        } /* vsip_svmul_f(ps,l,l); */
        row_sv_f(R,r,j);
        {
            vsip_scalar_f *p = r->block->array + r->offset * r->block->rstride;
            vsip_stride std = r->stride * r->block->rstride;
            vsip_length n = r->length * std;
            vsip_index k;
            for(k=0; k<n; k+=std) p[k] *= ps;
        } /* vsip_svmul_f(ps,r,r); */
        vsip_vput_f(f,i,m);
        vsip_vput_f(f,j,ps * VI_VGET_F(f,j));
    }
    j=n_f;
    i=j-1;
    ps=VI_VGET_F(f,i);
    m=vsip_mag_f(ps);
    ps=sign_f(ps);
    vsip_vput_f(f,i,m);
    col_sv_f(L, l, j);
    {
        vsip_scalar_f *p = l->block->array + l->offset * l->block->rstride;
        vsip_stride std = l->stride * l->block->rstride;
        vsip_length n = l->length * std;
        vsip_index k;
        for(k=0; k<n; k+=std) p[k] *= ps;
    } /*vsip_svmul_f(ps,l,l); */
    row_sv_f(R,r,j);
    {
        vsip_scalar_f *p = r->block->array + r->offset * r->block->rstride;
        vsip_stride std = r->stride * r->block->rstride;
        vsip_length n = r->length * std;
        vsip_index k;
        for(k=0; k<n; k+=std) p[k] *= ps;
    } /* vsip_svmul_f(ps,r,r); */
} 
static void phaseCheck_f(svdObj_f *svd)
{
    biDiagPhaseToZero_f(svd);
} 

static void houseProd_f(vsip_vview_f *v, vsip_mview_f *A)
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
static void prodHouse_f(vsip_mview_f *A, vsip_vview_f *v)
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
    vsip_scalar_f t = VI_VGET_F(x,0);
    vsip_scalar_f s = t +  sign_f(t) * nrm;
    vsip_vput_f(x,0,s); 
    nrm = vnorm2_f(x);
    if (nrm == 0.0)
        vsip_vput_f(x,0,1.0); 
    else {
        vsip_scalar_f *p = x->block->array + x->offset * x->block->rstride;
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
    vsip_length n = vsip_mgetrowlength_f(B);
    vsip_mview_f *Bs=&svd->Bs;
    vsip_mview_f *V=svd->R;
    vsip_mview_f *Vs=&svd->Rs;
    vsip_vview_f *v;
    vsip_scalar_f t;
    if(n < 3)
        return;
    v = row_sv_f(B,&svd->bs,0);
    for(i=n-3; i>0; i--){
        j=i+1;
        row_sv_f(msv_f(B,Bs,i,j),v,0);
        t=VI_VGET_F(v,0);vsip_vput_f(v,0,1.0);
        prodHouse_f(msv_f(V,Vs,j,j),v);
        vsip_vput_f(v,0,t);
    }
    row_sv_f(msv_f(B,Bs,0,1),v,0);
    t=VI_VGET_F(v,0);vsip_vput_f(v,0,1.0);
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
    vsip_mview_f *Bs=&svd->Bs;
    vsip_mview_f *Us=&svd->Ls;
    vsip_vview_f *v;
    vsip_scalar_f t;
    v = col_sv_f(B,&svd->bs,0);
    if (m > n){
        i=n-1;
        col_sv_f(msv_f(B,Bs,i,i),v,0);
        t=VI_VGET_F(v,0); vsip_vput_f(v,0,1.0);
        houseProd_f(v,msv_f(U,Us,i,i));
        vsip_vput_f(v,0,t);
    }
    for(i=n-2; i>0; i--){
        col_sv_f(msv_f(B,Bs,i,i),v,0);
        t=VI_VGET_F(v,0); vsip_vput_f(v,0,1.0);
        houseProd_f(v,msv_f(U,Us,i,i));
        vsip_vput_f(v,0,t);
    }
    col_sv_f(msv_f(B,Bs,0,0),v,0);
    t=VI_VGET_F(v,0); vsip_vput_f(v,0,1.0);
    houseProd_f(v,msv_f(U,Us,0,0));
    vsip_vput_f(v,0,t);
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
        houseProd_f(v,Bs);
        VI_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
        if(i < n-2){
            j = i+1;
            v->length = n-j;
            VI_vcopy_f_f(row_sv_f(msv_f(B,Bs,i,j),x,0),v);
            houseVector_f(v);
            scaleV(v)         /*   vsip_svmul_f(1.0/VI_VGET_F(v,0),v,v);*/
            prodHouse_f(Bs,v);
            VI_vcopy_f_f(vsv_f(v,vs,1),vsv_f(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_vputlength_f(v,m-i);
        vsip_vcopy_f_f(col_sv_f(msv_f(B,Bs,i,i),x,0),v);
        houseVector_f(v);
        scaleV(v)         /*vsip_svmul_f(1.0/VI_VGET_F(v,0),v,v); */
        houseProd_f(v,Bs);
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
    VI_vcopy_f_f(diag_sv_f(B,&svd->bs,0),svd->d);
    VI_vcopy_f_f(diag_sv_f(B,&svd->bs,1),svd->f);
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
    vsip_vview_f *d=&svd->ds;
    vsip_vview_f *f=&svd->fs;
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
        gtProd_f(0,1,g.c,g.s,svd);
    }else if (n == 2){
        xd=VI_VGET_F(d,1);
        xf=VI_VGET_F(f,1);
        g=givensCoef_f(xd,xf);
        vsip_vput_f(d,1,g.r);
        vsip_vput_f(f,1,0.0);
        xf=VI_VGET_F(f,0);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_f(f,0,xf);
        gtProd_f(1,2,g.c,g.s,svd);
        xd=VI_VGET_F(d,0);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,0,g.r);
        gtProd_f(0,2,g.c,g.s,svd);
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
        gtProd_f(i,k+1,g.c,g.s,svd);
        while (i > 1){
            i = j; j = i-1;
            xd=VI_VGET_F(d,i);
            g=givensCoef_f(xd,t);
            vsip_vput_f(d,i,g.r);
            xf=VI_VGET_F(f,j);
            t= -xf * g.s; xf *= g.c;
            vsip_vput_f(f,j,xf);
            gtProd_f(i,k+1,g.c,g.s,svd);
        }
        xd=VI_VGET_F(d,0);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,0,g.r);
        gtProd_f(0,k+1,g.c,g.s,svd);
    }
} 
static void zeroRow_f(svdObj_f *svd)
{
    vsip_vview_f *d = &svd->ds;
    vsip_vview_f *f = &svd->fs;
    vsip_length n = d->length;
    givensObj_f g;
    vsip_scalar_f xd,xf,t;
    vsip_index i;
    xd=VI_VGET_F(d,0);
    xf=VI_VGET_F(f,0);
    g=givensCoef_f(xd,xf);
    if (n == 1){
        vsip_vput_f(f,0,0.0);
        vsip_vput_f(d,0,g.r);
    }else{
        vsip_vput_f(f,0,0.0);
        vsip_vput_f(d,0,g.r);
        xf=VI_VGET_F(f,1);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_f(f,1,xf);
        prodG_f(svd,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=VI_VGET_F(d,i);
            g=givensCoef_f(xd,t);
            prodG_f(svd,i+1,0,g.c,g.s);
            vsip_vput_f(d,i,g.r);
            xf=VI_VGET_F(f,i+1);
            t=-xf * g.s; xf *= g.c;
            vsip_vput_f(f,i+1,xf);
        }
        xd=VI_VGET_F(d,n-1);
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
    vsip_index j = d->length;
    vsip_scalar_f xd=VI_VGET_F(d,j-1);
    while(xd > eps0){
        if (j > 1){ 
            j -= 1;
            xd=VI_VGET_F(d,j-1);
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
    vsip_index j=f->length-1;
    vsip_index i;
    while((j > 0) && (VI_VGET_F(f,j) == 0.0))
        j-=1;
    if(j == 0 && VI_VGET_F(f,0) == 0.0){
        crnr.i=0;
        crnr.j=0;
    } else {
        i = j;
        j += 1;
        while((i > 0) && (VI_VGET_F(f,i) != 0.0))
            i -= 1;
        if((i == 0) && (VI_VGET_F(f,0)== 0.0)){
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
    vsip_vview_f *d = &svd->ds;
    vsip_vview_f *f = &svd->fs;
    givensObj_f g;
    vsip_length n = d->length;
    vsip_scalar_f mu=0.0, x1=0.0, x2=0.0;
    vsip_scalar_f t=0.0;
    vsip_index i,j,k;
    vsip_scalar_f d2,f1,d3,f2;  
    if(n >= 3){
        d2=VI_VGET_F(d,n-2);f1= VI_VGET_F(f,n-3);d3 = VI_VGET_F(d,n-1);f2= VI_VGET_F(f,n-2);
    } else if(n == 2){
        d2=VI_VGET_F(d,0);f1= 0.0;d3 = VI_VGET_F(d,1);f2= VI_VGET_F(f,0);
    } else {
        d2=VI_VGET_F(d,0);f1 = 0.0;d3 = 0.0;f2 = 0.0;   
    }
    mu = svdMu_f(d2,f1,d3,f2);
    x1=VI_VGET_F(d,0);
    x2 = x1 * VI_VGET_F(f,0); 
    x1 *= x1; x1 -= mu;   
    g=givensCoef_f(x1,x2);
    x1=VI_VGET_F(d,0);x2=VI_VGET_F(f,0);
    vsip_vput_f(f,0,g.c * x2 - g.s * x1);
    vsip_vput_f(d,0,x1 * g.c + x2 * g.s); 
    t=VI_VGET_F(d,1); vsip_vput_f(d,1,t*g.c);
    t*=g.s;
    gtProd_f(0,1,g.c,g.s,svd);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_f(VI_VGET_F(d,i),t);
        vsip_vput_f(d,i,g.r);      
        x1=VI_VGET_F(d,j)*g.c; 
        x2=VI_VGET_F(f,i)*g.s;
        t= x1 - x2;       
        x1=VI_VGET_F(f,i) * g.c;
        x2=VI_VGET_F(d,j) * g.s ;      
        vsip_vput_f(f,i,x1+x2);
        vsip_vput_f(d,j,t);       
        x1=VI_VGET_F(f,j);
        t=g.s * x1; 
        vsip_vput_f(f,j, x1*g.c);
        prodG_f(svd,i, j, g.c, g.s);
        g=givensCoef_f(VI_VGET_F(f,i),t);
        vsip_vput_f(f,i,g.r);
        x1=VI_VGET_F(d,j); x2=VI_VGET_F(f,j);
        vsip_vput_f(d,j,g.c * x1 + g.s * x2); vsip_vput_f(f,j,g.c * x2 - g.s * x1);
        x1=VI_VGET_F(d,k);
        t=g.s * x1; vsip_vput_f(d,k,x1*g.c);
        gtProd_f(j,k, g.c, g.s,svd);
    }
    i=n-2; j=n-1;
    g = givensCoef_f(VI_VGET_F(d,i),t);
    vsip_vput_f(d,i,g.r);
    x1=VI_VGET_F(d,j)*g.c; x2=VI_VGET_F(f,i)*g.s;
    t=x1 - x2;
    x1 = VI_VGET_F(f,i) * g.c; x2=VI_VGET_F(d,j) * g.s;
    vsip_vput_f(f,i,x1+x2);
    vsip_vput_f(d,j,t);
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
    vsip_length maxcntr=20*d0->length;
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
        if (k > 0){
            if(VI_VGET_F(d,n) == 0.0){
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
static vsip_cmview_f* cimsv_f( vsip_cmview_f *B, vsip_cmview_f *BS, vsip_index i1,vsip_index j1, 
                                                                    vsip_index i2, vsip_index j2)
{
    *BS=*B;
    if(j1 == 0) j1 =BS->col_length;
    if(j2 == 0) j2 =BS->row_length;
    BS->col_length = (j1 - i1);
    BS->row_length = (j2 - i2);
    BS->offset += i2 * BS->row_stride + i1 * BS->col_stride;
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
static vsip_cmview_f* cmeye_f(vsip_length n)
{
    vsip_cvview_f d;
    vsip_cmview_f *retval = vsip_cmcreate_f(n,n,VSIP_ROW,VSIP_MEM_NONE);
    if(retval){
        d.block = retval->block; d.length = n; d.stride = n+1; d.offset = 0;
        vsip_cmfill_f(retval->block->a_zero,retval);
        VI_cvfill_f(retval->block->a_one,&d);
    } 
    return retval;
}

static void csvdZeroCheckAndSet_f(vsip_scalar_f e, vsip_cvview_f *b0, vsip_cvview_f *b1)
{
    vsip_index i;
    vsip_length n = b1->length;
    for(i=0; i<n; i++){
        vsip_scalar_f b = vsip_cmag_f(vsip_cvget_f(b1,i));
        vsip_scalar_f a = e*(vsip_cmag_f(vsip_cvget_f(b0,i))
                        +    vsip_cmag_f(vsip_cvget_f(b0,i+1)));
        if( b < a ) vsip_cvput_f(b1,i,b1->block->a_zero);
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
    for(i=0; i<n_d; i++){
        ps=vsip_cvget_f(d,i);
        if(ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps=vsip_cmplx_f(-1.0,0.0);
            else
                ps= vsip_cmplx_f(1.0,0.0);
            m = vsip_mag_f(m); 
        } else {
            m=vsip_cmag_f(ps);
            ps.r /= m; ps.i/=m;
        }
        if(m > eps0){
            ccol_sv_f(L,l,i);vsip_csvmul_f(ps,l,l);
            vsip_cvput_f(d,i,vsip_cmplx_f(m,0));
            if (i < n_f)
                vsip_cvput_f(f,i,vsip_cjmul_f(vsip_cvget_f(f,i),ps));
        }else{
            vsip_cvput_f(d,i,d->block->a_zero);
        }
    }
    csvdZeroCheckAndSet_f(eps0,d,f);          
    for (i=0; i<n_f-1; i++){
        j=i+1;
        ps = vsip_cvget_f(f,i);
        if (ps.i == 0.0){
            m = ps.r;
            if (m < 0.0)
                ps=vsip_cmplx_f(-1.0,0.0);
            else
                ps= vsip_cmplx_f(1.0,0.0);
            m = vsip_mag_f(m);
        }else{
            m=vsip_cmag_f(ps);
            ps.r /= m; ps.i/=m;
        }
        ccol_sv_f(L, l, j);vsip_csvmul_f(vsip_conj_f(ps),l,l);
        crow_sv_f(R,r,j);vsip_csvmul_f(ps,r,r);
        vsip_cvput_f(f,i,vsip_cmplx_f(m,0));
        vsip_cvput_f(f,j,vsip_cmul_f(vsip_cvget_f(f,j),ps));
    }
    j=n_f;
    i=j-1;
    ps=vsip_cvget_f(f,i);
    if (ps.i == 0.0){
        m = ps.r;
        if(m < 0.0)
            ps=vsip_cmplx_f(-1.0,0.0);
        else
            ps= vsip_cmplx_f(1.0,0.0);
        m = vsip_mag_f(m);
    }else{
        m=vsip_cmag_f(ps);
        ps.r /= m; ps.i/=m;
    }
    vsip_cvput_f(f,i,vsip_cmplx_f(m,0.0));
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
   vsip_index i,j;
   vsip_scalar_f ps;
   vsip_scalar_f m;
   vsip_cvview_f *l = &svd->ls_one;
   vsip_cvview_f *r = &svd->rs_one;
   for(i=0; i<d->length; i++){
        ps=VI_VGET_F(d,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        if(m > eps0){
            ccol_sv_f(L,l,i);vsip_rscvmul_f(ps,l,l);
            vsip_vput_f(d,i,m);
            if (i < nf)
                vsip_vput_f(f,i,ps*VI_VGET_F(f,i));
        } else {
            vsip_vput_f(d,i,0.0);
        }
    }
    svdZeroCheckAndSet_f(eps0,d,f);          
    for (i=0; i<nf-1; i++){
        j=i+1;
        ps = VI_VGET_F(f,i);
        m = vsip_mag_f(ps);
        ps=sign_f(ps);
        ccol_sv_f(L, l, j);vsip_rscvmul_f(ps,l,l);
        crow_sv_f(R,r,j);vsip_rscvmul_f(ps,r,r);
        vsip_vput_f(f,i,m);
        vsip_vput_f(f,j,ps * VI_VGET_F(f,j));
    }
    j=nf;
    i=j-1;
    ps=VI_VGET_F(f,i);
    m=vsip_mag_f(ps);
    ps=sign_f(ps);
    vsip_vput_f(f,i,m);
    ccol_sv_f(L, l, j);vsip_rscvmul_f(ps,l,l);
    crow_sv_f(R,r,j);vsip_rscvmul_f(ps,r,r);
}

void chouseProd_f(vsip_cvview_f *v, vsip_cmview_f *A)
{
    vsip_cmattr_f a_atr; 
    vsip_cvview_f *w;
    vsip_cmview_f *B;
    vsip_scalar_f beta = 2.0/vsip_cvjdot_f(v,v).r;
    vsip_cmgetattrib_f(A,&a_atr);
    B=vsip_cmcreate_f(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_cvcreate_f(a_atr.row_length,VSIP_MEM_NONE);
    vsip_cvconj_f(v,v);
    vsip_cvmprod_f(v,A,w);vsip_cvconj_f(w,w);
    vsip_cvconj_f(v,v);
    vsip_cvouter_f(vsip_cmplx_f(beta,0.0),v,w,B);
    vsip_cmsub_f(A,B,A);
    vsip_cvalldestroy_f(w);
    vsip_cmalldestroy_f(B);
} /* needs work on OPU*/
void cprodHouse_f(vsip_cmview_f *A, vsip_cvview_f *v)
{
    vsip_cmattr_f a_atr; 
    vsip_cvview_f *w;
    vsip_cmview_f *B;
    vsip_scalar_f beta = 2.0/vsip_cvjdot_f(v,v).r;
    vsip_cmgetattrib_f(A,&a_atr);
    B=vsip_cmcreate_f(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_cvcreate_f(a_atr.col_length,VSIP_MEM_NONE);
    vsip_cmvprod_f(A,v,w);
    vsip_cvouter_f(vsip_cmplx_f(beta,0.0),w,v,B);
    vsip_cmsub_f(A,B,A);
    vsip_cvalldestroy_f(w);
    vsip_cmalldestroy_f(B);
} /* needs work on OPU*/
static vsip_cvview_f *chouseVector_f(vsip_cvview_f* x)
{
    vsip_cscalar_f t = vsip_cvget_f(x,0); /*x[0]*/
    vsip_scalar_f nrm=cvnorm2_f(x); /* x.norm2 */
    vsip_cscalar_f s = vsip_cadd_f(t, vsip_cmul_f(csign_f(t), vsip_cmplx_f(nrm, 0.0)));
    vsip_cvput_f(x,0,s);
    nrm = cvnorm2_f(x);
    if (nrm == 0.0)
        vsip_cvput_f(x,0,x->block->a_one);
    else
        vsip_rscvmul_f(1.0/nrm,x,x);
    return x;
}
static void cVHmatExtract_f(csvdObj_f *svd)
{
    vsip_cmview_f*B = svd->B;
    vsip_index i,j;
    vsip_length n = vsip_cmgetrowlength_f(B);
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
        cprodHouse_f(cmsv_f(V,Vs,j,j),v);
        vsip_cvput_f(v,0,t);
    }
    crow_sv_f(cmsv_f(B,Bs,0,1),v,0);
    t=vsip_cvget_f(v,0);vsip_cvput_f(v,0,v->block->a_one);
    cprodHouse_f(cmsv_f(V,Vs,1,1),v);
    vsip_cvput_f(v,0,t);       
} 
static void cUmatExtract_f(csvdObj_f *svd)
{
    vsip_cmview_f* B=svd->B;
    vsip_cmview_f *U=svd->L;
    vsip_index i;
    vsip_length m = vsip_cmgetcollength_f(B);
    vsip_length n = vsip_cmgetrowlength_f(B);
    vsip_cmview_f *Bs=&svd->Bs;
    vsip_cmview_f *Us=&svd->Ls;
    vsip_cvview_f *v;
    vsip_cscalar_f t;
    v = ccol_sv_f(B,&svd->bs,0);
    if (m > n){
        i=n-1;
        ccol_sv_f(cmsv_f(B,Bs,i,i),v,0);
        t=vsip_cvget_f(v,0); vsip_cvput_f(v,0,v->block->a_one);
        chouseProd_f(v,cmsv_f(U,Us,i,i));
        vsip_cvput_f(v,0,t);
    }
    for(i=n-2; i>0; i--){
        ccol_sv_f(cmsv_f(B,Bs,i,i),v,0);
        t=vsip_cvget_f(v,0); vsip_cvput_f(v,0,v->block->a_one);
        chouseProd_f(v,cmsv_f(U,Us,i,i));
        vsip_cvput_f(v,0,t);
    } 
    ccol_sv_f(cmsv_f(B,Bs,0,0),v,0);
    t=vsip_cvget_f(v,0); vsip_cvput_f(v,0,v->block->a_one);
    chouseProd_f(v,cmsv_f(U,Us,0,0));
    vsip_cvput_f(v,0,t);
} 
static void cbidiag_f(csvdObj_f *svd)
{
    vsip_cmview_f *B = svd->B;
    vsip_cmview_f *Bs = &svd->Bs;
    vsip_length m = vsip_cmgetcollength_f(B);
    vsip_length n = vsip_cmgetrowlength_f(B);
    vsip_cvview_f *x=ccol_sv_f(B,&svd->bs,0);
    vsip_cvview_f *v=cvclone_f(x,svd->t);
    vsip_cvview_f *vs = &svd->ts;
    vsip_index i,j;
    for(i=0; i<n-1; i++){
        vsip_cvputlength_f(v,m-i);
        vsip_cvcopy_f_f(ccol_sv_f(cmsv_f(B,Bs,i,i),x,0),v);
        chouseVector_f(v);
        vsip_csvmul_f(vsip_cdiv_f(v->block->a_one,vsip_cvget_f(v,0)),v,v);
        chouseProd_f(v,Bs);
        vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
        if(i < n-2){
            j = i+1;
            vsip_cvputlength_f(v,n-j);
            vsip_cvcopy_f_f(crow_sv_f(cmsv_f(B,Bs,i,j),x,0),v);
            chouseVector_f(v);vsip_cvconj_f(v,v);
            vsip_csvmul_f(vsip_cdiv_f(v->block->a_one,vsip_cvget_f(v,0)),v,v);
            cprodHouse_f(Bs,v);
            vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_cvputlength_f(v,m-i);
        vsip_cvcopy_f_f(ccol_sv_f(cmsv_f(B,Bs,i,i),x,0),v);
        chouseVector_f(v);
        vsip_csvmul_f(vsip_cdiv_f(v->block->a_one,vsip_cvget_f(v,0)),v,v);
        chouseProd_f(v,Bs);
        vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
    }
}
static void csvdBidiag_f(csvdObj_f *svd)
{
    vsip_cmview_f *B = svd->B;
    svd->eps0=(cmnormFro_f(B)/(vsip_scalar_f)vsip_cmgetrowlength_f(B))*1E-10;
    cbidiag_f(svd);
    cUmatExtract_f(svd);
    cVHmatExtract_f(svd);
    cbiDiagPhaseToZero_f(svd);
    vsip_vcopy_f_f(vreal_sv_f(cdiag_sv_f(svd->B, &svd->bs, 0),&svd->rbs),svd->d);
    vsip_vcopy_f_f(vreal_sv_f(cdiag_sv_f(svd->B, &svd->bs, 1),&svd->rbs),svd->f);
}

static void cgtProd_f(vsip_index i, vsip_index j,vsip_scalar_f c, vsip_scalar_f s,csvdObj_f *svd)
{
    vsip_cmview_f* R=svd->R;
    vsip_cvview_f *a1= crow_sv_f(R,&svd->rs_one,i);
    vsip_cvview_f *a2= crow_sv_f(R,&svd->rs_two,j);
    vsip_cvview_f *a1c=cvclone_f(a1,&svd->ts);
    vsip_cvattr_f a1attr,tsattr;
    vsip_cvgetattrib_f(a1, &a1attr);
    vsip_cvgetattrib_f(a1c,&tsattr);
    vsip_rscvmul_f(c,a1c,a1);
    vsip_cvsma_f(a2,vsip_cmplx_f(s,0.0),a1,a1);
    vsip_rscvmul_f(-s,a1c,a1c);
    vsip_cvsma_f(a2,vsip_cmplx_f(c,0.0),a1c,a2);
}
static void cprodG_f(csvdObj_f *svd,vsip_index i, vsip_index j,vsip_scalar_f c, vsip_scalar_f s)
{
    vsip_cmview_f* L=svd->L;
    vsip_cvview_f *a1= ccol_sv_f(L,&svd->ls_one,i);
    vsip_cvview_f *a2= ccol_sv_f(L,&svd->ls_two,j);
    vsip_cvview_f *a1c=cvclone_f(a1,&svd->ts);
    vsip_rscvmul_f(c,a1c,a1); vsip_cvsma_f(a2,vsip_cmplx_f(s,0.0),a1,a1);
    vsip_rscvmul_f(-s,a1c,a1c);vsip_cvsma_f(a2,vsip_cmplx_f(c,0.0),a1c,a2);
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
    xd=VI_VGET_F(d,0);
    xf=VI_VGET_F(f,0);
    g=givensCoef_f(xd,xf);
    if (n == 1){
        vsip_vput_f(f,0,0.0);
        vsip_vput_f(d,0,g.r);
    }else{
        vsip_vput_f(f,0,0.0);
        vsip_vput_f(d,0,g.r);
        xf=VI_VGET_F(f,1);
        t= -xf * g.s; xf *= g.c;
        vsip_vput_f(f,1,xf);
        cprodG_f(svd,1,0,g.c,g.s);
        for(i=1; i<n-1; i++){
            xd=VI_VGET_F(d,i);
            g=givensCoef_f(xd,t);
            cprodG_f(svd,i+1,0,g.c,g.s);
            vsip_vput_f(d,i,g.r);
            xf=VI_VGET_F(f,i+1);
            t=-xf * g.s; xf *= g.c;
            vsip_vput_f(f,i+1,xf);
        }
        xd=VI_VGET_F(d,n-1);
        g=givensCoef_f(xd,t);
        vsip_vput_f(d,n-1,g.r);
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
    vsip_scalar_f d2,f1,d3,f2;  
     /* this if list section below needs some more thought */
     /* we probably should never have n=1 */
    if(n >= 3){
        d2=VI_VGET_F(d,n-2);f1= VI_VGET_F(f,n-3);d3 = VI_VGET_F(d,n-1);f2= VI_VGET_F(f,n-2);
    } else if(n == 2){
        d2=VI_VGET_F(d,0);f1= 0.0;d3 = VI_VGET_F(d,1);f2= VI_VGET_F(f,0);
    } else {
        d2=VI_VGET_F(d,0);f1 = 0.0;d3 = 0.0;f2 = 0.0;  
    }
    mu = svdMu_f(d2,f1,d3,f2);
    x1=VI_VGET_F(d,0);
    x2 = x1 * VI_VGET_F(f,0); 
    x1 *= x1; x1 -= mu;   
    g=givensCoef_f(x1,x2);
    x1=VI_VGET_F(d,0);x2=VI_VGET_F(f,0);
    vsip_vput_f(f,0,g.c * x2 - g.s * x1);
    vsip_vput_f(d,0,x1 * g.c + x2 * g.s); 
    t=VI_VGET_F(d,1); vsip_vput_f(d,1,t*g.c);
    t*=g.s;
    cgtProd_f(0,1,g.c,g.s,svd);
    for(i=0; i<n-2; i++){
        j=i+1; k=i+2;
        g = givensCoef_f(VI_VGET_F(d,i),t);
        vsip_vput_f(d,i,g.r);      
        x1=VI_VGET_F(d,j)*g.c; 
        x2=VI_VGET_F(f,i)*g.s;
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
    vsip_length maxcntr=20*d0->length;
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
            if(VI_VGET_F(d,n) == 0.0){
                czeroCol_f(svd);
            }else{
                cimsv_f(L,L,0,0,k-1,0);
                ivsv_f(d0,d,k,0);
                ivsv_f(f0,f,k-1,0);
                czeroRow_f(svd);
            }
        }else{
            csvdStep_f(svd);
        }
    }
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
    vsip_valldestroy_f(s->t);
    vsip_malldestroy_f(s->B);
    vsip_malldestroy_f(s->R);
    vsip_malldestroy_f(s->L);
    vsip_valldestroy_vi(s->indx_L);
    vsip_valldestroy_vi(s->indx_R);
    vsip_valldestroy_f(s->d);
    vsip_valldestroy_f(s->f);
    if(s) free(s);
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
    if(!(s->t = vsip_vcreate_f(m,VSIP_MEM_NONE))) s->init++;
    if(!(s->B=vsip_mcreate_f(m,n,VSIP_ROW,VSIP_MEM_NONE))) s->init++; 
    if(!(s->L=meye_f(m)))s->init++;
    if(!(s->R=meye_f(n)))s->init++;
    if(!(s->indx_L=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    if(!(s->indx_R=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    if(!(s->d = vsip_vcreate_f(n,VSIP_MEM_NONE))) s->init++; 
    if(!(s->f = vsip_vcreate_f(n-1,VSIP_MEM_NONE)))s->init++;
    if(s->init) svdFinalize_f(s);
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
    vsip_cvalldestroy_f(s->t);
    vsip_cmalldestroy_f(s->B);
    vsip_cmalldestroy_f(s->R);
    vsip_cmalldestroy_f(s->L);
    vsip_valldestroy_vi(s->indx_L);
    vsip_valldestroy_vi(s->indx_R);
    vsip_valldestroy_f(s->d);
    vsip_valldestroy_f(s->f);
    if(s) free(s);
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
    if(!(s->t = vsip_cvcreate_f(m,VSIP_MEM_NONE)))s->init++;
    if(!(s->B=vsip_cmcreate_f(m,n,VSIP_ROW,VSIP_MEM_NONE)))s->init++;
    if(!(s->L=cmeye_f(m)))s->init++;
    if(!(s->R=cmeye_f(n)))s->init++;
    if(!(s->indx_L=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    if(!(s->indx_R=vsip_vcreate_vi(n,VSIP_MEM_NONE))) s->init++;
    if(!(s->d = vsip_vcreate_f(n,VSIP_MEM_NONE)))s->init++;
    if(!(s->f = vsip_vcreate_f(n-1,VSIP_MEM_NONE)))s->init++; 
    if(s->init) csvdFinalize_f(s);
    return s;
}
static void csvd_f(csvdObj_f *s)
{
    csvdBidiag_f(s);
    csvdIteration_f(s);
    csvdSort_f(s);
}
