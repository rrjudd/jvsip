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
/* $Id: vkron_f.h,v 2.0 2003/02/22 15:23:29 judd Exp $ */
#include"VU_mprintm_f.include"
#include"VU_vprintm_f.include"
static void vkron_f(void){
   printf("********\nTEST vkron_f\n");
   {
     vsip_scalar_f alpha = 1.5;
     vsip_scalar_f data_a[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_f data_b[] = {22.1, 12.2, -13.1, -0.3};
     vsip_scalar_f ans[] = { 36.465, 20.13, -21.615, -0.495,
                               39.780, 21.96, -23.580, -0.540,
                               69.615, 38.43, -41.265, -0.945,
                               72.930, 40.26, -43.23, -0.990,
                             -102.765, -56.73, 60.915, 1.395,
                             -109.395, -60.39, 64.845, 1.485};

     vsip_block_f  *block_a = vsip_blockbind_f(data_a,6,VSIP_MEM_NONE);
     vsip_block_f  *block_b = vsip_blockbind_f(data_b,4,VSIP_MEM_NONE);
     vsip_block_f  *block_c = vsip_blockcreate_f(100,VSIP_MEM_NONE);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,24,VSIP_MEM_NONE);

     vsip_vview_f  *a = vsip_vbind_f(block_a,0,1,6);
     vsip_vview_f  *b = vsip_vbind_f(block_b,0,1,4);
     vsip_mview_f  *c = vsip_mbind_f(block_c,99,-1,4,-4,6);

     vsip_mview_f  *ansm = vsip_mbind_f(ans_block,0,1,4,4,6);
     vsip_mview_f  *chk = vsip_mcreate_f(4,6,VSIP_ROW,VSIP_MEM_NONE);

     vsip_blockadmit_f(block_a,VSIP_TRUE);
     vsip_blockadmit_f(block_b,VSIP_TRUE);
     vsip_blockadmit_f(ans_block,VSIP_TRUE);

     printf("vsip_vkron_f(alpha,a,b,c)\n");
     vsip_vkron_f(alpha,a,b,c);
     printf("alpha = %f \n",alpha);
     printf("vector a\n");VU_vprintm_f("8.6",a);
     printf("vector b\n");VU_vprintm_f("8.6",b);
     printf("matrix c\n");VU_mprintm_f("8.6",c);
     printf("right answer\n");VU_mprintm_f("8.4",ansm);

     vsip_msub_f(c,ansm,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_f(a);
     vsip_valldestroy_f(b);
     vsip_malldestroy_f(c);
     vsip_malldestroy_f(chk);
     vsip_malldestroy_f(ansm);
   }
   return;
}
