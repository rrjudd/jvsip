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
/* $Id: cmherm_d.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
#include"VU_cmprintm_d.include"
static void cmherm_d(void){
   printf("********\nTEST cmherm_d\n");
   {
     vsip_scalar_d data_1_r[] = {1,  2,  3,  4,
                                  5,  6,  7,  8, 
                                  9, 10, 11, 12,
                                 13, 14, 15, 16};
     vsip_scalar_d data_1_i[] = {9,  8,  7,  6,
                                  5,  4,  2,  1, 
                                  12, 10, 9, 7,
                                  14, 11, 8, 5};
     vsip_scalar_d ans_1_r[] = {1,  2,  3,  4,
                                  5,  6,  7,  8, 
                                  9, 10, 11, 12,
                                 13, 14, 15, 16};
     vsip_scalar_d ans_1_i[] = {-9,  -8,  -7,  -6,
                                  -5,  -4,  -2,  -1, 
                                  -12, -10, -9, -7,
                                  -14, -11, -8, -5};
     vsip_scalar_d data_2_r[] = {  .1,  .2,  .3,  .4,    
                                  1.0, 1.1, 1.2, 1.3,
                                  2.1, 2.2, 2.3, 2.4};
     vsip_scalar_d data_2_i[] = {  1,  2,  3,  4,    
                                   -1.0, -1.1, -1.2, -1.3,
                                    .1, .2, .3, .4};
     vsip_scalar_d ans_2_r[] = {  .1,  .2,  .3,  .4,    
                                  1.0, 1.1, 1.2, 1.3,
                                  2.1, 2.2, 2.3, 2.4};
     vsip_scalar_d ans_2_i[] = {  -1,  -2,  -3,  -4,    
                                   +1.0, +1.1, +1.2, +1.3,
                                    -.1, -.2, -.3, -.4};
     vsip_cblock_d *block_1 = vsip_cblockbind_d(data_1_r,data_1_i,16,VSIP_MEM_NONE);
     vsip_cblock_d *block_2 = vsip_cblockbind_d(data_2_r,data_2_i,12,VSIP_MEM_NONE);
     vsip_cblock_d *ans_block_1 = vsip_cblockbind_d(ans_1_r,ans_1_i,16,VSIP_MEM_NONE);
     vsip_cblock_d *ans_block_2 = vsip_cblockbind_d(ans_2_r,ans_2_i,12,VSIP_MEM_NONE);
     vsip_cblock_d *block = vsip_cblockcreate_d(200,VSIP_MEM_NONE);
     vsip_cmview_d *d_1   = vsip_cmbind_d(block_1,0,4,4,1,4);
     vsip_cmview_d *ans_d1 = vsip_cmbind_d(ans_block_1,0,1,4,4,4);
     vsip_cmview_d *d_2   = vsip_cmbind_d(block_2,0,4,3,1,4);
     vsip_cmview_d *ans_d2 = vsip_cmbind_d(ans_block_2,0,1,4,4,3);

     vsip_cmview_d *a_1 = vsip_cmbind_d(block,18,-4,4,-1,4);
     vsip_cmview_d *a_2 = vsip_cmbind_d(block,70,-2,3,-10,4);

     vsip_cmview_d *c_2 = vsip_cmbind_d(block,150,8,4,1,3);
     vsip_cmview_d *chk_1 = vsip_cmcreate_d(4,4,VSIP_COL,VSIP_MEM_NONE);
     vsip_cmview_d *chk_2 = vsip_cmcreate_d(4,3,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *chk_1_r = vsip_mrealview_d(chk_1);
     vsip_mview_d *chk_2_r =  vsip_mrealview_d(chk_2);
     vsip_cmview_d *ans_1 = vsip_cmcreate_d(4,4,VSIP_COL,VSIP_MEM_NONE);
     vsip_cmview_d *ans_2 = vsip_cmcreate_d(4,3,VSIP_COL,VSIP_MEM_NONE);

     vsip_cblockadmit_d(block_1,VSIP_TRUE);
     vsip_cblockadmit_d(block_2,VSIP_TRUE);
     vsip_cblockadmit_d(ans_block_1,VSIP_TRUE);
     vsip_cblockadmit_d(ans_block_2,VSIP_TRUE);

     vsip_cmcopy_d_d(ans_d1,ans_1);
     vsip_cmcopy_d_d(ans_d2,ans_2);
     vsip_cmcopy_d_d(d_1,a_1);
     vsip_cmcopy_d_d(d_2,a_2);

     printf("4x4 in place\n");
     printf("matrix a = ");VU_cmprintm_d("6.4",a_1);
     printf("vsip_cmherm_d(a_1,a_1)\n");
     vsip_cmherm_d(a_1,a_1);
     printf("matrix a = ");VU_cmprintm_d("6.4",a_1);
     printf("matrix ans = ");VU_cmprintm_d("6.4",ans_1);
     vsip_cmsub_d(a_1,ans_1,chk_1); vsip_cmmag_d(chk_1,chk_1_r); vsip_mclip_d(chk_1_r,.0001,.0001,0,1,chk_1_r);
     if(vsip_msumval_d(chk_1_r) > .5)
         printf("error\n\n");
     else
         printf("correct\n\n");
     
     printf("3x4 out of place\n");
     printf("vsip_cmherm_d(a,b)\n");
     printf("matrix a = "); VU_cmprintm_d("6.4",a_2);
     vsip_cmherm_d(a_2,c_2);
     printf("matrix b = "); VU_cmprintm_d("6.4",c_2);
     printf("matrix ans = ");VU_cmprintm_d("6.4",ans_2);
     vsip_cmsub_d(c_2,ans_2,chk_2); vsip_cmmag_d(chk_2,chk_2_r); vsip_mclip_d(chk_2_r,.0001,.0001,0,1,chk_2_r);
     if(vsip_msumval_d(chk_2_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_mdestroy_d(chk_1_r);
     vsip_mdestroy_d(chk_2_r);
     vsip_cmalldestroy_d(chk_1);
     vsip_cmalldestroy_d(chk_2);
     vsip_cmdestroy_d(a_1); vsip_cmdestroy_d(a_2); vsip_cmalldestroy_d(c_2);
     vsip_cmalldestroy_d(ans_1); vsip_cmalldestroy_d(ans_2);
     vsip_cmdestroy_d(ans_d1); vsip_cmalldestroy_d(d_1);
     vsip_cmdestroy_d(ans_d2); vsip_cmalldestroy_d(d_2);
   }
   return;
}
