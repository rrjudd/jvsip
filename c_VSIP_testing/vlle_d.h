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
/* $Id: vlle_d.h,v 2.0 2003/02/22 15:23:29 judd Exp $ */
#include"VU_vprintm_d.include"
static void vlle_d(void){
   printf("********\nTEST vlle_d\n");
   {
      vsip_scalar_d data1[] = { 0.0, 1.2, 2.0, 4.2, 3.3, -2.2, 5.2};
      vsip_scalar_d data2[] = { 1.0, 1.2, 2.9, 4.2, 2.3, -2.2, 3.2};
      vsip_scalar_d ans_data[]   = { 1.0, 1.0, 1.0, 1.0, 0.0,  1.0, 0.0};
      vsip_block_d  *block_a = vsip_blockbind_d(data1,7,VSIP_MEM_NONE);
      vsip_block_d  *block_b = vsip_blockbind_d(data2,7,VSIP_MEM_NONE);
      vsip_block_d  *block_ans = vsip_blockbind_d(ans_data,7,VSIP_MEM_NONE);
      vsip_vview_d *a = vsip_vbind_d(block_a,0,1,7);
      vsip_vview_d *b = vsip_vbind_d(block_b,0,1,7);
      vsip_vview_d *ans = vsip_vbind_d(block_ans,0,1,7);
      vsip_vview_bl *c = vsip_vcreate_bl(7,VSIP_MEM_NONE);
      vsip_vview_d  *d = vsip_vcreate_d(7,VSIP_MEM_NONE);
      vsip_vview_d  *chk = vsip_vcreate_d(7,VSIP_MEM_NONE);
      vsip_blockadmit_d(block_a,VSIP_TRUE);
      vsip_blockadmit_d(block_b,VSIP_TRUE);
      vsip_blockadmit_d(block_ans,VSIP_TRUE);
      
      vsip_vlle_d(a,b,c);
      vsip_vcopy_bl_d(c,d);
      printf("vsip_vlle_d(a,b,c)");
      printf("vector a\n");VU_vprintm_d("8.6",a);
      printf("vector b\n");VU_vprintm_d("8.6",b);
      printf("vector c\n");VU_vprintm_d("1.0",d);
      printf("right answer\n");VU_vprintm_d("1.0",ans);

      vsip_vsub_d(d,ans,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
      if(vsip_vsumval_d(chk) > .5)
         printf("error\n");
      else
         printf("correct\n");

   }
   return;
}
