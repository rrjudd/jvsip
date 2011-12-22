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
/* $Id: veuler_f.h,v 2.0 2003/02/22 15:23:28 judd Exp $ */
static void veuler_f(void){
   printf("********\nTEST veuler_f\n");
   {
      vsip_scalar_f data[] = {.1*M_PI,.3*M_PI, .5*M_PI, .7*M_PI, .9 *M_PI};
      vsip_scalar_f ansdata[]={0.9511,0.309, 0.5878,0.809, 0.0,1.0, -0.5878,0.809, -0.9511,0.309};
      vsip_block_f  *block = vsip_blockbind_f(data,5,VSIP_MEM_NONE);
      vsip_cblock_f *ans_block = vsip_cblockbind_f(ansdata,NDPTR_f,5,VSIP_MEM_NONE);
      vsip_vview_f  *a = vsip_vbind_f(block,0,1,5);
      vsip_cvview_f *ans = vsip_cvbind_f(ans_block,0,1,5);
      vsip_cvview_f *b = vsip_cvcreate_f(5,VSIP_MEM_NONE);
      vsip_cvview_f *chk = vsip_cvcreate_f(5,VSIP_MEM_NONE);
      vsip_vview_f  *chk_r = vsip_vrealview_f(chk);
      vsip_vview_f  *a2 = vsip_vrealview_f(b);
      vsip_blockadmit_f(block,VSIP_TRUE);
      vsip_cblockadmit_f(ans_block,VSIP_TRUE);
      vsip_veuler_f(a,b);
      printf("vsip_veuler_f(a,b)\n");
      printf("vector a\n");VU_vprintm_f("8.6",a);
      printf("vector b\n");VU_cvprintm_f("8.6",b);
      printf("right answer \n");VU_cvprintm_f("8.4",ans);
      vsip_cvsub_f(b,ans,chk);vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
      if(vsip_vsumval_f(chk_r) < .5)
          printf("correct\n");
      else
          printf("error\n");
      vsip_vcopy_f_f(a,a2); 
      printf("in place, |a> real view of |b>\n");
      vsip_veuler_f(a2,b);
      vsip_cvsub_f(b,ans,chk);vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,.0001,.0001,0,1,chk_r);
      if(vsip_vsumval_f(chk_r) < .5)
          printf("correct\n");
      else
          printf("error\n");
   }
   return;
}
