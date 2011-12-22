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
/* $Id: vdiv_d.h,v 2.0 2003/02/22 15:23:28 judd Exp $ */
static void vdiv_d(void){
   printf("********\nTEST vdiv_d\n");
   {
     vsip_scalar_d data_a[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_d data_b[] = {10.1, 11.2, 22.1, 12.2, -13.1, -0.3};
     vsip_scalar_d ans[] = { 0.1089 ,0.1071 ,0.0950 ,0.1803 ,0.2366 ,11.0000 };

     vsip_block_d  *block_a = vsip_blockbind_d(data_a,6,VSIP_MEM_NONE);
     vsip_block_d  *block_b = vsip_blockbind_d(data_b,6,VSIP_MEM_NONE);
     vsip_block_d  *block_c = vsip_blockcreate_d(30,VSIP_MEM_NONE);
     vsip_block_d  *block_d = vsip_blockcreate_d(30,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,6,VSIP_MEM_NONE);

     vsip_vview_d  *a = vsip_vbind_d(block_a,0,1,6);
     vsip_vview_d  *b = vsip_vbind_d(block_b,0,1,6);
     vsip_vview_d  *c = vsip_vbind_d(block_c,18,-2,6);
     vsip_vview_d  *d = vsip_vbind_d(block_d,2,3,6);

     vsip_vview_d  *ansv = vsip_vbind_d(ans_block,0,1,6);
     vsip_vview_d  *chk = vsip_vcreate_d(6,VSIP_MEM_NONE);

     vsip_blockadmit_d(block_a,VSIP_TRUE);
     vsip_blockadmit_d(block_b,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);

     printf("vsip_vdiv_d(a,b)\n");
     vsip_vdiv_d(a,b,c);
     printf("vdiv_d(a,b,c)\n vector a\n");VU_vprintm_d("8.6",a);
     printf("vector b\n");VU_vprintm_d("8.6",b);
     printf("vector c\n");VU_vprintm_d("8.6",c);
     printf("right answer\n");VU_vprintm_d("8.4",ansv);

     vsip_vsub_d(c,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,c in place\n");
     vsip_vcopy_d_d(a,d);
     vsip_vdiv_d(d,b,d);
     vsip_vsub_d(d,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\nb,c in place\n");
     vsip_vcopy_d_d(b,c);
     vsip_vdiv_d(a,c,c);
     vsip_vsub_d(c,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_d(a);
     vsip_valldestroy_d(b);
     vsip_valldestroy_d(c);
     vsip_valldestroy_d(d);
     vsip_valldestroy_d(chk);
     vsip_valldestroy_d(ansv);
   }
   return;
}
