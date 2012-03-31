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
/* $Id: chol_d.h,v 2.0 2003/02/22 15:23:07 judd Exp $ */

#include"VU_mprintm_d.include"
static void chol_d(void){
   printf("********\nTEST chol_d\n");
   {
      vsip_index i,j;
      vsip_block_d *ablock = vsip_blockcreate_d(200,VSIP_MEM_NONE);
      vsip_mview_d *R = vsip_mcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);
      vsip_mview_d *RH = vsip_mcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);
/*      vsip_mview_d *A = vsip_mcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE); */
      vsip_mview_d *A = vsip_mbind_d(ablock,99,-11,4,-2,4);
/*      vsip_mview_d *B = vsip_mcreate_d(4,3,VSIP_COL,VSIP_MEM_NONE); */
      vsip_mview_d *B = vsip_mbind_d(ablock,100,20,4,2,3);
      vsip_mview_d *ans = vsip_mcreate_d(4,3,VSIP_ROW,VSIP_MEM_NONE);
      vsip_chol_d  *chol = vsip_chold_create_d(VSIP_TR_UPP,4);
      vsip_scalar_d chk;
      vsip_scalar_d data_R[4][4] = { 
                             {1.0,  -2.0,  3.0,  1.0}, 
                             {0.0,   2.0,  4.0, -1.0}, 
                             {0.0,   0.0,  4.0,  3.0}, 
                             {0.0,   0.0,  0.0,  6.0} };
      vsip_scalar_d data_Br[4][3] = { 
                            { 1.0, 2.0, 3.0},  
                            { 0.0, 1.0, 2.0}, 
                            { 3.0, 0.0, 1.0}, 
                            { 3.0, 4.0, 5.0}};
      vsip_scalar_d data_ans[4][3] = {   
                            {  4.6250, 13.9062, 21.0000},
                            {  1.3333,  4.1667,  6.3333},
                            { -0.3750, -1.3438, -2.0000},
                            {  0.1667,  0.4583,  0.6667}};
   
      for(i=0; i<4; i++)
         for(j=0; j<4; j++)
            vsip_mput_d(R,i,j,data_R[i][j]);
      for(i=0; i<4; i++) {
         for(j=0; j<3; j++){
            vsip_mput_d(B,i,j,data_Br[i][j]);
            vsip_mput_d(ans,i,j,data_ans[i][j]);
         }
      }
      vsip_mtrans_d(R,RH);
      vsip_mprod_d(RH,R,A);
      printf("R = \n");VU_mprintm_d("4.2",R);
      printf("RH = \n");VU_mprintm_d("4.2",RH);
      printf("A = R * RH\n");VU_mprintm_d("4.2",A);
      printf("B \n");VU_mprintm_d("4.2",B);
   
      vsip_chold_d(chol,A);
      vsip_cholsol_d(chol,B);
      printf("Solve using cholesky AX = B\n X = \n");VU_mprintm_d("4.2",B);
      vsip_chold_destroy_d(chol);
      printf("right answer \n ans = \n");VU_mprintm_d("4.2",ans);
   
      vsip_msub_d(ans,B,B);
      chk =  vsip_msumsqval_d(B);
      if(chk > .001)
         printf("error\n");
      else
         printf("correct\n");
   
      {
         vsip_lu_d *lu = vsip_lud_create_d(4);
         vsip_mview_d *Bans = vsip_mcreate_d(4,3,VSIP_ROW,VSIP_MEM_NONE);
         vsip_mprod_d(RH,R,A);
         for(i=0; i<4; i++)
            for(j=0; j<3; j++)
               vsip_mput_d(B,i,j,data_Br[i][j]);
         vsip_lud_d(lu,A);
         vsip_lusol_d(lu,VSIP_MAT_NTRANS,B);
         printf("Solve using LUD AX = B\n X = \n");VU_mprintm_d("4.2",B);
         vsip_lud_destroy_d(lu);
         vsip_mprod_d(RH,R,A);
         vsip_mprod_d(A,B,Bans);
         printf("Bans = A X\n");VU_mprintm_d("4.2",Bans);
         vsip_msub_d(ans,B,B);
         chk =  vsip_msumsqval_d(B);
         if(chk > .001)
            printf("error\n");
         else
            printf("correct\n");
         vsip_malldestroy_d(Bans);
      }
      vsip_malldestroy_d(R);
      vsip_malldestroy_d(RH);
      vsip_mdestroy_d(B);
      vsip_malldestroy_d(A);
   }
}
