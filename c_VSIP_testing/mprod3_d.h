/* Created RJudd    */
/*  */
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
/*  */
/* $Id: mprod3_d.h,v 2.1 2006/04/27 01:40:55 judd Exp $ */
static void mprod3_d(void){
   printf("********\nTEST mprod4_d\n");
   {
     vsip_scalar_d datal[] = {1.0,  2.0,  4.0,  
                              5.0,  5.0,  0.2, 
                              2.0,  0.0, 1.0}; 
                              
     vsip_scalar_d datar[] = {0.1,  0.2,  0.3,  0.4,  1.0,  1.1,  1.2,  1.3,
                              2.1,  2.2,  2.3,  2.4, -1.1, -1.2, -1.3, -1.4,
                              2.1,  2.2,  0.3,  3.2,  2.1,  2.2,  1.0,  5.1};
                              
     vsip_scalar_d ans_data[] = {0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.0,
                                 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.0,
                                 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.0};
                                 

     vsip_block_d *blockl = vsip_blockbind_d(datal,9,VSIP_MEM_NONE);
     vsip_block_d *blockr = vsip_blockbind_d(datar,24,VSIP_MEM_NONE);
     vsip_block_d *block_ans = vsip_blockbind_d(ans_data,24,VSIP_MEM_NONE);
     vsip_block_d *block  = vsip_blockcreate_d(200,VSIP_MEM_NONE);
     vsip_mview_d *ml = vsip_mbind_d(blockl,0,3,3,1,3);
     vsip_mview_d *mr = vsip_mbind_d(blockr,0,8,3,1,8);
     vsip_mview_d *ans = vsip_mbind_d(block_ans,0,8,3,1,8);
     vsip_mview_d *a = vsip_mbind_d(block,20,-1,3,-4,3);
     vsip_mview_d *a_cm = vsip_mcreate_d(3,3,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *a_rm = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d *b_cm = vsip_mcreate_d(3,8,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *b_rm = vsip_mcreate_d(3,8,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d *c_cm = vsip_mcreate_d(3,8,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *c_rm = vsip_mcreate_d(3,8,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d *b = vsip_mbind_d(block,100,-1,3,-6,8);
     vsip_mview_d *c = vsip_mbind_d(block,150,-8,3,-1,8);
     vsip_mview_d *chk = vsip_mcreate_d(3,8,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *aa = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d *bb = vsip_mcreate_d(3,8,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *cc = vsip_mcreate_d(3,8,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_d *c_cc = vsip_cmcreate_d(3,8,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_d *c_bb = vsip_cmcreate_d(3,8,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *i_cc = vsip_mimagview_d(c_cc);
     vsip_mview_d *r_bb = vsip_mrealview_d(c_bb);
     
     vsip_blockadmit_d(blockl,VSIP_TRUE);
     vsip_blockadmit_d(blockr,VSIP_TRUE);
     vsip_blockadmit_d(block_ans,VSIP_TRUE);
     vsip_mcopy_d_d(ml,a);
     vsip_mcopy_d_d(ml,a_cm);
     vsip_mcopy_d_d(ml,a_rm);
     vsip_mcopy_d_d(mr,b);
     vsip_mcopy_d_d(mr,b_cm);
     vsip_mcopy_d_d(mr,b_rm);
     vsip_mcopy_d_d(mr,r_bb);
     vsip_mcopy_d_d(a,aa); vsip_mcopy_d_d(b,bb);
     
     vsip_mprod_d(a,b,ans);
     
     vsip_mprod3_d(a,b,c);
     printf("vsip_mprod3_d(a,b,c)\n");    
     printf("a\n"); VU_mprintm_d("6.4",a);
     printf("b\n"); VU_mprintm_d("6.4",b);
     printf("c\n"); VU_mprintm_d("6.4",c);
     printf("right answer\n"); VU_mprintm_d("6.4",ans);
     vsip_msub_d(c,ans,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_mprod3_d(aa,bb,cc);
     printf("vsip_mprod3_d(aa,bb,cc)\n");    
     printf("aa\n"); VU_mprintm_d("6.4",aa);
     printf("bb\n"); VU_mprintm_d("6.4",bb);
     printf("cc\n"); VU_mprintm_d("6.4",cc);
     printf("right answer\n"); VU_mprintm_d("6.4",ans);
     vsip_msub_d(cc,ans,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_mprod3_d(aa,r_bb,i_cc);
     printf("vsip_mprod3_d(aa,bb,cc)\n");
     printf("aa\n"); VU_mprintm_d("6.4",aa);
     printf("bb\n"); VU_mprintm_d("6.4",r_bb);
     printf("cc\n"); VU_mprintm_d("6.4",i_cc);
     printf("right answer\n"); VU_mprintm_d("6.4",ans);
     vsip_msub_d(i_cc,ans,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");
      
     printf("check ccc\n");
     vsip_mprod3_d(a_cm,b_cm,c_cm);
     vsip_msub_d(c_cm,ans,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check ccr\n");
     vsip_mprod3_d(a_cm,b_cm,c_rm);
     vsip_msub_d(c_rm,ans,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check crc\n");
     vsip_mprod3_d(a_cm,b_rm,c_cm);
     vsip_msub_d(c_cm,ans,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check crr\n");
     vsip_mprod3_d(a_cm,b_rm,c_rm);
     vsip_msub_d(c_rm,ans,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check rcc\n");
     vsip_mprod3_d(a_rm,b_cm,c_cm);
     vsip_msub_d(c_cm,ans,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check rcr\n");
     vsip_mprod3_d(a_rm,b_cm,c_rm);
     vsip_msub_d(c_rm,ans,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check rrc\n");
     vsip_mprod3_d(a_rm,b_rm,c_cm);
     vsip_msub_d(c_cm,ans,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check rrr\n");
     vsip_mprod3_d(a_rm,b_rm,c_rm);
     vsip_msub_d(c_rm,ans,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_malldestroy_d(ml);
     vsip_malldestroy_d(mr);
     vsip_mdestroy_d(a);
     vsip_malldestroy_d(aa);
     vsip_mdestroy_d(b);
     vsip_malldestroy_d(bb);
     vsip_malldestroy_d(c);
     vsip_malldestroy_d(cc);
     vsip_malldestroy_d(ans);
     vsip_malldestroy_d(chk);
     vsip_mdestroy_d(i_cc);
     vsip_mdestroy_d(r_bb);
     vsip_cmalldestroy_d(c_cc);
     vsip_cmalldestroy_d(c_bb);
     vsip_malldestroy_d(a_cm);
     vsip_malldestroy_d(a_rm);
     vsip_malldestroy_d(b_cm);
     vsip_malldestroy_d(b_rm);
     vsip_malldestroy_d(c_cm);
     vsip_malldestroy_d(c_rm);
   }
   return;
}
