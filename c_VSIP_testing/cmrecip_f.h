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
/* $Id: cmrecip_f.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
#include"VU_cmprintm_f.include"
static void cmrecip_f(void){
   printf("\n*******\nTEST cmrecip_f\n\n");
   { vsip_scalar_f data_r[] = {M_PI/8.0, M_PI/4.0, M_PI/3.0, M_PI/1.5, 1.25 * M_PI, 1.75 * M_PI};
     vsip_scalar_f data_i[] = {1,         2,        -1,      -2,         3,          4};
     vsip_scalar_f ans_r[] = {0.3402,    0.1701, 0.4995, 0.2497,  0.1608,  0.1189};
     vsip_scalar_f ans_i[] = { -0.8664, -0.4332, 0.4770, 0.2385, -0.1228, -0.0865};
     vsip_cblock_f  *block = vsip_cblockbind_f(data_r,data_i,6,VSIP_MEM_NONE);
     vsip_cblock_f  *ans_block = vsip_cblockbind_f(ans_r,ans_i,6,VSIP_MEM_NONE);
     vsip_cmview_f  *a = vsip_cmbind_f(block,0,2,3,1,2);
     vsip_cmview_f  *ansm = vsip_cmbind_f(ans_block,0,2,3,1,2);
     vsip_cmview_f  *b = vsip_cmcreate_f(3,2,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_f  *chk = vsip_cmcreate_f(3,2,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f  *chk_r = vsip_mcreate_f(3,2,VSIP_COL,VSIP_MEM_NONE);
     vsip_cblockadmit_f(block,VSIP_TRUE);
     vsip_cblockadmit_f(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_cmrecip_f(a,b);
     printf("cmrecip_f(a,b)\n matrix a\n");VU_cmprintm_f("8.6",a);
     printf("matrix b\n");VU_cmprintm_f("8.6",b);
     printf("answer\n");VU_cmprintm_f("8.4",ansm);

     vsip_cmsub_f(b,ansm,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_f(chk_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check cmrecip_f in place\n");
     vsip_cmrecip_f(a,a);
     vsip_cmsub_f(a,ansm,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_f(chk_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_cmalldestroy_f(a);
     vsip_cmalldestroy_f(b);
     vsip_mdestroy_f(chk_r);
     vsip_cmalldestroy_f(chk);
     vsip_cmalldestroy_f(ansm);
   }
   return;
}
