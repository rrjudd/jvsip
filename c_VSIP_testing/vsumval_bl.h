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
/* $Id: vsumval_bl.h,v 2.1 2009/09/05 18:01:45 judd Exp $ */
#include"VU_vprintm_d.include"
static void vsumval_bl(void){
   printf("********\nTEST vsumval_bl\n");
   {
       vsip_scalar_bl data[] = {0, 1, 0, 1, 0, 1, 1, 1, 1, 0};
       vsip_vview_bl *a = vsip_vbind_bl(
                 vsip_blockbind_bl(data,10,VSIP_MEM_NONE),0,1,10);
       vsip_block_bl  *block = vsip_blockcreate_bl(1024,VSIP_MEM_NONE);
       vsip_vview_bl *b = vsip_vbind_bl(block,250,-5,10);
       vsip_vview_d *c = vsip_vcreate_d(10,VSIP_MEM_NONE);
       vsip_index  val = 0;
       vsip_index  ans = 6;
       vsip_blockadmit_bl(vsip_vgetblock_bl(a),VSIP_TRUE);
       vsip_vcopy_bl_bl(a,b);
       vsip_vcopy_bl_d(a,c);
       printf("val = vsip_vsumval_bl(a)\n");
       printf("vector a\n"); VU_vprintm_d("1.0",c);
       val = vsip_vsumval_bl(b);
       printf("val = %u\n",(unsigned)val);
       printf("ans = %u\n",(unsigned)ans);
       if(((int)val - (int)ans) == 0)
          printf("correct\n");
       else
          printf("error\n");
       vsip_valldestroy_bl(a); 
       vsip_valldestroy_bl(b); 
       vsip_valldestroy_d(c);
    }
}
