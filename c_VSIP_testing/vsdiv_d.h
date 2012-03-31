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
/* $Id: vsdiv_d.h,v 2.0 2003/02/22 15:23:30 judd Exp $ */
#include"VU_vprintm_d.include"
static void vsdiv_d(void){
   printf("\n*******\nTEST vsdiv_d\n\n");
   {
     vsip_scalar_d data[] = {.5, 1.0, 1.5, 2.0, 2.5, 3.0};
     vsip_scalar_d beta = 10.5;
     vsip_scalar_d ans[] = {0.0476, 0.0952, 0.1429, 0.1905, 0.2381, 0.2857};
     vsip_block_d  *blockn = vsip_blockbind_d(data,6,VSIP_MEM_NONE);
     vsip_block_d  *ans_block = vsip_blockbind_d(ans,6,VSIP_MEM_NONE);
     vsip_vview_d  *a = vsip_vbind_d(blockn,0,1,6);
     vsip_vview_d  *ansv = vsip_vbind_d(ans_block,0,1,6);
     vsip_vview_d  *b = vsip_vcreate_d(18,VSIP_MEM_NONE);
     vsip_vview_d  *c = vsip_vcreate_d(18,VSIP_MEM_NONE);
     vsip_vview_d  *d = vsip_vcreate_d(6,VSIP_MEM_NONE);
     vsip_vview_d  *chk = vsip_vcreate_d(6,VSIP_MEM_NONE);

     vsip_vputlength_d(b,6);
     vsip_vputstride_d(b,2);
     vsip_vputlength_d(c,6);
     vsip_vputstride_d(c,3);

     vsip_blockadmit_d(blockn,VSIP_TRUE);
     vsip_blockadmit_d(ans_block,VSIP_TRUE);

     vsip_vcopy_d_d(a,b); vsip_vcopy_d_d(a,c);
     printf("test out of place, compact, user \"a\", vsipl \"b\"\n");
     vsip_vsdiv_d(a,beta,d);
     printf("vsdiv_d(a,beta,b)\n vector a\n");VU_vprintm_d("8.6",a);
     printf("beta = %f \n",beta);
     printf("vector b\n");VU_vprintm_d("8.6",d);
     printf("expected answer to 4 decimal digits\n");VU_vprintm_d("8.4",ansv);

     vsip_vsub_d(d,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5)
         printf(" vsdiv_d in error\n");
     else
         printf("vsdiv_d correct to 4 decimal digits\n");

     printf("\n");
     vsip_vsdiv_d(b,beta,b);
     vsip_vsub_d(b,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5)
         printf(" vsdiv_d in error for in place, stride 2\n");
     else
         printf("vsdiv_d correct to 4 decimal digits for in place, stride 2\n");

     printf("\n");
     /* check with a stride 1, b stride 3 */
     vsip_vfill_d(0,b);
     vsip_vsdiv_d(c,beta,b);
     vsip_vsub_d(b,ansv,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .5)
         printf(" vsdiv_d in error for strdie\n");
     else {
         printf("vsdiv_d correct to 4 decimal digits for\n");
         printf("input vsipl vector of stride 2, output vsipl vector of stride 3\n");
     }
     vsip_valldestroy_d(a);
     vsip_valldestroy_d(b);
     vsip_valldestroy_d(c);
     vsip_valldestroy_d(d);
     vsip_valldestroy_d(chk);
     vsip_valldestroy_d(ansv);
   }                         
   return;
}

