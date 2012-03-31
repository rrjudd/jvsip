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
/* $Id: mprod3_f.h,v 2.1 2006/04/27 01:40:55 judd Exp $ */
#include"VU_mprintm_f.include"
static void mprod3_f(void){
   printf("********\nTEST mprod4_f\n");
   {
     vsip_scalar_f datal[] = {1.0,  2.0,  4.0,  
                              5.0,  5.0,  0.2, 
                              2.0,  0.0, 1.0}; 
                              
     vsip_scalar_f datar[] = {0.1,  0.2,  0.3,  0.4,  1.0,  1.1,  1.2,  1.3,
                              2.1,  2.2,  2.3,  2.4, -1.1, -1.2, -1.3, -1.4,
                              2.1,  2.2,  0.3,  3.2,  2.1,  2.2,  1.0,  5.1};
                              
     vsip_scalar_f ans_data[] = {0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.0,
                                 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.0,
                                 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0,  0.0};
                                 

     vsip_block_f *blockl = vsip_blockbind_f(datal,9,VSIP_MEM_NONE);
     vsip_block_f *blockr = vsip_blockbind_f(datar,24,VSIP_MEM_NONE);
     vsip_block_f *block_ans = vsip_blockbind_f(ans_data,24,VSIP_MEM_NONE);
     vsip_block_f *block  = vsip_blockcreate_f(200,VSIP_MEM_NONE);
     vsip_mview_f *ml = vsip_mbind_f(blockl,0,3,3,1,3);
     vsip_mview_f *mr = vsip_mbind_f(blockr,0,8,3,1,8);
     vsip_mview_f *ans = vsip_mbind_f(block_ans,0,8,3,1,8);
     vsip_mview_f *a = vsip_mbind_f(block,20,-1,3,-4,3);
     vsip_mview_f *a_cm = vsip_mcreate_f(3,3,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f *a_rm = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f *b_cm = vsip_mcreate_f(3,8,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f *b_rm = vsip_mcreate_f(3,8,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f *c_cm = vsip_mcreate_f(3,8,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f *c_rm = vsip_mcreate_f(3,8,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f *b = vsip_mbind_f(block,100,-1,3,-6,8);
     vsip_mview_f *c = vsip_mbind_f(block,150,-8,3,-1,8);
     vsip_mview_f *chk = vsip_mcreate_f(3,8,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f *aa = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f *bb = vsip_mcreate_f(3,8,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f *cc = vsip_mcreate_f(3,8,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_f *c_cc = vsip_cmcreate_f(3,8,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_f *c_bb = vsip_cmcreate_f(3,8,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f *i_cc = vsip_mimagview_f(c_cc);
     vsip_mview_f *r_bb = vsip_mrealview_f(c_bb);
     
     vsip_blockadmit_f(blockl,VSIP_TRUE);
     vsip_blockadmit_f(blockr,VSIP_TRUE);
     vsip_blockadmit_f(block_ans,VSIP_TRUE);
     vsip_mcopy_f_f(ml,a);
     vsip_mcopy_f_f(ml,a_cm);
     vsip_mcopy_f_f(ml,a_rm);
     vsip_mcopy_f_f(mr,b);
     vsip_mcopy_f_f(mr,b_cm);
     vsip_mcopy_f_f(mr,b_rm);
     vsip_mcopy_f_f(mr,r_bb);
     vsip_mcopy_f_f(a,aa); vsip_mcopy_f_f(b,bb);
     
     vsip_mprod_f(a,b,ans);
     
     vsip_mprod3_f(a,b,c);
     printf("vsip_mprod3_f(a,b,c)\n");    
     printf("a\n"); VU_mprintm_f("6.4",a);
     printf("b\n"); VU_mprintm_f("6.4",b);
     printf("c\n"); VU_mprintm_f("6.4",c);
     printf("right answer\n"); VU_mprintm_f("6.4",ans);
     vsip_msub_f(c,ans,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_mprod3_f(aa,bb,cc);
     printf("vsip_mprod3_f(aa,bb,cc)\n");    
     printf("aa\n"); VU_mprintm_f("6.4",aa);
     printf("bb\n"); VU_mprintm_f("6.4",bb);
     printf("cc\n"); VU_mprintm_f("6.4",cc);
     printf("right answer\n"); VU_mprintm_f("6.4",ans);
     vsip_msub_f(cc,ans,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_mprod3_f(aa,r_bb,i_cc);
     printf("vsip_mprod3_f(aa,bb,cc)\n");
     printf("aa\n"); VU_mprintm_f("6.4",aa);
     printf("bb\n"); VU_mprintm_f("6.4",r_bb);
     printf("cc\n"); VU_mprintm_f("6.4",i_cc);
     printf("right answer\n"); VU_mprintm_f("6.4",ans);
     vsip_msub_f(i_cc,ans,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");
      
     printf("check ccc\n");
     vsip_mprod3_f(a_cm,b_cm,c_cm);
     vsip_msub_f(c_cm,ans,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check ccr\n");
     vsip_mprod3_f(a_cm,b_cm,c_rm);
     vsip_msub_f(c_rm,ans,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check crc\n");
     vsip_mprod3_f(a_cm,b_rm,c_cm);
     vsip_msub_f(c_cm,ans,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check crr\n");
     vsip_mprod3_f(a_cm,b_rm,c_rm);
     vsip_msub_f(c_rm,ans,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check rcc\n");
     vsip_mprod3_f(a_rm,b_cm,c_cm);
     vsip_msub_f(c_cm,ans,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check rcr\n");
     vsip_mprod3_f(a_rm,b_cm,c_rm);
     vsip_msub_f(c_rm,ans,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check rrc\n");
     vsip_mprod3_f(a_rm,b_rm,c_cm);
     vsip_msub_f(c_cm,ans,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check rrr\n");
     vsip_mprod3_f(a_rm,b_rm,c_rm);
     vsip_msub_f(c_rm,ans,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_malldestroy_f(ml);
     vsip_malldestroy_f(mr);
     vsip_mdestroy_f(a);
     vsip_malldestroy_f(aa);
     vsip_mdestroy_f(b);
     vsip_malldestroy_f(bb);
     vsip_malldestroy_f(c);
     vsip_malldestroy_f(cc);
     vsip_malldestroy_f(ans);
     vsip_malldestroy_f(chk);
     vsip_mdestroy_f(i_cc);
     vsip_mdestroy_f(r_bb);
     vsip_cmalldestroy_f(c_cc);
     vsip_cmalldestroy_f(c_bb);
     vsip_malldestroy_f(a_cm);
     vsip_malldestroy_f(a_rm);
     vsip_malldestroy_f(b_cm);
     vsip_malldestroy_f(b_rm);
     vsip_malldestroy_f(c_cm);
     vsip_malldestroy_f(c_rm);
   }
   return;
}
