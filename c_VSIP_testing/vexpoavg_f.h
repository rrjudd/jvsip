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
/* $Id: vexpoavg_f.h,v 2.0 2003/02/22 15:23:28 judd Exp $ */
#include"VU_vprintm_f.include"
static void vexpoavg_f(void){
   printf("********\nTEST vexpoavg_f\n");
   {
        vsip_scalar_f alpha = (vsip_scalar_f)(1.0/3.0);
        vsip_scalar_f data1[]= {1,.1, 2,.2, 3,.3, 4,-.1, 5,-.3};
        vsip_scalar_f data2[]= {2,.1, 3,.2, 4,.3, 6,-.1, 8,-.3};
        vsip_scalar_f data3[]= {0,.2, 3,.5, 3,.1, 2,-.1, 5,-.3};
        vsip_vview_f *ans = vsip_vcreate_f(10,VSIP_MEM_NONE);
        vsip_vview_f *m1 = vsip_vbind_f(
                  vsip_blockbind_f(data1,10,VSIP_MEM_NONE),0,1,10);
        vsip_vview_f *m2 = vsip_vbind_f(
                  vsip_blockbind_f(data2,10,VSIP_MEM_NONE),0,1,10);
        vsip_vview_f *m3 = vsip_vbind_f(
                  vsip_blockbind_f(data3,10,VSIP_MEM_NONE),0,1,10);
        vsip_vview_f *c = vsip_vcreate_f(10,VSIP_MEM_NONE);
        vsip_vview_f *chk = vsip_vcreate_f(10,VSIP_MEM_NONE);
        vsip_blockadmit_f(vsip_vgetblock_f(m1),VSIP_TRUE);
        vsip_blockadmit_f(vsip_vgetblock_f(m2),VSIP_TRUE);
        vsip_blockadmit_f(vsip_vgetblock_f(m3),VSIP_TRUE);
        printf("call vsip_vexpoavg_f(alpha,b,c) three times\n");
        printf("alpha = 1\n");
        printf("first call b =\n");VU_vprintm_f("8.6",m1);
        printf("alpha = 1/2\n");
        printf("second call b =\n");VU_vprintm_f("8.6",m2);
        printf("alpha = 1/3\n");
        printf("third call b =\n");VU_vprintm_f("8.6",m3);
        printf("c initialized to zero\n");
        vsip_vfill_f(0,c);
        vsip_vexpoavg_f(1.0,m1,c);
        vsip_vexpoavg_f(.5,m2,c);
        vsip_vexpoavg_f(1.0/3.0,m3,c);
        printf("after third call c =\n");VU_vprintm_f("8.6",c);
        vsip_vadd_f(m1,m2,ans);
        vsip_vadd_f(m3,ans,ans);
        vsip_svmul_f(alpha,ans,ans);
        printf("\nright answer =\n"); VU_vprintm_f("6.4",ans);
        vsip_vsub_f(ans,c,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,0,2 * .0001,0,1,chk);
        if(fabs(vsip_vsumval_f(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_valldestroy_f(m1); vsip_valldestroy_f(m2);
        vsip_valldestroy_f(m3); vsip_valldestroy_f(ans);
        vsip_valldestroy_f(c);
        vsip_valldestroy_f(chk);
    }                                                       
      
    return;
}
