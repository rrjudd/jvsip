/*
 *  vsip svd 
 *  Created by Randall Judd on 3/11/2013.
 *
 */
/*********************************************************************
// This code includes no warranty, express or implied, including     /
// the warranties of merchantability and fitness for a particular    /
// purpose.                                                          /
// No person or entity assumes any legal liability or responsibility /
// for the accuracy, completeness, or usefulness of any information, /
// apparatus, product, or process disclosed, or represents that      /
// its use would not infringe privately owned rights.                /
*********************************************************************/
#include<VI_svd_f.h>
#include"vsip_svd.h"

/* Real SVD */
int
jvsip_svd_destroy_f(jvsip_sv_f* s)
{
    if(s){
       svdObj_f* svd=(svdObj_f*)s->svd;
       svdFinalize_f(svd);
       free((void*)s);
       s=NULL;
    }
    return 0;
}
jvsip_sv_f *
jvsip_svd_create_f(vsip_length M, vsip_length N, vsip_svd_uv Usave, vsip_svd_uv Vsave)
{
    jvsip_sv_f *s = (jvsip_sv_f*) malloc(sizeof(jvsip_svd));
    if(s){
        if(M < N){
            s->svd = (void*) svdInit_f(N,M);
        }else{
            s->svd = (void*) svdInit_f(M,N);
        }
        if(s->svd){
            s->attr.Usave=Usave;
            s->attr.Vsave=Vsave;
            s->attr.m=M;
            s->attr.n=N;
            s->transpose = M < N ? 1:0;
        } else {
            jvsip_svd_destroy_f(s);
        }
    }
    return s;
}

int
jvsip_svd_f(jvsip_sv_f *svd, const vsip_mview_f *A, vsip_vview_f *sv)
{
    svdObj_f *s = (svdObj_f*) svd->svd;
    if(svd->transpose){
        vsip_mview_f *t=vsip_mcloneview_f(A);
        vsip_mattr_f attr0,attr;
        vsip_mgetattrib_f(t,&attr0);
        attr.offset=attr0.offset;
        attr.row_stride=attr0.col_stride;
        attr.col_stride = attr0.row_stride;
        attr.row_length=attr0.col_length;
        attr.col_length=attr0.row_length;
        vsip_mputattrib_f(t,&attr);
        vsip_mcopy_f_f(t,s->B);
        vsip_mdestroy_f(t);
    } else {
        vsip_mcopy_f_f(A,s->B);
    }
    svd_f(s);
    vsip_vcopy_f_f(s->d,sv);
    return 0;
}
void
jvsip_svd_getattr_f(const jvsip_sv_f *svd, vsip_sv_attr_f *attrib)
{
    attrib->Usave = svd->attr.Usave;
    attrib->Vsave = svd->attr.Vsave;
    attrib->m = svd->attr.m;
    attrib->n = svd->attr.n;
}

int 
jvsip_svdprodu_f(const jvsip_sv_f *svd, vsip_mat_op OpU, vsip_mat_side ApU,
const vsip_mview_f *C)
{
    if((OpU != VSIP_MAT_NTRANS) || (OpU != VSIP_MAT_TRANS)) return 1;
    if( (ApU != VSIP_MAT_LSIDE) || (ApU != VSIP_MAT_RSIDE)) return 1;
    if( svd->attr.Usave == VSIP_SVD_UVPART){
        if (ApU == VSIP_MAT_LSIDE){
            if(OpU == VSIP_MAT_NTRANS){
            } else {
            }
        } else { /* must be MAT_RSIDE */
            if(OpU == VSIP_MAT_NTRANS){
            } else {
            }
        }
    } else if(svd->attr.Usave == VSIP_SVD_UVFULL){
        if (ApU == VSIP_MAT_LSIDE){
            if(OpU == VSIP_MAT_NTRANS){
            } else {
            }
        } else { /* must be MAT_RSIDE */
            if(OpU == VSIP_MAT_NTRANS){
            } else {
            }
        }
    } else {
        return 1;
    }
    return 0;
} 


