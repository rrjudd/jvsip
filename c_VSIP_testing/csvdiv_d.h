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
/* $Id: csvdiv_d.h,v 2.0 2003/02/22 15:23:22 judd Exp $ */
#include"VU_cvprintm_d.include"
static void csvdiv_d(void){
    printf("\n********\nTEST csvdiv_d\n");
    {
       vsip_cscalar_d  alpha = vsip_cmplx_d(1.5,-1.5);
       vsip_cvview_d *b = vsip_cvcreate_d(7,VSIP_MEM_NONE);
       vsip_cvview_d *c = vsip_cvcreate_d(7,VSIP_MEM_NONE);
       vsip_vview_d  *c_i = vsip_vimagview_d(c);
       vsip_cvview_d *chk = vsip_cvcreate_d(7,VSIP_MEM_NONE);
       vsip_vview_d  *chk_i = vsip_vimagview_d(chk);
       vsip_scalar_d data_r[] ={.1, .2, .3, .4, .5, .6, .7};
       vsip_scalar_d data_i[] ={7,6,5,4,3,2,1};
       vsip_scalar_d data_ans[] ={-.2112,-.2173, -.2414,-.2580, 
                       -.2810,-.3169, -.3342,-.4084, -.4054,-.5676, 
                       -.4817,-0.8945, -0.3020,-1.7114};
       vsip_cblock_d *cblock = vsip_cblockbind_d(data_r,data_i,7,VSIP_MEM_NONE);
       vsip_cblock_d *cblock_ans = vsip_cblockbind_d(data_ans,
                           (vsip_scalar_d*)NULL,7,VSIP_MEM_NONE);
       vsip_cvview_d *u_b = vsip_cvbind_d(cblock,0,1,7);
       vsip_cvview_d *u_ans = vsip_cvbind_d(cblock_ans,0,1,7);

       vsip_cblockadmit_d(cblock,VSIP_TRUE);
       vsip_cblockadmit_d(cblock_ans,VSIP_TRUE);

       vsip_cvcopy_d_d(u_b,b);
       printf("call vsip_csvdiv_d(alpha,b,c)\n");
       printf("alpha = %f %+fi\n",vsip_real_d(alpha),vsip_imag_d(alpha));
       printf("b =\n");VU_cvprintm_d("8.6",b); 
       printf("test normal out of place\n");
       vsip_csvdiv_d(alpha,b,c);
       printf("c =\n");VU_cvprintm_d("8.6",c); 
       printf("right answer =\n");VU_cvprintm_d("8.4",u_ans); 

       vsip_cvsub_d(u_ans,c,chk);
       vsip_cvmag_d(chk,chk_i);
       vsip_vclip_d(chk_i,.0002,.0002,0,1,chk_i);
       if(vsip_vsumval_d(chk_i) > .5)
            printf("error\n");
       else
            printf("correct\n");

       
       printf("test b,c inplace\n");
       vsip_csvdiv_d(alpha,b,b);
       vsip_cvsub_d(u_ans,b,chk);
       vsip_cvmag_d(chk,chk_i);
       vsip_vclip_d(chk_i,.0002,.0002,0,1,chk_i);
       if(vsip_vsumval_d(chk_i) > .5)
            printf("error\n");
       else
            printf("correct\n");

       vsip_cvalldestroy_d(b);
       vsip_vdestroy_d(c_i); vsip_cvalldestroy_d(c);
       vsip_vdestroy_d(chk_i); vsip_cvalldestroy_d(chk);
       vsip_cvalldestroy_d(u_b);
       vsip_cvalldestroy_d(u_ans);

    }
    return;
}
