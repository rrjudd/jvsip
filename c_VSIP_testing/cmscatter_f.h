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
/* $Id: cmscatter_f.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
static void cmscatter_f(void){
    printf("\n******\nTEST cmscatter_f\n");
    {
        vsip_scalar_f data1_r[]= {1, .1, 2, .2, 3,.3,   4,-.1, 5,  -.3,  6,-.4, 7,.8, 8,.9, 9,-1};
        vsip_scalar_f data1_i[]= {1,  2, 3,  4, 5, 6,   7,  8, 9,   10, 11, 12,13,14,15,16,17,18};
        vsip_scalar_vi  data_index[] = {0,1 , 1,1 , 2,3 , 3,3 , 2,1}; 
        vsip_scalar_f data_ans_r[] = { 0.0, -1.0, 0.0, 0.0, 
                                       0.0, 0.9, 0.0, 0.0, 
                                       0.0, -.3, 0.0, 0.8, 
                                       0.0, 0.0, 0.0, -.4};
        vsip_scalar_f data_ans_i[] = { 0.0, 18.0, 0.0, 0.0, 
                                       0.0, 16, 0.0, 0.0, 
                                       0.0, 10, 0.0, 14, 
                                       0.0, 0.0, 0.0, 12};

        vsip_cvview_f *a = vsip_cvbind_f(
                  vsip_cblockbind_f(data1_r,data1_i,18,VSIP_MEM_NONE),17,-2,5);

        vsip_vview_mi *index = vsip_vbind_mi(/* matrix index is always interleaved */
                  vsip_blockbind_mi(data_index,5,VSIP_MEM_NONE),0,1,5);

        vsip_cmview_f *ans = vsip_cmbind_f(
                  vsip_cblockbind_f(data_ans_r,data_ans_i,16,VSIP_MEM_NONE),0,4,4,1,4);

        vsip_cmview_f *b   = vsip_cmcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);
        vsip_cmview_f *chk = vsip_cmcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_f  *chk_i = vsip_mimagview_f(chk);

        vsip_cblockadmit_f(vsip_cvgetblock_f(a),VSIP_TRUE);
        vsip_blockadmit_mi(vsip_vgetblock_mi(index),VSIP_TRUE);
        vsip_cblockadmit_f(vsip_cmgetblock_f(ans),VSIP_TRUE);
     
        { vsip_mview_f *t = vsip_mrealview_f(b);
          vsip_mfill_f(0,t);
          vsip_mdestroy_f(t); t = vsip_mimagview_f(b);
          vsip_mfill_f(0,t);
          vsip_mdestroy_f(t);
        }

        printf("call vsip_cmscatter_f(a,b,index) \n");
        vsip_cmscatter_f(a,b,index);
        printf("a =\n");VU_cvprintm_f("8.6",a);
        printf("index =\n");VU_vprintm_mi("",index); 
        printf("b=\n");VU_cmprintm_f("8.6",b);
        printf("\nright answer =\n"); VU_cmprintm_f("6.4",ans);
        vsip_cmsub_f(ans,b,chk); vsip_cmmag_f(chk,chk_i); vsip_mclip_f(chk_i,0,2 * .0001,0,1,chk_i);
        if(fabs(vsip_msumval_f(chk_i)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_cvalldestroy_f(a);
        vsip_valldestroy_mi(index);
        vsip_cmalldestroy_f(b);
        vsip_malldestroy_f(chk_i);
        vsip_cmalldestroy_f(chk);
    }                                                       
    return;
}
