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
/* $Id: mget_put_f.h,v 2.0 2003/02/22 15:23:34 judd Exp $ */
static void mget_put_f(void){
   printf("********\nTEST mget_put_f\n");
   {
     vsip_scalar_f data_a[]   = { 0, 1, 1, 0, 1, 0,
                                    1, 0, 0, 1, 0, 1};
                                 
     vsip_scalar_f ans[6][2]      = {{ 0, 1},{ 1, 0},{  1, 0},{ 1, 0},{ 0, 1},{ 0, 1}};
     vsip_block_f *block_a    = vsip_blockbind_f(data_a,12,VSIP_MEM_NONE);
     vsip_mview_f *a          = vsip_mbind_f(block_a,0,2,6,1,2);

     vsip_block_f *block_b    = vsip_blockcreate_f(50,VSIP_MEM_NONE);
     vsip_mview_f *b          = vsip_mbind_f(block_b,5,5,6,2,2);
     vsip_index i,j;

     vsip_blockadmit_f(block_a,VSIP_TRUE);

     /* copy <a> into <b> */
     for(i=0; i<6; i++) 
        for(j=0; j<2; j++)
           vsip_mput_f(b,i,j,vsip_mget_f(a,i,j));
     /* check <a> against ans */
     printf("check unit stride compact view\n");
     for(i=0; i<6; i++)
        for(j=0; j<2; j++) {
           vsip_scalar_f chk = fabs(ans[i][j] - vsip_mget_f(a,i,j));
           (chk < 0.0001) ? printf("correct\n") : printf("error\n");
           fflush(stdout);
     }
     printf("check general stride view\n");
     for(i=0; i<6; i++)
        for(j=0; j<2; j++){
           vsip_scalar_f chk = fabs(ans[i][j] - vsip_mget_f(b,i,j));
           (chk < 0.0001) ? printf("correct\n") : printf("error\n");
           fflush(stdout);
     }
     vsip_malldestroy_f(a);
     vsip_malldestroy_f(b);
   }
   return;
}
