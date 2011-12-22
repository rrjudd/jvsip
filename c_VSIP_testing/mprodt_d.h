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
/* $Id: mprodt_d.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
static void mprodt_d(void){
   printf("********\nTEST mprodt_d\n");
   {
     vsip_scalar_d datal[] = {1, 2.0, 3.0,  4,  5.0,
                                5,  .1,  .2, .3,   .4,
                                4, 3.0, 2.0,  0, -1.0};
     vsip_scalar_d datar[] = { .1, .2, .3, .4,    
                              1.0, 1.1, 1.2, 1.3,
                              2.1, 2.2, 2.3, 2.4,
                              -1.1, -1.2, -1.3, -1.4,
                              2.1, 2.2, 2.3, 3.4};
     vsip_scalar_d ans_data[] = { 
    5.88, 15.67, -1.14, 23.41,
    1.43,  7.02,  2.23,  3.88,
    1.56, 13.14,  6.62,  5.32};
     vsip_block_d *blockl = vsip_blockbind_d(datal,15,VSIP_MEM_NONE);
     vsip_block_d *blockr = vsip_blockbind_d(datar,20,VSIP_MEM_NONE);
     vsip_block_d *block_ans = vsip_blockbind_d(ans_data,12,VSIP_MEM_NONE);
     vsip_block_d *block  = vsip_blockcreate_d(70,VSIP_MEM_NONE);
     vsip_mview_d *ml = vsip_mbind_d(blockl,0,5,3,1,5);
     vsip_mview_d *mr = vsip_mbind_d(blockr,0,5,4,1,5);
     vsip_mview_d *ans = vsip_mbind_d(block_ans,0,4,3,1,4);
     vsip_mview_d *a = vsip_mbind_d(block,15,-1,3,-3,5);
     vsip_mview_d *b = vsip_mbind_d(block,50,-2,4,-10,5);
     vsip_mview_d *c = vsip_mbind_d(block,49,-8,3,-2,4);
     vsip_mview_d *chk = vsip_mcreate_d(3,4,VSIP_COL,VSIP_MEM_NONE);
     vsip_blockadmit_d(blockl,VSIP_TRUE);
     vsip_blockadmit_d(blockr,VSIP_TRUE);
     vsip_blockadmit_d(block_ans,VSIP_TRUE);
     vsip_mcopy_d_d(ml,a);
     vsip_mcopy_d_d(mr,b);
     vsip_mprodt_d(a,b,c);
     printf("vsip_mprodt_d(a,b,c)\n");    
     printf("a\n"); VU_mprintm_d("6.4",a);
     printf("b\n"); VU_mprintm_d("6.4",b);
     printf("c\n"); VU_mprintm_d("6.4",c);
     printf("right answer\n"); VU_mprintm_d("6.4",ans);
     vsip_msub_d(c,ans,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");
     vsip_malldestroy_d(ml);
     vsip_malldestroy_d(mr);
     vsip_mdestroy_d(a);
     vsip_mdestroy_d(b);
     vsip_malldestroy_d(c);
     vsip_malldestroy_d(ans);
     vsip_malldestroy_d(chk);
   }
   return;
}
