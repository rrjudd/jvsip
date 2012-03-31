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
/* $Id: cvouter_d.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
#include"VU_cmprintm_d.include"
#include"VU_cvprintm_d.include"
static void cvouter_d(void){
   printf("********\nTEST cvouter_d\n");
   {
     vsip_cscalar_d alpha = vsip_cmplx_d(1.5,-2.1);
     vsip_scalar_d data_a_r[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_d data_a_i[] = { -1.1, -1.2, -2.1, -2.2, 3.1, 3.3};
     vsip_scalar_d data_b_r[] = {22.1, 12.2, -13.1, -0.3};
     vsip_scalar_d data_b_i[] = {-2.1, -2.2, 3.1, 9.3};
     vsip_scalar_d ans_r[] = { -6.27, 0.66,-3.63, -36.63,
                                 -6.84, 0.72, -3.96, -39.96,
                                -11.97, 1.26, -6.93, -69.93,
                                -12.54, 1.32, -7.26, -73.26,
                                 17.67, -1.86, 10.23, 103.23,
                                 18.81, -1.98, 10.89, 109.89};
     vsip_scalar_d ans_i[] = {-88.902, -49.7640,  53.9220,   7.3260,
                                -96.984, -54.2880,  58.8240,   7.9920,
                               -169.722, -95.0040, 102.9420,  13.9860,
                               -177.804, -99.5280, 107.8440,  14.6520,
                                250.542, 140.2440,-151.9620, -20.6460,
                                266.706, 149.2920,-161.7660, -21.9780};

     vsip_cblock_d  *block_a = vsip_cblockbind_d(data_a_r,data_a_i,6,VSIP_MEM_NONE);
     vsip_cblock_d  *block_b = vsip_cblockbind_d(data_b_r,data_b_i,4,VSIP_MEM_NONE);
     vsip_cblock_d  *block_c = vsip_cblockcreate_d(100,VSIP_MEM_NONE);
     vsip_cblock_d  *ans_block = vsip_cblockbind_d(ans_r,ans_i,24,VSIP_MEM_NONE);

     vsip_cvview_d  *a = vsip_cvbind_d(block_a,0,1,6);
     vsip_cvview_d  *b = vsip_cvbind_d(block_b,0,1,4);
     vsip_cmview_d  *c = vsip_cmbind_d(block_c,99,-4,6,-1,4);

     vsip_cmview_d  *ansm = vsip_cmbind_d(ans_block,0,4,6,1,4);
     vsip_cmview_d  *chk = vsip_cmcreate_d(6,4,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d  *chk_i = vsip_mimagview_d(chk);

     vsip_cblockadmit_d(block_a,VSIP_TRUE);
     vsip_cblockadmit_d(block_b,VSIP_TRUE);
     vsip_cblockadmit_d(ans_block,VSIP_TRUE);

     printf("vsip_cvouter_d(alpha,a,b,c)\n");
     vsip_cvouter_d(alpha,a,b,c);
     printf("alpha = (%f %+fi) \n",vsip_real_d(alpha),vsip_imag_d(alpha));
     printf("vector a\n");VU_cvprintm_d("8.6",a);
     printf("vector b\n");VU_cvprintm_d("8.6",b);
     printf("matrix c\n");VU_cmprintm_d("8.6",c);
     printf("right answer\n");VU_cmprintm_d("8.4",ansm);

     vsip_cmsub_d(c,ansm,chk); vsip_cmmag_d(chk,chk_i); vsip_mclip_d(chk_i,.0001,.0001,0,1,chk_i);
     if(vsip_msumval_d(chk_i) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cvalldestroy_d(a);
     vsip_cvalldestroy_d(b);
     vsip_cmalldestroy_d(c);
     vsip_mdestroy_d(chk_i);
     vsip_cmalldestroy_d(chk);
     vsip_cmalldestroy_d(ansm);
   }
   return;
}
