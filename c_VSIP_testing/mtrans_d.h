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
/* $Id: mtrans_d.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
#include"VU_mprintm_d.include"
static void mtrans_d(void){
   printf("********\nTEST mtrans_d\n");
   {
     vsip_scalar_d data_1[] = {1,  2,  3,  4,
                                  5,  6,  7,  8, 
                                  9, 10, 11, 12,
                                 13, 14, 15, 16};
     vsip_scalar_d data_2[] = {  .1,  .2,  .3,  .4,    
                                  1.0, 1.1, 1.2, 1.3,
                                  2.1, 2.2, 2.3, 2.4};
     vsip_block_d *block_1 = vsip_blockbind_d(data_1,16,VSIP_MEM_NONE);
     vsip_block_d *block_2 = vsip_blockbind_d(data_2,12,VSIP_MEM_NONE);
     vsip_block_d *block = vsip_blockcreate_d(200,VSIP_MEM_NONE);
     vsip_mview_d *d_1   = vsip_mbind_d(block_1,0,4,4,1,4);
     vsip_mview_d *ans_d1 = vsip_mbind_d(block_1,0,1,4,4,4);
     vsip_mview_d *d_2   = vsip_mbind_d(block_2,0,4,3,1,4);
     vsip_mview_d *ans_d2 = vsip_mbind_d(block_2,0,1,4,4,3);

     vsip_mview_d *a_1 = vsip_mbind_d(block,18,-4,4,-1,4);
     vsip_mview_d *a_2 = vsip_mbind_d(block,70,-2,3,-10,4);

     vsip_mview_d *c_2 = vsip_mbind_d(block,150,8,4,1,3);
     vsip_mview_d *chk_1 = vsip_mcreate_d(4,4,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *chk_2 = vsip_mcreate_d(4,3,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *ans_1 = vsip_mcreate_d(4,4,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d *ans_2 = vsip_mcreate_d(4,3,VSIP_COL,VSIP_MEM_NONE);

     vsip_blockadmit_d(block_1,VSIP_TRUE);
     vsip_blockadmit_d(block_2,VSIP_TRUE);

     vsip_mcopy_d_d(ans_d1,ans_1);
     vsip_mcopy_d_d(ans_d2,ans_2);
     vsip_mcopy_d_d(d_1,a_1);
     vsip_mcopy_d_d(d_2,a_2);

     printf("4x4 in place\n");
     printf("matrix a = ");VU_mprintm_d("6.4",a_1);
     printf("vsip_mtrans_d(a_1,a_1)\n");
     vsip_mtrans_d(a_1,a_1);
     printf("matrix a = ");VU_mprintm_d("6.4",a_1);
     printf("matrix ans = ");VU_mprintm_d("6.4",ans_1);
     vsip_msub_d(a_1,ans_1,chk_1); vsip_mmag_d(chk_1,chk_1); vsip_mclip_d(chk_1,.0001,.0001,0,1,chk_1);
     if(vsip_msumval_d(chk_1) > .5)
         printf("error\n\n");
     else
         printf("correct\n\n");
     
     printf("3x4 out of place\n");
     printf("vsip_mtrans_d(a,b)\n");
     printf("matrix a = "); VU_mprintm_d("6.4",a_2);
     vsip_mtrans_d(a_2,c_2);
     printf("matrix b = "); VU_mprintm_d("6.4",c_2);
     printf("matrix ans = ");VU_mprintm_d("6.4",ans_2);
     vsip_msub_d(c_2,ans_2,chk_2); vsip_mmag_d(chk_2,chk_2); vsip_mclip_d(chk_2,.0001,.0001,0,1,chk_2);
     if(vsip_msumval_d(chk_2) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_malldestroy_d(chk_1);
     vsip_malldestroy_d(chk_2);
     vsip_mdestroy_d(a_1); vsip_mdestroy_d(a_2); vsip_malldestroy_d(c_2);
     vsip_malldestroy_d(ans_1); vsip_malldestroy_d(ans_2);
     vsip_mdestroy_d(ans_d1); vsip_malldestroy_d(d_1);
     vsip_mdestroy_d(ans_d2); vsip_malldestroy_d(d_2);
   }
   return;
}
