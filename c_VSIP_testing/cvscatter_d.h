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
/* $Id: cvscatter_d.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
static void cvscatter_d(void){
   printf("********\nTEST cvscatter_d\n");
   {
        vsip_scalar_d data1_r[]= {1, 2,3,4, 5, 6};
        vsip_scalar_d data1_i[]= {0,-1,1,2,-2,10};
        vsip_scalar_vi  data_index[] = {3, 2, 5, 6, 1,10};
        vsip_scalar_d data_ans_r[] = {0, 5, 2, 1,0,3, 4,0,0, 0, 6};
        vsip_scalar_d data_ans_i[] = {0,-2,-1, 0,0,1, 2,0,0, 0,10};
        vsip_cvview_d *a = vsip_cvbind_d(
                  vsip_cblockbind_d(data1_r,data1_i,6,VSIP_MEM_NONE),0,1,6);

        vsip_vview_vi *index = vsip_vbind_vi(/* matrix index is always interleaved */
                  vsip_blockbind_vi(data_index,6,VSIP_MEM_NONE),0,1,6);

        vsip_cvview_d *ans = vsip_cvbind_d(
                  vsip_cblockbind_d(data_ans_r,data_ans_i,11,VSIP_MEM_NONE),0,1,11);

        vsip_cvview_d *b   = vsip_cvcreate_d(11,VSIP_MEM_NONE);
        vsip_cvview_d *chk = vsip_cvcreate_d(11,VSIP_MEM_NONE);
        vsip_vview_d *chk_r = vsip_vrealview_d(chk);

        vsip_cblockadmit_d(vsip_cvgetblock_d(a),VSIP_TRUE);
        vsip_blockadmit_vi(vsip_vgetblock_vi(index),VSIP_TRUE);
        vsip_cblockadmit_d(vsip_cvgetblock_d(ans),VSIP_TRUE);

        vsip_cvfill_d(vsip_cmplx_d(0,VSIP_MEM_NONE),b);

        printf("call vsip_cvscatter_d(a,b,index) \n");
        vsip_cvscatter_d(a,b,index); 
        printf("a =\n");VU_cvprintm_d("8.6",a);
        printf("index =\n");VU_vprintm_vi("",index);
        printf("b=\n");VU_cvprintm_d("8.6",b);
        printf("\nright answer =\n"); VU_cvprintm_d("6.4",ans);
        vsip_cvsub_d(ans,b,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,0,2 * .0001,0,1,chk_r);
        if(fabs(vsip_vsumval_d(chk_r)) > .5)
            printf("error\n");
        else
            printf("correct\n");

        vsip_cvalldestroy_d(a);
        vsip_valldestroy_vi(index);
        vsip_cvalldestroy_d(b);
        vsip_vdestroy_d(chk_r);
        vsip_cvalldestroy_d(chk);
   }
   return;
}
