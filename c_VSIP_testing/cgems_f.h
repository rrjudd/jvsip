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
/* $Id: cgems_f.h,v 2.0 2003/02/22 15:23:20 judd Exp $ */
#include"VU_cmprintm_f.include"
static void cgems_f(void){
   printf("********\nTEST cgems_f\n");
   {
     vsip_cscalar_f alpha = vsip_cmplx_f(1.5,.25);
     vsip_cscalar_f beta  = vsip_cmplx_f(-.5,2.0);
     vsip_scalar_f data_ar[] = {1, 2.0, -3.0,  4,  5.0,
                                5,  .1,  .2, .3,   .4,
                                -4, 3.0, 2.0,  0, -1.0};
     vsip_scalar_f data_ai[] = {.1, 2.1, -2.0,  3,  5.0,
                                3,  1.1,  1.2, -5.3,   1.4,
                                -2, 2.2, 2.2,  0.5,  1.1};
     vsip_scalar_f ans_n_data_r[] = {
   -0.025,  0.975, -5.5,    3.750,  4.75,
    5.250, -1.625, -1.5,    0.275, -1.25,
   -7.0,    2.45,   0.95,  -1.625, -3.275};
     vsip_scalar_f ans_n_data_i[] = {
    2.15,   5.4,   -2.0,    7.25, 10.50,
    7.5,    3.425,  3.6,   -6.125, 3.95,
   -2.25,   5.8,    5.55,   2.5,   3.15};
     vsip_scalar_f ans_c_data_r[] = {
   -2.7625, -7.7625,  1.7500, -9.6250, -14.6250,
   -9.3750, -5.6125, -5.8500, 11.2375, -6.3250,
    1.5000, -7.7750, -8.0250, -4.0625, -5.8875 };
     vsip_scalar_f ans_c_data_i[] = {
   -1.025, -3.40,   -7.75,   0.375,  -2.0,
    3.500, -6.5875, -6.55,  11.6375, -6.475,
  -10.875, -0.55,   -3.675, -5.25,  -10.025};
     vsip_scalar_f ans_t_data_r[] = { 
    2.475,  7.75,  -4.5,
    3.475,  0.875,  4.950,
   -3.000,  1.000,  3.450,
    6.250,  2.775,  0.875,
    7.250,  1.250, -0.775};
     vsip_scalar_f ans_t_data_i[] = { 
    4.90,  10.250,  0.50,
    8.15,   6.175,  8.55,
    0.75,   6.350,  8.30,
   10.00,  -3.375,  5.25,
   13.25,   6.700,  5.90};
     vsip_cblock_f *block_a = vsip_cblockbind_f(data_ar,data_ai,15,VSIP_MEM_NONE);
     vsip_cblock_f *block_ans_n = vsip_cblockbind_f(ans_n_data_r,ans_n_data_i,15,VSIP_MEM_NONE);
     vsip_cblock_f *block_ans_c = vsip_cblockbind_f(ans_c_data_r,ans_c_data_i,15,VSIP_MEM_NONE);
     vsip_cblock_f *block_ans_t = vsip_cblockbind_f(ans_t_data_r,ans_t_data_i,15,VSIP_MEM_NONE);
     vsip_cblock_f *block  = vsip_cblockcreate_f(400,VSIP_MEM_NONE);
     vsip_cmview_f *au = vsip_cmbind_f(block_a,0,5,3,1,5);
     vsip_cmview_f *ans_n = vsip_cmbind_f(block_ans_n,0,5,3,1,5);
     vsip_cmview_f *ans_c = vsip_cmbind_f(block_ans_c,0,5,3,1,5);
     vsip_cmview_f *ans_t = vsip_cmbind_f(block_ans_t,0,3,5,1,3);
     vsip_cmview_f *a = vsip_cmbind_f(block,15,-1,3,-3,5);
     vsip_cmview_f *cn = vsip_cmbind_f(block,200,-10,3,-2,5);
     vsip_cmview_f *ct = vsip_cmbind_f(block,300,2,5,15,3);
     vsip_cmview_f *chk_n = vsip_cmcreate_f(3,5,VSIP_COL,VSIP_MEM_NONE);
     vsip_cmview_f *chk_t = vsip_cmcreate_f(5,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f *chk_n_r = vsip_mrealview_f(chk_n);
     vsip_mview_f *chk_t_r = vsip_mrealview_f(chk_t);
     vsip_cblockadmit_f(block_a,VSIP_TRUE);
     vsip_cblockadmit_f(block_ans_n,VSIP_TRUE);
     vsip_cblockadmit_f(block_ans_c,VSIP_TRUE);
     vsip_cblockadmit_f(block_ans_t,VSIP_TRUE);
     vsip_cmcopy_f_f(au,a);
     vsip_cmfill_f(vsip_cmplx_f(1.0,.5),cn);
     vsip_cmfill_f(vsip_cmplx_f(2.0,-1),ct);

     /* test n */
     printf("\nvsip_cgems_f(alpha,a,VSIP_MAT_NTRANS,beta,c)\n");
     printf("alpha = (%f %+fi)\n",vsip_real_f(alpha),vsip_imag_f(alpha));
     printf("matrix a = ");VU_cmprintm_f("6.4",a);
     printf("beta = (%f %+fi)\n",vsip_real_f(beta),vsip_imag_f(beta));
     printf("on input matrix c = ");VU_cmprintm_f("6.4",cn);
     vsip_cgems_f(alpha,a,VSIP_MAT_NTRANS,beta,cn);
     printf("on output matrix c = ");VU_cmprintm_f("6.4",cn);
     printf("right answer = ");VU_cmprintm_f("6.4",ans_n);
     vsip_cmsub_f(cn,ans_n,chk_n); vsip_cmmag_f(chk_n,chk_n_r); vsip_mclip_f(chk_n_r,.0001,.0001,0,1,chk_n_r);
     if(vsip_msumval_f(chk_n_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     /* test c */
     printf("\nvsip_cgems_f(alpha,a,VSIP_MAT_CONJ,beta,c)\n");
     printf("alpha = (%f %+fi)\n",vsip_real_f(alpha),vsip_imag_f(alpha));
     printf("matrix a = ");VU_cmprintm_f("6.4",a);
     printf("beta = (%f %+fi)\n",vsip_real_f(beta),vsip_imag_f(beta));
     printf("on input matrix c = ");VU_cmprintm_f("6.4",cn);
     vsip_cgems_f(alpha,a,VSIP_MAT_CONJ,beta,cn);
     printf("on output matrix c = ");VU_cmprintm_f("6.4",cn);
     printf("right answer = ");VU_cmprintm_f("6.4",ans_c);
     vsip_cmsub_f(cn,ans_c,chk_n); vsip_cmmag_f(chk_n,chk_n_r); vsip_mclip_f(chk_n_r,.0001,.0001,0,1,chk_n_r);
     if(vsip_msumval_f(chk_n_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     /* test t */
     printf("\nvsip_cgems_f(alpha,a,VSIP_MAT_TRANS,beta,c)\n");
     printf("alpha = (%f %+fi)\n",vsip_real_f(alpha),vsip_imag_f(alpha));
     printf("matrix a = ");VU_cmprintm_f("6.4",a);
     printf("beta = (%f %+fi)\n",vsip_real_f(beta),vsip_imag_f(beta));
     printf("on input matrix c = ");VU_cmprintm_f("6.4",ct);
     vsip_cgems_f(alpha,a,VSIP_MAT_TRANS,beta,ct);
     printf("on output matrix c = ");VU_cmprintm_f("6.4",ct);
     printf("right answer = ");VU_cmprintm_f("6.4",ans_t);
     vsip_cmsub_f(ct,ans_t,chk_t); vsip_cmmag_f(chk_t,chk_t_r); vsip_mclip_f(chk_t_r,.0001,.0001,0,1,chk_t_r);
     if(vsip_msumval_f(chk_t_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_cmalldestroy_f(au);

     vsip_cmdestroy_f(a); vsip_cmdestroy_f(cn);
     vsip_cmalldestroy_f(ct);

     vsip_cmalldestroy_f(ans_t); 
     vsip_cmalldestroy_f(ans_n);
     vsip_cmalldestroy_f(ans_c);

     vsip_mdestroy_f(chk_t_r); vsip_mdestroy_f(chk_n_r);
     vsip_cmalldestroy_f(chk_t); vsip_cmalldestroy_f(chk_n);
   }
   return;
}
