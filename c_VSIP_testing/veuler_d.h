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
/* $Id: veuler_d.h,v 2.0 2003/02/22 15:23:28 judd Exp $ */
#include"VU_vprintm_d.include"
#include"VU_cvprintm_d.include"
static void veuler_d(void){
   printf("********\nTEST veuler_d\n");
   {
      vsip_scalar_d data[] = {.1*M_PI,.3*M_PI, .5*M_PI, .7*M_PI, .9 *M_PI};
      vsip_scalar_d ansdata[]={0.9511,0.309, 0.5878,0.809, 0.0,1.0, -0.5878,0.809, -0.9511,0.309};
      vsip_block_d  *block = vsip_blockbind_d(data,5,VSIP_MEM_NONE);
      vsip_cblock_d *ans_block = vsip_cblockbind_d(ansdata,NDPTR_d,5,VSIP_MEM_NONE);
      vsip_vview_d  *a = vsip_vbind_d(block,0,1,5);
      vsip_cvview_d *ans = vsip_cvbind_d(ans_block,0,1,5);
      vsip_cvview_d *b = vsip_cvcreate_d(5,VSIP_MEM_NONE);
      vsip_cvview_d *chk = vsip_cvcreate_d(5,VSIP_MEM_NONE);
      vsip_vview_d  *chk_r = vsip_vrealview_d(chk);
      vsip_vview_d  *a2 = vsip_vrealview_d(b);
      vsip_blockadmit_d(block,VSIP_TRUE);
      vsip_cblockadmit_d(ans_block,VSIP_TRUE);
      vsip_veuler_d(a,b);
      printf("vsip_veuler_d(a,b)\n");
      printf("vector a\n");VU_vprintm_d("8.6",a);
      printf("vector b\n");VU_cvprintm_d("8.6",b);
      printf("right answer \n");VU_cvprintm_d("8.4",ans);
      vsip_cvsub_d(b,ans,chk);vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
      if(vsip_vsumval_d(chk_r) < .5)
          printf("correct\n");
      else
          printf("error\n");
      vsip_vcopy_d_d(a,a2); 
      printf("in place, |a> real view of |b>\n");
      vsip_veuler_d(a2,b);
      vsip_cvsub_d(b,ans,chk);vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,.0001,.0001,0,1,chk_r);
      if(vsip_vsumval_d(chk_r) < .5)
          printf("correct\n");
      else
          printf("error\n");
   }
   return;
}
