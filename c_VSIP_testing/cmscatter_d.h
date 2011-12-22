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
/* $Id: cmscatter_d.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
static void cmscatter_d(void){
    printf("\n******\nTEST cmscatter_d\n");
    {
        vsip_scalar_d data1_r[]= {1, .1, 2, .2, 3,.3,   4,-.1, 5,  -.3,  6,-.4, 7,.8, 8,.9, 9,-1};
        vsip_scalar_d data1_i[]= {1,  2, 3,  4, 5, 6,   7,  8, 9,   10, 11, 12,13,14,15,16,17,18};
        vsip_scalar_vi  data_index[] = {0,1 , 1,1 , 2,3 , 3,3 , 2,1}; 
        vsip_scalar_d data_ans_r[] = { 0.0, -1.0, 0.0, 0.0, 
                                       0.0, 0.9, 0.0, 0.0, 
                                       0.0, -.3, 0.0, 0.8, 
                                       0.0, 0.0, 0.0, -.4};
        vsip_scalar_d data_ans_i[] = { 0.0, 18.0, 0.0, 0.0, 
                                       0.0, 16, 0.0, 0.0, 
                                       0.0, 10, 0.0, 14, 
                                       0.0, 0.0, 0.0, 12};

        vsip_cvview_d *a = vsip_cvbind_d(
                  vsip_cblockbind_d(data1_r,data1_i,18,VSIP_MEM_NONE),17,-2,5);

        vsip_vview_mi *index = vsip_vbind_mi(/* matrix index is always interleaved */
                  vsip_blockbind_mi(data_index,5,VSIP_MEM_NONE),0,1,5);

        vsip_cmview_d *ans = vsip_cmbind_d(
                  vsip_cblockbind_d(data_ans_r,data_ans_i,16,VSIP_MEM_NONE),0,4,4,1,4);

        vsip_cmview_d *b   = vsip_cmcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);
        vsip_cmview_d *chk = vsip_cmcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_d  *chk_i = vsip_mimagview_d(chk);

        vsip_cblockadmit_d(vsip_cvgetblock_d(a),VSIP_TRUE);
        vsip_blockadmit_mi(vsip_vgetblock_mi(index),VSIP_TRUE);
        vsip_cblockadmit_d(vsip_cmgetblock_d(ans),VSIP_TRUE);
     
        { vsip_mview_d *t = vsip_mrealview_d(b);
          vsip_mfill_d(0,t);
          vsip_mdestroy_d(t); t = vsip_mimagview_d(b);
          vsip_mfill_d(0,t);
          vsip_mdestroy_d(t);
        }

        printf("call vsip_cmscatter_d(a,b,index) \n");
        vsip_cmscatter_d(a,b,index);
        printf("a =\n");VU_cvprintm_d("8.6",a);
        printf("index =\n");VU_vprintm_mi("",index); 
        printf("b=\n");VU_cmprintm_d("8.6",b);
        printf("\nright answer =\n"); VU_cmprintm_d("6.4",ans);
        vsip_cmsub_d(ans,b,chk); vsip_cmmag_d(chk,chk_i); vsip_mclip_d(chk_i,0,2 * .0001,0,1,chk_i);
        if(fabs(vsip_msumval_d(chk_i)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_cvalldestroy_d(a);
        vsip_valldestroy_mi(index);
        vsip_cmalldestroy_d(b);
        vsip_malldestroy_d(chk_i);
        vsip_cmalldestroy_d(chk);
    }                                                       
    return;
}
