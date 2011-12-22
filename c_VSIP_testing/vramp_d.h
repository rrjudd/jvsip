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
/* $Id: vramp_d.h,v 2.1 2009/09/05 18:01:45 judd Exp $ */
static void vramp_d(void){
   printf("********\nTEST vramp_d\n");
   {
     vsip_scalar_d ans[] = { 1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
     vsip_scalar_d start = 1.1;
     vsip_scalar_d inc   = 0.1;

     vsip_block_d  *block_c = vsip_blockcreate_d(30,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,6,VSIP_MEM_NONE);

     vsip_vview_d  *c = vsip_vbind_d(block_c,18,-2,6);
     vsip_vview_d  *ansv = vsip_vbind_d(ans_block,0,1,6);
     vsip_vview_d  *chk = vsip_vcreate_d(6,VSIP_MEM_NONE);

     vsip_blockadmit_d(ans_block,VSIP_TRUE);

     printf("vsip_vramp_d(start,inc,c)\n");
     vsip_vramp_d(start,inc,c);
     printf("start = %3.1f\ninc = %3.1f \nVector <c> of length 6\n",(double)start,(double)inc);
     printf("vector c\n");VU_vprintm_d("8.6",c);
     printf("right answer\n");VU_vprintm_d("8.4",ansv);

     vsip_vsub_d(c,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_d(c);
     vsip_valldestroy_d(chk);
     vsip_valldestroy_d(ansv);
   }
   return;
}
