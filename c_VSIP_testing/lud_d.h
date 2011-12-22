/* Created RJudd */
/* SPAWARSYSCEN D857 */
/**********************************************************************
// For TASP VSIPL Documentation and Code neither the United States    /
// Government, the United States Navy, nor any of their employees,    /
// makes any warranty, express or implied, including the warranties   /
// of merchantability and fitness for a particular purpose, or        /
// assumes any legal liability or responsibility for the accuracy,    /
// completeness, or usefulness of any information, apparatus,         /
// product, or process disclosed, or represents that its use would    /
// not infringe privately owned rights                                /
**********************************************************************/
/* $Id: lud_d.h,v 2.0 2003/02/22 15:23:14 judd Exp $ */
static void lud_d(void){
   printf("********\nTEST lud_d\n");
   {
      vsip_index i,j;
      /* make up some data space and views */
      vsip_block_d *block = vsip_blockcreate_d(500,VSIP_MEM_NONE);
      vsip_mview_d *AC = vsip_mbind_d(block,0,6,6,1,6);
      vsip_mview_d *AG = vsip_mbind_d(block,36,2,6,18,6);
      vsip_mview_d *IC = vsip_mbind_d(block,150,1,6,6,6);
      vsip_mview_d *IG = vsip_mbind_d(block,200,2,6,14,6);
      vsip_mview_d *B = vsip_mbind_d(block,300,6,6,1,6);
      vsip_mview_d *A = vsip_mbind_d(block,350,6,6,1,6);
      vsip_mview_d *X = vsip_mbind_d(block,400,5,6,1,3);
      vsip_mview_d *Y = vsip_mbind_d(block,450,3,6,1,3);
      vsip_lu_d* ludC = vsip_lud_create_d(6);
      vsip_lu_d* ludG = vsip_lud_create_d(6);
      vsip_mview_d *AT = vsip_mtransview_d(A);

      vsip_scalar_d chk;
      
      vsip_scalar_d data[6][6] = { \
        {0.50,     7.00,    10.00,    12.00,    -3.00,     0.00}, \
        {2.00,    13.00,    18.00,     6.00,     0.00,   130.00}, \
        {3.00,    -9.00,     2.00,     3.00,     2.00,    -9.00}, \
        {4.00,     2.00,     2.00,     4.00,     1.00,     2.00}, \
        {0.20,     2.00,     9.00,     4.00,     1.00,     2.00}, \
        {0.10,     2.00,     0.30,     4.00,     1.00,     2.00}};

      vsip_scalar_d ydata[6][3] = { \
     {  77.85,   155.70,   311.40}, \
     { 942.00,  1884.00,  3768.00}, \
     {   1.00,     2.00,     4.00}, \
     {  68.00,   136.00,   272.00}, \
     {  85.20,   170.40,   340.80}, \
     {  59.00,   118.00,   236.00}};
                  
      vsip_scalar_d Ident[6][6] = { \
                 {1, 0, 0, 0, 0, 0}, \
                 {0, 1, 0, 0, 0, 0}, \
                 {0, 0, 1, 0, 0, 0}, \
                 {0, 0, 0, 1, 0, 0}, \
                 {0, 0, 0, 0, 1, 0}, \
                 {0, 0, 0, 0, 0, 1}};

      for(i=0; i<6; i++){
         for(j=0; j<6; j++){
            vsip_mput_d(A, i,j,data[i][j]);
            vsip_mput_d(AC,i,j,data[i][j]);
            vsip_mput_d(AG,i,j,data[i][j]);
            vsip_mput_d(IC,i,j,Ident[i][j]);
            vsip_mput_d(IG,i,j,Ident[i][j]);
         }
      }
      for(i=0; i<6; i++)
         for(j=0; j<3; j++)
            vsip_mput_d(X,i,j,ydata[i][j]);

      printf("Matrix A = \n");VU_mprintm_d("7.2",A);fflush(stdout);
      vsip_lud_d(ludC,AC); vsip_lud_d(ludG,AG);
      printf("vsip_lusol(lud,VSIP_MAT_NTRANS,X)\n");
      printf("Solve A X = I \n"); fflush(stdout);
      vsip_lusol_d(ludC,VSIP_MAT_NTRANS,IC);
      vsip_lusol_d(ludG,VSIP_MAT_NTRANS,IG);
      printf("for compact case X = \n");VU_mprintm_d("8.4",IC); fflush(stdout);
      printf("for general case X = \n");VU_mprintm_d("8.4",IG); fflush(stdout);
      chk = 0;
      for(i=0; i<6; i++)
          for(j=0; j<6; j++)
              chk += fabs(vsip_mget_d(IC,i,j) - vsip_mget_d(IG,i,j));
      (chk > .01) ? printf("error\n") : printf("agree\n"); fflush(stdout);

      vsip_mprod_d(A,IC,B);

      chk = 0;
      for(i=0; i<6; i++)
          for(j=0; j<6; j++)
              chk += fabs(vsip_mget_d(B,i,j) - Ident[i][j]);
      vsip_mprod_d(A,IG,B);
      for(i=0; i<6; i++)
          for(j=0; j<6; j++)
              chk += fabs(vsip_mget_d(B,i,j) - Ident[i][j]);
      printf("mprod(A,X) = \n"); VU_mprintm_d("8.3",B); fflush(stdout);
      (chk > .01) ? printf("error\n") : printf("correct\n"); fflush(stdout);

/************************************************/
      /* check case VSIP_MAT_TRANS */
      printf("Matrix Transpose A = \n");VU_mprintm_d("7.2",AT);fflush(stdout);
      for(i=0; i<6; i++){
         for(j=0; j<6; j++){
            vsip_mput_d(IC,i,j,Ident[i][j]);
            vsip_mput_d(IG,i,j,Ident[i][j]);
         }
      }
      
      printf("vsip_lusol(lud,VSIP_MAT_TRANS,X)\n");
      printf("Solve trans(A) X = I \n"); fflush(stdout);
      vsip_lusol_d(ludC,VSIP_MAT_TRANS,IC);
      vsip_lusol_d(ludG,VSIP_MAT_TRANS,IG);
      printf("for compact case X = \n");VU_mprintm_d("8.4",IC); fflush(stdout);
      printf("for general case X = \n");VU_mprintm_d("8.4",IG); fflush(stdout);
      chk = 0;
      for(i=0; i<6; i++)
          for(j=0; j<6; j++)
              chk += fabs(vsip_mget_d(IC,i,j) - vsip_mget_d(IG,i,j));
      (chk > .01) ? printf("error\n") : printf("agree\n"); fflush(stdout);

      vsip_mprod_d(AT,IC,B);

      chk = 0;
      for(i=0; i<6; i++)
          for(j=0; j<6; j++)
              chk += fabs(vsip_mget_d(B,i,j) - Ident[i][j]);

      vsip_mprod_d(AT,IG,B);
      for(i=0; i<6; i++)
          for(j=0; j<6; j++)
              chk += fabs(vsip_mget_d(B,i,j) - Ident[i][j]);
      printf("mprod(trans(A),X) = \n"); VU_mprintm_d("8.3",B); fflush(stdout);
      (chk > .01) ? printf("error\n") : printf("correct\n"); fflush(stdout);

/************************************************/
      /* check case A X = B for VSIP_MAT_NTRANS */
      printf("check A X = Y; VSIP_MAT_NTRANS\n");
      printf("Y = \n");VU_mprintm_d("8.4",X);
      vsip_lusol_d(ludC,VSIP_MAT_NTRANS,X);
      printf("X = \n"); VU_mprintm_d("8.4",X);
      vsip_mprod_d(A,X,Y);
      printf(" Y = A X\n");VU_mprintm_d("8.4",Y);
      chk = 0;
      for(i=0; i<6; i++)
          for(j=0; j<3; j++)
              chk += fabs(vsip_mget_d(Y,i,j) - ydata[i][j]);
      (chk > .01) ? printf("error\n") : printf("agree\n"); fflush(stdout);

/************************************************/
      /* check case trans(A) X = B for VSIP_MAT_TRANS */
      for(i=0; i<6; i++)
         for(j=0; j<3; j++)
            vsip_mput_d(X,i,j,ydata[i][j]);
      printf("Y = \n");VU_mprintm_d("8.4",X);
      vsip_lusol_d(ludG,VSIP_MAT_TRANS,X);
      vsip_mprod_d(AT,X,Y);
      printf("X = \n");VU_mprintm_d("8.4",X);
      printf("Y = trans(A) X\n");VU_mprintm_d("8.4",Y);
      chk = 0;
      for(i=0; i<6; i++)
          for(j=0; j<3; j++)
              chk += fabs(vsip_mget_d(Y,i,j) - ydata[i][j]);
      (chk > .01) ? printf("error\n") : printf("agree\n"); fflush(stdout);

/***************************************************/
      /* destroy stuff */
      vsip_mdestroy_d(AC);
      vsip_mdestroy_d(AG);
      vsip_mdestroy_d(IC);
      vsip_mdestroy_d(IG);
      vsip_mdestroy_d(B);
      vsip_mdestroy_d(A);
      vsip_mdestroy_d(X);
      vsip_mdestroy_d(Y);
      vsip_malldestroy_d(AT);
      vsip_lud_destroy_d(ludC);
      vsip_lud_destroy_d(ludG);
   }
   return;
}
