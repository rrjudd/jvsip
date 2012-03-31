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
/* $Id: cvmeansqval_d.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
#include"VU_cvprintm_d.include"
static void cvmeansqval_d(void){
   printf("********\nTEST cvmeansqval_d\n");
   {
     vsip_scalar_d data[] = {-1,.5,  1,13, 0,.1,  2,-3.2, -2,1.762 };
     vsip_scalar_d ans =38.5209;
     vsip_scalar_d val =99999;
     vsip_cblock_d  *block = vsip_cblockbind_d(data,NDPTR_d,5,VSIP_MEM_NONE);
     vsip_cvview_d  *a = vsip_cvbind_d(block,0,1,5);
     vsip_cblockadmit_d(block,VSIP_TRUE);
     val = vsip_cvmeansqval_d(a);
     printf("val = vsip_cvmeansqval_d(a)\n vector a\n");VU_cvprintm_d("8.6",a);
     printf("val = %f)\n",val);
     printf("right answer %7.4f\n",ans);
     if(vsip_mag_d(val - ans) < .0002)
          printf("correct\n");
     else
          printf("error\n");
   }
   return;
}
