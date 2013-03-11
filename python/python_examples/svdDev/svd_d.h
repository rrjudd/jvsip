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
typedef struct {vsip_index i; vsip_index j;} svdCorner;
typedef struct {vsip_scalar_d c; vsip_scalar_d s; vsip_scalar_d r;}givensObj_d ;
typedef struct {vsip_vview_d* t; vsip_vview_d* ts;
                vsip_mview_d* B; vsip_mview_d* Bs; vsip_vview_d* bs;
                vsip_mview_d* L; vsip_mview_d* Ls; vsip_vview_d* ls_one; vsip_vview_d* ls_two;
                vsip_vview_d* d; vsip_vview_d* ds;
                vsip_vview_d* f; vsip_vview_d* fs;
                vsip_mview_d* R; vsip_mview_d* Rs; vsip_vview_d* rs_one; vsip_vview_d *rs_two;
                vsip_scalar_d eps0;int init;
                vsip_vview_vi *indx_L; vsip_vview_vi *indx_R;} svdObj_d;

svdObj_d *svdInit_d(vsip_length, vsip_length);
void svdFinalize_d(svdObj_d*);
svdObj_d *svd_d(vsip_mview_d*);

