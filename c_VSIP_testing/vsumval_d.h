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
/* $Id: vsumval_d.h,v 2.0 2003/02/22 15:23:30 judd Exp $ */
static void vsumval_d(void){
   printf("********\nTEST vsumval_d\n");
   {
       vsip_scalar_d data[] = {1.0, 1.1, 1.2, 1.3, 1.4, 1.4, 1.3, 1.2, 1.1, 1.0};
       vsip_scalar_d val = 0.0;
       vsip_scalar_d ans = 12.0;
       vsip_vview_d *a = vsip_vbind_d(
                 vsip_blockbind_d(data,10,VSIP_MEM_NONE),0,1,10);
       vsip_block_d  *block = vsip_blockcreate_d(1024,VSIP_MEM_NONE);
       vsip_vview_d *b = vsip_vbind_d(block,500,5,10);
  
       vsip_blockadmit_d(vsip_vgetblock_d(a),VSIP_TRUE);
       vsip_vcopy_d_d(a,b);
       
       printf("val = vsip_vsumval_d(a)\n");
       printf("vector a\n");VU_vprintm_d("6.4",a);
       val = vsip_vsumval_d(b);
       printf("val %f\n",val);
       printf("right answer %7.4f\n",ans);
       if(vsip_mag_d(val-ans) < .0001)
           printf("correct\n");
       else
           printf("error\n");
       vsip_valldestroy_d(a);
       vsip_valldestroy_d(b);
    }
    return;
}
