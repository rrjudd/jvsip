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
/* $Id: vscatter_d.h,v 2.0 2003/02/22 15:23:30 judd Exp $ */
#include"VU_vprintm_d.include"
#include"VU_vprintm_vi.include"
 void vscatter_d(void){
   printf("********\nTEST vscatter_d\n");
   {
        vsip_scalar_d data1[]= {1,2,3,4,5,6};
        vsip_scalar_vi  data_index[] = {3, 2, 5, 6, 1,10};
        vsip_scalar_d data_ans[] = {0,5,2,1,0,
                                      3,4,0,
                                      0,0,6};
        vsip_vview_d *a = vsip_vbind_d(
                  vsip_blockbind_d(data1,6,VSIP_MEM_NONE),0,1,6);

        vsip_vview_vi *index = vsip_vbind_vi(/* matrix index is always interleaved */
                  vsip_blockbind_vi(data_index,6,VSIP_MEM_NONE),0,1,6);

        vsip_vview_d *ans = vsip_vbind_d(
                  vsip_blockbind_d(data_ans,11,VSIP_MEM_NONE),0,1,11);

        vsip_vview_d *b   = vsip_vcreate_d(11,VSIP_MEM_NONE);
        vsip_vview_d *chk = vsip_vcreate_d(11,VSIP_MEM_NONE);

        vsip_blockadmit_d(vsip_vgetblock_d(a),VSIP_TRUE);
        vsip_blockadmit_vi(vsip_vgetblock_vi(index),VSIP_TRUE);
        vsip_blockadmit_d(vsip_vgetblock_d(ans),VSIP_TRUE);

        vsip_vfill_d(0,b);

        printf("call vsip_vscatter_d(a,b,index) \n");
        vsip_vscatter_d(a,b,index);
        printf("a =\n");VU_vprintm_d("8.6",a);
        printf("index =\n");VU_vprintm_vi("",index);
        printf("b=\n");VU_vprintm_d("8.6",b);
        printf("\nright answer =\n"); VU_vprintm_d("6.4",ans);
        vsip_vsub_d(ans,b,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,0,2 * .0001,0,1,chk);
        if(fabs(vsip_vsumval_d(chk)) > .5)
            printf("error\n");
        else
            printf("correct\n");

        vsip_valldestroy_d(a);
        vsip_valldestroy_vi(index);
        vsip_valldestroy_d(b);
        vsip_valldestroy_d(chk);
   }
   return;
}
