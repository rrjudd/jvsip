/* Created R Judd */
/* Copyright (c) 2006 Randall Judd */
/* MIT style license, see Copyright notice in top level directory */
/* $Id: llsqsol_f.h,v 1.1 2006/05/16 16:45:18 judd Exp $ */
#include"VU_mprintm_f.include"
static int llsqsol_f(void) {
   vsip_mview_f *A = vsip_mcreate_f(10,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_vview_f *ad = vsip_mdiagview_f(A,0);
   vsip_vview_f *ac = vsip_mcolview_f(A,0);
   vsip_mview_f *AT = vsip_mtransview_f(A);
   
   vsip_mview_f *XB = vsip_mcreate_f(10,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_f *XBs = vsip_msubview_f(XB,0,0,6,3);
   vsip_vview_f *xbc = vsip_mcolview_f(XB,0);
   
   vsip_mview_f *B = vsip_mcreate_f(10,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_f *Bs = vsip_msubview_f(B,0,0,6,3);
   
   vsip_mview_f *X = vsip_mcreate_f(6,3,VSIP_ROW,VSIP_MEM_NONE);
     
   vsip_mview_f *ATA = vsip_mcreate_f(6,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_f *ATXB = vsip_mcreate_f(6,3,VSIP_ROW,VSIP_MEM_NONE);
   
   int i;
   vsip_chol_f *chol = vsip_chold_create_f(VSIP_TR_LOW,6);
   vsip_block_f *ablock = vsip_blockcreate_f(500,VSIP_MEM_NONE);
   vsip_mview_f *A1 = vsip_mbind_f(ablock,200,-3,10,-31,6);
   vsip_mview_f *BX1 = vsip_mbind_f(ablock,203,8,10,2,3);
   vsip_mview_f *BX1s = vsip_msubview_f(BX1,0,0,6,3);
   
   vsip_mfill_f(0.0,A);
   vsip_mfill_f(0.0,XB);

   printf("********\nTEST covsol_f\n");
   printf("\n Test vsip_covsol_f\n");
   /* need to make up some data for A */
   for(i=0; i<6; i++){
      vsip_vputoffset_f(ac,i);
      vsip_vramp_f(-1.3,1.1,ac);
   }
   vsip_vramp_f(3,1.2,ad);
   
   /* need to make up some data for XB */
   for(i=0; i<3; i++){
      vsip_vputoffset_f(xbc,i);
      vsip_vramp_f(.1,(vsip_scalar_f)i/3.0,xbc);
   }

   /* square off A and XB for use with cholesky */
   vsip_mprod_f(AT,A,ATA);
   vsip_mprod_f(AT,XB,ATXB);
   vsip_mcopy_f_f(ATXB, Bs);
   
  /* Copy the original data for use with non-simple matrix */
   vsip_mcopy_f_f(XB,BX1);
   vsip_mcopy_f_f(A,A1);
   
      /* check input data */
   printf("Input Data \n");
   printf("A = ");VU_mprintm_f("4.2",A);
   printf("\nAT * A = ");VU_mprintm_f("4.2",ATA);
   printf("\nXB = ");VU_mprintm_f("4.2",XB);
   printf("\nAT * XB =");VU_mprintm_f("4.2",ATXB);
   
   /* slove using Cholesky and ATA matrix and Bs matrix */
   printf("\nSolve using cholesky and ATA matrix \n (AT * A) X = B \nfor X");
   vsip_chold_f(chol,ATA);
   vsip_cholsol_f(chol,Bs);
   printf("\nX = ");VU_mprintm_f("7.5",Bs);
   
   /* check */
   printf("\ncheck");
   /* the following Restores ATA but chol object is no longer correct */
   vsip_mprod_f(AT,A,ATA);
   vsip_mprod_f(ATA,Bs,X);
   printf("\nATA * X ="); VU_mprintm_f("4.2",X);
   vsip_msub_f(ATXB,X,X);
   { 
      float check = (float) vsip_msumval_f(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
    }

   /* slove using llsqsol and A, XB matrix */
   printf("\nSolve\n (AT * A) X = B \nfor X");
   vsip_llsqsol_f(A,XB);
   printf("\nXBs = ");VU_mprintm_f("7.5",XBs);
   vsip_msub_f(Bs,XBs,X);
   { 
      float check = (float) vsip_msumval_f(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
    }
   
   /* slove using llsqsol and A1,BX1 inputs */
   printf("\nSolve nonstandard stride _f \n (AT * A) X = B \nfor X");
   vsip_llsqsol_f(A1,BX1);
   vsip_mcopy_f_f(BX1s,X);
   printf("\nX = ");VU_mprintm_f("7.5",X);
   vsip_msub_f(Bs,BX1s,X);
   { 
      float check = (float) vsip_msumval_f(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
   }
   

   vsip_mdestroy_f(A1);
   vsip_mdestroy_f(BX1);
   vsip_mdestroy_f(BX1s);
   vsip_blockdestroy_f(ablock);
   
   vsip_vdestroy_f(ad);
   vsip_vdestroy_f(ac);
   vsip_vdestroy_f(xbc);
   vsip_mdestroy_f(AT);
   vsip_malldestroy_f(A);
   
   vsip_mdestroy_f(XBs);
   vsip_malldestroy_f(XB);
   
   vsip_malldestroy_f(X);
   
   vsip_mdestroy_f(Bs);
   vsip_malldestroy_f(B);
   
   vsip_malldestroy_f(ATA);
   vsip_malldestroy_f(ATXB);
   vsip_chold_destroy_f(chol);
   
   return 0;
}
