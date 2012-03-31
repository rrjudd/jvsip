/* Created R Judd */
/* Copyright (c) 2006 Randall Judd */
/* MIT style license, see Copyright notice in top level directory */
/* $Id: covsol_f.h,v 1.2 2006/05/16 16:45:18 judd Exp $ */
#include"VU_mprintm_f.include"
static int covsol_f(void) {
   vsip_mview_f *A = vsip_mcreate_f(10,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_f *BX = vsip_mcreate_f(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_f *B = vsip_mcreate_f(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_f *X = vsip_mcreate_f(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_vview_f *ad = vsip_mdiagview_f(A,0);
   vsip_vview_f *ac = vsip_mcolview_f(A,0);
   vsip_vview_f *bxr = vsip_mrowview_f(BX,0);
   vsip_mview_f *ATA = vsip_mcreate_f(6,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_f *AT = vsip_mtransview_f(A);
   int i;
   vsip_chol_f *chol = vsip_chold_create_f(VSIP_TR_LOW,6);
   vsip_block_f *ablock = vsip_blockcreate_f(500,VSIP_MEM_NONE);
   vsip_mview_f *A1 = vsip_mbind_f(ablock,200,-3,10,-31,6);
   vsip_mview_f *BX1 = vsip_mbind_f(ablock,203,8,6,2,3);
   
   vsip_mfill_f(0.0,A);
   vsip_mfill_f(0.0,BX);
   vsip_mfill_f(0.0,ATA);
   printf("********\nTEST covsol_f\n");
   printf("\n Test vsip_covsol_f\n");
   /* need to make up some data */
   for(i=0; i<6; i++){
      vsip_vputoffset_f(ac,i);
      vsip_vputoffset_f(bxr,i*3);
      vsip_vramp_f(.1,(vsip_scalar_f)i/3.0,bxr);
      vsip_vramp_f(-1.3,1.1,ac);
   }
   vsip_vramp_f(3,1.2,ad);
   vsip_mprod_f(AT,A,ATA);
   vsip_mcopy_f_f(BX,B);
   vsip_mcopy_f_f(BX,BX1);
   vsip_mcopy_f_f(A,A1);
   
      /* check input data */
   printf("Input Data \n");
   printf("A = ");VU_mprintm_f("4.2",A);
   printf("\nAT * A = ");VU_mprintm_f("4.2",ATA);
   printf("\nB = ");VU_mprintm_f("4.2",B);
   
   /* slove using Cholesky and ATA matrix */
   printf("\nSolve using cholesky and ATA matrix \n (AT * A) X = B \nfor X");
   vsip_chold_f(chol,ATA);
   vsip_cholsol_f(chol,BX);
   vsip_mcopy_f_f(BX,X);
   printf("\nX = ");VU_mprintm_f("7.5",X);
   
   /* check */
   printf("\ncheck");
   vsip_mprod_f(AT,A,ATA);
   vsip_mprod_f(ATA,X,BX);
   printf("\nATA * X ="); VU_mprintm_f("4.2",BX);
   vsip_msub_f(B,BX,X);
   { 
      float check = (float) vsip_msumval_f(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
    }
   
   /* slove using covsol and A matrix*/
   vsip_mcopy_f_f(B,BX); /* restore BX */
   printf("\nSolve\n (AT * A) X = B \nfor X");
   vsip_covsol_f(A,BX);
   vsip_mcopy_f_f(BX,X);
   printf("\nX = ");VU_mprintm_f("7.5",X);
   vsip_mprod_f(ATA,X,BX);
   printf("\nATA * X ="); VU_mprintm_f("4.2",BX);
   vsip_msub_f(B,BX,X);
   { 
      float check = (float) vsip_msumval_f(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
    }
   
   /* slove using covsol and A1,BX1 inputs */
   printf("\nSolve nonstandard stride _f \n (AT * A) X = B \nfor X");
   vsip_covsol_f(A1,BX1);
   vsip_mcopy_f_f(BX1,X);
   printf("\nX = ");VU_mprintm_f("7.5",X);
   vsip_mprod_f(ATA,X,BX);
   printf("\nATA * X ="); VU_mprintm_f("4.2",BX);
   vsip_msub_f(B,BX,X);
   { 
      float check = (float) vsip_msumval_f(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
   }
   

   vsip_mdestroy_f(A1);
   vsip_mdestroy_f(BX1);
   vsip_blockdestroy_f(ablock);
   vsip_vdestroy_f(ad);
   vsip_vdestroy_f(ac);
   vsip_vdestroy_f(bxr);
   vsip_mdestroy_f(AT);
   vsip_malldestroy_f(A);
   vsip_malldestroy_f(BX);
   vsip_malldestroy_f(X);
   vsip_malldestroy_f(B);
   vsip_malldestroy_f(ATA);
   vsip_chold_destroy_f(chol);
   
   return 0;
}
