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
/* $Id: marg_f.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
static void marg_f(void){
    printf("\n*****\nTEST marg_f\n");
    {
       vsip_cmview_f *a = vsip_cmcreate_f(22,22,VSIP_COL,VSIP_MEM_NONE);
       vsip_cvview_f *a_v = vsip_cvbind_f(vsip_cmgetblock_f(a),0,1,22*22);
       vsip_cmview_f *b = vsip_cmsubview_f(a,0,0,3,3);
       vsip_mview_f *chk = vsip_mcreate_f(3,3,VSIP_ROW,VSIP_MEM_NONE);
       vsip_vview_f *a_r, *a_i;
       vsip_mview_f  *arg = vsip_mcreate_f(3,3,VSIP_COL,VSIP_MEM_NONE);
       vsip_scalar_f data[] = {1.5708, 0.5880, -.1651, 1.3258, .2450, -.2783, .9828, 0.0, -.3588};
       vsip_block_f *block = vsip_blockbind_f(data,9,VSIP_MEM_NONE);
       vsip_mview_f *ans = vsip_mbind_f(block,0,3,3,1,3);
       vsip_blockadmit_f(block,VSIP_TRUE);
       vsip_cmputrowstride_f(b,6);
       vsip_cmputcolstride_f(b,2);
       a_r = vsip_vrealview_f(a_v);
       a_i = vsip_vimagview_f(a_v);
       vsip_vramp_f(0,.1,a_r);
       vsip_vramp_f(1,-.1,a_i);
       printf("call vsip_marg_f(b,arg)\n");
       printf("input matrix b\n"); VU_cmprintm_f("8.6",b);
       vsip_marg_f(b,arg);
       printf("output arg\n"); VU_mprintm_f("8.6",arg);
       printf("answer to 4 digits\n"); VU_mprintm_f("8.4",ans); 
       vsip_msub_f(arg,ans,chk); vsip_mmag_f(chk,chk);
       if(vsip_msumval_f(chk) > .0009)
         printf("error\n");
       else
         printf("correct\n");
       vsip_cmdestroy_f(b); 
       vsip_vdestroy_f(a_i); vsip_vdestroy_f(a_r);
       vsip_cvdestroy_f(a_v);
       vsip_cmalldestroy_f(a);
       vsip_malldestroy_f(arg); vsip_malldestroy_f(ans); vsip_malldestroy_f(chk);
    }
    return;
}

