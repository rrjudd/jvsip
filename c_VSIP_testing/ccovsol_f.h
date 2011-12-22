/* Created R Judd */
/* Copyright (c) 2006 Randall Judd */
/* MIT style license, see Copyright notice in top level directory */

int ccovsol_f(void) {
   vsip_cmview_f *A = vsip_cmcreate_f(10,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_f *BX = vsip_cmcreate_f(10,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_f *X = vsip_cmcreate_f(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_f *ANS = vsip_cmcreate_f(6,3,VSIP_ROW,VSIP_MEM_NONE);

   /* create space for ccovsol data */
   vsip_cblock_f *ablock = vsip_cblockcreate_f(500,VSIP_MEM_NONE);
   vsip_cmview_f *A1 = vsip_cmbind_f(ablock,200,-3,10,-31,6);
   vsip_cscalar_f a0 = vsip_cmplx_f(0.0,0.0);
   int i;
   
   vsip_cmfill_f(a0,A);
   vsip_cmfill_f(a0,BX);
   
   printf("********\nTEST ccovsol_f\n");
   printf("Test covariance solver vsip_ccovsol_f\n");
   /* Solving for X in A X = B */
   /* A is (M,N) M >= N; X is (N,K), B is (N,K) */
   
   /* need to make up some data */
   /* data for matrix A */
   for(i=0; i<vsip_cmgetrowlength_f(A); i++){ /* fill by column */
      vsip_cvview_f *ac = vsip_cmcolview_f(A,i);
      vsip_vview_f *ac_r = vsip_vrealview_f(ac);
      vsip_vview_f *ac_i = vsip_vimagview_f(ac);
      vsip_vramp_f(-1.3,1.1,ac_r);
      vsip_vramp_f(+1.3,-1.1,ac_i);
      vsip_vdestroy_f(ac_r); vsip_vdestroy_f(ac_i);
      vsip_cvdestroy_f(ac);
   }
   { /* make sure diagonal keeps things stable */ 
      vsip_cvview_f *ad = vsip_cmdiagview_f(A,0);
      vsip_vview_f *ad_r = vsip_vrealview_f(ad);
      vsip_vview_f *ad_i = vsip_vimagview_f(ad);
      vsip_vramp_f(3,1.2,ad_r);
      vsip_vramp_f(3,-1.2,ad_i);
      vsip_vdestroy_f(ad_r); vsip_vdestroy_f(ad_i);
      vsip_cvdestroy_f(ad);
   }
   /* Data for matrix B */
   for(i=0; i<vsip_cmgetcollength_f(BX); i++){ /* fill by row */
      vsip_cvview_f *bxr = vsip_cmrowview_f(BX,i);
      vsip_vview_f *bxr_r = vsip_vrealview_f(bxr);
      vsip_vview_f *bxr_i = vsip_vimagview_f(bxr);
      vsip_vramp_f(0.1,(vsip_scalar_f)i/3.0,bxr_r);
      vsip_vramp_f(0.1,(vsip_scalar_f)i/4.0,bxr_i);
      vsip_vdestroy_f(bxr_r);vsip_vdestroy_f(bxr_i);
      vsip_cvdestroy_f(bxr);
   }
   printf("Input data \n");
   printf("A = ");VU_cmprintm_f("4.2",A);
   printf("\nB = ");VU_cmprintm_f("4.2",BX);

   {
       vsip_cchol_f *chol = vsip_cchold_create_f(VSIP_TR_LOW,6);
       vsip_cmview_f *B = vsip_cmcreate_f(6,3,VSIP_ROW,VSIP_MEM_NONE);
       vsip_cmview_f *AHA = vsip_cmcreate_f(6,6,VSIP_ROW,VSIP_MEM_NONE);
       vsip_cmview_f *AH = vsip_cmcreate_f(6,10,VSIP_ROW,VSIP_MEM_NONE);
   
       /* solve using Cholesky and AHA matrix */
       printf("\nSolve using Cholesky");
  
       printf("\nA is input matrix, AT (AH) is transpose (Hermitian) of A\n");
       printf("Solve for X least squares using (AH prod A ) prod X = AH prod B\n");
       /* calculate matrix AHA = AH * A */
       vsip_cmherm_f(A,AH);
       vsip_cmprod_f(AH,A,AHA);
       /* calculate AH * B */
       vsip_cmprod_f(AH,BX,X); 
       printf("\nAH prod A = ");VU_cmprintm_f("4.2",AHA);
       printf("\nAH prod B = ");VU_cmprintm_f("4.2",X);
       vsip_cchold_f(chol,AHA);
       vsip_ccholsol_f(chol,X);/* B replaced by X */
       printf("\nX = ");VU_cmprintm_f("7.5",X);
       vsip_cchold_destroy_f(chol);
       /* check */
       printf("\ncheck\n (AH prod A) prod X := AH prod B");
       /* restore AHA */
       vsip_cmprod_f(AH,A,AHA);
       /* calculate AHA prod X */
       vsip_cmprod_f(AHA,X,B);
       vsip_cmcopy_f_f(X,ANS); /* if correct Need ANSwer */
       /* for check place AH * BX into X */
       vsip_cmprod_f(AH,BX, X);
       printf("\nAHA * X ="); VU_cmprintm_f("4.2",B);
       vsip_cmsub_f(X,B,X);
       { 
           float check = (float) vsip_cmmeansqval_f(X);
           if(fabs(check) < .0001)
              printf("check = %f\ncorrect\n",check);
           else
              printf("check = %f\nerror\n",check);
       }
       /* restore X for use by covsol */
       vsip_cmprod_f(AH,BX, X);
       vsip_cmalldestroy_f(B);
       vsip_cmalldestroy_f(AHA);
       vsip_cmalldestroy_f(AH);
    }
   
   /* solve using ccovsol */
   /* copy data so we can solve covariance problem later on */
   vsip_cmcopy_f_f(A,A1);
   printf("\nSolve using ccovsol_f ");
   vsip_ccovsol_f(A1,X);
   printf("Expect X to be\n");VU_cmprintm_f("7.5",ANS);
   printf("\nX = ");VU_cmprintm_f("7.5",X);
   vsip_cmsub_f(ANS,X,X);
   { 
      float check = (float) vsip_cmmeansqval_f(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
   }
   
   vsip_cmdestroy_f(A1);
   vsip_cblockdestroy_f(ablock);
   vsip_cmalldestroy_f(A);
   vsip_cmalldestroy_f(BX);
   vsip_cmalldestroy_f(X);
   return 0;
}
