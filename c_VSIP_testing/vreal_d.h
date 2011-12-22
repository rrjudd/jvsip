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
/* $Id: vreal_d.h,v 2.0 2003/02/22 15:23:30 judd Exp $ */
static void vreal_d(void){
   printf("********\nTEST vreal_d\n");
   {
     vsip_scalar_d data_a_i[] = { 1.1, -1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_d data_a_r[] = { 2.1, -3.2, -2.1, -2.2, +5.1, +5.3};
     vsip_scalar_d ans[] = {2.1, -3.2, -2.1, -2.2, +5.1, +5.3};

     vsip_cblock_d  *block_a = vsip_cblockbind_d(data_a_r,data_a_i,6,VSIP_MEM_NONE);
     vsip_block_d  *block_b = vsip_blockcreate_d(30,VSIP_MEM_NONE);
     vsip_cblock_d  *block_d = vsip_cblockcreate_d(30,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,6,VSIP_MEM_NONE);

     vsip_cvview_d  *a = vsip_cvbind_d(block_a,0,1,6);
     vsip_vview_d  *b = vsip_vbind_d(block_b,18,-2,6);
     vsip_cvview_d  *d = vsip_cvbind_d(block_d,2,3,6);
     vsip_vview_d   *d_i = vsip_vimagview_d(d);

     vsip_vview_d  *ansv = vsip_vbind_d(ans_block,0,1,6);
     vsip_vview_d  *chk = vsip_vcreate_d(6,VSIP_MEM_NONE);

     vsip_cblockadmit_d(block_a,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);

     printf("vsip_vreal_d(a,b)\n");
     vsip_vreal_d(a,b);
     printf("vector a\n");VU_cvprintm_d("8.6",a);
     printf("vector b\n");VU_vprintm_d("8.6",b);
     printf("right answer\n");VU_vprintm_d("8.4",ansv);

     vsip_vsub_d(b,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,b in place, <b> imag view of <a>.\n");
     vsip_cvcopy_d_d(a,d);
     vsip_vreal_d(d,d_i);
     vsip_vsub_d(d_i,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cvalldestroy_d(a);
     vsip_valldestroy_d(b);
     vsip_vdestroy_d(d_i);
     vsip_cvalldestroy_d(d);
     vsip_valldestroy_d(chk);
     vsip_valldestroy_d(ansv);
   }
   return;
}
