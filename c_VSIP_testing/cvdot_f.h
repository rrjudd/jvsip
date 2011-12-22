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
/* $Id: cvdot_f.h,v 2.0 2003/02/22 15:23:22 judd Exp $ */
static void cvdot_f(void){
   printf("********\nTEST cvdot_f\n");
   {
     vsip_scalar_f data_a_i[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_f data_a_r[] = { 2.1, 3.2, -2.1, -2.2, +5.1, +5.3};
     vsip_scalar_f data_b_i[] = {10.1, 11.2, 22.1, 12.2, -13.1, -0.3};
     vsip_scalar_f data_b_r[] = {8.1, 10.2, -12.1, 10.2, -11.1, -2.3};
     vsip_cscalar_f ans = vsip_cmplx_f(-155.58,-24.42);
     vsip_cscalar_f val = vsip_cmplx_f(0,VSIP_MEM_NONE);

     vsip_cblock_f  *block_a = vsip_cblockbind_f(data_a_r,data_a_i,6,VSIP_MEM_NONE);
     vsip_cblock_f  *block_b = vsip_cblockbind_f(data_b_r,data_b_i,6,VSIP_MEM_NONE);
     vsip_cblock_f  *block_c = vsip_cblockcreate_f(30,VSIP_MEM_NONE);

     vsip_cvview_f  *a = vsip_cvbind_f(block_a,0,1,6);
     vsip_cvview_f  *b = vsip_cvbind_f(block_b,0,1,6);
     vsip_cvview_f  *c = vsip_cvbind_f(block_c,18,-2,6);

     vsip_cblockadmit_f(block_a,VSIP_TRUE);
     vsip_cblockadmit_f(block_b,VSIP_TRUE);

     vsip_cvcopy_f_f(a,c);
     printf("val = vsip_cvdot_f(a,b)\n");
     val = vsip_cvdot_f(c,b);
     printf("vector a\n");VU_cvprintm_f("8.6",c);
     printf("vector b\n");VU_cvprintm_f("8.6",b);
     printf("val = (%f %+fi)\n",vsip_real_f(val),vsip_imag_f(val));
     printf("right answer (%6.4f %+6.4fi)\n",vsip_real_f(ans),vsip_imag_f(ans));
     if(vsip_cmag_f(vsip_csub_f(ans,val)) > .0002)
         printf("error\n");
     else
         printf("correct\n");

     vsip_cvalldestroy_f(a);
     vsip_cvalldestroy_f(b);
     vsip_cvalldestroy_f(c);
   }
   return;
}
