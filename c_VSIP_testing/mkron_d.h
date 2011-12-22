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
/* $Id: mkron_d.h,v 2.0 2003/02/22 15:23:25 judd Exp $ */
static void mkron_d(void){
   printf("********\nTEST mkron_d\n");
   {
     vsip_scalar_d alpha = 1.5;
     vsip_scalar_d data[] = { 1,   2,  
                              3,  4};
     vsip_scalar_d ans[] = { 1.5,  3,  3,  6, 
                             4.5,  6,  9, 12,
                             4.5,  9,  6, 12,
                            13.5, 18, 18, 24} ;

     vsip_block_d  *block_data = vsip_blockbind_d(data,4,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,16,VSIP_MEM_NONE);

     vsip_mview_d  *a = vsip_mbind_d(block_data,0,2,2,1,2);
     vsip_mview_d  *b = vsip_mcreate_d(2,2,VSIP_ROW,VSIP_MEM_NONE);
     vsip_mview_d  *c = vsip_mcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);

     vsip_mview_d  *ansm = vsip_mbind_d(ans_block,0,4,4,1,4);
     vsip_mview_d  *chk = vsip_mcreate_d(4,4,VSIP_ROW,VSIP_MEM_NONE);

     vsip_blockadmit_d(block_data,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);

     vsip_mcopy_d_d(a,b);
     printf("vsip_mkron_d(alpha,a,b,c)\n");
     vsip_mkron_d(alpha,a,b,c);
     printf("alpha = %f \n",alpha);
     printf("matrix a\n");VU_mprintm_d("8.6",a);
     printf("matrix b\n");VU_mprintm_d("8.6",b);
     printf("matrix c\n");VU_mprintm_d("8.6",c);
     printf("right answer\n");VU_mprintm_d("8.4",ansm);

     vsip_msub_d(c,ansm,chk); vsip_mmag_d(chk,chk); vsip_mclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_msumval_d(chk) > .5) 
         printf("error\n");
     else 
         printf("correct\n");

     vsip_malldestroy_d(a);
     vsip_malldestroy_d(b);
     vsip_malldestroy_d(c);
     vsip_malldestroy_d(chk);
     vsip_malldestroy_d(ansm);
   }
   return;
}
