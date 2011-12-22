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
/* $Id: vouter_d.h,v 2.0 2003/02/22 15:23:30 judd Exp $ */
static void vouter_d(void){
   printf("********\nTEST vouter_d\n");
   {
     vsip_scalar_d alpha = 1.5;
     vsip_scalar_d data_a[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_d data_b[] = {22.1, 12.2, -13.1, -0.3};
     vsip_scalar_d ans[] = { 36.465, 20.13, -21.615, -0.495,
                               39.780, 21.96, -23.580, -0.540,
                               69.615, 38.43, -41.265, -0.945,
                               72.930, 40.26, -43.23, -0.990,
                             -102.765, -56.73, 60.915, 1.395,
                             -109.395, -60.39, 64.845, 1.485};


     vsip_block_d  *block_a = vsip_blockbind_d(data_a,6,VSIP_MEM_NONE);
     vsip_block_d  *block_b = vsip_blockbind_d(data_b,4,VSIP_MEM_NONE);
     vsip_block_d  *block_c = vsip_blockcreate_d(100,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,24,VSIP_MEM_NONE);

     vsip_vview_d  *a = vsip_vbind_d(block_a,0,1,6);
     vsip_vview_d  *b = vsip_vbind_d(block_b,0,1,4);
     vsip_mview_d  *c = vsip_mbind_d(block_c,99,-4,6,-1,4);

     vsip_mview_d  *ansm = vsip_mbind_d(ans_block,0,4,6,1,4);
     vsip_mview_d  *chk = vsip_mcreate_d(6,4,VSIP_ROW,VSIP_MEM_NONE);

     vsip_blockadmit_d(block_a,VSIP_TRUE);
     vsip_blockadmit_d(block_b,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);

     printf("vsip_vouter_d(alpha,a,b,c)\n");
     vsip_vouter_d(alpha,a,b,c);
     printf("alpha = %f \n",alpha);
     printf("vector a\n");VU_vprintm_d("8.6",a);
     printf("vector b\n");VU_vprintm_d("8.6",b);
     printf("matrix c\n");VU_mprintm_d("8.6",c);
     printf("right answer\n");VU_mprintm_d("8.4",ansm);

     vsip_msub_d(c,ansm,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_d(a);
     vsip_valldestroy_d(b);
     vsip_malldestroy_d(c);
     vsip_malldestroy_d(chk);
     vsip_malldestroy_d(ansm);
   }
   return;
}
