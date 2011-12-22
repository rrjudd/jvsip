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
/* $Id: mget_put_bl.h,v 2.0 2003/02/22 15:23:34 judd Exp $ */
static void mget_put_bl(void){
   printf("********\nTEST mget_put_bl\n");
   {
     vsip_scalar_bl data_a[]   = { VSIP_FALSE, VSIP_TRUE, VSIP_TRUE, 
                                 VSIP_FALSE, VSIP_TRUE, VSIP_FALSE};
     int ans[2][3]             = {{ 0, 1, 1},{ 0,  1, 0}};
     vsip_block_bl *block_a    = vsip_blockbind_bl(data_a,6,VSIP_MEM_NONE);
     vsip_mview_bl *a          = vsip_mbind_bl(block_a,0,3,2,1,3);

     vsip_block_bl *block_b    = vsip_blockcreate_bl(50,VSIP_MEM_NONE);
     vsip_mview_bl *b          = vsip_mbind_bl(block_b, 45,-2,2,-8,3);
     vsip_index i,j;

     vsip_blockadmit_bl(block_a,VSIP_TRUE);

     /* copy <a> into <b> */
     for(j=0; j<3; j++)
        for(i=0; i<2; i++) 
           vsip_mput_bl(b,i,j,vsip_mget_bl(a,i,j));
     /* check <a> against ans */
     printf("check unit stride compact view\n");
     for(j=0; j<3; j++)
        for(i=0; i<2; i++){
          vsip_scalar_bl ck = (ans[i][j] == 0) ? VSIP_FALSE : VSIP_TRUE;
          (ck == vsip_mget_bl(a,i,j)) ? printf("correct\n") : printf("error\n");
          fflush(stdout);
     }
     printf("check general stride view\n");
     for(j=0; j<3; j++)
        for(i=0; i<2; i++){
           vsip_scalar_bl ck = (ans[i][j] == 0) ? VSIP_FALSE : VSIP_TRUE;
           (ck == vsip_mget_bl(b,i,j)) ? printf("correct\n") : printf("error\n");
           fflush(stdout);
     }
     vsip_malldestroy_bl(a);
     vsip_malldestroy_bl(b);
   }
   return;
}
