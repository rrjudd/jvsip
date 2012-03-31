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
/* $Id: vpolar_f.h,v 2.0 2003/02/22 15:23:30 judd Exp $ */
#include"VU_vprintm_f.include"
#include"VU_cvprintm_f.include"
static void vpolar_f(void){
   printf("********\nTEST vpolar_f\n");
   {
     vsip_scalar_f data_a_i[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_f data_a_r[] = { 2.1, 3.2, -2.1, -2.2, +5.1, +5.3};
     /* expected angle (argument) */
     vsip_scalar_f ans_a[] = { .4825133, 0.3587707 , 2.3561945, 2.3561945, -.5461666, -0.5569015};
     /* expected magnitude (radius) */
     vsip_scalar_f ans_r[] = { 2.3706539, 3.4176015, 2.9698485, 3.1112698, 5.9682493, 6.2433965};
     vsip_cblock_f *block_a = vsip_cblockbind_f(data_a_r,data_a_i,6,VSIP_MEM_NONE); 
     vsip_block_f  *block_arg = vsip_blockcreate_f(50,VSIP_MEM_NONE);
     vsip_block_f  *block_mag = vsip_blockcreate_f(30,VSIP_MEM_NONE);
     vsip_block_f  *ansa_block = vsip_blockbind_f(ans_a,6,VSIP_MEM_NONE);
     vsip_block_f  *ansr_block = vsip_blockbind_f(ans_r,6,VSIP_MEM_NONE);
     vsip_cvview_f  *a2 = vsip_cvcreate_f(6,VSIP_MEM_NONE);
     vsip_vview_f   *a2_r = vsip_vrealview_f(a2);
     vsip_vview_f   *a2_i = vsip_vimagview_f(a2);

     vsip_cvview_f  *a = vsip_cvbind_f(block_a,0,1,6);
     vsip_vview_f  *arg = vsip_vbind_f(block_arg,5,3,6);
     vsip_vview_f  *mag = vsip_vbind_f(block_mag,18,-2,6);

     vsip_vview_f  *ansa = vsip_vbind_f(ansa_block,0,1,6);
     vsip_vview_f  *ansr = vsip_vbind_f(ansr_block,0,1,6);
     vsip_vview_f  *chk = vsip_vcreate_f(6,VSIP_MEM_NONE);

     vsip_cblockadmit_f(block_a,VSIP_TRUE);
     vsip_blockadmit_f(ansa_block,VSIP_TRUE);
     vsip_blockadmit_f(ansr_block,VSIP_TRUE);

     vsip_cvcopy_f_f(a,a2);

     printf("vsip_vpolar_f(a,mag,arg)\n");
     vsip_vpolar_f(a,mag,arg);
     printf("vector a\n");VU_cvprintm_f("8.6",a);
     printf("vector mag\n");VU_vprintm_f("8.6",mag);
     printf("right mag\n");VU_vprintm_f("8.4",ansr);
     printf("vector arg\n");VU_vprintm_f("8.6",arg);
     printf("right arg\n");VU_vprintm_f("8.4",ansa);

     vsip_vsub_f(mag,ansr,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("mag in error\n");
     else 
         printf("mag correct\n");
     vsip_vsub_f(arg,ansa,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("arg in error\n");
     else 
         printf("arg correct\n");

     printf("\nin place arg real view of |a>, mag imag view of |a>\n");
     vsip_vpolar_f(a2,a2_r,a2_i);

     vsip_vsub_f(a2_r,ansr,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("mag in error\n");
     else 
         printf("mag correct\n");
     vsip_vsub_f(a2_i,ansa,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("arg in error\n");
     else 
         printf("arg correct\n");

     vsip_cvalldestroy_f(a);
     vsip_vdestroy_f(a2_r);
     vsip_vdestroy_f(a2_i);
     vsip_cvalldestroy_f(a2);
     vsip_valldestroy_f(arg);
     vsip_valldestroy_f(mag);
     vsip_valldestroy_f(ansa);
     vsip_valldestroy_f(ansr);
     vsip_valldestroy_f(chk);
   }
   return;
}
