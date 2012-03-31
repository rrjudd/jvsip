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
/* $Id: cmcopyto_user_f.h,v 1.1 2007/04/18 03:59:06 judd Exp $ */

#include"VU_cmprintm_f.include"
static void cmcopyto_user_f(void){
   vsip_index i,j;
   printf("********\nTEST cmcopyto_user_f\n");
   {  /* check row copy interleaved */
      vsip_cblock_f *block = vsip_cblockcreate_f(200,VSIP_MEM_NONE);
      vsip_scalar_f output[40];
      vsip_scalar_f ans[40]={0,0,0,1,0,2,0,3,1,0,1,1,1,2,1,3,2,0,2,1,2,2,2,3,3,0,3,1,3,2,3,3,4,0,4,1,4,2,4,3};
      vsip_cmview_f *view = vsip_cmbind_f(block,100,2,5,12,4);
      vsip_cvview_f *all = vsip_cvbind_f(block,0,1,200);
      vsip_scalar_f check = 0;
      vsip_cvfill_f(vsip_cmplx_f(-1,-1),all);
      for(i=0; i<5; i++){
         for(j=0; j < 4; j++){
            vsip_cscalar_f t = vsip_cmplx_f((vsip_scalar_f)i,(vsip_scalar_f)j);
            vsip_cmput_f(view,i,j,t);
         }
      }
      vsip_cmcopyto_user_f(view,VSIP_ROW,output,(vsip_scalar_f*)NULL);
      printf("check row copy interleaved\n");
      VU_cmprintm_f("3.2",view);
      for(i=0; i<40; i++) {
        check += fabs(output[i] - ans[i]);
        printf("%f\n",output[i]);
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
      vsip_scalar_f output[40];
      vsip_scalar_f ans[40]={0,0,1,0,2,0,3,0,4,0,0,1,1,1,2,1,3,1,4,1,0,2,1,2,2,2,3,2,4,2,0,3,1,3,2,3,3,3,4,3};
      vsip_cmview_f *view = vsip_cmbind_f(block,100,2,5,12,4);
      vsip_cvview_f *all = vsip_cvbind_f(block,0,1,200);
      vsip_scalar_f check = 0;
      vsip_cvfill_f(vsip_cmplx_f(-1,-1),all);
      for(i=0; i<5; i++){
         for(j=0; j < 4; j++){
            vsip_cscalar_f t = vsip_cmplx_f((vsip_scalar_f)i,(vsip_scalar_f)j);
            vsip_cmput_f(view,i,j,t);
         }
      }
      vsip_cmcopyto_user_f(view,VSIP_COL,output,(vsip_scalar_f*)NULL);
      printf("check col copy interleaved\n");
      VU_cmprintm_f("3.2",view);
      for(i=0; i<40; i++) {
        check += fabs(output[i] - ans[i]);
        printf("%f\n",output[i]);
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
      vsip_scalar_f output_r[20];
      vsip_scalar_f output_i[20];
      vsip_scalar_f ans_r[20]={0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4};
      vsip_scalar_f ans_i[20]={0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3};
      vsip_cmview_f *view = vsip_cmbind_f(block,100,2,5,12,4);
      vsip_cvview_f *all = vsip_cvbind_f(block,0,1,200);
      vsip_scalar_f check = 0;
      vsip_cvfill_f(vsip_cmplx_f(-1,-1),all);
      for(i=0; i<5; i++){
         for(j=0; j < 4; j++){
            vsip_cscalar_f t = vsip_cmplx_f((vsip_scalar_f)i,(vsip_scalar_f)j);
            vsip_cmput_f(view,i,j,t);
         }
      }
      vsip_cmcopyto_user_f(view,VSIP_ROW,output_r,output_i);
      printf("check row copy split\n");
      VU_cmprintm_f("3.2",view);
      for(i=0; i<20; i++) {
        check += fabs(output_r[i] - ans_r[i]);
        check += fabs(output_i[i] - ans_i[i]);
        printf("%f %f\n",output_r[i],output_i[i]);
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
      vsip_scalar_f output_r[20];
      vsip_scalar_f output_i[20];
      vsip_scalar_f ans_r[20]={0,1,2,3,4,0,1,2,3,4,0,1,2,3,4,0,1,2,3,4};
      vsip_scalar_f ans_i[20]={0,0,0,0,0,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3};
      vsip_cmview_f *view = vsip_cmbind_f(block,100,2,5,12,4);
      vsip_cvview_f *all = vsip_cvbind_f(block,0,1,200);
      vsip_scalar_f check = 0;
      vsip_cvfill_f(vsip_cmplx_f(-1,-1),all);
      for(i=0; i<5; i++){
         for(j=0; j < 4; j++){
            vsip_cscalar_f t = vsip_cmplx_f((vsip_scalar_f)i,(vsip_scalar_f)j);
            vsip_cmput_f(view,i,j,t);
         }
      }
      vsip_cmcopyto_user_f(view,VSIP_COL,output_r,output_i);
      printf("check col copy split\n");
      VU_cmprintm_f("3.2",view);
      for(i=0; i<20; i++) {
        check += fabs(output_r[i] - ans_r[i]);
        check += fabs(output_i[i] - ans_i[i]);
        printf("%f %f\n",output_r[i],output_i[i]);
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
