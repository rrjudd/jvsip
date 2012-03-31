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
/* $Id: vlog_d.h,v 2.0 2003/02/22 15:23:29 judd Exp $ */
#include"VU_vprintm_d.include"
static void vlog_d(void){
   printf("********\nTEST vlog_d\n");
   {
     vsip_scalar_d data[] = {.1, .2, 1.3, 2.4, 30.0, 600, 700, 800};
     vsip_scalar_d ans[] = { -2.3026, -1.6094, 0.2624, 0.8755, 3.4012, 6.3969, 6.5511, 6.6846 };
     vsip_block_d  *block = vsip_blockbind_d(data,8,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,8,VSIP_MEM_NONE);
     vsip_vview_d  *a = vsip_vbind_d(block,0,1,8);
     vsip_vview_d  *ansv = vsip_vbind_d(ans_block,0,1,8);
     vsip_vview_d  *b = vsip_vcreate_d(30,VSIP_MEM_NONE);
     vsip_vview_d  *chk = vsip_vcreate_d(8,VSIP_MEM_NONE);
     vsip_vputlength_d(b,8);
     vsip_blockadmit_d(block,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);
     vsip_vlog_d(a,b);
     printf("vsip_vlog_d(a,b)\n vector a\n");VU_vprintm_d("8.6",a);
     printf("vector b\n");VU_vprintm_d("8.6",b);
     printf("expected answer to 4 decimal digits\n");VU_vprintm_d("8.4",ansv);

     vsip_vsub_d(b,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,b in place\n");
     vsip_vputstride_d(b,2);vsip_vcopy_d_d(a,b);
     vsip_vlog_d(a,a);
     vsip_vsub_d(a,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_valldestroy_d(a);
     vsip_valldestroy_d(b);
     vsip_valldestroy_d(chk);
     vsip_valldestroy_d(ansv);
   }
   return;
}
