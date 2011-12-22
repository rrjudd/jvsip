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
/* $Id: cmgather_d.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
static void cmgather_d(void){
    printf("\n******\nTEST cmgather_d\n");
    {
        vsip_scalar_d data1_r[]= {1, .1, 2, .2, 3,.3,   4,-.1, 5,  -.3,  6,-.4, 7,.8, 8,.9, 9,-1};
        vsip_scalar_d data1_i[]= {1,  2, 3,  4, 5, 6,   7,  8, 9,   10, 11, 12,13,14,15,16,17,18};
        vsip_scalar_vi  data_index[] = {0,1 , 1,1 , 2,3 , 3,3 , 2,1}; 
        vsip_scalar_d data_ans_r[] = {.1,.3,-.4, .9, -.3};
        vsip_scalar_d data_ans_i[] = { 2, 6,  12, 16,  10};

        vsip_cmview_d *a = vsip_cmbind_d(
                  vsip_cblockbind_d(data1_r,data1_i,18,VSIP_MEM_NONE),0,4,4,1,4);

        vsip_vview_mi *index = vsip_vbind_mi(/* matrix index is always interleaved */
                  vsip_blockbind_mi(data_index,5,VSIP_MEM_NONE),0,1,5);

        vsip_cvview_d *ans = vsip_cvbind_d(
                  vsip_cblockbind_d(data_ans_r,data_ans_i,9,VSIP_MEM_NONE),0,1,5);

        vsip_cvview_d *c   = vsip_cvcreate_d(5,VSIP_MEM_NONE);
        vsip_cvview_d *chk = vsip_cvcreate_d(5,VSIP_MEM_NONE);
        vsip_vview_d  *chk_i = vsip_vimagview_d(chk);

        vsip_cblockadmit_d(vsip_cmgetblock_d(a),VSIP_TRUE);
        vsip_blockadmit_mi(vsip_vgetblock_mi(index),VSIP_TRUE);
        vsip_cblockadmit_d(vsip_cvgetblock_d(ans),VSIP_TRUE);
     
        printf("call vsip_cmgather_d(a,index,c) \n");
        vsip_cmgather_d(a,index,c);
        printf("a =\n");VU_cmprintm_d("8.6",a);
        printf("index =\n");VU_vprintm_mi("",index); 
        printf("c=\n");VU_cvprintm_d("8.6",c);
        printf("\nright answer =\n"); VU_cvprintm_d("6.4",ans);
        vsip_cvsub_d(ans,c,chk); vsip_cvmag_d(chk,chk_i); vsip_vclip_d(chk_i,0,2 * .0001,0,1,chk_i);
        if(fabs(vsip_vsumval_d(chk_i)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_cmalldestroy_d(a);
        vsip_valldestroy_mi(index);
        vsip_cvalldestroy_d(c);
        vsip_cvalldestroy_d(ans);
        vsip_valldestroy_d(chk_i);
        vsip_cvalldestroy_d(chk);
    }                                                       
    return;
}
