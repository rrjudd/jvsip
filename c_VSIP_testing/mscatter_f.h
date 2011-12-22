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
/* $Id: mscatter_f.h,v 2.0 2003/02/22 15:23:26 judd Exp $ */
static void mscatter_f(void){
    printf("\n******\nTEST mscatter_f\n");
    {
        vsip_scalar_f data1[]= {1, .1, 2, .2, 3,.3,   4,-.1, 5,  -.3, 6,-.4, 7,.8, 8,.9, 9,-1};
        vsip_scalar_vi  data_index[] = {0,1 , 1,1 , 2,3 , 3,3 , 2,1}; 
        vsip_scalar_f data_ans[] = { 0.0, -1.0, 0.0, 0.0, 
                                       0.0, 0.9, 0.0, 0.0, 
                                       0.0, -.3, 0.0, 0.8, 
                                       0.0, 0.0, 0.0, -.4};

        vsip_vview_f *a = vsip_vbind_f(
                  vsip_blockbind_f(data1,18,VSIP_MEM_NONE),17,-2,5);

        vsip_vview_mi *index = vsip_vbind_mi(/* matrix index is always interleaved */
                  vsip_blockbind_mi(data_index,5,VSIP_MEM_NONE),0,1,5);

        vsip_mview_f *ans = vsip_mbind_f(
                  vsip_blockbind_f(data_ans,16,VSIP_MEM_NONE),0,4,4,1,4);

        vsip_mview_f *b   = vsip_mcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);
        vsip_mview_f *chk = vsip_mcreate_f(4,4,VSIP_ROW,VSIP_MEM_NONE);

        vsip_blockadmit_f(vsip_vgetblock_f(a),VSIP_TRUE);
        vsip_blockadmit_mi(vsip_vgetblock_mi(index),VSIP_TRUE);
        vsip_blockadmit_f(vsip_mgetblock_f(ans),VSIP_TRUE);
     
        vsip_mfill_f(0,b);

        printf("call vsip_mscatter_f(a,b,index) \n");
        vsip_mscatter_f(a,b,index);
        printf("a =\n");VU_vprintm_f("8.6",a);
        printf("index =\n");VU_vprintm_mi("",index); 
        printf("b=\n");VU_mprintm_f("8.6",b);
        printf("\nright answer =\n"); VU_mprintm_f("6.4",ans);
        vsip_msub_f(ans,b,chk); vsip_mmag_f(chk,chk); vsip_mclip_f(chk,0,2 * .0001,0,1,chk);
        if(fabs(vsip_msumval_f(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");
       
        vsip_valldestroy_f(a);
        vsip_valldestroy_mi(index);
        vsip_malldestroy_f(b);
        vsip_malldestroy_f(chk);
    }                                                       
      
    return;
}
