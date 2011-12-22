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
/* $Id: cmvprod_d.h,v 2.0 2003/02/22 15:23:22 judd Exp $ */
static void cmvprod_d(void){
   printf("********\nTEST cmvprod_d\n");
   {
     vsip_scalar_d datav_r[] = {1,2,3,4,5};
     vsip_scalar_d datav_i[] = {5,4,3,2,1};
     vsip_scalar_d datam_r[] = { .1, .2, .3, .4,    
                              1.0, 1.1, 1.2, 1.3,
                              2.1, 2.2, 2.3, 2.4,
                              -1.1, -1.2, -1.3, -1.4,
                              2.1, 2.2, 2.3, 3.4};
     vsip_scalar_d datam_i[] = { 1.1, 2.2, 3.3, 4.4,    
                              -1.0, 0.1, 0.2, 0.3,
                              1.1, 3.2, 4.3, 5.4,
                              -1.1, -1.2, +1.2, -1.3,
                              2.1, 1.2, 2.7, 0.9};
     vsip_scalar_d ans_data_r[] = { 9.8,-4.6,-19.4,-16.1};
     vsip_scalar_d ans_data_i[] = { 19.2,25.0,47.8,35.5};
     vsip_cblock_d *blockv = vsip_cblockbind_d(datav_r,datav_i,5,VSIP_MEM_NONE);
     vsip_cblock_d *blockm = vsip_cblockbind_d(datam_r,datam_i,20,VSIP_MEM_NONE);
     vsip_cblock_d *block_ans = vsip_cblockbind_d(ans_data_r,ans_data_i,4,VSIP_MEM_NONE);
     vsip_cblock_d *block  = vsip_cblockcreate_d(70,VSIP_MEM_NONE);
     vsip_cvview_d *v = vsip_cvbind_d(blockv,0,1,5);
     vsip_cmview_d *m = vsip_cmbind_d(blockm,0,1,4,4,5);
     vsip_cvview_d *ans = vsip_cvbind_d(block_ans,0,1,4);
     vsip_cvview_d *b = vsip_cvbind_d(block,5,-1,5);
     vsip_cmview_d *a = vsip_cmbind_d(block,50,-2,4,-8,5);
     vsip_cvview_d *c = vsip_cvbind_d(block,49,-2,4);
     vsip_cvview_d *chk = vsip_cvcreate_d(4,VSIP_MEM_NONE);
     vsip_vview_d *chk_i = vsip_vimagview_d(chk);
     vsip_cblockadmit_d(blockv,VSIP_TRUE);
     vsip_cblockadmit_d(blockm,VSIP_TRUE);
     vsip_cblockadmit_d(block_ans,VSIP_TRUE);
     vsip_cvcopy_d_d(v,b);
     vsip_cmcopy_d_d(m,a);
     vsip_cmvprod_d(a,b,c);
     printf("vsip_cmvprod_d(a,b,c)\n");    
     printf("a\n"); VU_cmprintm_d("6.4",a);
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
