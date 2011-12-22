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
/* $Id: vget_put_uc.h,v 2.0 2003/02/22 15:23:36 judd Exp $ */
static void vget_put_uc(void){
   printf("********\nTEST vget_put_uc\n");
   {
     vsip_scalar_uc data_a[]   = { 0, 1, 1, 0,  1, 0};
                                 
     vsip_scalar_uc ans[]      = { 0, 1, 1, 0,  1, 0};
     vsip_block_uc *block_a    = vsip_blockbind_uc(data_a,6,VSIP_MEM_NONE);
     vsip_vview_uc *a          = vsip_vbind_uc(block_a,0,1,6);

     vsip_block_uc *block_b    = vsip_blockcreate_uc(50,VSIP_MEM_NONE);
     vsip_vview_uc *b          = vsip_vbind_uc(block_b, 35,-2,6);
     vsip_index i;

     vsip_blockadmit_uc(block_a,VSIP_TRUE);

     /* copy <a> into <b> */
     for(i=0; i<6; i++) vsip_vput_uc(b,i,vsip_vget_uc(a,i));
     /* check <a> against ans */
     printf("check unit stride compact view\n");
     for(i=0; i<6; i++){
        vsip_scalar_uc chk = (ans[i] - vsip_vget_uc(a,i));
        (chk == 0) ? printf("correct\n") : printf("error\n");
        fflush(stdout);
     }
     printf("check general stride view\n");
     for(i=0; i<6; i++){
        vsip_scalar_uc chk = (ans[i] - vsip_vget_uc(a,i));
        (chk == 0) ? printf("correct\n") : printf("error\n");
        fflush(stdout);
     }
     vsip_valldestroy_uc(a);
     vsip_valldestroy_uc(b);
   }
   return;
}
