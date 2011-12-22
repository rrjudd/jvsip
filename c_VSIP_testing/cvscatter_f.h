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
/* $Id: cvscatter_f.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
static void cvscatter_f(void){
   printf("********\nTEST cvscatter_f\n");
   {
        vsip_scalar_f data1_r[]= {1, 2,3,4, 5, 6};
        vsip_scalar_f data1_i[]= {0,-1,1,2,-2,10};
        vsip_scalar_vi  data_index[] = {3, 2, 5, 6, 1,10};
        vsip_scalar_f data_ans_r[] = {0, 5, 2, 1,0,3, 4,0,0, 0, 6};
        vsip_scalar_f data_ans_i[] = {0,-2,-1, 0,0,1, 2,0,0, 0,10};
        vsip_cvview_f *a = vsip_cvbind_f(
                  vsip_cblockbind_f(data1_r,data1_i,6,VSIP_MEM_NONE),0,1,6);

        vsip_vview_vi *index = vsip_vbind_vi(/* matrix index is always interleaved */
                  vsip_blockbind_vi(data_index,6,VSIP_MEM_NONE),0,1,6);

        vsip_cvview_f *ans = vsip_cvbind_f(
                  vsip_cblockbind_f(data_ans_r,data_ans_i,11,VSIP_MEM_NONE),0,1,11);

        vsip_cvview_f *b   = vsip_cvcreate_f(11,VSIP_MEM_NONE);
        vsip_cvview_f *chk = vsip_cvcreate_f(11,VSIP_MEM_NONE);
        vsip_vview_f *chk_r = vsip_vrealview_f(chk);

        vsip_cblockadmit_f(vsip_cvgetblock_f(a),VSIP_TRUE);
        vsip_blockadmit_vi(vsip_vgetblock_vi(index),VSIP_TRUE);
        vsip_cblockadmit_f(vsip_cvgetblock_f(ans),VSIP_TRUE);

        vsip_cvfill_f(vsip_cmplx_f(0,VSIP_MEM_NONE),b);

        printf("call vsip_cvscatter_f(a,b,index) \n");
        vsip_cvscatter_f(a,b,index); 
        printf("a =\n");VU_cvprintm_f("8.6",a);
        printf("index =\n");VU_vprintm_vi("",index);
        printf("b=\n");VU_cvprintm_f("8.6",b);
        printf("\nright answer =\n"); VU_cvprintm_f("6.4",ans);
        vsip_cvsub_f(ans,b,chk); vsip_cvmag_f(chk,chk_r); vsip_vclip_f(chk_r,0,2 * .0001,0,1,chk_r);
        if(fabs(vsip_vsumval_f(chk_r)) > .5)
            printf("error\n");
        else
            printf("correct\n");

        vsip_cvalldestroy_f(a);
        vsip_valldestroy_vi(index);
        vsip_cvalldestroy_f(b);
        vsip_vdestroy_f(chk_r);
        vsip_cvalldestroy_f(chk);
   }
   return;
}
