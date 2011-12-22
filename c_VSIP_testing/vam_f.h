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
/* $Id: vam_f.h,v 2.0 2003/02/22 15:23:27 judd Exp $ */
static void vam_f(void){
   printf("********\nTEST vam_f\n");
   {
     vsip_scalar_f data_a[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_f data_b[] = {10.1, 11.2, 22.1, 12.2, -13.1, -0.3};
     vsip_scalar_f data_c[] = {.3, .7, .11, 1.3, -1.7, -1.9};
     vsip_scalar_f ans[] = { 3.36, 8.68, 2.662, 18.72, 27.54, 6.84};

     vsip_block_f  *block_a = vsip_blockbind_f(data_a,6,VSIP_MEM_NONE);
     vsip_block_f  *block_b = vsip_blockbind_f(data_b,6,VSIP_MEM_NONE);
     vsip_block_f  *block_c = vsip_blockbind_f(data_c,6,VSIP_MEM_NONE);
     vsip_block_f  *block_d = vsip_blockcreate_f(30,VSIP_MEM_NONE);
     vsip_block_f  *block_e = vsip_blockcreate_f(30,VSIP_MEM_NONE);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,6,VSIP_MEM_NONE);

     vsip_vview_f  *a = vsip_vbind_f(block_a,0,1,6);
     vsip_vview_f  *b = vsip_vbind_f(block_b,0,1,6);
     vsip_vview_f  *c = vsip_vbind_f(block_c,0,1,6);
     vsip_vview_f  *d = vsip_vbind_f(block_d,18,-2,6);
     vsip_vview_f  *e = vsip_vbind_f(block_e,2,3,6);

     vsip_vview_f  *ansv = vsip_vbind_f(ans_block,0,1,6);
     vsip_vview_f  *chk = vsip_vcreate_f(6,VSIP_MEM_NONE);

     vsip_blockadmit_f(block_a,VSIP_TRUE);
     vsip_blockadmit_f(block_b,VSIP_TRUE);
     vsip_blockadmit_f(block_c,VSIP_TRUE);
     vsip_blockadmit_f(ans_block,VSIP_TRUE);

     printf("vsip_vam_f(a,b,c,d)\n");
     vsip_vam_f(a,b,c,d);
     printf("vector a\n");VU_vprintm_f("8.6",a);
     printf("vector b\n");VU_vprintm_f("8.6",b);
     printf("vector c\n");VU_vprintm_f("8.6",c);
     printf("vector d\n");VU_vprintm_f("8.6",d);
     printf("right answer\n");VU_vprintm_f("8.4",ansv);

     vsip_vsub_f(d,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,d in place\n");
     vsip_vcopy_f_f(a,e);
     vsip_vam_f(e,b,c,e);
     vsip_vsub_f(e,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\nb,d in place\n");
     vsip_vcopy_f_f(b,d);
     vsip_vam_f(a,d,c,d);
     vsip_vsub_f(d,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_f(a);
     vsip_valldestroy_f(b);
     vsip_valldestroy_f(c);
     vsip_valldestroy_f(d);
     vsip_valldestroy_f(e);
     vsip_valldestroy_f(chk);
     vsip_valldestroy_f(ansv);
   }
   return;
}
