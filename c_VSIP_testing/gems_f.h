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
/* $Id: gems_f.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
static void gems_f(void){
   printf("********\nTEST gems_f\n");
   {
     vsip_scalar_f alpha = 1.5;
     vsip_scalar_f beta  = 2.0;
     vsip_scalar_f data_a[] = {1, 2.0, -3.0,  4,  5.0,
                                5,  .1,  .2, .3,   .4,
                                -4, 3.0, 2.0,  0, -1.0};
     vsip_scalar_f ans_n_data[] = {
    3.5,    5.0,   -2.5,    8.0,    9.5,
    9.5,    2.15,   2.3,    2.45,   2.6,
   -4.0,    6.50,   5.0,    2.0,    0.5 };
     vsip_scalar_f ans_t_data[] = { 
    5.5,   11.5,   -2.0,
    7.0,    4.15,   8.5,
   -0.5,    4.3,    7.0,
   10.0,    4.45,   4.0,
   11.5,    4.6,    2.5 };                                     
     vsip_block_f *block_a = vsip_blockbind_f(data_a,15,VSIP_MEM_NONE);
     vsip_block_f *block_ans_n = vsip_blockbind_f(ans_n_data,15,VSIP_MEM_NONE);
     vsip_block_f *block_ans_t = vsip_blockbind_f(ans_t_data,15,VSIP_MEM_NONE);
     vsip_block_f *block  = vsip_blockcreate_f(400,VSIP_MEM_NONE);
     vsip_mview_f *au = vsip_mbind_f(block_a,0,5,3,1,5);
     vsip_mview_f *ans_n = vsip_mbind_f(block_ans_n,0,5,3,1,5);
     vsip_mview_f *ans_t = vsip_mbind_f(block_ans_t,0,3,5,1,3);
     vsip_mview_f *a = vsip_mbind_f(block,15,-1,3,-3,5);
     vsip_mview_f *cn = vsip_mbind_f(block,200,-10,3,-2,5);
     vsip_mview_f *ct = vsip_mbind_f(block,300,2,5,15,3);
     vsip_mview_f *chk_n = vsip_mcreate_f(3,5,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_f *chk_t = vsip_mcreate_f(5,3,VSIP_ROW,VSIP_MEM_NONE);
     vsip_blockadmit_f(block_a,VSIP_TRUE);
     vsip_blockadmit_f(block_ans_n,VSIP_TRUE);
     vsip_blockadmit_f(block_ans_t,VSIP_TRUE);
     vsip_mcopy_f_f(au,a);
     vsip_mfill_f(1.0,cn);
     vsip_mfill_f(2.0,ct);

     /* test n */
     printf("\nvsip_gems_f(alpha,a,VSIP_MAT_NTRANS,beta,c)\n");
     printf("alpha = %f\n",alpha);
     printf("matrix a = ");VU_mprintm_f("6.4",a);
     printf("beta = %f\n",beta);
     printf("on input matrix c = ");VU_mprintm_f("6.4",cn);
     vsip_gems_f(alpha,a,VSIP_MAT_NTRANS,beta,cn);
     printf("on output matrix c = ");VU_mprintm_f("6.4",cn);
     printf("right answer = ");VU_mprintm_f("6.4",ans_n);
     vsip_msub_f(cn,ans_n,chk_n); vsip_mmag_f(chk_n,chk_n); vsip_mclip_f(chk_n,.0001,.0001,0,1,chk_n);
     if(vsip_msumval_f(chk_n) > .5)
         printf("error\n");
     else
         printf("correct\n");

     /* test t */
     printf("\nvsip_gems_f(alpha,a,VSIP_MAT_TRANS,beta,c)\n");
     printf("alpha = %f\n",alpha);
     printf("matrix a = ");VU_mprintm_f("6.4",a);
     printf("beta = %f\n",beta);
     printf("on input matrix c = ");VU_mprintm_f("6.4",ct);
     vsip_gems_f(alpha,a,VSIP_MAT_TRANS,beta,ct);
     printf("on output matrix c = ");VU_mprintm_f("6.4",ct);
     printf("right answer = ");VU_mprintm_f("6.4",ans_t);
     vsip_msub_f(ct,ans_t,chk_t); vsip_mmag_f(chk_t,chk_t); vsip_mclip_f(chk_t,.0001,.0001,0,1,chk_t);
     if(vsip_msumval_f(chk_t) > .5)
         printf("error\n");
     else
         printf("correct\n");

     vsip_malldestroy_f(au);

     vsip_mdestroy_f(a); vsip_mdestroy_f(cn);
     vsip_malldestroy_f(ct);

     vsip_malldestroy_f(ans_t); vsip_malldestroy_f(ans_n);

     vsip_malldestroy_f(chk_t); vsip_malldestroy_f(chk_n);
   }
   return;
}
