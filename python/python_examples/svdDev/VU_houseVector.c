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
vsip_vview_f *
houseVector_f(vsip_vview_f* x){
    vsip_length n = vsip_vgetlength_f(x);
    vsip_scalar_f nrm=0.0;
    vsip_scalar_f s = vsip_vget_f(x,0) +  sign_f(vsip_vget_f(x,0)) * vnorm2_f(x);
    vsip_vview_f *v=vsip_vcreate_f(n,VSIP_MEM_NONE);
    vsip_vcopy_f_f(x,v);
    vsip_vput_f(v,0,s); 
    n = vnorm2_f(v);
    if (n == 0.0)
        vsip_vput_f(v,0,1.0); 
    else
        vsip_svmul_f(1.0/n,v,v);
    return v;
}
vsip_vview_d *
houseVector_d(vsip_vview_d* x){
    vsip_length n = vsip_vgetlength_d(x);
    vsip_scalar_d nrm=0.0;
    vsip_vview_d *v=vsip_vcreate_d(n,VSIP_MEM_NONE);
    vsip_scalar_d s = vsip_vget_d(x,0) +  sign_d(vsip_vget_d(x,0)) * vnorm2_d(x);
    vsip_vcopy_d_d(x,v);
    vsip_vput_d(v,0,s);
    nrm = vnorm2_d(v);
    if (nrm == 0.0)
        vsip_vput_d(v,0,1.0);
    else
        vsip_svmul_d(1.0/nrm,v,v);
    return v;
}
vsip_cvview_f *
chouseVector_f(vsip_cvview_f* x){
    vsip_length n = vsip_cvgetlength_f(x);
    vsip_scalar_f nrm;
    vsip_cvview_f *v=vsip_cvcreate_f(n,VSIP_MEM_NONE);
    vsip_cscalar_f s = vsip_cadd_f(vsip_cvget_f(x,0),
                                   vsip_cmul_f(csign_f(vsip_cvget_f(x,0)),
                                               vsip_cmplx_f(cvnorm2_f(x),0.0)));
    vsip_cvcopy_f_f(x,v);
    vsip_cvput_f(v,0,s);
    nrm = cvnorm2_f(v);
    if (nrm == 0.0)
        vsip_cvput_f(v,0,vsip_cmplx_f(1.0,0.0));
    else
        vsip_rscvmul_f(1.0/nrm,v,v);
    return v;
}
vsip_cvview_d *
chouseVector_d(vsip_cvview_d* x){
    vsip_length n = vsip_cvgetlength_d(x);
    vsip_scalar_d nrm;
    vsip_cvview_d *v=vsip_cvcreate_d(n,VSIP_MEM_NONE);
    vsip_cscalar_d s = vsip_cadd_d(vsip_cvget_d(x,0),
                                   vsip_cmul_d(csign_d(vsip_cvget_d(x,0)),
                                               vsip_cmplx_d(cvnorm2_d(x),0.0)));
    vsip_cvcopy_d_d(x,v);
    vsip_cvput_d(v,0,s);
    nrm = cvnorm2_d(v);
    if (nrm == 0.0)
        vsip_cvput_d(v,0,vsip_cmplx_d(1.0,0.0));
    else
        vsip_rscvmul_d(1.0/nrm,v,v);
    return v;
}
void
houseProd_f(vsip_vview_f *v, vsip_mview_f *A){
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
}
void
prodHouse_f(vsip_mview_f *A, vsip_vview_f *v){
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
}
void
chouseProd_f(vsip_cvview_f *v, vsip_cmview_f *A){
    vsip_cmattr_f a_atr; 
    vsip_cvview_f *w;
    vsip_cmview_f *B;
    vsip_cmgetattrib_f(A,&a_atr);
    B=vsip_cmcreate_f(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_cvcreate_f(a_atr.row_length,VSIP_MEM_NONE);
    vsip_scalar_f beta = 2.0/vsip_cvjdot_f(v,v).r;
    vsip_cvconj_f(v,v);
    vsip_cvmprod_f(v,A,w);
    vsip_cvconj_f(v,v);
    vsip_cvouter_f(vsip_cmplx_f(1.0/beta,0.0),v,w,B);
    vsip_cmsub_f(A,B,A);
    vsip_cvalldestroy_f(w);
    vsip_cmalldestroy_f(B);
}
void
cprodHouse_f(vsip_cmview_f *A, vsip_cvview_f *v){
    vsip_cmattr_f a_atr; 
    vsip_cvview_f *w;
    vsip_cmview_f *B;
    vsip_cmgetattrib_f(A,&a_atr);
    B=vsip_cmcreate_f(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_cvcreate_f(a_atr.col_length,VSIP_MEM_NONE);
    vsip_scalar_f beta = 2.0/vsip_cvjdot_f(v,v).r;
    vsip_cvconj_f(v,v);
    vsip_cmvprod_f(A,v,w);
    vsip_cvconj_f(v,v);
    vsip_cvouter_f(vsip_cmplx_f(1.0/beta,0.0),w,v,B);
    vsip_cmsub_f(A,B,A);
    vsip_cvalldestroy_f(w);
    vsip_cmalldestroy_f(B);
}
void
houseProd_d(vsip_vview_d *v, vsip_mview_d *A){
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
}
void
prodHouse_d(vsip_mview_d *A, vsip_vview_d *v){
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
}
void
chouseProd_d(vsip_cvview_d *v, vsip_cmview_d *A){
    vsip_cmattr_d a_atr; 
    vsip_cvview_d *w;
    vsip_cmview_d *B;
    vsip_cmgetattrib_d(A,&a_atr);
    B=vsip_cmcreate_d(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_cvcreate_d(a_atr.row_length,VSIP_MEM_NONE);
    vsip_scalar_d beta = 2.0/vsip_cvjdot_d(v,v).r;
    vsip_cvconj_d(v,v);
    vsip_cvmprod_d(v,A,w);
    vsip_cvconj_d(v,v);
    vsip_cvouter_d(vsip_cmplx_d(1.0/beta,0.0),v,w,B);
    vsip_cmsub_d(A,B,A);
    vsip_cvalldestroy_d(w);
    vsip_cmalldestroy_d(B);
}
void
cprodHouse_d(vsip_cmview_d *A, vsip_cvview_d *v){
    vsip_cmattr_d a_atr; 
    vsip_cvview_d *w;
    vsip_cmview_d *B;
    vsip_cmgetattrib_d(A,&a_atr);
    B=vsip_cmcreate_d(a_atr.col_length,a_atr.row_length,VSIP_ROW,VSIP_MEM_NONE);
    w = vsip_cvcreate_d(a_atr.col_length,VSIP_MEM_NONE);
    vsip_scalar_d beta = 2.0/vsip_cvjdot_d(v,v).r;
    vsip_cvconj_d(v,v);
    vsip_cmvprod_d(A,v,w);
    vsip_cvconj_d(v,v);
    vsip_cvouter_d(vsip_cmplx_d(1.0/beta,0.0),w,v,B);
    vsip_cmsub_d(A,B,A);
    vsip_cvalldestroy_d(w);
    vsip_cmalldestroy_d(B);
}
