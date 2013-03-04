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

svdObj_f svd_f(vsip_mview_f*);
csvdObj_f csvd_f(vsip_cmview_f*);
svdObj_d svd_d(vsip_mview_d*);
csvdObj_d csvd_d(vsip_cmview_d*);
