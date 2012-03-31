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
/* $Id: vcopyfrom_user_f.h,v 1.1 2007/04/18 03:59:06 judd Exp $ */

#include"VU_vprintm_f.include"
static void vcopyfrom_user_f(void){
   printf("********\nTEST vcopyfrom_user_f\n");
   { 
      int i;
      vsip_block_f *block = vsip_blockcreate_f(200,VSIP_MEM_NONE);
      vsip_scalar_f input[5]={0,1,2,3,4};
      vsip_vview_f *view = vsip_vbind_f(block,100,3,5);
      vsip_vview_f *all = vsip_vbind_f(block,0,1,200);
      vsip_scalar_f check = 0;
      vsip_vfill_f(-1,all);
      vsip_vcopyfrom_user_f(input,view);
      VU_vprintm_f("3.2",view);
      for(i=0; i<5; i++){
         check += fabs(input[i] - vsip_vget_f(view,(vsip_index)i));
      }
      if(check < 0.1){
         printf("correct\n");
      } else {
         printf("error\n");
      }
      vsip_vdestroy_f(all);
      vsip_vdestroy_f(view);
      vsip_blockdestroy_f(block); 
   }
   return;
}
