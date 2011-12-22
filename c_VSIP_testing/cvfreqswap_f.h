/* Created RJudd */
/* */
static void cvfreqswap_f(void){
   printf("*********\nTEST  vfreqswap_f\n");
   {
      vsip_length M=8,N=9;
      vsip_cvview_f *even = vsip_cvcreate_f(M,VSIP_MEM_NONE);
      vsip_cvview_f *ans_even=vsip_cvcreate_f(M,VSIP_MEM_NONE);
      vsip_vview_f *v;
      vsip_cvview_f *odd = vsip_cvcreate_f(N,VSIP_MEM_NONE);
      vsip_cvview_f *ans_odd=vsip_cvcreate_f(N,VSIP_MEM_NONE);
      vsip_scalar_f even_ans_r[] = {4, 5, 6, 7, 0, 1, 2, 3};
      vsip_scalar_f even_ans_i[]={-4, -5, -6, -7, -0, -1, -2, -3};
      vsip_scalar_f odd_ans_r[] = {4, 5, 6, 7, 8, 0, 1, 2, 3};
      vsip_scalar_f odd_ans_i[]={-4,-5,-6,-7,-8,0,-1,-2,-3};
      vsip_cvcopyfrom_user_f(even_ans_r,even_ans_i, ans_even);
      vsip_cvcopyfrom_user_f(odd_ans_r,odd_ans_i, ans_odd);
      v=vsip_vrealview_f(even);vsip_vramp_f(0,1,v);vsip_vdestroy_f(v);
      v=vsip_vimagview_f(even);vsip_vramp_f(0,-1,v);vsip_vdestroy_f(v);
      v=vsip_vrealview_f(odd);vsip_vramp_f(0,1,v);vsip_vdestroy_f(v);
      v=vsip_vimagview_f(odd);vsip_vramp_f(0,-1,v);vsip_vdestroy_f(v);      

      printf("INPUT even\n");VU_cvprintm_f("2.1",even);
      
      vsip_cvfreqswap_f(even);
      printf("For even expect\n");VU_cvprintm_f("2.1",ans_even);
      printf("for even result\n");VU_cvprintm_f("2.1",even);
      {
         vsip_cvsub_f(even,ans_even,ans_even);
         if(vsip_vcmaxmgsqval_f(ans_even,NULL) > .00001){
            printf("error\n");
         }else{
            printf("correct\n");
         }
      }
      printf("INPUT odd\n");VU_cvprintm_f("2.1",odd);
      vsip_cvfreqswap_f(odd);
      printf("For odd expect\n");VU_cvprintm_f("2.1",ans_odd);
      printf("for odd result\n");VU_cvprintm_f("2.1",odd);
      {
         vsip_cvsub_f(odd,ans_odd,ans_odd);
         if(vsip_vcmaxmgsqval_f(ans_odd,NULL) > .00001){
            printf("error\n");
         }else{
            printf("correct\n");
         }
      }
      vsip_cvalldestroy_f(even);
      vsip_cvalldestroy_f(odd);
   }
}
