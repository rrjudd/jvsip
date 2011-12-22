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
/* $Id: vclip_f.h,v 2.1 2009/09/05 18:01:45 judd Exp $ */
static void vclip_f(void){
   printf("********\nTEST vclip_f\n");
   {
        vsip_scalar_f min_lim = -.6;
        vsip_scalar_f max_lim = .9;
        vsip_scalar_f min     = -5;
        vsip_scalar_f max     = 1;
        vsip_scalar_f data[]={0, 0.5878, 0.9511, 0.9511, 0.5878, 0.0, 
                                0.5878, -0.9511, -0.9511, -0.5878, -0.0};
        vsip_scalar_f data_ans[]={0, 0.5878, 1.0, 1.0, 0.5878, 0.0, 
                                0.5878, -5.0, -5.0, -0.5878, -0.0};
        vsip_block_f *block = vsip_blockbind_f(data,10,VSIP_MEM_NONE);
        vsip_block_f *block_ans = vsip_blockbind_f(data_ans,10,VSIP_MEM_NONE);
        vsip_vview_f *a = vsip_vbind_f(block,0,1,10);
        vsip_vview_f *ans = vsip_vbind_f(block_ans,0,1,10);
        vsip_vview_f *b = vsip_vcreate_f(10,VSIP_MEM_NONE);
        vsip_vview_f *chk = vsip_vcreate_f(10,VSIP_MEM_NONE);

        vsip_blockadmit_f(block,VSIP_TRUE);
        vsip_blockadmit_f(block_ans,VSIP_TRUE);

        printf("vsip_vclip_f(a,min_lim,max_lim,min,max,b)\n");
        vsip_vclip_f(a,min_lim,max_lim,min,max,b);
        printf("a = "); VU_vprintm_f("8.6",a);
        printf("min_lim = %4.2f\nmax_lim = %4.2f\nmin = %4.2f\nmax = %4.2f \n",
                min_lim,max_lim,min,max);
        printf("b = "); VU_vprintm_f("8.6",b);
        printf("right answer = "); VU_vprintm_f("8.6",ans);
        vsip_vsub_f(b,ans,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
        if(vsip_vsumval_f(chk) > .5)
            printf("error\n");
        else
            printf("correct\n");
        
        printf("a,b in place \n");
        vsip_vcopy_f_f(a,b);
        vsip_vclip_f(b,min_lim,max_lim,min,max,b);
        vsip_vsub_f(b,ans,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
        if(vsip_vsumval_f(chk) > .5)
            printf("error\n");
        else
            printf("correct\n");
   }
   return;
}
