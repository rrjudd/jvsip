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
/* $Id: cvneg_f.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
#include"VU_cvprintm_f.include"
static void cvneg_f(void){
   printf("********\nTEST cvneg_f\n");
   {
     vsip_scalar_f data_r[] = {-1,  1, 0,  2, -2 };
     vsip_scalar_f data_i[] = {-.1,  .1, .0,  .2, -.2 };
     vsip_scalar_f ans_r[]  = { 1, -1, 0, -2,  2};
     vsip_scalar_f ans_i[]  = { .1, -.1, 0, -.2,  .2};
     vsip_cblock_f  *block = vsip_cblockbind_f(data_r,data_i,5,VSIP_MEM_NONE);
     vsip_cblock_f  *ans_block = vsip_cblockbind_f(ans_r,ans_i,5,VSIP_MEM_NONE);
     vsip_cvview_f  *a = vsip_cvbind_f(block,0,1,5);
     vsip_cvview_f  *ansv = vsip_cvbind_f(ans_block,0,1,5);
     vsip_cvview_f  *b = vsip_cvcreate_f(15,VSIP_MEM_NONE);
     vsip_cvview_f  *chk = vsip_cvcreate_f(5,VSIP_MEM_NONE);
     vsip_vview_f  *chk_r = vsip_vrealview_f(chk);
     vsip_cvputlength_f(b,5);
     vsip_cblockadmit_f(block,VSIP_TRUE);
     vsip_cblockadmit_f(ans_block,VSIP_TRUE);
     vsip_cvneg_f(a,b);
     printf("vsip_cvneg_f(a,b)\n vector a\n");VU_cvprintm_f("8.6",a);
     printf("vector b\n");VU_cvprintm_f("8.6",b);
     printf("expected answer to 4 decimal digits\n");VU_cvprintm_f("8.4",ansv);

     vsip_cvsub_f(b,ansv,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,b in place\n");
     vsip_cvputstride_f(b,2);vsip_cvcopy_f_f(a,b);
     vsip_cvneg_f(a,a);
     vsip_cvsub_f(a,ansv,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\n");
     /* check with a stride 1, b stride 2 */
     printf("vsip_cvneg(a,b) with <a> stride 2, <b> stride 1\n");
     vsip_cvneg_f(b,a);
     vsip_cvsub_f(a,ansv,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf("error\n");
     else {
         printf("correct\n");
     }
     vsip_cvalldestroy_f(a);
     vsip_cvalldestroy_f(b);
     vsip_vdestroy_f(chk_r);
     vsip_cvalldestroy_f(chk);
     vsip_cvalldestroy_f(ansv);
   }
   return;
}
