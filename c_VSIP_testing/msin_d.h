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
/* $Id: msin_d.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
static void msin_d(void){
   printf("\n*******\nTEST msin_d\n\n");
   { vsip_scalar_d data[] = {0, M_PI/4.0, M_PI/2.0, M_PI, 1.25 * M_PI, 1.5 * M_PI};
     vsip_scalar_d ans[] = {0.0000, 0.7071, 1.0000, 0.0000,-0.7071, -1.0000};
     vsip_block_d  *block = vsip_blockbind_d(data,6,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,6,VSIP_MEM_NONE);
     vsip_mview_d  *a = vsip_mbind_d(block,0,2,3,1,2);
     vsip_mview_d  *ansm = vsip_mbind_d(ans_block,0,2,3,1,2);
     vsip_mview_d  *b = vsip_mcreate_d(3,2,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d  *chk = vsip_mcreate_d(3,2,VSIP_COL,VSIP_MEM_NONE);
     vsip_blockadmit_d(block,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_msin_d(a,b);
     printf("msin_d(a,b)\n matrix a\n");VU_mprintm_d("8.6",a);
     printf("matrix b\n");VU_mprintm_d("8.6",b);
     printf("expected answer to 4 decimal digits\n");VU_mprintm_d("8.4",ansm);

     vsip_msub_d(b,ansm,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check msin_d in place\n");
     vsip_msin_d(a,a);
     vsip_msub_d(a,ansm,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_malldestroy_d(a);
     vsip_malldestroy_d(b);
     vsip_malldestroy_d(chk);
     vsip_malldestroy_d(ansm);
   }
   return;
}
