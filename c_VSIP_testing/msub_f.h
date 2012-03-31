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
/* $Id: msub_f.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
#include"VU_mprintm_f.include"
static void msub_f(void){
    printf("\n******\nTEST msub_f\n");
    {
        vsip_scalar_f data1[]= {1,   2,   3,    4,   5,   2.5,   7,   16.5, 10};
        vsip_scalar_f data2[]= {1.1, 2.2, 3.3,  4.4, 5.5, 6.6, 7.7, 8.8,  9.9};
        vsip_scalar_f ans[] =  {-0.1000, -2.4000, -4.7000, 1.8000, -0.5000, -6.3000, 3.7000, 9.9000, 0.1000};
        vsip_mview_f *m1 = vsip_mbind_f(
                  vsip_blockbind_f(data1,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_f *m2 = vsip_mbind_f(
                  vsip_blockbind_f(data2,9,VSIP_MEM_NONE),0,1,3,3,3);
        vsip_mview_f *ma = vsip_mbind_f(
                  vsip_blockbind_f(ans,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_f *m3 = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_f *chk = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_blockadmit_f(vsip_mgetblock_f(m1),VSIP_TRUE);
        vsip_blockadmit_f(vsip_mgetblock_f(m2),VSIP_TRUE);
        vsip_blockadmit_f(vsip_mgetblock_f(ma),VSIP_TRUE);
        printf("call vsip_msub_f(a,b,c)\n");
        printf("a =\n");VU_mprintm_f("8.6",m1);
        printf("b =\n");VU_mprintm_f("8.6",m2);
        vsip_msub_f(m1,m2,m3);
        printf("c =\n");VU_mprintm_f("8.6",m3);
        printf("\nright answer =\n"); VU_mprintm_f("6.4",ma);
        vsip_msub_f(ma,m3,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_f(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_mcopy_f_f(m1,m3);
        printf(" a,c inplace\n");
        vsip_msub_f(m3,m2,m3);
        vsip_msub_f(ma,m3,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_f(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");

        vsip_mcopy_f_f(m2,m3);
        printf(" b,c inplace\n");
        vsip_msub_f(m1,m3,m3);
        vsip_msub_f(ma,m3,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_f(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_malldestroy_f(m1); vsip_malldestroy_f(m2);
        vsip_malldestroy_f(m3); vsip_malldestroy_f(ma);
        vsip_malldestroy_f(chk);
    }                                                       
      
    return;
}
