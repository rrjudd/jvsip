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
/* $Id: vdot_f.h,v 2.1 2007/04/18 17:05:54 judd Exp $ */
static void vdot_f(void){
   printf("********\nTEST vdot_f\n");
   {
     vsip_scalar_f data1[] = {-1,  1,  0,   2, -2 };
     vsip_scalar_f data2[] = { 3,  .4, 1,  11,  2 };
     vsip_scalar_f ans = 15.4;
     vsip_scalar_f val = 0;
  
     vsip_block_f  *block1 = vsip_blockbind_f(data1,5,VSIP_MEM_NONE);
     vsip_block_f  *block2 = vsip_blockbind_f(data2,5,VSIP_MEM_NONE);
     vsip_vview_f  *a1 = vsip_vbind_f(block1,0,1,5);
     vsip_vview_f  *a2 = vsip_vbind_f(block2,0,1,5);
     vsip_vview_f  *b = vsip_vcreate_f(15,VSIP_MEM_NONE);
     vsip_vputlength_f(b,5); vsip_vputoffset_f(b,10); vsip_vputstride_f(b,-2);
     vsip_blockadmit_f(block1,VSIP_TRUE);
     vsip_blockadmit_f(block2,VSIP_TRUE);
     vsip_vcopy_f_f(a2,b);
     val = vsip_vdot_f(a1,b);
     printf("val = vsip_vdot_f(a,b)\n vector a\n");VU_vprintm_f("8.6",a1);
     printf("vector b\n");VU_vprintm_f("8.6",b);
     printf("val = %f\n",val);
     printf("right answer = %f\n",ans);

     if(fabs(ans - val) < .0001)
         printf("correct\n");
     else
         printf("error \n");

     vsip_valldestroy_f(a1);
     vsip_valldestroy_f(a2);
     vsip_valldestroy_f(b);
   }
   return;
}
