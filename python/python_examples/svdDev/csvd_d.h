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
typedef struct {vsip_cvview_d* t; vsip_cvview_d* ts;
                vsip_cmview_d* B; vsip_cmview_d* Bs; vsip_cvview_d* bs; vsip_cvview_d *bfs; vsip_vview_d *rbs;
                vsip_cmview_d* L; vsip_cmview_d* Ls; vsip_cvview_d* ls_one; vsip_cvview_d* ls_two;
                vsip_vview_d* d; vsip_vview_d* ds;
                vsip_vview_d* f; vsip_vview_d* fs;
                vsip_cmview_d* R; vsip_cmview_d* Rs; vsip_cvview_d* rs_one; vsip_cvview_d *rs_two;
                vsip_scalar_d eps0;int init;
                vsip_vview_vi *indx_L; vsip_vview_vi *indx_R;} csvdObj_d;

csvdObj_d *csvdInit_d(vsip_length, vsip_length);
void csvdFinalize_d(csvdObj_d*);
csvdObj_d *csvd_d(vsip_cmview_d*);
