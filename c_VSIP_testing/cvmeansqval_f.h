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
/* $Id: cvmeansqval_f.h,v 2.0 2003/02/22 15:23:23 judd Exp $ */
#include"VU_cvprintm_f.include"
static void cvmeansqval_f(void){
   printf("********\nTEST cvmeansqval_f\n");
   {
     vsip_scalar_f data[] = {-1,.5,  1,13, 0,.1,  2,-3.2, -2,1.762 };
     vsip_scalar_f ans =38.5209;
     vsip_scalar_f val =99999;
     vsip_cblock_f  *block = vsip_cblockbind_f(data,NDPTR_f,5,VSIP_MEM_NONE);
     vsip_cvview_f  *a = vsip_cvbind_f(block,0,1,5);
     vsip_cblockadmit_f(block,VSIP_TRUE);
     val = vsip_cvmeansqval_f(a);
     printf("val = vsip_cvmeansqval_f(a)\n vector a\n");VU_cvprintm_f("8.6",a);
     printf("val = %f)\n",val);
     printf("right answer %7.4f\n",ans);
     if(vsip_mag_f(val - ans) < .0002)
          printf("correct\n");
     else
          printf("error\n");
   }
   return;
}
