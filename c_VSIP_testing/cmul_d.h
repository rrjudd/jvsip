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
/* $Id: cmul_d.h,v 2.0 2003/02/22 15:23:17 judd Exp $ */
static void cmul_d(void){
   printf("********\nTEST cmul_d\n");
   {
       vsip_cscalar_d a = vsip_cmplx_d(6.5,-.5);
       vsip_cscalar_d x = vsip_cmplx_d(-1.5,-2.5);
       vsip_cscalar_d y = vsip_cmplx_d(-1,2);
       vsip_cscalar_d b = vsip_cmul_d(x,y);
       printf("(%5.4f %+5.4fi) = vsip_cmul_d((%5.4f %+5.4fi),(%5.4f %+5.4fi))\n ",
                             b.r,b.i,x.r,x.i,y.r,y.i); 
       ((vsip_cmag_d(vsip_csub_d(a,b))) > .0001) ? printf("error\n") :
                             printf("correct\n");
       fflush(stdout);
   }
   return;
}
/* done */
