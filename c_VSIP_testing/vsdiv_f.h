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
/* $Id: vsdiv_f.h,v 2.0 2003/02/22 15:23:30 judd Exp $ */
#include"VU_vprintm_f.include"
static void vsdiv_f(void){
   printf("\n*******\nTEST vsdiv_f\n\n");
   {
     vsip_scalar_f data[] = {.5, 1.0, 1.5, 2.0, 2.5, 3.0};
     vsip_scalar_f beta = 10.5;
     vsip_scalar_f ans[] = {0.0476, 0.0952, 0.1429, 0.1905, 0.2381, 0.2857};
     vsip_block_f  *blockn = vsip_blockbind_f(data,6,VSIP_MEM_NONE);
     vsip_block_f  *ans_block = vsip_blockbind_f(ans,6,VSIP_MEM_NONE);
     vsip_vview_f  *a = vsip_vbind_f(blockn,0,1,6);
     vsip_vview_f  *ansv = vsip_vbind_f(ans_block,0,1,6);
     vsip_vview_f  *b = vsip_vcreate_f(18,VSIP_MEM_NONE);
     vsip_vview_f  *c = vsip_vcreate_f(18,VSIP_MEM_NONE);
     vsip_vview_f  *d = vsip_vcreate_f(6,VSIP_MEM_NONE);
     vsip_vview_f  *chk = vsip_vcreate_f(6,VSIP_MEM_NONE);

     vsip_vputlength_f(b,6);
     vsip_vputstride_f(b,2);
     vsip_vputlength_f(c,6);
     vsip_vputstride_f(c,3);

     vsip_blockadmit_f(blockn,VSIP_TRUE);
     vsip_blockadmit_f(ans_block,VSIP_TRUE);

     vsip_vcopy_f_f(a,b); vsip_vcopy_f_f(a,c);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_vsdiv_f(a,beta,d);
     printf("vsdiv_f(a,beta,b)\n vector a\n");VU_vprintm_f("8.6",a);
     printf("beta = %f \n",beta);
     printf("vector b\n");VU_vprintm_f("8.6",d);
     printf("expected answer to 4 decimal digits\n");VU_vprintm_f("8.4",ansv);

     vsip_vsub_f(d,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5)
         printf(" vsdiv_f in error\n");
     else
         printf("vsdiv_f correct to 4 decimal digits\n");

     printf("\n");
     vsip_vsdiv_f(b,beta,b);
     vsip_vsub_f(b,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5)
         printf(" vsdiv_f in error for in place, stride 2\n");
     else
         printf("vsdiv_f correct to 4 decimal digits for in place, stride 2\n");

     printf("\n");
     /* check with a stride 1, b stride 3 */
     vsip_vfill_f(0,b);
     vsip_vsdiv_f(c,beta,b);
     vsip_vsub_f(b,ansv,chk); vsip_vmag_f(chk,chk); vsip_vclip_f(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_f(chk) > .5)
         printf(" vsdiv_f in error for strdie\n");
     else {
         printf("vsdiv_f correct to 4 decimal digits for\n");
         printf("input vsipl vector of stride 2, output vsipl vector of stride 3\n");
     }
     vsip_valldestroy_f(a);
     vsip_valldestroy_f(b);
     vsip_valldestroy_f(c);
     vsip_valldestroy_f(d);
     vsip_valldestroy_f(chk);
     vsip_valldestroy_f(ansv);
   }                         
   return;
}

