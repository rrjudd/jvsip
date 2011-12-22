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
/* $Id: cvouter_covariance_d.h,v 2.1 2004/05/16 05:02:34 judd Exp $ */
static void cvouter_covariance_d(void){
   printf("********\nTEST cvouter_d\n");
   {
     vsip_cscalar_d alpha = vsip_cmplx_d(4.0,0.0);
     vsip_scalar_d data_a_r[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_d data_a_i[] = { -1.1, -2.2, -3.1, -4.2, 0.1, -2.3};
     vsip_cblock_d  *block_a = vsip_cblockbind_d(data_a_r,data_a_i,6,VSIP_MEM_NONE);
     vsip_cvview_d  *a = vsip_cvbind_d(block_a,0,1,6);

     vsip_cmview_d *ansm = vsip_cmcreate_d(6,6,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_d *chk = vsip_cmcreate_d(6,6,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_d *R = vsip_cmcreate_d(6,6,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d  *chk_i = vsip_mimagview_d(chk);

     vsip_cblockadmit_d(block_a,VSIP_TRUE);
     { /* make the answer matrix */
       vsip_index i,j;
       for(i=0; i< vsip_cvgetlength_d(a); i++){
          vsip_cscalar_d a1 = vsip_cvget_d(a,i);
          vsip_cmput_d(ansm,i,i,vsip_cmplx_d(vsip_cmagsq_d(a1),0));
          for(j=i+1; j<vsip_cvgetlength_d(a); j++){
             vsip_cscalar_d a2 = vsip_cmul_d(a1,vsip_conj_d(vsip_cvget_d(a,j)));
             vsip_cmput_d(ansm,i,j,a2);
             vsip_cmput_d(ansm,j,i,vsip_conj_d(a2));
          }
       }
       vsip_rscmmul_d(4.0,ansm,ansm);
     }
     printf("vsip_cvouter_d(alpha,a,a,R)\n");
     vsip_cvouter_d(alpha,a,a,R);
     printf("alpha = (%f %+fi) \n",vsip_real_d(alpha),vsip_imag_d(alpha));
     printf("vector a\n");VU_cvprintm_d("8.6",a);
     printf("matrix R\n");VU_cmprintm_d("8.6",R);
     printf("right answer\n");VU_cmprintm_d("8.4",ansm);

     vsip_cmsub_d(R,ansm,chk); vsip_cmmag_d(chk,chk_i); vsip_mclip_d(chk_i,.0001,.0001,0,1,chk_i);
     if(vsip_msumval_d(chk_i) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cvalldestroy_d(a);
     vsip_cmalldestroy_d(R);
     vsip_mdestroy_d(chk_i);
     vsip_cmalldestroy_d(chk);
     vsip_cmalldestroy_d(ansm);
   }
   return;
}
