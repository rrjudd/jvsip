/* Created RJudd */
/* */
#include"VU_vprintm_d.include"
static void interpolate_linear_d(void) {
   printf("*********\nTEST  linear fitfor double\n");
   {
      vsip_length N0 = 11;
      vsip_length N  = 50;
      vsip_vview_d *yf = vsip_vcreate_d(N,VSIP_MEM_NONE);
      vsip_vview_d *xf = vsip_vcreate_d(N,VSIP_MEM_NONE);
      vsip_vview_d *xp = vsip_vcreate_d(N0,VSIP_MEM_NONE);
      vsip_vview_d *yp = vsip_vcreate_d(N0,VSIP_MEM_NONE);
      vsip_vview_d *yf_ans=vsip_vcreate_d(N,VSIP_MEM_NONE);
      vsip_vramp_d(0.0,1.0,xp);
      vsip_vramp_d(0.0,0.204,xf);
      vsip_svmul_d(2.0/5.0 * M_PI,xp,yp);
      vsip_svmul_d(2.0/5.0 * M_PI,xf,yf_ans);
      vsip_vsin_d(yp,yp);
      vsip_vsin_d(yf_ans,yf_ans);
      printf("xp = ");VU_vprintm_d("5.4",xp);
      printf("yp = ");VU_vprintm_d("5.4",yp);
      printf("xf = ");VU_vprintm_d("5.4",xf);
      vsip_vinterp_linear_d(xp,yp,xf,yf);
      printf("linfit = ");VU_vprintm_d("5.4",yf);
      printf("ans = ");VU_vprintm_d("5.4",yf_ans);
      vsip_valldestroy_d(xf);
      vsip_valldestroy_d(xp);
      vsip_valldestroy_d(yp);
      vsip_valldestroy_d(yf);
      vsip_valldestroy_d(yf_ans);
   } 
}
