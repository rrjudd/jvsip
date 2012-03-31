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
/* $Id: cvkron_f.h,v 2.1 2009/09/05 18:01:45 judd Exp $ */
#include"VU_cmprintm_f.include"
#include"VU_cvprintm_f.include"
static void cvkron_f(void){
   printf("********\nTEST cvkron_f\n");
   {
     vsip_cscalar_f alpha = vsip_cmplx_f(-3,2);
     vsip_scalar_f data_a_r[] = { 1,  1};
     vsip_scalar_f data_a_i[] = { 1, -1};
     vsip_scalar_f data_b_r[] = {3, 5, 2};
     vsip_scalar_f data_b_i[] = {1, 1, 2};
     vsip_scalar_f ans_r[] = { -14.0,  -8.0,
                               -24.0, -10.0,
                                -8.0, -12.0};
     vsip_scalar_f ans_i[] = { -8.0,  14.0,
                              -10.0,  24.0,
                              -12.0,   8.0};


     vsip_cblock_f  *block_a = vsip_cblockbind_f(data_a_r,data_a_i,2,VSIP_MEM_NONE);
     vsip_cblock_f  *block_b = vsip_cblockbind_f(data_b_r,data_b_i,3,VSIP_MEM_NONE);
     vsip_cblock_f  *block_c = vsip_cblockcreate_f(100,VSIP_MEM_NONE);
     vsip_cblock_f  *ans_block = vsip_cblockbind_f(ans_r,ans_i,6,VSIP_MEM_NONE);

     vsip_cvview_f  *a = vsip_cvbind_f(block_a,0,1,2);
     vsip_cvview_f  *b = vsip_cvbind_f(block_b,0,1,3);
     vsip_cmview_f  *c = vsip_cmbind_f(block_c,99,-1,3,-4,2);

     vsip_cmview_f  *ansm = vsip_cmbind_f(ans_block,0,2,3,1,2);
     vsip_cmview_f  *chk = vsip_cmcreate_f(3,2,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f  *chk_r = vsip_mrealview_f(chk);

     vsip_cblockadmit_f(block_a,VSIP_TRUE);
     vsip_cblockadmit_f(block_b,VSIP_TRUE);
     vsip_cblockadmit_f(ans_block,VSIP_TRUE);

     printf("vsip_cvkron_f(alpha,a,b,c)\n");
     vsip_cvkron_f(alpha,a,b,c);
     printf("alpha = %f %+fi\n",(double)alpha.r,(double)alpha.i);
     printf("vector a\n");VU_cvprintm_f("8.6",a);
     printf("vector b\n");VU_cvprintm_f("8.6",b);
     printf("matrix c\n");VU_cmprintm_f("8.6",c);
     printf("right answer\n");VU_cmprintm_f("8.4",ansm);

     vsip_cmsub_f(c,ansm,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_f(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cvalldestroy_f(a);
     vsip_cvalldestroy_f(b);
     vsip_cmalldestroy_f(c);
     vsip_mdestroy_f(chk_r);
     vsip_cmalldestroy_f(chk);
     vsip_cmalldestroy_f(ansm);
   }
   return;
}
