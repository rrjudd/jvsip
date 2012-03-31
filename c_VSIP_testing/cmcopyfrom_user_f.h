/* Created RJudd */
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
/* $Id: cmcopyfrom_user_f.h,v 1.1 2007/04/18 03:59:06 judd Exp $ */

#include"VU_cmprintm_f.include"
static void cmcopyfrom_user_f(void){
   vsip_index i,j;
   printf("********\nTEST cmcopyfrom_user_f\n");
   {  /* check row copy interleaved */
      vsip_cblock_f *block = vsip_cblockcreate_f(200,VSIP_MEM_NONE);
      vsip_scalar_f input[40]={0,0,0,1,0,2,0,3,1,0,1,1,1,2,1,3,2,0,2,1,2,2,2,3,3,0,3,1,3,2,3,3,4,0,4,1,4,2,4,3};
      vsip_cmview_f *view = vsip_cmbind_f(block,100,2,5,12,4);
      vsip_cvview_f *all = vsip_cvbind_f(block,0,1,200);
      vsip_scalar_f check = 0;
      vsip_cvfill_f(vsip_cmplx_f(-1,-1),all);
      vsip_cmcopyfrom_user_f(input,(vsip_scalar_f*)NULL,VSIP_ROW,view);
      printf("check row copy interleaved\n");
      VU_cmprintm_f("3.2",view);
      for(i=0; i<5; i++) {
         for(j=0; j < 4; j++) {
           check += fabs(input[2*(i * 4 + j)] - vsip_real_f(vsip_cmget_f(view,i,j)));
           check += fabs(input[2*(i * 4 + j)+1] - vsip_imag_f(vsip_cmget_f(view,i,j)));
         }
      }
      if(check < 0.1){
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_cvdestroy_f(all);
      vsip_cmdestroy_f(view);
      vsip_cblockdestroy_f(block); 
   }
   {  /* check col copy interleaved*/
      vsip_cblock_f *block = vsip_cblockcreate_f(200,VSIP_MEM_NONE);
      vsip_scalar_f input[40]={0,0,1,0,2,0,3,0,4,0,0,1,1,1,2,1,3,1,4,1,0,2,1,2,2,2,3,2,4,2,0,3,1,3,2,3,3,3,4,3};
      vsip_cmview_f *view = vsip_cmbind_f(block,100,2,5,12,4);
      vsip_cvview_f *all = vsip_cvbind_f(block,0,1,200);
      vsip_scalar_f check = 0;
      vsip_cvfill_f(vsip_cmplx_f(-1,-1),all);
      vsip_cmcopyfrom_user_f(input,(vsip_scalar_f*)NULL,VSIP_COL,view);
      printf("check col copy interleaved\n");
      VU_cmprintm_f("3.2",view);
      for(j=0; j<4; j++) {
         for(i=0; i < 5; i++) {
           check += fabs(input[2*(i + j * 5)] - vsip_real_f(vsip_cmget_f(view,i,j)));
           check += fabs(input[2*(i + j * 5)+1] - vsip_imag_f(vsip_cmget_f(view,i,j)));
         }
      }
      if(check < 0.1){
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_cvdestroy_f(all);
      vsip_cmdestroy_f(view);
      vsip_cblockdestroy_f(block);
   }
   {  /* check row copy split */
      vsip_cblock_f *block = vsip_cblockcreate_f(200,VSIP_MEM_NONE);
      vsip_scalar_f input_r[20]={0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4};
      vsip_scalar_f input_i[20]={0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};
      vsip_cmview_f *view = vsip_cmbind_f(block,100,2,5,12,4);
      vsip_cvview_f *all = vsip_cvbind_f(block,0,1,200);
      vsip_scalar_f check = 0;
      vsip_cvfill_f(vsip_cmplx_f(-1,-1),all);
      vsip_cmcopyfrom_user_f(input_r,input_i,VSIP_ROW,view);
      printf("check row copy split\n");
      VU_cmprintm_f("3.2",view);
      for(i=0; i<5; i++) {
         for(j=0; j < 4; j++) {
           check += fabs(input_r[i * 4 + j] - vsip_real_f(vsip_cmget_f(view,i,j)));
           check += fabs(input_i[i * 4 + j] - vsip_imag_f(vsip_cmget_f(view,i,j)));
         }
      }
      if(check < 0.1){
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_cvdestroy_f(all);
      vsip_cmdestroy_f(view);
      vsip_cblockdestroy_f(block);
   }
   {  /* check col copy split*/
      vsip_cblock_f *block = vsip_cblockcreate_f(200,VSIP_MEM_NONE);
      vsip_scalar_f input_r[20]={0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4};
      vsip_scalar_f input_i[20]={0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3};
      vsip_cmview_f *view = vsip_cmbind_f(block,100,2,5,12,4);
      vsip_cvview_f *all = vsip_cvbind_f(block,0,1,200);
      vsip_scalar_f check = 0;
      vsip_cvfill_f(vsip_cmplx_f(-1,-1),all);
      vsip_cmcopyfrom_user_f(input_r,input_i,VSIP_COL,view);
      printf("check col copy split\n");
      VU_cmprintm_f("3.2",view);
      for(j=0; j<4; j++) {
         for(i=0; i < 5; i++) {
           check += fabs(input_r[i + j * 5] - vsip_real_f(vsip_cmget_f(view,i,j)));
           check += fabs(input_i[i + j * 5] - vsip_imag_f(vsip_cmget_f(view,i,j)));
         }
      }
      if(check < 0.1){
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_cvdestroy_f(all);
      vsip_cmdestroy_f(view);
      vsip_cblockdestroy_f(block);
   }
   return;
}
