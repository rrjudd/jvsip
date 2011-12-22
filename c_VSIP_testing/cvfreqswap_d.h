/* Created RJudd */
/* */
static void cvfreqswap_d(void){
   printf("*********\nTEST  vfreqswap_d\n");
   {
      vsip_length M=8,N=9;
      vsip_cvview_d *even = vsip_cvcreate_d(M,VSIP_MEM_NONE);
      vsip_cvview_d *ans_even=vsip_cvcreate_d(M,VSIP_MEM_NONE);
      vsip_vview_d *v;
      vsip_cvview_d *odd = vsip_cvcreate_d(N,VSIP_MEM_NONE);
      vsip_cvview_d *ans_odd=vsip_cvcreate_d(N,VSIP_MEM_NONE);
      vsip_scalar_d even_ans_r[] = {4, 5, 6, 7, 0, 1, 2, 3};
      vsip_scalar_d even_ans_i[]={-4, -5, -6, -7, -0, -1, -2, -3};
      vsip_scalar_d odd_ans_r[] = {4, 5, 6, 7, 8, 0, 1, 2, 3};
      vsip_scalar_d odd_ans_i[]={-4,-5,-6,-7,-8,0,-1,-2,-3};
      vsip_cvcopyfrom_user_d(even_ans_r,even_ans_i, ans_even);
      vsip_cvcopyfrom_user_d(odd_ans_r,odd_ans_i, ans_odd);
      v=vsip_vrealview_d(even);vsip_vramp_d(0,1,v);vsip_vdestroy_d(v);
      v=vsip_vimagview_d(even);vsip_vramp_d(0,-1,v);vsip_vdestroy_d(v);
      v=vsip_vrealview_d(odd);vsip_vramp_d(0,1,v);vsip_vdestroy_d(v);
      v=vsip_vimagview_d(odd);vsip_vramp_d(0,-1,v);vsip_vdestroy_d(v);      

      printf("INPUT even\n");VU_cvprintm_d("2.1",even);
      
      vsip_cvfreqswap_d(even);
      printf("For even expect\n");VU_cvprintm_d("2.1",ans_even);
      printf("for even result\n");VU_cvprintm_d("2.1",even);
      {
         vsip_cvsub_d(even,ans_even,ans_even);
         if(vsip_vcmaxmgsqval_d(ans_even,NULL) > .00001){
            printf("error\n");
         }else{
            printf("correct\n");
         }
      }
      printf("INPUT odd\n");VU_cvprintm_d("2.1",odd);
      vsip_cvfreqswap_d(odd);
      printf("For odd expect\n");VU_cvprintm_d("2.1",ans_odd);
      printf("for odd result\n");VU_cvprintm_d("2.1",odd);
      {
         vsip_cvsub_d(odd,ans_odd,ans_odd);
         if(vsip_vcmaxmgsqval_d(ans_odd,NULL) > .00001){
            printf("error\n");
         }else{
            printf("correct\n");
         }
      }
      vsip_cvalldestroy_d(even);
      vsip_cvalldestroy_d(odd);
   }
}
