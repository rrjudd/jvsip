/* Created Randall Judd 2013*/
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
/*********************************************************************
// The MIT License (see copyright for jvsip in top level directory)
// http://opensource.org/licenses/MIT
**********************************************************************/
#include<vsip.h>
typedef struct {vsip_mview_f* L;vsip_vview_f* d;vsip_vview_f* f;vsip_mview_f* R;vsip_scalar_f eps0;int init;} svdObj_f;
typedef struct {vsip_mview_d* L;vsip_vview_d* d;vsip_vview_d* f;vsip_mview_d* R;vsip_scalar_d eps0;int init;} svdObj_d;
typedef struct {vsip_cmview_f* L;vsip_vview_f* d;vsip_vview_f* f;vsip_cmview_f* R;vsip_scalar_f eps0;int init;} csvdObj_f;
typedef struct {vsip_cmview_d* L;vsip_vview_d* d;vsip_vview_d* f;vsip_cmview_d* R;vsip_scalar_d eps0;int init;} csvdObj_d;
typedef struct {vsip_scalar_f c; vsip_scalar_f s; vsip_scalar_f r;}givensObj_f ;
typedef struct {vsip_scalar_d c; vsip_scalar_d s; vsip_scalar_d r;}givensObj_d;
typedef struct {vsip_index i; vsip_index j;} svdCorner;
vsip_mview_f* meye_f(vsip_length);
vsip_cmview_f* cmeye_f(vsip_length);
vsip_mview_d* meye_d(vsip_length);
vsip_cmview_d* cmeye_d(vsip_length);
vsip_scalar_f sign_f(vsip_scalar_f);
vsip_cscalar_f csign_f(vsip_cscalar_f);
vsip_scalar_d sign_d(vsip_scalar_d);
vsip_cscalar_d csign_d(vsip_cscalar_d);
vsip_mview_f* bidiag_f( vsip_mview_f*);
vsip_cmview_f* cbidiag_f( vsip_cmview_f*);
vsip_mview_d* bidiag_d( vsip_mview_d*);
vsip_cmview_d* cbidiag_d( vsip_cmview_d*);
vsip_scalar_f vnormFro_f(vsip_vview_f*);
vsip_scalar_f vnorm2_f(vsip_vview_f*);
vsip_scalar_f cvnorm2_f(vsip_cvview_f*);
vsip_scalar_d vnormFro_d(vsip_vview_d*);
vsip_scalar_d vnorm2_d(vsip_vview_d*);
vsip_scalar_d cvnorm2_d(vsip_cvview_d*);
vsip_scalar_f mnormFro_f(vsip_mview_f*);
vsip_scalar_d mnormFro_d(vsip_mview_d*);
vsip_scalar_f cvnormFro_f(vsip_cvview_f*);
vsip_scalar_d cvnormFro_d(vsip_cvview_d*);
vsip_scalar_f cmnormFro_f(vsip_cmview_f*);
vsip_scalar_d cmnormFro_d(vsip_cmview_d*);
vsip_scalar_f meig_f(vsip_mview_f*);
vsip_scalar_d meig_d(vsip_mview_d*);
vsip_scalar_f cmeig_f(vsip_cmview_f*);
vsip_scalar_d cmeig_d(vsip_cmview_d*);
vsip_vview_f* houseVector_f(vsip_vview_f*);
vsip_vview_d* houseVector_d(vsip_vview_d*);
vsip_cvview_f* chouseVector_f(vsip_cvview_f*);
vsip_cvview_d* chouseVector_d(vsip_cvview_d*);
void houseProd_f(vsip_vview_f*,vsip_mview_f*);
void prodHouse_f(vsip_mview_f*,vsip_vview_f*);
void chouseProd_f(vsip_cvview_f*,vsip_cmview_f*);
void cprodHouse_f(vsip_cmview_f*,vsip_cvview_f*);
void houseProd_d(vsip_vview_d*,vsip_mview_d*);
void prodHouse_d(vsip_mview_d*,vsip_vview_d*);
void chouseProd_d(vsip_cvview_d*,vsip_cmview_d*);
void cprodHouse_d(vsip_cmview_d*,vsip_cvview_d*);
vsip_mview_f* msv_f(vsip_mview_f*,vsip_mview_f*,vsip_index,vsip_index);
vsip_vview_f* vsv_f(vsip_vview_f*,vsip_vview_f*,vsip_index);
vsip_vview_f* col_sv_f(vsip_mview_f*,vsip_vview_f*,vsip_index);
vsip_vview_f* row_sv_f(vsip_mview_f*,vsip_vview_f*,vsip_index);
vsip_mview_f* mclone_f(vsip_mview_f*);
vsip_vview_f* vclone_f(vsip_vview_f*);
vsip_cmview_f* cmsv_f(vsip_cmview_f*,vsip_cmview_f*,vsip_index,vsip_index);
vsip_cvview_f* cvsv_f(vsip_cvview_f*,vsip_cvview_f*,vsip_index);
vsip_cvview_f* ccol_sv_f(vsip_cmview_f*,vsip_cvview_f* ,vsip_index);
vsip_cvview_f* crow_sv_f(vsip_cmview_f*,vsip_cvview_f*,vsip_index);
vsip_cmview_f* cmclone_f(vsip_cmview_f*);
vsip_cvview_f* cvclone_f(vsip_cvview_f*);
vsip_mview_d* msv_d(vsip_mview_d*,vsip_mview_d*,vsip_index,vsip_index);
vsip_vview_d* vsv_d(vsip_vview_d*,vsip_vview_d*,vsip_index);
vsip_vview_d* col_sv_d(vsip_mview_d*,vsip_vview_d*,vsip_index);
vsip_vview_d* row_sv_d(vsip_mview_d*,vsip_vview_d*,vsip_index);
vsip_mview_d* mclone_d(vsip_mview_d*);
vsip_vview_d* vclone_d(vsip_vview_d*);
vsip_cmview_d* cmsv_d(vsip_cmview_d*,vsip_cmview_d*,vsip_index,vsip_index);
vsip_cvview_d* cvsv_d(vsip_cvview_d*,vsip_cvview_d*,vsip_index);
vsip_cvview_d* ccol_sv_d(vsip_cmview_d*,vsip_cvview_d*,vsip_index);
vsip_cvview_d* crow_sv_d(vsip_cmview_d*,vsip_cvview_d*,vsip_index);
vsip_cmview_d* cmclone_d(vsip_cmview_d*);
vsip_cvview_d* cvclone_d(vsip_cvview_d*);
vsip_mview_f* imsv_f(vsip_mview_f*,vsip_mview_f*,vsip_index,vsip_index,vsip_index,vsip_index);
vsip_vview_f* ivsv_f(vsip_vview_f*,vsip_vview_f*,vsip_index,vsip_index);
vsip_cmview_f* cimsv_f(vsip_cmview_f*,vsip_cmview_f*,vsip_index,vsip_index,vsip_index,vsip_index);
vsip_cvview_f *civsv_f(vsip_cvview_f*,vsip_cvview_f*,vsip_index,vsip_index);
vsip_mview_d* imsv_d(vsip_mview_d*,vsip_mview_d*,vsip_index,vsip_index,vsip_index,vsip_index);
vsip_vview_d* ivsv_d(vsip_vview_d*,vsip_vview_d*,vsip_index,vsip_index);
vsip_cmview_d* cimsv_d(vsip_cmview_d*,vsip_cmview_d*,vsip_index,vsip_index,vsip_index,vsip_index);
vsip_cvview_d *civsv_d(vsip_cvview_d*,vsip_cvview_d*,vsip_index,vsip_index);
vsip_mview_f *UmatExtract_f(vsip_mview_f*);
vsip_mview_f *VHmatExtract_f(vsip_mview_f*);
vsip_cmview_f *cUmatExtract_f(vsip_cmview_f*);
vsip_cmview_f *cVHmatExtract_f(vsip_cmview_f*);
vsip_mview_d *UmatExtract_d(vsip_mview_d*);
vsip_mview_d *VHmatExtract_d(vsip_mview_d*);
vsip_cmview_d *cUmatExtract_d(vsip_cmview_d*);
vsip_cmview_d *cVHmatExtract_d(vsip_cmview_d*);
void biDiagPhaseToZero_f(vsip_mview_f*,vsip_vview_f*,vsip_vview_f*,vsip_mview_f*,vsip_scalar_f);
void biDiagPhaseToZero_d(vsip_mview_d*,vsip_vview_d*,vsip_vview_d*,vsip_mview_d*,vsip_scalar_d);
void cbiDiagPhaseToZero_f( vsip_cmview_f*, vsip_cvview_f*, vsip_cvview_f*,vsip_cmview_f*,vsip_scalar_f);
void cbiDiagPhaseToZero_d( vsip_cmview_d*, vsip_cvview_d*, vsip_cvview_d*,vsip_cmview_d*,vsip_scalar_d);
svdObj_f svdBidiag_f(vsip_mview_f*);
csvdObj_f csvdBidiag_f(vsip_cmview_f*);
svdObj_d svdBidiag_d(vsip_mview_d*);
csvdObj_d csvdBidiag_d(vsip_cmview_d*);
svdCorner svdCorners_f(vsip_vview_f*);
svdCorner svdCorners_d(vsip_vview_d*);
givensObj_f givensCoef_f(vsip_scalar_f, vsip_scalar_f);
givensObj_d givensCoef_d(vsip_scalar_d, vsip_scalar_d);
void phaseCheck_f(vsip_mview_f*,vsip_vview_f*,vsip_vview_f*,vsip_mview_f*,vsip_scalar_f);
void cphaseCheck_f(vsip_cmview_f*, vsip_vview_f*, vsip_vview_f*,vsip_cmview_f*,vsip_scalar_f);
void phaseCheck_d(vsip_mview_d*,vsip_vview_d*,vsip_vview_d*,vsip_mview_d*,vsip_scalar_d);
void cphaseCheck_d(vsip_cmview_d*, vsip_vview_d*, vsip_vview_d*,vsip_cmview_d*,vsip_scalar_d);
vsip_index zeroFind_f(vsip_vview_f*, vsip_scalar_f);
vsip_index zeroFind_d(vsip_vview_d*, vsip_scalar_d);

