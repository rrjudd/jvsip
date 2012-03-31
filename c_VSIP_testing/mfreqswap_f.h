/* Created RJudd */
/* */
#include"VU_mprintm_f.include"
static void mfreqswap_f(void){
   printf("*********\nTEST  vfreqswap_f\n");
   {
      vsip_length M=6,N=5;
      vsip_mview_f *a = vsip_mcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_vview_f *v = vsip_vbind_f(vsip_mgetblock_f(a),0,1,M*N);
      vsip_mview_f *ans = vsip_mcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_scalar_f dta[]={ 18.0, 19.0, 20.0, 16.0, 17.0, 
                           23.0, 24.0, 25.0, 21.0, 22.0,
                           28.0, 29.0, 30.0, 26.0, 27.0,
                            3.0,  4.0,  5.0,  1.0,  2.0,
                            8.0,  9.0, 10.0,  6.0,  7.0, 
                           13.0, 14.0, 15.0, 11.0, 12.0};
      vsip_mcopyfrom_user_f(dta,VSIP_ROW,ans);
      vsip_vramp_f (1,1,v);
      printf("input matrix\n"); VU_mprintm_f("3.1",a);
      vsip_mfreqswap_f(a);
      printf("output matrix\n"); VU_mprintm_f("3.1",a);
      {
         vsip_msub_f(a,ans,ans);
         if(fabs(vsip_mmaxval_f(ans,NULL)) > .00001){
            printf("error\n");
         }else{
            printf("correct\n");
         }
      }
      vsip_vdestroy_f(v);
      vsip_malldestroy_f(a);
      vsip_malldestroy_f(ans);
   }
}
