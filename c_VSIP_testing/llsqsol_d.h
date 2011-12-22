/* Created R Judd */
/* Copyright (c) 2006 Randall Judd */
/* MIT style license, see Copyright notice in top level directory */
/* $Id: llsqsol_d.h,v 1.1 2006/05/16 16:45:18 judd Exp $ */

int llsqsol_d(void) {
   vsip_mview_d *A = vsip_mcreate_d(10,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_vview_d *ad = vsip_mdiagview_d(A,0);
   vsip_vview_d *ac = vsip_mcolview_d(A,0);
   vsip_mview_d *AT = vsip_mtransview_d(A);
   
   vsip_mview_d *XB = vsip_mcreate_d(10,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_d *XBs = vsip_msubview_d(XB,0,0,6,3);
   vsip_vview_d *xbc = vsip_mcolview_d(XB,0);
   
   vsip_mview_d *B = vsip_mcreate_d(10,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_d *Bs = vsip_msubview_d(B,0,0,6,3);
   
   vsip_mview_d *X = vsip_mcreate_d(6,3,VSIP_ROW,VSIP_MEM_NONE);
     
   vsip_mview_d *ATA = vsip_mcreate_d(6,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_d *ATXB = vsip_mcreate_d(6,3,VSIP_ROW,VSIP_MEM_NONE);
   
   int i;
   vsip_chol_d *chol = vsip_chold_create_d(VSIP_TR_LOW,6);
   vsip_block_d *ablock = vsip_blockcreate_d(500,VSIP_MEM_NONE);
   vsip_mview_d *A1 = vsip_mbind_d(ablock,200,-3,10,-31,6);
   vsip_mview_d *BX1 = vsip_mbind_d(ablock,203,8,10,2,3);
   vsip_mview_d *BX1s = vsip_msubview_d(BX1,0,0,6,3);
   
   vsip_mfill_d(0.0,A);
   vsip_mfill_d(0.0,XB);

   printf("********\nTEST covsol_d\n");
   printf("\n Test vsip_covsol_d\n");
   /* need to make up some data for A */
   for(i=0; i<6; i++){
      vsip_vputoffset_d(ac,i);
      vsip_vramp_d(-1.3,1.1,ac);
   }
   vsip_vramp_d(3,1.2,ad);
   
   /* need to make up some data for XB */
   for(i=0; i<3; i++){
      vsip_vputoffset_d(xbc,i);
      vsip_vramp_d(.1,(vsip_scalar_d)i/3.0,xbc);
   }

   /* square off A and XB for use with cholesky */
   vsip_mprod_d(AT,A,ATA);
   vsip_mprod_d(AT,XB,ATXB);
   vsip_mcopy_d_d(ATXB, Bs);
   
  /* Copy the original data for use with non-simple matrix */
   vsip_mcopy_d_d(XB,BX1);
   vsip_mcopy_d_d(A,A1);
   
      /* check input data */
   printf("Input Data \n");
   printf("A = ");VU_mprintm_d("4.2",A);
   printf("\nAT * A = ");VU_mprintm_d("4.2",ATA);
   printf("\nXB = ");VU_mprintm_d("4.2",XB);
   printf("\nAT * XB =");VU_mprintm_d("4.2",ATXB);
   
   /* slove using Cholesky and ATA matrix and Bs matrix */
   printf("\nSolve using cholesky and ATA matrix \n (AT * A) X = B \nfor X");
   vsip_chold_d(chol,ATA);
   vsip_cholsol_d(chol,Bs);
   printf("\nX = ");VU_mprintm_d("7.5",Bs);
   
   /* check */
   printf("\ncheck");
   /* the following Restores ATA but chol object is no longer correct */
   vsip_mprod_d(AT,A,ATA);
   vsip_mprod_d(ATA,Bs,X);
   printf("\nATA * X ="); VU_mprintm_d("4.2",X);
   vsip_msub_d(ATXB,X,X);
   { 
      float check = (float) vsip_msumval_d(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
    }

   /* slove using llsqsol and A, XB matrix */
   printf("\nSolve\n (AT * A) X = B \nfor X");
   vsip_llsqsol_d(A,XB);
   printf("\nXBs = ");VU_mprintm_d("7.5",XBs);
   vsip_msub_d(Bs,XBs,X);
   { 
      float check = (float) vsip_msumval_d(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
    }
   
   /* slove using llsqsol and A1,BX1 inputs */
   printf("\nSolve nonstandard stride _d \n (AT * A) X = B \nfor X");
   vsip_llsqsol_d(A1,BX1);
   vsip_mcopy_d_d(BX1s,X);
   printf("\nX = ");VU_mprintm_d("7.5",X);
   vsip_msub_d(Bs,BX1s,X);
   { 
      float check = (float) vsip_msumval_d(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
   }
   

   vsip_mdestroy_d(A1);
   vsip_mdestroy_d(BX1);
   vsip_mdestroy_d(BX1s);
   vsip_blockdestroy_d(ablock);
   
   vsip_vdestroy_d(ad);
   vsip_vdestroy_d(ac);
   vsip_vdestroy_d(xbc);
   vsip_mdestroy_d(AT);
   vsip_malldestroy_d(A);
   
   vsip_mdestroy_d(XBs);
   vsip_malldestroy_d(XB);
   
   vsip_malldestroy_d(X);
   
   vsip_mdestroy_d(Bs);
   vsip_malldestroy_d(B);
   
   vsip_malldestroy_d(ATA);
   vsip_malldestroy_d(ATXB);
   vsip_chold_destroy_d(chol);
   
   return 0;
}
