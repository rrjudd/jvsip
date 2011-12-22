/* Created RJudd */
/* */
static void interpolate_spline_f(void) {
   printf("*********\nTEST spline for float\n");
   {
      vsip_length N0 = 11;
      vsip_spline_f *spl = vsip_spline_create_f(N0);
      vsip_length N  = 50;
      vsip_index index;
      vsip_vview_f *yf = vsip_vcreate_f(N,VSIP_MEM_NONE);
      vsip_vview_f *xf = vsip_vcreate_f(N,VSIP_MEM_NONE);
      vsip_vview_f *xp = vsip_vcreate_f(N0,VSIP_MEM_NONE);
      vsip_vview_f *yp = vsip_vcreate_f(N0,VSIP_MEM_NONE);
      vsip_vview_f *yf_ans=vsip_vcreate_f(N,VSIP_MEM_NONE);
      vsip_vramp_f(0.0,1.0,xp);
      vsip_vramp_f(0.0,0.204,xf);
      vsip_svmul_f(2.0/5.0 * M_PI,xp,yp);
      vsip_svmul_f(2.0/5.0 * M_PI,xf,yf_ans);
      vsip_vsin_f(yp,yp);
      vsip_vsin_f(yf_ans,yf_ans);
      printf("xp = \n");VU_vprintm_f("5.4",xp);
      printf("yp = \n");VU_vprintm_f("5.4",yp);
      printf("xf = \n");VU_vprintm_f("5.4",xf);
      vsip_vinterp_spline_f(xp,yp,spl,xf,yf);
      printf("spline = \n");VU_vprintm_f("5.4",yf);
      printf("ans = \n");VU_vprintm_f("5.4",yf_ans);
      vsip_vsub_f(yf_ans,yf,yf_ans);
      vsip_vmag_f(yf_ans,yf_ans);
      if(vsip_vmaxval_f(yf_ans,&index) < .01)
         printf("correct\n");
      else
         printf("error\n");
      vsip_spline_destroy_f(spl);
      vsip_valldestroy_f(xf);
      vsip_valldestroy_f(xp);
      vsip_valldestroy_f(yp);
      vsip_valldestroy_f(yf);
      vsip_valldestroy_f(yf_ans);
   } 
}
