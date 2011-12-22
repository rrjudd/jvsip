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
/* $Id: mswap_d.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
static void mswap_d(void){
    printf("\n******\nTEST mswap_d\n");
    {
        vsip_scalar_d data1[]= {1, 2, 3, 4, 5, 6, 7, 8, 9};
        vsip_scalar_d data2[]= {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
        vsip_mview_d *a      = vsip_mbind_d(
                  vsip_blockbind_d(data1,9,VSIP_MEM_NONE),0,3,3,1,3);
        vsip_mview_d *b      = vsip_mbind_d(
                  vsip_blockbind_d(data2,9,VSIP_MEM_NONE),0,1,3,3,3);
        vsip_mview_d *a0     = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_d *b0     = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_d *chk    = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);

        vsip_blockadmit_d(vsip_mgetblock_d(a),VSIP_TRUE);
        vsip_blockadmit_d(vsip_mgetblock_d(b),VSIP_TRUE);

        vsip_mcopy_d_d(a,a0);
        vsip_mcopy_d_d(b,b0);

        printf("a =\n");VU_mprintm_d("8.6",a);
        printf("b =\n");VU_mprintm_d("8.6",b);
        printf("call vsip_mswap_d(a,b)\n");
        vsip_mswap_d(a,b);
        printf("a =\n");VU_mprintm_d("8.6",a);
        printf("b =\n");VU_mprintm_d("8.6",b);

        vsip_msub_d(a,b0,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_d(chk)) > .5)
            printf("error in <a>\n");
        else
            printf("<a> correct\n");
       
        vsip_msub_d(b,a0,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,0,.0001,0,1,chk);
        if(fabs(vsip_msumval_d(chk)) > .5)
            printf("error in <b>\n");
        else
            printf("<b> correct\n");

        vsip_malldestroy_d(a); vsip_malldestroy_d(a0);
        vsip_malldestroy_d(b); vsip_malldestroy_d(b0);
        vsip_malldestroy_d(chk);
    }                                                       
    return;
}
