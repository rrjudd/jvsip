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
/* $Id: cvsam_d.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
static void cvsam_d(void){
   printf("********\nTEST cvsam_d\n");
   {
     vsip_scalar_d data_a_i[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_d data_a_r[] = { 2.1, 3.2, -2.1, -2.2, +5.1, +5.3};
     vsip_cscalar_d beta = vsip_cmplx_d(1.5,-.5);
     vsip_scalar_d data_c_i[] = {-0.5, 16.2, -2.3, 1.5, -3.0, -0.3};
     vsip_scalar_d data_c_r[] = {7.1, 8.2, -2.1, 8.2, -1.1, -3.3};
     vsip_scalar_d ans_r[] = {25.86, 27.20, 4.94, -8.29, -18.06, -23.58};
     vsip_scalar_d ans_i[] = { 2.46, 81.88, -1.98, 12.89, -15.84, 10.50 };
     vsip_cblock_d  *block_a = vsip_cblockbind_d(data_a_r,data_a_i,6,VSIP_MEM_NONE);
     vsip_cblock_d  *block_c = vsip_cblockbind_d(data_c_r,data_c_i,6,VSIP_MEM_NONE);
     vsip_cblock_d  *block_d = vsip_cblockcreate_d(30,VSIP_MEM_NONE);
     vsip_cblock_d  *ans_block = vsip_cblockbind_d(ans_r,ans_i,6,VSIP_MEM_NONE);

     vsip_cvview_d  *a = vsip_cvbind_d(block_a,0,1,6);
     vsip_cvview_d  *c = vsip_cvbind_d(block_c,0,1,6);
     vsip_cvview_d  *d = vsip_cvbind_d(block_d,2,3,6);

     vsip_cvview_d  *ansv = vsip_cvbind_d(ans_block,0,1,6);
     vsip_cvview_d  *chk = vsip_cvcreate_d(6,VSIP_MEM_NONE);
     vsip_vview_d  *chk_r = vsip_vrealview_d(chk);

     vsip_cblockadmit_d(block_a,VSIP_TRUE);
     vsip_cblockadmit_d(block_c,VSIP_TRUE);
     vsip_cblockadmit_d(ans_block,VSIP_TRUE);

     printf("vsip_cvsam_d(a,beta,c,d)\n");
     vsip_cvsam_d(a,beta,c,d);
     printf("vector a\n");VU_cvprintm_d("8.6",a);
     printf("beta = (%f %+fi)\n",vsip_real_d(beta),vsip_imag_d(beta));
     printf("vector c\n");VU_cvprintm_d("8.6",c);
     printf("vector d\n");VU_cvprintm_d("8.6",d);
     printf("right answer\n");VU_cvprintm_d("8.4",ansv);

     vsip_cvsub_d(d,ansv,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,d in place\n");
     vsip_cvcopy_d_d(a,d);
     vsip_cvsam_d(d,beta,c,d);
     vsip_cvsub_d(d,ansv,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\nc,d in place\n");
     vsip_cvcopy_d_d(c,d);
     vsip_cvsam_d(a,beta,d,d);
     vsip_cvsub_d(d,ansv,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cvalldestroy_d(a);
     vsip_cvalldestroy_d(c);
     vsip_cvalldestroy_d(d);
     vsip_vdestroy_d(chk_r);
     vsip_cvalldestroy_d(chk);
     vsip_cvalldestroy_d(ansv);
   }
   return;
}
