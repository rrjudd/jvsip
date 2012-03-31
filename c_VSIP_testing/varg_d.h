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
/* $Id: varg_d.h,v 2.0 2003/02/22 15:23:28 judd Exp $ */
#include"VU_vprintm_d.include"
#include"VU_cvprintm_d.include"
static void varg_d(void){
    printf("\n*****\nTEST varg_d\n");
    {
       vsip_cvview_d *a = vsip_cvcreate_d(22,VSIP_MEM_NONE);
       vsip_cvview_d *b = vsip_cvsubview_d(a,2,6);
       vsip_vview_d *chk = vsip_vcreate_d(6,VSIP_MEM_NONE);
       vsip_vview_d *b_r, *b_i;
       vsip_vview_d  *arg = vsip_vcreate_d(6,VSIP_MEM_NONE);
       vsip_scalar_d data[] = {1.5708, 1.4601, 1.3258, 1.1659, .9828, .7854};
       vsip_block_d *block = vsip_blockbind_d(data,6,VSIP_MEM_NONE);
       vsip_vview_d *ans = vsip_vbind_d(block,0,1,6);
       vsip_blockadmit_d(block,VSIP_TRUE);
       vsip_cvputstride_d(b,2);
       b_r = vsip_vrealview_d(b);
       b_i = vsip_vimagview_d(b);
       vsip_vramp_d(0,.1,b_r);
       vsip_vramp_d(1,-.1,b_i);
       printf("input vector\n"); VU_cvprintm_d("8.6",b);
       vsip_varg_d(b,arg);
       printf("varg_d(b,arg)\n"); VU_vprintm_d("8.6",arg);
       printf("answer to 4 digits\n"); VU_vprintm_d("8.4",ans); 
       vsip_vsub_d(arg,ans,chk);
       vsip_vmag_d(chk,chk);
       if(vsip_vsumval_d(chk) > .0006)
         printf("error\n");
       else
         printf("correct\n");
       vsip_cvdestroy_d(b); vsip_vdestroy_d(b_i); vsip_vdestroy_d(b_r);
       vsip_cvalldestroy_d(a);
       vsip_valldestroy_d(arg); vsip_valldestroy_d(ans); vsip_valldestroy_d(chk);
    }
    return;
}

