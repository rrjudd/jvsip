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
/* $Id: cmprod_d.h,v 2.1 2006/04/09 19:28:53 judd Exp $ */
#include"VU_cmprintm_d.include"
static void cmprod_d(void){
   printf("********\nTEST cmprod_d\n");
   {
     vsip_scalar_d datal_r[] = {1, 2.0, 3.0,  4,  5.0,
                                5,  .1,  .2, .3,   .4,
                                4, 3.0, 2.0,  0, -1.0};
     vsip_scalar_d datal_i[] = {9, 3.0, 2.0,  4.3,  3.2,
                                5,  .1,  1.2, .3,   1.4,
                                3, 2.0, -2.1,  0.1, 1.0};
     vsip_scalar_d datar_r[] = { .1, .2, .3, .4,    
                              1.0, 1.1, 1.2, 1.3,
                              2.1, 2.2, 2.3, 2.4,
                              -1.1, -1.2, -1.3, -1.4,
                              2.1, 2.2, 2.3, 3.4};
     vsip_scalar_d datar_i[] = { 1.1, 5.2, 3.3, 1.4,    
                              2.1, 1.0, 1.2, 1.2,
                              4.1, 3.0, 2.3, 2.3,
                               1.1, -1.2, -1.3,  1.0,
                              1.0, 2.2, -2.3, 3.4};
     vsip_scalar_d ans_data_r[] = { -17.27, -41.34,  -7.85, -13.04,
                                       -7.07, -10.83,  -1.88,  -8.35,
                                       5.5,   -7.08,   2.06,   1.63};
     vsip_scalar_d ans_data_i[] = { 40.43, 35.62, 10.73, 51.06,
                                       5.55, -0.39,  0.66,  8.03,
                                      17.78, 27.86, 24.34, 12.42};
     vsip_cblock_d *blockl = vsip_cblockbind_d(datal_r,datal_i,15,VSIP_MEM_NONE);
     vsip_cblock_d *blockr = vsip_cblockbind_d(datar_r,datar_i,20,VSIP_MEM_NONE);
     vsip_cblock_d *block_ans = vsip_cblockbind_d(ans_data_r,ans_data_i,12,VSIP_MEM_NONE);
     vsip_cblock_d *block  = vsip_cblockcreate_d(70,VSIP_MEM_NONE);
     vsip_cmview_d *ml = vsip_cmbind_d(blockl,0,5,3,1,5);
     vsip_cmview_d *mr = vsip_cmbind_d(blockr,0,4,5,1,4);
     vsip_cmview_d *ans = vsip_cmbind_d(block_ans,0,4,3,1,4);
     vsip_cmview_d *a = vsip_cmbind_d(block,15,-1,3,-3,5);
     vsip_cmview_d *b = vsip_cmbind_d(block,50,-2,5,-10,4);
     vsip_cmview_d *c = vsip_cmbind_d(block,49,-8,3,-2,4);
     vsip_cmview_d *chk = vsip_cmcreate_d(3,4,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *chk_r = vsip_mrealview_d(chk);
     vsip_cblockadmit_d(blockl,VSIP_TRUE);
     vsip_cblockadmit_d(blockr,VSIP_TRUE);
     vsip_cblockadmit_d(block_ans,VSIP_TRUE);
     vsip_cmcopy_d_d(ml,a);
     vsip_cmcopy_d_d(mr,b);
     vsip_cmprod_d(a,b,c);
     printf("vsip_cmprod_d(a,b,c)\n");    
     printf("a\n"); VU_cmprintm_d("6.4",a);
     printf("b\n"); VU_cmprintm_d("6.4",b);
     printf("c\n"); VU_cmprintm_d("6.4",c);
     printf("right answer\n"); VU_cmprintm_d("6.4",ans);
     vsip_cmsub_d(c,ans,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_d(chk_r) > .5)
         printf("error\n");
     else
         printf("correct\n");
     { /* ccc */
         vsip_cmview_d *a1 = vsip_cmcreate_d(3,5,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(5,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(3,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod_d(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_d("6.4",c1);
         printf("right answer\n"); VU_cmprintm_d("6.4",ans);
         vsip_cmsub_d(c1,ans,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_d(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_d(a1);
         vsip_cmalldestroy_d(b1);
         vsip_cmalldestroy_d(c1);
     }
     { /* ccr */
         vsip_cmview_d *a1 = vsip_cmcreate_d(3,5,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(5,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(3,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod_d(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_d("6.4",c1);
         printf("right answer\n"); VU_cmprintm_d("6.4",ans);
         vsip_cmsub_d(c1,ans,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_d(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_d(a1);
         vsip_cmalldestroy_d(b1);
         vsip_cmalldestroy_d(c1);
     }
     { /* crc */
         vsip_cmview_d *a1 = vsip_cmcreate_d(3,5,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(5,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(3,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod_d(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_d("6.4",c1);
         printf("right answer\n"); VU_cmprintm_d("6.4",ans);
         vsip_cmsub_d(c1,ans,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_d(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_d(a1);
         vsip_cmalldestroy_d(b1);
         vsip_cmalldestroy_d(c1);
     }
     { /* crr */
         vsip_cmview_d *a1 = vsip_cmcreate_d(3,5,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(5,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(3,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod_d(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_d("6.4",c1);
         printf("right answer\n"); VU_cmprintm_d("6.4",ans);
         vsip_cmsub_d(c1,ans,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_d(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_d(a1);
         vsip_cmalldestroy_d(b1);
         vsip_cmalldestroy_d(c1);
     }
     { /* rcc */
         vsip_cmview_d *a1 = vsip_cmcreate_d(3,5,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(5,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(3,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod_d(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_d("6.4",c1);
         printf("right answer\n"); VU_cmprintm_d("6.4",ans);
         vsip_cmsub_d(c1,ans,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_d(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_d(a1);
         vsip_cmalldestroy_d(b1);
         vsip_cmalldestroy_d(c1);
     }
     { /* rcr */
         vsip_cmview_d *a1 = vsip_cmcreate_d(3,5,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(5,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(3,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod_d(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_d("6.4",c1);
         printf("right answer\n"); VU_cmprintm_d("6.4",ans);
         vsip_cmsub_d(c1,ans,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_d(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_d(a1);
         vsip_cmalldestroy_d(b1);
         vsip_cmalldestroy_d(c1);
     }
     { /* rrc */
         vsip_cmview_d *a1 = vsip_cmcreate_d(3,5,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(5,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(3,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod_d(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_d("6.4",c1);
         printf("right answer\n"); VU_cmprintm_d("6.4",ans);
         vsip_cmsub_d(c1,ans,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_d(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_d(a1);
         vsip_cmalldestroy_d(b1);
         vsip_cmalldestroy_d(c1);
     }
     { /* rrr */
         vsip_cmview_d *a1 = vsip_cmcreate_d(3,5,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(5,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(3,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod_d(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_d("6.4",c1);
         printf("right answer\n"); VU_cmprintm_d("6.4",ans);
         vsip_cmsub_d(c1,ans,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_d(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_d(a1);
         vsip_cmalldestroy_d(b1);
         vsip_cmalldestroy_d(c1);
     }
     
     vsip_cmalldestroy_d(ml);
     vsip_cmalldestroy_d(mr);
     vsip_cmdestroy_d(a);
     vsip_cmdestroy_d(b);
     vsip_cmalldestroy_d(c);
     vsip_cmalldestroy_d(ans);
     vsip_mdestroy_d(chk_r);
     vsip_cmalldestroy_d(chk);
   }
   return;
}
