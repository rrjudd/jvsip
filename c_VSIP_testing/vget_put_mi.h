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
/* $Id: vget_put_mi.h,v 2.0 2003/02/22 15:23:36 judd Exp $ */
static void vget_put_mi(void){
   printf("********\nTEST vget_put_mi\n");
   {
     vsip_scalar_vi data_a[]   = { 0,0, 1,2, 1,3, 2,3,  1,0, 4,1};
                                 
     vsip_scalar_vi ans_r[]      = { 0, 1, 1, 2,  1, 4};
     vsip_scalar_vi ans_c[]      = { 0, 2, 3, 3,  0, 1};
     
     vsip_block_mi *block_a    = vsip_blockbind_mi(data_a,6,VSIP_MEM_NONE);
     vsip_vview_mi *a          = vsip_vbind_mi(block_a,0,1,6);

     vsip_block_mi *block_b    = vsip_blockcreate_mi(50,VSIP_MEM_NONE);
     vsip_vview_mi *b          = vsip_vbind_mi(block_b, 35,-2,6);
     vsip_index i;

     vsip_blockadmit_mi(block_a,VSIP_TRUE);

     /* copy <a> into <b> */
     for(i=0; i<6; i++) vsip_vput_mi(b,i,vsip_vget_mi(a,i));
     /* check <a> against ans */
     printf("check unit stride compact view\n");
     for(i=0; i<6; i++){
        vsip_scalar_mi chk = vsip_vget_mi(a,i);
        chk.r = ans_r[i] - chk.r + ans_c[i] - chk.c;
        (chk.r == 0) ? printf("correct\n") : printf("error\n");
        fflush(stdout);
     }
     printf("check general stride view\n");
     for(i=0; i<6; i++){
        vsip_scalar_mi chk = vsip_vget_mi(a,i);
        chk.r = ans_r[i] - chk.r + ans_c[i] - chk.c;
        (chk.r == 0) ? printf("correct\n") : printf("error\n");
        fflush(stdout);
     }
     vsip_valldestroy_mi(a);
     vsip_valldestroy_mi(b);
   }
   return;
}
