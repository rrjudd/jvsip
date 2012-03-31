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
/* $Id: rcvdiv_f.h,v 2.0 2003/02/22 15:23:27 judd Exp $ */
#include"VU_vprintm_f.include"
#include"VU_cvprintm_f.include"
static void rcvdiv_f(void){
    printf("\n********\nTEST rcvdiv_f\n");
    {
       vsip_vview_f  *a = vsip_vcreate_f(7,VSIP_MEM_NONE);
       vsip_cvview_f *b = vsip_cvcreate_f(7,VSIP_MEM_NONE);
       vsip_cvview_f *c = vsip_cvcreate_f(7,VSIP_MEM_NONE);
       vsip_vview_f  *c_i = vsip_vimagview_f(c);
       vsip_cvview_f *chk = vsip_cvcreate_f(7,VSIP_MEM_NONE);
       vsip_vview_f  *chk_i = vsip_vimagview_f(chk);
       vsip_scalar_f data[] = {1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7};
       vsip_scalar_f data_r[] ={.1, .2, .3, .4, .5, .6, .7};
       vsip_scalar_f data_i[] ={7,6,5,4,3,2,1};
       vsip_scalar_f data_ans[] ={.0020,-.1428, .0061,-.1831, 
                       .0143,-.2391, .0322,-.3218, .0757,-.4541, 
                       .2064,-.6881, .7517,-1.0738};
       vsip_block_f  *block = vsip_blockbind_f(data,7,VSIP_MEM_NONE);
       vsip_cblock_f *cblock = vsip_cblockbind_f(data_r,data_i,7,VSIP_MEM_NONE);
       vsip_cblock_f *cblock_ans = vsip_cblockbind_f(data_ans,
                           (vsip_scalar_f*)NULL,7,VSIP_MEM_NONE);
       vsip_vview_f  *u_a = vsip_vbind_f(block,0,1,7);
       vsip_cvview_f *u_b = vsip_cvbind_f(cblock,0,1,7);
       vsip_cvview_f *u_ans = vsip_cvbind_f(cblock_ans,0,1,7);

       vsip_blockadmit_f(block,VSIP_TRUE);
       vsip_cblockadmit_f(cblock,VSIP_TRUE);
       vsip_cblockadmit_f(cblock_ans,VSIP_TRUE);

       vsip_vcopy_f_f(u_a,a);
       vsip_cvcopy_f_f(u_b,b);
       printf("call vsip_rcvdiv_f(a,b,c)\n");
       printf("a =\n");VU_vprintm_f("8.6",a); 
       printf("b =\n");VU_cvprintm_f("8.6",b); 
       printf("test normal out of place\n");
       vsip_rcvdiv_f(a,b,c);
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
       vsip_rcvdiv_f(a,b,b);
       vsip_cvsub_f(u_ans,b,chk);
       vsip_cvmag_f(chk,chk_i);
       vsip_vclip_f(chk_i,.0002,.0002,0,1,chk_i);
       if(vsip_vsumval_f(chk_i) > .5)
            printf("error\n");
       else
            printf("correct\n");

       printf("test in place a= imaginary(c)\n");
       vsip_vcopy_f_f(u_a,c_i);
       vsip_cvcopy_f_f(u_b,b);
       vsip_rcvdiv_f(c_i,b,c);
       vsip_cvsub_f(u_ans,c,chk);
       vsip_cvmag_f(chk,chk_i);
       vsip_vclip_f(chk_i,.0002,.0002,0,1,chk_i);
       if(vsip_vsumval_f(chk_i) > .5)
            printf("error\n");
       else
            printf("correct\n");

       vsip_valldestroy_f(a);
       vsip_cvalldestroy_f(b);
       vsip_vdestroy_f(c_i); vsip_cvalldestroy_f(c);
       vsip_vdestroy_f(chk_i); vsip_cvalldestroy_f(chk);
       vsip_valldestroy_f(u_a);
       vsip_cvalldestroy_f(u_b);
       vsip_cvalldestroy_f(u_ans);         
    }
    return;
}
