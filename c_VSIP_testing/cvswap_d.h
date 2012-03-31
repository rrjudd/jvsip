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
/* $Id: cvswap_d.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
#include"VU_cvprintm_d.include"
static void cvswap_d(void){
   printf("********\nTEST cvswap_d\n");
   {
     vsip_scalar_d data1_r[] = {-1,  1, 0,  2, -2 };
     vsip_scalar_d data1_i[] = {-.1,  .1, .0,  .2, -.2 };
     vsip_scalar_d data2_r[]  = { 2, -6, 1, 0,  2};
     vsip_scalar_d data2_i[]  = { .2, .5, 0, -.2,  .2};
     vsip_cblock_d  *block1 = vsip_cblockbind_d(data1_r,data1_i,5,VSIP_MEM_NONE);
     vsip_cblock_d  *block2 = vsip_cblockbind_d(data2_r,data2_i,5,VSIP_MEM_NONE);
     vsip_cvview_d  *a = vsip_cvbind_d(block1,0,1,5);
     vsip_cvview_d  *b = vsip_cvbind_d(block2,0,1,5);
     vsip_cvview_d  *a1 = vsip_cvcreate_d(15,VSIP_MEM_NONE);
     vsip_cvview_d  *b1 = vsip_cvcreate_d(45,VSIP_MEM_NONE);
     vsip_cvview_d  *chk = vsip_cvcreate_d(5,VSIP_MEM_NONE);
     vsip_vview_d  *chk_r = vsip_vrealview_d(chk);
     vsip_cvputlength_d(a1,5); vsip_cvputstride_d(a1,2);
     vsip_cvputlength_d(b1,5); vsip_cvputoffset_d(b1,31);vsip_cvputstride_d(b1,-3);
     vsip_cblockadmit_d(block1,VSIP_TRUE);
     vsip_cblockadmit_d(block2,VSIP_TRUE);
     vsip_cvcopy_d_d(a,a1); vsip_cvcopy_d_d(b,b1);
     vsip_cvswap_d(a1,b1);
     printf("vector a\n");VU_cvprintm_d("8.6",a);
     printf("vector b\n");VU_cvprintm_d("8.6",b);
     printf("vsip_cvswap_d(a,b)\n vector a\n");VU_cvprintm_d("8.6",a);
     printf("vector b\n");VU_cvprintm_d("8.6",b);

     vsip_cvsub_d(a,b1,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("<a> in error\n");
     else 
         printf("<a> correct\n");

     vsip_cvsub_d(b,a1,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf("<b> in error\n");
     else 
         printf("<b> correct\n");

     vsip_cvalldestroy_d(a);
     vsip_cvalldestroy_d(b);
     vsip_cvalldestroy_d(a1);
     vsip_cvalldestroy_d(b1);
     vsip_vdestroy_d(chk_r);
     vsip_cvalldestroy_d(chk);
   }
   return;
}
