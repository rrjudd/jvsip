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
/* $Id: cvrsdiv_f.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
static void cvrsdiv_f(void){
    printf("\n********\nTEST cvrsdiv_f\n");
    {
       vsip_scalar_f  beta = 2.5;
       vsip_cvview_f *a = vsip_cvcreate_f(7,VSIP_MEM_NONE);
       vsip_cvview_f *c = vsip_cvcreate_f(7,VSIP_MEM_NONE);
       vsip_vview_f  *c_i = vsip_vimagview_f(c);
       vsip_cvview_f *chk = vsip_cvcreate_f(7,VSIP_MEM_NONE);
       vsip_vview_f  *chk_i = vsip_vimagview_f(chk);
       vsip_scalar_f data_r[] ={.1, .2, .3, .4, .5, .6, .7};
       vsip_scalar_f data_i[] ={7,6,5,4,3,2,1};
       vsip_scalar_f data_ans[] ={0.0400, 2.8000, 0.0800, 2.4000,
                       0.1200, 2.0000, 0.1600, 1.600, 0.2000, 1.2000,
                       0.2400, 0.8000, 0.2800, 0.4000};
       vsip_cblock_f *cblock = vsip_cblockbind_f(data_r,data_i,7,VSIP_MEM_NONE);
       vsip_cblock_f *cblock_ans = vsip_cblockbind_f(data_ans,
                           (vsip_scalar_f*)NULL,7,VSIP_MEM_NONE);
       vsip_cvview_f *u_a = vsip_cvbind_f(cblock,0,1,7);
       vsip_cvview_f *u_ans = vsip_cvbind_f(cblock_ans,0,1,7);

       vsip_cblockadmit_f(cblock,VSIP_TRUE);
       vsip_cblockadmit_f(cblock_ans,VSIP_TRUE);

       vsip_cvcopy_f_f(u_a,a);
       printf("call vsip_cvrsdiv_f(a,beta,c)\n");
       printf("beta = %f\n",beta);
       printf("a =\n");VU_cvprintm_f("8.6",a); 
       printf("test normal out of place\n");
       vsip_cvrsdiv_f(a,beta,c);
       printf("c =\n");VU_cvprintm_f("8.6",c); 
       printf("right answer =\n");VU_cvprintm_f("8.4",u_ans); 

       vsip_cvsub_f(u_ans,c,chk);
       vsip_cvmag_f(chk,chk_i);
       vsip_vclip_f(chk_i,.0002,.0002,0,1,chk_i);
       if(vsip_vsumval_f(chk_i) > .5)
            printf("error\n");
       else
            printf("correct\n");

       
       printf("test a,c inplace\n");
       vsip_cvrsdiv_f(a,beta,a);
       vsip_cvsub_f(u_ans,a,chk);
       vsip_cvmag_f(chk,chk_i);
       vsip_vclip_f(chk_i,.0002,.0002,0,1,chk_i);
       if(vsip_vsumval_f(chk_i) > .5)
            printf("error\n");
       else
            printf("correct\n");

       vsip_cvalldestroy_f(a);
       vsip_vdestroy_f(c_i); vsip_cvalldestroy_f(c);
       vsip_vdestroy_f(chk_i); vsip_cvalldestroy_f(chk);
       vsip_cvalldestroy_f(u_a);
       vsip_cvalldestroy_f(u_ans);

    }
    return;
}
