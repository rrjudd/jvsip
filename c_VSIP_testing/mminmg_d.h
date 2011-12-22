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
/* $Id: mminmg_d.h,v 2.0 2003/02/22 15:23:25 judd Exp $ */
static void mminmg_d(void){
   printf("\n*******\nTEST mminmg_d\n\n");
   { vsip_scalar_d data1[]  = {-1, 2, 0, -5, -6,  3.4, -3.4, 5.6, -.3};
     vsip_scalar_d data2[] = {-2, 1, 0, -3, -7, -3.4, -3.5, 5.6, -.2};
     vsip_scalar_d ans[]  =  { 1, 1, 0,  3,  6,  3.4,  3.4, 5.6,  .2};
     vsip_block_d  *block1 = vsip_blockbind_d(data1,9,VSIP_MEM_NONE);
     vsip_block_d  *block2 = vsip_blockbind_d(data2,9,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,9,VSIP_MEM_NONE);
     vsip_mview_d  *a = vsip_mbind_d(block1,0,3,3,1,3);
     vsip_mview_d  *b = vsip_mbind_d(block2,0,3,3,1,3);
     vsip_mview_d  *ansm = vsip_mbind_d(ans_block,0,3,3,1,3);
     vsip_mview_d  *c = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d  *chk = vsip_mcreate_d(3,3,VSIP_COL,VSIP_MEM_NONE);
     vsip_blockadmit_d(block1,VSIP_TRUE);
     vsip_blockadmit_d(block2,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_mminmg_d(a,b,c);
     printf("vsip_mminmg_d(a,b,c)\n matrix a\n");VU_mprintm_d("8.6",a);
     printf("matrix b\n");VU_mprintm_d("8.6",b);
     printf("matrix c\n");VU_mprintm_d("8.6",c);
     printf("expected answer to 4 decimal digits\n");VU_mprintm_d("8.4",ansm);

     vsip_msub_d(c,ansm,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check mminmg_d b,c inplace\n");
     vsip_mminmg_d(a,b,b);
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
