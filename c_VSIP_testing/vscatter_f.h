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
/* $Id: vscatter_f.h,v 2.0 2003/02/22 15:23:30 judd Exp $ */
#include"VU_vprintm_f.include"
#include"VU_vprintm_vi.include"
static void vscatter_f(void){
   printf("********\nTEST vscatter_f\n");
   {
        vsip_scalar_f data1[]= {1,2,3,4,5,6};
        vsip_scalar_vi  data_index[] = {3, 2, 5, 6, 1,10};
        vsip_scalar_f data_ans[] = {0,5,2,1,0,
                                      3,4,0,
                                      0,0,6};
        vsip_vview_f *a = vsip_vbind_f(
                  vsip_blockbind_f(data1,6,VSIP_MEM_NONE),0,1,6);

        vsip_vview_vi *index = vsip_vbind_vi(/* matrix index is always interleaved */
                  vsip_blockbind_vi(data_index,6,VSIP_MEM_NONE),0,1,6);

        vsip_vview_f *ans = vsip_vbind_f(
                  vsip_blockbind_f(data_ans,11,VSIP_MEM_NONE),0,1,11);

        vsip_vview_f *b   = vsip_vcreate_f(11,VSIP_MEM_NONE);
        vsip_vview_f *chk = vsip_vcreate_f(11,VSIP_MEM_NONE);

        vsip_blockadmit_f(vsip_vgetblock_f(a),VSIP_TRUE);
        vsip_blockadmit_vi(vsip_vgetblock_vi(index),VSIP_TRUE);
        vsip_blockadmit_f(vsip_vgetblock_f(ans),VSIP_TRUE);

        vsip_vfill_f(0,b);

        printf("call vsip_vscatter_f(a,b,index) \n");
        vsip_vscatter_f(a,b,index);
        printf("a =\n");VU_vprintm_f("8.6",a);
        printf("index =\n");VU_vprintm_vi("",index);
        printf("b=\n");VU_vprintm_f("8.6",b);
        printf("\nright answer =\n"); VU_vprintm_f("6.4",ans);
        vsip_vsub_f(ans,b,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,0,2 * .0001,0,1,chk);
        if(fabs(vsip_vsumval_f(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");

        vsip_valldestroy_f(a);
        vsip_valldestroy_vi(index);
        vsip_valldestroy_f(b);
        vsip_valldestroy_f(chk);
   }
   return;
}