int 
jvsip_svdprodv_f(const jvsip_sv_f *svd, vsip_mat_op OpV, vsip_mat_side ApV,const vsip_mview_f *C)
{
    return 0;
}

int 
jvsip_svdmatu_f(const jvsip_sv_f *svd, vsip_scalar_vi low, vsip_scalar_vi high, const vsip_mview_f *C)
{
    vsip_mattr_f attr,sattr;
    svdObj_f *s = (svdObj_f*) svd->svd;
    if(svd->transpose){
        vsip_mview_f *L = s->R;
        vsip_mview_f *Ls = &s->Rs;
        vsip_mgetattrib_f(L,&attr);
        sattr.offset=attr.offset + attr.col_stride * low; 
        sattr.row_stride=attr.col_stride; sattr.col_stride=attr.row_stride;
        sattr.row_length = (high-low) + 1; sattr.col_length=attr.row_length;
        vsip_mputattrib_f(Ls,&sattr);
        vsip_mcopy_f_f(Ls,C);
    } else {
        vsip_mview_f *L = s->L;
        vsip_mview_f *Ls = &s->Ls;
        vsip_mgetattrib_f(L,&attr);vsip_mgetattrib_f(L,&sattr);
        sattr.offset = attr.offset + attr.row_stride * low;
        sattr.row_length = (high-low) + 1;
        vsip_mputattrib_f(Ls,&sattr);
        vsip_mcopy_f_f(Ls,C);
    }
    return 0;
}

int 
jvsip_svdmatv_f(const jvsip_sv_f *svd, vsip_scalar_vi low, vsip_scalar_vi high, const vsip_mview_f *C)
{
    vsip_mattr_f attr,tattr;
    svdObj_f *s = (svdObj_f*) svd->svd;
    if(svd->transpose){
        vsip_mview_f *R  = s->L;
        vsip_mview_f *Rs = &s->Ls;
        vsip_mgetattrib_f(R,&attr);
        tattr=attr;
        tattr.offset += tattr.row_stride * low;
        tattr.row_length = (high-low) + 1;
        vsip_mputattrib_f(Rs,&tattr);
        vsip_mcopy_f_f(Rs,C);
    } else {
        vsip_mview_f *R  = s->R;
        vsip_mview_f *Rs = &s->Rs;
        vsip_mgetattrib_f(R,&attr);
        tattr.offset=attr.offset;
        tattr.row_stride=attr.col_stride;
        tattr.col_stride=attr.row_stride;
        tattr.row_length=attr.col_length;
        tattr.col_length=attr.row_length;
        tattr.offset += tattr.row_stride * low;
        tattr.row_length = (high-low) + 1;
        vsip_mputattrib_f(Rs,&tattr);
        vsip_mcopy_f_f(Rs,C);
    }
    return 0;
}

/* Complex */
int
jvsip_csvd_destroy_f(jvsip_csv_f* s)
{
    if(s){
       csvdObj_f* svd=(csvdObj_f*)s->svd;
       csvdFinalize_f(svd);
       free((void*)s);
       s=NULL;
    }
    return 0;
}

jvsip_csv_f *
jvsip_csvd_create_f(vsip_length M, vsip_length N, vsip_svd_uv Usave, vsip_svd_uv Vsave)
{
    jvsip_csv_f *s = (jvsip_csv_f*) malloc(sizeof(jvsip_csv_f));
    if(s){
        if(M < N){
            s->svd = (void*) csvdInit_f(N,M);
        }else{
            s->svd = (void*)csvdInit_f(M,N);
        }
        if(s->svd){
            s->attr.Usave=Usave;
            s->attr.Vsave=Vsave;
            s->attr.m=M;
            s->attr.n=N;
            s->transpose = M < N ? 1:0;
        } else {
            jvsip_svd_destroy_f(s);
        }
    }
    return s;
}

