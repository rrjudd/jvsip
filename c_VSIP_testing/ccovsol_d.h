/* Created R Judd */
/* Copyright (c) 2006 Randall Judd */
/* MIT style license, see Copyright notice in top level directory */
/* $Id: ccovsol_d.h,v 1.2 2006/05/16 16:45:18 judd Exp $ */

int ccovsol_d(void) {
   vsip_cmview_d *A = vsip_cmcreate_d(10,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_d *BX = vsip_cmcreate_d(10,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_d *X = vsip_cmcreate_d(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_cmview_d *ANS = vsip_cmcreate_d(6,3,VSIP_ROW,VSIP_MEM_NONE);

   /* create space for ccovsol data */
   vsip_cblock_d *ablock = vsip_cblockcreate_d(500,VSIP_MEM_NONE);
   vsip_cmview_d *A1 = vsip_cmbind_d(ablock,200,-3,10,-31,6);
   vsip_cscalar_d a0 = vsip_cmplx_d(0.0,0.0);
   int i;
   
   vsip_cmfill_d(a0,A);
   vsip_cmfill_d(a0,BX);
   
   printf("********\nTEST ccovsol_d\n");
   printf("Test covariance solver vsip_ccovsol_d\n");
   /* Solving for X in A X = B */
   /* A is (M,N) M >= N; X is (N,K), B is (N,K) */
   
   /* need to make up some data */
   /* data for matrix A */
   for(i=0; i<vsip_cmgetrowlength_d(A); i++){ /* fill by column */
      vsip_cvview_d *ac = vsip_cmcolview_d(A,i);
      vsip_vview_d *ac_r = vsip_vrealview_d(ac);
      vsip_vview_d *ac_i = vsip_vimagview_d(ac);
      vsip_vramp_d(-1.3,1.1,ac_r);
      vsip_vramp_d(+1.3,-1.1,ac_i);
      vsip_vdestroy_d(ac_r); vsip_vdestroy_d(ac_i);
      vsip_cvdestroy_d(ac);
   }
   { /* make sure diagonal keeps things stable */ 
      vsip_cvview_d *ad = vsip_cmdiagview_d(A,0);
      vsip_vview_d *ad_r = vsip_vrealview_d(ad);
      vsip_vview_d *ad_i = vsip_vimagview_d(ad);
      vsip_vramp_d(3,1.2,ad_r);
      vsip_vramp_d(3,-1.2,ad_i);
      vsip_vdestroy_d(ad_r); vsip_vdestroy_d(ad_i);
      vsip_cvdestroy_d(ad);
   }
   /* Data for matrix B */
   for(i=0; i<vsip_cmgetcollength_d(BX); i++){ /* fill by row */
      vsip_cvview_d *bxr = vsip_cmrowview_d(BX,i);
      vsip_vview_d *bxr_r = vsip_vrealview_d(bxr);
      vsip_vview_d *bxr_i = vsip_vimagview_d(bxr);
      vsip_vramp_d(0.1,(vsip_scalar_d)i/3.0,bxr_r);
      vsip_vramp_d(0.1,(vsip_scalar_d)i/4.0,bxr_i);
      vsip_vdestroy_d(bxr_r);vsip_vdestroy_d(bxr_i);
      vsip_cvdestroy_d(bxr);
   }
   printf("Input data \n");
   printf("A = ");VU_cmprintm_d("4.2",A);
   printf("\nB = ");VU_cmprintm_d("4.2",BX);

   {
       vsip_cchol_d *chol = vsip_cchold_create_d(VSIP_TR_LOW,6);
       vsip_cmview_d *B = vsip_cmcreate_d(6,3,VSIP_ROW,VSIP_MEM_NONE);
       vsip_cmview_d *AHA = vsip_cmcreate_d(6,6,VSIP_ROW,VSIP_MEM_NONE);
       vsip_cmview_d *AH = vsip_cmcreate_d(6,10,VSIP_ROW,VSIP_MEM_NONE);
   
       /* solve using Cholesky and AHA matrix */
       printf("\nSolve using Cholesky");
  
       printf("\nA is input matrix, AT (AH) is transpose (Hermitian) of A\n");
       printf("Solve for X least squares using (AH prod A ) prod X = AH prod B\n");
       /* calculate matrix AHA = AH * A */
       vsip_cmherm_d(A,AH);
       vsip_cmprod_d(AH,A,AHA);
       /* calculate AH * B */
       vsip_cmprod_d(AH,BX,X); 
       printf("\nAH prod A = ");VU_cmprintm_d("4.2",AHA);
       printf("\nAH prod B = ");VU_cmprintm_d("4.2",X);
       vsip_cchold_d(chol,AHA);
       vsip_ccholsol_d(chol,X);/* B replaced by X */
       printf("\nX = ");VU_cmprintm_d("7.5",X);
       vsip_cchold_destroy_d(chol);
       /* check */
       printf("\ncheck\n (AH prod A) prod X := AH prod B");
       /* restore AHA */
       vsip_cmprod_d(AH,A,AHA);
       /* calculate AHA prod X */
       vsip_cmprod_d(AHA,X,B);
       vsip_cmcopy_d_d(X,ANS); /* if correct Need ANSwer */
       /* for check place AH * BX into X */
       vsip_cmprod_d(AH,BX, X);
       printf("\nAHA * X ="); VU_cmprintm_d("4.2",B);
       vsip_cmsub_d(X,B,X);
       { 
           float check = (float) vsip_cmmeansqval_d(X);
           if(fabs(check) < .0001)
              printf("check = %f\ncorrect\n",check);
           else
              printf("check = %f\nerror\n",check);
       }
       /* restore X for use by covsol */
       vsip_cmprod_d(AH,BX, X);
       vsip_cmalldestroy_d(B);
       vsip_cmalldestroy_d(AHA);
       vsip_cmalldestroy_d(AH);
    }
   
   /* solve using ccovsol */
   /* copy data so we can solve covariance problem later on */
   vsip_cmcopy_d_d(A,A1);
   printf("\nSolve using ccovsol_d ");
   vsip_ccovsol_d(A1,X);
   printf("Expect X to be\n");VU_cmprintm_d("7.5",ANS);
   printf("\nX = ");VU_cmprintm_d("7.5",X);
   vsip_cmsub_d(ANS,X,X);
   { 
      float check = (float) vsip_cmmeansqval_d(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
   }
   
   vsip_cmdestroy_d(A1);
   vsip_cblockdestroy_d(ablock);
   vsip_cmalldestroy_d(A);
   vsip_cmalldestroy_d(BX);
   vsip_cmalldestroy_d(X);
   return 0;
}
