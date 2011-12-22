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
/* $Id: vfill_f.h,v 2.0 2003/02/22 15:23:28 judd Exp $ */
static void vfill_f(void){
   printf("********\nTEST vfill_f\n");
   {
     vsip_scalar_f alpha     = 1.5;
     vsip_scalar_f ans[]    = {1.5,1.5,1.5,1.5,1.5,1.5};

     vsip_block_f  *block_c = vsip_blockcreate_f(30,VSIP_MEM_NONE);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,6,VSIP_MEM_NONE);

     vsip_vview_f  *c = vsip_vbind_f(block_c,18,-2,6);

     vsip_vview_f  *ansv = vsip_vbind_f(ans_block,0,1,6);
     vsip_vview_f  *chk = vsip_vcreate_f(6,VSIP_MEM_NONE);

     vsip_blockadmit_f(ans_block,VSIP_TRUE);

     printf("vsip_vfill_f(alpha,b)\n");
     vsip_vfill_f(alpha,c);
     printf("alpha = %f\n",alpha);
     printf("vector c\n");VU_vprintm_f("8.6",c);
     printf("right answer\n");VU_vprintm_f("8.4",ansv);

     vsip_vsub_f(c,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_f(c);
     vsip_valldestroy_f(chk);
     vsip_valldestroy_f(ansv);
   }
   return;
}
