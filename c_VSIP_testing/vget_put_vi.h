/* Created RJudd */
/* SPAWARSYSCEN D857 */
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
/* $Id: vget_put_vi.h,v 2.0 2003/02/22 15:23:36 judd Exp $ */
static void vget_put_vi(void){
   printf("********\nTEST vget_put_vi\n");
   {
     vsip_scalar_vi data_a[]   = { 0, 1, 1, 2,  1, 4};
                                 
     vsip_scalar_vi ans[]      = { 0, 1, 1, 2,  1, 4};
     vsip_block_vi *block_a    = vsip_blockbind_vi(data_a,6,VSIP_MEM_NONE);
     vsip_vview_vi *a          = vsip_vbind_vi(block_a,0,1,6);

     vsip_block_vi *block_b    = vsip_blockcreate_vi(50,VSIP_MEM_NONE);
     vsip_vview_vi *b          = vsip_vbind_vi(block_b, 35,-2,6);
     vsip_index i;

     vsip_blockadmit_vi(block_a,VSIP_TRUE);

     /* copy <a> into <b> */
     for(i=0; i<6; i++) vsip_vput_vi(b,i,vsip_vget_vi(a,i));
     /* check <a> against ans */
     printf("check unit stride compact view\n");
     for(i=0; i<6; i++){
        int chk = (int)(ans[i] - vsip_vget_vi(a,i));
        (chk == 0) ? printf("correct\n") : printf("error\n");
        fflush(stdout);
     }
     printf("check general stride view\n");
     for(i=0; i<6; i++){
        int chk = (int)(ans[i] - vsip_vget_vi(a,i));
        (chk == 0) ? printf("correct\n") : printf("error\n");
        fflush(stdout);
     }
     vsip_valldestroy_vi(a);
     vsip_valldestroy_vi(b);
   }
   return;
}
