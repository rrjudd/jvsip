/* Created RJudd */
/* */
#include"VU_vprintm_f.include"
static void vfreqswap_f(void){
   printf("*********\nTEST  vfreqswap_f\n");
   {
      vsip_length M=8,N=9;
      vsip_vview_f *even = vsip_vcreate_f(M,VSIP_MEM_NONE);
      vsip_vview_f *ans_even=vsip_vcreate_f(M,VSIP_MEM_NONE);
      vsip_vview_f *odd = vsip_vcreate_f(N,VSIP_MEM_NONE);
      vsip_vview_f *ans_odd=vsip_vcreate_f(N,VSIP_MEM_NONE);
      vsip_scalar_f even_ans[] = {4, 5, 6, 7, 0, 1, 2, 3};
      vsip_scalar_f odd_ans[] = {4, 5, 6, 7, 8, 0, 1, 2, 3};
      vsip_vcopyfrom_user_f(even_ans, ans_even);
      vsip_vcopyfrom_user_f(odd_ans, ans_odd);
      vsip_vramp_f(0,1,even);
      vsip_vramp_f(0,1,odd);
      vsip_vfreqswap_f(even);
      printf("For even expect\n");VU_vprintm_f("2.1",ans_even);
      printf("for even result\n");VU_vprintm_f("2.1",even);
      {
         vsip_vsub_f(even,ans_even,ans_even);
         if(fabs(vsip_vmaxval_f(ans_even,NULL)) > .00001){
            printf("error\n");
         }else{
            printf("correct\n");
         }
      }
      vsip_vfreqswap_f(odd);
      printf("For odd expect\n");VU_vprintm_f("2.1",ans_odd);
      printf("for odd result\n");VU_vprintm_f("2.1",odd);
      {
         vsip_vsub_f(odd,ans_odd,ans_odd);
         if(fabs(vsip_vmaxval_f(ans_odd,NULL)) > .00001){
            printf("error\n");
         }else{
            printf("correct\n");
         }
      }
      vsip_valldestroy_f(even);
      vsip_valldestroy_f(odd);
   }
}
