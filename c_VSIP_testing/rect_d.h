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
/* $Id: rect_d.h,v 2.0 2003/02/22 15:23:18 judd Exp $ */
static void rect_d(void){
   printf("********\nTEST rect_d\n");
   {
       vsip_cscalar_d ans = vsip_cmplx_d(3,4);
       vsip_scalar_d  r = 5;
       vsip_scalar_d  a = 0.927295218002;
       vsip_cscalar_d s = vsip_rect_d(r,a);
       printf("(%3.2f %+3.2fi) = vsip_rect_d(%5.4f,%5.4f);\n",s.r,s.i,r,a);
       (vsip_cmag_d(vsip_csub_d(ans,s)) > .0001 ) ? 
                  printf("error\n") : printf("correct\n");
       fflush(stdout);
   }
   return;
}
/* done */
