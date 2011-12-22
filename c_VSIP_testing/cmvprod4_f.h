/* Created RJudd */
/*  */
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
/* $Id: cmvprod4_f.h,v 2.1 2006/04/27 01:40:55 judd Exp $ */
static void cmvprod4_f(void){
   printf("********\nTEST cmvprod4_f\n");
   {
     vsip_scalar_f datav_r[] = {1.0, 2.0, 3.0, 4.0};
     vsip_scalar_f datav_i[] = {5.0, 4.0, 3.0, 2.0};
     vsip_scalar_f datam_r[] = { .1, .2, .3, .4,
                                1.0, 1.1, 1.2, 1.3,
                                2.1, 2.2, 2.3, 2.4,
                                3.2, 3.3, 3.4, 3.5};
     vsip_scalar_f datam_i[] = { 1.1, 2.2, 3.3, 4.4,
                                -1.0, 0.1, 0.2, 0.3,
                                 1.1, 3.2, 4.3, 45.4,
                                 2.1, 3.0, -5.1, .3};
     vsip_scalar_f ans_data_r[] = { 0.0, 0.0, 0.0, 0.0};
     vsip_scalar_f ans_data_i[] = { 0.0, 0.0, 0.0, 0.0 };
     vsip_cblock_f *blockv = vsip_cblockbind_f(datav_r,datav_i,4,VSIP_MEM_NONE);
     vsip_cblock_f *blockm = vsip_cblockbind_f(datam_r,datam_i,16,VSIP_MEM_NONE);
     vsip_cblock_f *block_ans = vsip_cblockbind_f(ans_data_r,ans_data_i,4,VSIP_MEM_NONE);
     vsip_cblock_f *block  = vsip_cblockcreate_f(70,VSIP_MEM_NONE);

     vsip_cvview_f *v = vsip_cvbind_f(blockv,0,1,4);
     vsip_cmview_f *m = vsip_cmbind_f(blockm,0,1,4,4,4);
     vsip_cvview_f *ans = vsip_cvbind_f(block_ans,0,1,4);

     vsip_cvview_f *b = vsip_cvbind_f(block,5,-1,4);
     vsip_cmview_f *a = vsip_cmbind_f(block,50,-2,4,-8,4);
     vsip_cvview_f *c = vsip_cvbind_f(block,49,-2,4);

     vsip_cvview_f *chk = vsip_cvcreate_f(4,VSIP_MEM_NONE);
     vsip_vview_f *chk_i = vsip_vimagview_f(chk);

     vsip_cblockadmit_f(blockv,VSIP_TRUE);
     vsip_cblockadmit_f(blockm,VSIP_TRUE);
     vsip_cblockadmit_f(block_ans,VSIP_TRUE);

     vsip_cvcopy_f_f(v,b);
     vsip_cmcopy_f_f(m,a);
     vsip_cmvprod_f(a,b,ans);
     vsip_cmvprod4_f(a,b,c);

     printf("vsip_cmvprod4_f(a,b,c)\n");    
     printf("m\n"); VU_cmprintm_f("6.4",m);
     printf("a\n"); VU_cmprintm_f("6.4",a);
     printf("v\n"); VU_cvprintm_f("6.4",v);
     printf("b\n"); VU_cvprintm_f("6.4",b);
     printf("c\n"); VU_cvprintm_f("6.4",c);
     printf("right answer\n"); VU_cvprintm_f("6.4",ans);
     vsip_cvsub_f(c,ans,chk); vsip_cvmag_f(chk,chk_i); vsip_vclip_f(chk_i,.0001,.0001,0,1,chk_i);
     if(vsip_vsumval_f(chk_i) > .5)
         printf("error\n");
     else
         printf("correct\n");
     vsip_cvalldestroy_f(v);
     vsip_cmalldestroy_f(m);
     vsip_cvalldestroy_f(ans);
     vsip_cvdestroy_f(b);
     vsip_cmdestroy_f(a);
     vsip_cvalldestroy_f(c);
     vsip_vdestroy_f(chk_i);
     vsip_cvalldestroy_f(chk);
   }
   return;
}
