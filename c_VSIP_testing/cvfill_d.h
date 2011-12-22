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
/* $Id: cvfill_d.h,v 2.0 2003/02/22 15:23:22 judd Exp $ */
static void cvfill_d(void){
   printf("********\nTEST cvfill_d\n");
   {
     vsip_cscalar_d alpha = vsip_cmplx_d(1.5,-2.2);
     vsip_scalar_d ans_r[] = { 1.5,1.5,1.5,1.5,1.5,1.5};
     vsip_scalar_d ans_i[] = { -2.2,-2.2,-2.2,-2.2,-2.2,-2.2};

     vsip_cblock_d  *block_c = vsip_cblockcreate_d(30,VSIP_MEM_NONE);
     vsip_cblock_d  *block_d = vsip_cblockcreate_d(30,VSIP_MEM_NONE);
     vsip_cblock_d  *ans_block = vsip_cblockbind_d(ans_r,ans_i,6,VSIP_MEM_NONE);

     vsip_cvview_d  *c = vsip_cvbind_d(block_c,18,-2,6);
     vsip_cvview_d  *d = vsip_cvbind_d(block_d,2,3,6);

     vsip_cvview_d  *ansv = vsip_cvbind_d(ans_block,0,1,6);
     vsip_cvview_d  *chk = vsip_cvcreate_d(6,VSIP_MEM_NONE);
     vsip_vview_d   *chk_r = vsip_vrealview_d(chk);

     vsip_cblockadmit_d(ans_block,VSIP_TRUE);

     printf("vsip_cvfill_d(alpha,b)\n");
     printf("\nstride -2\n");
     vsip_cvfill_d(alpha,c);
     printf(" alpha = (%f %+fi) \n",vsip_real_d(alpha), vsip_imag_d(alpha));
     printf("vector c\n");VU_cvprintm_d("8.6",c);
     printf("right answer\n");VU_cvprintm_d("8.4",ansv);

     vsip_cvsub_d(c,ansv,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\nstride 3\n");
     vsip_cvfill_d(alpha,d);
     vsip_cvsub_d(d,ansv,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cvalldestroy_d(c);
     vsip_cvalldestroy_d(d);
     vsip_vdestroy_d(chk_r);
     vsip_cvalldestroy_d(chk);
     vsip_cvalldestroy_d(ansv);
   }
   return;
}
