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
/* $Id: vpolar_d.h,v 2.0 2003/02/22 15:23:30 judd Exp $ */
static void vpolar_d(void){
   printf("********\nTEST vpolar_d\n");
   {
     vsip_scalar_d data_a_i[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_d data_a_r[] = { 2.1, 3.2, -2.1, -2.2, +5.1, +5.3};
     /* expected angle (argument) */
     vsip_scalar_d ans_a[] = { .4825133, 0.3587707 , 2.3561945, 2.3561945, -.5461666, -0.5569015};
     /* expected magnitude (radius) */
     vsip_scalar_d ans_r[] = { 2.3706539, 3.4176015, 2.9698485, 3.1112698, 5.9682493, 6.2433965};
     vsip_cblock_d *block_a = vsip_cblockbind_d(data_a_r,data_a_i,6,VSIP_MEM_NONE); 
     vsip_block_d  *block_arg = vsip_blockcreate_d(50,VSIP_MEM_NONE);
     vsip_block_d  *block_mag = vsip_blockcreate_d(30,VSIP_MEM_NONE);
     vsip_block_d  *ansa_block = vsip_blockbind_d(ans_a,6,VSIP_MEM_NONE);
     vsip_block_d  *ansr_block = vsip_blockbind_d(ans_r,6,VSIP_MEM_NONE);
     vsip_cvview_d  *a2 = vsip_cvcreate_d(6,VSIP_MEM_NONE);
     vsip_vview_d   *a2_r = vsip_vrealview_d(a2);
     vsip_vview_d   *a2_i = vsip_vimagview_d(a2);

     vsip_cvview_d  *a = vsip_cvbind_d(block_a,0,1,6);
     vsip_vview_d  *arg = vsip_vbind_d(block_arg,5,3,6);
     vsip_vview_d  *mag = vsip_vbind_d(block_mag,18,-2,6);

     vsip_vview_d  *ansa = vsip_vbind_d(ansa_block,0,1,6);
     vsip_vview_d  *ansr = vsip_vbind_d(ansr_block,0,1,6);
     vsip_vview_d  *chk = vsip_vcreate_d(6,VSIP_MEM_NONE);

     vsip_cblockadmit_d(block_a,VSIP_TRUE);
     vsip_blockadmit_d(ansa_block,VSIP_TRUE);
     vsip_blockadmit_d(ansr_block,VSIP_TRUE);

     vsip_cvcopy_d_d(a,a2);

     printf("vsip_vpolar_d(a,mag,arg)\n");
     vsip_vpolar_d(a,mag,arg);
     printf("vector a\n");VU_cvprintm_d("8.6",a);
     printf("vector mag\n");VU_vprintm_d("8.6",mag);
     printf("right mag\n");VU_vprintm_d("8.4",ansr);
     printf("vector arg\n");VU_vprintm_d("8.6",arg);
     printf("right arg\n");VU_vprintm_d("8.4",ansa);

     vsip_vsub_d(mag,ansr,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("mag in error\n");
     else 
         printf("mag correct\n");
     vsip_vsub_d(arg,ansa,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("arg in error\n");
     else 
         printf("arg correct\n");

     printf("\nin place arg real view of |a>, mag imag view of |a>\n");
     vsip_vpolar_d(a2,a2_r,a2_i);

     vsip_vsub_d(a2_r,ansr,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("mag in error\n");
     else 
         printf("mag correct\n");
     vsip_vsub_d(a2_i,ansa,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("arg in error\n");
     else 
         printf("arg correct\n");

     vsip_cvalldestroy_d(a);
     vsip_vdestroy_d(a2_r);
     vsip_vdestroy_d(a2_i);
     vsip_cvalldestroy_d(a2);
     vsip_valldestroy_d(arg);
     vsip_valldestroy_d(mag);
     vsip_valldestroy_d(ansa);
     vsip_valldestroy_d(ansr);
     vsip_valldestroy_d(chk);
   }
   return;
}
