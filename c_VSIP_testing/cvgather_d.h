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
/* $Id: cvgather_d.h,v 2.0 2003/02/22 15:23:22 judd Exp $ */
#include"VU_cvprintm_d.include"
#include"VU_vprintm_vi.include"
 void cvgather_d(void){
   printf("********\nTEST cvgather_d\n");
   {
        vsip_scalar_d data1_r[]= {1, .1, 2, .2, 3,.3, 4,-.1,  5,-.3,  6,-.4, 7,.8};
        vsip_scalar_d data1_i[]= {.1, 2,.2, -3,.3, 4,-.1, 3,-.3,  2,-.4,  7,.8, 1};
        vsip_scalar_vi  data_index[] = {2,  1, 8, 5, 11};
        vsip_scalar_d data_ans_r[] = { 2,.1  ,5,.3,-.4};
        vsip_scalar_d data_ans_i[] = {.2 ,2, -.3, 4,  7};

        vsip_cvview_d *a = vsip_cvbind_d(
                  vsip_cblockbind_d(data1_r,data1_i,14,VSIP_MEM_NONE),0,1,14);

        vsip_vview_vi *index = vsip_vbind_vi(/* matrix index is always interleaved */
                  vsip_blockbind_vi(data_index,5,VSIP_MEM_NONE),0,1,5);

        vsip_cvview_d *ans = vsip_cvbind_d(
                  vsip_cblockbind_d(data_ans_r,data_ans_i,5,VSIP_MEM_NONE),0,1,5);

        vsip_cvview_d *c = vsip_cvcreate_d(5,VSIP_MEM_NONE);
        vsip_cvview_d *chk = vsip_cvcreate_d(5,VSIP_MEM_NONE);
        vsip_vview_d *chk_r = vsip_vrealview_d(chk);

        vsip_cblockadmit_d(vsip_cvgetblock_d(a),VSIP_TRUE);
        vsip_blockadmit_vi(vsip_vgetblock_vi(index),VSIP_TRUE);
        vsip_cblockadmit_d(vsip_cvgetblock_d(ans),VSIP_TRUE);

        printf("call vsip_vgather_d(a,index,c) \n");
        vsip_cvgather_d(a,index,c);
        printf("a =\n");VU_cvprintm_d("6.4",a);
        printf("index =\n");VU_vprintm_vi("",index); 
        printf("c=\n");VU_cvprintm_d("6.4",c);
        printf("\nright answer =\n"); VU_cvprintm_d("6.4",ans);
        vsip_cvsub_d(ans,c,chk); vsip_cvmag_d(chk,chk_r); vsip_vclip_d(chk_r,0,2 * .0001,0,1,chk_r);
        if(fabs(vsip_vsumval_d(chk_r)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_cvalldestroy_d(a);
        vsip_valldestroy_vi(index);
        vsip_cvalldestroy_d(c);
        vsip_vdestroy_d(chk_r);
        vsip_cvalldestroy_d(chk);
    }                                                       
      
    return;
}
