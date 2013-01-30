/* Created RJudd January 8, 2013 */
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
#include"VU_svdUtils.h"

vsip_mview_f* msv_f(
    vsip_mview_f *B, 
    vsip_mview_f *BS, 
    vsip_index i,vsip_index j){
    vsip_mattr_f attr;
    vsip_mgetattrib_f(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_mputattrib_f(BS,&attr);
    return BS;
}
vsip_vview_f *vsv_f(
    vsip_vview_f *v,
    vsip_vview_f *vs,
    vsip_index i){
     vsip_vattr_f attr;
     vsip_vgetattrib_f(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_vputattrib_f(vs,&attr);
     return vs;
}
vsip_vview_f *col_sv_f(vsip_mview_f*Am,vsip_vview_f* vv,vsip_index col){
    vsip_mattr_f A; vsip_vattr_f v;
    vsip_mgetattrib_f(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_vputattrib_f(vv,&v);
    return vv;
}
vsip_vview_f *row_sv_f(vsip_mview_f*Am,vsip_vview_f* vv,vsip_index row){
    vsip_mattr_f A; vsip_vattr_f v;
    vsip_mgetattrib_f(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_vputattrib_f(vv,&v);
    return vv;
}
vsip_mview_f* mclone_f(vsip_mview_f*A){
    vsip_mview_f *B = vsip_mcreate_f(
                      vsip_mgetcollength_f(A),
                      vsip_mgetrowlength_f(A),
                      VSIP_ROW,VSIP_MEM_NONE);
    if(B) vsip_mcopy_f_f(A,B);
    return B;
}
vsip_vview_f* vclone_f(vsip_vview_f*x){
    vsip_vview_f *v = vsip_vcreate_f(
                      vsip_vgetlength_f(x),
                      VSIP_MEM_NONE);
    if(v) vsip_vcopy_f_f(x,v);
    return v;
}
vsip_mview_f *bidiag_f(
    vsip_mview_f *A){
    vsip_length m = vsip_mgetcollength_f(A);
    vsip_length n = vsip_mgetrowlength_f(A);
    vsip_mview_f *B = mclone_f(A);
    vsip_mview_f *Bs= vsip_mcloneview_f(B);
    vsip_vview_f *x=vsip_mcolview_f(B,0);
    vsip_vview_f *v=vclone_f(x);
    vsip_vview_f *vs = vsip_vcloneview_f(v);
    vsip_index i,j;
    for(i=0; i<n-1; i++){
    /* x=B[i:,i:].colview(0); v=houseVector(x); v/=v[0]*/
        vsip_vputlength_f(v,m-i);
        vsip_vcopy_f_f(col_sv_f(msv_f(B,Bs,i,i),x,0),v);
        houseVector_f(v);
        vsip_svmul_f(1.0/vsip_vget_f(v,0),v,v);
    /* houseProd(v,B[i:,i:]) */
        houseProd_f(v,Bs);
    /* x[1:]=v[1:] */
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
    vsip_vdestroy_f(vs); vsip_valldestroy_f(v);
    vsip_vdestroy_f(x); vsip_mdestroy_f(Bs);
    return B;
}

vsip_cmview_f* cmsv_f(
    vsip_cmview_f *B, 
    vsip_cmview_f *BS, 
    vsip_index i,vsip_index j){
    vsip_cmattr_f attr;
    vsip_cmgetattrib_f(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_cmputattrib_f(BS,&attr);
    return BS;
}
vsip_cvview_f *cvsv_f(
    vsip_cvview_f *v,
    vsip_cvview_f *vs,
    vsip_index i){
     vsip_cvattr_f attr;
     vsip_cvgetattrib_f(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_cvputattrib_f(vs,&attr);
     return vs;
}
vsip_cvview_f *ccol_sv_f(vsip_cmview_f*Am,vsip_cvview_f* vv,vsip_index col){
    vsip_cmattr_f A; vsip_cvattr_f v;
    vsip_cmgetattrib_f(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_cvputattrib_f(vv,&v);
    return vv;
}
vsip_cvview_f *crow_sv_f(vsip_cmview_f*Am,vsip_cvview_f* vv,vsip_index row){
    vsip_cmattr_f A; vsip_cvattr_f v;
    vsip_cmgetattrib_f(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_cvputattrib_f(vv,&v);
    return vv;
}
vsip_cmview_f* cmclone_f(vsip_cmview_f*A){
    vsip_cmview_f *B = vsip_cmcreate_f(
                      vsip_cmgetcollength_f(A),
                      vsip_cmgetrowlength_f(A),
                      VSIP_ROW,VSIP_MEM_NONE);
    if(B) vsip_cmcopy_f_f(A,B);
    return B;
}
vsip_cvview_f* cvclone_f(vsip_cvview_f*x){
    vsip_cvview_f *v = vsip_cvcreate_f(
                      vsip_cvgetlength_f(x),
                      VSIP_MEM_NONE);
    if(v) vsip_cvcopy_f_f(x,v);
    return v;
}
vsip_cmview_f *cbidiag_f(
    vsip_cmview_f *A){
    vsip_length m = vsip_cmgetcollength_f(A);
    vsip_length n = vsip_cmgetrowlength_f(A);
    vsip_cmview_f *B = cmclone_f(A);
    vsip_cmview_f *Bs= vsip_cmcloneview_f(B);
    vsip_cvview_f *x=vsip_cmcolview_f(B,0);
    vsip_cvview_f *v=cvclone_f(x);
    vsip_cvview_f *vs = vsip_cvcloneview_f(v);
    vsip_index i,j;
    for(i=0; i<n-1; i++){
    /* x=B[i:,i:].colview(0); v=chouseVector(x); v/=v[0]*/
        vsip_cvputlength_f(v,m-i);
        vsip_cvcopy_f_f(ccol_sv_f(cmsv_f(B,Bs,i,i),x,0),v);
        chouseVector_f(v);
        vsip_csvmul_f(vsip_cdiv_f(vsip_cmplx_f(1.0,0.0),vsip_cvget_f(v,0)),v,v);
    /* houseProd(v,B[i:,i:]) */
        chouseProd_f(v,Bs);
    /* x[1:]=v[1:] */
        vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
        if(i < n-2){
            j = i+1;
            vsip_cvputlength_f(v,n-j);
            vsip_cvcopy_f_f(crow_sv_f(cmsv_f(B,Bs,i,j),x,0),v);
            chouseVector_f(v);vsip_cvconj_f(v,v);
            vsip_csvmul_f(vsip_cdiv_f(vsip_cmplx_f(1.0,0.0),vsip_cvget_f(v,0)),v,v);
            cprodHouse_f(Bs,v);
            vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
        }
    }
    if(m > n){
        i=n-1;
        vsip_cvputlength_f(v,m-i);
        vsip_cvcopy_f_f(ccol_sv_f(cmsv_f(B,Bs,i,i),x,0),v);
        chouseVector_f(v);
        vsip_csvmul_f(vsip_cdiv_f(vsip_cmplx_f(1.0,0.0),vsip_cvget_f(v,0)),v,v);
        chouseProd_f(v,Bs);
        vsip_cvcopy_f_f(cvsv_f(v,vs,1),cvsv_f(x,x,1));
    }
    vsip_cvdestroy_f(vs); vsip_cvalldestroy_f(v);
    vsip_cvdestroy_f(x); vsip_cmdestroy_f(Bs);
    return B;
}vsip_mview_d* msv_d(
    vsip_mview_d *B, 
    vsip_mview_d *BS, 
    vsip_index i,vsip_index j){
    vsip_mattr_d attr;
    vsip_mgetattrib_d(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_mputattrib_d(BS,&attr);
    return BS;
}

vsip_vview_d *vsv_d(
    vsip_vview_d *v,
    vsip_vview_d *vs,
    vsip_index i){
     vsip_vattr_d attr;
     vsip_vgetattrib_d(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_vputattrib_d(vs,&attr);
     return vs;
}
vsip_vview_d *col_sv_d(vsip_mview_d*Am,vsip_vview_d* vv,vsip_index col){
    vsip_mattr_d A; vsip_vattr_d v;
    vsip_mgetattrib_d(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_vputattrib_d(vv,&v);
    return vv;
}
vsip_vview_d *row_sv_d(vsip_mview_d*Am,vsip_vview_d* vv,vsip_index row){
    vsip_mattr_d A; vsip_vattr_d v;
    vsip_mgetattrib_d(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_vputattrib_d(vv,&v);
    return vv;
}
vsip_mview_d* mclone_d(vsip_mview_d*A){
    vsip_mview_d *B = vsip_mcreate_d(
                      vsip_mgetcollength_d(A),
                      vsip_mgetrowlength_d(A),
                      VSIP_ROW,VSIP_MEM_NONE);
    if(B) vsip_mcopy_d_d(A,B);
    return B;
}
vsip_vview_d* vclone_d(vsip_vview_d*x){
    vsip_vview_d *v = vsip_vcreate_d(
                      vsip_vgetlength_d(x),
                      VSIP_MEM_NONE);
    if(v) vsip_vcopy_d_d(x,v);
    return v;
}
vsip_mview_d *bidiag_d(
    vsip_mview_d *A){
    vsip_length m = vsip_mgetcollength_d(A);
    vsip_length n = vsip_mgetrowlength_d(A);
    vsip_mview_d *B = mclone_d(A);
    vsip_mview_d *Bs= vsip_mcloneview_d(B);
    vsip_vview_d *x=vsip_mcolview_d(B,0);
    vsip_vview_d *v=vclone_d(x);
    vsip_vview_d *vs = vsip_vcloneview_d(v);
    vsip_index i,j;
    for(i=0; i<n-1; i++){
    /* x=B[i:,i:].colview(0); v=houseVector(x); v/=v[0]*/
        vsip_vputlength_d(v,m-i);
        vsip_vcopy_d_d(col_sv_d(msv_d(B,Bs,i,i),x,0),v);
        houseVector_d(v);
        vsip_svmul_d(1.0/vsip_vget_d(v,0),v,v);
    /* houseProd(v,B[i:,i:]) */
        houseProd_d(v,Bs);
    /* x[1:]=v[1:] */
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
    vsip_vdestroy_d(vs); vsip_valldestroy_d(v);
    vsip_vdestroy_d(x); vsip_mdestroy_d(Bs);
    return B;
}

vsip_cmview_d* cmsv_d(
    vsip_cmview_d *B, 
    vsip_cmview_d *BS, 
    vsip_index i,vsip_index j){
    vsip_cmattr_d attr;
    vsip_cmgetattrib_d(B,&attr);
    attr.row_length -= j;
    attr.col_length -= i;
    attr.offset += j * attr.row_stride + i * attr.col_stride;
    vsip_cmputattrib_d(BS,&attr);
    return BS;
}
vsip_cvview_d *cvsv_d(
    vsip_cvview_d *v,
    vsip_cvview_d *vs,
    vsip_index i){
     vsip_cvattr_d attr;
     vsip_cvgetattrib_d(v,&attr);
     attr.offset += i * attr.stride;
     attr.length -= i;
     vsip_cvputattrib_d(vs,&attr);
     return vs;
}
vsip_cvview_d *ccol_sv_d(vsip_cmview_d*Am,vsip_cvview_d* vv,vsip_index col){
    vsip_cmattr_d A; vsip_cvattr_d v;
    vsip_cmgetattrib_d(Am,&A);
    v.offset = A.offset + col * A.row_stride;
    v.stride = A.col_stride;
    v.length = A.col_length;
    vsip_cvputattrib_d(vv,&v);
    return vv;
}
vsip_cvview_d *crow_sv_d(vsip_cmview_d*Am,vsip_cvview_d* vv,vsip_index row){
    vsip_cmattr_d A; vsip_cvattr_d v;
    vsip_cmgetattrib_d(Am,&A);
    v.offset = A.offset + row * A.col_stride;
    v.stride = A.row_stride;
    v.length = A.row_length;
    vsip_cvputattrib_d(vv,&v);
    return vv;
}
vsip_cmview_d* cmclone_d(vsip_cmview_d*A){
    vsip_cmview_d *B = vsip_cmcreate_d(
                      vsip_cmgetcollength_d(A),
                      vsip_cmgetrowlength_d(A),
                      VSIP_ROW,VSIP_MEM_NONE);
    if(B) vsip_cmcopy_d_d(A,B);
    return B;
}
vsip_cvview_d* cvclone_d(vsip_cvview_d*x){
    vsip_cvview_d *v = vsip_cvcreate_d(
                      vsip_cvgetlength_d(x),
                      VSIP_MEM_NONE);
    if(v) vsip_cvcopy_d_d(x,v);
    return v;
}
vsip_cmview_d *cbidiag_d(
    vsip_cmview_d *A){
    vsip_length m = vsip_cmgetcollength_d(A);
    vsip_length n = vsip_cmgetrowlength_d(A);
    vsip_cmview_d *B = cmclone_d(A);
    vsip_cmview_d *Bs= vsip_cmcloneview_d(B);
    vsip_cvview_d *x=vsip_cmcolview_d(B,0);
    vsip_cvview_d *v=cvclone_d(x);
    vsip_cvview_d *vs = vsip_cvcloneview_d(v);
    vsip_index i,j;
    for(i=0; i<n-1; i++){
    /* x=B[i:,i:].colview(0); v=chouseVector(x); v/=v[0]*/
        vsip_cvputlength_d(v,m-i);
        vsip_cvcopy_d_d(ccol_sv_d(cmsv_d(B,Bs,i,i),x,0),v);
        chouseVector_d(v);
        vsip_csvmul_d(vsip_cdiv_d(vsip_cmplx_d(1.0,0.0),vsip_cvget_d(v,0)),v,v);
    /* houseProd(v,B[i:,i:]) */
        chouseProd_d(v,Bs);
    /* x[1:]=v[1:] */
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
    vsip_cvdestroy_d(vs); vsip_cvalldestroy_d(v);
    vsip_cvdestroy_d(x); vsip_cmdestroy_d(Bs);
    return B;
}

vsip_mview_f *UmatExtract_f(vsip_mview_f*B){
    vsip_stride i;
    vsip_length m = vsip_mgetcollength_f(B);
    vsip_length n = vsip_mgetrowlength_f(B);
    vsip_mview_f *U=meye_f(m);
    vsip_mview_f *Bs, *Us;
    vsip_vview_f *v;
    vsip_scalar_f t;
    v = vsip_mrowview_f(B,0);
    Bs=vsip_mcloneview_f(B);
    Us=vsip_mcloneview_f(U);
    if (m > n){
        i=n-1;
        row_sv_f(msv_f(B,Bs,i,i),v,0);
        t=vsip_vget_f(v,0); vsip_vput_f(v,0,1.0);
        houseProd_f(v,msv_f(U,Us,i,i));
        vsip_vput_f(v,0,t);
    }
    for(i=n-2; i>=0; i--){
        row_sv_f(msv_f(B,Bs,i,i),v,0);
        t=vsip_vget_f(v,0); vsip_vput_f(v,0,1.0);
        houseProd_f(v,msv_f(U,Us,i,i));
        vsip_vput_f(v,0,t);
    } 
    return U;
}
vsip_mview_f *VHmatExtract_f(vsip_mview_f*B){
    vsip_stride i;
    vsip_length n = vsip_mgetrowlength_f(B);
    vsip_mview_f *Bs; 
    vsip_mview_f *V=meye_f(n);
    vsip_mview_f *Vs;
    vsip_vview_f *v;
    vsip_scalar_f t;
    if(n < 3)
        return V;
    v = vsip_mrowview_f(B,0);
    Vs=vsip_mcloneview_f(V);
    Bs=vsip_mcloneview_f(B);
    for(i=n-3; i>=0; i--){
        vsip_stride j=i+1;
        row_sv_f(msv_f(B,Bs,i,j),v,0);
        t=vsip_vget_f(v,0);vsip_vput_f(v,0,1.0);
        prodHouse_f(msv_f(V,Vs,j,j),v);
        vsip_vput_f(v,0,t);
    }      
    vsip_vdestroy_f(v);
    vsip_mdestroy_f(Vs);
    vsip_mdestroy_f(Bs);
    return V;
}







