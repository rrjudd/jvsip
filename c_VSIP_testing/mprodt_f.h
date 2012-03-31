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
/* $Id: mprodt_f.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
#include"VU_mprintm_f.include"
static void mprodt_f(void){
   printf("********\nTEST mprodt_f\n");
   {
     vsip_scalar_f datal[] = {1, 2.0, 3.0,  4,  5.0,
                                5,  .1,  .2, .3,   .4,
                                4, 3.0, 2.0,  0, -1.0};
     vsip_scalar_f datar[] = { .1, .2, .3, .4,    
                              1.0, 1.1, 1.2, 1.3,
                              2.1, 2.2, 2.3, 2.4,
                              -1.1, -1.2, -1.3, -1.4,
                              2.1, 2.2, 2.3, 3.4};
     vsip_scalar_f ans_data[] = { 
    5.88, 15.67, -1.14, 23.41,
    1.43,  7.02,  2.23,  3.88,
    1.56, 13.14,  6.62,  5.32};
     vsip_block_f *blockl = vsip_blockbind_f(datal,15,VSIP_MEM_NONE);
     vsip_block_f *blockr = vsip_blockbind_f(datar,20,VSIP_MEM_NONE);
     vsip_block_f *block_ans = vsip_blockbind_f(ans_data,12,VSIP_MEM_NONE);
     vsip_block_f *block  = vsip_blockcreate_f(70,VSIP_MEM_NONE);
     vsip_mview_f *ml = vsip_mbind_f(blockl,0,5,3,1,5);
     vsip_mview_f *mr = vsip_mbind_f(blockr,0,5,4,1,5);
     vsip_mview_f *ans = vsip_mbind_f(block_ans,0,4,3,1,4);
     vsip_mview_f *a = vsip_mbind_f(block,15,-1,3,-3,5);
     vsip_mview_f *b = vsip_mbind_f(block,50,-2,4,-10,5);
     vsip_mview_f *c = vsip_mbind_f(block,49,-8,3,-2,4);
     vsip_mview_f *chk = vsip_mcreate_f(3,4,VSIP_COL,VSIP_MEM_NONE);
     vsip_blockadmit_f(blockl,VSIP_TRUE);
     vsip_blockadmit_f(blockr,VSIP_TRUE);
     vsip_blockadmit_f(block_ans,VSIP_TRUE);
     vsip_mcopy_f_f(ml,a);
     vsip_mcopy_f_f(mr,b);
     vsip_mprodt_f(a,b,c);
     printf("vsip_mprodt_f(a,b,c)\n");    
     printf("a\n"); VU_mprintm_f("6.4",a);
     printf("b\n"); VU_mprintm_f("6.4",b);
     printf("c\n"); VU_mprintm_f("6.4",c);
     printf("right answer\n"); VU_mprintm_f("6.4",ans);
     vsip_msub_f(c,ans,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");
     vsip_malldestroy_f(ml);
     vsip_malldestroy_f(mr);
     vsip_mdestroy_f(a);
     vsip_mdestroy_f(b);
     vsip_malldestroy_f(c);
     vsip_malldestroy_f(ans);
     vsip_malldestroy_f(chk);
   }
   return;
}
