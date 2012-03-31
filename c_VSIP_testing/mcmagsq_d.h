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
/* $Id: mcmagsq_d.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
#include"VU_cmprintm_d.include"
#include"VU_mprintm_d.include"
static void mcmagsq_d(void){
   printf("\n*******\nTEST mcmagsq_d\n\n");
   { vsip_scalar_d data_r[] = {M_PI/8.0,  M_PI/4.0,  M_PI/3.0,  M_PI/1.5,  1.25 * M_PI,  1.75 * M_PI};
     vsip_scalar_d data_i[] = { 1,        2,         -3,        -4,         5,           6};
     vsip_scalar_d ans[] = {1.1542, 4.6169, 10.0966, 20.3865, 40.4213, 66.2257};
     vsip_cblock_d  *block = vsip_cblockbind_d(data_r,data_i,6,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,6,VSIP_MEM_NONE);
     vsip_cmview_d  *a = vsip_cmbind_d(block,0,2,3,1,2);
     vsip_mview_d  *ansm = vsip_mbind_d(ans_block,0,2,3,1,2);
     vsip_mview_d  *b = vsip_mcreate_d(3,2,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d  *chk = vsip_mcreate_d(3,2,VSIP_COL,VSIP_MEM_NONE);
     vsip_cblockadmit_d(block,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_mcmagsq_d(a,b);
     printf("vsip_mcmagsq_d(a,b)\n matrix a\n");VU_cmprintm_d("8.6",a);
     printf("matrix b\n");VU_mprintm_d("8.6",b);
     printf("answer\n");VU_mprintm_d("8.4",ansm);

     vsip_msub_d(b,ansm,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_cmalldestroy_d(a);
     vsip_malldestroy_d(b);
     vsip_malldestroy_d(chk);
     vsip_malldestroy_d(ansm);
   }
   return;
}
