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
/* $Id: vfirst_i.h,v 2.1 2007/04/18 17:05:54 judd Exp $ */
static
vsip_bool first_test_i(
          vsip_scalar_i a,
          vsip_scalar_i b)
{
   if(a>b){
      return VSIP_TRUE;
   } else {
      return VSIP_FALSE;
   }
}
         
static void vfirst_i(void){
   printf("********\nTEST vfirst_i\n");
   {
      vsip_scalar_i data1[] = {  1,  2,  3,  4, 5,  6, 7,   8,  9};
      vsip_scalar_i data2[] = { -1, -2,  4, -4, -5,  7, -7, -8, -9};
      vsip_scalar_i ans_data[]  = {2,2,2,5,5,5,9,9,9};

      vsip_block_i  *block_a = vsip_blockbind_i(data1,9,VSIP_MEM_NONE);
      vsip_block_i  *block_b = vsip_blockbind_i(data2,9,VSIP_MEM_NONE);
      vsip_block_i *block_ans = vsip_blockbind_i(ans_data,9,VSIP_MEM_NONE);

      vsip_vview_i *a = vsip_vbind_i(block_a,0,1,9);
      vsip_vview_i *b = vsip_vbind_i(block_b,0,1,9);
      vsip_vview_i *ans = vsip_vbind_i(block_ans,0,1,9);
      vsip_index j=0;
      vsip_vview_i *r = vsip_vcreate_i(9,VSIP_MEM_NONE);
      vsip_vview_i *chk = vsip_vcreate_i(9,VSIP_MEM_NONE);
      vsip_blockadmit_i(block_a,VSIP_TRUE);
      vsip_blockadmit_i(block_b,VSIP_TRUE);
      vsip_blockadmit_i(block_ans,VSIP_TRUE);
      printf("vsip_vfirst_f(index,function*,b,a)");
      printf("If index > a,b length then return index\n");
      if(vsip_vfirst_i(10,first_test_i,b,a) == (vsip_index)10){
         printf("correct\n"); fflush(stdout);
      } else {
         printf("error \n"); fflush(stdout);
      }
      printf("check for correct index, if not true return length \n");
      for(j=0; j<9; j++){
         vsip_vput_i(r,j,(vsip_scalar_i)vsip_vfirst_i(j,first_test_i,b,a));
      }
      printf("vector a\n");VU_vprintm_i("3",a);
      printf("vector b\n");VU_vprintm_i("3",b);
      printf("vector r\n");VU_vprintm_i("3",r);
      printf("right answer\n");VU_vprintm_i("3",ans);

      vsip_vsub_i(r,ans,chk);
      vsip_vmul_i(chk,chk,chk);  /* make sure we don't get zero by mistake */
      if(vsip_vsumval_i(chk) > 0)
         printf("error\n");
      else
         printf("correct\n");

   }
   return;
}
