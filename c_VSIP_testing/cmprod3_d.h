/*
 *  cmprod3_d.h
 *  vsip_atest
 *
 *  Created by Randall Judd on 4/26/06.
 *  Copyright 2006 
 *
 */

/* $Id: cmprod3_d.h,v 2.1 2006/04/27 01:40:55 judd Exp $ */
static void cmprod3_d(void){
   printf("********\nTEST cmprod3_d\n");
   {
     vsip_scalar_d datal_r[] = {1.0, 2.0,  3.0,  
                                5.0, 5.0,  0.1, 
                                2.0, 0.0, -1.0};
     vsip_scalar_d datal_i[] = {9.0, 3.0,  2.0, 
                                3.2, 5.0,  1.2,
                               -2.1, 0.1,  2.0};
                            
                              

     vsip_scalar_d datar_r[] = {0.1, 0.2, 0.3, 0.4,  1.0,  1.1,  1.2,  1.3,
                                2.1, 2.2, 2.3, 2.4, -1.1, -2.2, -2.3, -1.4,
                                3.1, 2.2, 1.3, 0.4, -1.1, -1.3,  4.3, -1.4};

     vsip_scalar_d datar_i[] = { 1.1, 5.2,  3.3, 1.4, 2.1,  1.0,  1.2, 1.2,
                                 4.1, 3.0,  2.3, 2.3, 1.1, -6.2, -1.3, 9.3,
                                 1.0, 2.2, -2.3, 3.4, 4.6,  5.0,  2.1, 7.3};
                                 

     /* we use vsip_cmprod_d to fill up the answer data space */
     vsip_scalar_d ans_data_r[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; 
                                    
     vsip_scalar_d ans_data_i[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
                                     

     vsip_cblock_d *blockl = vsip_cblockbind_d(datal_r,datal_i,9,VSIP_MEM_NONE);
     vsip_cblock_d *blockr = vsip_cblockbind_d(datar_r,datar_i,24,VSIP_MEM_NONE);
     vsip_cblock_d *block_ans = vsip_cblockbind_d(ans_data_r,ans_data_i,24,VSIP_MEM_NONE);
     vsip_cblock_d *block  = vsip_cblockcreate_d(250,VSIP_MEM_NONE);
     vsip_cmview_d *ml = vsip_cmbind_d(blockl,0,3,3,1,3);
     vsip_cmview_d *mr = vsip_cmbind_d(blockr,0,8,3,1,8);
     vsip_cmview_d *ans = vsip_cmbind_d(block_ans,0,8,3,1,8);
     vsip_cmview_d *a = vsip_cmbind_d(block,70,-1,3,-6,3);
     vsip_cmview_d *b = vsip_cmbind_d(block,71, 1,3,5,8);
     vsip_cmview_d *c = vsip_cmbind_d(block,220,-9,3,-1,8);
     vsip_cmview_d *chk = vsip_cmcreate_d(3,8,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *chk_r = vsip_mrealview_d(chk);
     vsip_cblockadmit_d(blockl,VSIP_TRUE);
     vsip_cblockadmit_d(blockr,VSIP_TRUE);
     vsip_cblockadmit_d(block_ans,VSIP_TRUE);
     vsip_cmcopy_d_d(ml,a);
     vsip_cmcopy_d_d(mr,b);
     vsip_cmprod_d(a,b,ans);
     vsip_cmprod3_d(a,b,c);
     printf("vsip_cmprod3_d(a,b,c)\n");    
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
         vsip_cmview_d *a1 = vsip_cmcreate_d(4,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod3_d(a1,b1,c1);
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
         vsip_cmview_d *a1 = vsip_cmcreate_d(4,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod3_d(a1,b1,c1);
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
         vsip_cmview_d *a1 = vsip_cmcreate_d(4,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod3_d(a1,b1,c1);
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
         vsip_cmview_d *a1 = vsip_cmcreate_d(4,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod3_d(a1,b1,c1);
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
         vsip_cmview_d *a1 = vsip_cmcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod3_d(a1,b1,c1);
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
         vsip_cmview_d *a1 = vsip_cmcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod3_d(a1,b1,c1);
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
         vsip_cmview_d *a1 = vsip_cmcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod3_d(a1,b1,c1);
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
         vsip_cmview_d *a1 = vsip_cmcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *b1 = vsip_cmcreate_d(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_d *c1 = vsip_cmcreate_d(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopy_d_d(a,a1);
         vsip_cmcopy_d_d(b,b1);
         vsip_cmprod3_d(a1,b1,c1);
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


