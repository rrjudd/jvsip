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
/* $Id: cmexpoavg_d.h,v 2.0 2003/02/22 15:23:20 judd Exp $ */
static void cmexpoavg_d(void){
    printf("\n******\nTEST cmexpoavg_d\n");
    {
        vsip_scalar_d alpha = (vsip_scalar_d)(1.0/3.0);
        vsip_scalar_d data1[]= {1,.1, 2,.2, 3,.3, 4,-.1, 5,-.3, 6,-.4, 7,.8, 8,.9, 9,-1};
        vsip_scalar_d data2[]= {2,.1, 3,.2, 4,.3, 6,-.1, 8,-.3, 6,-.6, 7,.7, 8,.5, 1,-1.3};
        vsip_scalar_d data3[]= {0,.2, 3,.5, 3,.1, 2,-.1, 5,-.3, 6,-.4, 7,.8, 8,.9, 9,-1.5};
        vsip_cmview_d *ans = vsip_cmcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_cmview_d *m1 = vsip_cmbind_d(
                  vsip_cblockbind_d(data1,NDPTR_d,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_cmview_d *m2 = vsip_cmbind_d(
                  vsip_cblockbind_d(data2,NDPTR_d,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_cmview_d *m3 = vsip_cmbind_d(
                  vsip_cblockbind_d(data3,NDPTR_d,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_cmview_d *c = vsip_cmcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_cmview_d *chk = vsip_cmcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_d *chk_r = vsip_mrealview_d(chk);
        vsip_cblockadmit_d(vsip_cmgetblock_d(m1),VSIP_TRUE);
        vsip_cblockadmit_d(vsip_cmgetblock_d(m2),VSIP_TRUE);
        vsip_cblockadmit_d(vsip_cmgetblock_d(m3),VSIP_TRUE);
        printf("call vsip_cmexpoavg_d(alpha,b,c) three times\n");
        printf("alpha = 1\n");
        printf("first call b =\n");VU_cmprintm_d("8.6",m1);
        printf("alpha = 1/2\n");
        printf("second call b =\n");VU_cmprintm_d("8.6",m2);
        printf("alpha = 1/3\n");
        printf("third call b =\n");VU_cmprintm_d("8.6",m3);
        printf("c initialized to zero\n");
        { vsip_mview_d *cr = vsip_mrealview_d(c);
          vsip_mview_d *ci = vsip_mimagview_d(c);
          vsip_mfill_d(0,cr); vsip_mfill_d(0,ci);
          vsip_mdestroy_d(cr); vsip_mdestroy_d(ci);
        }
        vsip_cmexpoavg_d(1.0,m1,c);
        vsip_cmexpoavg_d(.5,m2,c);
        vsip_cmexpoavg_d(1.0/3.0,m3,c);
        printf("after third call c =\n");VU_cmprintm_d("8.6",c);
        vsip_cmadd_d(m1,m2,ans);
        vsip_cmadd_d(m3,ans,ans);
        vsip_rscmmul_d(alpha,ans,ans);
        printf("\nright answer =\n"); VU_cmprintm_d("6.4",ans);
        vsip_cmsub_d(ans,c,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,0,2 * .0001,0,1,chk_r);
        if(fabs(vsip_msumval_d(chk_r)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_cmalldestroy_d(m1); vsip_cmalldestroy_d(m2);
        vsip_cmalldestroy_d(m3); vsip_cmalldestroy_d(ans);
        vsip_cmalldestroy_d(c);
        vsip_mdestroy_d(chk_r);  vsip_cmalldestroy_d(chk);
    }                                                       
      
    return;
}
