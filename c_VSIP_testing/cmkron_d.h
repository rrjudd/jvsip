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
/* $Id: cmkron_d.h,v 2.0 2003/02/22 15:23:21 judd Exp $ */
#include"VU_cmprintm_d.include"
static void cmkron_d(void){
   printf("********\nTEST cmkron_d\n");
   {
     vsip_cscalar_d alpha = vsip_cmplx_d(-3,2);
     vsip_scalar_d data_a_r[] = { 1, 1,
                                  2, 0.5}; /* (2,2) rowmajor */
     vsip_scalar_d data_a_i[] = { 1, -1,
                                 .5,  2};
     vsip_scalar_d data_b_r[] = { 3,  4,  1, 
                                  5,  3,  4, 
                                  2,  2,  3}; /* (3,3) rowmajor */
     vsip_scalar_d data_b_i[] = { 1,  1,   5, 
                                  1,  0.5, 1, 
                                  2, -2,  -1};
                              
     vsip_scalar_d ans_r[] = { -14.0, -19.0,    0,    -8.0,  -9.0, -26.00,
                               -24.0, -14.5,  -19.0, -10.0,  -5.5,  -9.00,
                                -8.0, -12.0,  -16.0, -12.0,   8.0,   2.00,
                               -23.5, -30.5,  -19.5, -11.5, -17.0,  19.50,
                               -37.5, -22.25, -30.5, -22.5, -14.0, -17.00,
                               -19.0,  -9.0,  -18.5,  -1.0, -21.0, -21.50};

     vsip_scalar_d ans_i[] = { -8.0,  -9.0, -26.0,  14.0,  19.0,    0,
                              -10.0,  -5.5,  -9.0,  24.0,  14.5,   19.0,
                              -12.0,   8.0,   2.0,   8.0,  12.0,   16.0,
                                0.5,   3.0, -32.5, -20.5, -25.5,  -32.5,
                                5.5,   4.0,   3.0, -30.5, -17.75, -25.5,
                               -9.0,  19.0,  14.5, -21.0,   1.0,   -9.5};
                             

     vsip_cblock_d  *block_a = vsip_cblockbind_d(data_a_r,data_a_i,4,VSIP_MEM_NONE);
     vsip_cblock_d  *block_b = vsip_cblockbind_d(data_b_r,data_b_i,9,VSIP_MEM_NONE);
     vsip_cblock_d  *block   = vsip_cblockcreate_d(100,VSIP_MEM_NONE);
     vsip_cblock_d  *ans_block = vsip_cblockbind_d(ans_r,ans_i,36,VSIP_MEM_NONE);

     vsip_cmview_d  *a   = vsip_cmbind_d(block_a,0,2,2,1,2);
     vsip_cmview_d  *t_b = vsip_cmbind_d(block_b,0,3,3,1,3);
     vsip_cmview_d  *b   = vsip_cmbind_d(block,95,-1,3,-9,3);
     vsip_cmview_d  *c = vsip_cmcreate_d(6,6,VSIP_COL,VSIP_MEM_NONE);

     vsip_cmview_d  *ansm = vsip_cmbind_d(ans_block,0,6,6,1,6);
     vsip_cmview_d  *chk = vsip_cmcreate_d(6,6,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d   *chk_r = vsip_mrealview_d(chk);

     vsip_cblockadmit_d(block_a,VSIP_TRUE);
     vsip_cblockadmit_d(block_b,VSIP_TRUE);
     vsip_cblockadmit_d(ans_block,VSIP_TRUE);

     vsip_cmcopy_d_d(t_b,b);
     printf("vsip_cmkron_d(alpha,a,b,c)\n");
     vsip_cmkron_d(alpha,a,b,c);
     printf("alpha = %f %+fi\n",alpha.r,alpha.i);
     printf("matrix a\n");VU_cmprintm_d("8.6",a);
     printf("matrix b\n");VU_cmprintm_d("8.6",b);
     printf("matrix c\n");VU_cmprintm_d("8.6",c);
     printf("right answer\n");VU_cmprintm_d("8.4",ansm);

     vsip_cmsub_d(c,ansm,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_d(chk_r) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_cmalldestroy_d(a);
     vsip_cmalldestroy_d(t_b);
     vsip_cmalldestroy_d(b);
     vsip_cmalldestroy_d(c);
     vsip_mdestroy_d(chk_r);
     vsip_cmalldestroy_d(chk);
     vsip_cmalldestroy_d(ansm);
   }
   return;
}
