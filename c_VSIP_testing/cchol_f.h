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
/* $Id: cchol_f.h,v 2.2 2006/04/09 20:58:37 judd Exp $ */

#include"VU_cmprintm_f.include"
static void cchol_f(void){
   printf("********\nTEST cchol_f\n"); 
   {
      vsip_index i,j;
      vsip_cblock_f *ablock = vsip_cblockcreate_f(200,VSIP_MEM_NONE);
      vsip_cmview_f *R = vsip_cmcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);
      vsip_cmview_f *RH = vsip_cmcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);
/*      vsip_cmview_f *A = vsip_cmcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE); */
      vsip_cmview_f *A = vsip_cmbind_f(ablock,40,-9,4,-2,4);
/*      vsip_cmview_f *B = vsip_cmcreate_f(4,3,VSIP_COL,VSIP_MEM_NONE); */
      vsip_cmview_f *B = vsip_cmbind_f(ablock,100,10,4,3,3);
      vsip_cchol_f  *chol = vsip_cchold_create_f(VSIP_TR_UPP,4);
      vsip_cmview_f *ans = vsip_cmcreate_f(4,3,VSIP_ROW,VSIP_MEM_NONE);
      vsip_scalar_f chk;
      vsip_scalar_f data_R[4][4] = { 
                             {1.0,  -2.0,  3.0,  1.0}, 
                             {0.0,   2.0,  4.0, -1.0}, 
                             {0.0,   0.0,  4.0,  3.0}, 
                             {0.0,   0.0,  0.0,  6.0} };
      vsip_scalar_f data_I[4][4] = { 
                             { 0.0,  2.0,  2.0,  1.0}, 
                             { 0.0,  0.0,  2.0, -4.0}, 
                             { 0.0,  0.0,  0.0,  2.0}, 
                             { 0.0,  0.0,  0.0,  0.0} };
      vsip_scalar_f data_Br[4][3] = { 
                             {1.0, 2.0, 3.0},  
                             {0.0, 1.0, 2.0}, 
                             {3.0, 0.0, 1.0}, 
                             {3.0, 4.0, 5.0}};
      vsip_scalar_f data_Bi[4][3] = { 
                             {1.0, 0.5, 3.2}, 
                             {2.0, 0.0, 0.6}, 
                             {0.6, 2.0, 0.0}, 
                             {5.0, 7.0, 8.0}};
      vsip_scalar_f data_ans_r[4][3] = {
                             {13.6236, 27.5451, 43.1573},
                             {-0.1104,  5.2370,  3.3312},
                             {-0.8403, -1.9410, -2.9823},
                             { 0.7000,  0.8125,  1.7375} };
      vsip_scalar_f data_ans_i[4][3] = {
                             {19.4965,  5.3707, 40.9604},
                             { 6.7292,  5.4896, 15.8781},
                             {-1.4021, -0.3776, -2.9688},
                             { 0.3694, -0.1632,  0.4667} };
   
      for(i=0; i<4; i++)
         for(j=0; j<4; j++)
            vsip_cmput_f(R,i,j,vsip_cmplx_f(data_R[i][j],data_I[i][j]));
      for(i=0; i<4; i++){
         for(j=0; j<3; j++){
            vsip_cmput_f(B,i,j,vsip_cmplx_f(data_Br[i][j],data_Bi[i][j]));
            vsip_cmput_f(ans,i,j,vsip_cmplx_f(data_ans_r[i][j],data_ans_i[i][j]));
         }
      }
      vsip_cmherm_f(R,RH);
      vsip_cmprod_f(RH,R,A);
      printf("R = \n");VU_cmprintm_f("4.2",R);
      printf("RH = \n");VU_cmprintm_f("4.2",RH);
      printf("A = R * RH\n");VU_cmprintm_f("4.2",A);
      printf("B \n");VU_cmprintm_f("4.2",B);
   
      vsip_cchold_f(chol,A);
      vsip_ccholsol_f(chol,B);
      printf("Solve using cholesky AX = B\n X = \n");VU_cmprintm_f("4.2",B);
      vsip_cchold_destroy_f(chol);
      printf("right answer \n ans = \n");VU_cmprintm_f("4.2",ans);
   
      vsip_cmsub_f(ans,B,B);  
      chk =  vsip_cmmeansqval_f(B);   
      if(chk > .001)
         printf("error\n");  
      else
         printf("correct\n");
   
      {
         vsip_clu_f *lu = vsip_clud_create_f(4);
         vsip_cmview_f *Bans = vsip_cmcreate_f(4,3,VSIP_ROW,VSIP_MEM_NONE);
         vsip_cmprod_f(RH,R,A);
         for(i=0; i<4; i++)
            for(j=0; j<3; j++)
               vsip_cmput_f(B,i,j,vsip_cmplx_f(data_Br[i][j],data_Bi[i][j]));
         vsip_clud_f(lu,A);
         vsip_clusol_f(lu,VSIP_MAT_NTRANS,B);
         printf("Solve using LUD AX = B\n X = \n");VU_cmprintm_f("4.2",B);
         vsip_clud_destroy_f(lu);
         vsip_cmprod_f(RH,R,A);
         vsip_cmprod_f(A,B,Bans);
         printf("Bans = A X \n");VU_cmprintm_f("4.2",Bans);
         vsip_cmsub_f(ans,B,B);
         chk =  vsip_cmmeansqval_f(B);
         if(chk > .001)
            printf("error\n");
         else
            printf("correct\n");
         vsip_cmalldestroy_f(Bans);
      }
      vsip_cmalldestroy_f(R);
      vsip_cmalldestroy_f(RH);
      vsip_cmdestroy_f(B);
      vsip_cmalldestroy_f(A);
   } 
}
