/* Created RJudd */
/* */
#include"VU_cmprintm_d.include"
static void cmfreqswap_d(void){
   printf("*********\nTEST  cmfreqswap_d\n");
   {
      vsip_length M=6,N=5;
      vsip_cmview_d *a = vsip_cmcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_cvview_d *v = vsip_cvbind_d(vsip_cmgetblock_d(a),0,1,M*N);
      vsip_vview_d *v_r=vsip_vrealview_d(v);
      vsip_vview_d *v_i=vsip_vimagview_d(v);
      vsip_cmview_d *ans = vsip_cmcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_scalar_d rdta[]={ 18.0, 19.0, 20.0, 16.0, 17.0, 
                           23.0, 24.0, 25.0, 21.0, 22.0,
                           28.0, 29.0, 30.0, 26.0, 27.0,
                            3.0,  4.0,  5.0,  1.0,  2.0,
                            8.0,  9.0, 10.0,  6.0,  7.0, 
                           13.0, 14.0, 15.0, 11.0, 12.0};
      vsip_scalar_d idta[]={-18.0,-19.0,-20.0,-16.0,-17.0,
                           -23.0,-24.0,-25.0,-21.0,-22.0,
                           -28.0,-29.0,-30.0,-26.0,-27.0,
                            -3.0,- 4.0,- 5.0,- 1.0,- 2.0,
                            -8.0,- 9.0,-10.0,- 6.0,- 7.0, 
                           -13.0,-14.0,-15.0,-11.0,-12.0};
      vsip_cmcopyfrom_user_d(rdta,idta,VSIP_ROW,ans);
      vsip_vramp_d (1,1,v_r);
      vsip_vramp_d (-1,-1,v_i);
      printf("input matrix\n"); VU_cmprintm_d("3.1",a);
      vsip_cmfreqswap_d(a);
      printf("expected output matrix\n"); VU_cmprintm_d("3.1",ans);
      printf("output matrix\n"); VU_cmprintm_d("3.1",a);
      {
         vsip_cmsub_d(a,ans,ans);
         if(vsip_mcmaxmgsqval_d(ans,NULL) > .00001){
            printf("error\n");
         }else{
            printf("correct\n");
         }
      }
      vsip_vdestroy_d(v_r);
      vsip_vdestroy_d(v_i);
      vsip_cvdestroy_d(v);
      vsip_cmalldestroy_d(a);
      vsip_cmalldestroy_d(ans);
   }
}
