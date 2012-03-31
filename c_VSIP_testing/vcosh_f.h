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
/* $Id: vcosh_f.h,v 2.0 2003/02/22 15:23:28 judd Exp $ */
#include"VU_vprintm_f.include"
static void vcosh_f(void){
   printf("\n*******\nTEST vcosh_f\n\n");
   { vsip_scalar_f data[] = {0, M_PI/4.0, M_PI/2.0, M_PI, 1.5 * M_PI};
     vsip_scalar_f ans[] = {1, 1.3246, 2.5092, 11.5920, 55.6634};
     vsip_block_f  *block = vsip_blockbind_f(data,5,VSIP_MEM_NONE);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,5,VSIP_MEM_NONE);
     vsip_vview_f  *a = vsip_vbind_f(block,0,1,5);
     vsip_vview_f  *ansv = vsip_vbind_f(ans_block,0,1,5);
     vsip_vview_f  *b = vsip_vcreate_f(15,VSIP_MEM_NONE);
     vsip_vview_f  *chk = vsip_vcreate_f(5,VSIP_MEM_NONE);
     vsip_vputlength_f(b,5);
     vsip_blockadmit_f(block,VSIP_TRUE);
     vsip_blockadmit_f(ans_block,VSIP_TRUE);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_vcosh_f(a,b);
     printf("vcosh_f(a,b)\n vector a\n");VU_vprintm_f("8.6",a);
     printf("vector b\n");VU_vprintm_f("8.6",b);
     printf("expected answer to 4 decimal digits\n");VU_vprintm_f("8.4",ansv);

     vsip_vsub_f(b,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5)
         printf(" vcosh_f in error\n");
     else
         printf("vcosh_f correct to 4 decimal digits\n");

     printf("\n");
     vsip_vputstride_f(b,3);vsip_vcopy_f_f(a,b);
     vsip_vcosh_f(a,a);
     vsip_vsub_f(a,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5)
         printf(" vcosh_f in error for in place\n");
     else
         printf("vcosh_f correct to 4 decimal digits for in place\n");

     printf("\n");
     /* check with a stride 1, b stride 3 */
     vsip_vcosh_f(b,a);
     vsip_vsub_f(a,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5)
         printf(" vcosh_f in error for in place\n");
     else {
         printf("vcosh_f correct to 4 decimal digits for\n");
         printf("input vsipl vector of stride 3, output user vector of stride 1\n");
     }
     vsip_valldestroy_f(a);
     vsip_valldestroy_f(b);
     vsip_valldestroy_f(chk);
     vsip_valldestroy_f(ansv);
   }
   return;
}
