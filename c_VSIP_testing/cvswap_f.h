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
/* $Id: cvswap_f.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
static void cvswap_f(void){
   printf("********\nTEST cvswap_f\n");
   {
     vsip_scalar_f data1_r[] = {-1,  1, 0,  2, -2 };
     vsip_scalar_f data1_i[] = {-.1,  .1, .0,  .2, -.2 };
     vsip_scalar_f data2_r[]  = { 2, -6, 1, 0,  2};
     vsip_scalar_f data2_i[]  = { .2, .5, 0, -.2,  .2};
     vsip_cblock_f  *block1 = vsip_cblockbind_f(data1_r,data1_i,5,VSIP_MEM_NONE);
     vsip_cblock_f  *block2 = vsip_cblockbind_f(data2_r,data2_i,5,VSIP_MEM_NONE);
     vsip_cvview_f  *a = vsip_cvbind_f(block1,0,1,5);
     vsip_cvview_f  *b = vsip_cvbind_f(block2,0,1,5);
     vsip_cvview_f  *a1 = vsip_cvcreate_f(15,VSIP_MEM_NONE);
     vsip_cvview_f  *b1 = vsip_cvcreate_f(45,VSIP_MEM_NONE);
     vsip_cvview_f  *chk = vsip_cvcreate_f(5,VSIP_MEM_NONE);
     vsip_vview_f  *chk_r = vsip_vrealview_f(chk);
     vsip_cvputlength_f(a1,5); vsip_cvputstride_f(a1,2);
     vsip_cvputlength_f(b1,5); vsip_cvputoffset_f(b1,31);vsip_cvputstride_f(b1,-3);
     vsip_cblockadmit_f(block1,VSIP_TRUE);
     vsip_cblockadmit_f(block2,VSIP_TRUE);
     vsip_cvcopy_f_f(a,a1); vsip_cvcopy_f_f(b,b1);
     vsip_cvswap_f(a1,b1);
     printf("vector a\n");VU_cvprintm_f("8.6",a);
     printf("vector b\n");VU_cvprintm_f("8.6",b);
     printf("vsip_cvswap_f(a,b)\n vector a\n");VU_cvprintm_f("8.6",a);
     printf("vector b\n");VU_cvprintm_f("8.6",b);

     vsip_cvsub_f(a,b1,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf("<a> in error\n");
     else 
         printf("<a> correct\n");

     vsip_cvsub_f(b,a1,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf("<b> in error\n");
     else 
         printf("<b> correct\n");

     vsip_cvalldestroy_f(a);
     vsip_cvalldestroy_f(b);
     vsip_cvalldestroy_f(a1);
     vsip_cvalldestroy_f(b1);
     vsip_vdestroy_f(chk_r);
     vsip_cvalldestroy_f(chk);
   }
   return;
}
