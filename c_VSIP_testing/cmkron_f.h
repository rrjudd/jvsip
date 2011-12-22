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
/* $Id: cmkron_f.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
static void cmkron_f(void){
   printf("********\nTEST cmkron_f\n");
   {
     vsip_cscalar_f alpha = vsip_cmplx_f(-3,2);
     vsip_scalar_f data_a_r[] = { 1, 1,
                                  2, 0.5}; /* (2,2) rowmajor */
     vsip_scalar_f data_a_i[] = { 1, -1,
                                 .5,  2};
     vsip_scalar_f data_b_r[] = { 3,  4,  1, 
                                  5,  3,  4, 
                                  2,  2,  3}; /* (3,3) rowmajor */
     vsip_scalar_f data_b_i[] = { 1,  1,   5, 
                                  1,  0.5, 1, 
                                  2, -2,  -1};
                              
     vsip_scalar_f ans_r[] = { -14.0, -19.0,    0,    -8.0,  -9.0, -26.00,
                               -24.0, -14.5,  -19.0, -10.0,  -5.5,  -9.00,
                                -8.0, -12.0,  -16.0, -12.0,   8.0,   2.00,
                               -23.5, -30.5,  -19.5, -11.5, -17.0,  19.50,
                               -37.5, -22.25, -30.5, -22.5, -14.0, -17.00,
                               -19.0,  -9.0,  -18.5,  -1.0, -21.0, -21.50};

     vsip_scalar_f ans_i[] = { -8.0,  -9.0, -26.0,  14.0,  19.0,    0,
                              -10.0,  -5.5,  -9.0,  24.0,  14.5,   19.0,
                              -12.0,   8.0,   2.0,   8.0,  12.0,   16.0,
                                0.5,   3.0, -32.5, -20.5, -25.5,  -32.5,
                                5.5,   4.0,   3.0, -30.5, -17.75, -25.5,
                               -9.0,  19.0,  14.5, -21.0,   1.0,   -9.5};
                             

     vsip_cblock_f  *block_a = vsip_cblockbind_f(data_a_r,data_a_i,4,VSIP_MEM_NONE);
     vsip_cblock_f  *block_b = vsip_cblockbind_f(data_b_r,data_b_i,9,VSIP_MEM_NONE);
     vsip_cblock_f  *block   = vsip_cblockcreate_f(100,VSIP_MEM_NONE);
     vsip_cblock_f  *ans_block = vsip_cblockbind_f(ans_r,ans_i,36,VSIP_MEM_NONE);

     vsip_cmview_f  *a   = vsip_cmbind_f(block_a,0,2,2,1,2);
     vsip_cmview_f  *t_b = vsip_cmbind_f(block_b,0,3,3,1,3);
     vsip_cmview_f  *b   = vsip_cmbind_f(block,95,-1,3,-9,3);
     vsip_cmview_f  *c = vsip_cmcreate_f(6,6,VSIP_COL,VSIP_MEM_NONE);

     vsip_cmview_f  *ansm = vsip_cmbind_f(ans_block,0,6,6,1,6);
     vsip_cmview_f  *chk = vsip_cmcreate_f(6,6,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_f   *chk_r = vsip_mrealview_f(chk);

     vsip_cblockadmit_f(block_a,VSIP_TRUE);
     vsip_cblockadmit_f(block_b,VSIP_TRUE);
     vsip_cblockadmit_f(ans_block,VSIP_TRUE);

     vsip_cmcopy_f_f(t_b,b);
     printf("vsip_cmkron_f(alpha,a,b,c)\n");
     vsip_cmkron_f(alpha,a,b,c);
     printf("alpha = %f %+fi\n",alpha.r,alpha.i);
     printf("matrix a\n");VU_cmprintm_f("8.6",a);
     printf("matrix b\n");VU_cmprintm_f("8.6",b);
     printf("matrix c\n");VU_cmprintm_f("8.6",c);
     printf("right answer\n");VU_cmprintm_f("8.4",ansm);

     vsip_cmsub_f(c,ansm,chk); vsip_cmmag_f(chk,chk_r); vsip_mclip_f(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_f(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cmalldestroy_f(a);
     vsip_cmalldestroy_f(t_b);
     vsip_cmalldestroy_f(b);
     vsip_cmalldestroy_f(c);
     vsip_mdestroy_f(chk_r);
     vsip_cmalldestroy_f(chk);
     vsip_cmalldestroy_f(ansm);
   }
   return;
}
