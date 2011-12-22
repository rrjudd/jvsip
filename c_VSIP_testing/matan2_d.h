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
/* $Id: matan2_d.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
static void matan2_d(void){
   printf("\n*******\nTEST matan2_d\n\n");
   { vsip_scalar_d data_a[] = {0,1,2,3,4,5};
     vsip_scalar_d data_b[] = {5,4,3,2,1,0};
     vsip_scalar_d ans[] = {0, 0.2450, 0.5880, 0.9828, 1.3258, 1.5708};
     vsip_block_d  *block_a = vsip_blockbind_d(data_a,6,VSIP_MEM_NONE);
     vsip_block_d  *block_b = vsip_blockbind_d(data_b,6,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,6,VSIP_MEM_NONE);
     vsip_mview_d  *a = vsip_mbind_d(block_a,0,3,2,1,3);
     vsip_mview_d  *b = vsip_mbind_d(block_b,0,3,2,1,3);
     vsip_mview_d  *ansm = vsip_mbind_d(ans_block,0,3,2,1,3);
     vsip_mview_d  *c = vsip_mcreate_d(2,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d  *chk = vsip_mcreate_d(2,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_blockadmit_d(block_a,VSIP_TRUE);
     vsip_blockadmit_d(block_b,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);
     printf("vsip_matan2_d(a,b,c)\n");
     vsip_matan2_d(a,b,c);
     printf("matrix a\n");VU_mprintm_d("8.6",a);
     printf("matrix b\n");VU_mprintm_d("8.6",b);
     printf("matrix c\n");VU_mprintm_d("8.6",c);
     printf("right answer \n");VU_mprintm_d("8.4",ansm);

     vsip_msub_d(c,ansm,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("inplace b,c\n");
     vsip_matan2_d(a,b,b);
     vsip_msub_d(b,ansm,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_malldestroy_d(a);
     vsip_malldestroy_d(b);
     vsip_malldestroy_d(c);
     vsip_malldestroy_d(chk);
     vsip_malldestroy_d(ansm);
   }
   return;
}
