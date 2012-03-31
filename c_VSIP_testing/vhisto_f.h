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
/* $Id: vhisto_f.h,v 2.0 2003/02/22 15:23:29 judd Exp $ */
#include"VU_vprintm_f.include"
static void vhisto_f(void){
   printf("********\nTEST vhisto_f\n");
   {
     vsip_scalar_f min_bin = 2.0;
     vsip_scalar_f max_bin = 20.0;
     vsip_scalar_f data[] = {0, 1, 2, 3, 4, 
                             5, 6, 14, 13, 12, 
                             11, 10, 9, 8, 7, 
                             24, 23, 22, 21, 20,
                             19, 18, 17, 16, 15};
     vsip_scalar_f ans_data[]= {2,6,6,6,5};
     vsip_block_f *block = vsip_blockbind_f(data,25,VSIP_MEM_NONE);
     vsip_vview_f *a = vsip_vbind_f(block,0,1,25);
     vsip_vview_f *hist = vsip_vcreate_f(5,VSIP_MEM_NONE);
     vsip_block_f *ans_block = vsip_blockbind_f(ans_data,5,VSIP_MEM_NONE);
     vsip_vview_f *ans = vsip_vbind_f(ans_block,0,1,5);
     vsip_vview_f *chk = vsip_vcreate_f(5,VSIP_MEM_NONE);
     vsip_blockadmit_f(block,VSIP_TRUE);
     vsip_blockadmit_f(ans_block,VSIP_TRUE);

     vsip_vhisto_f(a,min_bin,max_bin,VSIP_HIST_RESET,hist);

     printf("vsip_vhisto_f(a,min_bin,max_bin,VSIP_HIST_RESET,hist)\n");
     printf("min_bin %f\n",min_bin);
     printf("max_bin %f\n",max_bin);
     printf("a = "); VU_vprintm_f("15.12",a);
     printf("hist = "); VU_vprintm_f("4.0",hist);
     printf("expected histogram = "); VU_vprintm_f("4.0",ans);
     vsip_vsub_f(hist,ans,chk); vsip_vmag_f(chk,chk);
     if(vsip_vsumval_f(chk) > .0005)
        printf("error\n");
     else
        printf("correct\n");
     vsip_valldestroy_f(a);
     vsip_valldestroy_f(hist);
     vsip_valldestroy_f(ans);
     vsip_valldestroy_f(chk);
   }
   return;
}
