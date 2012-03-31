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
/* $Id: csvdiv_f.h,v 2.0 2003/02/22 15:23:22 judd Exp $ */
#include"VU_cvprintm_f.include"
static void csvdiv_f(void){
    printf("\n********\nTEST csvdiv_f\n");
    {
       vsip_cscalar_f  alpha = vsip_cmplx_f(1.5,-1.5);
       vsip_cvview_f *b = vsip_cvcreate_f(7,VSIP_MEM_NONE);
       vsip_cvview_f *c = vsip_cvcreate_f(7,VSIP_MEM_NONE);
       vsip_vview_f  *c_i = vsip_vimagview_f(c);
       vsip_cvview_f *chk = vsip_cvcreate_f(7,VSIP_MEM_NONE);
       vsip_vview_f  *chk_i = vsip_vimagview_f(chk);
       vsip_scalar_f data_r[] ={.1, .2, .3, .4, .5, .6, .7};
       vsip_scalar_f data_i[] ={7,6,5,4,3,2,1};
       vsip_scalar_f data_ans[] ={-.2112,-.2173, -.2414,-.2580, 
                       -.2810,-.3169, -.3342,-.4084, -.4054,-.5676, 
                       -.4817,-0.8945, -0.3020,-1.7114};
       vsip_cblock_f *cblock = vsip_cblockbind_f(data_r,data_i,7,VSIP_MEM_NONE);
       vsip_cblock_f *cblock_ans = vsip_cblockbind_f(data_ans,
                           (vsip_scalar_f*)NULL,7,VSIP_MEM_NONE);
       vsip_cvview_f *u_b = vsip_cvbind_f(cblock,0,1,7);
       vsip_cvview_f *u_ans = vsip_cvbind_f(cblock_ans,0,1,7);

       vsip_cblockadmit_f(cblock,VSIP_TRUE);
       vsip_cblockadmit_f(cblock_ans,VSIP_TRUE);

       vsip_cvcopy_f_f(u_b,b);
       printf("call vsip_csvdiv_f(alpha,b,c)\n");
       printf("alpha = %f %+fi\n",vsip_real_f(alpha),vsip_imag_f(alpha));
       printf("b =\n");VU_cvprintm_f("8.6",b); 
       printf("test normal out of place\n");
       vsip_csvdiv_f(alpha,b,c);
       printf("c =\n");VU_cvprintm_f("8.6",c); 
       printf("right answer =\n");VU_cvprintm_f("8.4",u_ans); 

       vsip_cvsub_f(u_ans,c,chk);
       vsip_cvmag_f(chk,chk_i);
       vsip_vclip_f(chk_i,.0002,.0002,0,1,chk_i);
       if(vsip_vsumval_f(chk_i) > .5)
            printf("error\n");
       else
            printf("correct\n");

       
       printf("test b,c inplace\n");
       vsip_csvdiv_f(alpha,b,b);
       vsip_cvsub_f(u_ans,b,chk);
       vsip_cvmag_f(chk,chk_i);
       vsip_vclip_f(chk_i,.0002,.0002,0,1,chk_i);
       if(vsip_vsumval_f(chk_i) > .5)
            printf("error\n");
       else
            printf("correct\n");

       vsip_cvalldestroy_f(b);
       vsip_vdestroy_f(c_i); vsip_cvalldestroy_f(c);
       vsip_vdestroy_f(chk_i); vsip_cvalldestroy_f(chk);
       vsip_cvalldestroy_f(u_b);
       vsip_cvalldestroy_f(u_ans);

    }
    return;
}
