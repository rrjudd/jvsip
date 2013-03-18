#include<vsip.h>

typedef vsip_sv_attr_f sv_attr;
typedef struct{
    void *svd;
    sv_attr attr;
    int transpose;
} jvsip_svd;
typedef jvsip_svd jvsip_sv_f;
typedef jvsip_svd jvsip_csv_f;
int jvsip_svd_destroy_f(jvsip_sv_f* );
jvsip_sv_f * jvsip_svd_create_f(vsip_length , vsip_length , vsip_svd_uv , vsip_svd_uv );
int jvsip_svd_f(jvsip_sv_f *, const vsip_mview_f *, vsip_vview_f *);
void jvsip_svd_getattr_f(const jvsip_sv_f *, vsip_sv_attr_f *);
int jvsip_svdprodu_f(const jvsip_sv_f*, vsip_mat_op, vsip_mat_side, const vsip_mview_f*);
int jvsip_svdprodv_f(const jvsip_sv_f*, vsip_mat_op, vsip_mat_side, const vsip_mview_f*);
int jvsip_svdmatu_f(const jvsip_sv_f*, vsip_scalar_vi, vsip_scalar_vi, const vsip_mview_f*);
int jvsip_svdmatv_f(const jvsip_sv_f*, vsip_scalar_vi, vsip_scalar_vi, const vsip_mview_f*);
/* Complex */
jvsip_csv_f * jvsip_csvd_create_f(vsip_length, vsip_length, vsip_svd_uv Usave, vsip_svd_uv Vsave);
int jvsip_csvd_destroy_f(jvsip_csv_f* svd);
int jvsip_csvd_f(jvsip_csv_f*, const vsip_cmview_f*, vsip_vview_f *s);
void jvsip_csvd_getattr_f(const jvsip_csv_f*, vsip_csv_attr_f*);
int jvsip_csvdprodu_f(const jvsip_sv_f*, vsip_mat_op, vsip_mat_side, const vsip_mview_f*);
int jvsip_csvdprodv_f(const jvsip_csv_f*, vsip_mat_op, vsip_mat_side,const vsip_cmview_f*);
int jvsip_csvdmatu_f(const jvsip_csv_f*, vsip_scalar_vi, vsip_scalar_vi, const vsip_cmview_f*);
int jvsip_csvdmatv_f(const jvsip_csv_f*, vsip_scalar_vi, vsip_scalar_vi, const vsip_cmview_f*);
