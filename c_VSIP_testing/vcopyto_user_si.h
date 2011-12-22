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

static void vcopyto_user_si(void){
   printf("********\nTEST vcopyto_user_si\n");
   { 
      int i;
      vsip_block_si *block = vsip_blockcreate_si(200,VSIP_MEM_NONE);
      vsip_scalar_si ans[5]={0,1,2,3,4},output[5];
      vsip_vview_si *view = vsip_vbind_si(block,100,-3,5);
      vsip_vview_si *all = vsip_vbind_si(block,0,1,200);
      vsip_scalar_si check = 0;
      vsip_vfill_si(-1,all);
      vsip_vramp_si(0,1.0,view);
      vsip_vcopyto_user_si(view,output);
      VU_vprintm_si("1",view);
      for(i=0; i<5; i++){
         printf("%d\n",(int)output[i]);
         check += fabs((float)(output[i] - ans[i]));
      }
      if(check < 0.1){
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_vdestroy_si(all);
      vsip_vdestroy_si(view);
      vsip_blockdestroy_si(block); 
   }
   return;
}
