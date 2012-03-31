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
/* $Id: mexpoavg_d.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
#include"VU_mprintm_d.include"
static void mexpoavg_d(void){
    printf("\n******\nTEST mexpoavg_d\n");
    {
        vsip_scalar_d alpha = (vsip_scalar_d)(1.0/3.0);
        vsip_scalar_d data1[]= {1,.1, 2,.2, 3,.3, 4,-.1, 5,-.3, 6,-.4, 7,.8, 8,.9, 9,-1};
        vsip_scalar_d data2[]= {2,.1, 3,.2, 4,.3, 6,-.1, 8,-.3, 6,-.6, 7,.7, 8,.5, 1,-1.3};
        vsip_scalar_d data3[]= {0,.2, 3,.5, 3,.1, 2,-.1, 5,-.3, 6,-.4, 7,.8, 8,.9, 9,-1.5};
        vsip_mview_d *ans = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_d *m1 = vsip_mbind_d(
                  vsip_blockbind_d(data1,18,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_d *m2 = vsip_mbind_d(
                  vsip_blockbind_d(data2,18,VSIP_MEM_NONE),1,4,3,1,3);
        vsip_mview_d *m3 = vsip_mbind_d(
                  vsip_blockbind_d(data3,18,VSIP_MEM_NONE),3,1,3,3,3);
        vsip_mview_d *c = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_d *chk = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_blockadmit_d(vsip_mgetblock_d(m1),VSIP_TRUE);
        vsip_blockadmit_d(vsip_mgetblock_d(m2),VSIP_TRUE);
        vsip_blockadmit_d(vsip_mgetblock_d(m3),VSIP_TRUE);
        printf("call vsip_mexpoavg_d(alpha,b,c) three times\n");
        printf("alpha = 1\n");
        printf("first call b =\n");VU_mprintm_d("8.6",m1);
        printf("alpha = 1/2\n");
        printf("second call b =\n");VU_mprintm_d("8.6",m2);
        printf("alpha = 1/3\n");
        printf("third call b =\n");VU_mprintm_d("8.6",m3);
        printf("c initialized to zero\n");
        vsip_mfill_d(0,c);
        vsip_mexpoavg_d(1.0,m1,c);
        vsip_mexpoavg_d(.5,m2,c);
        vsip_mexpoavg_d(1.0/3.0,m3,c);
        printf("after third call c =\n");VU_mprintm_d("8.6",c);
        vsip_madd_d(m1,m2,ans);
        vsip_madd_d(m3,ans,ans);
        vsip_smmul_d(alpha,ans,ans);
        printf("\nright answer =\n"); VU_mprintm_d("6.4",ans);
        vsip_msub_d(ans,c,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,0,2 * .0001,0,1,chk);
        if(fabs(vsip_msumval_d(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_malldestroy_d(m1); vsip_malldestroy_d(m2);
        vsip_malldestroy_d(m3); vsip_malldestroy_d(ans);
        vsip_malldestroy_d(c);
        vsip_malldestroy_d(chk);
    }                                                       
      
    return;
}
