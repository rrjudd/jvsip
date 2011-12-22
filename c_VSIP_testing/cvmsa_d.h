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
/* $Id: cvmsa_d.h,v 2.1 2007/04/18 17:05:54 judd Exp $ */
static void cvmsa_d(void){
   printf("********\nTEST cvmsa_d\n");
   {
     vsip_scalar_d data_a_i[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_d data_a_r[] = { 2.1, 3.2, -2.1, -2.2, +5.1, +5.3};
     vsip_scalar_d data_b_i[] = {10.1, 11.2, 22.1, 12.2, -13.1, -0.3};
     vsip_scalar_d data_b_r[] = {8.1, 10.2, -12.1, 10.2, -11.1, -2.3};
     vsip_cscalar_d gama = vsip_cmplx_d(-.5,1.25);
     vsip_scalar_d ans_r[] = { 5.40, 18.70, -21.50, -49.78, -97.72, -13.68};
     vsip_scalar_d ans_i[] = { 31.37, 49.33, -70.57, -3.15, -31.15, 7.25 };
     vsip_cblock_d  *block_a = vsip_cblockbind_d(data_a_r,data_a_i,6,VSIP_MEM_NONE);
     vsip_cblock_d  *block_b = vsip_cblockbind_d(data_b_r,data_b_i,6,VSIP_MEM_NONE);
     vsip_cblock_d  *block_d = vsip_cblockcreate_d(30,VSIP_MEM_NONE);
     vsip_cblock_d  *ans_block = vsip_cblockbind_d(ans_r,ans_i,6,VSIP_MEM_NONE);

     vsip_cvview_d  *a = vsip_cvbind_d(block_a,0,1,6);
     vsip_cvview_d  *b = vsip_cvbind_d(block_b,0,1,6);
     vsip_cvview_d  *d = vsip_cvbind_d(block_d,2,3,6);

     vsip_cvview_d  *ansv = vsip_cvbind_d(ans_block,0,1,6);
     vsip_cvview_d  *chk = vsip_cvcreate_d(6,VSIP_MEM_NONE);
     vsip_vview_d  *chk_r = vsip_vrealview_d(chk);

     vsip_cblockadmit_d(block_a,VSIP_TRUE);
     vsip_cblockadmit_d(block_b,VSIP_TRUE);
     vsip_cblockadmit_d(ans_block,VSIP_TRUE);

     printf("vsip_cvmsa_d(a,b,gama,d)\n");
     vsip_cvmsa_d(a,b,gama,d);
     printf("vector a\n");VU_cvprintm_d("8.6",a);
     printf("vector b\n");VU_cvprintm_d("8.6",b);
     printf("gama = (%f %+fi)\n",vsip_real_d(gama),vsip_imag_d(gama));
     printf("vector d\n");VU_cvprintm_d("8.6",d);
     printf("right answer\n");VU_cvprintm_d("8.4",ansv);

     vsip_cvsub_d(d,ansv,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,d in place\n");
     vsip_cvcopy_d_d(a,d);
     vsip_cvmsa_d(d,b,gama,d);
     vsip_cvsub_d(d,ansv,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\nb,d in place\n");
     vsip_cvcopy_d_d(b,d);
     vsip_cvmsa_d(a,d,gama,d);
     vsip_cvsub_d(d,ansv,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cvalldestroy_d(a);
     vsip_cvalldestroy_d(b);
     vsip_cvalldestroy_d(d);
     vsip_vdestroy_d(chk_r);
     vsip_cvalldestroy_d(chk);
     vsip_cvalldestroy_d(ansv);
   }
   return;
}
