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
/* $Id: rcvsub_f.h,v 2.0 2003/02/22 15:23:27 judd Exp $ */
static void rcvsub_f(void){
   printf("********\nTEST rcvsub_f\n");
   {
     vsip_scalar_f data_a[]   = { 1.1,  1.2,    2.1,  2.2,  -3.1, -3.3};
     vsip_scalar_f data_b_r[] = { 8.1, 10.2,  -12.1, 10.2, -11.1, -2.3};
     vsip_scalar_f data_b_i[] = {10.1, 11.2,   22.1, 12.2, -13.1, -0.3};
     vsip_scalar_f ans_r[]    = { -7.0,  -9.0,  14.2,  -8.0,  8.0, -1.0};
     vsip_scalar_f ans_i[]    = {-10.1, -11.2, -22.1, -12.2, 13.1,  0.3 };

     vsip_block_f   *block_a = vsip_blockbind_f(data_a,6,VSIP_MEM_NONE);
     vsip_cblock_f  *block_b = vsip_cblockbind_f(data_b_r,data_b_i,6,VSIP_MEM_NONE);
     vsip_cblock_f  *block_c = vsip_cblockcreate_f(30,VSIP_MEM_NONE);
     vsip_cblock_f  *block_d = vsip_cblockcreate_f(30,VSIP_MEM_NONE);
     vsip_cblock_f  *ans_block = vsip_cblockbind_f(ans_r,ans_i,6,VSIP_MEM_NONE);

     vsip_vview_f  *a = vsip_vbind_f(block_a,0,1,6);
     vsip_cvview_f  *b = vsip_cvbind_f(block_b,0,1,6);
     vsip_cvview_f  *c = vsip_cvbind_f(block_c,18,-2,6);
     vsip_cvview_f  *d = vsip_cvbind_f(block_d,2,3,6);

     vsip_cvview_f  *ansv = vsip_cvbind_f(ans_block,0,1,6);
     vsip_cvview_f  *chk = vsip_cvcreate_f(6,VSIP_MEM_NONE);
     vsip_vview_f   *chk_r = vsip_vrealview_f(chk);

     vsip_blockadmit_f(block_a,VSIP_TRUE);
     vsip_cblockadmit_f(block_b,VSIP_TRUE);
     vsip_cblockadmit_f(ans_block,VSIP_TRUE);

     printf("vsip_rcvsub_f(a,b,c)\n");
     vsip_rcvsub_f(a,b,c);
     printf("vector a\n");VU_vprintm_f("8.6",a);
     printf("vector b\n");VU_cvprintm_f("8.6",b);
     printf("vector c\n");VU_cvprintm_f("8.6",c);
     printf("right answer\n");VU_cvprintm_f("8.4",ansv);

     vsip_cvsub_f(c,ansv,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,c in place, <a> real view of <c>\n");
     { vsip_vview_f *a_r = vsip_vrealview_f(d);
       vsip_vcopy_f_f(a,a_r);
       vsip_rcvsub_f(a_r,b,d);
       vsip_vdestroy_f(a_r);
     }
     vsip_cvsub_f(d,ansv,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_f(a);
     vsip_cvalldestroy_f(b);
     vsip_cvalldestroy_f(c);
     vsip_cvalldestroy_f(d);
     vsip_vdestroy_f(chk_r);
     vsip_cvalldestroy_f(chk);
     vsip_cvalldestroy_f(ansv);
   }
   return;
}