vsip_scalar_f svdMu_f(vsip_scalar_f,vsip_scalar_f,vsip_scalar_f,vsip_scalar_f);
vsip_scalar_d svdMu_d(vsip_scalar_d,vsip_scalar_d,vsip_scalar_d,vsip_scalar_d);

void gtProd_f(vsip_index, vsip_index, vsip_scalar_f,vsip_scalar_f, vsip_mview_f*);
void gtProd_d(vsip_index,vsip_index,vsip_scalar_d,vsip_scalar_d,vsip_mview_d*);
void cgtProd_f(vsip_index,vsip_index,vsip_scalar_f,vsip_scalar_f,vsip_cmview_f*);
void cgtProd_d(vsip_index,vsip_index,vsip_scalar_d,vsip_scalar_d,vsip_cmview_d*);

void prodG_f(vsip_mview_f*,vsip_index,vsip_index,vsip_scalar_f,vsip_scalar_f);
void prodG_d(vsip_mview_d*,vsip_index,vsip_index,vsip_scalar_d,vsip_scalar_d);
void cprodG_f(vsip_cmview_f*,vsip_index,vsip_index,vsip_scalar_f,vsip_scalar_f);
void cprodG_d(vsip_cmview_d*,vsip_index,vsip_index,vsip_scalar_d,vsip_scalar_d);

void svdStep_f(vsip_mview_f*, vsip_vview_f*, vsip_vview_f*, vsip_mview_f*);
void svdStep_d(vsip_mview_d*, vsip_vview_d*, vsip_vview_d*, vsip_mview_d*);
void csvdStep_f(vsip_cmview_f*, vsip_vview_f*, vsip_vview_f*, vsip_cmview_f*);

void csvdStep_d(vsip_cmview_d*, vsip_vview_d*, vsip_vview_d*, vsip_cmview_d*);
void zeroRow_f(vsip_mview_f*,vsip_vview_f*,vsip_vview_f*);
void zeroCol_f(vsip_vview_f*,vsip_vview_f*, vsip_mview_f*);
void svdIteration_f(vsip_mview_f*, vsip_vview_f*, vsip_vview_f*, vsip_mview_f*, vsip_scalar_f);
