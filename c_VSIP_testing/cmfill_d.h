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
/* $Id: cmfill_d.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
static void cmfill_d(void){
    printf("\n******\nTEST cmfill_d\n");
    {
        vsip_cscalar_d alpha = vsip_cmplx_d(5.5,-1.5);
        vsip_scalar_d ans_r[] =  { 5.5,   5.5,  5.5,  5.5,  5.5,  5.5,  5.5,  5.5};
        vsip_scalar_d ans_i[] =  { -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5};
        vsip_cmview_d *ans = vsip_cmbind_d(
                  vsip_cblockbind_d(ans_r,ans_i,8,VSIP_MEM_NONE),0,2,4,1,2);
        vsip_cmview_d *b = vsip_cmcreate_d(4,2,VSIP_COL,VSIP_MEM_NONE);
        vsip_cmview_d *chk = vsip_cmcreate_d(4,2,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_d  *chk_r = vsip_mrealview_d(chk);
        vsip_cblockadmit_d(vsip_cmgetblock_d(ans),VSIP_TRUE);

        printf("alpha = %f %+fi\n",vsip_real_d(alpha),vsip_imag_d(alpha));
        printf("vsip_cmfill_d(alpha,b)\n");
        vsip_cmfill_d(alpha,b);
        printf("b =\n");VU_cmprintm_d("8.6",b);
        printf("\nright answer =\n"); VU_cmprintm_d("6.4",ans);
        vsip_cmsub_d(ans,b,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,0,2 * .0001,0,1,chk_r);
        if(fabs(vsip_msumval_d(chk_r)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_cmalldestroy_d(b);
        vsip_cmalldestroy_d(ans);
        vsip_mdestroy_d(chk_r); vsip_cmalldestroy_d(chk);
    }                                                       
      
    return;
}
