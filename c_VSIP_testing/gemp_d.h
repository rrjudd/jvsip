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
/* $Id: gemp_d.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
static void gemp_d(void){
   printf("********\nTEST gemp_d\n");
   {
     vsip_scalar_d alpha = 1.5;
     vsip_scalar_d beta  = 2.0;
     vsip_scalar_d data_a[] = {1, 2.0, -3.0,  4,  5.0,
                                5,  .1,  .2, .3,   .4,
                                -4, 3.0, 2.0,  0, -1.0};
     vsip_scalar_d data_b[] = {.4, 1.5, -2.7,  3,  9.0,
                                -1.1,  -.2,  -.3, -.2,   1.3,
                                3, 2.0, 1.0,  4, -1.0};
     vsip_scalar_d ans_nt_data[] = { 104.75,  9.65,  24.5, 
                                        11.165, -5.68, 26.3, 
                                       -15.25,   4.85, -2.5};
     vsip_scalar_d ans_tn_data[] = { -21.65, - 7.25,  -8.3,   -17.,    33.25,
                                        18.535, 17.47,   0.355,  30.97,  26.695,
                                        10.87,   3.19,  19.06,    2.44, -39.11,
                                         5.905, 12.91, -12.335,  21.91,  58.585,
                                         1.84,  12.13, -17.93,   20.38,  73.78};
     vsip_block_d *block_a = vsip_blockbind_d(data_a,15,VSIP_MEM_NONE);
     vsip_block_d *block_b = vsip_blockbind_d(data_b,15,VSIP_MEM_NONE);
     vsip_block_d *block_ans_nt = vsip_blockbind_d(ans_nt_data,9,VSIP_MEM_NONE);
     vsip_block_d *block_ans_tn = vsip_blockbind_d(ans_tn_data,25,VSIP_MEM_NONE);
     vsip_block_d *block  = vsip_blockcreate_d(400,VSIP_MEM_NONE);
     vsip_mview_d *au = vsip_mbind_d(block_a,0,5,3,1,5);
     vsip_mview_d *bu = vsip_mbind_d(block_b,0,5,3,1,5);
     vsip_mview_d *ans_nt = vsip_mbind_d(block_ans_nt,0,3,3,1,3);
     vsip_mview_d *ans_tn = vsip_mbind_d(block_ans_tn,0,5,5,1,5);
     vsip_mview_d *a = vsip_mbind_d(block,15,-1,3,-3,5);
     vsip_mview_d *b = vsip_mbind_d(block,100,2,3,10,5);
     vsip_mview_d *cnt = vsip_mbind_d(block,200,-8,3,-2,3);
     vsip_mview_d *ctn = vsip_mbind_d(block,300,2,5,15,5);
     vsip_mview_d *chk_nt = vsip_mcreate_d(3,3,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *chk_tn = vsip_mcreate_d(5,5,VSIP_ROW,VSIP_MEM_NONE);
     vsip_blockadmit_d(block_a,VSIP_TRUE);
     vsip_blockadmit_d(block_b,VSIP_TRUE);
     vsip_blockadmit_d(block_ans_nt,VSIP_TRUE);
     vsip_blockadmit_d(block_ans_tn,VSIP_TRUE);
     vsip_mcopy_d_d(au,a);
     vsip_mcopy_d_d(bu,b);
     vsip_mfill_d(1.0,cnt);
     vsip_mfill_d(2.0,ctn);

     /* test nt */
     printf("\nvsip_gemp_d(alpha,a,VSIP_MAT_NTRANS,b,VSIP_MAT_TRANS,beta,c)\n");
     printf("alpha = %f\n",alpha);
     printf("matrix a = ");VU_mprintm_d("6.4",a);
     printf("matrix b = ");VU_mprintm_d("6.4",b);
     printf("beta = %f\n",beta);
     printf("on input matrix c = ");VU_mprintm_d("6.4",cnt);
     vsip_gemp_d(alpha,a,VSIP_MAT_NTRANS,b,VSIP_MAT_TRANS,beta,cnt);
     printf("on output matrix c = ");VU_mprintm_d("6.4",cnt);
     printf("right answer = ");VU_mprintm_d("6.4",ans_nt);
     vsip_msub_d(cnt,ans_nt,chk_nt); vsip_mmag_d(chk_nt,chk_nt); vsip_mclip_d(chk_nt,.0001,.0001,0,1,chk_nt);
     if(vsip_msumval_d(chk_nt) > .5)
         printf("error\n");
     else
         printf("correct\n");

     /* test tn */
     printf("\nvsip_gemp_d(alpha,a,VSIP_MAT_TRANS,b,VSIP_MAT_NTRANS,beta,c)\n");
     printf("alpha = %f\n",alpha);
     printf("matrix a = ");VU_mprintm_d("6.4",a);
     printf("matrix b = ");VU_mprintm_d("6.4",b);
     printf("beta = %f\n",beta);
     printf("on input matrix c = ");VU_mprintm_d("6.4",ctn);
     vsip_gemp_d(alpha,a,VSIP_MAT_TRANS,b,VSIP_MAT_NTRANS,beta,ctn);
     printf("on output matrix c = ");VU_mprintm_d("6.4",ctn);
     printf("right answer = ");VU_mprintm_d("6.4",ans_tn);
     vsip_msub_d(ctn,ans_tn,chk_tn); vsip_mmag_d(chk_tn,chk_tn); vsip_mclip_d(chk_tn,.0001,.0001,0,1,chk_tn);
     if(vsip_msumval_d(chk_tn) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_malldestroy_d(au); vsip_malldestroy_d(bu);

     vsip_mdestroy_d(a); vsip_mdestroy_d(b); vsip_mdestroy_d(cnt);
     vsip_malldestroy_d(ctn);

     vsip_malldestroy_d(ans_tn); vsip_malldestroy_d(ans_nt);

     vsip_malldestroy_d(chk_tn); vsip_malldestroy_d(chk_nt);
   }
   return;
}
