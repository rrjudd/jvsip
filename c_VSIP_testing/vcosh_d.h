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
/* $Id: vcosh_d.h,v 2.0 2003/02/22 15:23:28 judd Exp $ */
static void vcosh_d(void){
   printf("\n*******\nTEST vcosh_d\n\n");
   { vsip_scalar_d data[] = {0, M_PI/4.0, M_PI/2.0, M_PI, 1.5 * M_PI};
     vsip_scalar_d ans[] = {1, 1.3246, 2.5092, 11.5920, 55.6634};
     vsip_block_d  *block = vsip_blockbind_d(data,5,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,5,VSIP_MEM_NONE);
     vsip_vview_d  *a = vsip_vbind_d(block,0,1,5);
     vsip_vview_d  *ansv = vsip_vbind_d(ans_block,0,1,5);
     vsip_vview_d  *b = vsip_vcreate_d(15,VSIP_MEM_NONE);
     vsip_vview_d  *chk = vsip_vcreate_d(5,VSIP_MEM_NONE);
     vsip_vputlength_d(b,5);
     vsip_blockadmit_d(block,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_vcosh_d(a,b);
     printf("vcosh_d(a,b)\n vector a\n");VU_vprintm_d("8.6",a);
     printf("vector b\n");VU_vprintm_d("8.6",b);
     printf("expected answer to 4 decimal digits\n");VU_vprintm_d("8.4",ansv);

     vsip_vsub_d(b,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5)
         printf(" vcosh_d in error\n");
     else
         printf("vcosh_d correct to 4 decimal digits\n");

     printf("\n");
     vsip_vputstride_d(b,3);vsip_vcopy_d_d(a,b);
     vsip_vcosh_d(a,a);
     vsip_vsub_d(a,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5)
         printf(" vcosh_d in error for in place\n");
     else
         printf("vcosh_d correct to 4 decimal digits for in place\n");

     printf("\n");
     /* check with a stride 1, b stride 3 */
     vsip_vcosh_d(b,a);
     vsip_vsub_d(a,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5)
         printf(" vcosh_d in error for in place\n");
     else {
         printf("vcosh_d correct to 4 decimal digits for\n");
         printf("input vsipl vector of stride 3, output user vector of stride 1\n");
     }
     vsip_valldestroy_d(a);
     vsip_valldestroy_d(b);
     vsip_valldestroy_d(chk);
     vsip_valldestroy_d(ansv);
   }
   return;
}
