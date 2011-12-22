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
/* $Id: vrect_f.h,v 2.0 2003/02/22 15:23:30 judd Exp $ */
static void vrect_f(void){
   printf("********\nTEST vrect_f\n");
   {
     vsip_scalar_f ans_r[] = { 2.1, 3.2, -2.1, -2.2, +5.1, +5.3};
     vsip_scalar_f ans_i[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     /* expected angle (argument) */
     vsip_scalar_f data_a[] = { .4825133, 0.3587707 , 2.3561945, 2.3561945, -.5461666, -0.5569015};
     /* expected magnitude (radius) */
     vsip_scalar_f data_r[] = { 2.3706539, 3.4176015, 2.9698485, 3.1112698, 5.9682493, 6.2433965};
     vsip_block_f *block_a = vsip_blockbind_f(data_a,6,VSIP_MEM_NONE); 
     vsip_block_f *block_r = vsip_blockbind_f(data_r,6,VSIP_MEM_NONE); 
     vsip_block_f  *block_arg = vsip_blockcreate_f(50,VSIP_MEM_NONE);
     vsip_block_f  *block_mag = vsip_blockcreate_f(30,VSIP_MEM_NONE);
     vsip_cblock_f  *ans_block = vsip_cblockbind_f(ans_r,ans_i,6,VSIP_MEM_NONE);
     vsip_cvview_f  *a2 = vsip_cvcreate_f(6,VSIP_MEM_NONE);
     vsip_vview_f   *a2_r = vsip_vrealview_f(a2);
     vsip_vview_f   *a2_i = vsip_vimagview_f(a2);

     vsip_vview_f  *a = vsip_vbind_f(block_a,0,1,6);
     vsip_vview_f  *r = vsip_vbind_f(block_r,0,1,6);
     vsip_vview_f  *arg = vsip_vbind_f(block_arg,5,3,6);
     vsip_vview_f  *mag = vsip_vbind_f(block_mag,18,-2,6);

     vsip_cvview_f  *ans = vsip_cvbind_f(ans_block,0,1,6);
     vsip_cvview_f  *chk = vsip_cvcreate_f(6,VSIP_MEM_NONE);
     vsip_vview_f  *chk_r = vsip_vrealview_f(chk);

     vsip_blockadmit_f(block_a,VSIP_TRUE);
     vsip_blockadmit_f(block_r,VSIP_TRUE);
     vsip_cblockadmit_f(ans_block,VSIP_TRUE);

     vsip_vcopy_f_f(a,arg);
     vsip_vcopy_f_f(r,mag);

     printf("vsip_vrect_f(r,phi,y)\n");
     vsip_vrect_f(mag,arg,a2);
     printf("vector r\n");VU_vprintm_f("8.6",r);
     printf("vector phi\n");VU_vprintm_f("8.6",a);
     printf("vector y\n");VU_cvprintm_f("8.6",a2);
     printf("right answer\n");VU_cvprintm_f("6.4",ans);

     vsip_cvsub_f(a2,ans,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf(" error\n");
     else 
         printf("correct\n");

     vsip_vcopy_f_f(a,a2_i);
     vsip_vcopy_f_f(r,a2_r);
     printf("\nin place arg imag view of |a>, mag real view of |a>\n");
     vsip_vrect_f(a2_r,a2_i,a2);

     vsip_cvsub_f(a2,ans,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_f(chk_r) > .5) 
         printf(" error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_f(a);
     vsip_valldestroy_f(r);
     vsip_vdestroy_f(a2_r);
     vsip_vdestroy_f(a2_i);
     vsip_cvalldestroy_f(a2);
     vsip_valldestroy_f(arg);
     vsip_valldestroy_f(mag);
     vsip_cvalldestroy_f(ans);
     vsip_vdestroy_f(chk_r);
     vsip_cvalldestroy_f(chk);
   }
   return;
}
