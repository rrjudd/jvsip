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
/* $Id: rect_f.h,v 2.0 2003/02/22 15:23:18 judd Exp $ */
static void rect_f(void){
   printf("********\nTEST rect_f\n");
   {
       vsip_cscalar_f ans = vsip_cmplx_f(3,4);
       vsip_scalar_f  r = 5;
       vsip_scalar_f  a = 0.927295218002;
       vsip_cscalar_f s = vsip_rect_f(r,a);
       printf("(%3.2f %+3.2fi) = vsip_rect_f(%5.4f,%5.4f);\n",s.r,s.i,r,a);
       (vsip_cmag_f(vsip_csub_f(ans,s)) > .0001 ) ? 
                  printf("error\n") : printf("correct\n");
       fflush(stdout);
   }
   return;
}
/* done */
