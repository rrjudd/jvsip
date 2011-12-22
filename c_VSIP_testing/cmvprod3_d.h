/* Created RJudd */
/* */
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
/* $Id: cmvprod3_d.h,v 2.1 2006/04/27 01:40:55 judd Exp $ */
static void cmvprod3_d(void){
   printf("********\nTEST cmvprod3_d\n");
   {
     vsip_scalar_d datav_r[] = {1.0, 2.0, 3.0};
     vsip_scalar_d datav_i[] = {5.0, 4.0, 3.0};
     vsip_scalar_d datam_r[] = { .1, .2, .3,
                                1.0, 1.1, 1.2,
                                2.1, 2.2, 2.3};
     vsip_scalar_d datam_i[] = { 1.1, 2.2, 3.3,
                                -1.0, 0.1, 0.2,
                                 1.1, 3.2, 4.3};
     vsip_scalar_d ans_data_r[] = { 0.0, 0.0, 0.0 };
     vsip_scalar_d ans_data_i[] = { 0.0, 0.0, 0.0 };
     vsip_cblock_d *blockv = vsip_cblockbind_d(datav_r,datav_i,3,VSIP_MEM_NONE);
     vsip_cblock_d *blockm = vsip_cblockbind_d(datam_r,datam_i,9,VSIP_MEM_NONE);
     vsip_cblock_d *block_ans = vsip_cblockbind_d(ans_data_r,ans_data_i,3,VSIP_MEM_NONE);
     vsip_cblock_d *block  = vsip_cblockcreate_d(70,VSIP_MEM_NONE);

     vsip_cvview_d *v = vsip_cvbind_d(blockv,0,1,3);
     vsip_cmview_d *m = vsip_cmbind_d(blockm,0,1,3,3,3);
     vsip_cvview_d *ans = vsip_cvbind_d(block_ans,0,1,3);

     vsip_cvview_d *b = vsip_cvbind_d(block,5,-1,3);
     vsip_cmview_d *a = vsip_cmbind_d(block,50,-2,3,-8,3);
     vsip_cvview_d *c = vsip_cvbind_d(block,49,-2,3);

     vsip_cvview_d *chk = vsip_cvcreate_d(3,VSIP_MEM_NONE);
     vsip_vview_d *chk_i = vsip_vimagview_d(chk);

     vsip_cblockadmit_d(blockv,VSIP_TRUE);
     vsip_cblockadmit_d(blockm,VSIP_TRUE);
     vsip_cblockadmit_d(block_ans,VSIP_TRUE);

     vsip_cvcopy_d_d(v,b);
     vsip_cmcopy_d_d(m,a);
     vsip_cmvprod_d(a,b,ans);
     vsip_cmvprod3_d(a,b,c);

     printf("vsip_cmvprod3_d(a,b,c)\n");    
     printf("m\n"); VU_cmprintm_d("6.4",m);
     printf("a\n"); VU_cmprintm_d("6.4",a);
     printf("v\n"); VU_cvprintm_d("6.4",v);
     printf("b\n"); VU_cvprintm_d("6.4",b);
     printf("c\n"); VU_cvprintm_d("6.4",c);
     printf("right answer\n"); VU_cvprintm_d("6.4",ans);
     vsip_cvsub_d(c,ans,chk); vsip_cvmag_d(chk,chk_i); vsip_vclip_d(chk_i,.0001,.0001,0,1,chk_i);
     if(vsip_vsumval_d(chk_i) > .5)
         printf("error\n");
     else
         printf("correct\n");
     vsip_cvalldestroy_d(v);
     vsip_cmalldestroy_d(m);
     vsip_cvalldestroy_d(ans);
     vsip_cvdestroy_d(b);
     vsip_cmdestroy_d(a);
     vsip_cvalldestroy_d(c);
     vsip_vdestroy_d(chk_i);
     vsip_cvalldestroy_d(chk);
   }
   return;
}
