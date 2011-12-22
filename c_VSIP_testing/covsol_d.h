/* Created R Judd */
/* Copyright (c) 2006 Randall Judd */
/* MIT style license, see Copyright notice in top level directory */
/* $Id: covsol_d.h,v 1.2 2006/05/16 16:45:18 judd Exp $ */

int covsol_d(void) {
   vsip_mview_d *A = vsip_mcreate_d(10,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_d *BX = vsip_mcreate_d(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_d *B = vsip_mcreate_d(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_d *X = vsip_mcreate_d(6,3,VSIP_ROW,VSIP_MEM_NONE);
   vsip_vview_d *ad = vsip_mdiagview_d(A,0);
   vsip_vview_d *ac = vsip_mcolview_d(A,0);
   vsip_vview_d *bxr = vsip_mrowview_d(BX,0);
   vsip_mview_d *ATA = vsip_mcreate_d(6,6,VSIP_ROW,VSIP_MEM_NONE);
   vsip_mview_d *AT = vsip_mtransview_d(A);
   int i;
   vsip_chol_d *chol = vsip_chold_create_d(VSIP_TR_LOW,6);
   vsip_block_d *ablock = vsip_blockcreate_d(500,VSIP_MEM_NONE);
   vsip_mview_d *A1 = vsip_mbind_d(ablock,200,-3,10,-31,6);
   vsip_mview_d *BX1 = vsip_mbind_d(ablock,203,8,6,2,3);
   
   vsip_mfill_d(0.0,A);
   vsip_mfill_d(0.0,BX);
   vsip_mfill_d(0.0,ATA);
   printf("********\nTEST covsol_d\n");
   printf("\n Test vsip_covsol_d\n");
   /* need to make up some data */
   for(i=0; i<6; i++){
      vsip_vputoffset_d(ac,i);
      vsip_vputoffset_d(bxr,i*3);
      vsip_vramp_d(.1,(vsip_scalar_d)i/3.0,bxr);
      vsip_vramp_d(-1.3,1.1,ac);
   }
   vsip_vramp_d(3,1.2,ad);
   vsip_mprod_d(AT,A,ATA);
   vsip_mcopy_d_d(BX,B);
   vsip_mcopy_d_d(BX,BX1);
   vsip_mcopy_d_d(A,A1);
   
      /* check input data */
   printf("Input Data \n");
   printf("A = ");VU_mprintm_d("4.2",A);
   printf("\nAT * A = ");VU_mprintm_d("4.2",ATA);
   printf("\nB = ");VU_mprintm_d("4.2",B);
   
   /* slove using Cholesky and ATA matrix */
   printf("\nSolve using cholesky and ATA matrix \n (AT * A) X = B \nfor X");
   vsip_chold_d(chol,ATA);
   vsip_cholsol_d(chol,BX);
   vsip_mcopy_d_d(BX,X);
   printf("\nX = ");VU_mprintm_d("7.5",X);
   
   /* check */
   printf("\ncheck");
   vsip_mprod_d(AT,A,ATA);
   vsip_mprod_d(ATA,X,BX);
   printf("\nATA * X ="); VU_mprintm_d("4.2",BX);
   vsip_msub_d(B,BX,X);
   { 
      float check = (float) vsip_msumval_d(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
    }
   
   /* slove using covsol and A matrix*/
   vsip_mcopy_d_d(B,BX); /* restore BX */
   printf("\nSolve\n (AT * A) X = B \nfor X");
   vsip_covsol_d(A,BX);
   vsip_mcopy_d_d(BX,X);
   printf("\nX = ");VU_mprintm_d("7.5",X);
   vsip_mprod_d(ATA,X,BX);
   printf("\nATA * X ="); VU_mprintm_d("4.2",BX);
   vsip_msub_d(B,BX,X);
   { 
      float check = (float) vsip_msumval_d(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
    }
   
   /* slove using covsol and A1,BX1 inputs */
   printf("\nSolve nonstandard stride _d \n (AT * A) X = B \nfor X");
   vsip_covsol_d(A1,BX1);
   vsip_mcopy_d_d(BX1,X);
   printf("\nX = ");VU_mprintm_d("7.5",X);
   vsip_mprod_d(ATA,X,BX);
   printf("\nATA * X ="); VU_mprintm_d("4.2",BX);
   vsip_msub_d(B,BX,X);
   { 
      float check = (float) vsip_msumval_d(X);
      if(fabs(check) < .0001)
         printf("check = %f\ncorrect\n",check);
      else
         printf("check = %f\nerror\n",check);
   }
   

   vsip_mdestroy_d(A1);
   vsip_mdestroy_d(BX1);
   vsip_blockdestroy_d(ablock);
   vsip_vdestroy_d(ad);
   vsip_vdestroy_d(ac);
   vsip_vdestroy_d(bxr);
   vsip_mdestroy_d(AT);
   vsip_malldestroy_d(A);
   vsip_malldestroy_d(BX);
   vsip_malldestroy_d(X);
   vsip_malldestroy_d(B);
   vsip_malldestroy_d(ATA);
   vsip_chold_destroy_d(chol);
   
   return 0;
}
