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
/* $Id: meuler_d.h,v 2.0 2003/02/22 15:23:24 judd Exp $ */
static void meuler_d(void){
   printf("\n*******\nTEST meuler_d\n\n");
   { vsip_scalar_d data[] = {M_PI/8.0, M_PI/4.0, M_PI/3.0, M_PI/1.5, 1.25 * M_PI, 1.75 * M_PI};
     vsip_scalar_d ans_r[] = {0.9239, 0.7071, 0.5000, -0.5000, -0.7071, 0.7071};
     vsip_scalar_d ans_i[] = {0.3827, 0.7071, 0.8660, 0.8660, -0.7071, -0.7071};
     vsip_block_d  *block = vsip_blockbind_d(data,6,VSIP_MEM_NONE);
     vsip_cblock_d  *ans_block = vsip_cblockbind_d(ans_r,ans_i,6,VSIP_MEM_NONE);
     vsip_mview_d  *a = vsip_mbind_d(block,0,2,3,1,2);
     vsip_cmview_d  *ansm = vsip_cmbind_d(ans_block,0,2,3,1,2);
     vsip_cmview_d  *b = vsip_cmcreate_d(3,2,VSIP_ROW,VSIP_MEM_NONE);
     vsip_cmview_d  *chk = vsip_cmcreate_d(3,2,VSIP_COL,VSIP_MEM_NONE);
     vsip_mview_d  *chk_r = vsip_mrealview_d(chk);
     vsip_blockadmit_d(block,VSIP_TRUE);
     vsip_cblockadmit_d(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_meuler_d(a,b);
     printf("meuler_d(a,b)\n matrix a\n");VU_mprintm_d("8.6",a);
     printf("matrix b\n");VU_cmprintm_d("8.6",b);
     printf("answer\n");VU_cmprintm_d("8.4",ansm);

     vsip_cmsub_d(b,ansm,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_d(chk_r) > .5)
         printf("error\n");
     else
         printf("correct\n");

     printf("check meuler_d in place, <a> realview of <b>.\n");
     { vsip_mview_d *d = vsip_mrealview_d(b);
       vsip_mcopy_d_d(a,d);
       vsip_meuler_d(d,b);
       vsip_cmsub_d(b,ansm,chk); vsip_cmmag_d(chk,chk_r); vsip_mclip_d(chk_r,.0001,.0001,0,1,chk_r);
     if(vsip_msumval_d(chk_r) > .5)
         printf("error\n");
     else
         printf("correct\n");
       vsip_mdestroy_d(d);
     }

     vsip_malldestroy_d(a);
     vsip_cmalldestroy_d(b);
     vsip_mdestroy_d(chk_r);
     vsip_cmalldestroy_d(chk);
     vsip_cmalldestroy_d(ansm);
   }
   return;
}
