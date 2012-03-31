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
/* $Id: vcminmgsqval_d.h,v 2.1 2009/09/05 18:01:45 judd Exp $ */
#include"VU_cvprintm_d.include"
static void vcminmgsqval_d(void){
   printf("********\nTEST vcminmgsqval_d\n");
   {
     vsip_scalar_d data_a_i[] = { 1.1, 1.2, 2.1, 2.2, -3.1, -3.3};
     vsip_scalar_d data_a_r[] = { 2.1, 3.2, -2.1, -2.2, +5.1, +5.3};
     vsip_scalar_d ans = 5.62;
     vsip_scalar_d val = 0;
     vsip_index  ans_ind = 0; 
     vsip_index  ind = 9999;
     vsip_cblock_d  *block_a = vsip_cblockbind_d(data_a_r,data_a_i,6,VSIP_MEM_NONE);
     vsip_cvview_d  *a = vsip_cvbind_d(block_a,0,1,6);
     vsip_cblockadmit_d(block_a,VSIP_TRUE);
     val = vsip_vcminmgsqval_d(a,&ind);
     printf("vector |a>\n"),VU_cvprintm_d("6.4",a);
     printf("val = vsip_vcminmgsqval_d(a,&ind)\n");
     printf("val = %f\nexpected answer %f\n",val,ans);
     printf("ind = %u\nexpected index %u\n",(unsigned)ind,(unsigned)ans_ind);

     if(fabs(val - ans) < .0001)
        printf("val correct\n");
     else
        printf("val in error\n");

     if(ind == ans_ind)
        printf("index correct\n");
     else
        printf("index in error\n");

     vsip_cvalldestroy_d(a);
   }
   return;
}
