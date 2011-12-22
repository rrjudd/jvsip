/*
 *  svd5_f.h
 *  VSIP_svd_fev
 *
 *  Created by Randall Judd on 9/13/08.
 *  Copyright 2008 Home. All rights reserved.
 *
 */

static void svd5_f(void){
   printf("********\nTEST svd5 for float\n");
   {
      vsip_index i;
      vsip_length M=3, N=10;
      vsip_scalar_f data[30] = {0,  0, 0, 0, \
         0, 0, 0, 0, \
         0,  0, 0, 1, \
         0,  0, 0, 100,\
         0, 0, 1, 0, \
      1,0,0,1,0,0,0,0,0,0};
      
      vsip_vview_f *s = vsip_vcreate_f(((M > N) ? N : M),VSIP_MEM_NONE);
      vsip_sv_f *svd = vsip_svd_create_f(M,N,VSIP_SVD_UVFULL,VSIP_SVD_UVFULL);
      
      vsip_block_f *block = vsip_blockbind_f(data,(M * N),VSIP_MEM_NONE);
      vsip_mview_f *A0 = vsip_mbind_f(block,0,1,M,M,N);
      vsip_block_f *vblk = vsip_blockcreate_f(600,VSIP_MEM_NONE);
      vsip_mview_f *A = vsip_mbind_f(vblk,3,3, M,3*M , N);
      vsip_mview_f *U = vsip_mcreate_f(M,M,VSIP_COL,VSIP_MEM_NONE);
      vsip_mview_f *V = vsip_mcreate_f(N,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_f *B = vsip_mcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_blockadmit_f(block,VSIP_TRUE);
      vsip_mcopy_f_f(A0,A);
      printf("in = ");VU_mprintm_f("6.3",A);
      if(vsip_svd_f(svd,A,s)){
         printf("svd error\n");
         return;
      }
      /* create the singular value matrix */
      vsip_mfill_f(0.0,B);
      for(i=0; i<vsip_vgetlength_f(s); i++) vsip_mput_f(B,i,i,vsip_vget_f(s,i));
      vsip_svdmatu_f(svd, 0, M-1, U);
      vsip_svdmatv_f(svd, 0, N-1, V);
      printf("U = ");VU_mprintm_f("12.10",U);
      printf("B = ");VU_mprintm_f("12.10",B);
      printf("V = ");VU_mprintm_f("12.10",V);
      VU_vprintm_f("12.10",s);
      {  /* check that A0 = U * B * V' */
         vsip_scalar_mi mi;
         vsip_scalar_f chk = 1.0;
         vsip_scalar_f lim = 5 * FLT_EPSILON * fabs(vsip_mmaxmgval_f(A0,&mi));
         vsip_mview_f *dif=vsip_mcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
         vsip_mview_f *out = vsip_mcreate_f(M,N,VSIP_ROW,VSIP_MEM_NONE);
         vsip_mview_f *Vt = vsip_mtransview_f(V);
         vsip_mprod_f(U,B,dif);
         vsip_mprod_f(dif,Vt,out);
         vsip_msub_f(out,A0,dif);
         vsip_mmag_f(dif, dif);
         chk = vsip_msumval_f(dif)/(2 * M * N);
         printf("%20.18e - %20.18e = %e\n",lim,chk, (lim - chk));
         if(chk > lim){
            printf("error\n");
         } else {
            printf("correct\n");
         }
         vsip_malldestroy_f(dif);
         vsip_malldestroy_f(out);
         vsip_mdestroy_f(Vt);
      }
      vsip_svd_destroy_f(svd);
      vsip_malldestroy_f(A0);
      vsip_malldestroy_f(A);
      vsip_valldestroy_f(s);
      vsip_malldestroy_f(U);
      vsip_malldestroy_f(B);
      vsip_malldestroy_f(V);
   }
   return;
}
