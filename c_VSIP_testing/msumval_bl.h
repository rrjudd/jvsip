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
/* $Id: msumval_bl.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
#include"VU_mprintm_d.include"
static void msumval_bl(void){
   printf("\n*******\nTEST msumval_bl\n");
   {
       vsip_scalar_bl data[] = {0, 1, 0, 1, 0, 1, 1, 1, 1, 0};
       vsip_mview_bl *m1 = vsip_mbind_bl(
                 vsip_blockbind_bl(data,10,VSIP_MEM_NONE),0,5,2,1,5);       
       vsip_block_bl  *block = vsip_blockcreate_bl(1024,VSIP_MEM_NONE);
       vsip_mview_bl *m = vsip_mbind_bl(block,4,20,2,2,5);
       vsip_mview_d *pm = vsip_mcreate_d(2,5,VSIP_ROW,VSIP_MEM_NONE);
       vsip_blockadmit_bl(vsip_mgetblock_bl(m1),VSIP_TRUE);
       vsip_mcopy_bl_bl(m1,m);
       printf("matrix m1, user matrix, compact, row major\n");
       vsip_mcopy_bl_d(m1,pm);
       VU_mprintm_d("1.0",pm);
       printf("matrix m1, VSIPL matrix, irregular, row major\n");
       printf("col stride 20, row stride 2\n");
       printf("copy m1 to m. Matrix m equals\n");
       vsip_mcopy_bl_d(m,pm);
       VU_mprintm_d("1.0",pm);
       printf("msumval_bl(m1) = %ld\n",vsip_msumval_bl(m1));
       printf("msumval_bl(m) = %ld\n",vsip_msumval_bl(m));
       printf("ans should be 6 \n");
       if((fabs(6 - vsip_msumval_bl(m) > .0001)) || 
          (fabs(6.- vsip_msumval_bl(m1) > .0001))){
          printf("error\n");
       }else{
           printf("correct\n");
       }
       vsip_malldestroy_bl(m); vsip_malldestroy_bl(m1); vsip_malldestroy_d(pm);
    }
    return;
}
