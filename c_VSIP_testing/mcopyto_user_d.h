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
/* $Id: mcopyto_user_d.h,v 1.1 2007/04/18 03:59:06 judd Exp $ */

static void mcopyto_user_d(void){
   vsip_index i,j;
   printf("********\nTEST mcopyto_user_d\n");
   {  /* check row copy */
      vsip_block_d *block = vsip_blockcreate_d(200,VSIP_MEM_NONE);
      vsip_scalar_d ans[20]={0,1,2,3,10,11,12,13,20,21,22,23,30,31,32,33,40,41,42,43},output[20];
      vsip_mview_d *view = vsip_mbind_d(block,100,2,5,12,4);
      vsip_vview_d *all = vsip_vbind_d(block,0,1,200);
      vsip_scalar_d check = 0;
      vsip_vfill_d(-1,all);
      for(i=0; i<5; i++){
         for(j=0; j<4; j++){
            vsip_mput_d(view,i,j,i*10+j);
         }
      }
      printf("check row copy\n");
      vsip_mcopyto_user_d(view,VSIP_ROW,output);
      VU_mprintm_d("3.2",view);
      for(i=0; i<20;i++) {
        check += fabs(ans[i]-output[i]);
        printf("%f\n",(float)output[i]);
      }
      if(check < 0.1){
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_vdestroy_d(all);
      vsip_mdestroy_d(view);
      vsip_blockdestroy_d(block); 
   }
   {  /* check col copy */
      vsip_block_d *block = vsip_blockcreate_d(200,VSIP_MEM_NONE);
      vsip_scalar_d ans[20]={0,10,20,30,40,1,11,21,31,41,2,12,22,32,42,3,13,23,33,43},output[20];
      vsip_mview_d *view = vsip_mbind_d(block,100,2,5,12,4);
      vsip_vview_d *all = vsip_vbind_d(block,0,1,200);
      vsip_scalar_d check = 0;
      vsip_vfill_d(-1,all);
      for(i=0; i<5; i++){
         for(j=0; j<4; j++){
            vsip_mput_d(view,i,j,i*10+j);
         }
      }
      printf("check col copy\n");
      vsip_mcopyto_user_d(view,VSIP_COL,output);
      VU_mprintm_d("3.2",view);
      for(i=0; i<20;i++) {
        check += fabs(ans[i]-output[i]);
        printf("%f\n",(float)output[i]);
      }
      if(check < 0.1){
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_vdestroy_d(all);
      vsip_mdestroy_d(view);
      vsip_blockdestroy_d(block);
   }

   return;
}
