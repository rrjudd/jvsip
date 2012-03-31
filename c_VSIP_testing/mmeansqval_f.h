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
/* $Id: mmeansqval_f.h,v 2.0 2003/02/22 15:23:25 judd Exp $ */
#include"VU_mprintm_f.include"
static void mmeansqval_f(void){
   printf("\n*******\nTEST mmeansqval_f\n");
   {
       vsip_scalar_f data[] = {1.0, 1.1, 1.2, 1.3, 1.4, 1.4, 1.3, 1.2, 1.1, 1.0};
       vsip_mview_f *m1 = vsip_mbind_f(
                 vsip_blockbind_f(data,10,VSIP_MEM_NONE),0,5,2,1,5);       
       vsip_block_f  *block = vsip_blockcreate_f(1024,VSIP_MEM_NONE);
       vsip_mview_f *m = vsip_mbind_f(block,4,20,2,2,5);
       vsip_blockadmit_f(vsip_mgetblock_f(m1),VSIP_TRUE);
       vsip_mcopy_f_f(m1,m);
       printf("matrix m1, user matrix, compact, row major\n");
       VU_mprintm_f("6.4",m1);
       printf("matrix m1, VSIPL matrix, irregular, row major\n");
       printf("col stride 20, row stride 2\n");
       printf("copy m1 to m. Matrix m equals\n");
       VU_mprintm_f("6.4",m);
       printf("mmeansqval_f(m1) = %f\n",vsip_mmeansqval_f(m1));
       printf("mmeansqval_f(m) = %f\n",vsip_mmeansqval_f(m));
       printf("ans should be 1.46 \n");
       if((fabs(1.4600-vsip_mmeansqval_f(m) > .0001)) ||
          (fabs(1.4600-vsip_mmeansqval_f(m1) > .0001))) {
          printf("error\n");
       }else{
           printf("correct\n");
       }
       vsip_malldestroy_f(m); vsip_malldestroy_f(m1);
    }
    return;
}
