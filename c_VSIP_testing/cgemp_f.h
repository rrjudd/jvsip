/* Created RJudd */
/* SPAWARSYSCEN D857 */
/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
/* $Id: cgemp_f.h,v 2.0 2003/02/22 15:23:20 judd Exp $ */
#include"VU_cmprintm_f.include"
static void cgemp_f(void){
   printf("********\nTEST cgemp_f\n");
   {
     vsip_cscalar_f alpha = vsip_cmplx_f(1.5,.25);
     vsip_cscalar_f beta  = vsip_cmplx_f(-.5,2.0);
     vsip_scalar_f data_ar[] = {1, 2.0, -3.0,  4,  5.0,
                                5,  .1,  .2, .3,   .4,
                                -4, 3.0, 2.0,  0, -1.0};
     vsip_scalar_f data_ai[] = {.1, 2.1, -2.0,  3,  5.0,
                                3,  1.1,  1.2, -5.3,   1.4,
                                -2, 2.2, 2.2,  0.5,  1.1};
     vsip_scalar_f data_br[] = {.4, 1.5, -2.7,  3,  9.0,
                                -1.1,  -.2,  -.3, -.2,   1.3,
                                3, 2.0, 1.0,  4, -1.0};
     vsip_scalar_f data_bi[] = {1.4, 1.2, -1.7,  3,  9.0,
                                -1.1,  -3.1,  -1.3, -.2,   1.3,
                                2.2, 2.1, 1.1,  40, -1.0};
     vsip_scalar_f ans_nh_data_r[] = { 192.1675,    8.0525,  234.2950,
                                          11.6775,  -18.4175, -273.6475,
                                         -13.0900,  -10.6825,   26.1100 };
     vsip_scalar_f ans_nh_data_i[] = { 28.9250,    9.0000, -188.0425,
                                        -19.1325,    6.0375,  -94.8375,
                                         34.2900,   17.5325,    7.5850 };
     vsip_scalar_f ans_hn_data_r[] = {
  -35.0800,  -25.7575,  -18.3475, -103.0250,   37.2750,
   24.6250,   19.8000,   -7.4075,  141.3150,   51.6400,
   10.0750,   -1.7650,   22.5000,  104.9800,  -67.5450,
   20.4150,   42.2025,  -11.5300,   64.0300,   80.8050,
   10.5100,   16.7750,  -35.2700,  116.5100,  139.1600
};
     vsip_scalar_f ans_hn_data_i[] = {
   -7.1250,  -28.0950,  -13.2625, -243.6250,   30.1250,
   13.1550,    9.2675,    8.6025,  199.1650,    8.3150,
   -0.9250,    2.2200,    7.7750,  127.2800,  -22.4950,
    2.7100,    7.2200,    0.5925,   14.8200,   43.6700,
    7.0100,   -3.2925,    2.6175,  -44.3900,   28.7600
};
     vsip_scalar_f ans_tn_data_r[] = {
   23.0200,  84.6762,  36.7462, 679.7875, -66.4125,
  -37.8225, -24.4900, -12.2688,-618.3525, -55.2650,
    1.4875,  -2.4025, -21.7000,-449.6300,  75.4575,
  -33.8675, -60.8587, -11.9650, -94.8350,-116.5725,
  -35.2850,  -2.6475,   9.8700, -39.6850,-148.9600
};
     vsip_scalar_f ans_tn_data_i[] = {
 -102.2225, -76.7225, -54.2013,-317.1125, 102.1125,
   66.7325,  59.8587, -25.1238, 375.3125, 148.2625,
   28.2675,  -2.6900,  63.9775, 235.9000,-197.4375,
   57.7100,  92.6550, -46.4638, 152.1200, 227.9700,
   27.3650,  53.6788,-107.6362, 234.3250, 402.5000
};
     vsip_cblock_f *block_a = vsip_cblockbind_f(data_ar,data_ai,15,VSIP_MEM_NONE);
     vsip_cblock_f *block_b = vsip_cblockbind_f(data_br,data_bi,15,VSIP_MEM_NONE);
     vsip_cblock_f *block_ans_nh = vsip_cblockbind_f(ans_nh_data_r,ans_nh_data_i,9,VSIP_MEM_NONE);
     vsip_cblock_f *block_ans_hn = vsip_cblockbind_f(ans_hn_data_r,ans_hn_data_i,25,VSIP_MEM_NONE);
     vsip_cblock_f *block_ans_tn = vsip_cblockbind_f(ans_tn_data_r,ans_tn_data_i,25,VSIP_MEM_NONE);
     vsip_cblock_f *block  = vsip_cblockcreate_f(400,VSIP_MEM_NONE);
     vsip_cmview_f *au = vsip_cmbind_f(block_a,0,5,3,1,5);
     vsip_cmview_f *bu = vsip_cmbind_f(block_b,0,5,3,1,5);
     vsip_cmview_f *ans_nh = vsip_cmbind_f(block_ans_nh,0,3,3,1,3);
     vsip_cmview_f *ans_hn = vsip_cmbind_f(block_ans_hn,0,5,5,1,5);
     vsip_cmview_f *ans_tn = vsip_cmbind_f(block_ans_tn,0,5,5,1,5);
     vsip_cmview_f *a = vsip_cmbind_f(block,15,-1,3,-3,5);
     vsip_cmview_f *b = vsip_cmbind_f(block,100,2,3,10,5);
     vsip_cmview_f *cnt = vsip_cmbind_f(block,200,-8,3,-2,3);
     vsip_cmview_f *ctn = vsip_cmbind_f(block,300,2,5,15,5);
     vsip_cmview_f *chk_nt = vsip_cmcreate_f(3,3,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f *chk_nt_r = vsip_mrealview_f(chk_nt);
     vsip_cmview_f *chk_tn = vsip_cmcreate_f(5,5,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f *chk_tn_r = vsip_mrealview_f(chk_tn);
     vsip_cblockadmit_f(block_a,VSIP_TRUE);
     vsip_cblockadmit_f(block_b,VSIP_TRUE);
     vsip_cblockadmit_f(block_ans_nh,VSIP_TRUE);
     vsip_cblockadmit_f(block_ans_hn,VSIP_TRUE);
     vsip_cblockadmit_f(block_ans_tn,VSIP_TRUE);
     vsip_cmcopy_f_f(au,a);
     vsip_cmcopy_f_f(bu,b);
     vsip_cmfill_f(vsip_cmplx_f(1.0,.5),cnt);
     vsip_cmfill_f(vsip_cmplx_f(2.0,-1),ctn);

     /* test nh */
     printf("\nvsip_cgemp_f(alpha,a,VSIP_MAT_NTRANS,b,VSIP_MAT_HERM,beta,c)\n");
     printf("alpha = (%f %+fi)\n",vsip_real_f(alpha),vsip_imag_f(alpha));
     printf("matrix a = ");VU_cmprintm_f("6.4",a);
     printf("matrix b = ");VU_cmprintm_f("6.4",b);
     printf("beta = (%f %+fi)\n",vsip_real_f(beta),vsip_imag_f(beta));
     printf("on input matrix c = ");VU_cmprintm_f("6.4",cnt);
     vsip_cgemp_f(alpha,a,VSIP_MAT_NTRANS,b,VSIP_MAT_HERM,beta,cnt);
     printf("on output matrix c = ");VU_cmprintm_f("6.4",cnt);
     printf("right answer = ");VU_cmprintm_f("6.4",ans_nh);
     vsip_cmsub_f(cnt,ans_nh,chk_nt); vsip_cmmag_f(chk_nt,chk_nt_r); vsip_mclip_f(chk_nt_r,.0001,.0001,0,1,chk_nt_r);
     if(vsip_msumval_f(chk_nt_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     /* test hn */
     printf("\nvsip_cgemp_f(alpha,a,VSIP_MAT_HERM,b,VSIP_MAT_NTRANS,beta,c)\n");
     printf("alpha = (%f %+fi)\n",vsip_real_f(alpha),vsip_imag_f(alpha));
     printf("matrix a = ");VU_cmprintm_f("6.4",a);
     printf("matrix b = ");VU_cmprintm_f("6.4",b);
     printf("beta = (%f %+fi)\n",vsip_real_f(beta),vsip_imag_f(beta));
     printf("on input matrix c = ");VU_cmprintm_f("6.4",ctn);
     vsip_cgemp_f(alpha,a,VSIP_MAT_HERM,b,VSIP_MAT_NTRANS,beta,ctn);
     printf("on output matrix c = ");VU_cmprintm_f("6.4",ctn);
     printf("right answer = ");VU_cmprintm_f("6.4",ans_hn);
     vsip_cmsub_f(ctn,ans_hn,chk_tn); vsip_cmmag_f(chk_tn,chk_tn_r); vsip_mclip_f(chk_tn_r,.0001,.0001,0,1,chk_tn_r);
     if(vsip_msumval_f(chk_tn_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     /* test tn */
     printf("\nvsip_cgemp_f(alpha,a,VSIP_MAT_TRANS,b,VSIP_MAT_NTRANS,beta,c)\n");
     printf("alpha = (%f %+fi)\n",vsip_real_f(alpha),vsip_imag_f(alpha));
     printf("matrix a = ");VU_cmprintm_f("6.4",a);
     printf("matrix b = ");VU_cmprintm_f("6.4",b);
     printf("beta = (%f %+fi)\n",vsip_real_f(beta),vsip_imag_f(beta));
     printf("on input matrix c = ");VU_cmprintm_f("6.4",ctn);
     vsip_cgemp_f(alpha,a,VSIP_MAT_TRANS,b,VSIP_MAT_NTRANS,beta,ctn);
     printf("on output matrix c = ");VU_cmprintm_f("6.4",ctn);
     printf("right answer = ");VU_cmprintm_f("6.4",ans_tn);
     vsip_cmsub_f(ctn,ans_tn,chk_tn); vsip_cmmag_f(chk_tn,chk_tn_r); vsip_mclip_f(chk_tn_r,.0001,.0001,0,1,chk_tn_r);
     if(vsip_msumval_f(chk_tn_r) > .5)
         printf("error\n");
     else
         printf("correct\n");



     vsip_cmalldestroy_f(au); vsip_cmalldestroy_f(bu);

     vsip_cmdestroy_f(a); vsip_cmdestroy_f(b); vsip_cmdestroy_f(cnt);
     vsip_cmalldestroy_f(ctn);

     vsip_cmalldestroy_f(ans_hn); vsip_cmalldestroy_f(ans_nh);
     vsip_cmalldestroy_f(ans_tn);

     vsip_mdestroy_f(chk_tn_r); vsip_mdestroy_f(chk_nt_r);
     vsip_cmalldestroy_f(chk_tn); vsip_cmalldestroy_f(chk_nt);
   }
   return;
}
