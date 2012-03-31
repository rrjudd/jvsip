/*
 *  svd7_d.h
 *
 *  Created by Randall Judd on 10/03/08.
 *  Copyright 2008 Home. All rights reserved.
 *
 */

#include"VU_mprintm_d.include"
#include"VU_vprintm_d.include"
static void svd7_d(void){
   printf("********\nTEST svd7 for double\n");
   {
      vsip_index i;
      vsip_length M=9, N=9;
      vsip_scalar_d data[81] = { \
          8.96933746, -2.73806572, 1.43051147e-06, 0, 0, 0, -24.4797363, -0.863142371, 1.43051147e-06,\
         -2.73806572, 1.62158346, -1.43051147e-06, 0, 0, 0, 7.47291851, 0.511184692, -1.43051147e-06,\
         1.43051147e-06, -1.43051147e-06, 4, 0, 0, 0, -3.33786011e-06, -4.47034836e-07, 3.90333748,\
         0, 0, 0, 8.96933746, -2.73806572, 1.43051147e-06, 1.85705733, 1.05920994, 1.1920929e-07,\
         0, 0, 0, -2.73806572, 1.62158346, -1.43051147e-06, -0.566903055, -0.627303123, -1.04308128e-07,\
         0, 0, 0, 1.43051147e-06, -1.43051147e-06, 4, 2.98023224e-07, 5.66244125e-07, 0.295684814,\
         -24.4797363, 7.47291851, -3.33786011e-06, 1.85705733, -0.566903055, 2.98023224e-07, 67.1962814, 2.57505178, -3.81469727e-06,\
         -0.863142371, 0.511184692, -4.47034836e-07, 1.05920994, -0.627303123, 5.66244125e-07, 2.57505178, 0.403814614, -4.17232513e-07,\
         1.43051147e-06, -1.43051147e-06, 3.90333748, 1.1920929e-07, -1.04308128e-07, 0.295684814, -3.81469727e-06, -4.17232513e-07, 3.83086824 };
      
      vsip_vview_d *s = vsip_vcreate_d(((M > N) ? N : M),VSIP_MEM_NONE);
      vsip_sv_d *svd = vsip_svd_create_d(M,N,VSIP_SVD_UVFULL,VSIP_SVD_UVFULL);
      
      vsip_block_d *block = vsip_blockbind_d(data,(M * N),VSIP_MEM_NONE);
      vsip_mview_d *A0 = vsip_mbind_d(block,0,1,M,M,N);
      vsip_block_d *vblk = vsip_blockcreate_d(600,VSIP_MEM_NONE);
      vsip_mview_d *A = vsip_mbind_d(vblk,3,3, M,3*M , N);
      vsip_mview_d *U = vsip_mcreate_d(M,M,VSIP_COL,VSIP_MEM_NONE);
      vsip_mview_d *V = vsip_mcreate_d(N,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *B = vsip_mcreate_d(M,N,VSIP_ROW,VSIP_MEM_NONE);
      vsip_blockadmit_d(block,VSIP_TRUE);
      vsip_mcopy_d_d(A0,A);
      printf("in = ");VU_mprintm_d("6.3",A);
      if(vsip_svd_d(svd,A,s)){
         printf("svd error\n");
         return;
      }
      /* create the singular value matrix */
      vsip_mfill_d(0.0,B);
      for(i=0; i<vsip_vgetlength_d(s); i++) vsip_mput_d(B,i,i,vsip_vget_d(s,i));
      vsip_svdmatu_d(svd, 0, M-1, U);
      vsip_svdmatv_d(svd, 0, N-1, V);
      printf("U = ");VU_mprintm_d("12.10",U);
      printf("B = ");VU_mprintm_d("12.10",B);
      printf("V = ");VU_mprintm_d("12.10",V);
      VU_vprintm_d("12.10",s);
      {  /* check that A0 = U * B * V' */
         vsip_scalar_mi mi;
         vsip_scalar_d chk = 1.0;
         vsip_scalar_d lim = 5 * FLT_EPSILON * fabs(vsip_mmaxmgval_d(A0,&mi));
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
