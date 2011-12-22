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
/* $Id: cvmag_f.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
static void cvmag_f(void){
   printf("********\nTEST cvmag_f\n");
   {
     vsip_scalar_f data_a_i[] = { 1.1, -1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_f data_a_r[] = { 2.1, -3.2, -2.1, -2.2, +5.1, +5.3};
     vsip_scalar_f ans[] = {2.3707, 3.4176, 2.9698, 3.1113, 5.9682, 6.2434};

     vsip_cblock_f  *block_a = vsip_cblockbind_f(data_a_r,data_a_i,6,VSIP_MEM_NONE);
     vsip_block_f  *block_b = vsip_blockcreate_f(30,VSIP_MEM_NONE);
     vsip_cblock_f  *block_d = vsip_cblockcreate_f(30,VSIP_MEM_NONE);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,6,VSIP_MEM_NONE);

     vsip_cvview_f  *a = vsip_cvbind_f(block_a,0,1,6);
     vsip_vview_f  *b = vsip_vbind_f(block_b,18,-2,6);
     vsip_cvview_f  *d = vsip_cvbind_f(block_d,2,3,6);
     vsip_vview_f   *d_i = vsip_vimagview_f(d);

     vsip_vview_f  *ansv = vsip_vbind_f(ans_block,0,1,6);
     vsip_vview_f  *chk = vsip_vcreate_f(6,VSIP_MEM_NONE);

     vsip_cblockadmit_f(block_a,VSIP_TRUE);
     vsip_blockadmit_f(ans_block,VSIP_TRUE);

     printf("vsip_cvmag_f(a,b)\n");
     vsip_cvmag_f(a,b);
     printf("vector a\n");VU_cvprintm_f("8.6",a);
     printf("vector b\n");VU_vprintm_f("8.6",b);
     printf("right answer\n");VU_vprintm_f("8.4",ansv);

     vsip_vsub_f(b,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,b in place, <b> imag view of <a>.\n");
     vsip_cvcopy_f_f(a,d);
     vsip_cvmag_f(d,d_i);
     vsip_vsub_f(d_i,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cvalldestroy_f(a);
     vsip_valldestroy_f(b);
     vsip_vdestroy_f(d_i);
     vsip_cvalldestroy_f(d);
     vsip_valldestroy_f(chk);
     vsip_valldestroy_f(ansv);
   }
   return;
}
