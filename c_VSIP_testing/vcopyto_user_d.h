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
/* $Id: vcopyto_user_d.h,v 1.1 2007/04/18 03:59:06 judd Exp $ */

static void vcopyto_user_d(void){
   printf("********\nTEST vcopyto_user_d\n");
   { 
      int i;
      vsip_block_d *block = vsip_blockcreate_d(200,VSIP_MEM_NONE);
      vsip_scalar_d ans[5]={0,1,2,3,4},output[5];
      vsip_vview_d *view = vsip_vbind_d(block,100,-3,5);
      vsip_vview_d *all = vsip_vbind_d(block,0,1,200);
      vsip_scalar_d check = 0;
      vsip_vfill_d(-1,all);
      vsip_vramp_d(0,1.0,view);
      vsip_vcopyto_user_d(view,output);
      VU_vprintm_d("3.2",view);
      for(i=0; i<5; i++){
         printf("%f\n",(float)output[i]);
         check += fabs(output[i] - ans[i]);
      }
      if(check < 0.1){
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_vdestroy_d(all);
      vsip_vdestroy_d(view);
      vsip_blockdestroy_d(block); 
   }
   return;
}
