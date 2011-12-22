/* Created RJudd */
/* */
static void vfreqswap_d(void){
   printf("*********\nTEST  vfreqswap_d\n");
   {
      vsip_length M=8,N=9;
      vsip_vview_d *even = vsip_vcreate_d(M,VSIP_MEM_NONE);
      vsip_vview_d *ans_even=vsip_vcreate_d(M,VSIP_MEM_NONE);
      vsip_vview_d *odd = vsip_vcreate_d(N,VSIP_MEM_NONE);
      vsip_vview_d *ans_odd=vsip_vcreate_d(N,VSIP_MEM_NONE);
      vsip_scalar_d even_ans[] = {4, 5, 6, 7, 0, 1, 2, 3};
      vsip_scalar_d odd_ans[] = {4, 5, 6, 7, 8, 0, 1, 2, 3};
      vsip_vcopyfrom_user_d(even_ans, ans_even);
      vsip_vcopyfrom_user_d(odd_ans, ans_odd);
      vsip_vramp_d(0,1,even);
      vsip_vramp_d(0,1,odd);
      vsip_vfreqswap_d(even);
      printf("For even expect\n");VU_vprintm_d("2.1",ans_even);
      printf("for even result\n");VU_vprintm_d("2.1",even);
      {
         vsip_vsub_d(even,ans_even,ans_even);
         if(fabs(vsip_vmaxval_d(ans_even,NULL)) > .00001){
            printf("error\n");
         }else{
            printf("correct\n");
         }
      }
      vsip_vfreqswap_d(odd);
      printf("For odd expect\n");VU_vprintm_d("2.1",ans_odd);
      printf("for odd result\n");VU_vprintm_d("2.1",odd);
      {
         vsip_vsub_d(odd,ans_odd,ans_odd);
         if(fabs(vsip_vmaxval_d(ans_odd,NULL)) > .00001){
            printf("error\n");
         }else{
            printf("correct\n");
         }
      }
      vsip_valldestroy_d(even);
      vsip_valldestroy_d(odd);
   }
}
