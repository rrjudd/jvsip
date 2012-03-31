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
/* $Id: mtanh_d.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
#include"VU_mprintm_d.include"
static void mtanh_d(void){
   printf("\n*******\nTEST mtanh_d\n\n");
   { vsip_scalar_d data[] = {0, .1, .2, .4, .8, 1.6};
     vsip_scalar_d ans[] = {0, .0997, .1974, .3799,.6640,.9217};
     vsip_block_d  *block = vsip_blockbind_d(data,6,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,6,VSIP_MEM_NONE);
     vsip_mview_d  *a = vsip_mbind_d(block,0,1,2,2,3);
     vsip_mview_d  *ansv = vsip_mbind_d(ans_block,0,1,2,2,3);
     vsip_mview_d  *b = vsip_mcreate_d(2,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d  *chk = vsip_mcreate_d(2,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_blockadmit_d(block,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);
     printf("vsip_mtanh_d(a,b)\n");
     vsip_mtanh_d(a,b);
     printf("matrix a\n");VU_mprintm_d("8.6",a);
     printf("matrix b\n");VU_mprintm_d("8.6",b);
     printf("right answer \n");VU_mprintm_d("8.4",ansv);

     vsip_msub_d(b,ansv,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("inplace\n");
     vsip_mtanh_d(a,a);
     vsip_msub_d(a,ansv,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_malldestroy_d(a);
     vsip_malldestroy_d(b);
     vsip_malldestroy_d(chk);
     vsip_malldestroy_d(ansv);
   }
   return;
}
