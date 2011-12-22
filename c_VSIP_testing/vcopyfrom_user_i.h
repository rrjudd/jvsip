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
/* $Id: vcopyfrom_user_i.h,v 1.1 2007/04/21 19:38:33 judd Exp $ */

static void vcopyfrom_user_i(void){
   printf("********\nTEST vcopyfrom_user_i\n");
   { 
      int i;
      vsip_block_i *block = vsip_blockcreate_i(200,VSIP_MEM_NONE);
      vsip_scalar_i input[5]={0,1,2,3,4};
      vsip_vview_i *view = vsip_vbind_i(block,100,3,5);
      vsip_vview_i *all = vsip_vbind_i(block,0,1,200);
      vsip_scalar_i check = 0;
      vsip_vfill_i(-1,all);
      vsip_vcopyfrom_user_i(input,view);
      VU_vprintm_i("3",view);
      for(i=0; i<5; i++){
         check += fabs((float)(input[i] - vsip_vget_i(view,(vsip_index)i)));
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
