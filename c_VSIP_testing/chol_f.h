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
/* $Id: chol_f.h,v 2.2 2006/04/09 20:58:37 judd Exp $ */

static
void
chol_f(void){
   printf("********\nTEST chol_f\n");
   {
      vsip_index i,j;
      vsip_block_f *ablock = vsip_blockcreate_f(200,VSIP_MEM_NONE);
      vsip_mview_f *R = vsip_mcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_f *RH = vsip_mcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);
/*      vsip_mview_f *A = vsip_mcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE); */
      vsip_mview_f *A = vsip_mbind_f(ablock,99,-11,4,-2,4);
/*      vsip_mview_f *B = vsip_mcreate_f(4,3,VSIP_COL,VSIP_MEM_NONE); */
      vsip_mview_f *B = vsip_mbind_f(ablock,100,20,4,2,3);
      vsip_mview_f *ans = vsip_mcreate_f(4,3,VSIP_ROW,VSIP_MEM_NONE);
      vsip_chol_f  *chol = vsip_chold_create_f(VSIP_TR_UPP,4);
      vsip_scalar_f chk;
      vsip_scalar_f data_R[4][4] = { 
                            { 1.0,  -2.0,  3.0,  1.0}, 
                            { 0.0,   2.0,  4.0, -1.0}, 
                            { 0.0,   0.0,  4.0,  3.0}, 
                            { 0.0,   0.0,  0.0,  6.0} };
      vsip_scalar_f data_Br[4][3] = { 
                            { 1.0, 2.0, 3.0},  
                            { 0.0, 1.0, 2.0}, 
                            { 3.0, 0.0, 1.0}, 
                            { 3.0, 4.0, 5.0}};
      vsip_scalar_f data_ans[4][3] = {   
                            {  4.6250, 13.9062, 21.0000},
                            {  1.3333,  4.1667,  6.3333},
                            { -0.3750, -1.3438, -2.0000},
                            {  0.1667,  0.4583,  0.6667}};
   
      for(i=0; i<4; i++)
         for(j=0; j<4; j++)
            vsip_mput_f(R,i,j,data_R[i][j]);
      for(i=0; i<4; i++) {
         for(j=0; j<3; j++){
            vsip_mput_f(B,i,j,data_Br[i][j]);
            vsip_mput_f(ans,i,j,data_ans[i][j]);
         }
      }
      vsip_mtrans_f(R,RH);
      vsip_mprod_f(RH,R,A);
      printf("R = \n");VU_mprintm_f("4.2",R);
      printf("RH = \n");VU_mprintm_f("4.2",RH);
      printf("A = R * RH\n");VU_mprintm_f("4.2",A);
      printf("B \n");VU_mprintm_f("4.2",B);
   
      vsip_chold_f(chol,A);
      printf("A after decomp");VU_mprintm_f("4.2",A);
      vsip_cholsol_f(chol,B);
      printf("Solve using cholesky AX = B\n X = \n");VU_mprintm_f("4.2",B);
      vsip_chold_destroy_f(chol);
      printf("right answer \n ans = \n");VU_mprintm_f("4.2",ans);
   
      vsip_msub_f(ans,B,B);
      chk =  vsip_msumsqval_f(B);
      if(chk > .001)
         printf("error\n");
      else
         printf("correct\n");
   
      {
         vsip_lu_f *lu = vsip_lud_create_f(4);
         vsip_mview_f *Bans = vsip_mcreate_f(4,3,VSIP_ROW,VSIP_MEM_NONE);
         vsip_mprod_f(RH,R,A);
         for(i=0; i<4; i++)
            for(j=0; j<3; j++)
               vsip_mput_f(B,i,j,data_Br[i][j]);
         vsip_lud_f(lu,A);
         vsip_lusol_f(lu,VSIP_MAT_NTRANS,B);
         printf("Solve using LUD AX = B\n X = \n");VU_mprintm_f("4.2",B);
         vsip_lud_destroy_f(lu);
         vsip_mprod_f(RH,R,A);
         vsip_mprod_f(A,B,Bans);
         printf("Bans = A X\n");VU_mprintm_f("4.2",Bans);
         vsip_msub_f(ans,B,B);
         chk =  vsip_msumsqval_f(B);
         if(chk > .001)
            printf("error\n");
         else
            printf("correct\n");
         vsip_malldestroy_f(Bans);
      }
      vsip_malldestroy_f(R);
      vsip_malldestroy_f(RH);
      vsip_mdestroy_f(B);
      vsip_malldestroy_f(A);
   }
}
