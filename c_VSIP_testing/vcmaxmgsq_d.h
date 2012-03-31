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
/* $Id: vcmaxmgsq_d.h,v 2.0 2003/02/22 15:23:28 judd Exp $ */
#include"VU_vprintm_d.include"
#include"VU_cvprintm_d.include"
static void vcmaxmgsq_d(void){
   printf("********\nTEST vcmaxmgsq_d\n");
   {
     vsip_scalar_d data_a_i[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_d data_a_r[] = { 2.1, 3.2, -2.1, -2.2, +5.1, +5.3};
     vsip_scalar_d data_b_i[] = {10.1, 11.2, 22.1, 12.2, -13.1, -0.3};
     vsip_scalar_d data_b_r[] = {8.1, 10.2, -12.1, 10.2, -11.1, -2.3};
     vsip_scalar_d ans[] = {167.62,229.48,634.82,252.88,294.82,38.98};

     vsip_cblock_d  *block_a = vsip_cblockbind_d(data_a_r,data_a_i,6,VSIP_MEM_NONE);
     vsip_cblock_d  *block_b = vsip_cblockbind_d(data_b_r,data_b_i,6,VSIP_MEM_NONE);
     vsip_block_d   *block_c = vsip_blockcreate_d(30,VSIP_MEM_NONE);
     vsip_block_d   *ans_block = vsip_blockbind_d(ans,6,VSIP_MEM_NONE);

     vsip_cvview_d  *a = vsip_cvbind_d(block_a,0,1,6);
     vsip_cvview_d  *b = vsip_cvbind_d(block_b,0,1,6);
     vsip_vview_d  *c = vsip_vbind_d(block_c,18,-2,6);

     vsip_vview_d  *ansv = vsip_vbind_d(ans_block,0,1,6);
     vsip_vview_d   *chk = vsip_vcreate_d(6,VSIP_MEM_NONE);

     vsip_cblockadmit_d(block_a,VSIP_TRUE);
     vsip_cblockadmit_d(block_b,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);

     printf("vsip_vcmaxmgsq_d(a,b,c)\n");
     vsip_vcmaxmgsq_d(a,b,c);
     printf("vcmaxmgsq_d(a,b,c)\n vector a\n");VU_cvprintm_d("8.6",a);
     printf("vector b\n");VU_cvprintm_d("8.6",b);
     printf("vector c\n");VU_vprintm_d("8.6",c);
     printf("right answer\n");VU_vprintm_d("8.4",ansv);

     vsip_vsub_d(c,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,c in place, <c> real view of <a>\n");
     {  vsip_vview_d *a_r = vsip_vrealview_d(a);
        vsip_vcmaxmgsq_d(a,b,a_r);
        vsip_vsub_d(a_r,ansv,chk); 
        vsip_vdestroy_d(a_r);
     }
     vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cvalldestroy_d(a);
     vsip_cvalldestroy_d(b);
     vsip_valldestroy_d(c);
     vsip_valldestroy_d(chk);
     vsip_valldestroy_d(ansv);
   }
   return;
}
