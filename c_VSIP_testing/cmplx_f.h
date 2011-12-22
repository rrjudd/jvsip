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
/* $Id: cmplx_f.h,v 2.0 2003/02/22 15:23:17 judd Exp $ */
static void cmplx_f(void){
   printf("********\nTEST cmplx_f\n");
   {
      vsip_scalar_f a_r = 1;
      vsip_scalar_f a_i = 2;
      vsip_cscalar_f s  = vsip_cmplx_f(a_r,a_i);
      printf("(%2.0f %+2.0fi) = vsip_cmplx_f(%2.0f,%2.0f)\n",a_r,a_i,s.r,s.i);
      (((a_r - s.r) == 0 ) && ((a_i - s.i) == 0)) ? 
                printf("correct\n") : printf("error\n");
      fflush(stdout);
   }
   return;
}
/* done */
