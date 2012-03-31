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
/* $Id: mexp10_f.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
#include"VU_mprintm_f.include"
static void mexp10_f(void){
   printf("\n*******\nTEST mexp10_f\n\n");
   { vsip_scalar_f data[] = {0.1, 0.2, 0.4, 0.8, 1.6, 3.2};
     vsip_scalar_f ans[] = {1.2589, 1.5849, 2.5119, 6.3096,39.8107, 1584.8932};
     vsip_block_f  *block = vsip_blockbind_f(data,6,VSIP_MEM_NONE);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,6,VSIP_MEM_NONE);
     vsip_mview_f  *a = vsip_mbind_f(block,0,2,3,1,2);
     vsip_mview_f  *ansm = vsip_mbind_f(ans_block,0,2,3,1,2);
     vsip_mview_f  *b = vsip_mcreate_f(3,2,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f  *chk = vsip_mcreate_f(3,2,VSIP_COL,VSIP_MEM_NONE);
     vsip_blockadmit_f(block,VSIP_TRUE);
     vsip_blockadmit_f(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_mexp10_f(a,b);
     printf("mexp10_f(a,b)\n matrix a\n");VU_mprintm_f("8.6",a);
     printf("matrix b\n");VU_mprintm_f("8.6",b);
     printf("expected answer to 4 decimal digits\n");VU_mprintm_f("9.4",ansm);

     vsip_msub_f(b,ansm,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.001,.001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check mexp10_f in place\n");
     vsip_mexp10_f(a,a);
     vsip_msub_f(a,ansm,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.001,.001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_malldestroy_f(a);
     vsip_malldestroy_f(b);
     vsip_malldestroy_f(chk);
     vsip_malldestroy_f(ansm);
   }
   return;
}
