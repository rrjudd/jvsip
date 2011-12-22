/* Created RJudd */
/* */
static void cmfreqswap_f(void){
   printf("*********\nTEST  cmfreqswap_f\n");
   {
      vsip_length M=6,N=5;
      vsip_cmview_f *a = vsip_cmcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_cvview_f *v = vsip_cvbind_f(vsip_cmgetblock_f(a),0,1,M*N);
      vsip_vview_f *v_r=vsip_vrealview_f(v);
      vsip_vview_f *v_i=vsip_vimagview_f(v);
      vsip_cmview_f *ans = vsip_cmcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_scalar_f rdta[]={ 18.0, 19.0, 20.0, 16.0, 17.0, 
                           23.0, 24.0, 25.0, 21.0, 22.0,
                           28.0, 29.0, 30.0, 26.0, 27.0,
                            3.0,  4.0,  5.0,  1.0,  2.0,
                            8.0,  9.0, 10.0,  6.0,  7.0, 
                           13.0, 14.0, 15.0, 11.0, 12.0};
      vsip_scalar_f idta[]={-18.0,-19.0,-20.0,-16.0,-17.0,
                           -23.0,-24.0,-25.0,-21.0,-22.0,
                           -28.0,-29.0,-30.0,-26.0,-27.0,
                            -3.0,- 4.0,- 5.0,- 1.0,- 2.0,
                            -8.0,- 9.0,-10.0,- 6.0,- 7.0, 
                           -13.0,-14.0,-15.0,-11.0,-12.0};
      vsip_cmcopyfrom_user_f(rdta,idta,VSIP_ROW,ans);
      vsip_vramp_f (1,1,v_r);
      vsip_vramp_f (-1,-1,v_i);
      printf("input matrix\n"); VU_cmprintm_f("3.1",a);
      vsip_cmfreqswap_f(a);
      printf("expected output matrix\n"); VU_cmprintm_f("3.1",ans);
      printf("output matrix\n"); VU_cmprintm_f("3.1",a);
      {
         vsip_cmsub_f(a,ans,ans);
         if(vsip_mcmaxmgsqval_f(ans,NULL) > .00001){
            printf("error\n");
         }else{
            printf("correct\n");
         }
      }
      vsip_vdestroy_f(v_r);
      vsip_vdestroy_f(v_i);
      vsip_cvdestroy_f(v);
      vsip_cmalldestroy_f(a);
      vsip_cmalldestroy_f(ans);
   }
}
