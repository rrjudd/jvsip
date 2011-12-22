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
/* $Id: mminval_d.h,v 2.0 2003/02/22 15:23:25 judd Exp $ */
static void mminval_d(void){
   printf("\n*******\nTEST mminval_d\n\n");
   { vsip_scalar_d data1[]  = {-1, 2, 0, -5, -6,  3.4, -3.4, 5.6, -.3};
     vsip_block_d  *block1 = vsip_blockbind_d(data1,9,VSIP_MEM_NONE);
     vsip_mview_d  *a = vsip_mbind_d(block1,0,3,3,1,3);
     vsip_block_d  *block2 = vsip_blockcreate_d(50,VSIP_MEM_NONE);
     vsip_mview_d  *b = vsip_mbind_d(block2,49,-2,3,-8,3);

     vsip_scalar_mi index;
     vsip_scalar_mi ind_ans = vsip_matindex(1,1);
     vsip_scalar_d val;

     vsip_blockadmit_d(block1,VSIP_TRUE);

     vsip_mcopy_d_d(a,b);

     val = vsip_mminval_d(a,&index);
     printf("val = vsip_mminval_d(a,index)\n matrix a = \n");VU_mprintm_d("8.6",a);
     printf("val = %f\n",val); 
     printf("index = (%ld, %ld)\n",vsip_colindex(index),vsip_rowindex(index));
     if(fabs(-6 - val) > .0001)
        printf("value error\n");
     else
        printf("value correct\n");
     if((vsip_colindex(index) != vsip_colindex(ind_ans)) ||
        (vsip_rowindex(index) != vsip_rowindex(ind_ans)))
        printf("index error\n");
     else
        printf("index correct\n");

     printf("case for non-compact matrix with negative strides\n");
     val = vsip_mminval_d(b,&index);
     printf("val = vsip_mminval_d(b,index)\n matrix b = \n");VU_mprintm_d("8.6",b);
     printf("val = %f\n",val); 
     printf("index = (%ld, %ld)\n",vsip_colindex(index),vsip_rowindex(index));
     if(fabs(-6 - val) > .0001)
        printf("value error\n");
     else
        printf("value correct\n");
     if((vsip_colindex(index) != vsip_colindex(ind_ans)) ||
        (vsip_rowindex(index) != vsip_rowindex(ind_ans)))
        printf("index error\n");
     else
        printf("index correct\n");

     vsip_malldestroy_d(a);
     vsip_malldestroy_d(b);
   }
   return;
}
