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
/* $Id: vgather_f.h,v 2.0 2003/02/22 15:23:29 judd Exp $ */
static void vgather_f(void){
   printf("********\nTEST vgather_f\n");
   {
        vsip_scalar_f data1[]= {1, .1, 2, .2, 3,.3, 4,-.1,  5,-.3,  6,-.4, 7,.8};
        vsip_scalar_vi  data_index[] = {2,  1, 8,  5, 11};
        vsip_scalar_f data_ans[] = { 2,  .1 ,5, .3,-.4};

        vsip_vview_f *a = vsip_vbind_f(
                  vsip_blockbind_f(data1,14,VSIP_MEM_NONE),0,1,14);

        vsip_vview_vi *index = vsip_vbind_vi(/* matrix index is always interleaved */
                  vsip_blockbind_vi(data_index,5,VSIP_MEM_NONE),0,1,5);

        vsip_vview_f *ans = vsip_vbind_f(
                  vsip_blockbind_f(data_ans,5,VSIP_MEM_NONE),0,1,5);

        vsip_vview_f *c = vsip_vcreate_f(5,VSIP_MEM_NONE);
        vsip_vview_f *chk = vsip_vcreate_f(5,VSIP_MEM_NONE);

        vsip_blockadmit_f(vsip_vgetblock_f(a),VSIP_TRUE);
        vsip_blockadmit_vi(vsip_vgetblock_vi(index),VSIP_TRUE);
        vsip_blockadmit_f(vsip_vgetblock_f(ans),VSIP_TRUE);

        printf("call vsip_vgather_f(a,index,c) \n");
        vsip_vgather_f(a,index,c);
        printf("a =\n");VU_vprintm_f("6.4",a);
        printf("index =\n");VU_vprintm_vi("",index); 
        printf("c=\n");VU_vprintm_f("6.4",c);
        printf("\nright answer =\n"); VU_vprintm_f("6.4",ans);
        vsip_vsub_f(ans,c,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,0,2 * .0001,0,1,chk);
        if(fabs(vsip_vsumval_f(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_valldestroy_f(a);
        vsip_valldestroy_vi(index);
        vsip_valldestroy_f(c);
        vsip_valldestroy_f(chk);
    }                                                       
      
    return;
}
