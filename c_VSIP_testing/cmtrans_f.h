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
/* $Id: cmtrans_f.h,v 2.0 2003/02/22 15:23:22 judd Exp $ */
static void cmtrans_f(void){
   printf("********\nTEST cmtrans_f\n");
   {
     vsip_scalar_f data_1_r[] = {1,  2,  3,  4,
                                  5,  6,  7,  8, 
                                  9, 10, 11, 12,
                                 13, 14, 15, 16};
     vsip_scalar_f data_1_i[] = {9,  8,  7,  6,
                                  5,  4,  2,  1, 
                                  12, 10, 9, 7,
                                  14, 11, 8, 5};
     vsip_scalar_f data_2_r[] = {  .1,  .2,  .3,  .4,    
                                  1.0, 1.1, 1.2, 1.3,
                                  2.1, 2.2, 2.3, 2.4};
     vsip_scalar_f data_2_i[] = {  1,  2,  3,  4,    
                                   -1.0, -1.1, -1.2, -1.3,
                                    .1, .2, .3, .4};
     vsip_cblock_f *block_1 = vsip_cblockbind_f(data_1_r,data_1_i,16,VSIP_MEM_NONE);
     vsip_cblock_f *block_2 = vsip_cblockbind_f(data_2_r,data_2_i,12,VSIP_MEM_NONE);
     vsip_cblock_f *block = vsip_cblockcreate_f(200,VSIP_MEM_NONE);
     vsip_cmview_f *d_1   = vsip_cmbind_f(block_1,0,4,4,1,4);
     vsip_cmview_f *ans_d1 = vsip_cmbind_f(block_1,0,1,4,4,4);
     vsip_cmview_f *d_2   = vsip_cmbind_f(block_2,0,4,3,1,4);
     vsip_cmview_f *ans_d2 = vsip_cmbind_f(block_2,0,1,4,4,3);

     vsip_cmview_f *a_1 = vsip_cmbind_f(block,18,-4,4,-1,4);
     vsip_cmview_f *a_2 = vsip_cmbind_f(block,70,-2,3,-10,4);

     vsip_cmview_f *c_2 = vsip_cmbind_f(block,150,8,4,1,3);
     vsip_cmview_f *chk_1 = vsip_cmcreate_f(4,4,VSIP_COL,VSIP_MEM_NONE);
     vsip_cmview_f *chk_2 = vsip_cmcreate_f(4,3,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f *chk_1_r = vsip_mrealview_f(chk_1);
     vsip_mview_f *chk_2_r =  vsip_mrealview_f(chk_2);
     vsip_cmview_f *ans_1 = vsip_cmcreate_f(4,4,VSIP_COL,VSIP_MEM_NONE);
     vsip_cmview_f *ans_2 = vsip_cmcreate_f(4,3,VSIP_COL,VSIP_MEM_NONE);

     vsip_cblockadmit_f(block_1,VSIP_TRUE);
     vsip_cblockadmit_f(block_2,VSIP_TRUE);

     vsip_cmcopy_f_f(ans_d1,ans_1);
     vsip_cmcopy_f_f(ans_d2,ans_2);
     vsip_cmcopy_f_f(d_1,a_1);
     vsip_cmcopy_f_f(d_2,a_2);

     printf("4x4 in place\n");
     printf("matrix a = ");VU_cmprintm_f("6.4",a_1);
     printf("vsip_cmtrans_f(a_1,a_1)\n");
     vsip_cmtrans_f(a_1,a_1);
     printf("matrix a = ");VU_cmprintm_f("6.4",a_1);
     printf("matrix ans = ");VU_cmprintm_f("6.4",ans_1);
     vsip_cmsub_f(a_1,ans_1,chk_1); vsip_cmmag_f(chk_1,chk_1_r); vsip_mclip_f(chk_1_r,.0001,.0001,0,1,chk_1_r);
     if(vsip_msumval_f(chk_1_r) > .5)
         printf("error\n\n");
     else
         printf("correct\n\n");
     
     printf("3x4 out of place\n");
     printf("vsip_cmtrans_f(a,b)\n");
     printf("matrix a = "); VU_cmprintm_f("6.4",a_2);
     vsip_cmtrans_f(a_2,c_2);
     printf("matrix b = "); VU_cmprintm_f("6.4",c_2);
     printf("matrix ans = ");VU_cmprintm_f("6.4",ans_2);
     vsip_cmsub_f(c_2,ans_2,chk_2); vsip_cmmag_f(chk_2,chk_2_r); vsip_mclip_f(chk_2_r,.0001,.0001,0,1,chk_2_r);
     if(vsip_msumval_f(chk_2_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_mdestroy_f(chk_1_r);
     vsip_mdestroy_f(chk_2_r);
     vsip_cmalldestroy_f(chk_1);
     vsip_cmalldestroy_f(chk_2);
     vsip_cmdestroy_f(a_1); vsip_cmdestroy_f(a_2); vsip_cmalldestroy_f(c_2);
     vsip_cmalldestroy_f(ans_1); vsip_cmalldestroy_f(ans_2);
     vsip_cmdestroy_f(ans_d1); vsip_cmalldestroy_f(d_1);
     vsip_cmdestroy_f(ans_d2); vsip_cmalldestroy_f(d_2);
   }
   return;
}
