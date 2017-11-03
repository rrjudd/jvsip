/*
 *  vsip_svdattributes_f.h
 *  Created by Randall Judd on 9/5/08.
 *  Copyright 2008 Home. All rights reserved.
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

#ifndef _vsip_svd_f_h  
#define _vsip_svd_f_h 1 

#include"vsip.h"
#include"vsip_vviewattributes_f.h"
#include"vsip_mviewattributes_f.h"
#include"vsip_mviewattributes_f.h"
#include"vsip_cmviewattributes_f.h"
#include"vsip_cvviewattributes_f.h"
#include"vsip_vviewattributes_vi.h"

typedef vsip_sv_attr_f sv_attr;
struct vsip_svd{
    void *svd;
    sv_attr attr;
    int transpose;
};
typedef struct {vsip_vview_f* t; vsip_vview_f ts;
    vsip_vview_f* w;
    vsip_mview_f B; vsip_mview_f Bs; vsip_vview_f bs;
    vsip_mview_f* L; vsip_mview_f Ls; vsip_vview_f ls_one; vsip_vview_f ls_two;
    vsip_vview_f* d; vsip_vview_f ds;
    vsip_vview_f* f; vsip_vview_f fs;
    vsip_mview_f* R; vsip_mview_f Rs; vsip_vview_f rs_one; vsip_vview_f rs_two;
    vsip_scalar_f eps0;int init;
    vsip_vview_vi *indx_L; vsip_vview_vi *indx_R;} svdObj_f;

typedef struct {vsip_cvview_f* t; vsip_cvview_f ts;
    vsip_cvview_f* w;
    vsip_cmview_f B; vsip_cmview_f Bs; vsip_cvview_f bs; vsip_cvview_f bfs; vsip_vview_f rbs;
    vsip_cmview_f* L; vsip_cmview_f Ls; vsip_cvview_f ls_one; vsip_cvview_f ls_two;
    vsip_vview_f* d; vsip_vview_f ds;
    vsip_vview_f* f; vsip_vview_f fs;
    vsip_cmview_f* R; vsip_cmview_f Rs; vsip_cvview_f rs_one; vsip_cvview_f rs_two;
    vsip_scalar_f eps0;int init;
    vsip_vview_vi *indx_L; vsip_vview_vi *indx_R;} csvdObj_f;



#endif /*_vsip_svd_f_h */
