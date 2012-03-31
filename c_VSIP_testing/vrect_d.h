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
/* $Id: vrect_d.h,v 2.0 2003/02/22 15:23:30 judd Exp $ */
#include"VU_vprintm_d.include"
#include"VU_cvprintm_d.include"
static void vrect_d(void){
   printf("********\nTEST vrect_d\n");
   {
     vsip_scalar_d ans_r[] = { 2.1, 3.2, -2.1, -2.2, +5.1, +5.3};
     vsip_scalar_d ans_i[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     /* expected angle (argument) */
     vsip_scalar_d data_a[] = { .4825133, 0.3587707 , 2.3561945, 2.3561945, -.5461666, -0.5569015};
     /* expected magnitude (radius) */
     vsip_scalar_d data_r[] = { 2.3706539, 3.4176015, 2.9698485, 3.1112698, 5.9682493, 6.2433965};
     vsip_block_d *block_a = vsip_blockbind_d(data_a,6,VSIP_MEM_NONE); 
     vsip_block_d *block_r = vsip_blockbind_d(data_r,6,VSIP_MEM_NONE); 
     vsip_block_d  *block_arg = vsip_blockcreate_d(50,VSIP_MEM_NONE);
     vsip_block_d  *block_mag = vsip_blockcreate_d(30,VSIP_MEM_NONE);
     vsip_cblock_d  *ans_block = vsip_cblockbind_d(ans_r,ans_i,6,VSIP_MEM_NONE);
     vsip_cvview_d  *a2 = vsip_cvcreate_d(6,VSIP_MEM_NONE);
     vsip_vview_d   *a2_r = vsip_vrealview_d(a2);
     vsip_vview_d   *a2_i = vsip_vimagview_d(a2);

     vsip_vview_d  *a = vsip_vbind_d(block_a,0,1,6);
     vsip_vview_d  *r = vsip_vbind_d(block_r,0,1,6);
     vsip_vview_d  *arg = vsip_vbind_d(block_arg,5,3,6);
     vsip_vview_d  *mag = vsip_vbind_d(block_mag,18,-2,6);

     vsip_cvview_d  *ans = vsip_cvbind_d(ans_block,0,1,6);
     vsip_cvview_d  *chk = vsip_cvcreate_d(6,VSIP_MEM_NONE);
     vsip_vview_d  *chk_r = vsip_vrealview_d(chk);

     vsip_blockadmit_d(block_a,VSIP_TRUE);
     vsip_blockadmit_d(block_r,VSIP_TRUE);
     vsip_cblockadmit_d(ans_block,VSIP_TRUE);

     vsip_vcopy_d_d(a,arg);
     vsip_vcopy_d_d(r,mag);

     printf("vsip_vrect_d(r,phi,y)\n");
     vsip_vrect_d(mag,arg,a2);
     printf("vector r\n");VU_vprintm_d("8.6",r);
     printf("vector phi\n");VU_vprintm_d("8.6",a);
     printf("vector y\n");VU_cvprintm_d("8.6",a2);
     printf("right answer\n");VU_cvprintm_d("6.4",ans);

     vsip_cvsub_d(a2,ans,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf(" error\n");
     else 
         printf("correct\n");

     vsip_vcopy_d_d(a,a2_i);
     vsip_vcopy_d_d(r,a2_r);
     printf("\nin place arg imag view of |a>, mag real view of |a>\n");
     vsip_vrect_d(a2_r,a2_i,a2);

     vsip_cvsub_d(a2,ans,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_vsumval_d(chk_r) > .5) 
         printf(" error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_d(a);
     vsip_valldestroy_d(r);
     vsip_vdestroy_d(a2_r);
     vsip_vdestroy_d(a2_i);
     vsip_cvalldestroy_d(a2);
     vsip_valldestroy_d(arg);
     vsip_valldestroy_d(mag);
     vsip_cvalldestroy_d(ans);
     vsip_vdestroy_d(chk_r);
     vsip_cvalldestroy_d(chk);
   }
   return;
}
