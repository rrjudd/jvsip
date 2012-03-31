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
/* $Id: cmfill_f.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
#include"VU_cmprintm_f.include"
static void cmfill_f(void){
    printf("\n******\nTEST cmfill_f\n");
    {
        vsip_cscalar_f alpha = vsip_cmplx_f(5.5,-1.5);
        vsip_scalar_f ans_r[] =  { 5.5,   5.5,  5.5,  5.5,  5.5,  5.5,  5.5,  5.5};
        vsip_scalar_f ans_i[] =  { -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5, -1.5};
        vsip_cmview_f *ans = vsip_cmbind_f(
                  vsip_cblockbind_f(ans_r,ans_i,8,VSIP_MEM_NONE),0,2,4,1,2);
        vsip_cmview_f *b = vsip_cmcreate_f(4,2,VSIP_COL,VSIP_MEM_NONE);
        vsip_cmview_f *chk = vsip_cmcreate_f(4,2,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_f  *chk_r = vsip_mrealview_f(chk);
        vsip_cblockadmit_f(vsip_cmgetblock_f(ans),VSIP_TRUE);

        printf("alpha = %f %+fi\n",vsip_real_f(alpha),vsip_imag_f(alpha));
        printf("vsip_cmfill_f(alpha,b)\n");
        vsip_cmfill_f(alpha,b);
        printf("b =\n");VU_cmprintm_f("8.6",b);
        printf("\nright answer =\n"); VU_cmprintm_f("6.4",ans);
        vsip_cmsub_f(ans,b,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,0,2 * .0001,0,1,chk_r);
        if(fabs(vsip_msumval_f(chk_r)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_cmalldestroy_f(b);
        vsip_cmalldestroy_f(ans);
        vsip_mdestroy_f(chk_r); vsip_cmalldestroy_f(chk);
    }                                                       
      
    return;
}
