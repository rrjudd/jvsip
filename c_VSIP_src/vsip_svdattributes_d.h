/*
 *  vsip_svdattributes_d.h
 *  Created by Randall Judd  5/2013.
 *  Copyright 2013 All rights reserved.
 *
 */
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

#ifndef _vsip_svd_d_h  
#define _vsip_svd_d_h 1 

#include<vsip.h>
#include<vsip_vviewattributes_d.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_mviewattributes_d.h>
#include<vsip_cmviewattributes_d.h>
#include<vsip_cvviewattributes_d.h>
#include<vsip_vviewattributes_vi.h>

typedef vsip_sv_attr_d sv_attr;
struct vsip_svd{
    void *svd;
    sv_attr attr;
    int transpose;
};
typedef struct {vsip_vview_d* t; vsip_vview_d ts;
    vsip_vview_d* w;
    vsip_mview_d B; vsip_mview_d Bs; vsip_vview_d bs;
    vsip_mview_d* L; vsip_mview_d Ls; vsip_vview_d ls_one; vsip_vview_d ls_two;
    vsip_vview_d* d; vsip_vview_d ds;
    vsip_vview_d* f; vsip_vview_d fs;
    vsip_mview_d* R; vsip_mview_d Rs; vsip_vview_d rs_one; vsip_vview_d rs_two;
    vsip_scalar_d eps0;int init;
    vsip_vview_vi *indx_L; vsip_vview_vi *indx_R;} svdObj_d;

typedef struct {vsip_cvview_d* t; vsip_cvview_d ts;
    vsip_cvview_d* w;
    vsip_cmview_d B; vsip_cmview_d Bs; vsip_cvview_d bs; vsip_cvview_d bfs; vsip_vview_d rbs;
    vsip_cmview_d* L; vsip_cmview_d Ls; vsip_cvview_d ls_one; vsip_cvview_d ls_two;
    vsip_vview_d* d; vsip_vview_d ds;
    vsip_vview_d* f; vsip_vview_d fs;
    vsip_cmview_d* R; vsip_cmview_d Rs; vsip_cvview_d rs_one; vsip_cvview_d rs_two;
    vsip_scalar_d eps0;int init;
    vsip_vview_vi *indx_L; vsip_vview_vi *indx_R;} csvdObj_d;



#endif /*_vsip_svd_d_h */
