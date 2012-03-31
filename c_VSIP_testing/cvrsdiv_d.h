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
/* $Id: cvrsdiv_d.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
#include"VU_cvprintm_d.include"
static void cvrsdiv_d(void){
    printf("\n********\nTEST cvrsdiv_d\n");
    {
       vsip_scalar_d  beta = 2.5;
       vsip_cvview_d *a = vsip_cvcreate_d(7,VSIP_MEM_NONE);
       vsip_cvview_d *c = vsip_cvcreate_d(7,VSIP_MEM_NONE);
       vsip_vview_d  *c_i = vsip_vimagview_d(c);
       vsip_cvview_d *chk = vsip_cvcreate_d(7,VSIP_MEM_NONE);
       vsip_vview_d  *chk_i = vsip_vimagview_d(chk);
       vsip_scalar_d data_r[] ={.1, .2, .3, .4, .5, .6, .7};
       vsip_scalar_d data_i[] ={7,6,5,4,3,2,1};
       vsip_scalar_d data_ans[] ={0.0400, 2.8000, 0.0800, 2.4000,
                       0.1200, 2.0000, 0.1600, 1.600, 0.2000, 1.2000,
                       0.2400, 0.8000, 0.2800, 0.4000};
       vsip_cblock_d *cblock = vsip_cblockbind_d(data_r,data_i,7,VSIP_MEM_NONE);
       vsip_cblock_d *cblock_ans = vsip_cblockbind_d(data_ans,
                           (vsip_scalar_d*)NULL,7,VSIP_MEM_NONE);
       vsip_cvview_d *u_a = vsip_cvbind_d(cblock,0,1,7);
       vsip_cvview_d *u_ans = vsip_cvbind_d(cblock_ans,0,1,7);

       vsip_cblockadmit_d(cblock,VSIP_TRUE);
       vsip_cblockadmit_d(cblock_ans,VSIP_TRUE);

       vsip_cvcopy_d_d(u_a,a);
       printf("call vsip_cvrsdiv_d(a,beta,c)\n");
       printf("beta = %f\n",beta);
       printf("a =\n");VU_cvprintm_d("8.6",a); 
       printf("test normal out of place\n");
       vsip_cvrsdiv_d(a,beta,c);
       printf("c =\n");VU_cvprintm_d("8.6",c); 
       printf("right answer =\n");VU_cvprintm_d("8.4",u_ans); 

       vsip_cvsub_d(u_ans,c,chk);
       vsip_cvmag_d(chk,chk_i);
       vsip_vclip_d(chk_i,.0002,.0002,0,1,chk_i);
       if(vsip_vsumval_d(chk_i) > .5)
            printf("error\n");
       else
            printf("correct\n");

       
       printf("test a,c inplace\n");
       vsip_cvrsdiv_d(a,beta,a);
       vsip_cvsub_d(u_ans,a,chk);
       vsip_cvmag_d(chk,chk_i);
       vsip_vclip_d(chk_i,.0002,.0002,0,1,chk_i);
       if(vsip_vsumval_d(chk_i) > .5)
            printf("error\n");
       else
            printf("correct\n");

       vsip_cvalldestroy_d(a);
       vsip_vdestroy_d(c_i); vsip_cvalldestroy_d(c);
       vsip_vdestroy_d(chk_i); vsip_cvalldestroy_d(chk);
       vsip_cvalldestroy_d(u_a);
       vsip_cvalldestroy_d(u_ans);

    }
    return;
}
