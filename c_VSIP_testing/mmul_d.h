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
/* $Id: mmul_d.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
#include"VU_mprintm_d.include"
static void mmul_d(void){
    printf("\n******\nTEST mmul_d\n");
    {
        vsip_scalar_d data1[]= {1, 2, 3, 4, 5, 6, 7, 8, 9};
        vsip_scalar_d data2[]= {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
        vsip_scalar_d ans[] =  {1.1, 8.8, 23.1, 8.8, 27.5, 52.8, 23.1, 52.8, 89.1};
        vsip_mview_d *m1 = vsip_mbind_d(
                  vsip_blockbind_d(data1,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_d *m2 = vsip_mbind_d(
                  vsip_blockbind_d(data2,9,VSIP_MEM_NONE),0,1,3,3,3);
        vsip_mview_d *ma = vsip_mbind_d(
                  vsip_blockbind_d(ans,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_d *m3 = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
/*        vsip_mview_d *m2T = vsip_mtransview_d(m2); */
        vsip_blockadmit_d(vsip_mgetblock_d(m1),VSIP_TRUE);
        vsip_blockadmit_d(vsip_mgetblock_d(m2),VSIP_TRUE);
        vsip_blockadmit_d(vsip_mgetblock_d(ma),VSIP_TRUE);
        printf("input matrix m1\n");VU_mprintm_d("6.4",m1);
        printf("input matrix m2\n");VU_mprintm_d("6.4",m2);
        vsip_mmul_d(m1,m2,m3);
        printf("output matrix vsip_mmul_d(m1,m2,m3)\n");VU_mprintm_d("6.4",m3);
        printf("\nanswer should be\n"); VU_mprintm_d("6.4",ma);
        vsip_msub_d(ma,m3,m3);
        if(fabs(vsip_msumval_d(m3)) > .0001){
          printf("error\n");
       }else{
           printf("correct\n");
       }
       vsip_malldestroy_d(m1); vsip_malldestroy_d(m2);
       vsip_malldestroy_d(m3); vsip_malldestroy_d(ma);
    }                                                       
      
/*        VU_mprintm_d("6.4",m3); */
/*        VU_mprintm_d("6.4",m1); */
/*        VU_mprintm_d("6.4",m2T); */
/*        vsip_mmul_d(m1,m2T,m3); */
/*        VU_mprintm_d("6.4",m3); */
     return;
}
