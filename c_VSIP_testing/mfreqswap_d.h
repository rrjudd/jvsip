/* Created RJudd */
/* */
static void mfreqswap_d(void){
   printf("*********\nTEST  vfreqswap_d\n");
   {
      vsip_length M=6,N=5;
      vsip_mview_d *a = vsip_mcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_vview_d *v = vsip_vbind_d(vsip_mgetblock_d(a),0,1,M*N);
      vsip_mview_d *ans = vsip_mcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_scalar_d dta[]={ 18.0, 19.0, 20.0, 16.0, 17.0, 
                           23.0, 24.0, 25.0, 21.0, 22.0,
                           28.0, 29.0, 30.0, 26.0, 27.0,
                            3.0,  4.0,  5.0,  1.0,  2.0,
                            8.0,  9.0, 10.0,  6.0,  7.0, 
                           13.0, 14.0, 15.0, 11.0, 12.0};
      vsip_mcopyfrom_user_d(dta,VSIP_ROW,ans);
      vsip_vramp_d (1,1,v);
      printf("input matrix\n"); VU_mprintm_d("3.1",a);
      vsip_mfreqswap_d(a);
      printf("output matrix\n"); VU_mprintm_d("3.1",a);
      {
         vsip_msub_d(a,ans,ans);
         if(fabs(vsip_mmaxval_d(ans,NULL)) > .00001){
            printf("error\n");
         }else{
            printf("correct\n");
         }
      }
      vsip_vdestroy_d(v);
      vsip_malldestroy_d(a);
      vsip_malldestroy_d(ans);
   }
}
