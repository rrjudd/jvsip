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
/* $Id: clud_d.h,v 2.0 2003/02/22 15:23:14 judd Exp $ */
#include"VU_cmprintm_d.include"
static void clud_d(void){
   printf("********\nTEST clud_d\n");
   {
      vsip_index i,j;
      /* make up some data space and views */
      vsip_cblock_d *block = vsip_cblockcreate_d(600,VSIP_MEM_NONE);
      vsip_cmview_d *AC = vsip_cmbind_d(block,0,7,7,1,7);
      vsip_cmview_d *AG = vsip_cmbind_d(block,175,-2,7,-18,7);
      vsip_cmview_d *IC = vsip_cmbind_d(block,176,1,7,7,7);
      vsip_cmview_d *IG = vsip_cmbind_d(block,226,2,7,15,7);
      vsip_cmview_d *B = vsip_cmbind_d(block,335,7,7,1,7);
      vsip_cmview_d *A = vsip_cmbind_d(block,385,7,7,1,7);
      vsip_cmview_d *X = vsip_cmbind_d(block,434,5,7,1,3);
      vsip_cmview_d *Y = vsip_cmbind_d(block,475,3,7,1,3);
      vsip_clu_d* ludC = vsip_clud_create_d(7);
      vsip_clu_d* ludG = vsip_clud_create_d(7);

      vsip_scalar_d chk;
      
      vsip_scalar_d data_r[7][7] = { \
          {0.5,  7.0, 10.0, 12.0, -3.0,  0.0,   0.05}, \
          {2.0, 13.0, 18.0,  6.0,  0.0, 130.0,  8.0}, \
          {3.0, -9.0,  2.0,  3.0,  2.0,  -9.0,  6.0}, \
          {4.0,  2.0,  2.0,  4.0,  1.0,   2.0,  3.0}, \
          {0.2,  2.0,  9.0,  4.0,  1.0,   2.0,  3.0}, \
          {0.1,  2.0,  0.3,  4.0,  1.0,   2.0,  3.0}, \
          {0.0,  0.2,  3.0,  4.0,  1.0,   2.0,  3.0}};
      vsip_scalar_d data_i[7][7] = {
         {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1}, \
        {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1}, \
        {0.1, 0.1, 0.1, 0.2, 0.2,-0.2, 0.2}, \
        {0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2}, \
        {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3}, \
        {0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4}, \
        {0.4, 0.4, 0.4, 0.4, 0.4, 0.4, 0.4}};

      vsip_scalar_d ydata_r[7][3] = { \
        {77.85,   155.70,   311.40}, \
       {942.00,  1884.00,  3768.00}, \
         {1.00,     2.00,     4.00}, \
        {68.00,   136.00,   272.00}, \
        {85.20,   170.40,   340.80}, \
        {59.00,   118.00,   236.00}, \
         {5.00,    18.00,     6.00}};

      vsip_scalar_d ydata_i[7][3] = { \
        {4.5,      1.70,   -3.40}, \
        {3.7,    184.00,   -2.00}, \
        {1.00,     3.00,    2.00}, \
        {68.00,   16.00,  272.00}, \
        {85.20, 1170.40,  340.80}, \
        {59.00,   18.50,   62.00}, \
        {59.00,   11.60,   26.00}};

                  
      vsip_scalar_d Ident[7][7] = {    \
                  {1, 0, 0, 0, 0, 0, 0}, \
                  {0, 1, 0, 0, 0, 0, 0}, \
                  {0, 0, 1, 0, 0, 0, 0}, \
                  {0, 0, 0, 1, 0, 0, 0}, \
                  {0, 0, 0, 0, 1, 0, 0}, \
                  {0, 0, 0, 0, 0, 1, 0}, \
                  {0, 0, 0, 0, 0, 0, 1}};

      vsip_cmview_d *AH = vsip_cmcreate_d(7,7,VSIP_ROW,VSIP_MEM_NONE);

      for(i=0; i<7; i++){
         for(j=0; j<7; j++){
            vsip_cscalar_d a = vsip_cmplx_d(data_r[i][j],data_i[i][j]);
            vsip_cscalar_d e = vsip_cmplx_d(Ident[i][j],0);
            vsip_cmput_d(A, i,j,a);
            vsip_cmput_d(AC,i,j,a);
            vsip_cmput_d(AG,i,j,a);
            vsip_cmput_d(IC,i,j,e);
            vsip_cmput_d(IG,i,j,e);
         }
      }
      for(i=0; i<7; i++){
         for(j=0; j<3; j++){
            vsip_cscalar_d a = vsip_cmplx_d(ydata_r[i][j],ydata_i[i][j]);
            vsip_cmput_d(X,i,j,a);
         }
      }
      vsip_cmherm_d(A,AH);

      printf("Matrix A = \n");VU_cmprintm_d("7.2",A);fflush(stdout);
      vsip_clud_d(ludC,AC); vsip_clud_d(ludG,AG);
      printf("vsip_clusol(lud,VSIP_MAT_NTRANS,X)\n");
      printf("Solve A X = I \n"); fflush(stdout);
      vsip_clusol_d(ludC,VSIP_MAT_NTRANS,IC);
      vsip_clusol_d(ludG,VSIP_MAT_NTRANS,IG);
      printf("for compact case X = \n");VU_cmprintm_d("8.4",IC); fflush(stdout);
      printf("for general case X = \n");VU_cmprintm_d("8.4",IG); fflush(stdout);
      chk = 0;
      for(i=0; i<7; i++)
          for(j=0; j<7; j++)
              chk += vsip_cmag_d(vsip_csub_d(vsip_cmget_d(IC,i,j) , vsip_cmget_d(IG,i,j)));
      (chk > .01) ? printf("error\n") : printf("agree\n"); fflush(stdout);

      vsip_cmprod_d(A,IC,B);

      chk = 0;
      for(i=0; i<7; i++)
          for(j=0; j<7; j++)
              chk += vsip_cmag_d(
                 vsip_csub_d(vsip_cmget_d(B,i,j),vsip_cmplx_d(Ident[i][j],0)));
      vsip_cmprod_d(A,IG,B);
      for(i=0; i<7; i++)
          for(j=0; j<7; j++)
              chk += vsip_cmag_d(
                 vsip_csub_d(vsip_cmget_d(B,i,j),vsip_cmplx_d(Ident[i][j],0)));
      printf("mprod(A,X) = \n"); VU_cmprintm_d("8.3",B); fflush(stdout);
      (chk > .01) ? printf("error\n") : printf("correct\n"); fflush(stdout);

/************************************************/
      /* check case VSIP_MAT_HERM */
      printf("Matrix Hermitian A = \n");VU_cmprintm_d("7.2",AH);fflush(stdout);
      for(i=0; i<7; i++){
         for(j=0; j<7; j++){
            vsip_cmput_d(IC,i,j,vsip_cmplx_d(Ident[i][j],0));
            vsip_cmput_d(IG,i,j,vsip_cmplx_d(Ident[i][j],0));
         }
      }
      
      printf("vsip_clusol(lud,VSIP_MAT_HERM,X)\n");
      printf("Solve herm(A) X = I \n"); fflush(stdout);
      vsip_clusol_d(ludC,VSIP_MAT_HERM,IC);
      vsip_clusol_d(ludG,VSIP_MAT_HERM,IG);
      printf("for compact case X = \n");VU_cmprintm_d("8.4",IC); fflush(stdout);
      printf("for general case X = \n");VU_cmprintm_d("8.4",IG); fflush(stdout);
      chk = 0;
      for(i=0; i<7; i++)
          for(j=0; j<7; j++)
              chk += vsip_cmag_d(vsip_csub_d(vsip_cmget_d(IC,i,j) , vsip_cmget_d(IG,i,j)));
      (chk > .01) ? printf("error\n") : printf("agree\n"); fflush(stdout);

      vsip_cmprod_d(AH,IC,B);

      chk = 0;
      for(i=0; i<7; i++)
          for(j=0; j<7; j++)
              chk += vsip_cmag_d(
                 vsip_csub_d(vsip_cmget_d(B,i,j),vsip_cmplx_d(Ident[i][j],0)));
      vsip_cmprod_d(AH,IG,B);
      for(i=0; i<7; i++)
          for(j=0; j<7; j++)
              chk += vsip_cmag_d(
                 vsip_csub_d(vsip_cmget_d(B,i,j),vsip_cmplx_d(Ident[i][j],0)));
      printf("mprod(herm(A),X) = \n"); VU_cmprintm_d("8.3",B); fflush(stdout);
      (chk > .01) ? printf("error\n") : printf("correct\n"); fflush(stdout);

/************************************************/
      /* check case A X = B for VSIP_MAT_NTRANS */
      printf("check A X = Y; VSIP_MAT_NTRANS\n");
      printf("Y = \n");VU_cmprintm_d("8.4",X);
      vsip_clusol_d(ludC,VSIP_MAT_NTRANS,X);
      printf("X = \n"); VU_cmprintm_d("8.4",X);
      vsip_cmprod_d(A,X,Y);
      printf(" Y = A X\n");VU_cmprintm_d("8.4",Y);
      chk = 0;
      for(i=0; i<7; i++)
          for(j=0; j<3; j++)
              chk += vsip_cmag_d(
                 vsip_csub_d(vsip_cmget_d(Y,i,j),
                    vsip_cmplx_d(ydata_r[i][j],ydata_i[i][j])));
      (chk > .01) ? printf("error\n") : printf("agree\n"); fflush(stdout);

/************************************************/
      /* check case herm(A) X = B for VSIP_MAT_HERM */
      for(i=0; i<7; i++)
         for(j=0; j<3; j++)
            vsip_cmput_d(X,i,j,vsip_cmplx_d(ydata_r[i][j],ydata_i[i][j]));
      printf("Y = \n");VU_cmprintm_d("8.4",X);
      vsip_clusol_d(ludG,VSIP_MAT_HERM,X);
      vsip_cmprod_d(AH,X,Y);
      printf("X = \n");VU_cmprintm_d("8.4",X);
      printf("Y = herm(A) X\n");VU_cmprintm_d("8.4",Y);
      chk = 0;
      for(i=0; i<7; i++)
          for(j=0; j<3; j++)
              chk += vsip_cmag_d(
                 vsip_csub_d(vsip_cmget_d(Y,i,j),
                    vsip_cmplx_d(ydata_r[i][j],ydata_i[i][j])));
      (chk > .01) ? printf("error\n") : printf("agree\n"); fflush(stdout);

/***************************************************/
      /* destroy stuff */
      vsip_cmdestroy_d(AC);
      vsip_cmdestroy_d(AG);
      vsip_cmdestroy_d(IC);
      vsip_cmdestroy_d(IG);
      vsip_cmdestroy_d(B);
      vsip_cmdestroy_d(A);
      vsip_cmdestroy_d(X);
      vsip_cmalldestroy_d(Y);
      vsip_cmalldestroy_d(AH);
      vsip_clud_destroy_d(ludC);
      vsip_clud_destroy_d(ludG);
   }
   return;
}
