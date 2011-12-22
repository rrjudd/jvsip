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
/* $Id: rvcmmul_f.h,v 2.0 2003/02/22 15:23:27 judd Exp $ */
static void rvcmmul_f(void){
   printf("********\nTEST rvcmmul_f\n");
   {
     vsip_scalar_f data_a1[] = { 1, 2, 3, 4 };
     vsip_scalar_f data_a2[] = { 6, 5, 4, 3, 2, 1};
     vsip_scalar_f data_b[] = { 1,.1, 1,.1,  1,.1, 1,.1,
                                  1,.1, 1,.1,  1,.1, 1,.1,
                                  1,.1, 1,.1,  1,.1, 1,.1,
                                  1,.1, 1,.1,  1,.1, 1,.1,
                                  1,.1, 1,.1,  1,.1, 1,.1,
                                  1,.1, 1,.1,  1,.1, 1,.1 };
     vsip_scalar_f ans1[] = { 1,.1, 2,.2, 3,.3, 4,.4,
                                1,.1, 2,.2, 3,.3, 4,.4, 
                                1,.1, 2,.2, 3,.3, 4,.4,
                                1,.1, 2,.2, 3,.3, 4,.4,
                                1,.1, 2,.2, 3,.3, 4,.4,
                                1,.1, 2,.2, 3,.3, 4,.4 };
     vsip_scalar_f ans2[] = { 6,.6, 6,.6, 6,.6, 6,.6,
                                5,.5, 5,.5, 5,.5, 5,.5,
                                4,.4, 4,.4, 4,.4, 4,.4,
                                3,.3, 3,.3, 3,.3, 3,.3,
                                2,.2, 2,.2, 2,.2, 2,.2,
                                1,.1, 1,.1, 1,.1, 1,.1 };

     vsip_block_f   *block_a1 = vsip_blockbind_f(data_a1,4,VSIP_MEM_NONE);
     vsip_block_f   *block_a2 = vsip_blockbind_f(data_a2,6,VSIP_MEM_NONE);
     vsip_cblock_f  *block_b = vsip_cblockbind_f(data_b,NDPTR_f,24,VSIP_MEM_NONE);
     vsip_cblock_f  *block_c = vsip_cblockcreate_f(100,VSIP_MEM_NONE);
     vsip_cblock_f  *block_d = vsip_cblockcreate_f(100,VSIP_MEM_NONE);
     vsip_cblock_f  *ans1_block = vsip_cblockbind_f(ans1,NDPTR_f,24,VSIP_MEM_NONE);
     vsip_cblock_f  *ans2_block = vsip_cblockbind_f(ans2,NDPTR_f,24,VSIP_MEM_NONE);

     vsip_vview_f   *a1 = vsip_vbind_f(block_a1,0,1,4);
     vsip_vview_f   *a2 = vsip_vbind_f(block_a2,0,1,6);
     vsip_cmview_f  *b = vsip_cmbind_f(block_b,0,4,6,1,4);
     vsip_cmview_f  *c = vsip_cmbind_f(block_c,95,-1,6,-12,4);
     vsip_cmview_f  *d = vsip_cmbind_f(block_d,0,16,6,2,4);

     vsip_cmview_f  *ansm1 = vsip_cmbind_f(ans1_block,0,4,6,1,4);
     vsip_cmview_f  *ansm2 = vsip_cmbind_f(ans2_block,0,4,6,1,4);
     vsip_cmview_f  *chk = vsip_cmcreate_f(6,4,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f   *chk_r = vsip_mrealview_f(chk);

     vsip_blockadmit_f(block_a1,VSIP_TRUE);
     vsip_blockadmit_f(block_a2,VSIP_TRUE);
     vsip_cblockadmit_f(block_b,VSIP_TRUE);
     vsip_cblockadmit_f(ans1_block,VSIP_TRUE);
     vsip_cblockadmit_f(ans2_block,VSIP_TRUE);

     printf("vsip_rvcmmul_f(a,b,VSIP_ROW,c); \n");
     vsip_rvcmmul_f(a1,b,VSIP_ROW,c);
     printf("vector a\n");VU_vprintm_f("6.2",a1);
     printf("matrix b\n");VU_cmprintm_f("6.2",b);
     printf("matrix c\n");VU_cmprintm_f("6.2",c);
     printf("right answer\n");VU_cmprintm_f("6.2",ansm1);
     vsip_cmsub_f(c,ansm1,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_f(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\nb,c in place\n");
     vsip_cmcopy_f_f(b,d);
     vsip_rvcmmul_f(a1,d,VSIP_ROW,d);
     vsip_cmsub_f(d,ansm1,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_f(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("vsip_rvcmmul_f(a,b,VSIP_COL,c); \n");
     vsip_rvcmmul_f(a2,b,VSIP_COL,c);
     printf("vector a\n");VU_vprintm_f("6.2",a2);
     printf("matrix b\n");VU_cmprintm_f("6.2",b);
     printf("matrix c\n");VU_cmprintm_f("6.2",c);
     printf("right answer\n");VU_cmprintm_f("6.2",ansm2);
     vsip_cmsub_f(c,ansm2,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_f(chk_r) > .5)
         printf("error\n");
     else 
         printf("correct\n");

     printf("\nb,c in place\n");
     vsip_cmcopy_f_f(b,c);
     vsip_rvcmmul_f(a2,c,VSIP_COL,c);
     vsip_cmsub_f(c,ansm2,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_f(chk_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_valldestroy_f(a1);
     vsip_valldestroy_f(a2);
     vsip_cmalldestroy_f(b);
     vsip_cmalldestroy_f(c);
     vsip_cmalldestroy_f(d);
     vsip_mdestroy_f(chk_r);
     vsip_cmalldestroy_f(chk);
     vsip_cmalldestroy_f(ansm1);
     vsip_cmalldestroy_f(ansm2);
   }
   return;
}
