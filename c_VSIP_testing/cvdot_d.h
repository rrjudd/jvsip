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
/* $Id: cvdot_d.h,v 2.0 2003/02/22 15:23:22 judd Exp $ */
#include"VU_cvprintm_d.include"
static void cvdot_d(void){
   printf("********\nTEST cvdot_d\n");
   {
     vsip_scalar_d data_a_i[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_d data_a_r[] = { 2.1, 3.2, -2.1, -2.2, +5.1, +5.3};
     vsip_scalar_d data_b_i[] = {10.1, 11.2, 22.1, 12.2, -13.1, -0.3};
     vsip_scalar_d data_b_r[] = {8.1, 10.2, -12.1, 10.2, -11.1, -2.3};
     vsip_cscalar_d ans = vsip_cmplx_d(-155.58,-24.42);
     vsip_cscalar_d val = vsip_cmplx_d(0,VSIP_MEM_NONE);

     vsip_cblock_d  *block_a = vsip_cblockbind_d(data_a_r,data_a_i,6,VSIP_MEM_NONE);
     vsip_cblock_d  *block_b = vsip_cblockbind_d(data_b_r,data_b_i,6,VSIP_MEM_NONE);
     vsip_cblock_d  *block_c = vsip_cblockcreate_d(30,VSIP_MEM_NONE);

     vsip_cvview_d  *a = vsip_cvbind_d(block_a,0,1,6);
     vsip_cvview_d  *b = vsip_cvbind_d(block_b,0,1,6);
     vsip_cvview_d  *c = vsip_cvbind_d(block_c,18,-2,6);

     vsip_cblockadmit_d(block_a,VSIP_TRUE);
     vsip_cblockadmit_d(block_b,VSIP_TRUE);

     vsip_cvcopy_d_d(a,c);
     printf("val = vsip_cvdot_d(a,b)\n");
     val = vsip_cvdot_d(c,b);
     printf("vector a\n");VU_cvprintm_d("8.6",c);
     printf("vector b\n");VU_cvprintm_d("8.6",b);
     printf("val = (%f %+fi)\n",vsip_real_d(val),vsip_imag_d(val));
     printf("right answer (%6.4f %+6.4fi)\n",vsip_real_d(ans),vsip_imag_d(ans));
     if(vsip_cmag_d(vsip_csub_d(ans,val)) > .0002)
         printf("error\n");
     else
         printf("correct\n");

     vsip_cvalldestroy_d(a);
     vsip_cvalldestroy_d(b);
     vsip_cvalldestroy_d(c);
   }
   return;
}
