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
/* $Id: cvexpoavg_f.h,v 2.0 2003/02/22 15:23:22 judd Exp $ */
#include"VU_cvprintm_f.include"
static void cvexpoavg_f(void){
    printf("\n******\nTEST cvexpoavg_f\n");
    {
        vsip_scalar_f alpha = (vsip_scalar_f)(1.0/3.0);
        vsip_scalar_f data1[]= {1,.1, 2,.2, 3,.3, 4,-.1, 5,-.3, 6,-.4, 7,.8, 8,.9, 9,-1};
        vsip_scalar_f data2[]= {2,.1, 3,.2, 4,.3, 6,-.1, 8,-.3, 6,-.6, 7,.7, 8,.5, 1,-1.3};
        vsip_scalar_f data3[]= {0,.2, 3,.5, 3,.1, 2,-.1, 5,-.3, 6,-.4, 7,.8, 8,.9, 9,-1.5};
        vsip_cvview_f *ans = vsip_cvcreate_f(9,VSIP_MEM_NONE);
        vsip_cvview_f *m1 = vsip_cvbind_f(
                  vsip_cblockbind_f(data1,NDPTR_f,9,VSIP_MEM_NONE),0,1,9);
        vsip_cvview_f *m2 = vsip_cvbind_f(
                  vsip_cblockbind_f(data2,NDPTR_f,9,VSIP_MEM_NONE),0,1,9);
        vsip_cvview_f *m3 = vsip_cvbind_f(
                  vsip_cblockbind_f(data3,NDPTR_f,9,VSIP_MEM_NONE),0,1,9);
        vsip_cvview_f *c = vsip_cvcreate_f(9,VSIP_MEM_NONE);
        vsip_cvview_f *chk = vsip_cvcreate_f(9,VSIP_MEM_NONE);
        vsip_vview_f *chk_r = vsip_vrealview_f(chk);
        vsip_cblockadmit_f(vsip_cvgetblock_f(m1),VSIP_TRUE);
        vsip_cblockadmit_f(vsip_cvgetblock_f(m2),VSIP_TRUE);
        vsip_cblockadmit_f(vsip_cvgetblock_f(m3),VSIP_TRUE);
        printf("call vsip_cvexpoavg_f(alpha,b,c) three times\n");
        printf("alpha = 1\n");
        printf("first call b =\n");VU_cvprintm_f("8.6",m1);
        printf("alpha = 1/2\n");
        printf("second call b =\n");VU_cvprintm_f("8.6",m2);
        printf("alpha = 1/3\n");
        printf("third call b =\n");VU_cvprintm_f("8.6",m3);
        printf("c initialized to zero\n");
        { vsip_vview_f *cr = vsip_vrealview_f(c);
          vsip_vview_f *ci = vsip_vimagview_f(c);
          vsip_vfill_f(0,cr); vsip_vfill_f(0,ci);
          vsip_vdestroy_f(cr); vsip_vdestroy_f(ci);
        }
        vsip_cvexpoavg_f(1.0,m1,c);
        vsip_cvexpoavg_f(.5,m2,c);
        vsip_cvexpoavg_f(1.0/3.0,m3,c);
        printf("after third call c =\n");VU_cvprintm_f("8.6",c);
        vsip_cvadd_f(m1,m2,ans);
        vsip_cvadd_f(m3,ans,ans);
        vsip_rscvmul_f(alpha,ans,ans);
        printf("\nright answer =\n"); VU_cvprintm_f("6.4",ans);
        vsip_cvsub_f(ans,c,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,0,2 * .0001,0,1,chk_r);
        if(fabs(vsip_vsumval_f(chk_r)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_cvalldestroy_f(m1); vsip_cvalldestroy_f(m2);
        vsip_cvalldestroy_f(m3); vsip_cvalldestroy_f(ans);
        vsip_cvalldestroy_f(c);
        vsip_vdestroy_f(chk_r);  vsip_cvalldestroy_f(chk);
    }                                                       
      
    return;
}
