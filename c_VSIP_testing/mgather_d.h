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
/* $Id: mgather_d.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
#include"VU_mprintm_d.include"
#include"VU_vprintm_d.include"
#include"VU_vprintm_mi.include"
 void mgather_d(void){
    printf("\n******\nTEST mgather_d\n");
    {
        vsip_scalar_d data1[]= {1,.1, 2,.2, 3,.3, 4,-.1, 5,-.3, 6,-.4, 7,.8, 8,.9, 9,-1};
        vsip_scalar_vi  data_index[] = {0,1 , 1,1 , 2,3 , 3,3 , 2,1}; 
        vsip_scalar_d data_ans[] = {  .1,   .3,  -.4,   .9,  -.3};

        vsip_mview_d *a = vsip_mbind_d(
                  vsip_blockbind_d(data1,18,VSIP_MEM_NONE),0,4,4,1,4);

        vsip_vview_mi *index = vsip_vbind_mi(/* matrix index is always interleaved */
                  vsip_blockbind_mi(data_index,5,VSIP_MEM_NONE),0,1,5);

        vsip_vview_d *ans = vsip_vbind_d(
                  vsip_blockbind_d(data_ans,5,VSIP_MEM_NONE),0,1,5);

        vsip_vview_d *c = vsip_vcreate_d(5,VSIP_MEM_NONE);
        vsip_vview_d *chk = vsip_vcreate_d(5,VSIP_MEM_NONE);

        vsip_blockadmit_d(vsip_mgetblock_d(a),VSIP_TRUE);
        vsip_blockadmit_mi(vsip_vgetblock_mi(index),VSIP_TRUE);
        vsip_blockadmit_d(vsip_vgetblock_d(ans),VSIP_TRUE);

        printf("call vsip_mgather_d(a,index,c) \n");
        vsip_mgather_d(a,index,c);
        printf("a =\n");VU_mprintm_d("8.6",a);
        printf("index =\n");VU_vprintm_mi("",index); 
        printf("c=\n");VU_vprintm_d("8.6",c);
        printf("\nright answer =\n"); VU_vprintm_d("6.4",ans);
        vsip_vsub_d(ans,c,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,0,2 * .0001,0,1,chk);
        if(fabs(vsip_vsumval_d(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_malldestroy_d(a);
        vsip_valldestroy_mi(index);
        vsip_valldestroy_d(c);
        vsip_valldestroy_d(chk);
    }                                                       
      
    return;
}
