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
/* $Id: vget_put_bl.h,v 2.0 2003/02/22 15:23:36 judd Exp $ */
static void vget_put_bl(void){
   printf("********\nTEST vget_put_bl\n");
   {
     vsip_scalar_bl data_a[]   = { VSIP_FALSE, VSIP_TRUE, VSIP_TRUE, 
                                 VSIP_FALSE, VSIP_TRUE, VSIP_FALSE};
     int ans[]                 = { 0, 1, 1, 0,  1, 0};
     vsip_block_bl *block_a    = vsip_blockbind_bl(data_a,6,VSIP_MEM_NONE);
     vsip_vview_bl *a          = vsip_vbind_bl(block_a,0,1,6);

     vsip_block_bl *block_b    = vsip_blockcreate_bl(50,VSIP_MEM_NONE);
     vsip_vview_bl *b          = vsip_vbind_bl(block_b, 35,-2,6);
     vsip_index i;

     vsip_blockadmit_bl(block_a,VSIP_TRUE);

     /* copy <a> into <b> */
     for(i=0; i<6; i++) vsip_vput_bl(b,i,vsip_vget_bl(a,i));
     /* check <a> against ans */
     printf("check unit stride compact view\n");
     for(i=0; i<6; i++){
        vsip_scalar_bl ck = (ans[i] == 0) ? VSIP_FALSE : VSIP_TRUE;
        (ck == vsip_vget_bl(a,i)) ? printf("correct\n") : printf("error\n");
        fflush(stdout);
     }
     printf("check general stride view\n");
     for(i=0; i<6; i++){
        vsip_scalar_bl ck = (ans[i] == 0) ? VSIP_FALSE : VSIP_TRUE;
        (ck == vsip_vget_bl(b,i)) ? printf("correct\n") : printf("error\n");
        fflush(stdout);
     }
     vsip_valldestroy_bl(a);
     vsip_valldestroy_bl(b);
   }
   return;
}
