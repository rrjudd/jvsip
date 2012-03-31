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
/* $Id: mvprod3_d.h,v 2.1 2006/04/09 19:28:23 judd Exp $ */
#include"VU_mprintm_d.include"
#include"VU_vprintm_d.include"
static void mvprod3_d(void){
   printf("********\nTEST mvprod_d\n");
   {
     vsip_scalar_d datav[] = {1,2,3};
     vsip_scalar_d datam[] = { 1,1,1,2,2,2,3,3,3};
     vsip_scalar_d ans_data[] = {6,12,18}; 
     vsip_block_d *blockv = vsip_blockbind_d(datav,3,VSIP_MEM_NONE);
     vsip_block_d *blockm = vsip_blockbind_d(datam,9,VSIP_MEM_NONE);
     vsip_block_d *block_ans = vsip_blockbind_d(ans_data,3,VSIP_MEM_NONE);
     vsip_block_d *block  = vsip_blockcreate_d(70,VSIP_MEM_NONE);
     vsip_vview_d *v = vsip_vbind_d(blockv,0,1,3);
     vsip_mview_d *m = vsip_mbind_d(blockm,0,3,3,1,3);
     vsip_vview_d *ans = vsip_vbind_d(block_ans,0,1,3);
     vsip_vview_d *b = vsip_vbind_d(block,5,-1,3);
     vsip_mview_d *a = vsip_mbind_d(block,50,-2,3,-8,3);
     vsip_vview_d *c = vsip_vbind_d(block,49,-2,3);
     vsip_vview_d *chk = vsip_vcreate_d(3,VSIP_MEM_NONE);
     vsip_blockadmit_d(blockv,VSIP_TRUE);
     vsip_blockadmit_d(blockm,VSIP_TRUE);
     vsip_blockadmit_d(block_ans,VSIP_TRUE);
     vsip_vcopy_d_d(v,b);
     vsip_mcopy_d_d(m,a);
     vsip_mvprod3_d(a,b,c);
     printf("vsip_mvprod3_d(a,b,c)\n");    
     printf("a\n"); VU_mprintm_d("6.4",a);
     printf("b\n"); VU_vprintm_d("6.4",b);
     printf("c\n"); VU_vprintm_d("6.4",c);
     printf("right answer\n"); VU_vprintm_d("6.4",ans);
     vsip_vsub_d(c,ans,chk); vsip_vmag_d(chk,chk); vsip_vclip_d(chk,.0001,.0001,0,1,chk);
     if(vsip_vsumval_d(chk) > .1)
         printf("error\n");
     else
         printf("correct\n");
     vsip_valldestroy_d(v);
     vsip_malldestroy_d(m);
     vsip_valldestroy_d(ans);
     vsip_vdestroy_d(b);
     vsip_mdestroy_d(a);
     vsip_valldestroy_d(c);
     vsip_valldestroy_d(chk);
   }
   return;
}
