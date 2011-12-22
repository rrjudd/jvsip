/*
 *  cmprod3_f.h
 *  vsip_atest
 *
 *  Created by Randall Judd on 4/26/06.
 *  Copyright 2006 
 *
 */

/* $Id: cmprod3_f.h,v 2.1 2006/04/27 01:40:55 judd Exp $ */
static void cmprod3_f(void){
   printf("********\nTEST cmprod3_f\n");
   {
     vsip_scalar_f datal_r[] = {1.0, 2.0,  3.0,  
                                5.0, 5.0,  0.1, 
                                2.0, 0.0, -1.0};
     vsip_scalar_f datal_i[] = {9.0, 3.0,  2.0, 
                                3.2, 5.0,  1.2,
                               -2.1, 0.1,  2.0};
                            
                              

     vsip_scalar_f datar_r[] = {0.1, 0.2, 0.3, 0.4,  1.0,  1.1,  1.2,  1.3,
                                2.1, 2.2, 2.3, 2.4, -1.1, -2.2, -2.3, -1.4,
                                3.1, 2.2, 1.3, 0.4, -1.1, -1.3,  4.3, -1.4};

     vsip_scalar_f datar_i[] = { 1.1, 5.2,  3.3, 1.4, 2.1,  1.0,  1.2, 1.2,
                                 4.1, 3.0,  2.3, 2.3, 1.1, -6.2, -1.3, 9.3,
                                 1.0, 2.2, -2.3, 3.4, 4.6,  5.0,  2.1, 7.3};
                                 

     /* we use vsip_cmprod_f to fill up the answer data space */
     vsip_scalar_f ans_data_r[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}; 
                                    
     vsip_scalar_f ans_data_i[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
                                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
                                     

     vsip_cblock_f *blockl = vsip_cblockbind_f(datal_r,datal_i,9,VSIP_MEM_NONE);
     vsip_cblock_f *blockr = vsip_cblockbind_f(datar_r,datar_i,24,VSIP_MEM_NONE);
     vsip_cblock_f *block_ans = vsip_cblockbind_f(ans_data_r,ans_data_i,24,VSIP_MEM_NONE);
     vsip_cblock_f *block  = vsip_cblockcreate_f(250,VSIP_MEM_NONE);
     vsip_cmview_f *ml = vsip_cmbind_f(blockl,0,3,3,1,3);
     vsip_cmview_f *mr = vsip_cmbind_f(blockr,0,8,3,1,8);
     vsip_cmview_f *ans = vsip_cmbind_f(block_ans,0,8,3,1,8);
     vsip_cmview_f *a = vsip_cmbind_f(block,70,-1,3,-6,3);
     vsip_cmview_f *b = vsip_cmbind_f(block,71, 1,3,5,8);
     vsip_cmview_f *c = vsip_cmbind_f(block,220,-9,3,-1,8);
     vsip_cmview_f *chk = vsip_cmcreate_f(3,8,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f *chk_r = vsip_mrealview_f(chk);
     vsip_cblockadmit_f(blockl,VSIP_TRUE);
     vsip_cblockadmit_f(blockr,VSIP_TRUE);
     vsip_cblockadmit_f(block_ans,VSIP_TRUE);
     vsip_cmcopy_f_f(ml,a);
     vsip_cmcopy_f_f(mr,b);
     vsip_cmprod_f(a,b,ans);
     vsip_cmprod3_f(a,b,c);
     printf("vsip_cmprod3_f(a,b,c)\n");    
     printf("a\n"); VU_cmprintm_f("6.4",a);
     printf("b\n"); VU_cmprintm_f("6.4",b);
     printf("c\n"); VU_cmprintm_f("6.4",c);
     printf("right answer\n"); VU_cmprintm_f("6.4",ans);
     vsip_cmsub_f(c,ans,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_f(chk_r) > .5)
         printf("error\n");
     else
         printf("correct\n");
     { /* ccc */
         vsip_cmview_f *a1 = vsip_cmcreate_f(4,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_f *b1 = vsip_cmcreate_f(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_f *c1 = vsip_cmcreate_f(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmcopy_f_f(a,a1);
         vsip_cmcopy_f_f(b,b1);
         vsip_cmprod3_f(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_f("6.4",c1);
         printf("right answer\n"); VU_cmprintm_f("6.4",ans);
         vsip_cmsub_f(c1,ans,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_f(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_f(a1);
         vsip_cmalldestroy_f(b1);
         vsip_cmalldestroy_f(c1);
     }
     { /* ccr */
         vsip_cmview_f *a1 = vsip_cmcreate_f(4,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_f *b1 = vsip_cmcreate_f(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_f *c1 = vsip_cmcreate_f(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopy_f_f(a,a1);
         vsip_cmcopy_f_f(b,b1);
         vsip_cmprod3_f(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_f("6.4",c1);
         printf("right answer\n"); VU_cmprintm_f("6.4",ans);
         vsip_cmsub_f(c1,ans,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_f(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_f(a1);
         vsip_cmalldestroy_f(b1);
         vsip_cmalldestroy_f(c1);
     }
     { /* crc */
         vsip_cmview_f *a1 = vsip_cmcreate_f(4,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_f *b1 = vsip_cmcreate_f(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_f *c1 = vsip_cmcreate_f(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmcopy_f_f(a,a1);
         vsip_cmcopy_f_f(b,b1);
         vsip_cmprod3_f(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_f("6.4",c1);
         printf("right answer\n"); VU_cmprintm_f("6.4",ans);
         vsip_cmsub_f(c1,ans,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_f(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_f(a1);
         vsip_cmalldestroy_f(b1);
         vsip_cmalldestroy_f(c1);
     }
     { /* crr */
         vsip_cmview_f *a1 = vsip_cmcreate_f(4,4,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_f *b1 = vsip_cmcreate_f(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_f *c1 = vsip_cmcreate_f(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopy_f_f(a,a1);
         vsip_cmcopy_f_f(b,b1);
         vsip_cmprod3_f(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_f("6.4",c1);
         printf("right answer\n"); VU_cmprintm_f("6.4",ans);
         vsip_cmsub_f(c1,ans,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_f(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_f(a1);
         vsip_cmalldestroy_f(b1);
         vsip_cmalldestroy_f(c1);
     }
     { /* rcc */
         vsip_cmview_f *a1 = vsip_cmcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_f *b1 = vsip_cmcreate_f(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_f *c1 = vsip_cmcreate_f(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmcopy_f_f(a,a1);
         vsip_cmcopy_f_f(b,b1);
         vsip_cmprod3_f(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_f("6.4",c1);
         printf("right answer\n"); VU_cmprintm_f("6.4",ans);
         vsip_cmsub_f(c1,ans,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_f(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_f(a1);
         vsip_cmalldestroy_f(b1);
         vsip_cmalldestroy_f(c1);
     }
     { /* rcr */
         vsip_cmview_f *a1 = vsip_cmcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_f *b1 = vsip_cmcreate_f(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmview_f *c1 = vsip_cmcreate_f(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopy_f_f(a,a1);
         vsip_cmcopy_f_f(b,b1);
         vsip_cmprod3_f(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_f("6.4",c1);
         printf("right answer\n"); VU_cmprintm_f("6.4",ans);
         vsip_cmsub_f(c1,ans,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_f(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_f(a1);
         vsip_cmalldestroy_f(b1);
         vsip_cmalldestroy_f(c1);
     }
     { /* rrc */
         vsip_cmview_f *a1 = vsip_cmcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_f *b1 = vsip_cmcreate_f(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_f *c1 = vsip_cmcreate_f(4,8,VSIP_COL,VSIP_MEM_NONE);
         vsip_cmcopy_f_f(a,a1);
         vsip_cmcopy_f_f(b,b1);
         vsip_cmprod3_f(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_f("6.4",c1);
         printf("right answer\n"); VU_cmprintm_f("6.4",ans);
         vsip_cmsub_f(c1,ans,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_f(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_f(a1);
         vsip_cmalldestroy_f(b1);
         vsip_cmalldestroy_f(c1);
     }
     { /* rrr */
         vsip_cmview_f *a1 = vsip_cmcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_f *b1 = vsip_cmcreate_f(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmview_f *c1 = vsip_cmcreate_f(4,8,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmcopy_f_f(a,a1);
         vsip_cmcopy_f_f(b,b1);
         vsip_cmprod3_f(a1,b1,c1);
         printf("c1\n"); VU_cmprintm_f("6.4",c1);
         printf("right answer\n"); VU_cmprintm_f("6.4",ans);
         vsip_cmsub_f(c1,ans,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
         if(vsip_msumval_f(chk_r) > .5)
            printf("error\n");
         else
         printf("correct\n");
         vsip_cmalldestroy_f(a1);
         vsip_cmalldestroy_f(b1);
         vsip_cmalldestroy_f(c1);
     }
     
     vsip_cmalldestroy_f(ml);
     vsip_cmalldestroy_f(mr);
     vsip_cmdestroy_f(a);
     vsip_cmdestroy_f(b);
     vsip_cmalldestroy_f(c);
     vsip_cmalldestroy_f(ans);
     vsip_mdestroy_f(chk_r);
     vsip_cmalldestroy_f(chk);
   }
   return;
}


