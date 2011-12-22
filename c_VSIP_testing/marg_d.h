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
/* $Id: marg_d.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
static void marg_d(void){
    printf("\n*****\nTEST marg_d\n");
    {
       vsip_cmview_d *a = vsip_cmcreate_d(22,22,VSIP_COL,VSIP_MEM_NONE);
       vsip_cvview_d *a_v = vsip_cvbind_d(vsip_cmgetblock_d(a),0,1,22*22);
       vsip_cmview_d *b = vsip_cmsubview_d(a,0,0,3,3);
       vsip_mview_d *chk = vsip_mcreate_d(3,3,VSIP_ROW,VSIP_MEM_NONE);
       vsip_vview_d *a_r, *a_i;
       vsip_mview_d  *arg = vsip_mcreate_d(3,3,VSIP_COL,VSIP_MEM_NONE);
       vsip_scalar_d data[] = {1.5708, 0.5880, -.1651, 1.3258, .2450, -.2783, .9828, 0.0, -.3588};
       vsip_block_d *block = vsip_blockbind_d(data,9,VSIP_MEM_NONE);
       vsip_mview_d *ans = vsip_mbind_d(block,0,3,3,1,3);
       vsip_blockadmit_d(block,VSIP_TRUE);
       vsip_cmputrowstride_d(b,6);
       vsip_cmputcolstride_d(b,2);
       a_r = vsip_vrealview_d(a_v);
       a_i = vsip_vimagview_d(a_v);
       vsip_vramp_d(0,.1,a_r);
       vsip_vramp_d(1,-.1,a_i);
       printf("call vsip_marg_d(b,arg)\n");
       printf("input matrix b\n"); VU_cmprintm_d("8.6",b);
       vsip_marg_d(b,arg);
       printf("output arg\n"); VU_mprintm_d("8.6",arg);
       printf("answer to 4 digits\n"); VU_mprintm_d("8.4",ans); 
       vsip_msub_d(arg,ans,chk); vsip_mmag_d(chk,chk);
       if(vsip_msumval_d(chk) > .0009)
         printf("error\n");
       else
         printf("correct\n");
       vsip_cmdestroy_d(b); 
       vsip_vdestroy_d(a_i); vsip_vdestroy_d(a_r);
       vsip_cvdestroy_d(a_v);
       vsip_cmalldestroy_d(a);
       vsip_malldestroy_d(arg); vsip_malldestroy_d(ans); vsip_malldestroy_d(chk);
    }
    return;
}

