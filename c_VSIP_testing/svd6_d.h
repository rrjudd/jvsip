/*
 *  svd6.h
 *  VSIP_svd_dev
 *
 *  Created by Randall Judd on 9/13/08.
 *  Copyright 2008 Home. All rights reserved
 *
 */

static void svd6_d(void){
   printf("********\nTEST svd6 for double\n");
   {
      vsip_index i;
      vsip_length M=50, N=100;
      vsip_randstate *state=vsip_randcreate(4,1,0,VSIP_PRNG);      
      vsip_vview_d *s = vsip_vcreate_d(((M > N) ? N : M),VSIP_MEM_NONE);
      vsip_sv_d *svd = vsip_svd_create_d(M,N,VSIP_SVD_UVFULL,VSIP_SVD_UVFULL);
      vsip_mview_d *A0 = vsip_mcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_vview_d *va0 = vsip_vbind_d(vsip_mgetblock_d(A0),0,1,M*N);
      vsip_mview_d *A = vsip_mcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *U = vsip_mcreate_d(M,M,VSIP_COL,VSIP_MEM_NONE);
      vsip_mview_d *V = vsip_mcreate_d(N,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *B = vsip_mcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_vrandn_d(state,va0);
      vsip_mcopy_d_d(A0,A);
      if(vsip_svd_d(svd,A,s)){
         printf("svd error\n");
         return;
      }
      /* create the singular value matrix */
      vsip_mfill_d(0.0,B);
      for(i=0; i<vsip_vgetlength_d(s); i++) vsip_mput_d(B,i,i,vsip_vget_d(s,i));
      vsip_svdmatu_d(svd, 0, M-1, U);
      vsip_svdmatv_d(svd, 0, N-1, V);
      VU_vprintm_d("12.10",s);
      {  /* check that A0 = U * B * V' */
         vsip_scalar_mi mi;
         vsip_scalar_d chk = 1.0;
         vsip_scalar_d lim = 5 * DBL_EPSILON * fabs(vsip_mmaxmgval_d(A0,&mi));
         vsip_mview_d *dif=vsip_mcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
         vsip_mview_d *out = vsip_mcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
         vsip_mview_d *Vt = vsip_mtransview_d(V);
         vsip_mprod_d(U,B,dif);
         vsip_mprod_d(dif,Vt,out);
         vsip_msub_d(out,A0,dif);
         vsip_mmag_d(dif, dif);
         chk = vsip_msumval_d(dif)/(2 * M * N);
         printf("%20.18e - %20.18e = %e\n",lim,chk, (lim - chk));
         if(chk > lim){
            printf("error\n");
         } else {
            printf("correct\n");
         }
         vsip_malldestroy_d(dif);
         vsip_malldestroy_d(out);
         vsip_mdestroy_d(Vt);
      }
      vsip_randdestroy(state);
      vsip_vdestroy_d(va0);
      vsip_svd_destroy_d(svd);
      vsip_malldestroy_d(A0);
      vsip_malldestroy_d(A);
      vsip_valldestroy_d(s);
      vsip_malldestroy_d(U);
      vsip_malldestroy_d(B);
      vsip_malldestroy_d(V);
   }
   return;
}
