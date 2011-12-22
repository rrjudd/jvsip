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
/* $Id: mfill_d.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
static void mfill_d(void){
    printf("\n******\nTEST mfill_d\n");
    {
        vsip_scalar_d alpha = 1.2345;
        vsip_scalar_d ans[] = {1.2345,1.2345,1.2345,1.2345,1.2345,1.2345,1.2345,1.2345,1.2345};
        vsip_mview_d *ma = vsip_mbind_d(
                  vsip_blockbind_d(ans,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_d *chk = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_d *B = vsip_mcreate_d(9,9,VSIP_COL,VSIP_MEM_NONE);
        vsip_mview_d *b = vsip_msubview_d(B,2,2,3,3);
        vsip_blockadmit_d(vsip_mgetblock_d(ma),VSIP_TRUE);
        vsip_mputrowstride_d(b,4);
        printf("call vsip_mfill_d(alpha,b)\n");
        printf("alpha = %f\n",alpha);
        vsip_mfill_d(alpha,b);
        printf("b =\n");VU_mprintm_d("8.6",b);
        printf("\nright answer =\n"); VU_mprintm_d("6.4",ma);
        vsip_msub_d(ma,b,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_d(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_mdestroy_d(b);
        vsip_malldestroy_d(B);
        vsip_malldestroy_d(ma);
        vsip_malldestroy_d(chk);
    }                                                       
      
    return;
}
