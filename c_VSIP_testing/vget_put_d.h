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
/* $Id: vget_put_d.h,v 2.0 2003/02/22 15:23:36 judd Exp $ */
static void vget_put_d(void){
   printf("********\nTEST vget_put_d\n");
   {
     vsip_scalar_d data_a[]   = { 0, 1, 1, 0,  1, 0};
                                 
     vsip_scalar_d ans[]      = { 0, 1, 1, 0,  1, 0};
     vsip_block_d *block_a    = vsip_blockbind_d(data_a,6,VSIP_MEM_NONE);
     vsip_vview_d *a          = vsip_vbind_d(block_a,0,1,6);

     vsip_block_d *block_b    = vsip_blockcreate_d(50,VSIP_MEM_NONE);
     vsip_vview_d *b          = vsip_vbind_d(block_b, 35,-2,6);
     vsip_index i;

     vsip_blockadmit_d(block_a,VSIP_TRUE);

     /* copy <a> into <b> */
     for(i=0; i<6; i++) vsip_vput_d(b,i,vsip_vget_d(a,i));
     /* check <a> against ans */
     printf("check unit stride compact view\n");
     for(i=0; i<6; i++){
        vsip_scalar_d chk = fabs(ans[i] - vsip_vget_d(a,i));
        (chk < 0.0001) ? printf("correct\n") : printf("error\n");
        fflush(stdout);
     }
     printf("check general stride view\n");
     for(i=0; i<6; i++){
        vsip_scalar_d chk = fabs(ans[i] - vsip_vget_d(a,i));
        (chk < 0.0001) ? printf("correct\n") : printf("error\n");
        fflush(stdout);
     }
     vsip_valldestroy_d(a);
     vsip_valldestroy_d(b);
   }
   return;
}
