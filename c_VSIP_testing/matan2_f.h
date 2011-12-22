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
/* $Id: matan2_f.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
static void matan2_f(void){
   printf("\n*******\nTEST matan2_f\n\n");
   { vsip_scalar_f data_a[] = {0,1,2,3,4,5};
     vsip_scalar_f data_b[] = {5,4,3,2,1,0};
     vsip_scalar_f ans[] = {0, 0.2450, 0.5880, 0.9828, 1.3258, 1.5708};
     vsip_block_f  *block_a = vsip_blockbind_f(data_a,6,VSIP_MEM_NONE);
     vsip_block_f  *block_b = vsip_blockbind_f(data_b,6,VSIP_MEM_NONE);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,6,VSIP_MEM_NONE);
     vsip_mview_f  *a = vsip_mbind_f(block_a,0,3,2,1,3);
     vsip_mview_f  *b = vsip_mbind_f(block_b,0,3,2,1,3);
     vsip_mview_f  *ansm = vsip_mbind_f(ans_block,0,3,2,1,3);
     vsip_mview_f  *c = vsip_mcreate_f(2,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f  *chk = vsip_mcreate_f(2,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_blockadmit_f(block_a,VSIP_TRUE);
     vsip_blockadmit_f(block_b,VSIP_TRUE);
     vsip_blockadmit_f(ans_block,VSIP_TRUE);
     printf("vsip_matan2_f(a,b,c)\n");
     vsip_matan2_f(a,b,c);
     printf("matrix a\n");VU_mprintm_f("8.6",a);
     printf("matrix b\n");VU_mprintm_f("8.6",b);
     printf("matrix c\n");VU_mprintm_f("8.6",c);
     printf("right answer \n");VU_mprintm_f("8.4",ansm);

     vsip_msub_f(c,ansm,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("inplace b,c\n");
     vsip_matan2_f(a,b,b);
     vsip_msub_f(b,ansm,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_malldestroy_f(a);
     vsip_malldestroy_f(b);
     vsip_malldestroy_f(c);
     vsip_malldestroy_f(chk);
     vsip_malldestroy_f(ansm);
   }
   return;
}
