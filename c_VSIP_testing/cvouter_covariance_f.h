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
/* $Id: cvouter_covariance_f.h,v 2.1 2004/05/16 05:02:35 judd Exp $ */
#include"VU_cmprintm_f.include"
#include"VU_cvprintm_f.include"
static void cvouter_covariance_f(void){
   printf("********\nTEST cvouter_f\n");
   {
     vsip_cscalar_f alpha = vsip_cmplx_f(4.0,0.0);
     vsip_scalar_f data_a_r[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_f data_a_i[] = { -1.1, -2.2, -3.1, -4.2, 0.1, -2.3};
     vsip_cblock_f  *block_a = vsip_cblockbind_f(data_a_r,data_a_i,6,VSIP_MEM_NONE);
     vsip_cvview_f  *a = vsip_cvbind_f(block_a,0,1,6);

     vsip_cmview_f *ansm = vsip_cmcreate_f(6,6,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_f *chk = vsip_cmcreate_f(6,6,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_f *R = vsip_cmcreate_f(6,6,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f  *chk_i = vsip_mimagview_f(chk);

     vsip_cblockadmit_f(block_a,VSIP_TRUE);
     { /* make the answer matrix */
       vsip_index i,j;
       for(i=0; i< vsip_cvgetlength_f(a); i++){
          vsip_cscalar_f a1 = vsip_cvget_f(a,i);
          vsip_cmput_f(ansm,i,i,vsip_cmplx_f(vsip_cmagsq_f(a1),0));
          for(j=i+1; j<vsip_cvgetlength_f(a); j++){
             vsip_cscalar_f a2 = vsip_cmul_f(a1,vsip_conj_f(vsip_cvget_f(a,j)));
             vsip_cmput_f(ansm,i,j,a2);
             vsip_cmput_f(ansm,j,i,vsip_conj_f(a2));
          }
       }
       vsip_rscmmul_f(4.0,ansm,ansm);
     }
     printf("vsip_cvouter_f(alpha,a,a,R)\n");
     vsip_cvouter_f(alpha,a,a,R);
     printf("alpha = (%f %+fi) \n",vsip_real_f(alpha),vsip_imag_f(alpha));
     printf("vector a\n");VU_cvprintm_f("8.6",a);
     printf("matrix R\n");VU_cmprintm_f("8.6",R);
     printf("right answer\n");VU_cmprintm_f("8.4",ansm);

     vsip_cmsub_f(R,ansm,chk); vsip_cmmag_f(chk,chk_i); vsip_mclip_f(chk_i,.0001,.0001,0,1,chk_i);
     if(vsip_msumval_f(chk_i) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cvalldestroy_f(a);
     vsip_cmalldestroy_f(R);
     vsip_mdestroy_f(chk_i);
     vsip_cmalldestroy_f(chk);
     vsip_cmalldestroy_f(ansm);
   }
   return;
}
