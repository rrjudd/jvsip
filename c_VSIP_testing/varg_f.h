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
/* $Id: varg_f.h,v 2.0 2003/02/22 15:23:28 judd Exp $ */
#include"VU_vprintm_f.include"
#include"VU_cvprintm_f.include"
static void varg_f(void){
    printf("\n*****\nTEST varg_f\n");
    {
       vsip_cvview_f *a = vsip_cvcreate_f(22,VSIP_MEM_NONE);
       vsip_cvview_f *b = vsip_cvsubview_f(a,2,6);
       vsip_vview_f *chk = vsip_vcreate_f(6,VSIP_MEM_NONE);
       vsip_vview_f *b_r, *b_i;
       vsip_vview_f  *arg = vsip_vcreate_f(6,VSIP_MEM_NONE);
       vsip_scalar_f data[] = {1.5708, 1.4601, 1.3258, 1.1659, .9828, .7854};
       vsip_block_f *block = vsip_blockbind_f(data,6,VSIP_MEM_NONE);
       vsip_vview_f *ans = vsip_vbind_f(block,0,1,6);
       vsip_blockadmit_f(block,VSIP_TRUE);
       vsip_cvputstride_f(b,2);
       b_r = vsip_vrealview_f(b);
       b_i = vsip_vimagview_f(b);
       vsip_vramp_f(0,.1,b_r);
       vsip_vramp_f(1,-.1,b_i);
       printf("input vector\n"); VU_cvprintm_f("8.6",b);
       vsip_varg_f(b,arg);
       printf("varg_f(b,arg)\n"); VU_vprintm_f("8.6",arg);
       printf("answer to 4 digits\n"); VU_vprintm_f("8.4",ans); 
       vsip_vsub_f(arg,ans,chk);
       vsip_vmag_f(chk,chk);
       if(vsip_vsumval_f(chk) > .0006)
         printf("error\n");
       else
         printf("correct\n");
       vsip_cvdestroy_f(b); vsip_vdestroy_f(b_i); vsip_vdestroy_f(b_r);
       vsip_cvalldestroy_f(a);
       vsip_valldestroy_f(arg); vsip_valldestroy_f(ans); vsip_valldestroy_f(chk);
    }
    return;
}

