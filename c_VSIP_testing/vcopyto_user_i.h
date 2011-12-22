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
/* $Id */

static void vcopyto_user_i(void){
   printf("********\nTEST vcopyto_user_i\n");
   { 
      int i;
      vsip_block_i *block = vsip_blockcreate_i(200,VSIP_MEM_NONE);
      vsip_scalar_i ans[5]={0,1,2,3,4},output[5];
      vsip_vview_i *view = vsip_vbind_i(block,100,-3,5);
      vsip_vview_i *all = vsip_vbind_i(block,0,1,200);
      vsip_scalar_i check = 0;
      vsip_vfill_i(-1,all);
      vsip_vramp_i(0,1,view);
      vsip_vcopyto_user_i(view,output);
      VU_vprintm_i("1",view);
      for(i=0; i<5; i++){
         printf("%d\n",(int)output[i]);
         check += fabs((float)(output[i] - ans[i]));
      }
      if(check < 0.1){
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_vdestroy_i(all);
      vsip_vdestroy_i(view);
      vsip_blockdestroy_i(block); 
   }
   return;
}
