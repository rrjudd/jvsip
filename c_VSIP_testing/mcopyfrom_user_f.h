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
/* $Id: mcopyfrom_user_f.h,v 1.1 2007/04/18 03:59:06 judd Exp $ */
#include"VU_mprintm_f.include"
static void mcopyfrom_user_f(void){
   vsip_index i,j;
   printf("********\nTEST mcopyfrom_user_f\n");
   {  /* check row copy */
      vsip_block_f *block = vsip_blockcreate_f(200,VSIP_MEM_NONE);
      vsip_scalar_f input[20]={0,1,2,3,10,11,12,13,20,21,22,23,30,31,32,33,40,41,42,43};
      vsip_mview_f *view = vsip_mbind_f(block,100,2,5,12,4);
      vsip_vview_f *all = vsip_vbind_f(block,0,1,200);
      vsip_scalar_f check = 0;
      vsip_vfill_f(-1,all);
      vsip_mcopyfrom_user_f(input,VSIP_ROW,view);
      printf("check row copy\n");
      VU_mprintm_f("3.2",view);
      for(i=0; i<5; i++) {
         for(j=0; j < 4; j++) {
           check += fabs(input[i * 4 + j] - vsip_mget_f(view,i,j));
         }
      }
      if(check < 0.1){
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_vdestroy_f(all);
      vsip_mdestroy_f(view);
      vsip_blockdestroy_f(block); 
   }
   {  /* check col copy */
      vsip_block_f *block = vsip_blockcreate_f(200,VSIP_MEM_NONE);
      vsip_scalar_f input[20]={0,10,20,30,40,1,11,21,31,41,2,12,22,32,42,3,13,23,33,43};
      vsip_mview_f *view = vsip_mbind_f(block,100,2,5,12,4);
      vsip_vview_f *all = vsip_vbind_f(block,0,1,200);
      vsip_scalar_f check = 0;
      vsip_vfill_f(-1,all);
      vsip_mcopyfrom_user_f(input,VSIP_COL,view);
      printf("check col copy\n");
      VU_mprintm_f("3.2",view);
      for(j=0; j<4; j++) {
         for(i=0; i < 5; i++) {
           check += fabs(input[j * 5 + i] - vsip_mget_f(view,i,j));
         }
      }
      if(check < 0.1){
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_vdestroy_f(all);
      vsip_mdestroy_f(view);
      vsip_blockdestroy_f(block);
   }

   return;
}