int
jvsip_csvd_f(jvsip_csv_f *svd, const vsip_cmview_f *A, vsip_vview_f *sv)
{
    csvdObj_f *s = (csvdObj_f*) svd->svd;
    if(svd->transpose){
        vsip_cmherm_f(A,s->B);
    } else {
        vsip_cmcopy_f_f(A,s->B);
    }
    csvd_f(s);
    vsip_vcopy_f_f(s->d,sv);
    return 0;;
}

void 
jvsip_csvd_getattr_f(const jvsip_csv_f *svd, vsip_csv_attr_f *attrib)
{
    attrib->Usave = svd->attr.Usave;
    attrib->Vsave = svd->attr.Vsave;
    attrib->m = svd->attr.m;
    attrib->n = svd->attr.n;
}

int 
jvsip_csvdprodu_f(const jvsip_sv_f *svd, vsip_mat_op OpU, vsip_mat_side ApU,
const vsip_mview_f *C)
{
    return 0;
}

int 
jvsip_csvdprodv_f(const jvsip_csv_f *svd, vsip_mat_op OpV, vsip_mat_side ApV,const vsip_cmview_f *C)
{
    return 0;
}

int 
jvsip_csvdmatu_f(const jvsip_csv_f *svd, vsip_scalar_vi low, vsip_scalar_vi high, const vsip_cmview_f *C)
{
    csvdObj_f *s = (csvdObj_f*) svd->svd;
    vsip_cmattr_f attr,sattr;
    if(svd->transpose){
        vsip_cmview_f *L = s->R;
        vsip_cmview_f *Ls = &s->Rs; 
        vsip_cmgetattrib_f(L,&attr);
        sattr.offset=attr.offset + attr.col_stride * low; 
        sattr.row_stride=attr.col_stride; sattr.col_stride=attr.row_stride;
        sattr.row_length = (high-low) + 1; sattr.col_length=attr.row_length;
        vsip_cmputattrib_f(Ls,&sattr);
        vsip_cmcopy_f_f(Ls,C);
        vsip_cmconj_f(C,C);
    } else {
        vsip_cmview_f *L = s->L;
        vsip_cmview_f *Ls = &s->Ls;
        vsip_cmgetattrib_f(L,&attr);vsip_cmgetattrib_f(L,&sattr);
        sattr.offset = attr.offset + attr.row_stride * low;
        sattr.row_length = (high-low) + 1;
        vsip_cmputattrib_f(Ls,&sattr);
        vsip_cmcopy_f_f(Ls,C);
    }
    return 0;
}

int 
jvsip_csvdmatv_f(const jvsip_csv_f *svd, vsip_scalar_vi low, vsip_scalar_vi high, const vsip_cmview_f *C)
{
    vsip_cmattr_f attr,tattr;
    csvdObj_f *s = (csvdObj_f*) svd->svd;
    if(svd->transpose){
        vsip_cmview_f *R  = s->L;
        vsip_cmview_f *Rs = &s->Ls;
        vsip_cmgetattrib_f(R,&attr);
        tattr=attr;
        tattr.offset += tattr.row_stride * low;
        tattr.row_length = (high-low) + 1;
        vsip_cmputattrib_f(Rs,&tattr);
        vsip_cmcopy_f_f(Rs,C);
    } else {
        vsip_cmview_f *R  = s->R;
        vsip_cmview_f *Rs = &s->Rs;
        vsip_cmgetattrib_f(R,&attr);
        tattr.offset=attr.offset;
        tattr.row_stride=attr.col_stride;
        tattr.col_stride=attr.row_stride;
        tattr.row_length=attr.col_length;
        tattr.col_length=attr.row_length;
        tattr.offset += tattr.row_stride * low;
        tattr.row_length = (high-low) + 1;
        vsip_cmputattrib_f(Rs,&tattr);
        vsip_cmconj_f(Rs,C);
    }
    return 0;
}
