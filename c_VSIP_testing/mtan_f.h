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
/* $Id: mtan_f.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
static void mtan_f(void){
   printf("\n*******\nTEST mtan_f\n\n");
   { vsip_scalar_f data[] = {M_PI/8.0, M_PI/4.0, M_PI/3.0, M_PI/1.5, 1.25 * M_PI, 1.75 * M_PI};
     vsip_scalar_f ans[] = {0.4142, 1.0000, 1.7321,-1.7321,1.0000,-1.0000};
     vsip_block_f  *block = vsip_blockbind_f(data,6,VSIP_MEM_NONE);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,6,VSIP_MEM_NONE);
     vsip_mview_f  *a = vsip_mbind_f(block,0,2,3,1,2);
     vsip_mview_f  *ansm = vsip_mbind_f(ans_block,0,2,3,1,2);
     vsip_mview_f  *b = vsip_mcreate_f(3,2,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f  *chk = vsip_mcreate_f(3,2,VSIP_COL,VSIP_MEM_NONE);
     vsip_blockadmit_f(block,VSIP_TRUE);
     vsip_blockadmit_f(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_mtan_f(a,b);
     printf("mtan_f(a,b)\n matrix a\n");VU_mprintm_f("8.6",a);
     printf("matrix b\n");VU_mprintm_f("8.6",b);
     printf("expected answer to 4 decimal digits\n");VU_mprintm_f("8.4",ansm);

     vsip_msub_f(b,ansm,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check mtan_f in place\n");
     vsip_mtan_f(a,a);
     vsip_msub_f(a,ansm,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
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
