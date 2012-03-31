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
/* $Id: vnot_bl.h,v 2.0 2003/02/22 15:23:30 judd Exp $ */
#include"VU_vprintm_f.include"
static void vnot_bl(void){
   printf("********\nTEST vnot_bl\n");
   {
     vsip_scalar_bl  data[] = { 1,  1, 0, 0, 1 };
     vsip_scalar_bl  ans[]  = { 0,  0, 1, 1, 0};
     vsip_block_bl  *block = vsip_blockbind_bl(data,5,VSIP_MEM_NONE);
     vsip_block_bl  *ans_block = vsip_blockbind_bl(ans,5,VSIP_MEM_NONE);
     vsip_vview_bl  *a = vsip_vbind_bl(block,0,1,5);
     vsip_vview_bl  *ansv = vsip_vbind_bl(ans_block,0,1,5);
     vsip_vview_bl  *b = vsip_vcreate_bl(5,VSIP_MEM_NONE);
     vsip_vview_f *fv = vsip_vcreate_f(5,VSIP_MEM_NONE);
     vsip_vview_f *fv2 = vsip_vcreate_f(5,VSIP_MEM_NONE);
     vsip_vview_f  *chk = vsip_vcreate_f(5,VSIP_MEM_NONE);
     vsip_blockadmit_bl(block,VSIP_TRUE);
     vsip_blockadmit_bl(ans_block,VSIP_TRUE);
     vsip_vnot_bl(a,b);
     vsip_vcopy_bl_f(a,fv);
     printf("vsip_vnot_bl(a,b)\n vector a\n");VU_vprintm_f("1.0",fv);
     vsip_vcopy_bl_f(b,fv);
     printf("vector b\n");VU_vprintm_f("1.0",fv);
     vsip_vcopy_bl_f(ansv,fv2);
     printf("right answer\n");VU_vprintm_f("1.0",fv2);

     vsip_vsub_f(fv,fv2,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     printf("\na,b in place\n");
     vsip_vnot_bl(a,a);
     vsip_vcopy_bl_f(a,fv);
     vsip_vsub_f(fv,fv2,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");
     vsip_valldestroy_bl(a);
     vsip_valldestroy_bl(b);
     vsip_valldestroy_f(chk);
     vsip_valldestroy_f(fv);
     vsip_valldestroy_f(fv2);
     vsip_valldestroy_bl(ansv);
   }
   return;
}
