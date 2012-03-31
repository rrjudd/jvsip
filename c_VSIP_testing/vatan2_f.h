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
/* $Id: vatan2_f.h,v 2.0 2003/02/22 15:23:28 judd Exp $ */
#include"VU_vprintm_f.include"
static void vatan2_f(void){
   printf("********\nTEST vatan2_f\n");
   {
     vsip_scalar_f data_a[] = {.1, .0, .3, 4, .5, 6, .7, 8};
     vsip_scalar_f data_b[] = {.0, .2, .3, .4, 5, .6, 7, .8};
     vsip_scalar_f ans[] = { 1.5708, 0, 0.7854, 1.4711, 0.0997, 1.4711, 0.0997, 1.4711};
     vsip_block_f  *block_a = vsip_blockbind_f(data_a,8,VSIP_MEM_NONE);
     vsip_block_f  *block_b = vsip_blockbind_f(data_b,8,VSIP_MEM_NONE);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,8,VSIP_MEM_NONE);
     vsip_vview_f  *a = vsip_vbind_f(block_a,0,1,8);
     vsip_vview_f  *b = vsip_vbind_f(block_b,0,1,8);
     vsip_vview_f  *ansv = vsip_vbind_f(ans_block,0,1,8);
     vsip_vview_f  *c = vsip_vcreate_f(30,VSIP_MEM_NONE);
     vsip_vview_f  *chk = vsip_vcreate_f(8,VSIP_MEM_NONE);
     vsip_vputlength_f(c,8);
     vsip_blockadmit_f(block_a,VSIP_TRUE);
     vsip_blockadmit_f(block_b,VSIP_TRUE);
     vsip_blockadmit_f(ans_block,VSIP_TRUE);
     printf("test out of place\n");
     vsip_vatan2_f(a,b,c);
     printf("vatan2_f(a,b,c)\n vector a\n");VU_vprintm_f("8.6",a);
     printf("vector b\n");VU_vprintm_f("8.6",b);
     printf("vector c\n");VU_vprintm_f("8.6",c);
     printf("expected answer to 4 decimal digits\n");VU_vprintm_f("8.4",ansv);

     vsip_vsub_f(c,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,c in place\n");
     vsip_vputstride_f(c,2);vsip_vcopy_f_f(a,c);
     vsip_vatan2_f(c,b,c);
     vsip_vsub_f(c,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_f(a);
     vsip_valldestroy_f(b);
     vsip_valldestroy_f(c);
     vsip_valldestroy_f(chk);
     vsip_valldestroy_f(ansv);
   }
   return;
}
