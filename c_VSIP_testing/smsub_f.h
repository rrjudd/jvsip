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
/* $Id: smsub_f.h,v 2.0 2003/02/22 15:23:27 judd Exp $ */
#include"VU_mprintm_f.include"
static void smsub_f(void){
    printf("\n******\nTEST smsub_f\n");
    {
        vsip_scalar_f alpha = 1.2345;
        vsip_scalar_f data2[]= {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
        vsip_scalar_f ans[] = {0.1345, -3.1655, -6.4655, -0.9655, -4.2655, -7.5655, -2.0655, -5.3655, -8.6655};
        vsip_mview_f *m2 = vsip_mbind_f(
                  vsip_blockbind_f(data2,9,VSIP_MEM_NONE),0,1,3,3,3);
        vsip_mview_f *ma = vsip_mbind_f(
                  vsip_blockbind_f(ans,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_f *m3 = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_f *chk = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_blockadmit_f(vsip_mgetblock_f(m2),VSIP_TRUE);
        vsip_blockadmit_f(vsip_mgetblock_f(ma),VSIP_TRUE);
        printf("call vsip_smsub_f(alpha,b,c)\n");
        printf("alpha = %f\n",alpha);
        printf("b =\n");VU_mprintm_f("8.6",m2);
        vsip_smsub_f(alpha,m2,m3);
        printf("c =\n");VU_mprintm_f("8.6",m3);
        printf("\nright answer =\n"); VU_mprintm_f("6.4",ma);
        vsip_msub_f(ma,m3,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_f(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_mcopy_f_f(m2,m3);
        printf(" b,c inplace\n");
        vsip_smsub_f(alpha,m3,m3);
        vsip_msub_f(ma,m3,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_f(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_malldestroy_f(m2);
        vsip_malldestroy_f(m3); vsip_malldestroy_f(ma);
        vsip_malldestroy_f(chk);
    }                                                       
      
    return;
}
