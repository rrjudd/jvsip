/* Created RJudd */
/* SPAWARSYSCEN */
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
/* $Id: cchol_d.h,v 2.1 2004/07/30 16:03:04 judd Exp $ */

#include"VU_cmprintm_d.include"
static void cchol_d(void){
   printf("********\nTEST cchol_d\n"); 
   {
      vsip_index i,j;
/* use this block for default creater */
/*      vsip_cblock_d *ablock = vsip_cblockcreate_d(200,VSIP_MEM_NONE); */

/* use this block to ensure split complex */
      vsip_scalar_d rdta[200];
      vsip_scalar_d idta[200];
      vsip_cblock_d *ablock = vsip_cblockbind_d(rdta,idta,200,VSIP_MEM_NONE);

      vsip_cmview_d *R = vsip_cmcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);
      vsip_cmview_d *RH = vsip_cmcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);
/*      vsip_cmview_d *A = vsip_cmcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE); */
      vsip_cmview_d *A = vsip_cmbind_d(ablock,40,-9,4,-2,4);
/*      vsip_cmview_d *B = vsip_cmcreate_d(4,3,VSIP_COL,VSIP_MEM_NONE); */
      vsip_cmview_d *B = vsip_cmbind_d(ablock,100,10,4,3,3);
      vsip_cchol_d  *chol = vsip_cchold_create_d(VSIP_TR_UPP,4);
      vsip_cmview_d *ans = vsip_cmcreate_d(4,3,VSIP_ROW,VSIP_MEM_NONE);
      vsip_scalar_d chk;
      vsip_scalar_d data_R[4][4] = { 
                             {1.0,  -2.0,  3.0,  1.0}, 
                             {0.0,   2.0,  4.0, -1.0}, 
                             {0.0,   0.0,  4.0,  3.0}, 
                             {0.0,   0.0,  0.0,  6.0} };
      vsip_scalar_d data_I[4][4] = { 
                              {0.0,  2.0,  2.0,  1.0}, 
                              {0.0,  0.0,  2.0, -4.0}, 
                              {0.0,  0.0,  0.0,  2.0}, 
                              {0.0,  0.0,  0.0,  0.0} };
      vsip_scalar_d data_Br[4][3] = { 
                             {1.0, 2.0, 3.0},  
                             {0.0, 1.0, 2.0}, 
                             {3.0, 0.0, 1.0}, 
                             {3.0, 4.0, 5.0}};
      vsip_scalar_d data_Bi[4][3] = { 
                             {1.0, 0.5, 3.2}, 
                             {2.0, 0.0, 0.6}, 
                             {0.6, 2.0, 0.0}, 
                             {5.0, 7.0, 8.0}};
      vsip_scalar_d data_ans_r[4][3] = {
                             {13.6236, 27.5451, 43.1573},
                             {-0.1104,  5.2370,  3.3312},
                             {-0.8403, -1.9410, -2.9823},
                             { 0.7000,  0.8125,  1.7375} };
      vsip_scalar_d data_ans_i[4][3] = {
                             {19.4965,  5.3707, 40.9604},
                             { 6.7292,  5.4896, 15.8781},
                             {-1.4021, -0.3776, -2.9688},
                              {0.3694, -0.1632,  0.4667} };
   
      vsip_cblockadmit_d(ablock,VSIP_FALSE);
      for(i=0; i<4; i++)
         for(j=0; j<4; j++)
            vsip_cmput_d(R,i,j,vsip_cmplx_d(data_R[i][j],data_I[i][j]));
      for(i=0; i<4; i++){
         for(j=0; j<3; j++){
            vsip_cmput_d(B,i,j,vsip_cmplx_d(data_Br[i][j],data_Bi[i][j]));
            vsip_cmput_d(ans,i,j,vsip_cmplx_d(data_ans_r[i][j],data_ans_i[i][j]));
         }
      }
      vsip_cmherm_d(R,RH);
      vsip_cmprod_d(RH,R,A);
      printf("R = \n");VU_cmprintm_d("4.2",R);
      printf("RH = \n");VU_cmprintm_d("4.2",RH);
      printf("A = R * RH\n");VU_cmprintm_d("4.2",A);
      printf("B \n");VU_cmprintm_d("4.2",B);
   
      vsip_cchold_d(chol,A);
      vsip_ccholsol_d(chol,B);
      printf("Solve using cholesky AX = B\n X = \n");VU_cmprintm_d("4.2",B);
      vsip_cchold_destroy_d(chol);
      printf("right answer \n ans = \n");VU_cmprintm_d("4.2",ans);
   
      vsip_cmsub_d(ans,B,B);  
      chk =  vsip_cmmeansqval_d(B);   
      if(chk > .001)
         printf("error\n");  
      else
         printf("correct\n");
   
      {
         vsip_clu_d *lu = vsip_clud_create_d(4);
         vsip_cmview_d *Bans = vsip_cmcreate_d(4,3,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmprod_d(RH,R,A);
         for(i=0; i<4; i++)
            for(j=0; j<3; j++)
               vsip_cmput_d(B,i,j,vsip_cmplx_d(data_Br[i][j],data_Bi[i][j]));
         vsip_clud_d(lu,A);
         vsip_clusol_d(lu,VSIP_MAT_NTRANS,B);
         printf("Solve using LUD AX = B\n X = \n");VU_cmprintm_d("4.2",B);
         vsip_clud_destroy_d(lu);
         vsip_cmprod_d(RH,R,A);
         vsip_cmprod_d(A,B,Bans);
         printf("Bans = A X \n");VU_cmprintm_d("4.2",Bans);
         vsip_cmsub_d(ans,B,B);
         chk =  vsip_cmmeansqval_d(B);
         if(chk > .001)
            printf("error\n");
         else
            printf("correct\n");
         vsip_cmalldestroy_d(Bans);
      }
      vsip_cmalldestroy_d(R);
      vsip_cmalldestroy_d(RH);
      vsip_cmdestroy_d(B);
      vsip_cmalldestroy_d(A);
   } 
}
